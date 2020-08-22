class CSystems;
class CSystems
{
public:
	void PhysicsClipVelocity(Vector &in, const Vector &normal, Vector &out, float overbounce);
	bool PhysicsApplyFriction(Vector &in, Vector &out, float flSurfaceFriction, float flTickRate);
	void DrawDebugArrow(const float x0, const float y0, const float x1, const float y1, const DWORD color, const int alpha);
	float GetEntityGravity();

	bool canReachVector(Vector loc, Vector dest);
	Vector VischeckCorner(int iPlayer1, int iPlayer2, float maxdist, bool checkWalkable);
	bool IsVectorVisible(Vector origin, Vector target, bool enviroment_only);
	bool VisCheckEntFromEnt(int iPlayer1, int iPlayer2);
	bool VisCheckEntFromEntVector(int iPlayer, Vector targetVector);
	std::pair<Vector, Vector> VischeckWall(int iPlayer1, int iPlayer2, float maxdist, bool checkWalkable);
	bool Clamp(double _in, double low, double high);
	std::pair<float, float> ComputeMove(const Vector & a, const Vector & b, usercmd_s * cmd);
	float DistanceToGround(cl_entity_s *ent);
	float VectorialDistanceToGround(Vector origin);
	void KnifeBot(struct usercmd_s *cmd);
	void AutoStrafe(struct usercmd_s *cmd);
	//void strafe_circle(struct usercmd_s *cmd);
	void circle_strafe(float* circle_yaw, struct usercmd_s *cmd);
	float get_move_angle(float speed);
	bool get_closest_plane(Vector* plane, int &ticks);
	bool will_hit_wall(float finish_time, float turn_angle, Vector &plane);
	void BunnyHop(struct usercmd_s *cmd);
	void FakeDuck(struct usercmd_s* cmd);
	void SGS(struct usercmd_s *cmd);
	void GS(struct usercmd_s *cmd);
	void bhop_nsd(struct usercmd_s *cmd);
	void gs_standup(struct usercmd_s *cmd);
	void Fastrun(struct usercmd_s *cmd);
	void RandomizeSteamID();
	void unbanSteamID();

	void cem_TransmitBits();
	void JumpBug(float frametime, struct usercmd_s *cmd);
	void air_duck(struct usercmd_s *cmd);
	void WalkTo(const Vector &vector, struct usercmd_s *cmd);
	void MoveTo(const Vector &vector, CBaseLocal *ent, struct usercmd_s *cmd);
private:
	int DetectStrafeDir(struct usercmd_s *cmd);
};
extern CSystems g_Systems;
