#include "pch.h"
#include "Hooks.h"
#include "Gui.h"
#include "Interfaces.h"

void __stdcall Hooks::hkLockCursor()
{
	//unlock the cursor when the gui is open
	if (Gui::Get().isOpen())
		return Interfaces::surface->unlockCursor();

	return surface.callOriginal<void, 67>();
}