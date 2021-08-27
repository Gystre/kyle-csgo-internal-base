#pragma once
#include "RecvProps.h"
#include "ClassId.h"
#include "WeaponId.h"

using CreateClientClass_t = void* (*)(int entityNum, int serialNum);
using CreateEvent_t = void* (*)();

class ClientClass {
public:
	CreateClientClass_t createFn;
	CreateEvent_t createEventFn;
	char* networkName;
	RecvTable* recvTablePtr;
	ClientClass* nextPtr;
	int classId;
	WeaponId weaponId;
};