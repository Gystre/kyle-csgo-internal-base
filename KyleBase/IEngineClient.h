#pragma once

#include "Vector3.h"
#include "PlayerInfo.h"
#include "VirtualMethod.h"
#include <d3d9.h>

class IEngineClient
{
public:
	int getLocalPlayer() {
		//if this doesn't work then just return 0
		using original_fn = int(__thiscall*)(IEngineClient*);
		return (*(original_fn**)this)[12](this);
	}

	int getPlayerFromUserId(int user_id) {
		using original_fn = int(__thiscall*)(IEngineClient*, int);
		return (*(original_fn**)this)[9](this, user_id);
	}

	VIRTUAL_METHOD(bool, getPlayerInfo, 8, (int entityIndex, PlayerInfo& playerInfo), (this, entityIndex, std::ref(playerInfo)))

	void getScreenSize(int& width, int& height) {
		using original_fn = void(__thiscall*)(IEngineClient*, int&, int&);
		return (*(original_fn**)this)[5](this, width, height);
	}

	void executeCmd(const char* cmd) {
		using original_fn = void(__thiscall*)(IEngineClient*, const char*);
		return (*(original_fn**)this)[108](this, cmd); // this always seems to crash whilst debugging, just feel free to continue.
	}

	void setViewAngles(Vector3& angles) {
		using original_fn = void(__thiscall*)(IEngineClient*, Vector3&);
		return (*(original_fn**)this)[19](this, angles);
	}

	Vector3 getViewAngles() {
		Vector3 temp;
		using original_fn = void(__thiscall*)(IEngineClient*, Vector3&);
		(*(original_fn**)this)[18](this, temp);
		return temp;
	}

	bool isConnected() {
		using original_fn = bool(__thiscall*)(IEngineClient*);
		return (*(original_fn**)this)[27](this);
	}

	bool isInGame() {
		using original_fn = bool(__thiscall*)(IEngineClient*);
		return (*(original_fn**)this)[26](this);
	}

	VIRTUAL_METHOD(int, getMaxClients, 20, (), (this))
	VIRTUAL_METHOD(const D3DMATRIX&, worldToScreenMatrix, 37, (), (this))
};