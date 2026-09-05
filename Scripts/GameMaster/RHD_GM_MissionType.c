enum RHD_GM_MissionType
{
    CONVOY = 0,
    SECURE = 1,
    RECOVERY = 2,
    ELIMINATION = 3,
    CIVILIAN_PROTECTION = 4,
    DEFENSE = 5,
    PATROL = 6
}

class RHD_GM_MissionTypeDefinition : RHD_GM_MissionDefinition
{
    RHD_GM_MissionType Type;

    void RHD_GM_MissionTypeDefinition(string id, string displayName, RHD_GM_MissionType type, string description = "")
    {
        Id = id;
        DisplayName = displayName;
        Description = description;
        Enabled = true;
        Type = type;
    }
}
