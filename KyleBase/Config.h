#pragma once

#include "Color.h"

//smart pointer cuz more convienent to select :P
class Config
{
public:
	Config(const char* name);

	constexpr auto& getConfigs() noexcept
	{
		return configs;
	}

	void listConfigs();

	//load by id
	void load(size_t id);

	//load by name
	void load(const char8_t* name);

	void save(size_t id);
	void openConfigDir();
	void add(const char* name);
	void remove(size_t id);
	void rename(size_t item, const char* newName);

	struct Misc
	{
		bool bunnyHop = false;
	} misc;

private:
	void createConfigDir();

	std::filesystem::path path;

	//the list of configs that will be displayed in the menu
	std::vector<std::string> configs;
};

inline std::unique_ptr<Config> config;