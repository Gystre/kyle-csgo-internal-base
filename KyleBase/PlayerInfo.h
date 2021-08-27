#pragma once

#include <stdint.h>

struct PlayerInfo {
	int64_t __pad0;
	union {
		int64_t xuid;
		struct {
			int xuidLow;
			int xuidHigh;
		};
	};
	char name[128];
	int userId;
	char guid[33];
	unsigned int friendsId;
	char friendsName[128];
	bool fakePlayer;
	bool isHltv;
	unsigned int customFiles[4];
	unsigned char filesDownloaded;
};