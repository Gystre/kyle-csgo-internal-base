#include "pch.h"
#include "Config.h"
#include "nlohmann/json.hpp"
#include <shellapi.h>

using json = nlohmann::json;
using value_t = json::value_t;

Config::Config(const char* name)
{
    if (PWSTR pathToDocuments; SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Documents, 0, nullptr, &pathToDocuments))) {
        path = pathToDocuments;
        CoTaskMemFree(pathToDocuments);
    }

    path /= name;

    //find the names of the configs
    listConfigs();

    load(u8"default.json");
}

void Config::listConfigs()
{
    configs.clear();

    std::error_code ec;
    std::transform(std::filesystem::directory_iterator{ path, ec },
        std::filesystem::directory_iterator{ },
        std::back_inserter(configs),
        [](const auto& entry) { return std::string{ (const char*)entry.path().filename().u8string().c_str() }; });
}

void Config::load(size_t id)
{
    load((const char8_t*)configs[id].c_str());
}

void Config::load(const char8_t* name)
{
    json j;

    //make sure the file exists
    if (std::ifstream in{ path / name }; in.good()) {
        j = json::parse(in, nullptr, false);
        if (j.is_discarded())
            return;
    }
    else {
        return;
    }

    misc.bunnyHop = j["Misc"]["BunnyHop"];
}

void Config::createConfigDir()
{
    std::error_code ec; std::filesystem::create_directory(path, ec);
}

void Config::openConfigDir()
{
    createConfigDir();
    ShellExecuteA(NULL, "open", path.string().c_str(), NULL, NULL, SW_SHOWDEFAULT);
}

void Config::save(size_t id)
{
    createConfigDir();

    std::filesystem::path file = path / configs[id].c_str();
    file.replace_extension(".json");
    std::ofstream out{ file.c_str() };
    if (out.good())
    {
        json j;

        j["Misc"]["BunnyHop"] = misc.bunnyHop;

        //would erase empty objects here but not sure if need to

        out << std::setw(2) << j;
    }
}

void Config::add(const char* name)
{
    if (*name && std::find(configs.cbegin(), configs.cend(), name) == configs.cend()) {
        configs.emplace_back(name);
        save(configs.size() - 1);
    }
}

void Config::remove(size_t id)
{
    std::error_code ec;
    std::filesystem::remove(path / (const char8_t*)configs[id].c_str(), ec);
    configs.erase(configs.cbegin() + id);
}

void Config::rename(size_t item, const char* newName)
{
    std::error_code ec;
    std::filesystem::rename(path / (const char8_t*)configs[item].c_str(), path / (const char8_t*)newName, ec);
    configs[item] = newName;
}