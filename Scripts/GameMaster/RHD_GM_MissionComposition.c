class RHD_GM_MissionComposition
{
    string Id;
    string DisplayName;
    string Description;
    ref RHD_GM_MissionConfig MissionConfig;
    ref RHD_GM_MissionSpawnConfig SpawnConfig;
    ref array<ref RHD_GM_MissionObjective> Objectives;

    void RHD_GM_MissionComposition(string id, string displayName, string description = "")
    {
        Id = id;
        DisplayName = displayName;
        Description = description;
        MissionConfig = new RHD_GM_MissionConfig();
        SpawnConfig = new RHD_GM_MissionSpawnConfig();
        Objectives = new array<ref RHD_GM_MissionObjective>();
    }

    void AddObjective(RHD_GM_MissionObjective objective)
    {
        if (!objective)
            return;

        Objectives.Insert(objective);
    }

    bool AreRequiredObjectivesComplete()
    {
        foreach (RHD_GM_MissionObjective objective : Objectives)
        {
            if (!objective || !objective.Required)
                continue;

            if (!objective.Completed)
                return false;
        }

        return true;
    }

    bool HasRequiredObjectiveFailure()
    {
        foreach (RHD_GM_MissionObjective objective : Objectives)
        {
            if (!objective || !objective.Required)
                continue;

            if (objective.Failed)
                return true;
        }

        return false;
    }
}
