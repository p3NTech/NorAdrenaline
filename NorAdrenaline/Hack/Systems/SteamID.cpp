#include "../../Required.h"
#include "../../../MultiEmulator/MultiEmulator/Source/Emulators/RevEmu2013.h"

#pragma comment(lib, "MultiEmulator.lib")

CSteamIDChanger g_SteamID;

class ISteamUser;

using TInitiateGameConnection = int(__fastcall*)(ISteamUser * self, int, void* pData, int cbMaxData, long long steamID, int unIPServer, short usPortServer, int bSecure);
using TSteamUser = ISteamUser * (*)();

TInitiateGameConnection pfnInitiateGameConnection = nullptr;

static int newSteamID{ NULL };
static bool RandomSteamID{ false };

int __fastcall hkInitiateGameConnection(ISteamUser* self, int, void* pData, int cbMaxData, long long steamID, int unIPServer, short usPortServer, int bSecure)
{
	static int iSID;

	if (RandomSteamID)
	{
		srand(time(NULL));

		iSID = rand() % 9999999 + 1000000;
	}
	else
	{
		iSID = newSteamID;
	}
	
	return GenerateRevEmu2013(pData, iSID);

	// return pfnInitiateGameConnection(self, 0, pData, cbMaxData, steamID, unIPServer, usPortServer, bSecure);
}

bool ChangeSID()
{
	HMODULE hSteamAPI;

	while (true)
	{
		hSteamAPI = GetModuleHandleA("steam_api.dll");

		if (hSteamAPI)
			break;

		Sleep(500);
	}

	auto pfnSteamUser = (TSteamUser)GetProcAddress(hSteamAPI, "SteamUser");

	if (!pfnSteamUser)
		return FALSE;

	auto pSteamUser = pfnSteamUser();
	if (!pSteamUser)
		return FALSE;

	/* Get pointer to InitiateGameConnection method address in virtual table of ISteamUser interface. */
	auto pfn = &((void**)(*(void**)pSteamUser))[3];

	/* Save original InitiateGameConnection method code address. */
	pfnInitiateGameConnection = (TInitiateGameConnection)*pfn;

	/* Write own InitiateGameConnection function address to virtual table. */
	DWORD oldProtect;
	VirtualProtect(pfn, sizeof(void*), PAGE_READWRITE, &oldProtect);
	*pfn = hkInitiateGameConnection;
	VirtualProtect(pfn, sizeof(void*), oldProtect, NULL);

	return TRUE;
}

void CSteamIDChanger::Apply(int newSID)
{
	if (newSID == NULL)
		RandomSteamID = true;
	else
		newSteamID = newSID;

	Change();
}

void CSteamIDChanger::Change()
{
	cvar.debug ? (ChangeSID() ? g_Engine.Con_Printf("SteamID changed successfully.\n") : g_Engine.Con_Printf("Failed to change SteamID.\n")) : ChangeSID() ? EXIT_SUCCESS : EXIT_FAILURE;
}