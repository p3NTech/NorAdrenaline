class CTraitorDetection
{
public:
    std::vector<std::string>    Traitors;
    std::vector<int>            TraitorsIdx;

    void Start(int indx);
    void Update(int idx);
    void Draw();
};
extern CTraitorDetection g_TraitorDetection;