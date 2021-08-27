#pragma once

#include "CUserCmd.h"

class CGlobalVars
{
public:
	float realTime;
	int frameCount;
	float absoluteFrameTime;
	float absoluteFrameStartTime;
	float curTime;
	float frameTime;
	int maxClients;
	int tickCount;
	float intervalPerTick;
	float interpolationAmount;
	int simTicksThisFrame;
	int networkProtocol;
	void* pSaveData;
	bool isClient;
	bool isRemoteClient;
	int timeStampNetworkingBase;
	int timeStampRandomizeWindow;

	float serverTime(CUserCmd* userCmd = nullptr) noexcept;
};