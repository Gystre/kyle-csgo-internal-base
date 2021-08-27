#include "pch.h"
#include "BunnyHop.h"
#include "Interfaces.h"
#include "EEntityFlags.h"
#include "ECmdButtons.h"
#include "Config.h"

void BunnyHop::UpdateCreateMove(C_BaseEntity* localPlayer, CUserCmd* userCmd)
{
	if (!config->misc.bunnyHop)
		return;

	static bool jumped_last_tick = false;
	static bool should_fake_jump = false;

	if (localPlayer->getMoveType() == MOVETYPE_LADDER || localPlayer->getMoveType() == MOVETYPE_NOCLIP || localPlayer->getFflags() & FL_INWATER) return;

	if (!jumped_last_tick && should_fake_jump) {
		should_fake_jump = false;
		userCmd->buttons |= in_jump;
	}
	else if (userCmd->buttons & in_jump) {
		if (localPlayer->getFflags() & FL_ONGROUND) {
			jumped_last_tick = true;
			should_fake_jump = true;
		}
		else {
			userCmd->buttons &= ~in_jump;
			jumped_last_tick = false;
		}
	}
	else {
		jumped_last_tick = false;
		should_fake_jump = false;
	}
}