#pragma once

#include "Hack.h"

class BunnyHop : public Hack
{
public:
	void UpdateCreateMove(C_BaseEntity* localPlayer, CUserCmd* userCmd);
};