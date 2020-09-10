struct Module
{
	DWORD base;
	DWORD size;
	DWORD end;
};

class COffsets;
class COffsets
{
private:
	DWORD dwOldPageProtection;//For EnablePageWrite & RestorePageProtection
public:
	Module hardware, client, gameui, vgui2, FileSystem_Stdio, steamclient;

	DWORD dwSendPacketPointer, dwSendPacketBackup, dwSpeedPointer;//Saved offsets

	bool FindHardware(void);//Init
	
	//Functions

	PVOID FindClient(void);
	PVOID FindEngine(void);
	PVOID FindStudio(void);
	PVOID FindPlayerMove(void);
	PVOID FindStudioModelRenderer(void);
	
	DWORD PreS_DynamicSound(void);
	DWORD Netchan_FragSend(void);
	DWORD Netchan_CreateFragments(void);
	DWORD Netchan_CreateFileFragments(void);
	DWORD Netchan_TransmitBits(void);
	DWORD CL_Move(void);
	DWORD FindSpeed(void);
	DWORD NET_SendPacket(void);

	void GlobalTime();

	void Error(PCHAR msg, bool terminate);

	void PatchInterpolation(void);
	void Call_CL_ProcessFile(void);

	UserMsg FindUserMsgBase(void);

	//Utils

	bool FindModuleByName(const char *moduleName, Module *module);
	bool RestorePageProtection(DWORD addr, DWORD size);
	bool EnablePageWrite(DWORD addr, DWORD size);

	DWORD FindPattern(PCHAR pattern, PCHAR mask, DWORD start, DWORD end, DWORD offset);
	DWORD FindPattern(PCHAR pattern, DWORD start, DWORD end, DWORD offset);
	DWORD FindReference(DWORD start, DWORD end, DWORD Address);
	DWORD FindPush(DWORD start, DWORD end, PCHAR Message);
	DWORD GetModuleSize(DWORD Address);
	DWORD FarProc(DWORD Address, DWORD LB, DWORD HB);
	DWORD Absolute(DWORD Address);



};
extern COffsets g_Offsets;