#include "../../../Required.h"
#include "../../../images.h"

CMenu g_Menu;
CPlayer g_PPlayer;

plist_item items[MAX_CLIENTS + 1];

#define MAX_TABS 6
#define TAB_WEIGHT 72
#define TAB_HEIGHT 60
#define BORDER_SIZE 4

typedef std::basic_string<TCHAR> tstring;

tstring VirtualKeyCodeToString(UCHAR virtualKey)
{
	UINT scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);

	TCHAR szName[128];
	int result = 0;
	switch (virtualKey)
	{
	case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN:
	case VK_PRIOR: case VK_NEXT:
	case VK_END: case VK_HOME:
	case VK_INSERT: case VK_DELETE:
	case VK_DIVIDE:
	case VK_NUMLOCK:
		scanCode |= KF_EXTENDED;
	default:
		result = GetKeyNameText(scanCode << 16, szName, 128);
	}
	if (result == 0)
		throw std::system_error(std::error_code(GetLastError(), std::system_category()),
			"WinAPI Error occured.");
	return szName;
}

void CPlayer::Add_Player(int idx)
{
	entity = g_Engine.GetEntityByIndex(idx);

	if (entity)
		index = idx;

	name		= g_PlayerInfoList[idx].name;
	health		= g_Player[idx].iHealth;
	alive		= g_Player[idx].bAlive;
	traitor		= g_Player[idx].bTraitor;
	_friend		= g_Player[idx].bFriend;
	priority	= g_Player[idx].bPriority;
	distance	= g_Player[idx].bAlive ? g_Player[idx].flDist : 0;
	weapon		= g_PlayerExtraInfoList[idx].szWeaponName;

	if (g_Player[idx].iTeam == CT)
		team = "CT";
	else if (g_Player[idx].iTeam == TERRORIST)
		team = "T";
	else if (g_Player[idx].iTeam == SPECTATOR)
		team = "SPECTATOR";
	else if (g_Player[idx].iTeam == UNASSIGNED)
		team = "UNASSIGNED";
}

void CPlayer::Reset_player()
{
	selected	= false;
	entity		= nullptr;
	index		= -1;
	name		= "N/A";
	weapon		= "N/A";
	team		= "N/A";
	health		= -1;
	alive		= false;
	traitor		= false;
	_friend		= false;
	priority	= false;
	distance	= 0;
}

void CMenu::Init()
{
	if (bInitialised)
		return;

	if (!player_avatar.index) player_avatar.index = g_pISurface->CreateNewTextureID(true);

	if (!background.index) background.index = g_pISurface->CreateNewTextureID(true);

	if (!icon_headshot.index) icon_headshot.index = g_pISurface->CreateNewTextureID(true);

	if (!icon_aimbot.index) icon_aimbot.index = g_pISurface->CreateNewTextureID(true);

	if (!icon_systems.index) icon_systems.index = g_pISurface->CreateNewTextureID(true);

	if (!icon_options.index) icon_options.index = g_pISurface->CreateNewTextureID(true);

	if (!icon_visuals.index) icon_visuals.index = g_pISurface->CreateNewTextureID(true);

	if (!icon_members.index) icon_members.index = g_pISurface->CreateNewTextureID(true);

	if (!icon_headshot_not_selected.index) icon_headshot_not_selected.index = g_pISurface->CreateNewTextureID(true);

	if (!icon_aimbot_not_selected.index) icon_aimbot_not_selected.index = g_pISurface->CreateNewTextureID(true);

	if (!icon_systems_not_selected.index) icon_systems_not_selected.index = g_pISurface->CreateNewTextureID(true);

	if (!icon_options_not_selected.index) icon_options_not_selected.index = g_pISurface->CreateNewTextureID(true);

	if (!icon_visuals_not_selected.index) icon_visuals_not_selected.index = g_pISurface->CreateNewTextureID(true);

	if (!icon_members_not_selected.index) icon_members_not_selected.index = g_pISurface->CreateNewTextureID(true);

	if (background.index &&
		icon_headshot.index && icon_aimbot.index && icon_systems.index && icon_options.index && icon_visuals.index && icon_members.index &&
		icon_headshot_not_selected.index && icon_aimbot_not_selected.index && icon_systems_not_selected.index && icon_options_not_selected.index && icon_visuals_not_selected.index && icon_members_not_selected.index)
	{
		background.width = 650;
		background.height = 490;

		icon_headshot.width = icon_headshot.width = 45;
		icon_aimbot.width = icon_aimbot.height = 45;
		icon_systems.width = icon_systems.height = 45;
		icon_options.width = icon_options.height = 45;
		icon_visuals.width = icon_visuals.height = 45;
		icon_members.width = icon_members.height = 45;

		icon_headshot_not_selected.width = icon_headshot_not_selected.width = 45;
		icon_aimbot_not_selected.width = icon_aimbot_not_selected.height = 45;
		icon_systems_not_selected.width = icon_systems_not_selected.height = 45;
		icon_options_not_selected.width = icon_options_not_selected.height = 45;
		icon_visuals_not_selected.width = icon_visuals_not_selected.height = 45;
		icon_members_not_selected.width = icon_members_not_selected.height = 45;

		g_pISurface->DrawSetTextureRGBA(background.index, gui_background, background.width, background.height, false, true);

		g_pISurface->DrawSetTextureRGBA(icon_headshot.index, gui_headshot, icon_headshot.width, icon_headshot.width, false, true);
		g_pISurface->DrawSetTextureRGBA(icon_aimbot.index, gui_aim, icon_aimbot.width, icon_aimbot.height, false, true);
		g_pISurface->DrawSetTextureRGBA(icon_options.index, gui_options, icon_options.width, icon_options.height, false, true);
		g_pISurface->DrawSetTextureRGBA(icon_members.index, gui_members, icon_members.width, icon_members.height, false, true);
		g_pISurface->DrawSetTextureRGBA(icon_visuals.index, gui_visuals, icon_visuals.width, icon_visuals.height, false, true);
		g_pISurface->DrawSetTextureRGBA(icon_systems.index, gui_system, icon_systems.width, icon_systems.height, false, true);

		g_pISurface->DrawSetTextureRGBA(icon_headshot_not_selected.index, gui_headshot_off, icon_headshot.width, icon_headshot.width, false, true);
		g_pISurface->DrawSetTextureRGBA(icon_aimbot_not_selected.index, gui_aim_off, icon_aimbot.width, icon_aimbot.height, false, true);
		g_pISurface->DrawSetTextureRGBA(icon_options_not_selected.index, gui_options_off, icon_options.width, icon_options.height, false, true);
		g_pISurface->DrawSetTextureRGBA(icon_members_not_selected.index, gui_members_off, icon_members.width, icon_members.height, false, true);
		g_pISurface->DrawSetTextureRGBA(icon_visuals_not_selected.index, gui_visuals_off, icon_visuals.width, icon_visuals.height, false, true);
		g_pISurface->DrawSetTextureRGBA(icon_systems_not_selected.index, gui_system_off, icon_systems.width, icon_systems.height, false, true);

		bInitialised = true;
		bOpened = false;
		bPlayerlistOpened = false;
		dwCheckboxBlockedTime = 0;
		dwInputfieldBlockedTime = 0;
		dwSliderBlockedTime = 0;
		dwPaletteBlockedTime = 0;
		dwListBlockedTime = 0;

		//default menu position
		MenuX = g_Screen.iWidth / 2;
		MenuY = g_Screen.iHeight / 2;
		plistX = g_Screen.iWidth / 2;
		plistY = g_Screen.iHeight / 2;

		iCurrentTab = 5; // default tab
	}
}

void CMenu::Run()
{
	Init();

	if (g_pGlobals.bSnapshot || g_pGlobals.bScreenshot)
		return;

	if (cvar.hide_from_obs && g_Local.status.connected && g_Local.iTeam == 0)
		return;

	static bool m_bMouseCapture = false;

	static bool m_bCursorState = false;

	static DWORD dwTemporaryBlockTimer = 0;

	int key = VK_INSERT;
	if (cvar.menu_key > 0 && cvar.menu_key < 255)
		key = cvar.menu_key;

	if (GetTickCount64() - dwTemporaryBlockTimer > 200 && keys[key])
	{
		bOpened = !bOpened;
		dwTemporaryBlockTimer = GetTickCount64();
	}

	if (!bOpened && m_bMouseCapture && g_pIRunGameEngine->IsInGame() && !g_pGameUI->IsGameUIActive())
	{
		g_pISurface->SetCursor(dc_none);
		g_pISurface->LockCursor();
		m_bMouseCapture = false;

		if (m_bCursorState)
		{
			g_pISurface->SurfaceSetCursorPos(g_Screen.iWidth / 2, g_Screen.iHeight / 2);
			m_bCursorState = false;
		}
	}

	if (!bOpened ||
		!g_pISurface->IsTextureIDValid(background.index) ||
		!g_pISurface->IsTextureIDValid(icon_headshot.index) || !g_pISurface->IsTextureIDValid(icon_aimbot.index) || !g_pISurface->IsTextureIDValid(icon_options.index) || !g_pISurface->IsTextureIDValid(icon_visuals.index) || !g_pISurface->IsTextureIDValid(icon_systems.index) || !g_pISurface->IsTextureIDValid(icon_members.index) ||
		!g_pISurface->IsTextureIDValid(icon_headshot_not_selected.index) || !g_pISurface->IsTextureIDValid(icon_aimbot_not_selected.index) || !g_pISurface->IsTextureIDValid(icon_options_not_selected.index) || !g_pISurface->IsTextureIDValid(icon_visuals_not_selected.index) || !g_pISurface->IsTextureIDValid(icon_systems_not_selected.index) || !g_pISurface->IsTextureIDValid(icon_members_not_selected.index))
		return;

	if (g_pIRunGameEngine->IsInGame() && !g_pGameUI->IsGameUIActive())
	{
		g_pISurface->SetCursor(dc_arrow);
		g_pISurface->UnlockCursor();
		m_bMouseCapture = true;

		if (!m_bCursorState)
		{
			g_pISurface->SurfaceSetCursorPos(CursorX, CursorY);
			m_bCursorState = true;
		}
	}

	g_Engine.GetMousePosition(&CursorX, &CursorY);

	g_Drawing.DrawTexture(background.index, MenuX, MenuY, background.width + MenuX, background.height + MenuY); // Draw background
	//Reset all
	bCursorInPalette = false;
	bCursorInList = false;
	iPaletteIndex = 0;
	iListIndex = 0;

	SelectTab();
	DrawMenuTabs();
	Playerlist();
	Tabs();
	Drag();
}

bool CMenu::IsMouseInRegion(int x, int y, int x2, int y2)
{
	if (g_Menu.CursorX > x && g_Menu.CursorY > y && g_Menu.CursorX < x2 && g_Menu.CursorY < y2)
		return true;
	else
		return false;
}

void CMenu::Playerlist()
{
	static DWORD dwTemporaryBlockTimer = 0;

	static const int key = VK_HOME;

	if (GetTickCount64() - dwTemporaryBlockTimer > 200 && keys[key])
	{
		bPlayerlistOpened = !bPlayerlistOpened;
		dwTemporaryBlockTimer = GetTickCount64();
	}

	if (!bPlayerlistOpened)
		return;

	DWORD col = func.rainbow(0.100f);

	g_Drawing.DrawRect(plistX, plistY - 3, 650, 3, RED(col), GREEN(col), BLUE(col), 255);

	g_Drawing.DrawRect(plistX, plistY, 650, 490, 30, 30, 30, 255);

	int x = plistX + 30;
	int y = plistY + 30;
	int box_indent_x = 15;
	int box_indent_y = 15;

	GroupBox(x, y, 590, 430, FONT_CENTER, "Player list");

	Update();
}

void CMenu::Update()
{
	if (g_Local.status.connected)
	{
		Reset();
		ResetItems();

		size_t max = g_Engine.GetMaxClients();

		if (max > 16)
			max = 16;

		for (int j = 1; j <= max; j++)
		{
			if (j == g_Local.iIndex)
				continue;

			if (g_PlayerInfoList[j].name)
				Players[j].Add_Player(j);
		}

		for (int j = max + 1; j <= g_Engine.GetMaxClients(); j++)
		{
			if (j == g_Local.iIndex)
				continue;

			if (g_PlayerInfoList[j].name)
				Players[j].Add_Player(j);

		}

		Paint();
	}
}

void CMenu::Paint()
{
	int x = plistX + 30;
	int y = plistY + 35;
	int box_indent_x = 15;
	int box_indent_y = 15;

	int nLine = box_indent_y;

	if (g_Local.status.connected)
	{
		std::vector <CPlayer*> draw_list;

		for (int i = 0; i < std::size(Players); i++)
		{
			if (i == g_Local.iIndex)
				continue;

			if (g_PlayerInfoList[i].name)
			{
				draw_list.push_back(&Players[i]);
			}
		}

		if (draw_list.size() > 0)
		{
			for (CPlayer* Player : draw_list)
			{
				int idx = Player->index;

				std::string playername = "";
				for (int i = 0; i < MAX_PLAYER_NAME_LENGTH; i++)
				{
					playername += std::string(Player->name)[i];
				}

				bool bInParams = IsCursorInItem(idx);

				items[idx].open = bInParams;

				std::vector<std::string> sItems;

				/*
				std::stringstream b1, b2, b3, b4, b5, b6, b7, b8, b9, b10;

				static const std::string s1		= "name     :";
				static const std::string s2		= "index    :";
				static const std::string s3		= "alive    :";
				static const std::string s4		= "traitor  :";
				static const std::string s5		= "friend   :";
				static const std::string s6		= "priority :";
				static const std::string s7		= "team     :";
				static const std::string s8		= "weapon   :";
				static const std::string s9		= "health   :";
				static const std::string s10	= "distance :";

				b1 << s1 << std::setw(10) << "	" << Player->name;
				b2 << s2 << std::setw(10) << "	" << idx;
				b3 << s3 << std::setw(10) << "	" << Player->alive ? "yes" : "no";
				b4 << s4 << std::setw(10) << "	" << Player->traitor ? "yes" : "no";
				b5 << s5 << std::setw(10) << "	" << Player->_friend ? "yes" : "no";
				b6 << s6 << std::setw(10) << "	" << Player->priority ? "yes" : "no";
				b7 << s7 << std::setw(10) << "	" << Player->team;
				b8 << s8 << std::setw(10) << "	" << Player->weapon;
				b9 << s9 << std::setw(10) << "	" << Player->health;
				b10 << s10 << std::setw(10) << "	" << (int)Player->distance;
				*/
				
				sItems.push_back(format("	name: %s",	Player->name).c_str());
				sItems.push_back(format("	index: %i",	idx).c_str());
				sItems.push_back(format("	alive: %s",	Player->alive ?		"yes" : "no").c_str());
				sItems.push_back(format("	traitor: %s",	Player->traitor ?	"yes" : "no").c_str());
				sItems.push_back(format("	friend: %s",	Player->_friend ?	"yes" : "no").c_str());
				sItems.push_back(format("	priority: %s",	Player->priority ?	"yes" : "no").c_str());
				sItems.push_back(format("	team: %s",	Player->team).c_str());
				sItems.push_back(format("	weapon: %s",	Player->weapon).c_str());
				sItems.push_back(format("	health: %i",	Player->health).c_str());
				sItems.push_back(format("	distance: %i",	(int)Player->distance).c_str());
				sItems.push_back(format("	SteamID: STEAM_0:%llu:%llu", (g_PlayerInfoList[idx].m_nSteamID & 0xFFFFFFFF) & 1, (g_PlayerInfoList[idx].m_nSteamID & 0xFFFFFFFF) >> 1).c_str());
				/*
				sItems.push_back(b1.str());
				sItems.push_back(b2.str());
				sItems.push_back(b3.str());
				sItems.push_back(b4.str());
				sItems.push_back(b5.str());
				sItems.push_back(b6.str());
				sItems.push_back(b7.str());
				sItems.push_back(b8.str());
				sItems.push_back(b9.str());
				sItems.push_back(b10.str());
				*/

				int startFillX, startFillY, endFillX, endFillY, itemX, itemY, Yscaling;

				itemX	= x + box_indent_x;
				itemY	= y + nLine;

				calculate_vectors(bInParams, sItems, itemX, itemY, startFillX, startFillY, endFillX, endFillY, Yscaling);

				items[idx].index			= idx;
				items[idx].startPoint.x		= startFillX;
				items[idx].startPoint.y		= startFillY;
				items[idx].endPoint.x		= endFillX;
				items[idx].endPoint.y		= endFillY;

				AddItem(idx, itemX, itemY, sItems);

				sItems.clear();

				nLine += 16;

				if (Yscaling != 0)
					nLine += Yscaling;

				if (bInParams)
				{
					selected_player = idx;
					Player->selected = true;
				}

			}
		}
	}
}

void CMenu::Reset()
{
	for (int i = 0; i < std::size(Players); i++)
	{
		Players[i].Reset_player();
	}
}

void CMenu::ResetItems()
{
	memset(items, NULL, sizeof(plist_item));
}

bool CMenu::IsCursorInItem(int index)
{
	return IsMouseInRegion(items[index].startPoint.x, items[index].startPoint.y, items[index].endPoint.x, items[index].endPoint.y);
}

void CMenu::calculate_vectors(bool open, std::vector<std::string> strList, int x, int y, int &_startFillX, int &_startFillY, int &_endFillX, int &_endFillY, int &_YScaling)
{
	// constants
	static const int scaling = 1;
	static const int width = 450;
	static const int height = 11;

	// position calc
	int startFillY = (y - height / 2) + scaling;
	int startFillX = x - scaling;

	int endFillY = startFillY;
	int endFillX = startFillX;

	if (open)
	{
		int newline = 0;

		for (auto p : strList)
		{
			newline += 11;
		}

		_YScaling = newline;

		endFillY	+= height	+ scaling + newline;
		endFillX	+= width	+ scaling;
	}
	else
	{
		_YScaling = 0;

		endFillY	+= height	+ scaling;
		endFillX	+= width	+ scaling;
	}

	_startFillX		= startFillX;
	_startFillY		= startFillY;
	_endFillX		= endFillX;
	_endFillY		= endFillY;
}

void CMenu::AddItem(int index, int x, int y, std::vector<std::string> strList)
{
	int startFillX, startFillY, endFillX, endFillY, _y;
	bool open;
	open		= items[index].open;
	startFillX	= items[index].startPoint.x;
	startFillY	= items[index].startPoint.y;
	endFillX	= items[index].endPoint.x;
	endFillY	= items[index].endPoint.y;

	// drawing
	g_pISurface->DrawSetColor(30, 30, 30, 255);
	g_pISurface->DrawFilledRect(startFillX, startFillY, endFillX, endFillY);

	auto col = [&open]() -> DWORD {
		if (open)
		{
			return COLORCODE(220, 0, 0, 255);
		}
		else
			return COLORCODE(20, 20, 20, 255);

	};

	DWORD selection_color = col();

	g_pISurface->DrawSetColor(RED(selection_color), GREEN(selection_color), BLUE(selection_color), 255);
	g_pISurface->DrawOutlinedRect(startFillX - 1, startFillY - 1, endFillX + 1, endFillY + 1);

	_y = startFillY + (11 / 2) + 1;

	// first element is name
	g_Drawing.DrawString(MENU, x + 1, _y, 200, 200, 200, 255, FONT_LEFT, strList[0].c_str());

	if (open)
	{
		int newline = _y + 11;
		// skip first element, draw other shit
		for (auto p : skip<decltype(strList)>(strList, 1))
		{
			g_Drawing.DrawString(MENU, x + 1, newline + 1, 220, 220, 220, 255, FONT_LEFT, p.c_str());
			newline += 11;
		}

		Checkbox(x + 220, _y, g_Player[index].bTraitor, "Traitor");
		Checkbox(x + 220, _y + 15, g_Player[index].bFriend, "Friend");
		Checkbox(x + 220, _y + 30, g_Player[index].bPriority, "Priority");

		CSteamID player_SID = CSteamID(g_PlayerInfoList[index].m_nSteamID);

		static int old_avatar = NULL;

		int avatar = g_SteamInterface.steamfriends->GetMediumFriendAvatar(player_SID);

		uint32 uAvatarWidth, uAvatarHeight;

		bool success = g_SteamInterface.steamutils->GetImageSize(avatar, &uAvatarWidth, &uAvatarHeight);

		const int uImageSizeInBytes = uAvatarWidth * uAvatarHeight * 4;
		uint8* pAvatarRGBA = new uint8[uImageSizeInBytes];

		success = g_SteamInterface.steamutils->GetImageRGBA(avatar, pAvatarRGBA, uImageSizeInBytes);

		if (success)
		{
			player_avatar.width		= uAvatarWidth;
			player_avatar.height	= uAvatarHeight;

			if (old_avatar != avatar && avatar)
			{
				g_pISurface->DrawSetTextureRGBA(player_avatar.index, pAvatarRGBA, player_avatar.width, player_avatar.height, false, false);
				old_avatar = avatar;
			}

			if (g_pISurface->IsTextureIDValid(player_avatar.index))
			{
				g_pISurface->DrawSetColor(cvar.cheat_global_color_r, cvar.cheat_global_color_g, cvar.cheat_global_color_b, 255);
				g_pISurface->DrawOutlinedRect(x + 279, _y - 1, (x + 281) + player_avatar.width, (_y + 1) + player_avatar.width);
				g_Drawing.DrawTexture(player_avatar.index, x + 280, _y, (x + 280) + player_avatar.width, _y + player_avatar.width);
			}
		}
		delete[] pAvatarRGBA; // free the memory
	}
}

void CMenu::Tabs()
{
	static int m_iOldTab = iCurrentTab;

	if (m_iOldTab != iCurrentTab)
	{
		for (unsigned int i = 0; i < LIMIT_LISTBOX; i++)
			bListBoxOpened[i] = false;

		for (unsigned int i = 0; i < LIMIT_PALETTE; i++)
			bPaletteOpened[i] = false;

		m_iOldTab = iCurrentTab;
	}

	static unsigned int indent_x = 10;
	static unsigned int indent_y = 14;

	if (iCurrentTab == 1)//Rage aimbot
	{
		unsigned int x = MenuX + 100;
		unsigned int y = MenuY + 30;

		unsigned int line_y = indent_y;

		unsigned int save[LIMIT_SAVE];

		{//BOX1
			GroupBox(x, y, 250, 230, FONT_CENTER, "Aimbot");

			Checkbox(x + indent_x, y + line_y, cvar.aim, "Enabled");
			KeyBind(x + indent_x + 180, y + line_y - 10, cvar.aim_key);
			line_y += 30;

			static char *szTargetSelection[] = { "Field of view", "Distance", "Cycle" };
			save[7] = y + line_y;
			line_y += 40;

			static char *szTargetHitbox[] = { "Head", "Neck", "Chest", "Stomach", "All hitboxes", "Vital hitboxes" };
			save[8] = y + line_y;
			line_y += 40;

			static char *szMultipoint[] = { "Low", "Medium", "High" };
			save[9] = y + line_y;
			line_y += 40;

			Checkbox(x + indent_x, y + line_y, cvar.aim_teammates, "Teammates");
			line_y += 15;

			Checkbox(x + indent_x, y + line_y, cvar.aim_penetration, "Automatic penetration");
			line_y += 15;

			Checkbox(x + indent_x, y + line_y, cvar.aim_silent, "Silent aim");
			line_y += 15;

			Checkbox(x + indent_x, y + line_y, cvar.aim_perfect_silent, "Perfect silent aim");
			line_y += 30;

			ListBox(iListIndex++, x + indent_x, save[9], "Multi-point", cvar.aim_multi_point, szMultipoint, 3, true);
			ListBox(iListIndex++, x + indent_x, save[8], "Target hitbox", cvar.aim_hitbox, szTargetHitbox, 6, false);
			ListBox(iListIndex++, x + indent_x, save[7], "Target selection", cvar.aim_target_selection, szTargetSelection, 3, false);
		}

		{//BOX1.2
			y = y + 250;
			line_y = 15;
			GroupBox(x, y, 250, 180, FONT_CENTER, "Fake-lag");

			Checkbox(x + indent_x, y + line_y, cvar.fakelag, "Enabled");
			line_y += 20;

			char *tmp4[] = { "On land", "On move", "In air", "All" };
			save[4] = y + line_y;
			line_y += 30;

			char *tmp3[] = { "Dynamic", "Maximum", "Flucture", "Break lag compensation" };
			save[3] = y + line_y;
			line_y += 40;

			Slider(x + indent_x, y + line_y, 0, 100, cvar.fakelag_variance, "Variance");
			line_y += 30;

			Slider(x + indent_x, y + line_y, 0, 30, cvar.fakelag_limit, "Limit");
			line_y += 20;

			Checkbox(x + indent_x, y + line_y, cvar.fakelag_while_shooting, "Fake lag while shooting");
			line_y += 20;

			ListBox(iListIndex++, x + indent_x, save[3], "", cvar.fakelag_move, tmp4, 4, false);
			ListBox(iListIndex++, x + indent_x, save[4], "", cvar.fakelag_type, tmp3, 4, false);
		}

		{//BOX2
			y = MenuY + 30;
			x = x + 270;
			line_y = 15;
			GroupBox(x, y, 250, 200, FONT_CENTER, "Other");

			Checkbox(x + indent_x, y + line_y, cvar.norecoil, "Remove recoil");
			line_y += 15;

			Checkbox(x + indent_x, y + line_y, cvar.nospread, "Remove spread");
			line_y += 15;

			Checkbox(x + indent_x, y + line_y, cvar.quick_stop, "Quick stop");
			line_y += 15;

			Checkbox(x + indent_x, y + line_y, cvar.quick_stop_duck, "Quick stop + duck");
			line_y += 15;

			Checkbox(x + indent_x, y + line_y, cvar.aim_autoscope, "Automatic scope");
			line_y += 15;

			Checkbox(x + indent_x, y + line_y, cvar.aim_delay_shot, "Anti-aim resolver");
			line_y += 15;

			Checkbox(x + indent_x, y + line_y, cvar.aim_delay_shot, "Delay shot");
			line_y += 30;

			char *tmp[] = { "Pitch / Yaw", "Roll" };
			ListBox(iListIndex++, x + indent_x, y + line_y, "Remove spread method", cvar.nospread_method, tmp, 2, false);
			line_y += 40;

			Slider(x + indent_x, y + line_y, 0, 180, cvar.aim_fov, "Aimbot FOV");
			line_y += 40;
		}

		{//BOX3
			y = y + 220;
			line_y = 30;
			GroupBox(x, y, 250, 210, FONT_CENTER, "Anti-Aimbot");

			char *tmp1[] = { "Fakedown", "Down", "Up", "Jitter", "Random" };
			save[0] = y + line_y;
			line_y += 40;

			char *tmp2[] = { "180", "180 jitter", "Spin", "Jitter", "Sideways", "Random", "Static" };
			save[1] = y + line_y;
			line_y += 40;

			char *tmp3[] = { "180", "180 jitter", "Spin", "Jitter", "Sideways", "Random", "Static" };
			save[2] = y + line_y;
			line_y += 40;

			char *tmp4[] = { "Standing", "In move", "All", "All + Fake" };
			save[5] = y + line_y;
			line_y += 40;

			char *tmp0[] = { "90", "180" };

			Slider(x + indent_x, y + line_y, -180, 180, cvar.aa_yaw_static, "Static yaw");
			line_y += 20;

			ListBox(iListIndex++, x + indent_x, save[5], "Edge", cvar.aa_edge, tmp4, 4, true);

			ListBox(iListIndex++, x + indent_x, save[10], "Legit AA", cvar.aa_legit, tmp0, 2, true);

			ListBox(iListIndex++, x + indent_x, save[2], "Yaw while running", cvar.aa_yaw_while_running, tmp3, 7, true);

			ListBox(iListIndex++, x + indent_x, save[1], "Yaw", cvar.aa_yaw, tmp2, 7, true);

			ListBox(iListIndex++, x + indent_x, save[0], "Pitch", cvar.aa_pitch, tmp1, 5, true);
		}
	}
	else if (iCurrentTab == 2)//Legit
	{
		int x = MenuX + 100;
		int y = MenuY + 30;
		int box_indent_x = 10;
		int box_indent_y = 15;

		int save[256];

		int line_y = 15;

		int weapon_id = 0;

		if (cvar.menu_legit_global_section == 1)
		{
			if (cvar.menu_legit_sub_section == 1)
				weapon_id = WEAPON_GLOCK18;
			else if (cvar.menu_legit_sub_section == 2)
				weapon_id = WEAPON_P228;
			else if (cvar.menu_legit_sub_section == 3)
				weapon_id = WEAPON_DEAGLE;
			else if (cvar.menu_legit_sub_section == 4)
				weapon_id = WEAPON_ELITE;
			else if (cvar.menu_legit_sub_section == 5)
				weapon_id = WEAPON_FIVESEVEN;
			else if (cvar.menu_legit_sub_section == 6)
				weapon_id = WEAPON_USP;
		}
		else if (cvar.menu_legit_global_section == 2)
		{
			if (cvar.menu_legit_sub_section == 1)
				weapon_id = WEAPON_AWP;
			else if (cvar.menu_legit_sub_section == 2)
				weapon_id = WEAPON_SCOUT;
			else if (cvar.menu_legit_sub_section == 3)
				weapon_id = WEAPON_G3SG1;
			else if (cvar.menu_legit_sub_section == 4)
				weapon_id = WEAPON_SG550;
		}
		else if (cvar.menu_legit_global_section == 3)
		{
			if (cvar.menu_legit_sub_section == 1)
				weapon_id = WEAPON_M4A1;
			else if (cvar.menu_legit_sub_section == 2)
				weapon_id = WEAPON_GALIL;
			else if (cvar.menu_legit_sub_section == 3)
				weapon_id = WEAPON_FAMAS;
			else if (cvar.menu_legit_sub_section == 4)
				weapon_id = WEAPON_AUG;
			else if (cvar.menu_legit_sub_section == 5)
				weapon_id = WEAPON_AK47;
			else if (cvar.menu_legit_sub_section == 6)
				weapon_id = WEAPON_SG552;
		}
		else if (cvar.menu_legit_global_section == 4)
		{
			if (cvar.menu_legit_sub_section == 1)
				weapon_id = WEAPON_XM1014;
			else if (cvar.menu_legit_sub_section == 2)
				weapon_id = WEAPON_M3;
		}
		else if (cvar.menu_legit_global_section == 5)
		{
			if (cvar.menu_legit_sub_section == 1)
				weapon_id = WEAPON_M249;
		}
		else if (cvar.menu_legit_global_section == 6)
		{
			if (cvar.menu_legit_sub_section == 1)
				weapon_id = WEAPON_TMP;
			else if (cvar.menu_legit_sub_section == 2)
				weapon_id = WEAPON_P90;
			else if (cvar.menu_legit_sub_section == 3)
				weapon_id = WEAPON_MP5N;
			else if (cvar.menu_legit_sub_section == 4)
				weapon_id = WEAPON_MAC10;
			else if (cvar.menu_legit_sub_section == 5)
				weapon_id = WEAPON_UMP45;
		}

		if (weapon_id > 0)
		{
			y = y + 45 + 20;

			{//BOX2
				GroupBox(x, y, 250, 365, FONT_CENTER, "Aimbot");

				Checkbox(x + box_indent_x, y + line_y, cvar.legit[weapon_id].aim, "Enabled");
				line_y += 30;

				Slider(x + box_indent_x, y + line_y, 0, 100, cvar.legit[weapon_id].aim_speed, "Speed (auto)");
				line_y += 30;

				Slider(x + box_indent_x, y + line_y, 0, 100, cvar.legit[weapon_id].aim_speed_in_attack, "Speed (in attack)");
				line_y += 30;

				Slider(x + box_indent_x, y + line_y, 0, 100, cvar.legit[weapon_id].aim_speed_scale_fov, "Speed scale - FOV", true, "%");
				line_y += 30;

				Slider(x + box_indent_x, y + line_y, 0, 1000, cvar.legit[weapon_id].aim_reaction_time, "Reaction time", true, "ms");
				line_y += 30;

				Slider(x + box_indent_x, y + line_y, 0, 180, cvar.legit[weapon_id].aim_fov, "Maximum FOV", false, "°", true);
				line_y += 30;

				Slider(x + box_indent_x, y + line_y, 0, 100, cvar.legit[weapon_id].aim_recoil_compensation_pitch, "Recoil compensation (P/Y)", true, "%");
				line_y += 20;

				Slider(x + box_indent_x, y + line_y, 0, 100, cvar.legit[weapon_id].aim_recoil_compensation_yaw, "", true, "%");
				line_y += 20;

				Checkbox(x + box_indent_x, y + line_y, cvar.legit[weapon_id].aim_humanize, "Humanize");
				line_y += 20;

				Checkbox(x + box_indent_x, y + line_y, cvar.legit[weapon_id].aim_quick_stop, "Quick stop");
				line_y += 20;

				Checkbox(x + box_indent_x, y + line_y, cvar.legit[weapon_id].aim_head, "Head");
				line_y += 20;

				Checkbox(x + box_indent_x, y + line_y, cvar.legit[weapon_id].aim_chest, "Chest");
				line_y += 20;

				Checkbox(x + box_indent_x, y + line_y, cvar.legit[weapon_id].aim_stomach, "Stomach");
				line_y += 30;
			}

			x = x + 270;
			line_y = 15;

			{//BOX3
				GroupBox(x, y, 250, 175, FONT_CENTER, "Triggerbot");

				Checkbox(x + box_indent_x, y + line_y, cvar.legit[weapon_id].trigger, "Enabled");
				KeyBind(x + box_indent_x + 180, y + line_y - 10, cvar.trigger_key);
				line_y += 20;

				Checkbox(x + box_indent_x, y + line_y, cvar.legit[weapon_id].trigger_penetration, "Automatic penetration");
				line_y += 20;

				Checkbox(x + box_indent_x, y + line_y, cvar.legit[weapon_id].trigger_head, "Head");
				line_y += 20;

				Checkbox(x + box_indent_x, y + line_y, cvar.legit[weapon_id].trigger_chest, "Chest");
				line_y += 20;

				Checkbox(x + box_indent_x, y + line_y, cvar.legit[weapon_id].trigger_stomach, "Stomach");
				line_y += 30;

				char *tmp[] = { "Recoil", "Recoil / Spread" };
				save[0] = y + line_y;

				line_y += 30;

				Checkbox(x + box_indent_x, y + line_y, cvar.trigger_only_zoomed, "Only zoomed");
				line_y += 20;

				ListBox(iListIndex++, x + box_indent_x, save[0], "Accuracy boost", cvar.legit[weapon_id].trigger_accuracy, tmp, 2, true);
			}

			y = y + 175 + 20;
			line_y = 15;

			{//BOX4
				GroupBox(x, y, 250, 170, FONT_CENTER, "Other");

				Checkbox(x + box_indent_x, y + line_y, cvar.legit_teammates, "Teammates");
				line_y += 30;

				Slider(x + box_indent_x, y + line_y, 0, 1000, cvar.block_attack_after_kill, "Block attack after kill", true, "ms");
				line_y += 30;

				char *tmp[] = { "Aiming", "Recoil", "Recoil / Spread" };
				save[0] = y + line_y;
				line_y += 40;

				Slider(x + box_indent_x, y + line_y, 0, 1, cvar.legit[weapon_id].aim_psilent, "Perfect silent", false, "°", true);
				line_y += 30;

				Slider(x + box_indent_x, y + line_y, 0, 10, cvar.legit[weapon_id].aim_recoil_compensation_after_shots_fired, "Recoil compensation after shots fired", true);
				line_y += 20;

				ListBox(iListIndex++, x + box_indent_x, save[0], "Accuracy boost", cvar.legit[weapon_id].aim_accuracy, tmp, 3, true);
			}
		}

		x = MenuX + 100;
		y = MenuY + 30;
		line_y = 15;

		{//BOX1
			GroupBox(x, y, 520, 45, FONT_CENTER, "Section");

			char *tmp[] = { "Pistol", "Sniper", "Rifle", "Shotgun", "Machine gun", "Submachine gun" };
			ListBox(iListIndex++, x + box_indent_x, y + line_y, "", cvar.menu_legit_global_section, tmp, 6, false);

			if (cvar.menu_legit_global_section == 1) {
				char *tmp2[] = { "GLOCK18", "P228", "DEAGLE", "ELITE", "FIVESEVEN", "USP" };
				ListBox(iListIndex++, x + box_indent_x + 270, y + line_y, "", cvar.menu_legit_sub_section, tmp2, 6, false);

				if (cvar.menu_legit_sub_section > 6)
					cvar.menu_legit_sub_section = 6;
			}
			else if (cvar.menu_legit_global_section == 2) {
				char *tmp2[] = { "AWP", "SCOUT", "G3SG1", "SG550", };
				ListBox(iListIndex++, x + box_indent_x + 270, y + line_y, "", cvar.menu_legit_sub_section, tmp2, 4, false);

				if (cvar.menu_legit_sub_section > 4)
					cvar.menu_legit_sub_section = 4;
			}
			else if (cvar.menu_legit_global_section == 3) {
				char *tmp2[] = { "M4A1", "GALIL", "FAMAS", "AUG", "AK47", "SG552" };
				ListBox(iListIndex++, x + box_indent_x + 270, y + line_y, "", cvar.menu_legit_sub_section, tmp2, 6, false);

				if (cvar.menu_legit_sub_section > 6)
					cvar.menu_legit_sub_section = 6;
			}
			else if (cvar.menu_legit_global_section == 4) {
				char *tmp2[] = { "XM1014", "M3" };
				ListBox(iListIndex++, x + box_indent_x + 270, y + line_y, "", cvar.menu_legit_sub_section, tmp2, 2, false);

				if (cvar.menu_legit_sub_section > 2)
					cvar.menu_legit_sub_section = 2;
			}
			else if (cvar.menu_legit_global_section == 5) {
				char *tmp2[] = { "M249" };
				ListBox(iListIndex++, x + box_indent_x + 270, y + line_y, "", cvar.menu_legit_sub_section, tmp2, 1, false);

				if (cvar.menu_legit_sub_section > 1)
					cvar.menu_legit_sub_section = 1;
			}
			else if (cvar.menu_legit_global_section == 6) {
				char *tmp2[] = { "TMP", "P90", "MP5N", "MAC10", "UMP45" };
				ListBox(iListIndex++, x + box_indent_x + 270, y + line_y, "", cvar.menu_legit_sub_section, tmp2, 5, false);

				if (cvar.menu_legit_sub_section > 5)
					cvar.menu_legit_sub_section = 5;
			}
		}
	}
	else if (iCurrentTab == 3)//Systems
	{
		int x = MenuX + 100;
		int y = MenuY + 30;
		int box_indent_x = 10;
		int box_indent_y = 15;

		int save[256];

		int line_y = 15;

		{//BOX1
			GroupBox(x, y, 250, 430, FONT_CENTER, "Movement");

			Checkbox(x + box_indent_x, y + line_y, cvar.bunnyhop, "Auto jump");
			line_y += 15;

			Checkbox(x + box_indent_x, y + line_y, cvar.air_duck, "Jump duck");
			line_y += 15;

			Checkbox(x + box_indent_x, y + line_y, cvar.jump_bug, "Jump bug");
			line_y += 15;

			Checkbox(x + box_indent_x, y + line_y, cvar.fastrun_temp, "Fast run");
			line_y += 15;

			Checkbox(x + box_indent_x, y + line_y, cvar.autostrafe, "Automatic strafing");
			line_y += 30;

			Slider(x + box_indent_x, y + line_y, 0, 1000, cvar.strafe_speed, "Strafing speed");
			line_y += 15;
		}

		{//BOX2
			x = x + 270;
			line_y = 15;
			GroupBox(x, y, 250, 200, FONT_CENTER, "Other");

			Checkbox(x + box_indent_x, y + line_y, cvar.knifebot, "Knifebot");
			line_y += 20;
		}

		{//BOX3
			y = y + 220;
			line_y = 15;
			GroupBox(x, y, 250, 210, FONT_CENTER, "Followbot");

			Checkbox(x + box_indent_x, y + line_y, cvar.Followbot, "enabled");
			line_y += 15;

			Checkbox(x + box_indent_x, y + line_y, cvar.Followbot_friends, "friends");
			line_y += 15;

			Checkbox(x + box_indent_x, y + line_y, cvar.Followbot_afk, "AFK");
			line_y += 15;

			Checkbox(x + box_indent_x, y + line_y, cvar.Followbot_corners, "corners");
			line_y += 15;

			Checkbox(x + box_indent_x, y + line_y, cvar.Followbot_draw, "visualize");
			line_y += 30;

			Slider(x + box_indent_x, y + line_y, 80, 1000, cvar.Followbot_activation, "activation distance");
			line_y += 30;

			Slider(x + box_indent_x, y + line_y, 200, 15000, cvar.Followbot_afk_time, "AFK time (ms)");
			line_y += 30;

			Slider(x + box_indent_x, y + line_y, 0, 400, cvar.Followbot_distance, "distance");
			line_y += 30;
		}
	}
	else if (iCurrentTab == 4)//Visuals
	{
		int x = MenuX + 100;
		int y = MenuY + 30;
		int box_indent_x = 10;
		int box_indent_y = 15;

		int save[256];

		int line_y = 15;

		{//BOX1
			GroupBox(x, y, 250, 430, FONT_CENTER, "Player ESP");

			Checkbox(x + box_indent_x, y + line_y, cvar.esp, "Enabled");
			line_y += 18;

			Checkbox(x + box_indent_x, y + line_y, cvar.esp_teammates, "Teammates");
			line_y += 18;

			Checkbox(x + box_indent_x, y + line_y, cvar.esp_box, "Bounding box");
			save[0] = y + line_y;
			line_y += 18;

			Checkbox(x + box_indent_x, y + line_y, cvar.esp_box_outline, "Bounding box outline");
			line_y += 18;

			Checkbox(x + box_indent_x, y + line_y, cvar.esp_behind, "Behind wall");
			save[5] = y + line_y;
			line_y += 18;

			Checkbox(x + box_indent_x, y + line_y, cvar.esp_health, "Health bar");
			line_y += 18;

			Checkbox(x + box_indent_x, y + line_y, cvar.esp_name, "Name");
			line_y += 18;

			Checkbox(x + box_indent_x, y + line_y, cvar.esp_trace_angles, "Trace angles");
			line_y += 30;

			//char *tmp3[] = { "Text", "Icon" };
			//ListBox(iListIndex++, x + box_indent_x, y + line_y, "Weapon", cvar.chams_type, tmp3, 2, true);
			save[6] = y + line_y;
			line_y += 30;

			Checkbox(x + box_indent_x, y + line_y, cvar.esp_distance, "Distance");
			line_y += 15;

			Checkbox(x + box_indent_x, y + line_y, cvar.esp_flags, "Flags");
			line_y += 15;

			Checkbox(x + box_indent_x, y + line_y, cvar.esp_line_of_sight, "Line of sight");
			save[1] = y + line_y;
			line_y += 15;

			Checkbox(x + box_indent_x, y + line_y, cvar.esp_sound, "Visualize sounds");
			line_y += 15;

			Checkbox(x + box_indent_x, y + line_y, cvar.esp_shots_fired, "Shots fired");
			line_y += 15;

			Checkbox(x + box_indent_x, y + line_y, cvar.esp_hitboxes, "Hitboxes");
			line_y += 15;

			Checkbox(x + box_indent_x, y + line_y, cvar.esp_screen, "Screen");
			line_y += 15;

			Checkbox(x + box_indent_x, y + line_y, cvar.glow_players, "Glow");
			save[2] = y + line_y;
			line_y += 30;

			char *tmp4[] = { "STUDIO_HAS_NORMALS", "STUDIO_HAS_VERTICES", "STUDIO_HAS_BBOX", "STUDIO_HAS_CHROME", "STUDIO_NF_FLATSHADE", "STUDIO_NF_CHROME" };
			ListBox(iListIndex++, x + indent_x, y + line_y, "Glow type", cvar.glow_type, tmp4, 6, false);
			line_y += 30;

			Checkbox(x + box_indent_x, y + line_y, cvar.chams, "Player colored model");
			save[3] = y + line_y;
			line_y += 18;

			Checkbox(x + box_indent_x, y + line_y, cvar.chams_behind_wall, "Player colored model (behind wall)");
			save[4] = y + line_y;
			line_y += 18;

			char *tmp[] = { "Flat", "Texture", "Material" };
			ListBox(iListIndex++, x + box_indent_x, y + line_y, "", cvar.chams_type, tmp, 3);

			char *tmp3[] = { "Text", "Icon" };
			ListBox(iListIndex++, x + box_indent_x, save[6], "Weapon", cvar.esp_weapon, tmp3, 2, true);
		}

		{//BOX2
			x = x + 270;
			line_y = 15;
			GroupBox(x, y, 250, 200, FONT_CENTER, "Other ESP");

			Checkbox(x + box_indent_x, y + line_y, cvar.esp_bomb, "C4");
			Palette(x + 227, y + line_y, cvar.esp_bomb_r, cvar.esp_bomb_g, cvar.esp_bomb_b);
			line_y += 15;

			Checkbox(x + box_indent_x, y + line_y, cvar.predict_path, "Simulate player trajectory");
			line_y += 15;

			Checkbox(x + box_indent_x, y + line_y, cvar.grenade_trajectory, "Simulate grenade trajectory");
			line_y += 15;

			Checkbox(x + box_indent_x, y + line_y, cvar.crosshair, "Crosshair");
			Palette(x + 227, y + line_y, cvar.crosshair_r, cvar.crosshair_g, cvar.crosshair_b);
			line_y += 15;

			Checkbox(x + box_indent_x, y + line_y, cvar.recoil_overlay, "Recoil overlay");
			Palette(x + 227, y + line_y, cvar.recoil_overlay_r, cvar.recoil_overlay_g, cvar.recoil_overlay_b);
			line_y += 15;

			Checkbox(x + box_indent_x, y + line_y, cvar.spread_overlay, "Spread overlay");
			Palette(x + 227, y + line_y, cvar.spread_overlay_r, cvar.spread_overlay_g, cvar.spread_overlay_b);
			line_y += 15;

			Checkbox(x + box_indent_x, y + line_y, cvar.penetration_info, "Penetration info");
			line_y += 30;

			char *tmp2[] = { "Text", "Icon" };
			ListBox(iListIndex++, x + box_indent_x, y + line_y, "Dropped weapons", cvar.esp_world_weapon, tmp2, 2, true);
			Palette(x + 227, y + line_y - 15, cvar.esp_world_weapon_r, cvar.esp_world_weapon_g, cvar.esp_world_weapon_b);
			line_y += 30;

			Checkbox(x + box_indent_x, y + line_y, cvar.draw_aim_fov, "Aimbot FOV");
			Palette(x + 227, y + line_y, cvar.draw_aim_fov_r, cvar.draw_aim_fov_g, cvar.draw_aim_fov_b);
			line_y += 15;
		}

		{//BOX3
			y = y + 220;
			line_y = 15;
			GroupBox(x, y, 250, 210, FONT_CENTER, "Effects");

			line_y += 10;
			Slider(x + box_indent_x, y + line_y, 0, 255, cvar.noflash, "Remove flashbang effects", true);
			line_y += 20;

			line_y += 10;
			Slider(x + box_indent_x, y + line_y, 0, 300, cvar.thirdperson, "Force third person", true);
			line_y += 20;

			Checkbox(x + box_indent_x, y + line_y, cvar.nosmoke, "Remove smoke");
			line_y += 18;

			Checkbox(x + box_indent_x, y + line_y, cvar.remove_scope, "Remove scope");
			line_y += 18;

			Checkbox(x + box_indent_x, y + line_y, cvar.norecoil_visual, "Visual norecoil");
			line_y += 18;

			line_y += 10;
			Slider(x + box_indent_x, y + line_y, 0, 255, cvar.brightness, "Brightness adjustment", true);
			Palette(x + 227, y + line_y - 15, cvar.brightness_r, cvar.brightness_g, cvar.brightness_b);
			line_y += 20;

			Checkbox(x + box_indent_x, y + line_y, cvar.disable_render_teammates, "Disable rendering of teammates");
			line_y += 18;

			Checkbox(x + box_indent_x, y + line_y, cvar.bullets_trace, "Bullets trace");
			line_y += 18;
		}

		{//draw no bug
			x = MenuX + 100;
			y = MenuY + 30;

			Palette(x + 227, save[4], cvar.chams_ct_invis_r, cvar.chams_ct_invis_g, cvar.chams_ct_invis_b);
			Palette(x + 207, save[4], cvar.chams_t_invis_r, cvar.chams_t_invis_g, cvar.chams_t_invis_b);

			Palette(x + 227, save[3], cvar.chams_ct_vis_r, cvar.chams_ct_vis_g, cvar.chams_ct_vis_b);
			Palette(x + 207, save[3], cvar.chams_t_vis_r, cvar.chams_t_vis_g, cvar.chams_t_vis_b);

			Palette(x + 227, save[5], cvar.esp_box_ct_invis_r, cvar.esp_box_ct_invis_g, cvar.esp_box_ct_invis_b);
			Palette(x + 207, save[5], cvar.esp_box_t_invis_r, cvar.esp_box_t_invis_g, cvar.esp_box_t_invis_b);

			Palette(x + 227, save[0], cvar.esp_box_ct_vis_r, cvar.esp_box_ct_vis_g, cvar.esp_box_ct_vis_b);
			Palette(x + 207, save[0], cvar.esp_box_t_vis_r, cvar.esp_box_t_vis_g, cvar.esp_box_t_vis_b);


			Palette(x + 227, save[1], cvar.esp_line_of_sight_r, cvar.esp_line_of_sight_g, cvar.esp_line_of_sight_b);

			Palette(x + 227, save[6] - 15, cvar.esp_weapon_r, cvar.esp_weapon_g, cvar.esp_weapon_b);
		}
	}
	else if (iCurrentTab == 5)
	{
		int x = MenuX + 100;
		int y = MenuY + 30;
		int box_indent_x = 10;
		int box_indent_y = 15;

		int save[256];

		int line_y = 15;

		{//BOX1
			GroupBox(x, y, 250, 430, FONT_CENTER, "Miscellaneous");

			Checkbox(x + box_indent_x, y + line_y, cvar.hud_clear, "HUD clear");
			line_y += 18;

			Checkbox(x + box_indent_x, y + line_y, cvar.autopistol, "Automatic weapons");
			line_y += 18;

			Checkbox(x + box_indent_x, y + line_y, cvar.autoreload, "Automatic reload");
			line_y += 18;

			Checkbox(x + box_indent_x, y + line_y, cvar.fastzoom, "Fast zoom");
			line_y += 18;

			Checkbox(x + box_indent_x, y + line_y, cvar.TTT, "TTT Mode");
			line_y += 30;

			if (cvar.TTT)
				cvar.aim_teammates = cvar.esp_teammates = true;

			Slider(x + box_indent_x, y + line_y, 0, 10000, cvar.name_stealer, "Name stealer", true, " ms");
			line_y += 20;

			if (DrawButton(x + box_indent_x, y + line_y, "Gamesites unban function",
				"Randomization of setinfo variables that are gamesites server's using to identify banned players."
			))
			{
				static int _ak, version, len;
				static char* str;
				char cmdstr[256];

				srand(time(NULL));

				len = rand() % 6 + 2;
				_ak = rand() % 999 + 100;
				version = rand() % 99999 + 10000;

				str = func.gen_random(len);

				std::string ch = std::to_string(func.hash_str(str));

				std::string s1 = "setinfo clientHash " + ch + "; ";
				std::string s2 = "setinfo _ak " + std::to_string(_ak) + "; ";
				std::string s3 = "setinfo version " + std::to_string(version) + "; ";
				std::string s123 = s1 + s2 + s3;

				strcat_s(cmdstr, s123.c_str());

				if (g_Local.status.connected)
					g_Engine.pfnClientCmd("disconnect");

				g_Engine.pfnClientCmd(cmdstr);

				if (cvar.debug)
				{
					g_Engine.Con_Printf("================================\n");
					g_Engine.Con_Printf("new clientHash %s\n", (PCHAR)ch.c_str());
					g_Engine.Con_Printf("new _ak %s\n", (PCHAR)std::to_string(_ak).c_str());
					g_Engine.Con_Printf("new version %s\n", (PCHAR)std::to_string(version).c_str());
					g_Engine.Con_Printf("================================\n");
				}
			}
			line_y += 22;

			if (DrawButton(x + box_indent_x, y + line_y, "Invisible name",
				"Sets name to invisible character."
			))
			{
				g_Engine.PlayerInfo_SetValueForKey("name", "kurva kokot");
			}
			line_y += 40;

			static int iSteamID;
			InputField(x + box_indent_x, y + line_y, "SteamID", 31, iSteamID, []() { g_SteamID.Apply(iSteamID); });
			line_y += 40;

			std::string backup_name;
			static std::string nick;

			if (backup_name.empty() && nick.empty() && (backup_name == g_Engine.pfnGetCvarString("name")))
				backup_name = g_Engine.pfnGetCvarString("name");

			if (nick.empty() && !backup_name.empty() && (backup_name != g_Engine.pfnGetCvarString("name")))
			{
				g_Engine.PlayerInfo_SetValueForKey("name", backup_name.c_str());
				backup_name.clear();
			}

			InputField(x + box_indent_x, y + line_y, "Name", 32, nick, []() { g_Engine.PlayerInfo_SetValueForKey("name", nick.c_str()); });
			line_y += 40;

			Checkbox(x + box_indent_x, y + line_y, cvar.spam, "Chat spam");
			line_y += 30;

			Slider(x + box_indent_x, y + line_y, 0, 10000, cvar.spam_timer, "Spam timer", true, " ms");
			line_y += 20;
		}

		{//BOX2
			x = x + 270;
			line_y = 15;
			GroupBox(x, y, 250, 170, FONT_CENTER, "Presets");

			if (DrawButton(x + box_indent_x, y + box_indent_y, "Load",
				"Load saved configuration."
			))
			{
				func.LoadCvars();
			}
			line_y += 22;

			if (DrawButton(x + box_indent_x, y + line_y, "Save",
				"Save current configuration."
			))
			{
				func.SaveCvars();
			}
			line_y += 24;

			if (cvar.rainbow == false)
			{
				g_Drawing.DrawString(MENU, x + box_indent_x, y + line_y, 180, 180, 180, 255, FONT_LEFT, "Menu color");
				save[0] = y + line_y;
				line_y += 14;

				Palette(x + 227, save[0], cvar.menu_color_r, cvar.menu_color_g, cvar.menu_color_b);
			}
			else
			{
				line_y += 10;

				Slider(x + box_indent_x, y + line_y, 0.1f, 26.0f, cvar.rainbow_freq, "Frequency", false, " Hz");
				line_y += 20;

				static DWORD color;
				color = func.rainbow(cvar.rainbow_freq);

				cvar.menu_color_r = RED(color);
				cvar.menu_color_g = GREEN(color);
				cvar.menu_color_b = BLUE(color);
			}


			if (cvar.rainbow2 == false)
			{
				g_Drawing.DrawString(MENU, x + box_indent_x, y + line_y, 180, 180, 180, 255, FONT_LEFT, "Other color");
				save[158] = y + line_y;
				line_y += 30;

				Palette(x + 227, save[158], cvar.cheat_global_color_r, cvar.cheat_global_color_g, cvar.cheat_global_color_b);
			}
			else
			{
				line_y += 10;

				Slider(x + box_indent_x, y + line_y, 0.1f, 26.0f, cvar.rainbow_freq2, "Frequency", false, " Hz");
				line_y += 20;

				static DWORD color;
				color = func.rainbow(cvar.rainbow_freq2);

				cvar.cheat_global_color_r = RED(color);
				cvar.cheat_global_color_g = GREEN(color);
				cvar.cheat_global_color_b = BLUE(color);
			}

			Checkbox(x + box_indent_x, y + line_y, cvar.rainbow, "Rainbow (1)");
			line_y += 13;

			Checkbox(x + box_indent_x, y + line_y, cvar.rainbow2, "Rainbow (2)");
			line_y += 18;

			g_Drawing.DrawString(MENU, x + box_indent_x, y + line_y, 180, 180, 180, 255, FONT_LEFT, "Menu key");
			KeyBind(x + box_indent_x + 180, y + line_y - 10, cvar.menu_key);
		}

		{//BOX3
			y = y + 180;
			line_y = 15;
			GroupBox(x, y, 250, 250, FONT_CENTER, "Other");

			Checkbox(x + box_indent_x, y + line_y, cvar.debug, "Debug");
			line_y += 14;

			Checkbox(x + box_indent_x, y + line_y, cvar.status, "Aimbot configuration");
			line_y += 14;

			Checkbox(x + box_indent_x, y + line_y, cvar.hide_from_obs, "Hide from OBS");
			line_y += 14;

			Checkbox(x + box_indent_x, y + line_y, cvar.bypass_valid_blockers, "Bypass valid blockers");
			line_y += 14;

			Checkbox(x + box_indent_x, y + line_y, cvar.bypass_trace_blockers, "Bypass trace blockers");
			line_y += 14;

			Checkbox(x + box_indent_x, y + line_y, cvar.esp_fake, "Bypass esp blockers");
			line_y += 30;

			Slider(x + box_indent_x, y + line_y, 0, 1, cvar.esp_sound_minimum_volume, "Minimum volume sound");
			line_y += 30;

			Slider(x + box_indent_x, y + line_y, 0, 6000, cvar.fakeping_amount, "Adjust speed");
			line_y += 20;

			Checkbox(x + box_indent_x, y + line_y, cvar.spread_overlay_old, "Spread overlay old");
			line_y += 18;

			if (DrawButton(x + box_indent_x, y + line_y, "Crash server",
				"#Label name crash exploit. (a lot servers have fixed this)"
			))
			{
				g_Misc.CrashServer();
			}
			line_y += 22;

			if (DrawButton(x + box_indent_x, y + line_y, "Patch interp cvars", format("Patch interpolation cvars.\n %20s\n%20s", "-cl_updaterate", "-ex_interp").c_str()
			))
			{
				g_Offsets.PatchInterpolation();
			}
			line_y += 22;

			if (DrawButton(x + box_indent_x, y + line_y, "Disable lag compensation (server)",
				"Force cl_lc to 0."
			))
			{
				g_Engine.PlayerInfo_SetValueForKey("cl_lc", "0");
			}
			line_y += 22;
		}
	}
	else if (iCurrentTab == 6)
	{
		int x = MenuX + 100;
		int y = MenuY + 30;
		int box_indent_x = 10;
		int box_indent_y = 15;

		int save[256];

		int line_y = 15;

		{//BOX1
			GroupBox(x, y, 520, 430, FONT_CENTER, "Player list");

			size_t max = g_Engine.GetMaxClients();

			if (max > 16)
				max = 16;

			for (int j = 1; j <= max; j++)
			{
				if (j == g_Local.iIndex)
					continue;

				if (g_PlayerInfoList[j].name)
				{
					if (g_Player[j].iTeam == CT)
						g_Drawing.DrawString(MENU, x + box_indent_x, y + line_y + 4, 0, 0, 180, 255, FONT_LEFT, "%i.) %s", j, g_PlayerInfoList[j].name);
					else if (g_Player[j].iTeam == TERRORIST)
						g_Drawing.DrawString(MENU, x + box_indent_x, y + line_y + 4, 180, 0, 0, 255, FONT_LEFT, "%i.) %s", j, g_PlayerInfoList[j].name);
					else
						g_Drawing.DrawString(MENU, x + box_indent_x, y + line_y + 4, 180, 180, 180, 255, FONT_LEFT, "%i.) %s", j, g_PlayerInfoList[j].name);
				}
				else
					g_Drawing.DrawString(MENU, x + box_indent_x, y + line_y + 4, 180, 180, 180, 255, FONT_LEFT, "%i.) ", j);

				if (g_PlayerInfoList[j].ping > 0)
				{
					Checkbox(x + box_indent_x + 160, y + line_y, g_Player[j].bFriend, "F");

					Checkbox(x + box_indent_x + 180, y + line_y, g_Player[j].bPriority, "P");

					Checkbox(x + box_indent_x + 200, y + line_y, g_Player[j].bTraitor, "T");
				}

				line_y += 20;
			}

			x = x + 270;
			line_y = 15;

			for (int j = max + 1; j <= g_Engine.GetMaxClients(); j++)
			{
				if (j == g_Local.iIndex)
					continue;

				if (g_PlayerInfoList[j].name)
				{
					if (g_Player[j].iTeam == CT)
						g_Drawing.DrawString(MENU, x + box_indent_x, y + line_y + 4, 0, 0, 180, 255, FONT_LEFT, "%i.) %s", j, g_PlayerInfoList[j].name);
					else if (g_Player[j].iTeam == TERRORIST)
						g_Drawing.DrawString(MENU, x + box_indent_x, y + line_y + 4, 180, 0, 0, 255, FONT_LEFT, "%i.) %s", j, g_PlayerInfoList[j].name);
					else
						g_Drawing.DrawString(MENU, x + box_indent_x, y + line_y + 4, 180, 180, 180, 255, FONT_LEFT, "%i.) %s", j, g_PlayerInfoList[j].name);
				}
				else
					g_Drawing.DrawString(MENU, x + box_indent_x, y + line_y + 4, 180, 180, 180, 255, FONT_LEFT, "%i.) ", j);

				if (g_PlayerInfoList[j].ping > 0)
				{
					Checkbox(x + box_indent_x + 160, y + line_y, g_Player[j].bFriend, "F");

					Checkbox(x + box_indent_x + 180, y + line_y, g_Player[j].bPriority, "P");
					
					Checkbox(x + box_indent_x + 200, y + line_y, g_Player[j].bTraitor, "T");
				}

				line_y += 20;
			}
		}
	}
}

void CMenu::InputField(int x, int y, char* text, int maxLen, int& out, std::function<void()>&& Callback)
{
	unsigned int w = 220;
	unsigned int h = 16;

	g_pISurface->DrawSetColor(cvar.cheat_global_color_r, cvar.cheat_global_color_g, cvar.cheat_global_color_b, 255);
	g_pISurface->DrawOutlinedRect(x - 2, y - 2, x + w + 2, y + h + 2);

	static bool callback	= false;
	static bool edit		= false;
	bool clicked			= false;
	bool inParams	= (CursorX >= x && CursorX <= x + w && CursorY >= y && CursorY <= y + h);

	auto effect_col = [&inParams]() -> DWORD {
		BYTE dR = 0;
		BYTE dG = 0;

		if (inParams)
		{
			if (g_Menu.keys[VK_RETURN])
				dR = 200;
			else
				dG = 200;
		}
		return COLORCODE(dR, dG, 0, 255);
	};

	DWORD colEffect = effect_col();

	static DWORD dwTemporaryBlockTimer = 0;

	static std::string value;

	if (GetTickCount64() - dwPaletteBlockedTime > 200 && GetTickCount64() - dwListBlockedTime > 200 && !bCursorInPalette && !bCursorInList && keys[VK_LBUTTON] && !IsDragging && inParams)
	{
		if (GetTickCount64() - dwTemporaryBlockTimer > 200)
		{
			clicked = true;
			dwTemporaryBlockTimer = GetTickCount64();
		}
	}

	if (clicked || inParams)
	{
		g_pISurface->DrawSetColor(RED(colEffect), GREEN(colEffect), BLUE(colEffect), 255);
		g_pISurface->DrawOutlinedRect(x - 1, y - 1, x + w + 1, y + h + 1);
	}

	if (text)
		g_Drawing.DrawString(MENU, x + 1, y - 10, 215, 215, 215, 255, FONT_LEFT, text);

	
	if (GetTickCount64() - dwInputfieldBlockedTime > 20 && !bCursorInPalette && !bCursorInList && !IsDragging && inParams)
	{
		if (maxLen != 0)
		{
			if (!(value.length() > maxLen))
				value.append(GetPressedNumKeyString());
		}

		if (!edit && keys[VK_BACK] == true)
		{
			edit = true;

			if (!value.empty())
				value.erase(std::prev(value.end()));
		}
		else if (keys[VK_BACK] == false)
		{
			edit = false;
		}

		dwInputfieldBlockedTime = GetTickCount64();
	}

	int iVal = std::atoi(value.c_str());

	//static bool update		= false;
	//static int attempts		= 0;

	if (inParams && !callback && (keys[VK_RETURN] == true))
	{
		callback = true;
		Callback();
	}
	else if (keys[VK_RETURN] == false)
	{
		callback = false;
	}

	if (out != iVal)
		out = iVal;

	/*
	if (out != iVal)
		if (inputfield.test_and_set(500))
			attempts++;

	if (attempts == 3)
	{
		attempts = 0;
		update = true;
	}
		
	if (update)
	{
		update = false;
		out = iVal;
		Callback();
	}
	*/

	if (!value.empty())
		g_Drawing.DrawString(MENU, x + w / 2, y + (h / 2), 220, 220, 220, 255, FONT_CENTER, value.c_str());
	else
		g_Drawing.DrawString(MENU, x + w / 2, y + (h / 2), 81, 81, 81, 255, FONT_CENTER, "N/A");

}

void CMenu::InputField(int x, int y, char* text, int maxStrLen, std::string& out, std::function<void()>&& Callback)
{
	unsigned int w = 220;
	unsigned int h = 16;

	g_pISurface->DrawSetColor(cvar.cheat_global_color_r, cvar.cheat_global_color_g, cvar.cheat_global_color_b, 255);
	g_pISurface->DrawOutlinedRect(x - 2, y - 2, x + w + 2, y + h + 2);

	static bool callback	= false;
	static bool edit		= false;
	bool clicked			= false;
	bool inParams			= (CursorX >= x && CursorX <= x + w && CursorY >= y && CursorY <= y + h);

	auto effect_col = [&inParams]() -> DWORD {
		BYTE dR = 0;
		BYTE dG = 0;

		if (inParams)
		{
			if (g_Menu.keys[VK_RETURN])
				dR = 200;
			else
				dG = 200;
		}
		return COLORCODE(dR, dG, 0, 255);
	};

	DWORD colEffect = effect_col();

	static DWORD dwTemporaryBlockTimer = 0;

	static std::string value;

	if (GetTickCount64() - dwPaletteBlockedTime > 200 && GetTickCount64() - dwListBlockedTime > 200 && !bCursorInPalette && !bCursorInList && keys[VK_LBUTTON] && !IsDragging && inParams)
	{
		if (GetTickCount64() - dwTemporaryBlockTimer > 200)
		{
			clicked = true;
			dwTemporaryBlockTimer = GetTickCount64();
		}
	}

	if (clicked || inParams)
	{
		g_pISurface->DrawSetColor(RED(colEffect), GREEN(colEffect), BLUE(colEffect), 255);
		g_pISurface->DrawOutlinedRect(x - 1, y - 1, x + w + 1, y + h + 1);
	}

	if (text)
		g_Drawing.DrawString(MENU, x + 1, y - 10, 215, 215, 215, 255, FONT_LEFT, text);


	if (GetTickCount64() - dwInputfieldBlockedTime > 20 && !bCursorInPalette && !bCursorInList && !IsDragging && inParams)
	{
		if (maxStrLen != 0)
		{
			if (!(value.length() > maxStrLen))
				value.append(GetPressedKeyString());
		}

		if (!edit && keys[VK_BACK] == true)
		{
			edit = true;

			if (!value.empty())
				value.erase(std::prev(value.end()));
		}
		else if (keys[VK_BACK] == false)
		{
			edit = false;
		}

		dwInputfieldBlockedTime = GetTickCount64();
	}

	std::string sVal = value.c_str();

	if (inParams && !callback && (keys[VK_RETURN] == true))
	{
		callback = true;
		Callback();
	}
	else if (keys[VK_RETURN] == false)
	{
		callback = false;
	}

	if (out != sVal)
		out = sVal;

	/*
	static bool update = false;
	static int attempts = 0;

	if (out != sVal)
		if (inputfield.test_and_set(500))
			attempts++;

	if (attempts == 3)
	{
		attempts = 0;
		update = true;
	}

	if (update)
	{
		update = false;
		out = sVal;
		Callback();
	}
	*/

	// draw value
	if (!value.empty())
		g_Drawing.DrawString(MENU, x + w / 2, y + (h / 2), 220, 220, 220, 255, FONT_CENTER, value.c_str());
	else
		g_Drawing.DrawString(MENU, x + w / 2, y + (h / 2), 81, 81, 81, 255, FONT_CENTER, "N/A");
}

bool CMenu::DrawButton(int x, int y, char *text)
{
	unsigned int w = 220;
	unsigned int h = 16;

	g_pISurface->DrawSetColor(cvar.cheat_global_color_r, cvar.cheat_global_color_g, cvar.cheat_global_color_b, 255);
	g_pISurface->DrawOutlinedRect(x - 2, y - 2, x + w + 2, y + h + 2);

	bool clicked = false;
	bool bCursorInParams = CursorX >= x && CursorX <= x + w && CursorY >= y && CursorY <= y + h;

	static DWORD dwTemporaryBlockTimer = 0;

	if (GetTickCount64() - dwPaletteBlockedTime > 200 && GetTickCount64() - dwListBlockedTime > 200 && !bCursorInPalette && !bCursorInList && keys[VK_LBUTTON] && !IsDragging && bCursorInParams)
	{
		if (GetTickCount64() - dwTemporaryBlockTimer > 200)
		{
			clicked = true;
			dwTemporaryBlockTimer = GetTickCount64();
		}
	}

	auto string_color = [&bCursorInParams]() -> DWORD {
		BYTE d = 0;
		int r, g, b;

		if (bCursorInParams)
		{
			r = cvar.cheat_global_color_r;
			g = cvar.cheat_global_color_g;
			b = cvar.cheat_global_color_b;
		}
		else
			r = g = b = 10;

		double luminance = (0.299 * r + 0.587 * g + 0.114 * b) / 255;

		if (luminance > 0.5)
			d = 0;
		else
			d = 255;

		return COLORCODE(d, d, d, 255);
	};

	DWORD sColor = string_color();

	if (clicked || bCursorInParams)
	{
		g_pISurface->DrawSetColor(cvar.cheat_global_color_r, cvar.cheat_global_color_g, cvar.cheat_global_color_b, 255);
		g_pISurface->DrawFilledRect(x, y, x + w, y + h);
	}
	else
	{
		g_pISurface->DrawSetColor(10, 10, 10, 255);
		g_pISurface->DrawFilledRect(x, y, x + w, y + h);
	}

	if (text)
		g_Drawing.DrawString(MENU, x + w / 2, y + (h / 2), RED(sColor), GREEN(sColor), BLUE(sColor), 255, FONT_CENTER, text);

	return clicked;
}

bool CMenu::DrawButton(int x, int y, char* text, const char* tooltip, ...)
{
	unsigned int w = 220;
	unsigned int h = 16;

	g_pISurface->DrawSetColor(cvar.cheat_global_color_r, cvar.cheat_global_color_g, cvar.cheat_global_color_b, 255);
	g_pISurface->DrawOutlinedRect(x - 2, y - 2, x + w + 2, y + h + 2);

	bool clicked = false;
	bool bCursorInParams = CursorX >= x && CursorX <= x + w && CursorY >= y && CursorY <= y + h;

	static DWORD dwTemporaryBlockTimer = 0;

	if (GetTickCount64() - dwPaletteBlockedTime > 200 && GetTickCount64() - dwListBlockedTime > 200 && !bCursorInPalette && !bCursorInList && keys[VK_LBUTTON] && !IsDragging && bCursorInParams)
	{
		if (GetTickCount64() - dwTemporaryBlockTimer > 200)
		{
			clicked = true;
			dwTemporaryBlockTimer = GetTickCount64();
		}
	}

	auto string_color = [&bCursorInParams]() -> DWORD {
		BYTE d = 0;
		int r, g, b;

		if (bCursorInParams)
		{
			r = cvar.cheat_global_color_r;
			g = cvar.cheat_global_color_g;
			b = cvar.cheat_global_color_b;
		}
		else
			r = g = b = 10;

		double luminance = (0.299 * r + 0.587 * g + 0.114 * b) / 255;

		if (luminance > 0.5)
			d = 0;
		else
			d = 255;

		return COLORCODE(d, d, d, 255);
	};

	DWORD sColor = string_color();

	if (clicked || bCursorInParams)
	{
		g_pISurface->DrawSetColor(cvar.cheat_global_color_r, cvar.cheat_global_color_g, cvar.cheat_global_color_b, 255);
		g_pISurface->DrawFilledRect(x, y, x + w, y + h);
	}
	else
	{
		g_pISurface->DrawSetColor(10, 10, 10, 255);
		g_pISurface->DrawFilledRect(x, y, x + w, y + h);
	}

	if (text)
		g_Drawing.DrawString(MENU, x + w / 2, y + (h / 2), RED(sColor), GREEN(sColor), BLUE(sColor), 255, FONT_CENTER, text);

	if (clicked || bCursorInParams)
	{
		static char formated_string[256];
		std::snprintf(formated_string, sizeof(formated_string), tooltip);

		if (strlen(formated_string) != 0)
			after_menu.push_back([&] { CMenu::Tooltip(formated_string); });
	}

	return clicked;
}

void CMenu::Palette(int x, int y, float &r, float &g, float &b)
{
	unsigned int w = 16;
	unsigned int h = 8;

	static DWORD dwTemporaryBlockTimer = 0;
	//Close others and open this
	if (GetTickCount64() - dwListBlockedTime > 200 && GetTickCount64() - dwPaletteBlockedTime > 200 && !bCursorInList && keys[VK_LBUTTON] && !IsDragging && CursorX >= x && CursorX <= x + w && CursorY >= y && CursorY <= y + h)
	{
		if (GetTickCount64() - dwTemporaryBlockTimer > 200)
		{
			bPaletteOpened[iPaletteIndex] = !bPaletteOpened[iPaletteIndex];

			dwTemporaryBlockTimer = GetTickCount64();

			for (unsigned int i = 0; i < LIMIT_PALETTE; i++)
			{
				if (i == iPaletteIndex) continue;

				if (bPaletteOpened[i])
					bPaletteOpened[i] = false;
			}
		}
	}

	g_pISurface->DrawSetColor(r, g, b, 255);
	g_pISurface->DrawFilledRect(x, y, x + w, y + h);

	g_pISurface->DrawSetColor(5, 5, 5, 230);
	g_pISurface->DrawOutlinedRect(x - 1, y - 1, x + w + 1, y + h + 1);

	//shadow
	g_pISurface->DrawSetColor(10, 10, 10, 230);
	g_pISurface->DrawOutlinedRect(x - 2, y - 2, x + w + 2, y + h + 2);

	static unsigned int panel_w = 230;
	static unsigned int panel_h = 54;
	static unsigned int indent = 8;
	static unsigned int border = 4;

	if (bPaletteOpened[iPaletteIndex])
	{
		g_pISurface->DrawSetColor(1, 1, 1, 255);
		g_pISurface->DrawFilledRect(x + w + indent - border, y - indent, x + w + panel_w + indent + border, y + panel_h + indent);

		g_pISurface->DrawSetColor(60, 60, 60, 255);
		g_pISurface->DrawOutlinedRect(x + w + indent - border - 1, y - indent - 1, x + w + panel_w + indent + border + 1, y + panel_h + indent + 1);

		//shadow
		g_pISurface->DrawSetColor(10, 10, 10, 255);
		g_pISurface->DrawOutlinedRect(x + w + indent - border - 2, y - indent - 2, x + w + panel_w + indent + border + 2, y + panel_h + indent + 2);

		SliderInPallete(x + w + indent, y, 0, 255, r, "", true);
		SliderInPallete(x + w + indent, y + 20, 0, 255, g, "", true);
		SliderInPallete(x + w + indent, y + 40, 0, 255, b, "", true);
	}

	if (bPaletteOpened[iPaletteIndex] && !IsDragging && CursorX >= x + w + indent - border && CursorX <= x + w + panel_w + indent + border && CursorY >= y - indent && CursorY <= y + panel_h + indent)
	{
		bCursorInPalette = true;
		dwInputfieldBlockedTime = GetTickCount64();
		dwCheckboxBlockedTime = GetTickCount64();
		dwPaletteBlockedTime = GetTickCount64();
		dwSliderBlockedTime = GetTickCount64();
	}

	iPaletteIndex++;
}

void CMenu::ListBox(int index, int x, int y, char *name, float &value, char **text, int size, bool default)
{
	unsigned int w = 230;
	unsigned int h = 18;

	if (name)
		g_Drawing.DrawString(MENU, x + 1, y - 10, 180, 180, 180, 255, FONT_LEFT, name);

	static DWORD dwTemporaryBlockTimer = 0;
	//Close others and open this
	if (!bListBoxOpened[index] && GetTickCount64() - dwPaletteBlockedTime > 200 && GetTickCount64() - dwListBlockedTime > 200 && !bCursorInPalette && keys[VK_LBUTTON] && !IsDragging && CursorX >= x && CursorX <= x + w && CursorY >= y && CursorY <= y + h)
	{
		if (GetTickCount64() - dwTemporaryBlockTimer > 200)
		{
			bListBoxOpened[index] = !bListBoxOpened[index];

			dwTemporaryBlockTimer = GetTickCount64();

			for (unsigned int i = 0; i < LIMIT_LISTBOX; i++)
			{
				if (i == index) continue;

				if (bListBoxOpened[i])
				{
					bListBoxOpened[i] = false;
				}
			}
		}
	}

	bool effect_cursor = false;
	int effect_cursor_x0, effect_cursor_y0, effect_cursor_x1, effect_cursor_y1;
	int tmp = h;

	if (!bListBoxOpened[index])
	{
		g_pISurface->DrawSetColor(1, 1, 1, 200);
		g_pISurface->DrawFilledRect(x, y, x + w, y + tmp);

		g_pISurface->DrawSetColor(5, 5, 5, 200);
		g_pISurface->DrawOutlinedRect(x - 1, y - 1, x + w + 1, y + tmp + 1);

		//shadow
		g_pISurface->DrawSetColor(cvar.cheat_global_color_r, cvar.cheat_global_color_g, cvar.cheat_global_color_b, 200);
		g_pISurface->DrawOutlinedRect(x - 2, y - 2, x + w + 2, y + tmp + 2);

		bool m_bDrawDefault = true;

		for (unsigned int i = 0; i < size; i++)
		{
			if (text[i] && value == i + 1)
			{
				m_bDrawDefault = false;
				g_Drawing.DrawString(MENU, x + 4, y + (h / 2), 220, 220, 220, 255, FONT_LEFT, text[i]);
			}
		}

		if (m_bDrawDefault && default)
			g_Drawing.DrawString(MENU, x + 4, y + (h / 2), 220, 220, 220, 255, FONT_LEFT, "None");
	}
	else
	{
		for (unsigned int i = 0; i < size; i++)
		{
			if (text[i])
			{
				if (CursorX >= x && CursorX <= x + w && CursorY >= y + tmp - h && CursorY <= y + tmp)
				{
					effect_cursor_x0 = x;
					effect_cursor_x1 = x + w;
					effect_cursor_y0 = y + tmp - h;
					effect_cursor_y1 = y + tmp;
					effect_cursor = true;
				}

				if (GetTickCount64() - dwTemporaryBlockTimer > 200 && keys[VK_LBUTTON] && !IsDragging && CursorX >= x && CursorX <= x + w && CursorY >= y + tmp - h && CursorY <= y + tmp)
				{
					value = i + 1;
					bListBoxOpened[index] = false;
					dwTemporaryBlockTimer = GetTickCount64();
				}

				tmp += h;
			}
		}

		if (default)
		{
			if (GetTickCount64() - dwTemporaryBlockTimer > 200 && keys[VK_LBUTTON] && !IsDragging && CursorX >= x && CursorX <= x + w && CursorY >= y && CursorY <= y + tmp)
			{
				value = 0;
				bListBoxOpened[index] = false;
				dwTemporaryBlockTimer = GetTickCount64();
			}
		}
		else
			tmp -= h;

		g_pISurface->DrawSetColor(1, 1, 1, 200);
		g_pISurface->DrawFilledRect(x, y, x + w, y + tmp);

		g_pISurface->DrawSetColor(5, 5, 5, 200);
		g_pISurface->DrawOutlinedRect(x - 1, y - 1, x + w + 1, y + tmp + 1);

		//shadow
		g_pISurface->DrawSetColor(cvar.cheat_global_color_r, cvar.cheat_global_color_g, cvar.cheat_global_color_b, 200);
		g_pISurface->DrawOutlinedRect(x - 2, y - 2, x + w + 2, y + tmp + 2);
	}

	if (effect_cursor)
	{
		g_pISurface->DrawSetColor(10, 10, 10, 200);
		g_pISurface->DrawFilledRect(effect_cursor_x0, effect_cursor_y0, effect_cursor_x1, effect_cursor_y1);
	}

	if (bListBoxOpened[index])
	{
		tmp = h;

		for (unsigned int i = 0; i < size; i++)
		{
			if (text[i])
			{
				g_Drawing.DrawString(MENU, x + 4, y + tmp - (h / 2), 220, 220, 220, 255, FONT_LEFT, text[i]);
				tmp += h;
			}
		}

		if (default)
			g_Drawing.DrawString(MENU, x + 4, y + tmp - (h / 2), 220, 220, 220, 255, FONT_LEFT, "None");
		else
			tmp -= h;
	}

	if (bListBoxOpened[index] && !IsDragging && CursorX >= x && CursorX <= x + w && CursorY >= y && CursorY <= y + tmp)
	{
		bCursorInList = true;
		dwCheckboxBlockedTime = GetTickCount64();
		dwListBlockedTime = GetTickCount64();
		dwSliderBlockedTime = GetTickCount64();
	}
}

void CMenu::SliderInPallete(int x, int y, float min, float max, float &value, char *text, bool ThisINT, char *amout, bool extra)
{
	unsigned int w = 230;
	unsigned int h = 12;

	g_pISurface->DrawSetColor(1, 1, 1, 100);
	g_pISurface->DrawFilledRect(x, y, x + w, y + h);

	g_pISurface->DrawSetColor(5, 5, 5, 100);
	g_pISurface->DrawOutlinedRect(x - 1, y - 1, x + w + 1, y + h + 1);

	//shadow
	g_pISurface->DrawSetColor(10, 10, 10, 200);
	g_pISurface->DrawOutlinedRect(x - 2, y - 2, x + w + 2, y + h + 2);

	if (text)
		g_Drawing.DrawString(MENU, x + 1, y - 10, 220, 220, 220, 255, FONT_LEFT, text);

	if (ThisINT)
		value = (int)value;

	if (value < min)
		value = min;
	else if (value > max)
		value = max;

	float one = (w / max);

	int fill = one * value;

	if (value < 0)
		fill *= -1;

	static const int highlightSizeX = 3;
	int highlightStartX = x + (fill - highlightSizeX);
	int highlightEndX = highlightStartX + highlightSizeX;

	g_pISurface->DrawSetColor(81, 81, 81, 255);
	g_pISurface->DrawFilledRect(x, y, x + fill - highlightSizeX, y + h);

	g_pISurface->DrawSetColor(cvar.cheat_global_color_r, cvar.cheat_global_color_g, cvar.cheat_global_color_b, 255);
	g_pISurface->DrawFilledRect(highlightStartX, y, highlightEndX, y + h);

	if (!amout)
		amout = "";

	if (!ThisINT)
	{
		if (!extra)
			g_Drawing.DrawString(MENU, x + (w / 2), y + (h / 2), 255, 255, 255, 255, FONT_CENTER, "%.2f%s", value, amout);
		else
			g_Drawing.DrawStringACP(MENU, x + (w / 2), y + (h / 2), 255, 255, 255, 255, FONT_CENTER, "%.2f%s", value, amout);
	}
	else
	{
		if (!extra)
			g_Drawing.DrawString(MENU, x + (w / 2), y + (h / 2), 255, 255, 255, 255, FONT_CENTER, "%.f%s", value, amout);
		else
			g_Drawing.DrawString(MENU, x + (w / 2), y + (h / 2), 255, 255, 255, 255, FONT_CENTER, "%.f%s", value, amout);
	}

	if (GetTickCount64() - dwListBlockedTime > 200 && !bCursorInPalette && !bCursorInList && !IsDragging && CursorX >= x && CursorX <= x + w && CursorY >= y && CursorY <= y + h)
	{
		if (keys[VK_LBUTTON]) {
			value = (CursorX - x) / one;

			if (value < min)
				value = min;
			else if (value > max)
				value = max;
		}
		else if (keys[VK_RBUTTON] && min < 0) {
			value = (CursorX - x) / one;
			value *= -1;

			if (value < min)
				value = min;
			else if (value > max)
				value = max;
		}
	}
}

void CMenu::KeyBind(int x, int y, int &key)
{
	unsigned int w = 60;
	unsigned int h = 18;

	bool clicked = false;

	static DWORD dwTemporaryBlockTimer = 0;

	if (GetTickCount64() - dwPaletteBlockedTime > 200 && GetTickCount64() - dwListBlockedTime > 200 && !bCursorInPalette && !bCursorInList && keys[VK_LBUTTON] && !IsDragging && CursorX >= x && CursorX <= x + w && CursorY >= y && CursorY <= y + h)
	{
		if (GetTickCount64() - dwTemporaryBlockTimer > 200)
		{
			clicked = true;
			dwTemporaryBlockTimer = GetTickCount64();
		}
	}

	if (key == -2 && GetTickCount64() - dwTemporaryBlockTimer > 200)
	{
		for (unsigned int i = 0; i < 255; i++)
		{
			if (g_Menu.keys[i])
			{
				if (i == VK_ESCAPE || i == VK_LBUTTON || i == VK_RBUTTON || i == cvar.menu_key)
				{
					key = -1;
					break;
				}
				key = i;
			}
		}
	}

	if (clicked)
	{
		if (key == -1) {
			key = -2;
		}
		else {
			key = -1;
		}
	}

	if (key == -1)
	{
		g_Drawing.DrawString(MENU, x + w / 2, y + (h / 2), 200, 200, 200, 255, FONT_CENTER, "[N/A]");
	}
	else if (key == -2)
	{
		g_Drawing.DrawString(MENU, x + w / 2, y + (h / 2), 220, 220, 220, 255, FONT_CENTER, "[Press key]");
	}
	else {
		g_Drawing.DrawString(MENU, x + w / 2, y + (h / 2), 255, 255, 255, 255, FONT_CENTER, "[%s]", VirtualKeyCodeToString(key).c_str());
	}
}

void CMenu::Slider(int x, int y, float min, float max, float &value, char *text, bool ThisINT, char *amout, bool extra)
{
	unsigned int w = 230;
	unsigned int h = 12;

	g_pISurface->DrawSetColor(5, 5, 5, 255);
	g_pISurface->DrawFilledRect(x, y, x + w, y + h);

	g_pISurface->DrawSetColor(0, 0, 0, 255);
	g_pISurface->DrawOutlinedRect(x - 1, y - 1, x + w + 1, y + h + 1);

	//shadow
	g_pISurface->DrawSetColor(10, 10, 10, 255);
	g_pISurface->DrawOutlinedRect(x - 2, y - 2, x + w + 2, y + h + 2);

	if (text)
		g_Drawing.DrawString(MENU, x + 1, y - 10, 220, 220, 220, 255, FONT_LEFT, text);

	if (ThisINT)
		value = (int)value;

	if (value < min)
		value = min;
	else if (value > max)
		value = max;

	float one = (w / max);

	int fill = one * value;

	if (value < 0)
		fill *= -1;

	static const int highlightSizeX = 3;
	int highlightStartX = x + (fill - highlightSizeX);
	int highlightEndX = highlightStartX + highlightSizeX;

	g_pISurface->DrawSetColor(81, 81, 81, 255);
	g_pISurface->DrawFilledRect(x, y, x + fill - highlightSizeX, y + h);

	g_pISurface->DrawSetColor(cvar.cheat_global_color_r, cvar.cheat_global_color_g, cvar.cheat_global_color_b, 125);
	g_pISurface->DrawFilledRect(highlightStartX, y, highlightEndX, y + h);

	if (!amout)
		amout = "";

	if (!ThisINT)
	{
		if (!extra)
			g_Drawing.DrawString(MENU, x + (w / 2), y + (h / 2), 255, 255, 255, 255, FONT_CENTER, "%.2f%s", value, amout);
		else
			g_Drawing.DrawStringACP(MENU, x + (w / 2), y + (h / 2), 255, 255, 255, 255, FONT_CENTER, "%.2f%s", value, amout);
	}
	else
	{
		if (!extra)
			g_Drawing.DrawString(MENU, x + (w / 2), y + (h / 2), 255, 255, 255, 255, FONT_CENTER, "%.f%s", value, amout);
		else
			g_Drawing.DrawString(MENU, x + (w / 2), y + (h / 2), 255, 255, 255, 255, FONT_CENTER, "%.f%s", value, amout);
	}

	if (GetTickCount64() - dwSliderBlockedTime > 200 && GetTickCount64() - dwListBlockedTime > 200 && !bCursorInPalette && !bCursorInList && !IsDragging && CursorX >= x && CursorX <= x + w && CursorY >= y && CursorY <= y + h)
	{
		static int upTrueCount = 0;
		static int downTrueCount = 0;

		time_t start = time(0);

		if (start < 1)
		{
			if (cvar.m_Wheel_up)
				upTrueCount += 1;

			if (cvar.m_Wheel_down)
				downTrueCount += 1;
		}


		if (cvar.m_Wheel_up)
			value += 3 + upTrueCount;

		if (cvar.m_Wheel_down)
			value -= 3 + downTrueCount;

		cvar.m_Wheel_up = false;
		cvar.m_Wheel_down = false;

		upTrueCount = 0;
		downTrueCount = 0;

		if (keys[VK_LBUTTON]) {
			value = (CursorX - x) / one;

			if (value < min)
				value = min;
			else if (value > max)
				value = max;
		}
		else if (keys[VK_RBUTTON] && min < 0) {
			value = (CursorX - x) / one;
			value *= -1;

			if (value < min)
				value = min;
			else if (value > max)
				value = max;
		}
	}
}

void CMenu::DrawMenuTabs()
{
	int tab_x = BORDER_SIZE + 1;
	int tab_y = BORDER_SIZE + 1 + 10;
	int tab_h = ((background.height - (BORDER_SIZE * 2)) / MAX_TABS) - 20;
	int tab_w = tab_x + TAB_WEIGHT;

	int y = BORDER_SIZE + 1 + 15;
	int x = BORDER_SIZE + 1 + 12;

	for (unsigned int i = 1; i <= MAX_TABS; i++)
	{
		if (i != iCurrentTab)
		{
			if (i == 1)
				g_Drawing.DrawTexture(icon_headshot_not_selected.index, MenuX + x, MenuY + y, MenuX + x + icon_headshot.width, MenuY + y + icon_headshot.width, 100, 100, 100, 100);
			else if (i == 2)
				g_Drawing.DrawTexture(icon_aimbot_not_selected.index, MenuX + x, MenuY + y, MenuX + x + icon_aimbot.width, MenuY + y + icon_aimbot.height, 100, 100, 100, 100);
			else if (i == 3)
				g_Drawing.DrawTexture(icon_systems_not_selected.index, MenuX + x, MenuY + y, MenuX + x + icon_systems.width, MenuY + y + icon_systems.height, 100, 100, 100, 100);
			else if (i == 4)
				g_Drawing.DrawTexture(icon_visuals_not_selected.index, MenuX + x, MenuY + y, MenuX + x + icon_visuals.width, MenuY + y + icon_visuals.height, 100, 100, 100, 100);
			else if (i == 5)
				g_Drawing.DrawTexture(icon_options_not_selected.index, MenuX + x, MenuY + y, MenuX + x + icon_options.width, MenuY + y + icon_options.height, 100, 100, 100, 100);
			else if (i == 6)
				g_Drawing.DrawTexture(icon_members_not_selected.index, MenuX + x, MenuY + y, MenuX + x + icon_members.width, MenuY + y + icon_members.height, 100, 100, 100, 100);
		}
		else {
			g_pISurface->DrawSetColor(30, 30, 30, 200);
			g_pISurface->DrawFilledRect(MenuX + tab_x, MenuY + tab_y, MenuX + tab_w, MenuY + tab_y + tab_h);

			g_pISurface->DrawSetColor(100, 100, 100, 200);
			g_pISurface->DrawFilledRect(MenuX + tab_x, MenuY + tab_y - 1, MenuX + tab_w, MenuY + tab_y);
			g_pISurface->DrawSetColor(0, 0, 0, 255);
			g_pISurface->DrawFilledRect(MenuX + tab_x, MenuY + tab_y - 1, MenuX + tab_w - 1, MenuY + tab_y - 2);

			g_pISurface->DrawSetColor(100, 100, 100, 200);
			g_pISurface->DrawFilledRect(MenuX + tab_x, MenuY + tab_y + tab_h - 1, MenuX + tab_w, MenuY + tab_y + tab_h);
			g_pISurface->DrawSetColor(0, 0, 0, 255);
			g_pISurface->DrawFilledRect(MenuX + tab_x, MenuY + tab_y + tab_h + 1, MenuX + tab_w - 1, MenuY + tab_y + tab_h + 2);

			if (iCurrentTab == 1)
				g_Drawing.DrawTexture(icon_headshot.index, MenuX + x, MenuY + y, MenuX + x + icon_headshot.width, MenuY + y + icon_headshot.width);
			else if (iCurrentTab == 2)
				g_Drawing.DrawTexture(icon_aimbot.index, MenuX + x, MenuY + y, MenuX + x + icon_aimbot.width, MenuY + y + icon_aimbot.height);
			else if (iCurrentTab == 3)
				g_Drawing.DrawTexture(icon_systems.index, MenuX + x, MenuY + y, MenuX + x + icon_systems.width, MenuY + y + icon_systems.height);
			else if (iCurrentTab == 4)
				g_Drawing.DrawTexture(icon_visuals.index, MenuX + x, MenuY + y, MenuX + x + icon_visuals.width, MenuY + y + icon_visuals.height);
			else if (iCurrentTab == 5)
				g_Drawing.DrawTexture(icon_options.index, MenuX + x, MenuY + y, MenuX + x + icon_options.width, MenuY + y + icon_options.height);
			else if (iCurrentTab == 6)
				g_Drawing.DrawTexture(icon_members.index, MenuX + x, MenuY + y, MenuX + x + icon_members.width, MenuY + y + icon_members.height);
		}

		y = y + tab_h + 20;
		tab_y = tab_y + tab_h + 20;
	}
}

void CMenu::Drag()
{
	if (bCursorInList || bCursorInPalette)
	{
		IsDragging = false;
		IsDraggingPlist = false;
		return;
	}

	static int drag_x = 0;
	static int drag_y = 0;

	if ((IsDragging || IsDraggingPlist) && !keys[VK_LBUTTON])
	{
		if (IsDragging)
			IsDragging = false;
		else if (IsDraggingPlist)
			IsDraggingPlist = false;
	}
	else if ((IsDragging || IsDraggingPlist) && keys[VK_LBUTTON])
	{
		if (IsDragging)
		{
			MenuX = CursorX - drag_x;
			MenuY = CursorY - drag_y;
		}
		else if (IsDraggingPlist)
		{
			plistX = CursorX - drag_x;
			plistY = CursorY - drag_y;
		}
	}

	//head move
	if (keys[VK_LBUTTON] && (
		(CursorX >= MenuX && CursorX <= background.width + MenuX && CursorY >= MenuY && CursorY <= MenuY + BORDER_SIZE) ||
		(CursorX >= MenuX && CursorX <= MenuX + BORDER_SIZE && CursorY >= MenuY && CursorY <= background.height + MenuY) ||
		(CursorX >= MenuX + background.width - BORDER_SIZE && CursorX <= MenuX + background.width && CursorY >= MenuY && CursorY <= background.height + MenuY) ||
		(CursorX >= MenuX && CursorX <= background.width + MenuX && CursorY >= MenuY + background.height - BORDER_SIZE && CursorY <= MenuY + background.height)))
	{
		drag_x = CursorX - MenuX;
		drag_y = CursorY - MenuY;
		IsDragging = true;
	}

	if (keys[VK_LBUTTON] && (
		(CursorX >= plistX && CursorX <= background.width + plistX && CursorY >= plistY && CursorY <= plistY + BORDER_SIZE) ||
		(CursorX >= plistX && CursorX <= plistX + BORDER_SIZE && CursorY >= plistY && CursorY <= background.height + plistY) ||
		(CursorX >= plistX + background.width - BORDER_SIZE && CursorX <= plistX + background.width && CursorY >= MenuY && CursorY <= background.height + plistY) ||
		(CursorX >= plistX && CursorX <= background.width + plistX && CursorY >= plistY + background.height - BORDER_SIZE && CursorY <= plistY + background.height)))
	{
		drag_x = CursorX - plistX;
		drag_y = CursorY - plistY;
		IsDraggingPlist = true;
	}
}

void CMenu::SelectTab()
{
	int x = BORDER_SIZE + 1;
	int y = BORDER_SIZE + 1;
	int h = (background.height - (BORDER_SIZE * 2)) / MAX_TABS;
	int w = x + TAB_WEIGHT - 1;

	if (keys[VK_LBUTTON] && !IsDragging)
	{
		for (unsigned int i = 1; i <= MAX_TABS; i++)
		{
			if (CursorX >= MenuX + x && CursorX <= MenuX + w && CursorY >= MenuY + y && CursorY <= MenuY + y + h)
			{
				iCurrentTab = i;
				return;
			}
			y = y + h;
		}
	}
}

void CMenu::Checkbox(int x, int y, bool &value, char *text)
{
	static unsigned int w = 8;
	static unsigned int h = 8;

	g_pISurface->DrawSetColor(30, 30, 30, 255);
	g_pISurface->DrawOutlinedRect(x, y, x + w, y + h);

	g_pISurface->DrawSetColor(0, 0, 0, 200);
	g_pISurface->DrawOutlinedRect(x - 1, y - 1, x + w + 1, y + h + 1);

	if (value)
	{
		g_pISurface->DrawSetColor(cvar.menu_color_r, cvar.menu_color_g, cvar.menu_color_b, 255);
		g_pISurface->DrawFilledRect(x + 1, y + 1, x + w - 1, y + h - 1);
	}

	if (text)
		g_Drawing.DrawString(MENU, x + 16, y + 4, 200, 200, 200, 255, FONT_LEFT, text);

	if (GetTickCount64() - dwCheckboxBlockedTime > 200 && !bCursorInPalette && !bCursorInList && keys[VK_LBUTTON] && !IsDragging && CursorX >= x && CursorX <= x + w && CursorY >= y && CursorY <= y + h)
	{
		value = !value;
		dwCheckboxBlockedTime = GetTickCount64();
	}
}

void CMenu::Tooltip(const char* text, ...)
{
	static const int scaling = 1;
	static const int y_offset = 20;
	static const int x_offset = 11;

	int width, height, x, y;
	g_Drawing.GetTextSize(width, height, MENU, text);

	g_pISurface->SurfaceGetCursorPos(x, y);

	int startFillY = (y + y_offset) - scaling;
	int startFillX = (x + x_offset) - scaling;

	int endFillY = startFillY;
	int endFillX = startFillX;

	endFillY += height	+ scaling;
	endFillX += width	+ scaling;

	g_pISurface->DrawSetColor(10, 10, 10, 255);
	g_pISurface->DrawFilledRect(startFillX, startFillY, endFillX, endFillY);

	g_pISurface->DrawSetColor(cvar.cheat_global_color_r, cvar.cheat_global_color_g, cvar.cheat_global_color_b, 255);
	g_pISurface->DrawOutlinedRect(startFillX - scaling, startFillY - scaling, endFillX + scaling, endFillY + scaling);

	auto strings = split_string(text, "\n");
	int line = (y + y_offset);

	for (auto itr = strings.begin(); itr != strings.end(); itr++)
	{
		std::string pString = *itr;
		g_Drawing.DrawString(MENU, x + x_offset, line, 220, 220, 220, 255, pString.c_str());
		line += 11;
	}
}

void CMenu::DrawBox(int x, int y, int w, int h)
{
	//box
	g_pISurface->DrawSetColor(0, 0, 0, 255);
	g_pISurface->DrawFilledRect(x, y, x + w, y + h);

	//outline
	g_pISurface->DrawSetColor(16, 16, 16, 255);
	g_pISurface->DrawOutlinedRect(x - 1, y - 1, x + w + 1, y + h + 1);

	//shadow
	g_pISurface->DrawSetColor(cvar.cheat_global_color_r, cvar.cheat_global_color_g, cvar.cheat_global_color_b, 255);
	g_pISurface->DrawOutlinedRect(x - 2, y - 2, x + w + 2, y + h + 2);
}

void CMenu::GroupBox(int x, int y, int w, int h, DWORD alignment, const char* name, ...)
{
	DrawBox(x, y, w, h);

	static const int scaling = 1;
	static const int y_offset = 2;
	static const int x_offset = 2;

	int width, height;
	g_Drawing.GetTextSize(width, height, MENU, name);

	if (alignment & FONT_RIGHT)
		x += (w - width) - scaling;
	else if (alignment & FONT_CENTER)
		x += (w - width) / 2 - scaling;
	else x += x_offset;

	int startFillY = (y - height / 2) - (scaling + y_offset);
	int startFillX = (x - x_offset) + scaling;

	int endFillY = startFillY;
	int endFillX = startFillX;

	endFillY += height	+ scaling;
	endFillX += width	+ scaling;

	g_pISurface->DrawSetColor(10, 10, 10, 255);
	g_pISurface->DrawFilledRect(startFillX, startFillY, endFillX, endFillY);

	//g_pISurface->DrawSetColor(100, 0, 0, 255);
	//g_pISurface->DrawOutlinedRect(startFillX - scaling, startFillY - scaling, endFillX + scaling, endFillY + scaling);

	g_Drawing.DrawString(MENU, x, (y - height / 2) - y_offset, 220, 220, 220, 255, name);
}