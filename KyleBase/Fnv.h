#pragma once
#include <string>

class FnvHash
{
private:
	struct Wrapper {
		Wrapper(const char* str) : str(str) { }
		const char* str;
	};

	static const unsigned int prime = 16777619u;
	static const unsigned int basis = 2166136261u;

	template <unsigned int n>
	static constexpr unsigned int fnvHashConst(const char(&str)[n], unsigned int i = n)
	{
		return i == 1 ? (basis ^ str[0]) * prime : (fnvHashConst(str, i - 1) ^ str[i - 1]) * prime;
	}

	static unsigned int hash(const char* str)
	{
		const size_t length = strlen(str) + 1;
		unsigned int hash = basis;

		for (size_t i = 0; i < length; ++i)
		{
			hash ^= *str++;
			hash *= prime;
		}

		return hash;
	}

	unsigned int hashValue;

public:
	FnvHash(Wrapper wrap) : hashValue(hash(wrap.str)) { }

	template <unsigned int n>
	constexpr FnvHash(const char(&str)[n]) : hashValue(FnvHashConst(str)) { }

	constexpr operator unsigned int() const
	{
		return this->hashValue;
	}
};