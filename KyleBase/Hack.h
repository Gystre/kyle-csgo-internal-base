#pragma once

#include "CBaseEntity.h"
#include "CUserCmd.h"
#include "ModelRenderInfo.h"
#include <d3d9.h>

class Hack
{
private:
	//probably gonna have generic stuff like name, enabled, and hotkey here eventually
public:
	virtual void UpdateCreateMove(C_BaseEntity* localPlayer, CUserCmd* userCmd) {}
	virtual void UpdatePaintTraverse(C_BaseEntity* localPlayer) {};
};

