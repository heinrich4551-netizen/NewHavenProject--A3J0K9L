class RHD_GM_ConvoyMissionAdapter : RHD_GM_MissionAdapter
{
    protected ref RHD_GM_MissionSpawnConfig m_SpawnConfig;
    protected bool m_ConvoyAlive;
    protected bool m_ConvoyReachedDestination;

    void RHD_GM_ConvoyMissionAdapter(RHD_GM_MissionSpawnConfig spawnConfig = null)
    {
        m_SpawnConfig = spawnConfig;
        if (m_SpawnConfig)
            m_SpawnConfig.ClampValues();
    }

    void SetSpawnConfig(RHD_GM_MissionSpawnConfig spawnConfig)
    {
        m_SpawnConfig = spawnConfig;
        if (m_SpawnConfig)
            m_SpawnConfig.ClampValues();
    }

    override bool CreateMissionEntities(RHD_GM_MissionInstance instance)
    {
        if (!instance || !m_SpawnConfig)
            return false;

        m_SpawnConfig.ClampValues();
        m_ConvoyAlive = true;
        m_ConvoyReachedDestination = false;

        // Actual entity creation belongs here in the New Haven Workbench
        // integration. Keep prefab/resource selection data-driven.
        return true;
    }

    override bool IsMissionSuccessful(RHD_GM_MissionInstance instance)
    {
        return m_ConvoyReachedDestination && m_ConvoyAlive;
    }

    override bool IsMissionFailed(RHD_GM_MissionInstance instance)
    {
        return !m_ConvoyAlive;
    }

    override void OnMissionStarted(RHD_GM_MissionInstance instance)
    {
        if (!instance)
            return;

        instance.AddTask(new RHD_GM_MissionTask(
            "CONVOY_ESCORT",
            "Escort the convoy",
            "Keep the convoy moving and protect it from hostile forces."
        ));

        instance.AddTask(new RHD_GM_MissionTask(
            "CONVOY_DESTINATION",
            "Reach the destination",
            "Ensure the convoy reaches its configured destination."
        ));
    }

    override void OnMissionCompleted(RHD_GM_MissionInstance instance)
    {
        if (!instance)
            return;

        m_ConvoyReachedDestination = true;
    }

    override void OnMissionFailed(RHD_GM_MissionInstance instance)
    {
        m_ConvoyAlive = false;
    }

    override void CleanupMissionEntities(RHD_GM_MissionInstance instance)
    {
        // New Haven integration removes only entities owned by this mission.
        // Never delete unrelated Game Master or civilian entities here.
    }

    void NotifyConvoyReachedDestination()
    {
        m_ConvoyReachedDestination = true;
    }

    void NotifyConvoyDestroyed()
    {
        m_ConvoyAlive = false;
    }
}
