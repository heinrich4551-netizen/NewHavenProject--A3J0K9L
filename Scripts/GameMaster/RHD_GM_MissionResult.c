class RHD_GM_MissionResult
{
    RHD_GM_MissionStatus Status;
    string MissionId;
    string DisplayName;
    float ElapsedSeconds;
    int ObjectivesCompleted;
    int ObjectivesRequired;
    int ReinforcementsDeployed;

    void RHD_GM_MissionResult(RHD_GM_MissionInstance instance)
    {
        Status = RHD_GM_MissionStatus.IDLE;
        MissionId = "";
        DisplayName = "";
        ElapsedSeconds = 0.0;
        ObjectivesCompleted = 0;
        ObjectivesRequired = 0;
        ReinforcementsDeployed = 0;

        if (!instance)
            return;

        Status = instance.GetStatus();
        ElapsedSeconds = instance.GetElapsedSeconds();

        if (instance.GetDefinition())
        {
            MissionId = instance.GetDefinition().Id;
            DisplayName = instance.GetDefinition().DisplayName;
        }

        foreach (RHD_GM_MissionObjective objective : instance.GetObjectives())
        {
            if (!objective || !objective.Required)
                continue;

            ObjectivesRequired++;
            if (objective.Completed)
                ObjectivesCompleted++;
        }

        if (instance.GetReinforcementState())
            ReinforcementsDeployed = instance.GetReinforcementState().GetGroupsSpawned();
    }
}
