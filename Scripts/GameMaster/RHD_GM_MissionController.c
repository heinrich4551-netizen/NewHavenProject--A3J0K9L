class RHD_GM_MissionController
{
    protected ref array<ref RHD_GM_MissionInstance> m_ActiveMissions;
    protected RHD_GM_MissionAdapter m_Adapter;

    void RHD_GM_MissionController(RHD_GM_MissionAdapter adapter = null)
    {
        m_ActiveMissions = new array<ref RHD_GM_MissionInstance>();
        m_Adapter = adapter;
    }

    void SetAdapter(RHD_GM_MissionAdapter adapter)
    {
        m_Adapter = adapter;
    }

    array<ref RHD_GM_MissionInstance> GetActiveMissions()
    {
        return m_ActiveMissions;
    }

    RHD_GM_MissionInstance StartMission(RHD_GM_MissionDefinition definition, RHD_GM_MissionConfig config)
    {
        if (!definition || !config || !definition.Enabled || !config.Enabled)
            return null;

        config.ClampValues();

        RHD_GM_MissionInstance instance = new RHD_GM_MissionInstance(definition, config);

        if (m_Adapter && !m_Adapter.CreateMissionEntities(instance))
            return null;

        instance.Start();
        m_ActiveMissions.Insert(instance);

        if (m_Adapter)
            m_Adapter.OnMissionStarted(instance);

        return instance;
    }

    void StopMission(RHD_GM_MissionInstance instance, bool failed = false)
    {
        if (!instance || !instance.IsRunning())
            return;

        instance.Stop();

        if (m_Adapter)
        {
            if (failed)
                m_Adapter.OnMissionFailed(instance);
            else
                m_Adapter.OnMissionCompleted(instance);

            m_Adapter.CleanupMissionEntities(instance);
        }

        m_ActiveMissions.RemoveItem(instance);
    }

    void Tick(float deltaSeconds)
    {
        if (deltaSeconds <= 0.0)
            return;

        for (int i = m_ActiveMissions.Count() - 1; i >= 0; i--)
        {
            RHD_GM_MissionInstance instance = m_ActiveMissions[i];
            if (!instance)
            {
                m_ActiveMissions.Remove(i);
                continue;
            }

            instance.Tick(deltaSeconds);

            RHD_GM_MissionConfig config = instance.GetConfig();
            if (config && instance.GetElapsedSeconds() >= config.MissionTimeoutSeconds)
            {
                StopMission(instance, true);
                continue;
            }

            if (m_Adapter && m_Adapter.IsMissionFailed(instance))
            {
                StopMission(instance, true);
                continue;
            }

            if (m_Adapter && m_Adapter.IsMissionSuccessful(instance))
            {
                StopMission(instance, false);
                continue;
            }
        }
    }
}
