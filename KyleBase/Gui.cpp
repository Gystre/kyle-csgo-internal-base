#include "pch.h"
#include "Gui.h"
#include "Config.h"
#include "Interfaces.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_stdlib.h"

void Gui::init()
{
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();

    style.ScrollbarSize = 9.0f;

    ImGuiIO& io = ImGui::GetIO();
    io.IniFilename = nullptr;
    io.LogFilename = nullptr;
    io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
}

void Gui::handleToggle()
{
	static bool isDown = false;
	static bool isClicked = false;
	if (GetAsyncKeyState(VK_INSERT))
	{
		isClicked = false;
		isDown = true;
	}
	else if (!GetAsyncKeyState(VK_INSERT) && isDown)
	{
		isClicked = true;
		isDown = false;
	}
	else
	{
		isClicked = false;
		isDown = false;
	}

	if (isClicked)
	{
		open = !open;
		if (!open)
			Interfaces::inputSystem->resetInputState();
	}
}

void Gui::drawAimbotTab()
{
	ImGui::BeginChild("aimbot", ImVec2(810, 555), true);
	{
		ImGui::Checkbox("Bunny Hop", &config->misc.bunnyHop);
	}
	ImGui::EndChild();
}

void Gui::drawVisualsTab()
{

}

void Gui::drawBacktrackTab()
{

}


void Gui::drawMiscTab()
{

}

void Gui::drawConfigTab()
{
	ImGui::Columns(2, nullptr, false);
	ImGui::SetColumnOffset(1, 170.0f);

	ImGui::PushItemWidth(160.0f);

	auto& configItems = config->getConfigs();
	static int currentConfig = -1;

	//refresh the configs
	static std::string buffer;
	timeToNextConfigRefresh -= ImGui::GetIO().DeltaTime;
	if (timeToNextConfigRefresh <= 0.0f)
	{
		config->listConfigs();
		if (const auto it = std::find(configItems.begin(), configItems.end(), buffer); it != configItems.end())
			currentConfig = std::distance(configItems.begin(), it);
		timeToNextConfigRefresh = 0.1f;
	}

	if (static_cast<std::size_t>(currentConfig) >= configItems.size())
		currentConfig = -1;

	if (ImGui::ListBox("", &currentConfig, [](void* data, int idx, const char** out_text) {
		auto& vector = *static_cast<std::vector<std::string>*>(data);
		*out_text = vector[idx].c_str();
		return true;
		}, &configItems, configItems.size(), 5) && currentConfig != -1)
		buffer = configItems[currentConfig];

		ImGui::PushID(0);
		if (ImGui::InputTextWithHint("", "config name", &buffer, ImGuiInputTextFlags_EnterReturnsTrue)) {
			if (currentConfig != -1)
				config->rename(currentConfig, buffer.c_str());
		}
		ImGui::PopID();
		ImGui::NextColumn();

		if (ImGui::Button("Open config directory"))
			config->openConfigDir();

		if (ImGui::Button("Create config", { 100.0f, 25.0f }))
			config->add(buffer.c_str());

		if (currentConfig != -1) {
			if (ImGui::Button("Load selected", { 100.0f, 25.0f })) {
				config->load(currentConfig);
			}
			if (ImGui::Button("Save selected", { 100.0f, 25.0f }))
				config->save(currentConfig);
			if (ImGui::Button("Delete selected", { 100.0f, 25.0f })) {
				config->remove(currentConfig);

				if (static_cast<std::size_t>(currentConfig) < configItems.size())
					buffer = configItems[currentConfig];
				else
					buffer.clear();
			}
		}

		ImGui::Columns(1);
}

void Gui::render()
{
	ImGui::SetNextWindowSize(ImVec2(850, 700));
	ImGui::Begin("White Fire Internal - by Kyle", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
	{
		static char buttons[][16] = { "Aimbot", "Visuals", "Backtrack", "Misc", "Config" };

		static int iTab = 0;
		for (int i = 0; i < 5; i++)
		{
			if (i > 0) ImGui::SameLine(0.0f, -0.3f);

			if (ImGui::Button(buttons[i], ImVec2(160, 30)))
				iTab = i;
		}
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();

		switch (iTab) {
		case 0: drawAimbotTab(); break;
		case 1: drawVisualsTab(); break;
		case 2: drawBacktrackTab(); break;
		case 3: drawMiscTab(); break;
		case 4: drawConfigTab(); break;
		}

	}
	ImGui::End();
}

void Gui::shutdown()
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}