#pragma once

#include <minwindef.h>
#include <string>
#include "Singleton.h"
#include "Color.h"

enum FontFlags {
	fontflag_none,
	fontflag_italic = 0x001,
	fontflag_underline = 0x002,
	fontflag_strikeout = 0x004,
	fontflag_symbol = 0x008,
	fontflag_antialias = 0x010,
	fontflag_gaussianblur = 0x020,
	fontflag_rotary = 0x040,
	fontflag_dropshadow = 0x080,
	fontflag_additive = 0x100,
	fontflag_outline = 0x200,
	fontflag_custom = 0x400,
	fontflag_bitmap = 0x800,
};

class Render : public Singleton<Render>
{
public:
	DWORD mainFont;
	DWORD espFont;

	void setupFonts();

	void drawLine(int x1, int y1, int x2, int y2, Color color);
	void drawText(int x, int y, unsigned long font, const char* string, Color color, bool textCentered = true);
	void drawText(int x, int y, unsigned long font, std::string string, Color color, bool textCentered = true);
	void drawFilledRect(int x, int y, int w, int h, Color color);
	void drawOutline(int x, int y, int w, int h, Color color);
	void drawCircle(int x, int y, float points, float radius, Color color);
};