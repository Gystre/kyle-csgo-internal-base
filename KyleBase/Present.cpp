#include "pch.h"
#include "Hooks.h"
#include "Gui.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_impl_win32.h"

HRESULT __stdcall Hooks::hkPresent(IDirect3DDevice9* device, const RECT* src, const RECT* dest, HWND windowOverride, const RGNDATA* dirtyRegion) {
    [[maybe_unused]] static bool imguiInit{ ImGui_ImplDX9_Init(device) };

    auto& Gui = Gui::Get();

    ImGui_ImplDX9_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    Gui.handleToggle();

    if (Gui.isOpen())
        Gui.render();

    ImGui::EndFrame();
    ImGui::Render();

    if (device->BeginScene() == D3D_OK) {
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
        device->EndScene();
    }

    return oPresent(device, src, dest, windowOverride, dirtyRegion);
}