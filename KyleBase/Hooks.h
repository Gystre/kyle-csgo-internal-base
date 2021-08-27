#pragma once

#include <d3d9.h>
#include <d3d9types.h>

#include "CUserCmd.h"
#include "MinHook.h"

namespace Hooks {
	extern HWND window;
	extern HMODULE moduleHandle;

	bool __fastcall hkCreateMove(uintptr_t ecx, uintptr_t edx, float frameTime, CUserCmd* userCmd);
	void __stdcall hkLockCursor();

	//gui hooks
	extern uintptr_t oPresentAddress;
	extern std::add_pointer_t<HRESULT __stdcall(IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA*)> oPresent;
	HRESULT __stdcall hkPresent(IDirect3DDevice9* device, const RECT* src, const RECT* dest, HWND windowOverride, const RGNDATA* dirtyRegion);
	
	extern uintptr_t oResetAddress;
	extern std::add_pointer_t <HRESULT __stdcall (IDirect3DDevice9*, D3DPRESENT_PARAMETERS*)> oReset;
	HRESULT __stdcall hkReset(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* params);

	extern std::add_pointer_t<LRESULT __stdcall(HWND, UINT, WPARAM, LPARAM)> oWndProc;
	LRESULT __stdcall hkWndProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);

	extern MinHook clientMode;
	extern MinHook surface;

	void initWndProcHook();
	void init();
	bool initGuiHook();
	void shutdown();
}