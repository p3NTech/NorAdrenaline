#include "Required.h"
#include <Shlobj.h>
#include "Reflective\ReflectiveLoader.h"

#pragma comment(lib, "ws2_32.lib")

IVGuiModuleLoader*			g_pIVGuiModuleLoader		= nullptr;
IRunGameEngine*				g_pIRunGameEngine			= nullptr;
IGameUI*					g_pGameUI					= nullptr;
IGameConsole*				g_pConsole					= nullptr;
vgui::IPanel*				g_pIPanel					= nullptr;
vgui::ISurface*				g_pISurface					= nullptr;
vgui::IEngineVGui*			g_pIEngineVGui				= nullptr;
cl_clientfunc_t*			g_pClient					= nullptr;
cl_clientfunc_t				g_Client;
cl_enginefunc_t*			g_pEngine					= nullptr;
cl_enginefunc_t				g_Engine;
engine_studio_api_t*		g_pStudio					= nullptr;
engine_studio_api_t			g_Studio;
playermove_t*				pmove						= nullptr;
UserMsg						pUserMsgBase				= nullptr;
Snapshot_t					Snapshot_s					= nullptr;
Screenshot_t				Screenshot_s				= nullptr;
CL_Move_t					CL_Move_s					= nullptr;
PreS_DynamicSound_t			PreS_DynamicSound_s			= nullptr;
StudioModelRenderer_t		g_StudioModelRenderer;
StudioModelRenderer_t*		g_pStudioModelRenderer		= nullptr;

Netchan_FragSend_t				Netchan_FragSend_s				= nullptr;
Netchan_TransmitBits_t			Netchan_TransmitBits_s			= nullptr;
Netchan_CreateFileFragments_t	Netchan_CreateFileFragments_s	= nullptr;

IFileSystem*				g_pFileSystem;
ISteamInterface				g_SteamInterface;

VHookTable PanelHook;

LRESULT CALLBACK Hooked_WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_LBUTTONDOWN:
		g_Menu.keys[VK_LBUTTON] = true;
		break;
	case WM_LBUTTONUP:
		g_Menu.keys[VK_LBUTTON] = false;
		break;
	case WM_RBUTTONDOWN:
		g_Menu.keys[VK_RBUTTON] = true;
		break;
	case WM_RBUTTONUP:
		g_Menu.keys[VK_RBUTTON] = false;
		break;
	case WM_KEYDOWN:
		g_Menu.keys[wParam] = true;
		break;
	case WM_KEYUP:
		g_Menu.keys[wParam] = false;
		break;
	case WM_MOUSEWHEEL:
		if ((short)HIWORD(wParam) < 0)
		{
			cvar.m_Wheel_up = false;
			cvar.m_Wheel_down = true;
		}
		else
		{
			cvar.m_Wheel_down = false;
			cvar.m_Wheel_up = true;
		}
		break;
	default: break;
	}

	return CallWindowProc(g_pGlobals.WndProcBackup, hwnd, uMsg, wParam, lParam);
}

std::string GetPressedNumKeyString()
{
	static bool press = false;
	static std::string out;
	static int iOut;

	static const int HexArr[10] = {
		0x60,
		0x61,
		0x62,
		0x63,
		0x64,
		0x65,
		0x66,
		0x67,
		0x68,
		0x69
	};

	static const char CharArr[][10] = {
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9"
	};

	for (int i = 0; i < _countof(HexArr); i++)
	{
		if (g_Menu.keys[HexArr[i]] == true)
		{
			out		= CharArr[i];
			iOut	= HexArr[i];
		}
	}

	if (!press && g_Menu.keys[iOut] == true)
	{
		press = true;
		return out;
	}
	else if (g_Menu.keys[iOut] == false)
	{
		press	= false;
		out		= std::string();
		iOut	= NULL;
	}

	return std::string();
}

std::string GetPressedKeyString()
{
	static bool press = false;
	static std::string out;
	static int iOut;

	static const int HexArr[34] = {
		0x41,
		0x42,
		0x43,
		0x44,
		0x45,
		0x46,
		0x47,
		0x48,
		0x49,
		0x4A,
		0x4B,
		0x4C,
		0x4D,
		0x4E,
		0x4F,
		0x50,
		0x51,
		0x52,
		0x53,
		0x54,
		0x55,
		0x56,
		0x57,
		0x58,
		0x59,
		0x5A,	// A-Z ends here
		0x6A,	// *
		0x6B,	// +
		0x6D,	// -
		0x6E,	// ,
		0x6F,	// / <- divide
		0xBF,	// /
		0xDC,
		0x20
	};

	static const char CharArr[][34] = {
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"*",
		"+",
		"-",
		".",
		"/",
		"/",
		" ", // idk
		" "
	};

	for (int i = 0; i < _countof(HexArr); i++)
	{
		if (g_Menu.keys[HexArr[i]] == true)
		{
			out		= CharArr[i];
			iOut	= HexArr[i];
		}
	}

	if (!press && g_Menu.keys[iOut] == true)
	{
		press = true;
		return out;
	}
	else if (g_Menu.keys[iOut] == false)
	{
		press	= false;
		out		= std::string();
		iOut	= NULL;
	}

	return std::string();
}

std::string base64_encode(const std::string &in)
{
	std::string out;

	int val = 0, valb = -6;
	for (unsigned char c : in) {
		val = (val << 8) + c;
		valb += 8;
		while (valb >= 0) {
			out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(val >> valb) & 0x3F]);
			valb -= 6;
		}
	}
	if (valb>-6) out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[((val << 8) >> (valb + 8)) & 0x3F]);
	while (out.size() % 4) out.push_back('=');
	return out;
}

static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

static inline bool is_base64(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_decode(std::string const& encoded_string) {
	int in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string ret;

	while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
		char_array_4[i++] = encoded_string[in_]; in_++;
		if (i == 4) {
			for (i = 0; i <4; i++)
				char_array_4[i] = base64_chars.find(char_array_4[i]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += char_array_3[i];
			i = 0;
		}
	}

	if (i) {
		for (j = i; j <4; j++)
			char_array_4[j] = 0;

		for (j = 0; j <4; j++)
			char_array_4[j] = base64_chars.find(char_array_4[j]);

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
	}

	return ret;
}

std::string StringToHex(const std::string input)
{
	const char* lut = "0123456789ABCDEF";
	size_t len = input.length();
	std::string output = "";

	output.reserve(2 * len);

	for (size_t i = 0; i < len; i++)
	{
		const unsigned char c = input[i];
		output.push_back(lut[c >> 4]);
		output.push_back(lut[c & 15]);
	}

	return output;
}

static UINT64 get_cpuid(void)
{
	DWORD dwStandard = 0;
	DWORD dwFeature = 0;

	_asm {
		mov eax, 1
		cpuid
		mov dwStandard, eax
		mov dwFeature, edx
	}
	return(((UINT64)(dwFeature) << 32) | ((UINT64)(dwStandard)));
}

static CHAR *GetHWID()
{
	HW_PROFILE_INFO hwProfileInfo;
	if (GetCurrentHwProfile(&hwProfileInfo))
		return hwProfileInfo.szHwProfileGuid;
}

void SaveLicense()
{
	char buffer[100];
	std::ofstream f(g_Utils.szDirFile(HACK_LICENSE), std::ios::out | std::ios::binary);
	f.write(std::to_string(get_cpuid()).c_str(), 100);
}

std::string encryptDecrypt(std::string toEncrypt)
{
	char key[] = { 'c', 'x', 'a', 'y', 'm', 'o', 'r', 'e' }; // Any chars will work

	std::string output = toEncrypt;

	for (int i = 0; i < toEncrypt.size(); i++)
		output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];

	return output;
}

bool isInCharString(char* str1, char* search)
{
	const char* mov_eax_offset_search = encryptDecrypt(search).c_str();
	for (int i = 0; i < strlen(str1); ++i)
	{
		if (strncmp(&str1[i], mov_eax_offset_search, strlen(mov_eax_offset_search)) == 0)
			return true;
	}

	return false;
}

int getHeaderLength(char* content)
{
	const char* srchStr1 = "\r\n\r\n", * srchStr2 = "\n\r\n\r";
	char* findPos;
	int ofset = -1;

	findPos = strstr(content, srchStr1);
	if (findPos != NULL)
	{
		ofset = findPos - content;
		ofset += strlen(srchStr1);
	}

	else
	{
		findPos = strstr(content, srchStr2);
		if (findPos != NULL)
		{
			ofset = findPos - content;
			ofset += strlen(srchStr2);
		}
	}
	return ofset;
}

char* Sys_GetLongPathName(void)
{
	char szShortPath[MAX_PATH];
	static char szLongPath[MAX_PATH];
	char* pszPath;

	szShortPath[0] = 0;
	szLongPath[0] = 0;

	if (GetModuleFileName(NULL, szShortPath, sizeof(szShortPath)))
	{
		GetLongPathName(szShortPath, szLongPath, sizeof(szLongPath));
		pszPath = strrchr(szLongPath, '\\');

		if (pszPath[0])
			pszPath[1] = 0;

		size_t len = strlen(szLongPath);

		if (len > 0)
		{
			if (szLongPath[len - 1] == '\\' || szLongPath[len - 1] == '/')
				szLongPath[len - 1] = 0;
		}
	}

	return szLongPath;
}

DWORD WINAPI Hook(LPVOID lpThreadParameter)
{
	CreateInterfaceFn gameui_factory		= CaptureFactory("gameui.dll");
	CreateInterfaceFn vgui2_factory			= CaptureFactory("vgui2.dll");
	CreateInterfaceFn hardware_factory		= CaptureFactory("hw.dll");
	CreateInterfaceFn client_factory		= CaptureFactory("client.dll");
	CreateInterfaceFn filesystem_factory	= CaptureFactory("FileSystem_Stdio.dll");
	CreateInterfaceFn steam_factory			= CaptureFactory("steamclient.dll");

	if (gameui_factory && vgui2_factory && hardware_factory && client_factory && filesystem_factory && steam_factory)
	{
		VIRTUALIZER_START
		while (!g_Offsets.FindHardware())
			Sleep(100);

		g_pFileSystem = (IFileSystem*)(CaptureInterface(filesystem_factory, FILESYSTEM_INTERFACE_VERSION));
		g_pFileSystem->Mount();
		g_pFileSystem->AddSearchPath(Sys_GetLongPathName(), "ROOT");

		g_pIVGuiModuleLoader			= (IVGuiModuleLoader*)	(CaptureInterface(gameui_factory,		VGUIMODULELOADER_INTERFACE_VERSION));
		g_pIRunGameEngine				= (IRunGameEngine*)		(CaptureInterface(gameui_factory,		RUNGAMEENGINE_INTERFACE_VERSION));
		g_pGameUI						= (IGameUI*)			(CaptureInterface(gameui_factory,		GAMEUI_INTERFACE_VERSION));
		g_pConsole						= (IGameConsole*)		(CaptureInterface(gameui_factory,		GAMECONSOLE_INTERFACE_VERSION));
		g_pIPanel						= (vgui::IPanel*)		(CaptureInterface(vgui2_factory,		VGUI_PANEL_INTERFACE_VERSION));
		g_pISurface						= (vgui::ISurface*)		(CaptureInterface(hardware_factory,		VGUI_SURFACE_INTERFACE_VERSION));
		g_pIEngineVGui					= (vgui::IEngineVGui*)	(CaptureInterface(hardware_factory,		VENGINE_VGUI_VERSION));
		g_SteamInterface.steamclient	= (ISteamClient017*)	(CaptureInterface(steam_factory,		STEAM_CLIENT_VERSION));
		
		HSteamPipe hNewPipe				= g_SteamInterface.steamclient->CreateSteamPipe();
		HSteamUser hNewUser				= g_SteamInterface.steamclient->ConnectToGlobalUser(hNewPipe);

		g_SteamInterface.steamfriends	= reinterpret_cast<ISteamFriends015*>			(g_SteamInterface.steamclient->GetISteamFriends		(hNewUser, hNewPipe,	STEAMFRIENDS_INTERFACE_VERSION_015));
		g_SteamInterface.steamuser		= reinterpret_cast<ISteamUser017*>				(g_SteamInterface.steamclient->GetISteamUser		(hNewUser, hNewPipe,	STEAMUSER_INTERFACE_VERSION_017));
		g_SteamInterface.steamuserStats = reinterpret_cast<ISteamUserStats011*>			(g_SteamInterface.steamclient->GetISteamUserStats	(hNewUser, hNewPipe,	STEAMUSERSTATS_INTERFACE_VERSION_011));
		g_SteamInterface.steamutils		= reinterpret_cast<ISteamUtils007*>				(g_SteamInterface.steamclient->GetISteamUtils		(hNewUser,				STEAMUTILS_INTERFACE_VERSION_007));

		g_pClient						= (cl_clientfunc_t*)		g_Offsets.FindClient();
		g_pEngine						= (cl_enginefunc_t*)		g_Offsets.FindEngine();
		g_pStudio						= (engine_studio_api_t*)	g_Offsets.FindStudio();
		g_pStudioModelRenderer			= (StudioModelRenderer_t*)	g_Offsets.FindStudioModelRenderer();
		
		while (!g_Client.V_CalcRefdef)
			RtlCopyMemory(&g_Client, g_pClient, sizeof(cl_clientfunc_t));

		while (!g_Engine.V_CalcShake)
			RtlCopyMemory(&g_Engine, g_pEngine, sizeof(cl_enginefunc_t));

		while (!g_Studio.StudioSetupSkin)
			RtlCopyMemory(&g_Studio, g_pStudio, sizeof(engine_studio_api_t));

		while (!g_StudioModelRenderer.StudioSlerpBones)
			RtlCopyMemory(&g_StudioModelRenderer, g_pStudioModelRenderer, sizeof(StudioModelRenderer_t));

		while (!pmove)
			pmove = (playermove_t*)g_Offsets.FindPlayerMove();

		while (!pUserMsgBase)
			pUserMsgBase = g_Offsets.FindUserMsgBase();

		g_Drawing.SetupFonts();

		if (PanelHook.HookTable((DWORD)g_pIPanel))
		{
			PanelHook.HookIndex(41, PaintTraversePanel);
		}

		g_NoFlash.pScreenFade = *(screenfade_t**)((DWORD)g_Engine.pfnSetScreenFade + 0x17);

		if (IsBadReadPtr(g_NoFlash.pScreenFade, sizeof(screenfade_t)))
			g_NoFlash.pScreenFade = *(screenfade_t**)((DWORD)g_Engine.pfnSetScreenFade + 0x18);

		g_Offsets.GlobalTime();

		g_Offsets.dwSpeedPointer = (DWORD)g_Offsets.FindSpeed();

		while (!g_pGlobals.hWindow)
		{
			if (!(g_pGlobals.hWindow = FindWindowA("Valve001", NULL)))
				g_pGlobals.hWindow = FindWindowA(NULL, "Counter-Strike");

			Sleep(200);
		}

		lstrcpyA(g_pGlobals.IniPath, g_Utils.szDirFile(HACK_FILE));

		g_pGlobals.WndProcBackup = (WNDPROC)SetWindowLongA(g_pGlobals.hWindow, GWL_WNDPROC, (LONG_PTR)&Hooked_WndProc);

		HookClient();

		VIRTUALIZER_END
	}

	return NULL;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpReserved)
{
	BOOL bReturnValue = TRUE;

	if (dwReason == DLL_QUERY_HMODULE)
	{
		if (lpReserved != NULL)
			*(HMODULE *)lpReserved = hAppInstance;
	}
	else if (dwReason == DLL_PROCESS_ATTACH)
	{
		hAppInstance = hinstDLL;

		DisableThreadLibraryCalls(hinstDLL);

		if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, g_pGlobals.BaseDir)))
		{
			GetModuleFileNameA(NULL, g_pGlobals.GamePath, MAX_PATH);

			char* pos = g_pGlobals.GamePath + strlen(g_pGlobals.GamePath);
			while (pos >= g_pGlobals.GamePath && *pos != '\\') --pos; pos[1] = 0;

			pos = g_pGlobals.BaseDir + strlen(g_pGlobals.BaseDir);
			while (pos >= g_pGlobals.BaseDir && *pos != '\\') --pos; pos[1] = 0;

			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Hook, NULL, NULL, NULL);
		}
	}

	return bReturnValue;//git test
}
