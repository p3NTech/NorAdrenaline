#include "ValveSDK\common\interface.h"
#include "ValveSDK\common\wrect.h"
#include "ValveSDK\common\cl_dll.h"
#include "ValveSDK\engine\cdll_int.h"
#include "ValveSDK\common\r_studioint.h"
#include "ValveSDK\common\com_model.h"
#include "ValveSDK\common\cl_entity.h"
#include "ValveSDK\common\ref_params.h"
#include "ValveSDK\pm_shared\pm_defs.h"
#include "ValveSDK\pm_shared\pm_movevars.h"
#include "ValveSDK\engine\studio.h"
#include "ValveSDK\parsemsg.h"
#include "ValveSDK\common\cvardef.h"
#include "ValveSDK\common\triangleapi.h"
#include "ValveSDK\common\pmtrace.h"
#include "ValveSDK\common\event_api.h"
#include "ValveSDK\common\r_efx.h"
#include "ValveSDK\common\entity_types.h"
#include "ValveSDK\common\screenfade.h"
#include "ValveSDK\common\net_api.h"

#include "ValveSDK\VGUI\VGUI_Frame.h"
#include "ValveSDK\VGUI\VGUI_Panel.h"
#include "ValveSDK\GameUI\IVGuiModuleLoader.h"
#include "ValveSDK\GameUI\IRunGameEngine.h"
#include "ValveSDK\GameUI\IGameUI.h"
#include "ValveSDK\GameUI\IGameConsole.h"
#include "ValveSDK\VGUI2\IHTML.h"
#include "ValveSDK\VGUI2\IPanel.h"
#include "ValveSDK\VGUI2\ISurface.h"
#include "ValveSDK\VGUI2\IEngineVGui.h"

#include "../include/steam/SteamTypes.h"
#include "../include/steam/Steamworks.h"

#include <gl\GL.h>

#pragma comment(lib, "OpenGL32.lib")
//#pragma comment(lib, "vgui.lib")

//using namespace std;

typedef float TransformMatrix[MAXSTUDIOBONES][3][4];

#define VectorTransform(a,b,c){(c)[0]=a.Dot((b)[0])+(b)[0][3];(c)[1]=a.Dot((b)[1])+(b)[1][3];(c)[2]=a.Dot((b)[2])+(b)[2][3];}
#define VectorMul(vec,num,res){(res)[0]=(vec)[0]*(num);(res)[1]=(vec)[1]*(num);(res)[2]=(vec)[2]*(num);}

#define DEFAULT_FOV	90	// the default field of view

#define PM_DEAD_VIEWHEIGHT	-8

#define PM_VEC_DUCK_VIEW			12
#define PM_VEC_VIEW	17

#define OBS_NONE				0
#define OBS_CHASE_LOCKED		1
#define OBS_CHASE_FREE			2
#define OBS_ROAMING				3
#define OBS_IN_EYE				4
#define OBS_MAP_FREE			5
#define OBS_MAP_CHASE			6

#define BOMB_FLAG_DROPPED	0 // if the bomb was dropped due to voluntary dropping or death/disconnect
#define BOMB_FLAG_PLANTED	1 // if the bomb has been planted will also trigger the round timer to hide will also show where the dropped bomb on the Terrorist team's radar.

#define NUMBLOOPS 50.0f
#define TIMEALIVE 3.00f
#define OLDDAMPER 1.75f 
#define NEWDAMPER 0.75f
#define SVGRAVITY 3.75f
#define FLOORSTOP 0.20f

#define ARMOR_RATIO			0.5	// Armor Takes 50% of the damage
#define ARMOR_BONUS	0.5	// Each Point of Armor is work 1/x points of health

#define MAX_BOMB_RADIUS	2048

#define M_PI_F	((float)(M_PI)) // Shouldn't collide with anything.
#define PI 3.14159265358979323846f
#define RAD2DEG( x )  ( (float)(x) * (float)(180.f / M_PI_F) )
#define DEG2RAD( x ) ( (float)(x) * (float)(M_PI_F / 180.f) )

#ifndef DEG2RAD_EX
#define DEG2RAD_EX(x) (float) (x) * (PI / 180.0f)
#endif

// player data iuser3
#define PLAYER_CAN_SHOOT		(1<<0)
#define PLAYER_FREEZE_TIME_OVER		(1<<1)
#define PLAYER_IN_BOMB_ZONE		(1<<2)
#define PLAYER_HOLDING_SHIELD		(1<<3)

#define MAX_PLAYER_NAME_LENGTH	32

#define RED(COLORCODE) ((int)(COLORCODE >> 24))
#define BLUE(COLORCODE) ((int)(COLORCODE >> 8) & 0xFF)
#define GREEN(COLORCODE) ((int)(COLORCODE >> 16) & 0xFF)
#define ALPHA(COLORCODE) ((int)COLORCODE & 0xFF)
#define COLORCODE(r, g, b, a) ((DWORD) ((((r)&0xff) << 24) | (((g)&0xff) << 16) | (((b)&0xff) << 8) | ((a)&0xff)))

#define FOOT_ORIGIN(Entity) (Vector(Entity->origin[0], Entity->origin[1], Entity->origin[2] -= ((Entity->curstate.maxs[2] - Entity->curstate.mins[2]) < 54 ? 18.0f : 36.0f)))
#define ENTITY(Indx) (g_Engine.GetEntityByIndex(Indx))
#define IS_VALID(Indx) (ENTITY(Indx) && ENTITY(Indx)->player)
#define TIME_TO_TICKS(dt) ((int)(0.5f + (float)(dt) / pmove->frametime))

struct CImageTexture
{
	unsigned int index;
	unsigned int width;
	unsigned int height;
};

enum FontRenderFlag_t
{
	FONT_LEFT = 0,
	FONT_RIGHT = 1,
	FONT_CENTER = 2
};

enum EFontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
};

enum ArmorType
{
	ARMOR_NONE,	// no armor
	ARMOR_KEVLAR,	// body vest only
	ARMOR_VESTHELM,	// vest and helmet
};

enum CursorCode
{
	dc_user,
	dc_none,
	dc_arrow,
	dc_ibeam,
	dc_hourglass,
	dc_waitarrow,
	dc_crosshair,
	dc_up,
	dc_sizenwse,
	dc_sizenesw,
	dc_sizewe,
	dc_sizens,
	dc_sizeall,
	dc_no,
	dc_hand,
	dc_blank, // don't show any custom vgui cursor, just let windows do it stuff (for HTML widget)
	dc_last,
};

enum
{
	SEQUENCE_IDLE = 0,
	SEQUENCE_SHOOT = 1,
	SEQUENCE_RELOAD = 2,
	SEQUENCE_DIE = 4,
	SEQUENCE_THROW = 8,
	SEQUENCE_ARM_C4 = 16,
	SEQUENCE_SHIELD = 32,
	SEQUENCE_SHIELD_SIDE = 64
};

enum TeamName
{
	UNASSIGNED,
	TERRORIST,
	CT,
	SPECTATOR,
};

class CBomb
{
public:
	Vector vOrigin;
	int iFlag;
};

typedef void(*xcommand_t)(void);
typedef struct cmd_s
{
	struct cmd_s *next;
	const char *name;
	xcommand_t function;
	int flags;
} cmd_t, *pcmd_t;

typedef struct _UserMsg
{
	int iMsg;
	int iSize;
	char szName[16];
	struct _UserMsg* next;
	pfnUserMsgHook pfn;
} *UserMsg;

typedef struct
{
	Vector origin;

	char *name;

	DWORD timestamp;

	int id;
} my_sound_t;

struct CBasePlayerWeapon
{
	bool m_bDelayFire;
	unsigned int random_seed;
	int m_iWeaponState;
	int m_iFlags;
	int m_iClip;
	int m_iWeaponID;
	int m_iInReload;
	int iPenetration;
	int iBulletType;
	int iDamage1;
	int iDamage2;
	int m_iShotsFired;
	int iuser3;
	float prevtime;
	float curtime;
	float m_flDecreaseShotsFired;
	float m_flAccuracy;
	float m_flSpread;
	float m_flNextPrimaryAttack;
	float m_flNextSecondaryAttack;
	float m_flNextAttack;
	float flPenetrationDistance;
	float flWallPierce1;
	float flWallPierce2;
};

struct info_map_parameters
{
	const char *levelname;

	float m_flBombRadius;
};

struct player_extra_info_t
{
	char *szWeaponName;

	Vector vHitbox[21];
	Vector vHitboxMin[21];
	Vector vHitboxMax[21];
	Vector vHitboxPoints[21][8];

	Vector vBones[53];

	bool bHitboxVisible[21];
	bool bHitboxPointsVisible[21][8];
	bool bHitboxBehindTheWall[21];
	bool bHitboxPointsBehindTheWall[21][8];

	float fHitboxFOV[21];
};

typedef struct cl_clientfuncs_s
{
	int(*Initialize) (cl_enginefunc_t *pEnginefuncs, int iVersion);
	int(*HUD_Init) (void);
	int(*HUD_VidInit) (void);
	void(*HUD_Redraw) (float time, int intermission);
	int(*HUD_UpdateClientData) (client_data_t *pcldata, float flTime);
	int(*HUD_Reset) (void);
	void(*HUD_PlayerMove) (struct playermove_s *ppmove, int server);
	void(*HUD_PlayerMoveInit) (struct playermove_s *ppmove);
	char(*HUD_PlayerMoveTexture) (char *name);
	void(*IN_ActivateMouse) (void);
	void(*IN_DeactivateMouse) (void);
	void(*IN_MouseEvent) (int mstate);
	void(*IN_ClearStates) (void);
	void(*IN_Accumulate) (void);
	void(*CL_CreateMove) (float frametime, struct usercmd_s *cmd, int active);
	int(*CL_IsThirdPerson) (void);
	void(*CL_CameraOffset) (float *ofs);
	struct kbutton_s *(*KB_Find) (const char *name);
	void(*CAM_Think) (void);
	void(*V_CalcRefdef) (struct ref_params_s *pparams);
	int(*HUD_AddEntity) (int type, struct cl_entity_s *ent, const char *modelname);
	void(*HUD_CreateEntities) (void);
	void(*HUD_DrawNormalTriangles) (void);
	void(*HUD_DrawTransparentTriangles) (void);
	void(*HUD_StudioEvent) (const struct mstudioevent_s *event, const struct cl_entity_s *entity);
	void(*HUD_PostRunCmd) (struct local_state_s *from, struct local_state_s *to, struct usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed);
	void(*HUD_Shutdown) (void);
	void(*HUD_TxferLocalOverrides) (struct entity_state_s *state, const struct clientdata_s *client);
	void(*HUD_ProcessPlayerState) (struct entity_state_s *dst, const struct entity_state_s *src);
	void(*HUD_TxferPredictionData) (struct entity_state_s *ps, const struct entity_state_s *pps, struct clientdata_s *pcd, const struct clientdata_s *ppcd, struct weapon_data_s *wd, const struct weapon_data_s *pwd);
	void(*Demo_ReadBuffer) (int size, unsigned char *buffer);
	int(*HUD_ConnectionlessPacket) (struct netadr_s *net_from, const char *args, char *response_buffer, int *response_buffer_size);
	int(*HUD_GetHullBounds) (int hullnumber, float *mins, float *maxs);
	void(*HUD_Frame) (double time);
	int(*HUD_Key_Event) (int down, int keynum, const char *pszCurrentBinding);
	void(*HUD_TempEntUpdate) (double frametime, double client_time, double cl_gravity, struct tempent_s **ppTempEntFree, struct tempent_s **ppTempEntActive, int(*Callback_AddVisibleEntity)(struct cl_entity_s *pEntity), void(*Callback_TempEntPlaySound)(struct tempent_s *pTemp, float damp));
	struct cl_entity_s *(*HUD_GetUserEntity) (int index);
	int(*HUD_VoiceStatus) (int entindex, qboolean bTalking);
	int(*HUD_DirectorMessage) (unsigned char command, unsigned int firstObject, unsigned int secondObject, unsigned int flags);
	int(*HUD_GetStudioModelInterface) (int version, struct r_studio_interface_s **ppinterface, struct engine_studio_api_s *pstudio);
	void(*HUD_CHATINPUTPOSITION_FUNCTION) (int *x, int *y);
	void(*CLIENTFACTORY) (void);
	int(*HUD_GETPLAYERTEAM_FUNCTION) (int iplayer);
} cl_clientfunc_t;

#ifndef IFILESYSTEM_H
#define IFILESYSTEM_H

#ifdef _WIN32
#pragma once
#endif

typedef void* FileHandle_t;
typedef int FileFindHandle_t;
typedef int WaitForResourcesHandle_t;

enum FileSystemSeek_t
{
	FILESYSTEM_SEEK_HEAD = 0,
	FILESYSTEM_SEEK_CURRENT,
	FILESYSTEM_SEEK_TAIL,
};

enum
{
	FILESYSTEM_INVALID_FIND_HANDLE = -1
};

enum FileWarningLevel_t
{
	FILESYSTEM_WARNING = -1,
	FILESYSTEM_WARNING_QUIET = 0,
	FILESYSTEM_WARNING_REPORTUNCLOSED,
	FILESYSTEM_WARNING_REPORTUSAGE,
	FILESYSTEM_WARNING_REPORTALLACCESSES,
	FILESYSTEM_WARNING_REPORTALLACCESSES_READ,
	FILESYSTEM_WARNING_REPORTALLACCESSES_READWRITE,
	FILESYSTEM_WARNING_REPORTALLACCESSES_ASYNC,
};

#define FILESYSTEM_INVALID_HANDLE (FileHandle_t)NULL

class IFileSystem : public IBaseInterface
{
public:
	virtual void Mount(void) = 0;
	virtual void Unmount(void) = 0;
	virtual void RemoveAllSearchPaths(void) = 0;
	virtual void AddSearchPath(const char* pPath, const char* pathID = 0) = 0;
	virtual bool RemoveSearchPath(const char* pPath) = 0;
	virtual void RemoveFile(const char* pRelativePath, const char* pathID = 0) = 0;
	virtual void CreateDirHierarchy(const char* path, const char* pathID = 0) = 0;
	virtual bool FileExists(const char* pFileName) = 0;
	virtual bool IsDirectory(const char* pFileName) = 0;
	virtual FileHandle_t Open(const char* pFileName, const char* pOptions, const char* pathID = 0) = 0;
	virtual void Close(FileHandle_t file) = 0;
	virtual void Seek(FileHandle_t file, int pos, FileSystemSeek_t seekType) = 0;
	virtual unsigned Tell(FileHandle_t file) = 0;
	virtual unsigned Size(FileHandle_t file) = 0;
	virtual unsigned Size(const char* pFileName) = 0;
	virtual long GetFileTime(const char* pFileName) = 0;
	virtual void FileTimeToString(char* pStrip, int maxCharsIncludingTerminator, long fileTime) = 0;
	virtual bool IsOk(FileHandle_t file) = 0;
	virtual void Flush(FileHandle_t file) = 0;
	virtual bool EndOfFile(FileHandle_t file) = 0;
	virtual int Read(void* pOutput, int size, FileHandle_t file) = 0;
	virtual int Write(void const* pInput, int size, FileHandle_t file) = 0;
	virtual char* ReadLine(char* pOutput, int maxChars, FileHandle_t file) = 0;
	virtual int FPrintf(FileHandle_t file, char* pFormat, ...) = 0;
	virtual char* GetReadBuffer(FileHandle_t file, char* pBuffer) = 0;
	virtual void ReleaseReadBuffer(FileHandle_t file, char* pBuffer) = 0;
	virtual const char* FindFirst(const char* pWildCard, FileFindHandle_t* pHandle, const char* pathID = 0) = 0;
	virtual const char* FindNext(FileFindHandle_t handle) = 0;
	virtual bool FindIsDirectory(FileFindHandle_t handle) = 0;
	virtual void FindClose(FileFindHandle_t handle) = 0;
	virtual void GetLocalCopy(const char* pFileName) = 0;
	virtual const char* GetLocalPath(const char* pFileName, char* pLocalPath, int maxlen) = 0;
	virtual char* ParseFile(char* data, char* token, bool* wasquoted) = 0;
	virtual bool FullPathToRelativePath(const char* pFullpath, char* pRelative) = 0;
	virtual bool GetCurrentDirectory(char* pDirectory, int maxlen) = 0;
	virtual void PrintOpenedFiles(void) = 0;
	virtual void SetWarningFunc(void (*pfnWarning)(const char* fmt, ...)) = 0;
	virtual void SetWarningLevel(FileWarningLevel_t level) = 0;
	virtual void LogLevelLoadStarted(const char* name) = 0;
	virtual void LogLevelLoadFinished(const char* name) = 0;
	virtual int HintResourceNeed(const char* hintlist, int forgetEverything) = 0;
	virtual int PauseResourcePreloading(void) = 0;
	virtual int ResumeResourcePreloading(void) = 0;
	virtual int SetVBuf(FileHandle_t stream, char* buffer, int mode, long size) = 0;
	virtual void GetInterfaceVersion(char* p, int maxlen) = 0;
	virtual bool IsFileImmediatelyAvailable(const char* path) = 0;
	virtual void* WaitForResources(const char* pFileName) = 0;
	virtual bool GetWaitForResourcesProgress(WaitForResourcesHandle_t handle, float* progress, bool* complete) = 0;
	virtual void CancelWaitForResources(WaitForResourcesHandle_t handle) = 0;
	virtual bool IsAppReadyForOfflinePlay(void) = 0;
	virtual void AddPackFile(const char* pPath, const char* pathID = 0) = 0;
	virtual void* OpenFromCacheForRead(const char* pFileName, const char* pOptions, const char* pathID = 0) = 0;
};
extern IFileSystem* g_pFileSystem;
#define FILESYSTEM_INTERFACE_VERSION "VFileSystem009"

#endif

class ISteamInterface
{
public:
	ISteamClient017*	steamclient		= nullptr;
	ISteamFriends015*	steamfriends	= nullptr;
	ISteamUser017*		steamuser		= nullptr;
	ISteamUserStats011* steamuserStats	= nullptr;
	ISteamUtils007*		steamutils		= nullptr;
};
extern ISteamInterface g_SteamInterface;
#define STEAM_CLIENT_VERSION "SteamClient017"

#define BIT(n) (1<<(n))

template< class T, class Y >
T Clamp2(T const &val, Y const &minVal, Y const &maxVal)
{
	if (val < minVal)
		return minVal;
	if (val > maxVal)
		return maxVal;
	return val;
}

inline void AngleNormalize(float& angle)
{
	while (angle > 180.f)
		angle -= 360.f;
	while (angle < -180.f)
		angle += 360.f;
}

inline float AngleNormalize(float angle)
{
	while (angle > 180.f)
		angle -= 360.f;
	while (angle < -180.f)
		angle += 360.f;
	return angle;
}

inline void AngleNormalize(Vector& angles)
{
	for (int i = 0; i < 3; i++)
	{
		while (angles[i] > 180.f)
			angles[i] -= 360.f;
		while (angles[i] < -180.f)
			angles[i] += 360.f;
	}

	if (angles[1] == -180.f) angles[1] = 180.f;
	angles.z = 0.f;
}

inline std::string format(const std::string fmt_str, ...)
{
	int final_n, n = ((int)fmt_str.size()) * 2;
	std::unique_ptr<char[]> formatted;
	va_list ap;
	while (1)
	{
		formatted.reset(new char[n]);
		strcpy(&formatted[0], fmt_str.c_str());
		va_start(ap, fmt_str);
		final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
		va_end(ap);
		if (final_n < 0 || final_n >= n)
			n += abs(final_n - n + 1);
		else
			break;
	}
	return std::string(formatted.get());
}

inline std::vector<std::string> split_string(const std::string& str, const std::string& delimiter)
{
	std::vector<std::string> strings;

	std::string::size_type pos = 0;
	std::string::size_type prev = 0;
	while ((pos = str.find(delimiter, prev)) != std::string::npos)
	{
		strings.push_back(str.substr(prev, pos - prev));
		prev = pos + 1;
	}
	strings.push_back(str.substr(prev));

	return strings;
}

typedef struct dataFragments_s
{
	FileHandle_t	file;			// open file handle
	char			filename[MAX_PATH]; // filename
	char* buffer;			// if NULL it's a file
	unsigned int	bytes;			// size in bytes
	unsigned int	bits;			// size in bits
	unsigned int	transferID;		// only for files
	bool			isCompressed;	// true if data is bzip compressed
	unsigned int	nUncompressedSize; // full size in bytes
	bool			asTCP;			// send as TCP stream
	bool            isDemo;         // is demo?
	int				numFragments;	// number of total fragments
	int				ackedFragments; // number of fragments send & acknowledged
	int				pendingFragments; // number of fragments send, but not acknowledged yet
} dataFragments_t;

class CStore
{
public:
	int g_iUser1;
	int g_iUser2;
	int g_iUser3;

	int g_iDestUser1;
	int g_iDestUser2;
	int g_iDestUser3;

	int g_iDestNumber;
};
extern CStore g_Store;