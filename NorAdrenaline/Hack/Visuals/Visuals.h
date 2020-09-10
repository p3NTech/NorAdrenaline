class CVisuals;
class CVisuals
{
private:
	void Debug();
	void Status();
	void PlayerESP(unsigned int i);
	void SoundESP();
	void SpectatorList();
	void PredictPath();
	void TraceAnglesESP(unsigned int i);
	void TraceGrenade();
	void ScreenESP(unsigned int i, byte r, byte g, byte b, byte a);
	void Bomb();
	void RemoveScope();
	void Crosshair();
	void DrawAimBotFOV();
	void PenetrationInfo();
	void DrawEntities();
	void DrawFake(int PlayerID, int EntityID);
	void DrawHistory(int i);


	CImageTexture wpn_p228;
	CImageTexture wpn_scout;
	CImageTexture wpn_hegrenade;
	CImageTexture wpn_xm1014;
	CImageTexture wpn_c4;
	CImageTexture wpn_mac10;
	CImageTexture wpn_aug;
	CImageTexture wpn_smokegrenade;
	CImageTexture wpn_elite;
	CImageTexture wpn_fiveseven;
	CImageTexture wpn_ump45;
	CImageTexture wpn_sg550;
	CImageTexture wpn_galil;
	CImageTexture wpn_famas;
	CImageTexture wpn_usp;
	CImageTexture wpn_glock18;
	CImageTexture wpn_awp;
	CImageTexture wpn_mp5n;
	CImageTexture wpn_m249;
	CImageTexture wpn_m3;
	CImageTexture wpn_m4a1;
	CImageTexture wpn_tmp;
	CImageTexture wpn_g3sg1;
	CImageTexture wpn_flashbang;
	CImageTexture wpn_deagle;
	CImageTexture wpn_sg552;
	CImageTexture wpn_ak47;
	CImageTexture wpn_knife;
	CImageTexture wpn_p90;
public:

	std::vector<std::string> spectators;

	void Run();
	void IconInit();
	void Lightmap();
	bool WorldToScreen(float* vOrigin, float* vScreen, bool& behind);
};
extern CVisuals g_Visuals;