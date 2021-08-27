#include "pch.h"
#include "Interfaces.h"
#include "Netvars.h"
#include "Hooks.h"
#include "HacksContainer.h"

//can't manual map in debug mode????
//ah well will just use extreme injector
void WINAPI start() noexcept
{
#ifdef _DEBUG
    AllocConsole();
    freopen_s((FILE**)stdin, "CONIN$", "r", stdin);
    freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
    SetConsoleTitleA("White Fire Internal");
#endif

    //init interfaces
    Interfaces::init();
    std::cout << "Initialized interfaces!" << std::endl;

    //init netvars
    NetvarManager::Get().init();
    std::cout << "Dumped netvars!" << std::endl;

    //init hacks
    HacksContainer::Get().Init();

    //init first hook
    Hooks::initWndProcHook();
    //and there's ur hack

    while (!GetAsyncKeyState(VK_END))
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

    //clean up hook
    Hooks::shutdown();

    //gui clean up is handled in thread created by hooks

#ifdef _DEBUG
    fclose((FILE*)stdin);
    fclose((FILE*)stdout);
    FreeConsole();
#endif
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        Hooks::moduleHandle = hModule;
        if (HANDLE thread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)start, NULL, NULL, NULL))
            CloseHandle(thread);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
