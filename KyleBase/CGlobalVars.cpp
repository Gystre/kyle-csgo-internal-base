#include "pch.h"
#include "CGlobalVars.h"
#include "CBaseEntity.h"
#include "Interfaces.h"

float CGlobalVars::serverTime(CUserCmd* cmd) noexcept
{
    static int tick;
    static CUserCmd* lastCmd;
    static C_BaseEntity* localPlayer = Interfaces::entityList->getClientEntity(Interfaces::engine->getLocalPlayer());

    if (cmd) {
        if (localPlayer && (!lastCmd || lastCmd->hasBeenPredicted))
            tick = localPlayer->getTickBase();
        else
            tick++;
        lastCmd = cmd;
    }
    return tick * intervalPerTick;
}
