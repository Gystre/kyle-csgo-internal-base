#pragma once

#include "Singleton.h"

class Gui : public Singleton<Gui> {
public:
	void init();
	void render();
	void handleToggle();
	bool isOpen() { return open; }

	void shutdown();

private:
	void drawAimbotTab();
	void drawVisualsTab();
	void drawBacktrackTab();
	void drawMiscTab();
	void drawConfigTab();

	bool open = true;
	float timeToNextConfigRefresh = 0.1f;
};