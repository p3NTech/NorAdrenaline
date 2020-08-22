class CDrawing;
class CDrawing
{
public:
	void DrawRect(int x, int y, int w, int h, int r, int g, int b, int a);
	void DrawOutlinedRect(int x, int y, int w, int h, int r, int g, int b, int a);
	void DrawCircle(float position[2], float points, float radius, int r, int g, int b, int a);
	void DrawCircle3D(Vector position, float points, float radius, int r, int g, int b, int a);
	void DrawLine(int x0, int y0, int x1, int y1, int r, int g, int b, int a);
	void DrawString(vgui::HFont font, int x, int y, int r, int g, int b, int a, DWORD alignment, const char* msg, ...);
	void DrawString(vgui::HFont font, int x, int y, int r, int g, int b, int a, const char* msg, ...);
	void DrawStringACP(vgui::HFont font, int x, int y, int r, int g, int b, int a, DWORD alignment, const char* msg, ...);
	void GetTextSize(int& wide, int& tall, vgui::HFont font, const char* text, ...);
	void DrawPlayerBox(int x, int y, int w, int h, int r, int g, int b, int a);
	void DrawBox(int x, int y, int w, int h, int r, int g, int b, int a);
	void DrawBone(int id, float *source, float *destination);
	void DrawTexture(int id, int x0, int y0, int x1, int y1, int r = 255, int g = 255, int b = 255, int a = 255);
	DWORD redGreenGradiant(float percent);
	DWORD redGreenGradiant(int i, int max);

	void SetupFonts();
};
extern CDrawing g_Drawing;

extern vgui::HFont ESP;
extern vgui::HFont MENU;