class RHD_GM_MissionAdapter
{
    // Adapter contract for scenario-specific entity creation and cleanup.
    // Implement this in the New Haven scenario layer rather than hard-coding
    // faction, vehicle, AI, marker, or task prefab identifiers here.

    bool CreateMissionEntities(RHD_GM_MissionInstance instance)
    {
        return false;
    }

    void CleanupMissionEntities(RHD_GM_MissionInstance instance)
    {
    }

    bool IsMissionSuccessful(RHD_GM_MissionInstance instance)
    {
        return false;
    }

    bool IsMissionFailed(RHD_GM_MissionInstance instance)
    {
        return false;
    }

    void OnMissionStarted(RHD_GM_MissionInstance instance)
    {
    }

    void OnMissionCompleted(RHD_GM_MissionInstance instance)
    {
    }

    void OnMissionFailed(RHD_GM_MissionInstance instance)
    {
    }
}
