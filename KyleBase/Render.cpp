#include "pch.h"
#include "Render.h"
#include "Interfaces.h"
#include "Vector2.h"

void Render::setupFonts()
{
	mainFont = Interfaces::surface->createFont();
	Interfaces::surface->setFontGlyphSet(mainFont, "Arial", 18, 600, 0, 0, FontFlags::fontflag_antialias);

	espFont = Interfaces::surface->createFont();
	Interfaces::surface->setFontGlyphSet(espFont, "Verdana", 14, 500, 0, 0, FontFlags::fontflag_outline);
}

void Render::drawLine(int x1, int y1, int x2, int y2, Color color)
{
	Interfaces::surface->setDrawColor(color.getR() * 255, color.getG() * 255, color.getB() * 255, color.values[3] = 255);
	Interfaces::surface->drawLine(x1, y1, x2, y2);
}

void Render::drawText(int x, int y, unsigned long font, const char* string, Color color, bool textCentered)
{
	va_list va_alist;
	char buf[1024];
	va_start(va_alist, string);
	_vsnprintf_s(buf, sizeof(buf), string, va_alist);
	va_end(va_alist);
	wchar_t wbuf[1024];
	MultiByteToWideChar(CP_UTF8, 0, buf, 256, wbuf, 256);

	int width, height;
	Interfaces::surface->getTextSize(font, wbuf, width, height);

	Interfaces::surface->setTextColor(color.getR() * 255, color.getG() * 255, color.getB() * 255, color.values[3] = 255);
	Interfaces::surface->setTextFont(font);
	if (textCentered)
		Interfaces::surface->setTextPosition(x - (width / 2), y);
	else
		Interfaces::surface->setTextPosition(x, y);
	Interfaces::surface->printText(wbuf, wcslen(wbuf));
}

void Render::drawText(int x, int y, unsigned long font, std::string string, Color color, bool textCentered)
{
	std::wstring text = std::wstring(string.begin(), string.end());
	const wchar_t* converted_text = text.c_str();

	int width, height;
	Interfaces::surface->getTextSize(font, converted_text, width, height);

	Interfaces::surface->setTextColor(color.getR() * 255, color.getG() * 255, color.getB() * 255, color.values[3] = 255);
	Interfaces::surface->setTextFont(font);
	if (textCentered)
		Interfaces::surface->setTextPosition(x - (width / 2), y);
	else
		Interfaces::surface->setTextPosition(x, y);
	Interfaces::surface->printText(converted_text, wcslen(converted_text));
}

void Render::drawFilledRect(int x, int y, int w, int h, Color color)
{
	Interfaces::surface->setDrawColor(color.getR() * 255, color.getG() * 255, color.getB() * 255, color.values[3] = 255);
	Interfaces::surface->drawFilledRect(x, y, x + w, y + h);
}

void Render::drawOutline(int x, int y, int w, int h, Color color)
{
	Interfaces::surface->setDrawColor(color.getR() * 255, color.getG() * 255, color.getB() * 255, color.values[3] = 255);
	Interfaces::surface->drawOutlinedRect(x + 1, y + 1, w - 2, h - 2);
	Interfaces::surface->drawOutlinedRect(x - 1, y - 1, w + 2, h + 2);
}

void Render::drawCircle(int x, int y, float points, float radius, Color color) 
{
	float step = M_PI * 2 / points;

	for (float i = 0; i < (M_PI * 2); i += step) {
		Vector2 start = Vector2(radius * cosf(i) + x, radius * sinf(i) + y);
		Vector2 end = Vector2(radius * cosf(i + step) + x, radius * sinf(i + step) + y);
		drawLine(start.x, start.y, end.x, end.y, color);
	}
}