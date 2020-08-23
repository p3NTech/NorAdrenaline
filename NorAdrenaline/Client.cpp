#include "Required.h"
#include <list>
#include <tchar.h>
#include <intrin.h>
#include <mutex>

CGlobalsVars g_pGlobals;
SCREENINFO g_Screen;

static float ticks = 0;

//test
uint32_t lastincomingsequencenumber = 0;
typedef struct s_incoming_sequence {
	int m_nInReliableState;
	int m_nOutReliableState;
	int m_nInSequenceNr;
	int curtime;
	
	s_incoming_sequence(int m_nInReliableState, int m_nOutReliableState, int m_nInSequenceNr, int curtime) {
		this->m_nInReliableState = m_nInReliableState;
		this->m_nOutReliableState = m_nOutReliableState;
		this->curtime = curtime;
		this->m_nInSequenceNr = m_nInSequenceNr;
	}
} t_incoming_sequence;
std::list<s_incoming_sequence> sequences;
netchan_t *g_pNetchan;

void AntiSnapshot() { g_pGlobals.bSnapshot = true; }
void AntiScreenshot() { g_pGlobals.bScreenshot = true; }
void AntiScreen()
{
	if (g_pGlobals.bSnapshot || g_pGlobals.bScreenshot)
	{
		g_pGlobals.ScreenTimer--;

		if (g_pGlobals.ScreenTimer <= 0)
		{
			if (g_pGlobals.bSnapshot)
			{
				Snapshot_s();
				g_pGlobals.bSnapshot = false;
			}
			else if (g_pGlobals.bScreenshot)
			{
				Screenshot_s();
				g_pGlobals.bScreenshot = false;
			}

			g_pGlobals.ScreenTimer = 5;
		}
	}
}

void WINAPI PaintTraversePanel(vgui::IPanel* vguiPanel, bool forceRepaint, bool allowForce)
{
	PanelHook.UnHook();

	g_pIPanel->PaintTraverse(vguiPanel, forceRepaint, allowForce);

	const char* PanelName = g_pIPanel->GetName(vguiPanel);

	if (strstr(PanelName, "StaticPanel") && !cvar.hide_from_obs && g_Engine.pfnGetCvarFloat("r_norefresh") == 0)
	{
		g_Visuals.Run();
		g_Menu.Run();
		while (!g_Menu.after_menu.empty())
		{
			g_Menu.after_menu.front()();
			g_Menu.after_menu.pop_front();
		}

		g_pISurface->DrawSetTextFont(ESP);
		g_pISurface->DrawSetTextColor(0, 0, 0, 0);
		g_pISurface->DrawSetTextPos(1, 1);
		g_pISurface->DrawPrintText((wchar_t*)__func__, wcslen((wchar_t*)__func__)); // fix rendering

		g_pISurface->DrawFlushText();

		AntiScreen();
	}
	else if (strstr(PanelName, "LoadingDialog") || strstr(PanelName, "BasePanel"))
	{
		g_pGlobals.dwLoadingFinished = GetTickCount();

		/*
		static DWORD dayn = GetTickCount() + 180000;

		if (GetTickCount() - dayn > 180000)
		{
			char tmp5[] = { '/','v','/','N','U','L','L','.','p','h','p',0 };

			char tmp6[] = { 'G','R','A','N','D','E','D',0 };

			std::string respone = GetUrlData(tmp5);
			std::string decode = base64_decode(respone.c_str());

			if (lstrcmpA(decode.c_str(), tmp6))
				g_Offsets.Error((PCHAR)decode.c_str(), false);

			g_Engine.Con_Printf("ACCESS:	%s \n", (PCHAR)decode.c_str());

			dayn = GetTickCount();
		}
		*/
	}

	PanelHook.ReHook();
}

void CL_CreateMove(float frametime, struct usercmd_s *cmd, int active)
{
	g_Client.CL_CreateMove(frametime, cmd, active);

	if (g_pGlobals.bResetSpeed == true)
	{
		func.ResetSpeed();
	}

	World.Update(frametime, cmd);
	
	if (g_Local.bAlive)
	{
		UpdateWeaponData();

		static float circle_yaw = g_Local.vEye.y;

		g_Systems.KnifeBot(cmd);
		g_Systems.BunnyHop(cmd);
		g_Systems.JumpBug(frametime, cmd);
		g_Systems.FakeDuck(cmd);
		g_Systems.AirDuck(cmd);
		g_Systems.AutoStrafe(cmd);
		g_Systems.circle_strafe(&circle_yaw, cmd);
		g_Systems.Fastrun(cmd);

		g_FollowBot.CM(cmd);

		g_AimBot.Run(cmd);

		g_Misc.AutoReload(cmd);
		g_Misc.AutoPistol(cmd);
		g_Misc.FastZoom(cmd);

		ItemPostFrame(cmd);

		if (!cvar.hide_from_obs && !g_pGlobals.bSnapshot && !g_pGlobals.bScreenshot && cvar.bullets_trace && CanAttack() && cmd->buttons & IN_ATTACK)
		{
			Vector vForward;
			Vector vAngle = cmd->viewangles;
			g_Engine.pfnAngleVectors(vAngle, vForward, NULL, NULL);
			int beamindex = g_Engine.pEventAPI->EV_FindModelIndex("sprites/laserbeam.spr");
			pmtrace_t tr;
			g_Engine.pEventAPI->EV_SetTraceHull(2);
			g_Engine.pEventAPI->EV_PlayerTrace(g_Local.vEye, g_Local.vEye + vForward * 8192, PM_GLASS_IGNORE, -1, &tr);
			Vector vecEnd = g_Local.vEye + vForward * tr.fraction * 8192;


			float fScreen[2];
			bool behind, behind2;

			g_Visuals.WorldToScreen(vecEnd, fScreen, behind);

			if (behind)
			{
				fScreen[0] = g_Screen.iWidth	- fScreen[0];
				fScreen[1] = g_Screen.iHeight	- fScreen[1];
			}

			if (g_Utils.bCalcScreen(vecEnd, fScreen)) {
				g_pISurface->DrawSetColor((int)cvar.cheat_global_color_r, (int)cvar.cheat_global_color_g, (int)cvar.cheat_global_color_b, 255);
				g_pISurface->DrawFilledRect(fScreen[0] - 3, fScreen[1] - 3, fScreen[0] + 3, fScreen[1] + 3);
			}
			g_Engine.pEfxAPI->R_BeamPoints(g_Local.vEye, tr.endpos, beamindex, 0.3f, 0.4f, 0, 32, 2, 0, 0, cvar.cheat_global_color_r, cvar.cheat_global_color_g, cvar.cheat_global_color_b);
		}

		g_NoRecoil.CL_CreateMove(cmd);
		g_NoSpread.CL_CreateMove(cmd);

		g_Misc.AntiAim(cmd);
		g_Misc.FakeLag(cmd);
		g_Misc.NameStealer();
		g_Systems.AdjustSpeed();
	}

	g_Misc.Spam();

	// Update incoming sequences
	if (g_pNetchan) {
		if (g_pNetchan->incoming_sequence > lastincomingsequencenumber) {
			lastincomingsequencenumber = g_pNetchan->incoming_sequence;

			sequences.push_front(t_incoming_sequence(g_pNetchan->incoming_reliable_sequence, g_pNetchan->reliable_sequence, g_pNetchan->incoming_sequence, pmove->time));
			if (cvar.debug)
				g_Engine.Con_Printf("add: num=> %d   time=> %.2f\n", g_pNetchan->incoming_sequence, g_pNetchan->last_received);
		}

		if (sequences.size() > 2048)
			sequences.pop_back();
	}
}

void HUD_PostRunCmd(struct local_state_s *from, struct local_state_s *to, struct usercmd_s *cmd, int runfuncs, double time, unsigned int random_seed)
{
	g_Client.HUD_PostRunCmd(from, to, cmd, runfuncs, time, random_seed);

	ItemPreFrame(from, to, cmd, runfuncs, time, random_seed);
}

void V_CalcRefdef(struct ref_params_s *pparams)
{
	g_Local.vPunchangle = pparams->punchangle;
	g_Local.vForward = pparams->forward;
	g_Local.vRight = pparams->right;
	g_Local.vUp = pparams->up;

	g_NoRecoil.V_CalcRefdef(pparams);
	g_NoSpread.V_CalcRefdef(pparams);

	g_Client.V_CalcRefdef(pparams);

	g_Misc.ThirdPerson(pparams);
}

void HUD_Frame(double time)
{
	g_Engine.pfnGetScreenInfo(&g_Screen);

	g_Engine.pNetAPI->Status(&(g_Local.status));

	World.UpdateMapInfo();

	g_Visuals.Lightmap();

	g_Client.HUD_Frame(time);
}

void HUD_Frame_init(double time)
{
	g_Screen.iSize = sizeof(SCREENINFO);
	g_Engine.pfnGetScreenInfo(&g_Screen);

	g_pGlobals.ScreenTimer = 5;
	g_pGlobals.bScreenshot = false;
	g_pGlobals.bSnapshot = false;

	g_pGlobals.dwLoadingFinished = 0;

	pcmd_t pSnapshot = CommandByName("snapshot");
	pcmd_t pScreenshot = CommandByName("screenshot");

	Snapshot_s = (Snapshot_t)pSnapshot->function;
	Screenshot_s = (Snapshot_t)pScreenshot->function;

	pSnapshot->function = (xcommand_t)AntiSnapshot;
	pScreenshot->function = (xcommand_t)AntiScreenshot;

	World.Reset();
	World.ClearMapInfo();

	cvar.Init();
	func.Init();

	func.LoadCvars();

	HookOpenGL();

	if (!g_pConsole->IsConsoleVisible())
		g_pConsole->Activate();

	// Patch interpolation
	g_Offsets.PatchInterpolation();

	// Patch rates
	g_Engine.pfnClientCmd("rate 999999; cl_updaterate 1000; cl_cmdrate 1000; cl_rate 9999; ex_interp 0.1");

	g_pEngine->pfnAddCommand("+na_gs", []() {
		cvar.gstrafe = true;
	});
	g_pEngine->pfnAddCommand("-na_gs", []() {
		cvar.gstrafe = false;
	});

	g_pEngine->pfnAddCommand("+na_strafe_circle", []() {
		cvar.cstrafe_temp = true;
	});
	g_pEngine->pfnAddCommand("-na_strafe_circle", []() {
		cvar.cstrafe_temp = false;
	});

	g_pEngine->pfnAddCommand("+na_strafe", []() {
		cvar.autostrafe = true;
	});
	g_pEngine->pfnAddCommand("-na_strafe", []() {
		cvar.autostrafe = false;
	});

	g_pEngine->pfnAddCommand("+na_fastrun", []() {
		cvar.fastrun_temp = true;
	});
	g_pEngine->pfnAddCommand("-na_fastrun", []() {
		cvar.fastrun_temp = false;
	});

	g_pEngine->pfnAddCommand("+na_bhop_nsd", []() {
		cvar.bhop_nsd = true;
	});
	g_pEngine->pfnAddCommand("-na_bhop_nsd", []() {
		cvar.bhop_nsd = false;
	});

	g_pEngine->pfnAddCommand("+na_gstrafe_bhop", []() {
		cvar.gstrafe_bhop = true;
	});
	g_pEngine->pfnAddCommand("-na_gstrafe_bhop", []() {
		cvar.gstrafe_bhop = false;
	});

	g_pEngine->pfnAddCommand("+na_gstrafe_standup", []() {
		cvar.gstrafe_standup = true;
	});
	g_pEngine->pfnAddCommand("-na_gstrafe_standup", []() {
		cvar.gstrafe_standup = false;
	});

	g_pEngine->pfnAddCommand("na_rand_SteamID_Mask", []() {
		g_Systems.RandomizeSteamIDMask();
	});

	g_pEngine->pfnAddCommand("+na_speedhack", []() {
		cvar.adjust_speed = true;
	});
	g_pEngine->pfnAddCommand("-na_speedhack", []() {
		cvar.adjust_speed = false;
	});

	g_pEngine->pfnAddCommand("+na_fakeduck", []() {
		cvar.fakeduck = true;
	});
	g_pEngine->pfnAddCommand("-na_fakeduck", []() {
		cvar.fakeduck = false;
	});

	g_pClient->HUD_Frame = HUD_Frame;
	g_Client.HUD_Frame(time);
}

int CL_IsThirdPerson(void)
{
	if (!cvar.hide_from_obs && !g_pGlobals.bSnapshot && !g_pGlobals.bScreenshot && cvar.thirdperson > 0 && g_Local.bAlive)
		return 1;

	return g_Client.CL_IsThirdPerson();
}

void HUD_PlayerMoveInit(struct playermove_s *ppmove)
{
	PM_InitTextureTypes(ppmove);

	return g_Client.HUD_PlayerMoveInit(ppmove);
}

int StudioCheckBBox() { return 1; }

void StudioSetRemapColors(int top, int bottom)
{
	cl_entity_s *ent = g_Studio.GetCurrentEntity();

	World.GetHitboxes(ent);

	g_Studio.StudioSetRemapColors(top, bottom);
}

int pfnDrawUnicodeCharacter(int x, int y, short number, int r, int g, int b, unsigned long hfont)
{
	if (!cvar.hide_from_obs && cvar.hud_clear && !g_pGlobals.bSnapshot && !g_pGlobals.bScreenshot)
		return 1;

	return g_Engine.pfnDrawUnicodeCharacter(x, y, number, r, g, b, hfont);
}

int HUD_AddEntity(int type, struct cl_entity_s *ent, const char *modelname)
{
	if (!cvar.hide_from_obs && cvar.esp && g_Utils.IsPlayer(ent) && g_Player[ent->index].bAlive && !g_pGlobals.bSnapshot && !g_pGlobals.bScreenshot)
	{
		if ((!cvar.esp_teammates || cvar.disable_render_teammates) && g_Player[ent->index].iTeam == g_Local.iTeam)
			return g_Client.HUD_AddEntity(type, ent, modelname);

		if (cvar.bullets_trace || cvar.esp_line_of_sight)
		{
			int beamindex = g_Engine.pEventAPI->EV_FindModelIndex("sprites/laserbeam.spr");

			Vector vecStart, vecEnd, vecForward;

			pmtrace_t tr;

			vecStart = g_PlayerExtraInfoList[ent->index].vHitbox[11];

			g_Engine.pfnAngleVectors(g_Player[ent->index].vAngles, vecForward, NULL, NULL);

			vecEnd = vecStart + vecForward * 8192;

			g_Engine.pEventAPI->EV_SetTraceHull(2);
			g_Engine.pEventAPI->EV_PlayerTrace(vecStart, vecEnd, PM_GLASS_IGNORE, -1, &tr);

			if (cvar.esp_line_of_sight)
			{
				g_Engine.pEfxAPI->R_BeamPoints(vecStart, tr.endpos, beamindex, 0.001f, 0.9f, 0, 32, 2, 0, 0, cvar.esp_line_of_sight_r / 255, cvar.esp_line_of_sight_g / 255, cvar.esp_line_of_sight_b / 255);
			}

			if (cvar.bullets_trace)
			{
				int seq = Cstrike_SequenceInfo[ent->curstate.sequence];

				if (seq == SEQUENCE_SHOOT && g_PlayerExtraInfoList[ent->index].szWeaponName != NULL && lstrcmpA(g_PlayerExtraInfoList[ent->index].szWeaponName, "knife"))
				{
					Vector view_ofs(0, 0, PM_VEC_VIEW);

					if (g_Player[ent->index].bDucked)
						view_ofs[2] = PM_VEC_DUCK_VIEW;

					if (g_Player[ent->index].iTeam == TERRORIST)
						g_Engine.pEfxAPI->R_BeamPoints(vecStart, tr.endpos, beamindex, 0.001f, 0.4f, 0, 32, 2, 0, 0, 1, 0, 0);
					else if (g_Player[ent->index].iTeam == CT)
						g_Engine.pEfxAPI->R_BeamPoints(vecStart, tr.endpos, beamindex, 0.001f, 0.4f, 0, 32, 2, 0, 0, 0, 0, 1);

					g_Engine.pEfxAPI->R_BeamPoints(vecStart, tr.endpos, beamindex, 0.001f, 0.9f, 0, 32, 2, 0, 0, cvar.esp_line_of_sight_r / 255, cvar.esp_line_of_sight_g / 255, cvar.esp_line_of_sight_b / 255);
				}
			}
		}
	}

	return g_Client.HUD_AddEntity(type, ent, modelname);
}

void HookUserMessages()
{
	pResetHUD		= HookUserMsg("ResetHUD", ResetHUD);
	pBombDrop		= HookUserMsg("BombDrop", BombDrop);
	pBattery		= HookUserMsg("Battery", Battery);
	pHealth			= HookUserMsg("Health", Health);
	pDeathMsg		= HookUserMsg("DeathMsg", DeathMsg);
	pSetFOV			= HookUserMsg("SetFOV", SetFOV);
	pTeamInfo		= HookUserMsg("TeamInfo", TeamInfo);
	pScoreAttrib	= HookUserMsg("ScoreAttrib", ScoreAttrib);
}

int HUD_GetHullBounds(int hullnum, float* mins, float* maxs)
{
	if (hullnum == 1)
		maxs[2] = 32.0f; // https://gist.github.com/WPMGPRoSToTeMa/2e6e0454654f9e4ca22ee3e987051b57
	return 1;
}

void CL_Move() //Create and send the command packet to the server
{
	g_Utils.bSendpacket(true);

	CL_Move_s();
}

void Netchan_TransmitBits(netchan_t *chan, int length, byte *data) {
	g_pNetchan = chan;
	if (g_AimBot.currentTargetIndex == 0)
		return Netchan_TransmitBits_s(chan, length, data);

	//bool isReliable = (uint)chan->incoming_reliable_sequence << 31;
	bool isReliable = chan->incoming_sequence | ((uint)chan->incoming_reliable_sequence << 31);

	// Process...
	int instate = chan->incoming_reliable_sequence;
	int insequencenr = chan->incoming_sequence;

	// Add lag
	if (cvar.fakelatency)
	{
		for (auto& seq : sequences)
		{
			int fakepingamount = cvar.fakelatency_amount;
			if (pmove->time - seq.curtime >= fakepingamount)
			{
				chan->incoming_reliable_sequence = seq.m_nInReliableState;
				chan->incoming_sequence = seq.m_nInSequenceNr;

				if (cvar.debug)
					g_Engine.Con_Printf(">>>> teleport to sequence %d\n", chan->incoming_sequence);

				break;
			}
		}
	}

	// Call original
	Netchan_TransmitBits_s(chan, length, data);

	// Needed?
	//chan->incoming_reliable_sequence = instate;
	//chan->incoming_sequence = insequencenr;
}

void HUD_ProcessPlayerState(struct entity_state_s *dst, const struct entity_state_s *src)
{
	if (cvar.bypass_valid_blockers) 
	{
		src->mins[0] = -16;
		src->mins[1] = -16;
		src->mins[2] = -36;

		src->maxs[0] = 16;
		src->maxs[1] = 16;
		src->maxs[2] = 36;
	}

	g_Client.HUD_ProcessPlayerState(dst, src);
}

int HUD_Key_Event(int down, int keynum, const char *pszCurrentBinding) {
	if (down) {
		switch (keynum) {
		case 137: // F3
			(int)cvar.aim_hschance--;
			break;
		case 138: // F4
			(int)cvar.aim_hschance++;
			break;
		case 139: // F5
			(int)cvar.aim_fov--;
			break;
		case 140: // F6
			(int)cvar.aim_fov++;
			break;
		case 141: // F7
			(int)cvar.thirdperson++;
			break;
		case 142: // F8
			(int)cvar.thirdperson--;

		}
	}
	//if (cvar.debug)
		//g_Engine.Con_Printf("down: %d, keynum: %d, currbind: %s", down, keynum, pszCurrentBinding);\

	return g_Client.HUD_Key_Event(down, keynum, pszCurrentBinding);
}

int(*StudioDrawPlayer)(int flags, struct entity_state_s *pplayer);
int newStudioDrawPlayer(int flags, struct entity_state_s *pplayer) {
	cl_entity_s *localPlayer = g_Engine.GetLocalPlayer();
	cl_entity_t *pEnt = g_Studio.GetCurrentEntity();

	int ret = StudioDrawPlayer(flags, pplayer); // original

	if (flags & STUDIO_RENDER && pEnt == localPlayer && cvar.thirdperson > 0 && cvar.aa_legit > 0) { // fake
		pEnt->angles = g_Player[localPlayer->index].vFakeAngles;
		pEnt->origin.x += 1;

		g_pStudio->SetForceFaceFlags(STUDIO_NF_CHROME);
		pEnt->curstate.renderfx = 0;
		pEnt->curstate.renderamt = 0;
		pEnt->curstate.rendermode = 0;
		pEnt->curstate.rendercolor.r = 255;
		pEnt->curstate.rendercolor.g = 255;
		pEnt->curstate.rendercolor.b = 255;
		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		StudioDrawPlayer(flags, pplayer);

		glEnable(GL_TEXTURE_2D);
	}

	return ret;
}

void StudioEntityLight(struct alight_s *plight) {
	cl_entity_s *ent = g_Studio.GetCurrentEntity();
	World.GetBones(ent);

	return g_Studio.StudioEntityLight(plight);
}

void HookClient()
{
	g_pClient->HUD_Frame				= HUD_Frame_init;
	g_pClient->HUD_PostRunCmd			= HUD_PostRunCmd;
	g_pClient->HUD_PlayerMoveInit		= HUD_PlayerMoveInit;
	g_pClient->CL_IsThirdPerson			= CL_IsThirdPerson;
	g_pClient->CL_CreateMove			= CL_CreateMove;
	g_pClient->V_CalcRefdef				= V_CalcRefdef;
	g_pClient->HUD_AddEntity			= HUD_AddEntity;
	g_pClient->HUD_GetHullBounds		= HUD_GetHullBounds;
	g_pClient->HUD_ProcessPlayerState	= HUD_ProcessPlayerState;
	g_pClient->HUD_Key_Event			= HUD_Key_Event;

	g_pStudio->StudioCheckBBox			= StudioCheckBBox;
	g_pStudio->StudioSetRemapColors		= StudioSetRemapColors;

	g_pEngine->pfnDrawUnicodeCharacter	= pfnDrawUnicodeCharacter;

	HookUserMessages();

	PreS_DynamicSound_s							= (PreS_DynamicSound_t)		DetourFunction((LPBYTE)g_Offsets.PreS_DynamicSound(),		(LPBYTE)&PreS_DynamicSound);
	CL_Move_s									= (CL_Move_t)				DetourFunction((LPBYTE)g_Offsets.CL_Move(),					(LPBYTE)&CL_Move);
	Netchan_TransmitBits_s						= (Netchan_TransmitBits_t)	DetourFunction((LPBYTE)g_Offsets.Netchan_TransmitBits(),	(LPBYTE)&Netchan_TransmitBits);
	g_Offsets.EnablePageWrite((DWORD)g_pStudioModelRenderer, sizeof(StudioModelRenderer_t));
	g_pStudioModelRenderer->StudioRenderModel	= StudioRenderModel_Gate;
	g_Offsets.RestorePageProtection((DWORD)g_pStudioModelRenderer, sizeof(StudioModelRenderer_t));

	r_studio_interface_t* g_pStudioAPI = nullptr;
	g_pStudioAPI = *(r_studio_interface_t**)g_Offsets.FindPattern("\xC7\xFF\xFF\xFF\xFF\xFF\xF3\xA5\xB9\xFF\xFF\xFF\xFF\xE8\xFF\xFF\xFF\xFF\x5F\xB8\xFF\xFF\xFF\xFF\x5E\xC3", "x?????xxx????x????xx????xx", g_Offsets.client.base, g_Offsets.client.end, 0x2);

	if (g_pStudioAPI) {
		StudioDrawPlayer = g_pStudioAPI->StudioDrawPlayer;
		g_pStudioAPI->StudioDrawPlayer = newStudioDrawPlayer;

		if (cvar.debug)
			g_Engine.Con_Printf("g_pStudioAPI: %X\n", g_pStudioAPI->version);
	}
}
