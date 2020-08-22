#include "../../Required.h"

CDrawing g_Drawing;

vgui::HFont ESP;
vgui::HFont MENU;

void CDrawing::SetupFonts()
{
	g_pISurface->AddGlyphSetToFont(ESP = g_pISurface->CreateFont(), "Tahoma", 13, FW_EXTRALIGHT, NULL, NULL, FONTFLAG_OUTLINE | FONTFLAG_OUTLINE, 0, 0);
	g_pISurface->AddGlyphSetToFont(MENU = g_pISurface->CreateFont(), "Tahoma", 11, FW_EXTRALIGHT, NULL, NULL, FONTFLAG_GAUSSIANBLUR | FONTFLAG_OUTLINE, 0, 0);
}

void CDrawing::DrawCircle3D(Vector position, float points, float radius, int r, int g, int b, int a)
{
	float step = (float)M_PI * 2.0f / points;

	for (float a = 0; a < (M_PI * 2.0f); a += step)
	{
		Vector start(radius * cosf(a) + position.x, radius * sinf(a) + position.y, position.z);
		Vector end(radius * cosf(a + step) + position.x, radius * sinf(a + step) + position.y, position.z);

		Vector start2d, end2d;
		if (!g_Utils.bCalcScreen(start, start2d) || !g_Utils.bCalcScreen(end, end2d))
			return;

		DrawLine(start2d.x, start2d.y, end2d.x, end2d.y, r, g, b, a);
	}
}

void CDrawing::DrawCircle(float position[2], float points, float radius, int r, int g, int b, int a)
{
	float step = (float)M_PI * 2.0f / points;

	float start[2], end[2];

	for (float x = 0; x < (M_PI * 2.0f); x += step)
	{
		start[0] = radius * cosf(x) + position[0];
		start[1] = radius * sinf(x) + position[1];
		end[0] = radius * cosf(x + step) + position[0];
		end[1] = radius * sinf(x + step) + position[1];
		DrawLine(start[0], start[1], end[0], end[1], r, g, b, a);
	}
}

void CDrawing::DrawPlayerBox(int x, int y, int w, int h, int r, int g, int b, int a)
{
	int x0 = x - w;
	int y0 = y;
	int x1 = x + w;
	int y1 = y + h;

	if (x1 < x0)
		std::swap(x1, x0);

	if (y1 < y0)
		std::swap(y1, y0);

	g_pISurface->DrawSetColor(r, g, b, a);
	g_pISurface->DrawOutlinedRect(x0, y0, x1, y1);

	if (cvar.esp_box_outline) 
	{
		g_pISurface->DrawSetColor(0, 0, 0, a);
		g_pISurface->DrawOutlinedRect(x0 - 1, y0 - 1, x1 + 1, y1 + 1);
		g_pISurface->DrawOutlinedRect(x0 + 1, y0 + 1, x1 - 1, y1 - 1);
	}
}

void CDrawing::DrawTexture(int id, int x0, int y0, int x1, int y1, int r, int g, int b, int a)
{
	g_pISurface->DrawSetColor(r, g, b, a);
	g_pISurface->DrawSetTexture(id);
	g_pISurface->DrawTexturedRect(x0, y0, x1, y1);
}

void CDrawing::DrawRect(int x, int y, int w, int h, int r, int g, int b, int a)
{
	int x0 = x;
	int y0 = y;
	int x1 = x + w;
	int y1 = y + h;

	if (x1 < x0)
		std::swap(x1, x0);

	if (y1 < y0)
		std::swap(y1, y0);

	g_pISurface->DrawSetColor(r, g, b, a);
	g_pISurface->DrawFilledRect(x0, y0, x1, y1);
}

void CDrawing::DrawOutlinedRect(int x, int y, int w, int h, int r, int g, int b, int a)
{
	int x0 = x;
	int y0 = y;
	int x1 = x + w;
	int y1 = y + h;

	if (x1 < x0)
		std::swap(x1, x0);

	if (y1 < y0)
		std::swap(y1, y0);

	g_pISurface->DrawSetColor(r, g, b, a);
	g_pISurface->DrawOutlinedRect(x0, y0, x1, y1);
}

void CDrawing::DrawLine(int x0, int y0, int x1, int y1, int r, int g, int b, int a)
{
	g_pISurface->DrawSetTextColor(r, g, b, a);
	g_pISurface->DrawLine(x0, y0, x1, y1);
}

void CDrawing::DrawBox(int x, int y, int w, int h, int r, int g, int b, int a)
{
	g_pISurface->DrawSetColor(r, g, b, a);
	g_pISurface->DrawOutlinedRect(x - w, y - h, x + w, y + h);
}

void CDrawing::DrawString(vgui::HFont font, int x, int y, int r, int g, int b, int a, DWORD alignment, const char* msg, ...)
{
	va_list va_alist;
	char buf[1024];
	va_start(va_alist, msg);
	_vsnprintf(buf, sizeof(buf), msg, va_alist);
	va_end(va_alist);
	wchar_t wbuf[1024];
	MultiByteToWideChar(CP_UTF8, 0, buf, 256, wbuf, 256);

	int width, height;
	g_pISurface->GetTextSize(font, wbuf, width, height);

	if (alignment & FONT_RIGHT)
		x -= width;
	if (alignment & FONT_CENTER)
		x -= width / 2;

	g_pISurface->DrawSetTextFont(font);
	g_pISurface->DrawSetTextColor(r, g, b, a);
	g_pISurface->DrawSetTextPos(x, y - height / 2);
	g_pISurface->DrawPrintText(wbuf, wcslen(wbuf));
}

void CDrawing::DrawString(vgui::HFont font, int x, int y, int r, int g, int b, int a, const char* msg, ...)
{
	va_list va_alist;
	char buf[1024];
	va_start(va_alist, msg);
	_vsnprintf(buf, sizeof(buf), msg, va_alist);
	va_end(va_alist);
	wchar_t wbuf[1024];
	MultiByteToWideChar(CP_UTF8, 0, buf, 256, wbuf, 256);

	g_pISurface->DrawSetTextFont(font);
	g_pISurface->DrawSetTextColor(r, g, b, a);
	g_pISurface->DrawSetTextPos(x, y);
	g_pISurface->DrawPrintText(wbuf, wcslen(wbuf));
}

void CDrawing::DrawStringACP(vgui::HFont font, int x, int y, int r, int g, int b, int a, DWORD alignment, const char* msg, ...)
{
	va_list va_alist;
	char buf[1024];
	va_start(va_alist, msg);
	_vsnprintf(buf, sizeof(buf), msg, va_alist);
	va_end(va_alist);
	wchar_t wbuf[1024];
	MultiByteToWideChar(CP_ACP, 0, buf, 256, wbuf, 256);

	int width, height;
	g_pISurface->GetTextSize(font, wbuf, width, height);

	if (alignment & FONT_RIGHT)
		x -= width;
	if (alignment & FONT_CENTER)
		x -= width / 2;

	g_pISurface->DrawSetTextFont(font);
	g_pISurface->DrawSetTextColor(r, g, b, a);
	g_pISurface->DrawSetTextPos(x, y - height / 2);
	g_pISurface->DrawPrintText(wbuf, wcslen(wbuf));
}

void CDrawing::GetTextSize(int& wide, int& tall, vgui::HFont font, const char* text, ...)
{
	va_list va_alist;
	char buf[1024];
	va_start(va_alist, text);
	_vsnprintf(buf, sizeof(buf), text, va_alist);
	va_end(va_alist);
	wchar_t wbuf[1024];
	MultiByteToWideChar(CP_ACP, 0, buf, 256, wbuf, 256);

	g_pISurface->GetTextSize(font, wbuf, wide, tall);
}

void CDrawing::DrawBone(int id, float *source, float *destination) {
	Vector fScreenBone1;
	Vector fScreenBone2;

	if (g_Utils.bCalcScreen(source, fScreenBone1) &&
		g_Utils.bCalcScreen(destination, fScreenBone2))
	{
		this->DrawLine(fScreenBone1.x, fScreenBone1.y, fScreenBone2.x, fScreenBone2.y, 255, 255, 255, 255);
	}
}

DWORD CDrawing::redGreenGradiant(float percent)
{
	if (percent < 0) {
		return COLORCODE(255, 0, 0, 255);
	}

	int r = 0, g = 0, b = 0;
	if (percent > 1) {
		g = 255;
		b = (int)(255 * (percent - 1) / 0.5);
	}
	else if (percent < 0.5) {
		r = 255;
		g = (int)(255 * percent / 0.5); // closer to 0.5, closer to yellow (255,255,0)
	}
	else {
		g = 255;
		r = 255 - (int)(255 * (percent - 0.5) / 0.5); // closer to 1.0, closer to green (0,255,0)
	}
	return COLORCODE(r, g, b, 255);
}

DWORD CDrawing::redGreenGradiant(int i, int max)
{
	float percent = float(i) / float(max);
	return this->redGreenGradiant(percent);
}
