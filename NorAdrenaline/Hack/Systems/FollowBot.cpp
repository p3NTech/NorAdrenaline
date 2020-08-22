#include "../../Required.h"

CFollowBot g_FollowBot;

extern "C"

using namespace std;
														// Define target
static std::vector<Vector> breadcrumbs;					// Something to store breadcrumbs created by followed players
static std::array<Timer, MAX_CLIENTS + 1> afkTicks;		// for how many ms the player hasn't been moving

int follow_target = 0;									// Followed entity, externed for highlight color
static int lastent = 0;

static Timer lastJump{};
static Timer crouch_timer{};
static const int crumb_limit = 64;

static bool inited;

void CFollowBot::Init()
{
	for (int i = 0; i < afkTicks.size(); i++)
	{
		afkTicks[i].update();
	}
	inited = true;
	return;
}

void CFollowBot::checkAFK()
{
	for (int i = 0; i < g_Engine.GetMaxClients(); i++)
	{
		if (i == g_Local.iIndex)
			continue;

		if (!g_Player[i].bAlive)
			continue;

		if (g_Player[i].vVelocity.IsZero())
		{
			afkTicks[i].update();
		}
	}
}

void CFollowBot::addCrumbs(int targetIndx, vec3_t corner = g_Local.vOrigin)
{
	vec3_t ref;

	breadcrumbs.clear();

    auto target = ENTITY(targetIndx);

	if (g_Local.vOrigin != corner)
	{
		vec3_t dist = corner - g_Local.vOrigin;

		int maxiterations = floor(corner.DistTo(g_Local.vOrigin)) / 40;

		for (int i = 0; i < maxiterations; i++)
		{
			breadcrumbs.push_back(g_Local.vOrigin + dist / ref.vectorMax(ref.vectorAbs(dist)) * 40.0f * (i + 1));
		}
	}

	vec3_t dist = target->origin - corner;

	int maxiterations = floor(corner.DistTo(target->origin)) / 40;

	for (int i = 0; i < maxiterations; i++)
	{
		breadcrumbs.push_back(corner + dist / ref.vectorMax(ref.vectorAbs(dist)) * 40.0f * (i + 1));
	}
}

void CFollowBot::addCrumbPair(int Iplayer1, int Iplayer2, std::pair<Vector, Vector> corners)
{
    vec3_t ref;

    Vector corner1 = corners.first;
    Vector corner2 = corners.second;

    auto player1 = ENTITY(Iplayer1);
    auto player2 = ENTITY(Iplayer2);

    {
        Vector dist = (corner1 - player1->origin);
        int maxiterations = floor(corner1.DistTo(player1->origin)) / 40;
        for (int i = 0; i < maxiterations; i++)
        {
            breadcrumbs.push_back(player1->origin + dist / ref.vectorMax(ref.vectorAbs(dist)) * 40.0f * (i + 1));
        }
    }
    {
        Vector dist = corner2 - corner1;
        int maxiterations = floor(corner2.DistTo(corner1)) / 40;
        for (int i = 0; i < maxiterations; i++)
        {
            breadcrumbs.push_back(corner1 + dist / ref.vectorMax(ref.vectorAbs(dist)) * 40.0f * (i + 1));
        }
    }
    {
        Vector dist = player2->origin - corner2;
        int maxiterations = floor(corner2.DistTo(player2->origin)) / 40;
        for (int i = 0; i < maxiterations; i++)
        {
            breadcrumbs.push_back(corner2 + dist / ref.vectorMax(ref.vectorAbs(dist)) * 40.0f * (i + 1));
        }
    }
}

bool CFollowBot::startFollow(int Indx)
{
    auto ent = ENTITY(Indx);
    auto index = ent->index;
    auto localIndex = g_Local.iIndex;

    float distance = g_Player[index].flDist;

    if (IS_VALID(index) && !cvar.Followbot_activation || distance <= cvar.Followbot_activation)
    {
        if (cvar.Followbot_corners)
        {
            Vector indirectOrigin = g_Systems.VischeckCorner(localIndex, index, cvar.Followbot_activation / 2, true);

            std::pair<Vector, Vector> corners;

            if (!indirectOrigin.z && index == lastent)
            {
                corners = g_Systems.VischeckWall(localIndex, index, cvar.Followbot_activation / 2, true);
                if (!corners.first.z || !corners.second.z)
                    return false;

                addCrumbPair(localIndex, index, corners);
                return true;
            }
            if (indirectOrigin.z)
            {
                addCrumbs(index, indirectOrigin);
                return true;
            }
        }
        else
        {
            if (g_Systems.VisCheckEntFromEnt(localIndex, index))
            {
                return true;
            }
        }
    }
    return false;
}

void CFollowBot::Draw()
{
	if (!cvar.Followbot || !cvar.Followbot_draw)
		return;

	if (breadcrumbs.size() < 2)
		return;

    float vecBottom[2], vecTop[2];

    bool behind, behind2;

	for (size_t i = 0; i < breadcrumbs.size() - 1; i++)
	{
        if (g_Visuals.WorldToScreen(breadcrumbs[i], vecTop, behind) && g_Visuals.WorldToScreen(breadcrumbs[i + 1], vecBottom, behind2))
        {
            if (behind)
            {
                vecTop[0] = g_Screen.iWidth - vecTop[0];
                vecTop[1] = g_Screen.iHeight - vecTop[1];
            }

            if (behind2)
            {
                vecBottom[0] = g_Screen.iWidth - vecBottom[0];
                vecBottom[1] = g_Screen.iHeight - vecBottom[1];
            }

            g_Drawing.DrawLine(vecTop[0], vecTop[1], vecBottom[0], vecBottom[1], 255, 255, 255, 255);
        }
	}

    float vecBottom1[2], vecTop1[2];
    bool behind1, behind3;

    if (g_Visuals.WorldToScreen(breadcrumbs[0], vecTop1, behind1) && g_Visuals.WorldToScreen(breadcrumbs[0], vecBottom1, behind3))
    {
        if (behind1)
        {
            vecTop1[0] = g_Screen.iWidth - vecTop1[0];
            vecTop1[1] = g_Screen.iHeight - vecTop1[1];
        }

        if (behind3)
        {
            vecBottom1[0] = g_Screen.iWidth - vecBottom1[0];
            vecBottom1[1] = g_Screen.iHeight - vecBottom1[1];
        }
        g_Drawing.DrawRect(vecTop1[0] - 4, vecTop1[1] - 4, 8, 8, 255, 255, 255, 255);
        g_Drawing.DrawOutlinedRect(vecTop1[0] - 4, vecTop1[1] - 4, 7, 7, 255, 255, 255, 255);
    }
}

bool CFollowBot::isValidTarget(int Indx)
{
	auto i = Indx;

	if (!g_Engine.GetEntityByIndex(i)) return false;
	// Check if already following
	if (i == follow_target) return false;
	// Don't follow yourself
	if (i == g_Local.iIndex) return false;
	// Don't follow dead players
	if (!g_Player[i].bAlive) return false;
	// Don't follow target that was determined as afk
	if (cvar.Followbot_afk && afkTicks[i].check(cvar.Followbot_afk_time)) return false;
	return true;
}

void CFollowBot::CM(struct usercmd_s* cmd)
{
    if (!cvar.Followbot || !g_Local.bAlive)
    {
        follow_target = 0;
        return;
    }
    if (!inited)
        Init();

    if (cvar.Followbot_afk)
        checkAFK();

    // Still good check
    if (follow_target)
    {
        // Overflow protection
        if (breadcrumbs.size() > crumb_limit)
            follow_target = 0;
        else if (!IS_VALID(follow_target) || !ENTITY(follow_target))
            follow_target = 0;
    }

    if (!follow_target)
    {
        breadcrumbs.clear();
        crouch_timer.update();
    }

    bool foundPreferredTarget = false;

    // Target Selection
    if (cvar.Followbot_friends)
    {
        auto& valid_target = follow_target;
        auto ent_count = g_Engine.GetMaxClients();

        if (cvar.Followbot_friends && !foundPreferredTarget)
        {
            if (!g_Player[valid_target].bFriend)
            {
                for (int i = 1; i <= ent_count; i++)
                {
                    auto entity = ENTITY(i);
                    auto index = entity->index;

                    if (!isValidTarget(index))
                        continue;
                    if (g_Player[index].iTeam != g_Local.iTeam)
                        continue;
                    if (!g_Player[index].bFriend)
                        continue;
                    if (startFollow(index))
                    {
                        follow_target = index;
                        foundPreferredTarget = true;
                        break;
                    }
                }
            }
            else
                foundPreferredTarget = true;
        }
    }

    if (!follow_target)
    {
        crouch_timer.update();
    }

    auto *followtar = ENTITY(follow_target);

    if (!IS_VALID(followtar->index) || !g_Player[followtar->index].bAlive)
    {
        follow_target = 0;
        return;
    }

    // Crouch logic
    bool ducked = g_Player[followtar->index].bDucked;

    if (!ducked)
        crouch_timer.update();
    else if (crouch_timer.check(500))
        cmd->buttons |= IN_DUCK;

    if (cvar.Followbot_afk)
    {
        if (afkTicks[follow_target].check(int(cvar.Followbot_afk_time)))
        {
            follow_target = 0;
            return;
        }
    }

    // Update timer on new target
    static Timer idle_time{};
    if (breadcrumbs.empty())
        idle_time.update();

    auto tar_orig = followtar->origin;
    auto loc_orig = g_Local.vOrigin;
    auto dist_to_target = loc_orig.DistTo(tar_orig);

    // If the player is close enough, we dont need to follow the path
    if ((dist_to_target < (float)cvar.Followbot_distance) && g_Systems.VisCheckEntFromEnt(g_Local.iIndex, followtar->index))
    {
        idle_time.update();
    }

    // Prune old and close crumbs that we wont need anymore, update idle
    // timer too
    for (int i = 0; i < breadcrumbs.size(); i++)
    {
        if (loc_orig.DistTo(breadcrumbs.at(i)) < 60.f)
        {
            idle_time.update();
            for (int j = 0; j <= i; j++)
                breadcrumbs.erase(breadcrumbs.begin());
        }
    }

    // New crumbs, we add one if its empty so we have something to follow
    if (breadcrumbs.empty() || (tar_orig.DistTo(breadcrumbs.at(breadcrumbs.size() - 1)) > 40.0F && g_Systems.VectorialDistanceToGround(ENTITY(follow_target)->origin) < 45))
        breadcrumbs.push_back(tar_orig);

    if (dist_to_target > cvar.Followbot_distance)
    {
        // Check for jump
        if (lastJump.check(1000) && (idle_time.check(2000) || g_Systems.VectorialDistanceToGround({ breadcrumbs[0].x, breadcrumbs[0].y, breadcrumbs[0].z + 5 }) > 47))
        {
            cmd->buttons |= IN_JUMP;
            lastJump.update();
        }

        // Basic idle check
        if (idle_time.test_and_set(5000))
        {
            follow_target = 0;
            return;
        }
        g_Systems.WalkTo(breadcrumbs[0], cmd);
    }
    else
        idle_time.update();
}