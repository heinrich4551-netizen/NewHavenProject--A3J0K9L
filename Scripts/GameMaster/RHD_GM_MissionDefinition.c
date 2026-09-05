class RHD_GM_MissionDefinition
{
    string Id;
    string DisplayName;
    string Description;
    bool Enabled;

    void RHD_GM_MissionDefinition(string id, string displayName, string description = "")
    {
        Id = id;
        DisplayName = displayName;
        Description = description;
        Enabled = true;
    }
}
