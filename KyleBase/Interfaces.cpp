#include "pch.h"
#include "Interfaces.h"

//brute forcing for now cuz it's simple and fast
template <typename T>
T* getInterface(const char* mod, const char* iface)
{
	void* interfaceAddress = nullptr;

	using CreateInterface_t = void* (*)(const char*, int*);
	auto CreateInterface = reinterpret_cast<CreateInterface_t>(GetProcAddress(GetModuleHandleA(mod), "CreateInterface"));

	//loop through 100 possible names
	char possibleInterfaceName[1024];
	for (int i = 1; i < 100; i++)
	{
		//apparently do it twice b/c sometimes u just don't get it the first time around
		sprintf_s(possibleInterfaceName, "%s0%i", iface, i);
		interfaceAddress = CreateInterface(possibleInterfaceName, NULL);
		if (interfaceAddress)
			break;

		sprintf_s(possibleInterfaceName, "%s00%i", iface, i);
		interfaceAddress = CreateInterface(possibleInterfaceName, NULL);
		if (interfaceAddress)
			break;
	}

	if (!interfaceAddress)
		std::cout << iface << " not found!" << std::endl;
	else
		std::cout << iface << " 0x" << interfaceAddress << std::endl;

	return (T*)interfaceAddress;
}

namespace Interfaces
{
	IBaseClientDll* clientDll = nullptr;
	IClientMode* clientMode = nullptr;
	IClientEntityList* entityList = nullptr;
	IEngineClient* engine = nullptr;
	CGlobalVars* globals = nullptr;
	IInputSystem* inputSystem;
	ISurface* surface = nullptr;
	IPanel* panel = nullptr;

	void init()
	{
		clientDll = getInterface<IBaseClientDll>("client.dll", "VClient");
		clientMode = **reinterpret_cast<IClientMode***>((*reinterpret_cast<uintptr_t**>(clientDll))[10] + 5); //update
		globals = **reinterpret_cast<CGlobalVars***>((*reinterpret_cast<uintptr_t**>(clientDll))[11] + 10);
		entityList = getInterface<IClientEntityList>("client.dll", "VClientEntityList");
		engine = getInterface<IEngineClient>("engine.dll", "VEngineClient");
		inputSystem = getInterface<IInputSystem>("inputsystem.dll", "InputSystemVersion");
		surface = getInterface<ISurface>("vguimatsurface.dll", "VGUI_Surface");
		panel = getInterface<IPanel>("vgui2.dll", "VGUI_Panel");
	}
}