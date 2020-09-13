#include <SDKDDKVer.h>
#include <windows.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "Wininet.h"
#include <comdef.h>
#include <Wbemidl.h>
#include <shellapi.h>
#include <sstream>
#include <algorithm>
#include <functional>
#include <thread>
#include <atomic>
#include <queue>
#include <array>
#include <string>
#include <iterator>
#include <list>

#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib,"Wininet.lib")

#define M_PI 3.14159265358979323846
#ifndef POW
#define POW(x) ((x)*(x))
#endif
#include "Vector.h"
#include "QAngle.h"
#define vec3_t Vector

#include "Structures.h"
#include "Offsets.h"
#include "Hook.h"
#include "detours.h"
#include "StudioModelRenderer.h"
#include "Color.h"
#include "Init.h"
#include "Timer.h"
#include "netchan.h"

#include "Hack\Hack.h"
#include "Usermsg.h"

#define VIRTUALIZER_START \
  __asm _emit 0xEB \
  __asm _emit 0x10 \
  __asm _emit 0x43\
  __asm _emit 0x56\
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x0C \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x43\
  __asm _emit 0x56\
  __asm _emit 0x20 \
  __asm _emit 0x20 \

#define VIRTUALIZER_END \
  __asm _emit 0xEB \
  __asm _emit 0x10 \
  __asm _emit 0x43\
  __asm _emit 0x56\
  __asm _emit 0x20 \
  __asm _emit 0x20 \
  __asm _emit 0x0D \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x00 \
  __asm _emit 0x43\
  __asm _emit 0x56\
  __asm _emit 0x20 \
  __asm _emit 0x20 \

#define A 12312
#define B 23423
#define C 34534
#define FIRSTH 37
#define FIRSTH 37

typedef void(*Snapshot_t)                       ();
typedef void(*Screenshot_t)                     ();
typedef void(*PreS_DynamicSound_t)              (int, DWORD, char *, float *, float, float, int, int);
typedef void(*CL_Move_t)                        ();
typedef void(*Netchan_FragSend_t)               (netchan_t *);
typedef void(*Netchan_TransmitBits_t)           (netchan_t *, int, byte *);
typedef void(*Netchan_CreateFragments__t)       (qboolean, netchan_t *, sizebuf_t *);
typedef int (*Netchan_CreateFileFragments_t)    (qboolean, netchan_t *, const char *);

extern cl_clientfunc_t                  *g_pClient;
extern cl_clientfunc_t                  g_Client;
extern cl_enginefunc_t                  *g_pEngine;
extern cl_enginefunc_t                  g_Engine;
extern engine_studio_api_t              *g_pStudio;
extern engine_studio_api_t              g_Studio;
extern playermove_t                     *pmove;
extern UserMsg                          pUserMsgBase;
extern VHookTable                       PanelHook;
extern SCREENINFO                       g_Screen;
extern Snapshot_t                       Snapshot_s;
extern Screenshot_t                     Screenshot_s;
extern CL_Move_t                        CL_Move_s;
extern PreS_DynamicSound_t              PreS_DynamicSound_s;
extern StudioModelRenderer_t            g_StudioModelRenderer;
extern StudioModelRenderer_t            *g_pStudioModelRenderer;
extern Netchan_FragSend_t               Netchan_FragSend_s;
extern Netchan_TransmitBits_t           Netchan_TransmitBits_s;
extern Netchan_CreateFragments__t       Netchan_CreateFragments__s;
extern Netchan_CreateFileFragments_t    Netchan_CreateFileFragments_s;

void HookClient();
void WINAPI PaintTraversePanel(vgui::IPanel* vguiPanel, bool forceRepaint, bool allowForce);
void AntiScreen();
void HookOpenGL();

std::string StringToHex(const std::string input);

std::string GetPressedNumKeyString();
std::string GetPressedKeyString();
std::string base64_encode(const std::string &in);
std::string base64_decode(const std::string &in);
std::string encryptDecrypt(std::string toEncrypt);

static UINT64 get_cpuid(void);
static CHAR* GetHWID();
void SaveLicense();
bool isInCharString(char* str1, char* search);
int getHeaderLength(char* content);
