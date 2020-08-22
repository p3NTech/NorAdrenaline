class CFollowBot
{
public:
	static void addCrumbs(int targetIndx, vec3_t corner);
	static void addCrumbPair(int Iplayer1, int Iplayer2, std::pair<Vector, Vector> corners);
	static bool startFollow(int Indx);
	static void checkAFK();
	static void Draw();
	static bool isValidTarget(int Indx);
	static void CM(struct usercmd_s* cmd);
	static void Init();
}; 
extern CFollowBot g_FollowBot;