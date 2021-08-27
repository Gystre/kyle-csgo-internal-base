#pragma once

enum EntityFlags
{
	FL_ONGROUND = (1 << 0),
	FL_DUCKING = (1 << 1),
	FL_WATERJUMP = (1 << 2),	// player jumping out of water
	FL_ONTRAIN = (1 << 3),		// player is _controlling_ a train, so movement commands should be ignored on client during prediction.
	FL_INRAIN = (1 << 4),
	FL_FROZEN = (1 << 5),		// player is frozen for 3rd person camera
	FL_ATCONTROLS = (1 << 6),	// player can't move, but keeps key inputs for controlling another entity
	FL_CLIENT = (1 << 7),		// is a player
	FL_FAKECLIENT = (1 << 8),	// fake client, simulated server side; don't send network messages to them
	FL_INWATER = (1 << 10),
};