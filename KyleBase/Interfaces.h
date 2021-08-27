#pragma once

#include "IBaseClientDll.h"
#include "IPanel.h"
#include "ISurface.h"
#include "IInputSystem.h"
#include "IClientMode.h"
#include "IClientEntityList.h"
#include "IEngineClient.h"
#include "CGlobalVars.h"

namespace Interfaces
{
	extern IBaseClientDll* clientDll;
	extern IClientMode* clientMode;
	extern IClientEntityList* entityList;
	extern IEngineClient* engine;
	extern CGlobalVars* globals;
	extern IInputSystem* inputSystem;
	extern ISurface* surface;
	extern IPanel* panel;

	extern void init();
}