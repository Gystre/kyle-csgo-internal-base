#include "pch.h"
#include "Hooks.h"

#include "imgui/imgui_impl_dx9.h"

HRESULT __stdcall Hooks::hkReset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params) {
	//prevent memory leak between csgo ui resets
	ImGui_ImplDX9_InvalidateDeviceObjects();

	return oReset(device, params);
}