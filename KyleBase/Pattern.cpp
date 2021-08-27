#include "pch.h"
#include "pattern.h"



std::pair<void*, std::size_t> getModuleInformation(const char* name) noexcept
{
	if (HMODULE handle = GetModuleHandleA(name)) {
		if (MODULEINFO moduleInfo; GetModuleInformation(GetCurrentProcess(), handle, &moduleInfo, sizeof(moduleInfo)))
			return std::make_pair(moduleInfo.lpBaseOfDll, moduleInfo.SizeOfImage);
	}
	return {};
}

Pattern::Pattern::Pattern(const std::string& str) {
	std::string part;
	if (str.empty())
		return;

	auto ss = std::stringstream(str);

	// iterate string stream, splitting by space delim.
	do {
		// too long...
		if (part.empty() || part.size() > 2)
			continue;

		// ensure it's a valid wildcard or byte.
		if (part[0] == '?')
			m_pattern.push_back({});

		else if (std::isxdigit(static_cast<uint8_t>(part[0])) && std::isxdigit(static_cast<uint8_t>(part[1])))
			m_pattern.push_back({ static_cast<uint8_t>(std::strtoul(part.c_str(), nullptr, 16)), false });
	} while (ss >> part);
}

uintptr_t Pattern::find(uintptr_t start, size_t len, const Pattern& pattern) {
	static auto search_pred = [](const uint8_t a, const PatternByte_t& b) {
		return b.match(a);
	};

	if (!start || !len || pattern.empty())
		return 0;

	uint8_t* scan_start = reinterpret_cast<uint8_t*>(start);
	uint8_t* scan_end = scan_start + len;

	auto it = std::search(
		scan_start,
		scan_end,
		pattern.begin(),
		pattern.end(),
		search_pred
	);

	// nothing found...
	if (it == scan_end)
		return 0;

	return reinterpret_cast<uintptr_t>(it);
}

// scan for pattern in range.
uintptr_t Pattern::find(uintptr_t start, size_t len, const std::string& pattern) {
	return find(start, len, Pattern(pattern));
}

// scan for pattern in entire module by module name string.
uintptr_t Pattern::find(const char* str, const std::string& pattern) {
	const auto [moduleBase, moduleSize] = getModuleInformation(str);

	if (!moduleBase || !moduleSize)
		return 0;

	return find((uintptr_t)moduleBase, moduleSize, pattern);
}
