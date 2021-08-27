#pragma once

#include "Vector3.h"

class CUserCmd {
public:
	virtual ~CUserCmd() = default;

	int commandNumber;
	int tickCount;
	Vector3 viewAngles;
	Vector3 aimDirection;
	float forwardMove;
	float sideMove;
	float upMove;
	int buttons;
	unsigned char impulse;
	int weaponSelect;
	int weaponSubType;
	int randomSeed;
	short mouseDx;
	short mouseDy;
	bool hasBeenPredicted;
	char pad_0x4c[0x18];
};
