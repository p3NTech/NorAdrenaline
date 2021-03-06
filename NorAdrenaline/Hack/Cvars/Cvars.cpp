#include "../../Required.h"
#include <stdio.h> 

CCvars cvar;
CFunctions func;

void CCvars::Init()
{
	hide_from_obs = false;

	aim = false;
	aim_key = -1;

	aim_teammates = false;
	aim_delay_shot = false;
	aim_aa_resolver = false;
	aim_bullet_time = false;
	aim_target_selection = 3;
	aim_hitbox = 1;
	aim_multi_point = 0;
	aim_penetration = false;
	aim_method = 1;
	aim_autoscope = false;
	aim_fov = 1;
	aim_hschance = 33;

	fakelag = false;
	fakelag_while_shooting = false;
	fakelag_type = 3;
	fakelag_move = 3;
	fakelag_variance = 0;
	fakelag_limit = 0;

	brightness = 0;
	brightness_r = 0;
	brightness_g = 0;
	brightness_b = 0;

	quick_stop = false;
	quick_stop_duck = false;

	autopistol = false;
	autoreload = false;
	fastzoom = false;

	nosmoke = false;
	remove_scope = false;
	crosshair = false;

	crosshair_r = 255;
	crosshair_g = 255;
	crosshair_b = 255;

	noflash = 0;
	thirdperson = 0;
	disable_render_teammates = false;
	bullets_trace = false;

	esp = false;
	esp_behind = false;
	esp_teammates = false;

	esp_box = false;
	esp_box_ct_vis_r = 0;
	esp_box_ct_vis_g = 100;
	esp_box_ct_vis_b = 255;
	esp_box_t_vis_r = 255;
	esp_box_t_vis_g = 100;
	esp_box_t_vis_b = 0;
	esp_box_ct_invis_r = 0;
	esp_box_ct_invis_g = 255;
	esp_box_ct_invis_b = 255;
	esp_box_t_invis_r = 255;
	esp_box_t_invis_g = 255;
	esp_box_t_invis_b = 0;
	esp_box_friends_r = 0;
	esp_box_friends_g = 255;
	esp_box_friends_b = 0;

	esp_box_outline = false;
	esp_trace_angles = false;
	esp_name = false;

	esp_fake = false;
	bypass_trace_blockers = true;
	bypass_valid_blockers = false;
	esp_sound_minimum_volume = 0;

	esp_weapon = 1;
	esp_weapon_r = 255;
	esp_weapon_g = 0;
	esp_weapon_b = 255;

	esp_world_weapon = 1;
	esp_world_weapon_r = 255;
	esp_world_weapon_g = 255;
	esp_world_weapon_b = 255;

	esp_shots_fired = false;

	esp_flags = false;
	esp_distance = false;
	esp_hitboxes = false;
	esp_sound = false;
	esp_health = false;

	esp_alpha = 255;

	esp_line_of_sight = false;

	esp_line_of_sight_r = 255;
	esp_line_of_sight_g = 255;
	esp_line_of_sight_b = 255;

	esp_screen = false;

	esp_bomb = false;
	esp_bomb_r = 255;
	esp_bomb_g = 0;
	esp_bomb_b = 0;

	predict_path = false;
	grenade_trajectory = false;

	glow_players = false;
	glow_type = 1;

	glow_players_ct_r = 0;
	glow_players_ct_g = 0;
	glow_players_ct_b = 255;

	glow_players_t_r = 255;
	glow_players_t_g = 0;
	glow_players_t_b = 0;

	hud_clear = false;

	penetration_info = false;

	recoil_overlay_r = 255;
	recoil_overlay_g = 255;
	recoil_overlay_b = 0;

	spread_overlay_r = 255;
	spread_overlay_g = 0;
	spread_overlay_b = 0;

	chams = false;
	chams_behind_wall = false;
	chams_type = 3;

	chams_t_vis_r = 255;
	chams_t_vis_g = 100;
	chams_t_vis_b = 0;

	chams_t_invis_r = 255;
	chams_t_invis_g = 255;
	chams_t_invis_b = 0;

	chams_ct_vis_r = 0;
	chams_ct_vis_g = 100;
	chams_ct_vis_b = 255;

	chams_ct_invis_r = 0;
	chams_ct_invis_g = 255;
	chams_ct_invis_b = 255;

	spread_overlay = false;
	spread_overlay_old = false;
	recoil_overlay = false;

	draw_aim_fov = false;
	draw_aim_fov_r = 255;
	draw_aim_fov_g = 255;
	draw_aim_fov_b = 255;

	norecoil = false;
	norecoil_visual = false;

	nospread = false;
	nospread_method = 1;

	aa_yaw_while_running = 0;
	aa_yaw = 0;
	aa_yaw_static = 0;
	aa_pitch = 0;
	aa_edge = 0;
	aa_legit = 0;

	legit_teammates = false;
	trigger_only_zoomed = false;
	block_attack_after_kill = 0;
	trigger_key = -1;

	menu_legit_global_section = 1;
	menu_legit_sub_section = 1;
	menu_key = 45;

	rainbow = false;
	rainbow_freq = 0.1f;

	menu_color_r = 215;
	menu_color_g = 111;
	menu_color_b = 234;

	cheat_global_color_r = 14;
	cheat_global_color_g = 14;
	cheat_global_color_b = 14;

	friend_color_r = 0;
	friend_color_g = 200;
	friend_color_b = 150;

	priority_color_r = 200;
	priority_color_g = 0;
	priority_color_b = 150;

	bunnyhop = false;
	fakeduck = false;
	knifebot = false;
	knifebot_silent = false;
	knifebot_dist = 64;
	knifebot_aim_hitbox = 1;
	knifebot_attack1 = false;
	autogoto = false;
	autogoto_adjust_speed = false;

	spectator_list = false;

	TTT = false;

	Followbot = false;
	Followbot_draw = false;
	Followbot_friends = false;
	Followbot_afk = false;
	Followbot_afk_time = 2000;
	Followbot_distance = 80;
	Followbot_activation = 1000;
	Followbot_corners = true;

	autostrafe = false;
	fastrun_temp = false;
	cstrafe_temp = false;
	bhop_nsd = false;
	gstrafe = false;
	gstrafe_standup = false;
	gstrafe_bhop = false;
	strafe_speed = 1000;
	air_duck = false;
	jump_bug = false;
	fps_boost = false;

	adjust_speed = false;
	adjust_speed = 0;
	fakelatency = false;
	fakelatency_amount = 0;

	spam = false;
	spam_timer = 0;

	name_stealer = false;

	debug = false;
	status = false;

	m_Wheel_up = false;
	m_Wheel_down = false;
}

static double PRECISION = 0.00000000000001;

char * dtoa(char *s, double n) {
	// handle special cases
	if (isnan(n)) {
		strcpy(s, "nan");
	}
	else if (isinf(n)) {
		strcpy(s, "inf");
	}
	else if (n == 0.0) {
		strcpy(s, "0");
	}
	else {
		int digit, m, m1;
		char *c = s;
		int neg = (n < 0);
		if (neg)
			n = -n;
		// calculate magnitude
		m = log10(n);
		int useExp = (m >= 14 || (neg && m >= 9) || m <= -9);
		if (neg)
			*(c++) = '-';
		// set up for scientific notation
		if (useExp) {
			if (m < 0)
				m -= 1.0;
			n = n / pow(10.0, m);
			m1 = m;
			m = 0;
		}
		if (m < 1.0) {
			m = 0;
		}
		// convert the number
		while (n > PRECISION || m >= 0) {
			double weight = pow(10.0, m);
			if (weight > 0 && !isinf(weight)) {
				digit = floor(n / weight);
				n -= (digit * weight);
				*(c++) = '0' + digit;
			}
			if (m == 0 && n > 0)
				*(c++) = '.';
			m--;
		}
		if (useExp) {
			// convert the exponent
			int i, j;
			*(c++) = 'e';
			if (m1 > 0) {
				*(c++) = '+';
			}
			else {
				*(c++) = '-';
				m1 = -m1;
			}
			m = 0;
			while (m1 > 0) {
				*(c++) = '0' + m1 % 10;
				m1 /= 10;
				m++;
			}
			c -= m;
			for (i = 0, j = m - 1; i<j; i++, j--) {
				// swap without temporary
				c[i] ^= c[j];
				c[j] ^= c[i];
				c[i] ^= c[j];
			}
			c += m;
		}
		*(c) = '\0';
	}
	return s;
}

void CFunctions::SaveCvars()
{
	char *Section = "Settings";
	
	char s[32];

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim", dtoa(s, cvar.aim));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_teammates", dtoa(s, cvar.aim_teammates));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_delay_shot", dtoa(s, cvar.aim_delay_shot));

	if (cvar.aim_method != 3)
		g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_bullet_time", dtoa(s, cvar.aim_bullet_time));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_target_selection", dtoa(s, cvar.aim_target_selection));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_hitbox", dtoa(s, cvar.aim_hitbox));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_multi_point", dtoa(s, cvar.aim_multi_point));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_penetration", dtoa(s, cvar.aim_penetration));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_method", dtoa(s, cvar.aim_method));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_autoscope", dtoa(s, cvar.aim_autoscope));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_fov", dtoa(s, cvar.aim_fov));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_key", dtoa(s, cvar.aim_key));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "fakelag", dtoa(s, cvar.fakelag));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "fakelag_while_shooting", dtoa(s, cvar.fakelag_while_shooting));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "fakelag_type", dtoa(s, cvar.fakelag_type));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "fakelag_move", dtoa(s, cvar.fakelag_move));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "fakelag_variance", dtoa(s, cvar.fakelag_variance));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "fakelag_limit", dtoa(s, cvar.fakelag_limit));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "brightness", dtoa(s, cvar.brightness));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "brightness_r", dtoa(s, cvar.brightness_r));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "brightness_g", dtoa(s, cvar.brightness_g));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "brightness_b", dtoa(s, cvar.brightness_b));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "quick_stop", dtoa(s, cvar.quick_stop));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "quick_stop_duck", dtoa(s, cvar.quick_stop_duck));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "autopistol", dtoa(s, cvar.autopistol));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "autoreload", dtoa(s, cvar.autoreload));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "fastzoom", dtoa(s, cvar.fastzoom));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "nosmoke", dtoa(s, cvar.nosmoke));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "remove_scope", dtoa(s, cvar.remove_scope));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "crosshair", dtoa(s, cvar.crosshair));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "crosshair_r", dtoa(s, cvar.crosshair_r));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "crosshair_g", dtoa(s, cvar.crosshair_g));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "crosshair_b", dtoa(s, cvar.crosshair_b));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "noflash", dtoa(s, cvar.noflash));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "thirdperson", dtoa(s, cvar.thirdperson));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "disable_render_teammates", dtoa(s, cvar.disable_render_teammates));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "bullets_trace", dtoa(s, cvar.bullets_trace));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp", dtoa(s, cvar.esp));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_behind", dtoa(s, cvar.esp_behind));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_teammates", dtoa(s, cvar.esp_teammates));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_box", dtoa(s, cvar.esp_box));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_box_ct_vis_r", dtoa(s, cvar.esp_box_ct_vis_r));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_box_ct_vis_g", dtoa(s, cvar.esp_box_ct_vis_g));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_box_ct_vis_b", dtoa(s, cvar.esp_box_ct_vis_b));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_box_t_vis_r", dtoa(s, cvar.esp_box_t_vis_r));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_box_t_vis_g", dtoa(s, cvar.esp_box_t_vis_g));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_box_t_vis_b", dtoa(s, cvar.esp_box_t_vis_b));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_box_ct_invis_r", dtoa(s, cvar.esp_box_ct_invis_r));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_box_ct_invis_g", dtoa(s, cvar.esp_box_ct_invis_g));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_box_ct_invis_b", dtoa(s, cvar.esp_box_ct_invis_b));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_box_t_invis_r", dtoa(s, cvar.esp_box_t_invis_r));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_box_t_invis_g", dtoa(s, cvar.esp_box_t_invis_g));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_box_t_invis_b", dtoa(s, cvar.esp_box_t_invis_b));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_box_friends_r", dtoa(s, cvar.esp_box_friends_r));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_box_friends_g", dtoa(s, cvar.esp_box_friends_g));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_box_friends_b", dtoa(s, cvar.esp_box_friends_b));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_box_outline", dtoa(s, cvar.esp_box_outline));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_name", dtoa(s, cvar.esp_name));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_fake", dtoa(s, cvar.esp_fake));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "bypass_trace_blockers", dtoa(s, cvar.bypass_trace_blockers));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "bypass_valid_blockers", dtoa(s, cvar.bypass_valid_blockers));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_sound_minimum_volume", dtoa(s, cvar.esp_sound_minimum_volume));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_weapon", dtoa(s, cvar.esp_weapon));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_weapon_r", dtoa(s, cvar.esp_weapon_r));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_weapon_g", dtoa(s, cvar.esp_weapon_g));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_weapon_b", dtoa(s, cvar.esp_weapon_b));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_world_weapon", dtoa(s, cvar.esp_world_weapon));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_world_weapon_r", dtoa(s, cvar.esp_world_weapon_r));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_world_weapon_g", dtoa(s, cvar.esp_world_weapon_g));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_world_weapon_b", dtoa(s, cvar.esp_world_weapon_b));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_shots_fired", dtoa(s, cvar.esp_shots_fired));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_flags", dtoa(s, cvar.esp_flags));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_distance", dtoa(s, cvar.esp_distance));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_hitboxes", dtoa(s, cvar.esp_hitboxes));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_sound", dtoa(s, cvar.esp_sound));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_health", dtoa(s, cvar.esp_health));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_alpha", dtoa(s, cvar.esp_alpha));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_line_of_sight", dtoa(s, cvar.esp_line_of_sight));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_line_of_sight_r", dtoa(s, cvar.esp_line_of_sight_r));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_line_of_sight_g", dtoa(s, cvar.esp_line_of_sight_g));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_line_of_sight_b", dtoa(s, cvar.esp_line_of_sight_b));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_screen", dtoa(s, cvar.esp_screen));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_bomb", dtoa(s, cvar.esp_bomb));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_bomb_r", dtoa(s, cvar.esp_bomb_r));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_bomb_g", dtoa(s, cvar.esp_bomb_g));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "esp_bomb_b", dtoa(s, cvar.esp_bomb_b));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "grenade_trajectory", dtoa(s, cvar.grenade_trajectory));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "predict_path", dtoa(s, cvar.predict_path));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "glow_players", dtoa(s, cvar.glow_players));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "glow_players_ct_r", dtoa(s, cvar.glow_players_ct_r));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "glow_players_ct_g", dtoa(s, cvar.glow_players_ct_g));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "glow_players_ct_b", dtoa(s, cvar.glow_players_ct_b));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "glow_players_t_r", dtoa(s, cvar.glow_players_t_r));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "glow_players_t_g", dtoa(s, cvar.glow_players_t_g));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "glow_players_t_b", dtoa(s, cvar.glow_players_t_b));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "hud_clear", dtoa(s, cvar.hud_clear));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "penetration_info", dtoa(s, cvar.penetration_info));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "recoil_overlay_r", dtoa(s, cvar.recoil_overlay_r));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "recoil_overlay_g", dtoa(s, cvar.recoil_overlay_g));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "recoil_overlay_b", dtoa(s, cvar.recoil_overlay_b));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "spread_overlay_r", dtoa(s, cvar.spread_overlay_r));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "spread_overlay_g", dtoa(s, cvar.spread_overlay_g));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "spread_overlay_b", dtoa(s, cvar.spread_overlay_b));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "chams", dtoa(s, cvar.chams));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "chams_behind_wall", dtoa(s, cvar.chams_behind_wall));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "chams_type", dtoa(s, cvar.chams_type));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "chams_t_vis_r", dtoa(s, cvar.chams_t_vis_r));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "chams_t_vis_g", dtoa(s, cvar.chams_t_vis_g));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "chams_t_vis_b", dtoa(s, cvar.chams_t_vis_b));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "chams_t_invis_r", dtoa(s, cvar.chams_t_invis_r));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "chams_t_invis_g", dtoa(s, cvar.chams_t_invis_g));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "chams_t_invis_b", dtoa(s, cvar.chams_t_invis_b));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "chams_ct_vis_r", dtoa(s, cvar.chams_ct_vis_r));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "chams_ct_vis_g", dtoa(s, cvar.chams_ct_vis_g));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "chams_ct_vis_b", dtoa(s, cvar.chams_ct_vis_b));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "chams_ct_invis_r", dtoa(s, cvar.chams_ct_invis_r));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "chams_ct_invis_g", dtoa(s, cvar.chams_ct_invis_g));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "chams_ct_invis_b", dtoa(s, cvar.chams_ct_invis_b));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "spread_overlay", dtoa(s, cvar.spread_overlay));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "spread_overlay_old", dtoa(s, cvar.spread_overlay_old));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "recoil_overlay", dtoa(s, cvar.recoil_overlay));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "draw_aim_fov", dtoa(s, cvar.draw_aim_fov));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "draw_aim_fov_r", dtoa(s, cvar.draw_aim_fov_r));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "draw_aim_fov_g", dtoa(s, cvar.draw_aim_fov_g));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "draw_aim_fov_b", dtoa(s, cvar.draw_aim_fov_b));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "norecoil", dtoa(s, cvar.norecoil));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "norecoil_visual", dtoa(s, cvar.norecoil_visual));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "nospread", dtoa(s, cvar.nospread));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "nospread_method", dtoa(s, cvar.nospread_method));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aa_yaw_while_running", dtoa(s, cvar.aa_yaw_while_running));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aa_yaw", dtoa(s, cvar.aa_yaw));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aa_yaw_static", dtoa(s, cvar.aa_yaw_static));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aa_pitch", dtoa(s, cvar.aa_pitch));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aa_edge", dtoa(s, cvar.aa_edge));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "hide_from_obs", dtoa(s, cvar.hide_from_obs));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "menu_legit_global_section", dtoa(s, cvar.menu_legit_global_section));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "menu_legit_sub_section", dtoa(s, cvar.menu_legit_sub_section));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "rainbow", dtoa(s, cvar.rainbow));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "rainbow2", dtoa(s, cvar.rainbow2));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "rainbow_freq", dtoa(s, cvar.rainbow_freq));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "rainbow_freq2", dtoa(s, cvar.rainbow_freq2));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "menu_color_r", dtoa(s, cvar.menu_color_r));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "menu_color_g", dtoa(s, cvar.menu_color_g));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "menu_color_b", dtoa(s, cvar.menu_color_b));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "cheat_global_color_r", dtoa(s, cvar.cheat_global_color_r));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "cheat_global_color_g", dtoa(s, cvar.cheat_global_color_g));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "cheat_global_color_b", dtoa(s, cvar.cheat_global_color_b));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "menu_key", dtoa(s, cvar.menu_key));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "bunnyhop", dtoa(s, cvar.bunnyhop));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "autostrafe", dtoa(s, cvar.autostrafe));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "gstrafe_bhop", dtoa(s, cvar.gstrafe_bhop));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "bhop_nsd", dtoa(s, cvar.bhop_nsd));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "gstrafe_standup", dtoa(s, cvar.gstrafe_standup));;
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "jump_bug", dtoa(s, cvar.jump_bug));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "knifebot", dtoa(s, cvar.knifebot));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "autogoto", dtoa(s, cvar.autogoto));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "autogoto_adjust_speed", dtoa(s, cvar.autogoto_adjust_speed));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "name_stealer", dtoa(s, cvar.name_stealer));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "fake_latency_amount", dtoa(s, cvar.fakelatency_amount));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "adjust_speed_amount", dtoa(s, cvar.adjust_speed_amount));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "legit_teammates", dtoa(s, cvar.legit_teammates));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "block_attack_after_kill", dtoa(s, cvar.block_attack_after_kill));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "trigger_only_zoomed", dtoa(s, cvar.trigger_only_zoomed));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "trigger_key", dtoa(s, cvar.trigger_key));

	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "TTT", dtoa(s, cvar.TTT));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "Aimbot configuration", dtoa(s, cvar.status));
	g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_hschance", dtoa(s, cvar.aim_hschance));

	for (int i = 1; i < 31; i++)
	{
		if (i == 2 || i == 4 || i == 6 || i == 9 || i == 25) continue;

		std::string loh = "WEAPON_";
		loh.append(dtoa(s, i));
		Section = (char*)loh.c_str();
		g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim", dtoa(s, cvar.legit[i].aim));
		g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_head", dtoa(s, cvar.legit[i].aim_head));
		g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_chest", dtoa(s, cvar.legit[i].aim_chest));
		g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_stomach", dtoa(s, cvar.legit[i].aim_stomach));
		g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_quick_stop", dtoa(s, cvar.legit[i].aim_quick_stop));
		g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_accuracy", dtoa(s, cvar.legit[i].aim_accuracy));
		g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_psilent", dtoa(s, cvar.legit[i].aim_psilent));
		g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_humanize", dtoa(s, cvar.legit[i].aim_humanize));
		g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_spread_compenstation", dtoa(s, cvar.legit[i].aim_spread_compenstation));
		g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_fov", dtoa(s, cvar.legit[i].aim_fov));
		g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_speed", dtoa(s, cvar.legit[i].aim_speed));
		g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_speed_in_attack", dtoa(s, cvar.legit[i].aim_speed_in_attack));
		g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_speed_scale_fov", dtoa(s, cvar.legit[i].aim_speed_scale_fov));
		g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_recoil_compensation_pitch", dtoa(s, cvar.legit[i].aim_recoil_compensation_pitch));
		g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_recoil_compensation_yaw", dtoa(s, cvar.legit[i].aim_recoil_compensation_yaw));
		g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_recoil_compensation_after_shots_fired", dtoa(s, cvar.legit[i].aim_recoil_compensation_after_shots_fired));
		g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "aim_reaction_time", dtoa(s, cvar.legit[i].aim_reaction_time));

		g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "trigger", dtoa(s, cvar.legit[i].trigger));
		g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "trigger_head", dtoa(s, cvar.legit[i].trigger_head));
		g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "trigger_chest", dtoa(s, cvar.legit[i].trigger_chest));
		g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "trigger_stomach", dtoa(s, cvar.legit[i].trigger_stomach));
		g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "trigger_penetration", dtoa(s, cvar.legit[i].trigger_penetration));
		g_Utils.cIniWrite(g_pGlobals.IniPath, Section, "trigger_accuracy", dtoa(s, cvar.legit[i].trigger_accuracy));
	}
}

void CFunctions::LoadCvars()
{
	if (!g_Utils.bFileExists(g_pGlobals.IniPath)) return;

	char *Section = "Settings";

	char s[32];

	cvar.hide_from_obs = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "hide_from_obs", "0"));

	cvar.aim = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim", "0"));
	cvar.aim_delay_shot = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_delay_shot", "0"));
	cvar.aim_bullet_time = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_bullet_time", "0"));
	cvar.aim_teammates = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_teammates", "0"));
	cvar.aim_target_selection = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_target_selection", "0"));
	cvar.aim_hitbox = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_hitbox", "0"));
	cvar.aim_multi_point = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_multi_point", "0"));
	cvar.aim_penetration = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_penetration", "0"));
	cvar.aim_method = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_method", "0"));
	cvar.aim_autoscope = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_autoscope", "0"));
	cvar.aim_key = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_key", "-1"));
	cvar.aim_fov = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_fov", "0"));

	cvar.fakelag = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "fakelag", "0"));
	cvar.fakelag_while_shooting = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "fakelag_while_shooting", "0"));
	cvar.fakelag_type = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "fakelag_type", "0"));
	cvar.fakelag_move = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "fakelag_move", "0"));
	cvar.fakelag_variance = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "fakelag_variance", "0"));
	cvar.fakelag_limit = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "fakelag_limit", "0"));

	cvar.brightness = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "brightness", "0"));
	cvar.brightness_r = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "brightness_r", "0"));
	cvar.brightness_g = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "brightness_g", "0"));
	cvar.brightness_b = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "brightness_b", "0"));

	cvar.quick_stop = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "quick_stop", "0"));
	cvar.quick_stop_duck = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "quick_stop_duck", "0"));
	
	cvar.autopistol = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "autopistol", "0"));
	cvar.autoreload = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "autoreload", "0"));
	cvar.fastzoom = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "fastzoom", "0"));

	cvar.nosmoke = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "nosmoke", "0"));
	cvar.remove_scope = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "remove_scope", "0"));
	cvar.crosshair = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "crosshair", "0"));

	cvar.crosshair_r = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "crosshair_r", "0"));
	cvar.crosshair_g = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "crosshair_g", "0"));
	cvar.crosshair_b = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "crosshair_b", "0"));

	cvar.noflash = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "noflash", "0"));
	cvar.thirdperson = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "thirdperson", "0"));
	cvar.disable_render_teammates = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "disable_render_teammates", "0"));
	cvar.bullets_trace = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "bullets_trace", "0"));

	cvar.esp = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp", "0"));
	cvar.esp_behind = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_behind", "0"));
	cvar.esp_teammates = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_teammates", "0"));

	cvar.esp_box = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_box", "0"));
	cvar.esp_box_ct_vis_r = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_box_ct_vis_r", "0"));
	cvar.esp_box_ct_vis_g = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_box_ct_vis_g", "0"));
	cvar.esp_box_ct_vis_b = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_box_ct_vis_b", "0"));
		cvar.esp_box_t_vis_r = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_box_t_vis_r", "0"));
	cvar.esp_box_t_vis_g = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_box_t_vis_g", "0"));
	cvar.esp_box_t_vis_b = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_box_t_vis_b", "0"));
	cvar.esp_box_ct_invis_r = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_box_ct_invis_r", "0"));
	cvar.esp_box_ct_invis_g = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_box_ct_invis_g", "0"));
	cvar.esp_box_ct_invis_b = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_box_ct_invis_b", "0"));
	cvar.esp_box_t_invis_r = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_box_t_invis_r", "0"));
	cvar.esp_box_t_invis_g = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_box_t_invis_g", "0"));
	cvar.esp_box_t_invis_b = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_box_t_invis_b", "0"));
	cvar.esp_box_friends_r = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_box_friends_r", "0"));
	cvar.esp_box_friends_g = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_box_friends_g", "0"));
	cvar.esp_box_friends_b = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_box_friends_b", "0"));

	cvar.esp_box_outline = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_box_outline", "0"));
	cvar.esp_name = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_name", "0"));

	cvar.esp_fake = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_fake", "0"));
	cvar.bypass_trace_blockers = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "bypass_trace_blockers", "0"));
	cvar.bypass_valid_blockers = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "bypass_valid_blockers", "0"));
	cvar.esp_sound_minimum_volume = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_sound_minimum_volume", "0"));

	cvar.esp_weapon = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_weapon", "0"));
	cvar.esp_weapon_r = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_weapon_r", "0"));
	cvar.esp_weapon_g = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_weapon_g", "0"));
	cvar.esp_weapon_b = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_weapon_b", "0"));

	cvar.esp_world_weapon = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_world_weapon", "0"));
	cvar.esp_world_weapon_r = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_world_weapon_r", "0"));
	cvar.esp_world_weapon_g = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_world_weapon_g", "0"));
	cvar.esp_world_weapon_b = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_world_weapon_b", "0"));

	cvar.esp_shots_fired = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_shots_fired", "0"));

	cvar.esp_flags = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_flags", "0"));
	cvar.esp_distance = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_distance", "0"));
	cvar.esp_hitboxes = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_hitboxes", "0"));
	cvar.esp_sound = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_sound", "0"));
	cvar.esp_health = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_health", "0"));

	cvar.esp_alpha = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_alpha", "0"));

	cvar.esp_line_of_sight = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_line_of_sight", "0"));

	cvar.esp_line_of_sight_r = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_line_of_sight_r", "0"));
	cvar.esp_line_of_sight_g = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_line_of_sight_g", "0"));
	cvar.esp_line_of_sight_b = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_line_of_sight_b", "0"));

	cvar.esp_screen = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_screen", "0"));

	cvar.esp_bomb = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_bomb", "0"));
	cvar.esp_bomb_r = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_bomb_r", "0"));
	cvar.esp_bomb_g = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_bomb_g", "0"));
	cvar.esp_bomb_b = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "esp_bomb_b", "0"));

	cvar.predict_path = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "predict_path", "0"));
	cvar.grenade_trajectory = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "grenade_trajectory", "0"));

	cvar.glow_players = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "glow_players", "0"));

	cvar.glow_players_ct_r = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "glow_players_ct_r", "0"));
	cvar.glow_players_ct_g = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "glow_players_ct_g", "0"));
	cvar.glow_players_ct_b = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "glow_players_ct_b", "0"));

	cvar.glow_players_t_r = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "glow_players_t_r", "0"));
	cvar.glow_players_t_g = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "glow_players_t_g", "0"));
	cvar.glow_players_t_b = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "glow_players_t_b", "0"));

	cvar.hud_clear = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "hud_clear", "0"));

	cvar.penetration_info = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "penetration_info", "0"));

	cvar.recoil_overlay_r = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "recoil_overlay_r", "0"));
	cvar.recoil_overlay_g = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "recoil_overlay_g", "0"));
	cvar.recoil_overlay_b = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "recoil_overlay_b", "0"));

	cvar.spread_overlay_r = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "spread_overlay_r", "0"));
	cvar.spread_overlay_g = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "spread_overlay_g", "0"));
	cvar.spread_overlay_b = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "spread_overlay_b", "0"));

	cvar.chams = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "chams", "0"));
	cvar.chams_behind_wall = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "chams_behind_wall", "0"));
	cvar.chams_type = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "chams_type", "0"));

	cvar.chams_t_vis_r = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "chams_t_vis_r", "0"));
	cvar.chams_t_vis_g = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "chams_t_vis_g", "0"));
	cvar.chams_t_vis_b = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "chams_t_vis_b", "0"));

	cvar.chams_t_invis_r = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "chams_t_invis_r", "0"));
	cvar.chams_t_invis_g = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "chams_t_invis_g", "0"));
	cvar.chams_t_invis_b = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "chams_t_invis_b", "0"));

	cvar.chams_ct_vis_r = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "chams_ct_vis_r", "0"));
	cvar.chams_ct_vis_g = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "chams_ct_vis_g", "0"));
	cvar.chams_ct_vis_b = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "chams_ct_vis_b", "0"));

	cvar.chams_ct_invis_r = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "chams_ct_invis_r", "0"));
	cvar.chams_ct_invis_g = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "chams_ct_invis_g", "0"));
	cvar.chams_ct_invis_b = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "chams_ct_invis_b", "0"));

	cvar.spread_overlay = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "spread_overlay", "0"));
	cvar.spread_overlay_old = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "spread_overlay_old", "0"));
	cvar.recoil_overlay = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "recoil_overlay", "0"));

	cvar.draw_aim_fov = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "draw_aim_fov", "0"));
	cvar.draw_aim_fov_r = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "draw_aim_fov_r", "0"));
	cvar.draw_aim_fov_g = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "draw_aim_fov_g", "0"));
	cvar.draw_aim_fov_b = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "draw_aim_fov_b", "0"));

	cvar.norecoil = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "norecoil", "0"));
	cvar.norecoil_visual = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "norecoil_visual", "0"));

	cvar.nospread = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "nospread", "0"));
	cvar.nospread_method = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "nospread_method", "0"));

	cvar.aa_yaw_while_running = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aa_yaw_while_running", "0"));
	cvar.aa_yaw = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aa_yaw", "0"));
	cvar.aa_yaw_static = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aa_yaw_static", "0"));
	cvar.aa_pitch = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aa_pitch", "0"));
	cvar.aa_edge = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aa_edge", "0"));

	cvar.menu_legit_global_section = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "menu_legit_global_section", "0"));
	cvar.menu_legit_sub_section = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "menu_legit_sub_section", "0"));
	
	cvar.rainbow = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "rainbow", "0"));
	cvar.rainbow2 = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "rainbow2", "0"));
	cvar.rainbow_freq = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "rainbow_freq", "0"));
	cvar.rainbow_freq2 = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "rainbow_freq2", "0"));
	cvar.menu_color_r = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "menu_color_r", "215"));
	cvar.menu_color_g = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "menu_color_g", "111"));
	cvar.menu_color_b = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "menu_color_b", "234"));
	cvar.cheat_global_color_r = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "cheat_global_color_r", "255"));
	cvar.cheat_global_color_g = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "cheat_global_color_g", "255"));
	cvar.cheat_global_color_b = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "cheat_global_color_b", "255"));

	cvar.menu_key = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "menu_key", "45"));

	cvar.name_stealer = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "name_stealer", "0"));

	cvar.legit_teammates = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "legit_teammates", "0"));
	cvar.block_attack_after_kill = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "block_attack_after_kill", "0"));
	cvar.trigger_only_zoomed = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "trigger_only_zoomed", "0"));
	cvar.trigger_key = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "trigger_key", "-1"));

	cvar.bunnyhop = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "bunnyhop", "0"));
	cvar.knifebot = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "knifebot", "0"));
	cvar.autogoto = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "autogoto", "0"));
	cvar.autogoto_adjust_speed = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "autogoto_adjust_speed", "0"));

	// add followbot cvars, im lazy

	cvar.bhop_nsd = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "bhop_nsd", "0"));
	cvar.jump_bug = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "jump_bug", "0"));
	cvar.gstrafe_bhop = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "gstrafe_bhop", "0"));
	cvar.gstrafe_standup = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "gstrafe_standup", "0"));
	cvar.fakelatency_amount = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "fake_latency_amount", "0"));
	cvar.adjust_speed_amount = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "adjust_speed_amount", "0"));

	cvar.TTT = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "TTT", "0"));
	cvar.status = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "Aimbot configuration", "0"));
	cvar.aim_hschance = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_hschance", "0"));

	for (int i = 1; i < 31; i++)
	{
		if (i == 2 || i == 4 || i == 6 || i == 9 || i == 25) continue;

		std::string loh = "WEAPON_";
		loh.append(dtoa(s, i));
		Section = (char*)loh.c_str();

		cvar.legit[i].aim = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim", "0"));
		cvar.legit[i].aim_head = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_head", "0"));
		cvar.legit[i].aim_chest = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_chest", "0"));
		cvar.legit[i].aim_stomach = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_stomach", "0"));
		cvar.legit[i].aim_quick_stop = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_quick_stop", "0"));
		cvar.legit[i].aim_spread_compenstation = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_spread_compenstation", "0"));
		cvar.legit[i].aim_fov = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_fov", "0"));
		cvar.legit[i].aim_speed = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_speed", "0"));
		cvar.legit[i].aim_speed_in_attack = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_speed_in_attack", "0"));
		cvar.legit[i].aim_speed_scale_fov = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_speed_scale_fov", "0"));
		cvar.legit[i].aim_humanize = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_humanize", "0"));
		cvar.legit[i].aim_recoil_compensation_pitch = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_recoil_compensation_pitch", "0"));
		cvar.legit[i].aim_recoil_compensation_yaw = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_recoil_compensation_yaw", "0"));
		cvar.legit[i].aim_recoil_compensation_after_shots_fired = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_recoil_compensation_after_shots_fired", "0"));
		cvar.legit[i].aim_reaction_time = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_reaction_time", "0"));
		cvar.legit[i].aim_accuracy = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_accuracy", "0"));
		cvar.legit[i].aim_psilent = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "aim_psilent", "0"));

		cvar.legit[i].trigger = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "trigger", "0"));
		cvar.legit[i].trigger_head = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "trigger_head", "0"));
		cvar.legit[i].trigger_chest = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "trigger_chest", "0"));
		cvar.legit[i].trigger_stomach = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "trigger_stomach", "0"));
		cvar.legit[i].trigger_penetration = atoi(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "trigger_penetration", "0"));
		cvar.legit[i].trigger_accuracy = atof(g_Utils.cIniRead(g_pGlobals.IniPath, Section, "trigger_accuracy", "0"));
	}
}

void CFunctions::Init()
{

}

void CFunctions::AdjustSpeed(double x)
{
	if (x != 1.0f)
	{
		g_pGlobals.bResetSpeed = true;
	}

	static DWORD SpeedPtr;
	int dwSpeedptr = g_Offsets.dwSpeedPointer;
	if (g_Offsets.dwSpeedPointer == 0)
	{
		dwSpeedptr = SpeedPtr;
	}
	static double LastSpeed = 1;
	if (x != LastSpeed)
	{
		*(double*)dwSpeedptr = (x * 1000);
		LastSpeed = x;
	}
}

void CFunctions::ResetSpeed()
{
	g_pGlobals.bResetSpeed = false;

	AdjustSpeed(1.0f);
}

unsigned CFunctions::hash_str(const char* s)
{
	unsigned h = FIRSTH;
	while (*s)
	{
		h = (h * A) ^ (s[0] * B);
		s++;
	}
	return h; // or return h % C;
}

char* CFunctions::gen_random(const int len)
{
	char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
					  'h', 'i', 'j', 'k', 'l', 'm', 'n',
					  'o', 'p', 'q', 'r', 's', 't', 'u',
					  'v', 'w', 'x', 'y', 'z' };

	char* res = "";
	for (int i = 0; i < len; i++)
		res = res + alphabet[rand() % 26];

	return res;
}

DWORD CFunctions::rainbow(float val)
{
	static uint32_t cnt = 0;
	float freq = val / 100;

	int r = 0, g = 0, b = 0, a = 0;
	r = std::sin(freq * cnt + 0) * 127 + 128;
	g = std::sin(freq * cnt + 2) * 127 + 128;
	b = std::sin(freq * cnt + 4) * 127 + 128;
	a = 255;

	// Probably redundant
	if (cnt++ >= (uint32_t)-1) cnt = 0;

	return COLORCODE(r, g, b, a);
}

std::string CFunctions::hexify(unsigned int n)
{
	std::string res;

	do
	{
		res += "0123456789ABCDEF"[n % 16];
		n >>= 4;
	} while (n);

	return std::string(res.rbegin(), res.rend());
}

char* CFunctions::strToChar(const char* str)
{
	char parsed = 0;
	for (int i = 0; i < 8; i++)
	{
		if (str[i] == '1')
		{
			parsed |= 1 << (7 - i);
		}
	}
	return &parsed;
}

const char* CFunctions::ConvertToUTF8(const wchar_t* pStr)
{
	static char szBuf[1024];
	WideCharToMultiByte(CP_UTF8, 0, pStr, -1, szBuf, sizeof(szBuf), NULL, NULL);
	return szBuf;
}

void CFunctions::toClipboard(const std::string& s)
{
	OpenClipboard(0);
	EmptyClipboard();
	const size_t len = strlen(s.c_str()) + 1;
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, len);
	if (!hg)
	{
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), len);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}

void CFunctions::DrawCircle(int x, int y, int r)
{
	//glBegin(GL_POINTS);

	//glColor3ub(134, 202, 117);
	/*
	double i, angle, x1, y1;

	for (i = 0; i < 360; i += 0.01)
	{
		angle = i;
		x1 = r * cos(angle * PI / 180);
		y1 = r * sin(angle * PI / 180);
		glVertex2d(x + x1, y + y1);
	}
	*/

	double dtheta = 2 * M_PI / 8 / r;
	int x1 = x + r, x2, y1 = y, y2;
	int n = 2 * M_PI / dtheta;
	for (int i = 1; i < n; i++)
	{
		double theta = i * dtheta;
		x2 = int(x + r * cos(theta)); y2 = int(y + r * sin(theta));
		g_Drawing.DrawLine(x1, y1, x2, y2, cvar.draw_aim_fov_r, cvar.draw_aim_fov_g, cvar.draw_aim_fov_b, cvar.esp_alpha);
		x1 = x2; y1 = y2;
	}

	//glEnd();
}