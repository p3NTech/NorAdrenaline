#include "../../Required.h"
#include <time.h>
#include <string>
#include <array>
#include <math.h>
#include "../../ValveSDK/pm_shared/pm_defs.h"
#include "../../ValveSDK/pm_shared/pm_materials.h"
#include "../../netchan.h"

#define PLAYER_FATAL_FALL_SPEED		980
#define PLAYER_MAX_SAFE_FALL_SPEED	504.8
#define DegToRad(Angle)((M_PI/180.0)*Angle)

CSystems g_Systems;
netchan_t g_pNetchan;

const float STOP_EPSILON = 0.1f;

bool CSystems::IsVectorVisible(Vector origin, Vector target, bool enviroment_only)
{

	if (!enviroment_only)
	{
		pmtrace_t trace;

		g_Engine.pEventAPI->EV_SetTraceHull(2);
		g_Engine.pEventAPI->EV_PlayerTrace(origin, target, PM_GLASS_IGNORE, -1, &trace);

		return (trace.fraction == 1.0f);
	}
	else
	{
		pmtrace_t trace;

		g_Engine.pEventAPI->EV_SetTraceHull(2);
		g_Engine.pEventAPI->EV_PlayerTrace(origin, target, PM_WORLD_ONLY, -1, &trace);

		return (trace.fraction == 1.0f);
	}
}

bool CSystems::canReachVector(Vector loc, Vector dest)
{
	if (!dest.IsZero())
	{
		Vector ref;
		Vector dist = dest - loc;
		int maxiterations = floor(dest.DistTo(loc)) / 40;
		for (int i = 0; i < maxiterations; i++)
		{
			// math to get the next vector 40.0f in the direction of dest
			Vector vec = loc + dist / ref.vectorMax(ref.vectorAbs(dist)) * 40.0f * (i + 1);

			if (VectorialDistanceToGround({ vec.x, vec.y, vec.z + 5 }) >= 40)
				return false;

			for (int j = 0; j < 4; j++)
			{
				Vector directionalLoc = vec;
				// what direction to check
				switch (j)
				{
				case 0:
					directionalLoc.x = directionalLoc.x + 40;
					break;
				case 1:
					directionalLoc.x = directionalLoc.x - 40;
					break;
				case 2:
					directionalLoc.y = directionalLoc.y + 40;
					break;
				case 3:
					directionalLoc.y = directionalLoc.y - 40;
					break;
				}
				pmtrace_t trace;

				g_Engine.pEventAPI->EV_SetTraceHull(2);
				g_Engine.pEventAPI->EV_PlayerTrace(vec, directionalLoc, PM_WORLD_ONLY, -1, &trace);

				// distance of trace < than 26
				if (vec.DistTo(trace.endpos) < 26.0f)
					return false;
			}
		}
	}
	else
	{
		if (VectorialDistanceToGround({ loc.x, loc.y, loc.z + 5 }) >= 40)
			return false;

		// check if there is enough space arround the vector for a player to fit
		// for loop for all 4 directions
		for (int i = 0; i < 4; i++)
		{
			Vector directionalLoc = loc;
			// what direction to check
			switch (i)
			{
			case 0:
				directionalLoc.x = directionalLoc.x + 40;
				break;
			case 1:
				directionalLoc.x = directionalLoc.x - 40;
				break;
			case 2:
				directionalLoc.y = directionalLoc.y + 40;
				break;
			case 3:
				directionalLoc.y = directionalLoc.y - 40;
				break;
			}

			pmtrace_t trace;

			g_Engine.pEventAPI->EV_SetTraceHull(2);
			g_Engine.pEventAPI->EV_PlayerTrace(loc, directionalLoc, PM_WORLD_ONLY, -1, &trace);

			// distance of trace < than 26
			if (loc.DistTo(trace.endpos) < 26.0f)
				return false;
		}
	}
	return true;
}

Vector CSystems::VischeckCorner(int iPlayer1, int iPlayer2, float maxdist, bool checkWalkable)
{
	auto player = ENTITY(iPlayer1);
	auto target = ENTITY(iPlayer2);

	auto Index1 = player->index;
	auto Index2 = target->index;

	int maxiterations = maxdist / 40;
	Vector origin = player->origin;

	// if we can see an entity, we don't need to run calculations
	if (VisCheckEntFromEnt(Index1, Index2))
	{
		if (!checkWalkable)
			return origin;
		else if (canReachVector(origin, target->origin))
			return origin;
	}

	for (int i = 0; i < 8; i++) // for loop for all 4 directions
	{
		// 40 * maxiterations = range in HU
		for (int j = 0; j < maxiterations; j++)
		{
			Vector virtualOrigin = origin;
			// what direction to go in
			switch (i)
			{
			case 0:
				virtualOrigin.x = virtualOrigin.x + 40 * (j + 1);
				break;
			case 1:
				virtualOrigin.x = virtualOrigin.x - 40 * (j + 1);
				break;
			case 2:
				virtualOrigin.y = virtualOrigin.y + 40 * (j + 1);
				break;
			case 3:
				virtualOrigin.y = virtualOrigin.y - 40 * (j + 1);
				break;
			case 4:
				virtualOrigin.x = virtualOrigin.x + 20 * (j + 1);
				virtualOrigin.y = virtualOrigin.y + 20 * (j + 1);
				break;
			case 5:
				virtualOrigin.x = virtualOrigin.x - 20 * (j + 1);
				virtualOrigin.y = virtualOrigin.y - 20 * (j + 1);
				break;
			case 6:
				virtualOrigin.x = virtualOrigin.x - 20 * (j + 1);
				virtualOrigin.y = virtualOrigin.y + 20 * (j + 1);
				break;
			case 7:
				virtualOrigin.x = virtualOrigin.x + 20 * (j + 1);
				virtualOrigin.y = virtualOrigin.y - 20 * (j + 1);
				break;
			}
			// check if player can see the players virtualOrigin
			if (!IsVectorVisible(origin, virtualOrigin, true))
				continue;
			// check if the virtualOrigin can see the target
			if (!VisCheckEntFromEntVector(Index2, virtualOrigin))
				continue;
			if (!checkWalkable)
				return virtualOrigin;

			// check if the location is accessible
			if (!canReachVector(origin, virtualOrigin))
				continue;
			if (canReachVector(virtualOrigin, target->origin))
				return virtualOrigin;
		}
	}
	// if we didn't find anything, return an empty Vector
	return { 0, 0, 0 };
}

bool CSystems::VisCheckEntFromEnt(int iPlayer1, int iPlayer2)
{
	auto player1 = ENTITY(iPlayer1);
	auto player2 = ENTITY(iPlayer2);

	Vector source = player1->origin;

	return true; //g_Visuals.GetAmountOfPlayerVisible(source, player2);
}

bool CSystems::VisCheckEntFromEntVector(int iPlayer, Vector targetVector)
{
	auto player1 = ENTITY(iPlayer);

	return true; //g_Visuals.GetAmountOfPlayerVisible(targetVector, player1);
}

std::pair<Vector, Vector> CSystems::VischeckWall(int iPlayer1, int iPlayer2, float maxdist, bool checkWalkable)
{
	auto player1 = ENTITY(iPlayer1);
	auto player2 = ENTITY(iPlayer2);

	auto i1 = player1->index;
	auto i2 = player2->index;

	int maxiterations = maxdist / 40;
	Vector origin = player1->origin;

	// if we can see an entity, we don't need to run calculations
	if (VisCheckEntFromEnt(i1, i2))
	{
		std::pair<Vector, Vector> orig(origin, player2->origin);
		if (!checkWalkable)
			return orig;
		else if (canReachVector(origin, player2->origin))
			return orig;
	}

	for (int i = 0; i < 8; i++) // for loop for all 4 directions
	{
		// 40 * maxiterations = range in HU
		for (int j = 0; j < maxiterations; j++)
		{
			Vector virtualOrigin = origin;
			// what direction to go in
			switch (i)
			{
			case 0:
				virtualOrigin.x = virtualOrigin.x + 40 * (j + 1);
				break;
			case 1:
				virtualOrigin.x = virtualOrigin.x - 40 * (j + 1);
				break;
			case 2:
				virtualOrigin.y = virtualOrigin.y + 40 * (j + 1);
				break;
			case 3:
				virtualOrigin.y = virtualOrigin.y - 40 * (j + 1);
				break;
			case 4:
				virtualOrigin.x = virtualOrigin.x + 20 * (j + 1);
				virtualOrigin.y = virtualOrigin.y + 20 * (j + 1);
				break;
			case 5:
				virtualOrigin.x = virtualOrigin.x - 20 * (j + 1);
				virtualOrigin.y = virtualOrigin.y - 20 * (j + 1);
				break;
			case 6:
				virtualOrigin.x = virtualOrigin.x - 20 * (j + 1);
				virtualOrigin.y = virtualOrigin.y + 20 * (j + 1);
				break;
			case 7:
				virtualOrigin.x = virtualOrigin.x + 20 * (j + 1);
				virtualOrigin.y = virtualOrigin.y - 20 * (j + 1);
				break;
			}
			// check if player can see the players virtualOrigin
			if (!IsVectorVisible(origin, virtualOrigin, true))
				continue;
			for (int i = 0; i < 8; i++) // for loop for all 4 directions
			{
				// 40 * maxiterations = range in HU
				for (int j = 0; j < maxiterations; j++)
				{
					Vector virtualOrigin2 = player2->origin;
					// what direction to go in
					switch (i)
					{
					case 0:
						virtualOrigin2.x = virtualOrigin2.x + 40 * (j + 1);
						break;
					case 1:
						virtualOrigin2.x = virtualOrigin2.x - 40 * (j + 1);
						break;
					case 2:
						virtualOrigin2.y = virtualOrigin2.y + 40 * (j + 1);
						break;
					case 3:
						virtualOrigin2.y = virtualOrigin2.y - 40 * (j + 1);
						break;
					case 4:
						virtualOrigin2.x = virtualOrigin2.x + 20 * (j + 1);
						virtualOrigin2.y = virtualOrigin2.y + 20 * (j + 1);
						break;
					case 5:
						virtualOrigin2.x = virtualOrigin2.x - 20 * (j + 1);
						virtualOrigin2.y = virtualOrigin2.y - 20 * (j + 1);
						break;
					case 6:
						virtualOrigin2.x = virtualOrigin2.x - 20 * (j + 1);
						virtualOrigin2.y = virtualOrigin2.y + 20 * (j + 1);
						break;
					case 7:
						virtualOrigin2.x = virtualOrigin2.x + 20 * (j + 1);
						virtualOrigin2.y = virtualOrigin2.y - 20 * (j + 1);
						break;
					}
					if (!IsVectorVisible(virtualOrigin, virtualOrigin2, true))
						continue;
					if (!IsVectorVisible(virtualOrigin2, player2->origin, true))
						continue;
					std::pair<Vector, Vector> toret(virtualOrigin, virtualOrigin2);
					if (!checkWalkable)
						return toret;
					if (!canReachVector(origin, virtualOrigin) || !canReachVector(virtualOrigin2, virtualOrigin))
						continue;
					if (canReachVector(virtualOrigin2, player2->origin))
						return toret;
				}
			}
		}
	}
	// if we didn't find anything, return an empty Vector
	return { { 0, 0, 0 }, { 0, 0, 0 } };
}

FORCEINLINE vec_t _DotProduct(const Vector& a, const Vector& b)
{
	if (!a || !b)
		return null;

	return(a.x*b.x + a.y*b.y + a.z*b.z);
}

void CSystems::PhysicsClipVelocity(Vector &in, const Vector &normal, Vector &out, float overbounce)
{
	float backoff = in.Dot(normal) * overbounce;

	for (int i = 0; i < 3; ++i) {
		float change = normal[i] * backoff;
		out[i] = in[i] - change;

		if (out[i] > -0.1f && out[i] < 0.1f)
			out[i] = 0.0f;
	}

	float adjust = out.Dot(normal);

	if (adjust < 0.0f)
		out -= (normal * adjust);
}

float CSystems::GetEntityGravity()
{
	if (pmove->movetype == MOVETYPE_NOCLIP || pmove->movetype == MOVETYPE_STEP || pmove->movetype == MOVETYPE_FLY)
		return 0.0f;

	return 1.0f;
}

bool CSystems::PhysicsApplyFriction(Vector &in, Vector &out, float flSurfaceFriction, float flTickRate)
{
	if (pmove->waterjumptime)
		return false;

	auto sv_stopspeed = pmove->movevars->stopspeed;
	auto sv_friction = pmove->movevars->friction;

	float speed = in.Length() / flTickRate;

	if (speed < 0.1f)
		return false;

	float drop = 0.0f;

	if (flSurfaceFriction != -1.0f) {
		float friction = sv_friction * flSurfaceFriction;
		float control = (speed < sv_stopspeed) ? sv_stopspeed : speed;
		drop += control * friction * flTickRate;
	}

	float newspeed = speed - drop;

	if (newspeed < 0.0f)
		newspeed = 0.0f;

	if (newspeed != speed) {
		newspeed /= speed;
		out = in * newspeed; // VectorScale(in, newspeed, out);
	}

	out -= in * (1.0f - newspeed);
	out *= flTickRate;
	return true;
}

void CSystems::DrawDebugArrow(const float x0, const float y0, const float x1, const float y1, const DWORD color, const int alpha)
{
	float size = 10.0f;
	QAngle angRotation;
	Vector from = { x0, y0, NULL };
	Vector to	= { x1, y1, NULL };
	g_Utils.VectorAngles(to - from, angRotation);
	Vector vecForward, vecRight, vecUp;
	g_Engine.pfnAngleVectors(angRotation, vecForward, vecRight, vecUp);

	g_Drawing.DrawLine(from.x, from.y, to.x, to.y, RED(color), GREEN(color), BLUE(color), alpha);
	g_Drawing.DrawLine(from.x, from.y, from.x - vecRight.x * size, from.y - vecRight.y * size, RED(color), GREEN(color), BLUE(color), alpha);
}

void ComputeMove(int id, float forwardmove, float sidemove)
{
	Vector vecVelocity = g_Player[id].vVelocity;

	float wtf_const = 33.4;

	float flSpeed = vecVelocity.Length2D() * wtf_const;

	cl_entity_s *ent = g_Engine.GetEntityByIndex(id);

	if (flSpeed > 0 && ent)
	{
		QAngle QAngles = ent->angles;

		Vector vecVelocityRotated;
		vecVelocityRotated.VectorRotate(vecVelocity, QAngles);

		forwardmove = vecVelocityRotated[0] * wtf_const;
		sidemove = -1 * vecVelocityRotated[1] * wtf_const;

		if (forwardmove > 250)
			forwardmove = 250;

		if (sidemove > 250)
			sidemove = 250;
	}
	else {
		forwardmove = 0;
		sidemove = 0;
	}
}

std::pair<float, float> CSystems::ComputeMove(const Vector &a, const Vector &b, usercmd_s* cmd)
{
	Vector diff = (b - a);

	if (diff.Length() == 0)
		return { 0, 0 };

	const float x = diff.x;
	const float y = diff.y;

	Vector vsilent(x, y, 0);

	float speed = sqrt(vsilent.x * vsilent.x + vsilent.y * vsilent.y);

	Vector ang;
	g_Utils.VectorAngles(vsilent, ang);

	float yaw = DEG2RAD(ang.y - cmd->viewangles.y);

	return { cos(yaw) * 450, -sin(yaw) * 450 };
}
float CSystems::DistanceToGround(cl_entity_s *ent)
{
	if (pmove->flags & FL_ONGROUND) return 0;

	Vector& origin = pmove->origin;
	float v1 = VectorialDistanceToGround(origin + Vector(10.0f, 10.0f, 0.0f));
	float v2 = VectorialDistanceToGround(origin + Vector(-10.0f, 10.0f, 0.0f));
	float v3 = VectorialDistanceToGround(origin + Vector(10.0f, -10.0f, 0.0f));
	float v4 = VectorialDistanceToGround(origin + Vector(-10.0f, -10.0f, 0.0f));
	return min(v1, min(v2, min(v3, v4)));
}

float CSystems::VectorialDistanceToGround(Vector origin)
{
	pmtrace_t tr;
	Vector endpos = origin;
	endpos.z -= 8192;
	g_Engine.pEventAPI->EV_PlayerTrace(origin, endpos, PM_GLASS_IGNORE, -1, &tr);
	return 8192.0f * tr.fraction;
}

void CSystems::WalkTo(const Vector &vector, struct usercmd_s *cmd)
{
	// Calculate how to get to a vector
	auto result = ComputeMove(g_Local.vOrigin, vector, cmd);

	// Push our move to usercmd
	cmd->forwardmove = result.first;
	cmd->sidemove = result.second;
}

void CSystems::MoveTo(const Vector &vector, CBaseLocal *ent, struct usercmd_s *cmd)
{
	auto result = ComputeMove(ent->vOrigin, vector, cmd);
	cmd->forwardmove = result.first;
	cmd->sidemove = result.second;
}

void CSystems::KnifeBot(struct usercmd_s *cmd)
{
	if (IsCurWeaponKnife() && CanAttack() && cvar.knifebot)
	{
		int id = NULL;
		float flDist = 8192.f;

		for (int i = 1; i <= g_Engine.GetMaxClients(); i++)
		{
			if (i == g_Local.iIndex)
				continue;

			if (!g_Player[i].bAlive)
				continue;

			if (g_Player[i].bFriend)
				continue;

			if (!g_Player[i].bVisible)
				continue;

			if (g_Player[i].iTeam == g_Local.iTeam)
				continue;

			if (g_Player[i].flDist < flDist || id == NULL)
			{
				flDist = g_Player[i].flDist;
				id = i;
			}
		}

		if (id > 0)
		{
			cl_entity_s *ent = g_Engine.GetEntityByIndex(id);

			if (!ent)
				return;

			int fDidHit = FALSE;

			Vector vecPlayerOrigin = ent->origin + g_Player[id].vVelocity * g_Player[id].flFrametime;

			if (vecPlayerOrigin.Distance(pmove->origin) < 64)
			{
				// hit
				fDidHit = TRUE;

				float flDamage = 65.0f;

				Vector vecForwardPlayer, vecForward;

				Vector vecSrc = g_Local.vEye;

				QAngle QAimAngle;

				g_Utils.VectorAngles(vecPlayerOrigin - vecSrc, QAimAngle);

				QAimAngle.Normalize();

				g_Engine.pfnAngleVectors(QAimAngle, vecForward, 0, 0);
				g_Engine.pfnAngleVectors(ent->angles, vecForwardPlayer, 0, 0);

				vecForwardPlayer.Normalize();
				vecForward.Normalize();

				float flDot = vecForward.Dot2D(vecForwardPlayer);

				//Triple the damage if we are stabbing them in the back.
				if (flDot > 0.80f)
				{
					flDamage *= 3.0f;
				}

				if (fDidHit)
				{
					g_Utils.MakeAngle(false, QAimAngle, cmd);

					cmd->buttons |= IN_ATTACK2;
				}
			}
		}
	}
}

double _my_abs(double n)
{
	if (n >= 0)return n; //if positive, return without ant change
	else return 0 - n; //if negative, return a positive version
}

void CSystems::JumpBug(float frametime, struct usercmd_s *cmd)
{
	static int state = 0;

	if (cvar.jump_bug && g_Local.flFallVelocity >= PLAYER_MAX_SAFE_FALL_SPEED)
	{
		if (g_Local.flHeightGround - (g_Local.flFallVelocity * frametime / 1 * 15) <= 0)
		{
			bool curveang = false;
			float fpheight = 0;
			if (g_Local.flGroundAngle > 1)
			{
				curveang = true;
				Vector vTemp = g_Local.vOrigin;
				vTemp[2] -= 8192;
				pmtrace_t* trace = g_Engine.PM_TraceLine(g_Local.vOrigin, vTemp, 1, 2, -1);
				fpheight = abs(g_Local.vOrigin.z - trace->endpos.z - (g_Local.iUseHull == 1 ? 18.0f : 36.0f));
			}
			else fpheight = g_Local.flHeightGround;

			static float last_h = 0.0f;
			float cur_frame_zdist = abs((g_Local.flFallVelocity + (800 * frametime)) * frametime);
			cmd->buttons |= IN_DUCK;
			cmd->buttons &= ~IN_JUMP;
			switch (state)
			{
			case 1:
				cmd->buttons &= ~IN_DUCK;
				cmd->buttons |= IN_JUMP;
				state = 2;
				break;
			case 2:
				state = 0;
				break;
			default:
				if (_my_abs(fpheight - cur_frame_zdist * 1.5) <= (20.0) && cur_frame_zdist > 0.0f)
				{
					float needspd = _my_abs(fpheight - (19.0));
					float scale = abs(needspd / cur_frame_zdist);
					func.AdjustSpeed(scale);
					state = 1;
				}
				break;
			}
			last_h = fpheight;
		}
		else state = 0;
	}
}

void CSystems::air_duck(struct usercmd_s *cmd)
{
	if (g_Local.flHeight <= 20 && cvar.air_duck)
	{
		if (cmd->buttons & IN_JUMP)
		{
			cmd->buttons |= IN_DUCK;
		}
		else
		{
			cmd->buttons &= ~IN_DUCK;
		}
	}
}

void CSystems::FakeDuck(struct usercmd_s* cmd)
{
	if (!cvar.fakeduck)
		return;

	static bool m_IsCounter = false;
	static int m_Ism_iCounters = 0;

	if (m_Ism_iCounters == 14)
	{
		m_Ism_iCounters = 0;
		m_IsCounter = !m_IsCounter;
	}
	m_Ism_iCounters++;

	if (m_IsCounter)
	{
		cmd->buttons |= IN_DUCK;
		g_Utils.bSendpacket(true);
	}
	else
	{
		cmd->buttons &= ~IN_DUCK;
		g_Utils.bSendpacket(false);
	}
}

void CSystems::BunnyHop(struct usercmd_s *cmd)
{
	if (cvar.bunnyhop)
	{
		if (cmd->buttons & IN_JUMP)
		{
			cmd->buttons &= ~IN_JUMP;

			if (pmove->flags & FL_ONGROUND || pmove->waterlevel >= 2 || pmove->movetype == MOVETYPE_FLY)
			{
				cmd->buttons |= IN_JUMP;
			}
		}
	}
}

void CSystems::GS(struct usercmd_s *cmd)
{
	if (cvar.gstrafe)
	{
		static int gs_state = 0;

		if (gs_state == 0 && pmove->flags & FL_ONGROUND)
		{
			cmd->buttons |= IN_DUCK;
			gs_state = 1;
		}
		else if (gs_state == 1)
		{
			cmd->buttons &= ~IN_DUCK;
			gs_state = 0;
		}
	}
}

bool CSystems::Clamp(double _in, double low, double high)
{
	if (_in < low)
	{
		low;
	}
	if (_in > high)
	{
		high;
	}
	return _in;
}

/*
void CSystems::strafe_circle(struct usercmd_s *cmd)
{
	if (!cvar.cstrafe_temp) return;

	static float CurYaw = 0.0f;
	cmd->forwardmove = 1000.0f;
	cmd->sidemove = 0.0f;
	float Vel2D = pmove->velocity.Length2D();
	if (Vel2D >= 50)
	{
		float TurnRate = this->Clamp((Vel2D / 100.f), 0.75f, 10.25f);
		CurYaw += TurnRate;
		if (CurYaw >= 180.f)
			CurYaw = -180.f;

		cmd->viewangles.y = CurYaw;
	}
}
*/

void CSystems::circle_strafe(float* circle_yaw, struct usercmd_s *cmd)
{
	if (!cvar.cstrafe_temp) {
		*circle_yaw = cmd->viewangles.y;
		return;
	}

	auto local = g_Local;
	const auto min_angle = 2.25f;
	const auto max_angle = 5.f;
	float speed = pmove->velocity.Length2D();

	const float perfect_strafe = Clamp2(g_Systems.get_move_angle(speed), min_angle, max_angle);
	const float finish_time = Clamp2(320.f / speed, 0.35f, 1.f);

	auto turn_angle = perfect_strafe;

	while (true)
	{
		Vector plane;
		if (!g_Systems.will_hit_wall(finish_time, turn_angle, plane) || turn_angle > max_angle)
			break;

		turn_angle += 0.2f;
	}

	if (turn_angle > max_angle)
	{
		turn_angle = perfect_strafe - 0.2f;

		while (true)
		{
			Vector plane;
			if (!g_Systems.will_hit_wall(finish_time, turn_angle, plane) || turn_angle < -min_angle)
				break;

			turn_angle -= 0.2f;
		}

		if (turn_angle < min_angle)
		{
			Vector plane;
			int ticks = 0;
			if (g_Systems.get_closest_plane(&plane, ticks))
				turn_angle = AngleNormalize(*circle_yaw - RAD2DEG(atan2(plane.y, plane.x)) + 90) * 0.2;
		}
		else
			turn_angle -= 0.2f;
	}
	else
		turn_angle += 0.2f;

	cmd->viewangles.y = *circle_yaw = AngleNormalize(*circle_yaw + turn_angle);
	cmd->sidemove = copysign(360.f, -turn_angle);
}

float CSystems::get_move_angle(float speed)
{
	auto move_angle = RAD2DEG(asin(30.f / speed));

	if (!isfinite(move_angle) || move_angle > 90.f)
		move_angle = 90.f;
	else if (move_angle < 0.f)
		move_angle = 0.f;

	return move_angle;
}

bool CSystems::get_closest_plane(Vector* plane, int &ticks)
{
	auto local = g_Local;
	pmtrace_t trace;

	auto vecMins = pmove->player_mins;
	auto vecMaxs = pmove->player_maxs;

	Vector start = local.vOrigin;

	Vector planes;
	auto count = 0;

	for (auto step = 0.f; step <= M_PI * 2.f; step += M_PI / 10.f)
	{
		auto end = start;

		end.x += cos(step) * (1 / 0.0078125f);
		end.y += sin(step) * (1 / 0.0078125f);

		g_Engine.pEventAPI->EV_SetTraceHull((pmove->flags & FL_DUCKING) ? 1 : 0);
		g_Engine.pEventAPI->EV_PlayerTrace(start, end, PM_GLASS_IGNORE | PM_STUDIO_BOX, g_Local.iIndex, &trace);

		if (trace.fraction < 1.f)
		{
			planes += trace.plane.normal;
			count++;
		}
		ticks++;
	}

	planes /= count;

	if (planes.z < 0.1f)
	{
		*plane = planes;
		return true;
	}

	return false;
}
#define TIME_TO_TICKS(dt) ((int)(0.5f + (float)(dt) / pmove->frametime))
bool CSystems::will_hit_wall(float finish_time, float turn_angle, Vector &plane)
{
	auto local = g_Local;
	static auto sv_gravity = g_Engine.pfnGetCvarFloat("sv_gravity");
	static float sv_jump_impulse = 301;

	bool ground = pmove->flags & FL_ONGROUND;
	float gravity_per_tick = sv_gravity * GetTickCount();

	Vector start = local.vOrigin, end = start;
	Vector velocity = pmove->velocity;

	pmtrace_t trace;

	int finish_tick = TIME_TO_TICKS(finish_time);
	double velocity_rotation_angle = RAD2DEG(atan2(velocity.y, velocity.x));
	int ticks_done = 0;

	if (finish_tick <= 0)
		return false;

	while (true)
	{
		float new_angle = velocity_rotation_angle + turn_angle;

		velocity.x = cos(DEG2RAD(new_angle)) * pmove->velocity.Length2D();
		velocity.y = sin(DEG2RAD(new_angle)) * pmove->velocity.Length2D();
		velocity.z = ground ? sv_jump_impulse : velocity.z - gravity_per_tick;

		end += velocity * pmove->frametime;

		//pmove->PM_PlayerTrace(start, end, PM_NORMAL, -1);
		g_Engine.pEventAPI->EV_SetTraceHull((pmove->flags & FL_DUCKING) ? 1 : 0);
		g_Engine.pEventAPI->EV_PlayerTrace(start, end, PM_GLASS_IGNORE | PM_STUDIO_BOX, g_Local.iIndex, &trace);

		if (trace.fraction != 1.f && trace.plane.normal.z <= 0.7f || trace.startsolid || trace.allsolid) {
			if (!trace.allsolid)
				plane = trace.plane.normal;
			break;
		}

		end = trace.endpos;
		end.z -= 2.f;

		g_Engine.pEventAPI->EV_SetTraceHull((pmove->flags & FL_DUCKING) ? 1 : 0);
		g_Engine.pEventAPI->EV_PlayerTrace(trace.endpos, end, PM_GLASS_IGNORE | PM_STUDIO_BOX, g_Local.iIndex, &trace);

		ground = (trace.fraction < 1.f || trace.allsolid || trace.startsolid) && trace.plane.normal.z >= 0.7f;

		if (++ticks_done >= finish_tick)
			return false;

		velocity_rotation_angle = new_angle;
	}

	return true;
}

void CSystems::AutoStrafe(struct usercmd_s *cmd)
{
	if (!cvar.autostrafe) return;

	static bool strafing;

	if (!(pmove->flags & FL_ONGROUND) && (pmove->movetype != 5) && g_Local.flVelocity >= 100) {
		float dir = 0.0f;

		int dir_value = this->DetectStrafeDir(cmd); 1;

		if (dir_value == 1)dir = 0 * M_PI / 180.0f;
		else if (dir_value == 2)	dir = 90 * M_PI / 180.0f;
		else if (dir_value == 3)	dir = 180 * M_PI / 180.0f;
		else if (dir_value == 4)	dir = -90 * M_PI / 180.0f;

		if (g_Local.flVelocity < 0.1f) {
			if (cmd->buttons&IN_FORWARD) {
				if (cmd->buttons&IN_MOVELEFT) {
					cmd->forwardmove = 3000.0;
					cmd->sidemove = -3000.0;
				}
				else if (cmd->buttons&IN_MOVERIGHT) {
					cmd->forwardmove = 3000.0;
					cmd->sidemove = 3000.0;
				}
				else
					cmd->forwardmove = 3000.0;
			}
			else if (cmd->buttons&IN_BACK) {
				if (cmd->buttons&IN_MOVELEFT) {
					cmd->forwardmove = -3000.0;
					cmd->sidemove = -3000.0;
				}
				else if (cmd->buttons&IN_MOVERIGHT) {
					cmd->forwardmove = -3000.0;
					cmd->sidemove = 3000.0;
				}
				else
					cmd->forwardmove = -3000.0;
			}
			else if (cmd->buttons&IN_MOVELEFT)
				cmd->sidemove = -3000.0;
			else if (cmd->buttons&IN_MOVERIGHT)
				cmd->sidemove = 3000.0;
			else
				cmd->forwardmove = 3000.0;
		}
		else {
			float va_speed = atan2(pmove->velocity.y, pmove->velocity.x);

			float va[3] = { 0, 0, 0 };
			g_Engine.GetViewAngles(va);

			float adif = va_speed - va[1] * M_PI / 180.0f - dir;

			adif = sin(adif);
			adif = atan2(adif, sqrt(1 - adif * adif));


			cmd->sidemove = (1000.1330)*(adif > 0 ? 1 : -1);
			cmd->forwardmove = 0;

			float angle;
			float osin, ocos, nsin, ncos;

			angle = cmd->viewangles.y * M_PI / 180.0f;
			osin = sin(angle);
			ocos = cos(angle);

			angle = 2.0f * cmd->viewangles.y * M_PI / 180.0f - va_speed + dir;
			nsin = sin(angle);
			ncos = cos(angle);

			cmd->forwardmove = cmd->sidemove * (osin * ncos - ocos * nsin);
			cmd->sidemove *= osin * nsin + ocos * ncos;

			float fs = 0;
			if (atan2(30.0 / g_Local.flVelocity, 1.0f) >= abs(adif)) {
				Vector vBodyDirection;

				if (dir_value)
					vBodyDirection = g_Local.vForward;
				else
					vBodyDirection = g_Local.vRight;

				vBodyDirection[2] = 0;
				vBodyDirection = vBodyDirection.Normalize();

#define POW(a) ((a) * (a))
				float vel = POW(vBodyDirection[0] * pmove->velocity[0]) + POW(vBodyDirection[1] * pmove->velocity[1]);

				fs = sqrt(cvar.strafe_speed * 160000 / vel);
			}

			cmd->forwardmove += fs;
		}

		float sdmw = cmd->sidemove;
		float fdmw = cmd->forwardmove;

		switch ((int)dir_value) {
		case 1:
			cmd->forwardmove = fdmw;
			cmd->sidemove = sdmw;
			break;
		case 2:
			cmd->forwardmove = -sdmw;
			cmd->sidemove = fdmw;
			break;
		case 3:
			cmd->forwardmove = -fdmw;
			cmd->sidemove = -sdmw;
			break;
		case 4:
			cmd->forwardmove = sdmw;
			cmd->sidemove = -fdmw;
			break;
		}
	}
}

void CSystems::bhop_nsd(struct usercmd_s *cmd) {
	if (cvar.bhop_nsd && (int)g_Local.flVelocity <= 299)
	{
		func.AdjustSpeed(0.0001);
	}
}

void CSystems::gs_standup(struct usercmd_s *cmd) {
	if (cvar.gstrafe_standup && g_Local.flHeight < 0.017638)
	{
		if (cvar.bhop_nsd && (g_Local.flGroundAngle < 5) && (g_Local.flHeight <= 0.000001f || cmd->buttons & FL_ONGROUND)) 
		{ 
			func.AdjustSpeed(0.0001); 
		}

		cmd->buttons |= IN_DUCK;
	}
}

void CSystems::SGS(struct usercmd_s *cmd) {
	static int gs_state = 0;
	if (!cvar.gstrafe_bhop && pmove->usehull == 0) { cmd->buttons |= IN_JUMP; }
	cmd->buttons &= ~IN_DUCK;
	if (pmove->flFallVelocity > 0) {
		if (pmove->flFallVelocity >= 139.337)
			if (g_Local.flHeight <= 30)
				cmd->buttons |= IN_DUCK;
	}
	if (gs_state == 0 && (pmove->flags & FL_ONGROUND)) {
		cmd->buttons |= IN_DUCK;

		gs_state = 1;
	}
	else if (gs_state == 1) {
		if (((pmove->flags & FL_DUCKING) ? 1 : 0) == 0)
			cmd->buttons |= IN_JUMP;

		cmd->buttons &= ~IN_DUCK;

		gs_state = 0;
	}
}

void CSystems::Fastrun(struct usercmd_s *cmd) {
	if (cvar.fastrun_temp && (pmove->flags & FL_ONGROUND)) {
		if (!(cmd->buttons&(IN_FORWARD | IN_BACK | IN_MOVELEFT | IN_MOVERIGHT))) return;

		if (cmd->buttons&IN_MOVELEFT && cmd->buttons&IN_MOVERIGHT)
			cmd->buttons &= ~(IN_MOVELEFT | IN_MOVERIGHT);

		if (cmd->buttons&IN_FORWARD && cmd->buttons&IN_BACK)
			cmd->buttons &= ~(IN_FORWARD | IN_BACK);

		float aaddtova;

		if (cmd->buttons&IN_FORWARD) {
			if (cmd->buttons&IN_MOVELEFT)
				aaddtova = 45.0f;
			else if (cmd->buttons&IN_MOVERIGHT)
				aaddtova = -45.0f;
			else
				aaddtova = 0.0f;
		}
		else if (cmd->buttons&IN_BACK) {
			if (cmd->buttons&IN_MOVELEFT)
				aaddtova = 135.0f;
			else if (cmd->buttons&IN_MOVERIGHT)
				aaddtova = -135.0f;
			else
				aaddtova = 180.0f;
		}
		else if (cmd->buttons&IN_MOVELEFT)
			aaddtova = 90.0f;
		else if (cmd->buttons&IN_MOVERIGHT)
			aaddtova = -90.0f;

		if (g_Local.flVelocity < 78) {
			if (cmd->buttons&IN_FORWARD) {
				if (cmd->buttons&IN_MOVELEFT) {
					cmd->forwardmove = 900;
					cmd->sidemove = -900;
				}
				else if (cmd->buttons&IN_MOVERIGHT) {
					cmd->forwardmove = 900;
					cmd->sidemove = 900;
				}
				else
					cmd->forwardmove = 900;
			}
			else if (cmd->buttons&IN_BACK) {
				if (cmd->buttons&IN_MOVELEFT) {
					cmd->forwardmove = -900;
					cmd->sidemove = -900;
				}
				else if (cmd->buttons&IN_MOVERIGHT) {
					cmd->forwardmove = -900;
					cmd->sidemove = 900;
				}
				else
					cmd->forwardmove = -900;
			}
			else if (cmd->buttons&IN_MOVELEFT)
				cmd->sidemove = -900;
			else if (cmd->buttons&IN_MOVERIGHT)
				cmd->sidemove = 900;

			return;
		}

		bool dir_rig = true;

		float yaw = atan2(pmove->velocity.y, pmove->velocity.x) * 180.0 / M_PI;

		yaw -= aaddtova;
		yaw = cmd->viewangles.y - yaw;

		int fadif = yaw;

		fadif = (fadif + 360) % 360;
		dir_rig = fadif <= 180;

		float x = 135.06374825035877480180939653038* (dir_rig ? -1 : +1);
		float y = 267.87643402987823669025530311859;

		float a = DegToRad(aaddtova);
		float sinA = sin(a);
		float cosA = cos(a);

		cmd->sidemove = x * cosA - y * sinA;
		cmd->forwardmove = y * cosA + x * sinA;

		x = cmd->sidemove;
		y = cmd->forwardmove;


		float newa = DegToRad(-yaw);
		sinA = sin(newa);
		cosA = cos(newa);

		cmd->sidemove = x * cosA - y * sinA;
		cmd->forwardmove = y * cosA + x * sinA;
	}
}

int CSystems::DetectStrafeDir(struct usercmd_s *cmd) {
	if (cmd->buttons&IN_FORWARD) {
		return 1; // Forward  W
	}
	if (cmd->buttons&IN_MOVERIGHT) {
		return 2; // Right    D
	}
	if (cmd->buttons&IN_BACK) {
		return 3; // Back     S
	}
	if (cmd->buttons&IN_MOVELEFT) {
		return 4; // Left     A
	}
}

void CSystems::RandomizeSteamID() {
	DWORD dwMask = 0x5A448; // steamclient.dll+5A448
	DWORD dwSteamID = 0x5AC4C; // steamclient.dll+5AC4C
	DWORD dwFlag = 0x5B4D4; // steamclient.dll+5B4D
	DWORD dwBase = reinterpret_cast<DWORD>(GetModuleHandle("steamclient.dll"));
	char szMask[14];

	srand(static_cast<unsigned int>(time(NULL)));
	char *szChars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	for (uint8_t i = 0; i < 14; i++) {
		szMask[i] = szChars[rand() % strlen(szChars)];
	}

	native_memwrite(dwBase + dwMask, reinterpret_cast<uintptr_t>(szMask), sizeof(szMask));

	DWORD dwOldProtect;
	VirtualProtect(LPVOID(dwBase + dwFlag), 1, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	*reinterpret_cast<uint8_t *>(dwBase + dwFlag) = 0;
	VirtualProtect(LPVOID(dwBase + dwFlag), 1, dwOldProtect, &dwOldProtect);

	g_pConsole->Printf("Randomized. New mask: %s", szMask);
}
void CSystems::unbanSteamID()
{
	srand(GetTickCount());

	DWORD NoSteamId = (DWORD)GetModuleHandle("steamclient.dll") + 0x5AC4C;
	NoSteamId += 4; *(DWORD*)NoSteamId = 0x6F676C61;

	DWORD UnLock = (DWORD)GetModuleHandle("steamclient.dll") + 0x5B4D4;
	*(DWORD*)UnLock = 0;

	DWORD SteamId = (DWORD)GetModuleHandle("steamclient.dll") + 0x5AC4C;
	*(DWORD*)SteamId = rand() % 99999999;

	g_pConsole->Printf("[NA] Validate as random Steam Enabled.");
}

void CSystems::cem_TransmitBits()
{
	if (cvar.lagexploit)
	{
		int val = cvar.fakeping_amount;
		int in = val * 10;

		func.AdjustSpeed(in);
		g_pNetchan.last_reliable_sequence	= in;
		g_pNetchan.outgoing_sequence		= in;
	}
}