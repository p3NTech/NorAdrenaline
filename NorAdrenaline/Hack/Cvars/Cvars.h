class CCvars;
class CCvars
{
public:
	void Init();

	bool hide_from_obs;

	bool aim;
	int aim_key;
	bool aim_teammates;
	bool aim_delay_shot;
	float aim_target_selection;
	float aim_hitbox;
	float aim_multi_point;
	bool aim_penetration;
	bool aim_silent;
	bool aim_perfect_silent;
	bool aim_autoscope;
	float aim_fov;
	float aim_hschance;

	bool quick_stop;
	bool quick_stop_duck;

	bool fakelag;
	bool fakelag_while_shooting;
	float fakelag_type;
	float fakelag_move;
	float fakelag_variance;
	float fakelag_limit;

	float brightness;
	float brightness_r;
	float brightness_g;
	float brightness_b;

	bool autopistol;
	bool autoreload;
	bool fastzoom;

	bool nosmoke;
	bool remove_scope;
	bool crosshair;

	float crosshair_r;
	float crosshair_g;
	float crosshair_b;

	float thirdperson;

	bool disable_render_teammates;

	bool bullets_trace;

	float noflash;

	bool esp;
	bool esp_behind;
	bool esp_teammates;

	bool esp_box;
	float esp_box_ct_vis_r;
	float esp_box_ct_vis_g;
	float esp_box_ct_vis_b;
	float esp_box_t_vis_r;
	float esp_box_t_vis_g;
	float esp_box_t_vis_b;
	float esp_box_ct_invis_r;
	float esp_box_ct_invis_g;
	float esp_box_ct_invis_b;
	float esp_box_t_invis_r;
	float esp_box_t_invis_g;
	float esp_box_t_invis_b;
	float esp_box_friends_r;
	float esp_box_friends_g;
	float esp_box_friends_b;
	
	bool esp_box_outline;
	bool esp_name;
	bool esp_trace_angles;

	bool esp_fake;
	bool bypass_trace_blockers;
	bool bypass_valid_blockers;
	float esp_sound_minimum_volume;

	float esp_weapon;
	float esp_weapon_r;
	float esp_weapon_g;
	float esp_weapon_b;

	float esp_world_weapon;
	float esp_world_weapon_r;
	float esp_world_weapon_g;
	float esp_world_weapon_b;

	bool esp_flags;
	bool esp_distance;
	bool esp_hitboxes;
	bool esp_sound;
	bool esp_health;

	float esp_alpha;

	bool esp_line_of_sight;
	float esp_line_of_sight_r;
	float esp_line_of_sight_g;
	float esp_line_of_sight_b;

	bool esp_screen;

	bool esp_shots_fired;

	bool esp_bomb;
	float esp_bomb_r;
	float esp_bomb_g;
	float esp_bomb_b;

	bool hud_clear;

	bool penetration_info;

	float recoil_overlay_r;
	float recoil_overlay_g;
	float recoil_overlay_b;

	float spread_overlay_r;
	float spread_overlay_g;
	float spread_overlay_b;

	bool predict_path;
	bool grenade_trajectory;

	bool chams;
	bool chams_behind_wall;
	float chams_type;

	float chams_t_vis_r;
	float chams_t_vis_g;
	float chams_t_vis_b;

	float chams_t_invis_r;
	float chams_t_invis_g;
	float chams_t_invis_b;

	float chams_ct_vis_r;
	float chams_ct_vis_g;
	float chams_ct_vis_b;

	float chams_ct_invis_r;
	float chams_ct_invis_g;
	float chams_ct_invis_b;

	bool glow_players;
	float glow_type;

	float glow_players_ct_r;
	float glow_players_ct_g;
	float glow_players_ct_b;

	float glow_players_t_r;
	float glow_players_t_g;
	float glow_players_t_b;

	bool spread_overlay;
	bool spread_overlay_old;
	bool recoil_overlay;

	bool draw_aim_fov;
	float draw_aim_fov_r;
	float draw_aim_fov_g;
	float draw_aim_fov_b;

	bool norecoil;
	bool norecoil_visual;

	bool nospread;
	float nospread_method;

	float aa_yaw_while_running;
	float aa_yaw;
	float aa_yaw_static;
	float aa_pitch;
	float aa_edge;
	float aa_legit;

	bool legit_teammates;
	bool trigger_only_zoomed;
	float block_attack_after_kill;
	int trigger_key;

	float menu_legit_global_section;
	float menu_legit_sub_section;

	int menu_key;

	bool rainbow;
	bool rainbow2;
	float rainbow_freq;
	float rainbow_freq2;

	float menu_color_r;
	float menu_color_g;
	float menu_color_b;

	float cheat_global_color_r;
	float cheat_global_color_g;
	float cheat_global_color_b;

	bool bunnyhop;
	bool fakeduck;
	bool knifebot;

	bool TTT;

	bool Followbot;
	bool Followbot_draw;
	bool Followbot_friends;
	bool Followbot_afk;
	float Followbot_afk_time;
	float Followbot_distance;
	float Followbot_activation;
	bool Followbot_corners;

	bool autostrafe;
	bool fastrun_temp;
	bool cstrafe_temp;
	bool gstrafe;
	bool gstrafe_standup;
	bool gstrafe_bhop;
	float strafe_speed;
	bool bhop_nsd;
	bool air_duck;
	bool jump_bug;
	bool fps_boost;
	bool StrafeDir;
	bool movement_all;

	///
	bool teleport_z;
	bool teleport_spectator;
	bool teleport_v2;
	bool lagexploit;
	bool fakelatency;
	float fakeping_amount;
	///
	
	bool spam;
	float spam_timer;

	float name_stealer;

	bool debug;
	bool status;

	bool m_Wheel_up;
	bool m_Wheel_down;

	struct legit_weapons
	{
		bool aim;
		bool aim_head;
		bool aim_chest;
		bool aim_stomach;
		bool aim_quick_stop;
		bool aim_humanize;
		bool aim_spread_compenstation;
		float aim_accuracy;
		float aim_psilent;
		float aim_fov;
		float aim_speed;
		float aim_speed_in_attack;
		float aim_speed_scale_fov;
		float aim_recoil_compensation_pitch;
		float aim_recoil_compensation_yaw;
		float aim_recoil_compensation_after_shots_fired;
		float aim_reaction_time;

		bool trigger;
		bool trigger_head;
		bool trigger_chest;
		bool trigger_stomach;
		bool trigger_penetration;
		float trigger_accuracy;
	} legit[31];
};
extern CCvars cvar;

class CFunctions
{
public:
	void Init();

	void LoadCvars();
	void SaveCvars();

	void AdjustSpeed(double x);
	void ResetSpeed();
	unsigned hash_str(const char* s);
	char* gen_random(const int len);
	DWORD rainbow(float val);
	std::string hexify(unsigned int n);
	char* strToChar(const char* str);
	void DrawCircle(int x, int y, int r);
};
extern CFunctions func;