#include "../../Required.h"

using namespace std;

CTraitorDetection g_TraitorDetection;

static const char WantedWeapons[][20] = { "knife", "silencedusp", "newton", "awp", "c4" };

void CTraitorDetection::Start(int indx)
{
	if (!cvar.TTT)
		return;

	cl_entity_s* ent = g_Engine.GetEntityByIndex(indx);

	auto index = ent->index;

	Update(indx);

	for (int i = 0; i < _countof(WantedWeapons); i++)
	{
		if (lstrcmpA(g_PlayerExtraInfoList[index].szWeaponName, WantedWeapons[i]) == 0)
		{
			auto name = g_PlayerInfoList[index].name;

			if (std::find(Traitors.begin(), Traitors.end(), name) == Traitors.end())
			{
				g_Player[index].bTraitor = true;
				Traitors.push_back(name);
				TraitorsIdx.push_back(index);

				g_Engine.Con_Printf("%s added to traitor list.\n", name);
			}
		}
	}
}

void CTraitorDetection::Update(int idx)
{
	if (!cvar.TTT)
		return;

	if (Traitors.size() > 0)
	{
		cl_entity_s* ent = g_Engine.GetEntityByIndex(idx);

		if (!g_Utils.IsPlayerUpdated(ent))
			return;

		if (!g_Utils.IsPlayerAlive(ent))
		{
			auto name = g_PlayerInfoList[idx].name;

			// erase index and name from traitor list
			auto itr_i = std::find(TraitorsIdx.begin(), TraitorsIdx.end(), idx);
			auto itr_s = std::find(Traitors.begin(), Traitors.end(), name);

			if (itr_i != TraitorsIdx.end())
			{
				TraitorsIdx.erase(itr_i);

				if (itr_s != Traitors.end())
				{
					g_Player[idx].bTraitor = false;
					Traitors.erase(itr_s);
					g_Engine.Con_Printf("%s removed from traitor list.\n", name);
				}
			}
		}
	}
}

void CTraitorDetection::Draw()
{
	if (!cvar.TTT)
		return;

	if (Traitors.size() > 0 )
	{
		int newline{};

		if (cvar.status)
		{
			newline = 180 + 90;
			if (cvar.aim_multi_point)
				newline += 15;

			if (cvar.aa_edge || cvar.aa_pitch || cvar.aa_yaw)
				newline += 15;

			if (cvar.aim_perfect_silent)
				newline += 15;
		}
		else
		{
			newline = 180;
		}

		g_Drawing.DrawString(ESP, g_Screen.iWidth / 100, (g_Screen.iHeight / 100) + newline, 205, 25, 25, cvar.esp_alpha, FONT_LEFT, "Detected:"); newline += 15;

		for (auto v : Traitors)
		{
			g_Drawing.DrawString(ESP, g_Screen.iWidth / 100, (g_Screen.iHeight / 100) + newline, 240, 240, 240, cvar.esp_alpha, FONT_LEFT, "%s", v.c_str());
			newline += 15;
		}
	}
}
