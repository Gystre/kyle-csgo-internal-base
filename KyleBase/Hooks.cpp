#include "pch.h"
#include "Hooks.h"

#include "Interfaces.h"
#include "HacksContainer.h"
#include "Pattern.h"
#include "Gui.h"
#include "MinHook/MinHook.h"
#include "Render.h"

namespace Hooks
{
	HWND window;
	HMODULE moduleHandle;

	uintptr_t oPresentAddress;
	std::add_pointer_t<HRESULT __stdcall(IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA*)> oPresent;
	uintptr_t oResetAddress;
	std::add_pointer_t <HRESULT __stdcall (IDirect3DDevice9*, D3DPRESENT_PARAMETERS*)> oReset;
	std::add_pointer_t<LRESULT __stdcall(HWND, UINT, WPARAM, LPARAM)> oWndProc;

	MinHook clientMode;
	MinHook surface;
}

//need to hook this one first to ensure that the config and menu exist first
//wndproc will call Hooks::Init();
void Hooks::initWndProcHook()
{
	_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
	_MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);

	//WndProc will hook the rest of the gui
	window = FindWindowW(L"Valve001", nullptr);
	oWndProc = WNDPROC(SetWindowLongPtrW(window, GWLP_WNDPROC, LONG_PTR(hkWndProc)));
}

void Hooks::init()
{
	Render::Get().setupFonts();

	MH_Initialize();

	clientMode.init(Interfaces::clientMode);
	clientMode.hookAt(24, &hkCreateMove);

	surface.init(Interfaces::surface);
	surface.hookAt(67, &hkLockCursor);

	MH_EnableHook(MH_ALL_HOOKS);
}

bool Hooks::initGuiHook()
{
	//hook the reset and present functions
	oPresentAddress = Pattern::find("gameoverlayrenderer.dll", "FF 15 ?? ?? ?? ?? 8B F0 85 FF") + 2;
	oPresent = **reinterpret_cast<decltype(oPresent)**>(oPresentAddress);
	**reinterpret_cast<decltype(hkPresent)***>(oPresentAddress) = hkPresent;

	oResetAddress = Pattern::find("gameoverlayrenderer.dll", "C7 45 ?? ?? ?? ?? ?? FF 15 ?? ?? ?? ?? 8B D8") + 9;
	oReset = **reinterpret_cast<decltype(oReset)**>(oResetAddress);
	**reinterpret_cast<decltype(hkReset)***>(oResetAddress) = hkReset;

	return true;
}

extern "C" BOOL WINAPI _CRT_INIT(HMODULE moduleHandle, DWORD reason, LPVOID reserved);

static DWORD WINAPI unloadGui(HMODULE moduleHandle) noexcept
{
	Sleep(100);

	Interfaces::inputSystem->enableInput(true);

	Gui::Get().shutdown();

	_CRT_INIT(moduleHandle, DLL_PROCESS_DETACH, nullptr);

	FreeLibraryAndExitThread(moduleHandle, 0);
}

void Hooks::shutdown()
{
	clientMode.restore();

	//clean up wnd proc hook
	SetWindowLongPtrW(window, GWLP_WNDPROC, LONG_PTR(oWndProc));
	**reinterpret_cast<void***>(oPresentAddress) = oPresent;
	**reinterpret_cast<void***>(oResetAddress) = oReset;

	MH_DisableHook(MH_ALL_HOOKS);
	MH_Uninitialize();

	if (HANDLE thread = CreateThread(nullptr, 0, LPTHREAD_START_ROUTINE(unloadGui), moduleHandle, NULL, nullptr))
		CloseHandle(thread);
}