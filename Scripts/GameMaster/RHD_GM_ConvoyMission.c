class RHD_GM_ConvoyMission
{
    protected ref RHD_GM_MissionConfig m_Config;
    protected bool m_Running;
    protected string m_MissionId;

    void RHD_GM_ConvoyMission(string missionId = "RHD_CONVOY")
    {
        m_MissionId = missionId;
        m_Config = new RHD_GM_MissionConfig();
        m_Config.ClampValues();
    }

    string GetMissionId()
    {
        return m_MissionId;
    }

    RHD_GM_MissionConfig GetConfig()
    {
        return m_Config;
    }

    bool Start()
    {
        if (!m_Config || !m_Config.Enabled || m_Running)
            return false;

        m_Config.ClampValues();
        m_Running = true;
        return true;
    }

    bool Stop()
    {
        if (!m_Running)
            return false;

        m_Running = false;
        return true;
    }

    bool IsRunning()
    {
        return m_Running;
    }

    // Game Master / scenario integration should call these adapter hooks.
    // They intentionally do not hard-code faction, vehicle, or AI prefab IDs.
    void OnConvoyCreated()
    {
    }

    void OnConvoyReachedDestination()
    {
        Stop();
    }

    void OnConvoyDestroyed()
    {
        Stop();
    }
}
