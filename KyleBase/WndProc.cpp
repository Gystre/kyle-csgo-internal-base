#include "pch.h"
#include "Hooks.h"
#include "Interfaces.h"
#include "Gui.h"
#include "Config.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"

LRESULT __stdcall Hooks::hkWndProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
{
    [[maybe_unused]] static const auto once = [](HWND window) noexcept {
        ImGui::CreateContext();
        ImGui_ImplWin32_Init(window);

        config = std::make_unique<Config>("CSGO White Fire Internal Configs");

        Gui::Get().init();

        //init hooks, ensures that config will exist
        Hooks::init();

        if (!initGuiHook())
        {
            std::cout << "Failed to hook one of the gui functions" << std::endl;
        }

        return true;
    }(window);

    LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    ImGui_ImplWin32_WndProcHandler(window, msg, wParam, lParam);

    Interfaces::inputSystem->enableInput(!Gui::Get().isOpen());

    return CallWindowProcW(oWndProc, window, msg, wParam, lParam);
}