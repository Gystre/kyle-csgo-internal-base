#include "pch.h"
#include "Hooks.h"
#include "Interfaces.h"
#include "HacksContainer.h"

bool __fastcall Hooks::hkCreateMove(uintptr_t ecx, uintptr_t edx, float frameTime, CUserCmd* userCmd)
{
	C_BaseEntity* localPlayer = Interfaces::entityList->getClientEntity(Interfaces::engine->getLocalPlayer());

	if (localPlayer)
	{
		Interfaces::globals->serverTime(userCmd);

		for (auto hack : HacksContainer::Get().hacks)
		{
			hack->UpdateCreateMove(localPlayer, userCmd);
		}
	}

	return false;
}