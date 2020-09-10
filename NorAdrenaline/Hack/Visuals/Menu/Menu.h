#pragma once

#define LIMIT_LISTBOX 48
#define LIMIT_PALETTE 48
#define LIMIT_SAVE 16

class CPlayer;
class CPlayer
{
public:
	void Add_Player(int idx);

	void Reset_player();

public:
	cl_entity_s*	entity;
	int				index		= -1;
	char*			name		= "N/A";
	char*			weapon		= "N/A";
	char*			team		= "N/A";
	int				health		= -1;
	bool			alive		= false;
	bool			selected	= false;
	bool			traitor		= false;
	bool			_friend		= false;
	bool			priority	= false;
	float			distance	= 0.0f;
};
extern CPlayer g_PPlayer;

class CMenu;
class CMenu
{
public:

	bool bInitialised;
	bool IsDragging;
#ifndef _MENUTAB_PLIST
	bool IsDraggingPlist;
#endif

	unsigned int iCurrentTab;

	unsigned int MenuX;
	unsigned int MenuY;
#ifndef _MENUTAB_PLIST
	unsigned int plistX;
	unsigned int plistY;
#endif

	int CursorX;
	int CursorY;

	CImageTexture player_avatar;

	CImageTexture background;

	CImageTexture icon_headshot;
	CImageTexture icon_headshot_not_selected;

	CImageTexture icon_aimbot;
	CImageTexture icon_aimbot_not_selected;

	CImageTexture icon_systems;
	CImageTexture icon_systems_not_selected;

	CImageTexture icon_options;
	CImageTexture icon_options_not_selected;

	CImageTexture icon_visuals;
	CImageTexture icon_visuals_not_selected;

	CImageTexture icon_members;
	CImageTexture icon_members_not_selected;

	bool bListBoxOpened[LIMIT_LISTBOX];
	bool bPaletteOpened[LIMIT_PALETTE];

	DWORD dwCheckboxBlockedTime;
	DWORD dwInputfieldBlockedTime;
	DWORD dwPaletteBlockedTime;
	DWORD dwListBlockedTime;
	DWORD dwSliderBlockedTime;

	bool bCursorInList;
	bool bCursorInPalette;

	int iPaletteIndex;
	int iListIndex;

	void Palette(int x, int y, float& r, float& g, float& b);
	void Checkbox(int x, int y, bool& value, char* text);
	void Tooltip(const char* text, ...);
	void Slider(int x, int y, float min, float max, float& value, char* text = 0, bool ThisINT = false, char* amout = 0, bool extra = false);
	void Slider(int x, int y, float min, float max, float& value, char* text, bool ThisINT, char* amout, bool extra, const float step);
	void SliderInPallete(int x, int y, float min, float max, float& value, char* text = 0, bool ThisINT = false, char* amout = 0, bool extra = false);
	void ListBox(int index, int x, int y, char* name, float& value, char** text, int size, bool default = false);
	//void InputField(int x, int y, char *text, int maxLen, int &out);
	//void InputField(int x, int y, char* text, int maxStrLen, std::string& out);
	bool DrawButton(int x, int y, char* text);
	bool DrawButton(int x, int y, char* text, const char* tooltip, ...);
	void KeyBind(int x, int y, int& key);

	void DrawBox(int x, int y, int w, int h);
	void GroupBox(int x, int y, int w, int h, DWORD alignment, const char* name, ...);
	void SelectTab();
	void DrawMenuTabs();

	bool IsMouseInRegion(int x, int y, int x2, int y2);
	void Reset();
	void ResetItems();
	bool IsCursorInItem(int index);
	void calculate_vectors(bool open, std::vector<std::string> strList, int x, int y, int& _startFillX, int& _startFillY, int& _endFillX, int& _endFillY, int& _YScaling);
	void AddItem(int index, int x, int y, std::vector<std::string> strList);
#ifndef _MENUTAB_PLIST
	void Playerlist();
#endif
	void Update();

	CPlayer Players[MAX_CLIENTS + 1];
	int previous_player = 0;
	int selected_player = 0;

	void Paint();
	void Tabs();
	void InputField(int x, int y, char* text, int maxLen, int& out, std::function<void()>&& Callback);
	void InputField(int x, int y, char* text, int maxStrLen, std::string& out, std::function<void()>&& Callback);
	void Drag();
	void Init();
public:
#ifndef _MENUTAB_PLIST
	bool bPlayerlistOpened;
#endif
	bool bOpened;
	bool keys[256];

	void Run();

	std::deque<std::function<void()>> after_menu;
};
extern CMenu g_Menu;

class plist_item {
public:
	bool open = false;
	int index;
	Vector startPoint;
	Vector endPoint;
};
extern plist_item items[MAX_CLIENTS + 1];

template <typename T>
struct skip
{
	T& t;
	std::size_t n;
	skip(T& v, std::size_t s) : t(v), n(s) {}
	auto begin() -> decltype(std::begin(t))
	{
		return std::next(std::begin(t), n);
	}
	auto end() -> decltype(std::end(t))
	{
		return std::end(t);
	}
};