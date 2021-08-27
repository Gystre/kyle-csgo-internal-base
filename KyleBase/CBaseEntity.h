#pragma once

#include "VirtualMethod.h"
#include "Netvars.h"
#include "Vector3.h"
#include "EMoveType.h"

class C_BaseEntity
{
public:
	NetvarFn(int, getHealth, "DT_BasePlayer", "m_iHealth");
	NetvarFn(int, getTeam, "DT_BaseEntity", "m_iTeamNum");
	NetvarFn(int, getFflags, "DT_BasePlayer", "m_fFlags");
	NetvarFn(Vector3, getVecOrigin, "DT_BaseEntity", "m_vecOrigin");
	NetvarFn(Vector3, getVecViewOffset, "DT_BasePlayer", "m_vecViewOffset[0]");
	NetvarFn(MoveType, getMoveType, "DT_BaseEntity", "m_nRenderMode");
	OffsetFn(bool, isDormant, 0xED);
	NetvarFn(int, getTickBase, "DT_BasePlayer", "m_nTickBase");

	Vector3 getEyePosition()
	{
		return getVecOrigin() + getVecViewOffset();
	}
};