class RHD_GM_MissionActivation
{
    protected RHD_GM_MissionController m_Controller;
    protected ref RHD_GM_MissionLibrary m_Library;
    protected ref RHD_GM_MissionEventDispatcher m_Events;

    void RHD_GM_MissionActivation(RHD_GM_MissionController controller = null)
    {
        m_Controller = controller;
        m_Library = new RHD_GM_MissionLibrary();
        m_Events = new RHD_GM_MissionEventDispatcher();
    }

    void SetController(RHD_GM_MissionController controller)
    {
        m_Controller = controller;
    }

    RHD_GM_MissionController GetController()
    {
        return m_Controller;
    }

    RHD_GM_MissionLibrary GetLibrary()
    {
        return m_Library;
    }

    RHD_GM_MissionEventDispatcher GetEvents()
    {
        return m_Events;
    }

    bool RegisterMission(RHD_GM_MissionComposition composition)
    {
        if (!m_Library)
            return false;

        return m_Library.Add(composition);
    }

    RHD_GM_MissionInstance StartMission(string missionId)
    {
        if (!m_Controller || !m_Library)
            return null;

        RHD_GM_MissionComposition composition = m_Library.Find(missionId);
        if (!composition)
            return null;

        RHD_GM_MissionTypeDefinition definition = new RHD_GM_MissionTypeDefinition(composition.Id, composition.DisplayName, ResolveMissionType(composition.Id), composition.Description);
        definition.Enabled = composition.MissionConfig && composition.MissionConfig.Enabled;

        RHD_GM_MissionInstance instance = m_Controller.StartMission(definition, composition.MissionConfig);
        if (!instance)
            return null;

        foreach (RHD_GM_MissionObjective objective : composition.Objectives)
        {
            if (objective)
                instance.AddObjective(objective.Clone());
        }

        if (m_Events)
            m_Events.Dispatch(new RHD_GM_MissionEvent(RHD_GM_MissionEventType.STARTED, composition.Id, "Mission started"));

        return instance;
    }

    bool StopMission(RHD_GM_MissionInstance instance, bool failed = false)
    {
        if (!m_Controller || !instance)
            return false;

        m_Controller.StopMission(instance, failed);
        return true;
    }

    protected RHD_GM_MissionType ResolveMissionType(string missionId)
    {
        if (missionId == "RHD_CONVOY")
            return RHD_GM_MissionType.CONVOY;

        if (missionId == "RHD_SECURE")
            return RHD_GM_MissionType.SECURE;

        if (missionId == "RHD_RECOVERY")
            return RHD_GM_MissionType.RECOVERY;

        if (missionId == "RHD_ELIMINATION")
            return RHD_GM_MissionType.ELIMINATION;

        if (missionId == "RHD_CIVILIAN_PROTECTION")
            return RHD_GM_MissionType.CIVILIAN_PROTECTION;

        if (missionId == "RHD_DEFENSE")
            return RHD_GM_MissionType.DEFENSE;

        if (missionId == "RHD_PATROL")
            return RHD_GM_MissionType.PATROL;

        return RHD_GM_MissionType.PATROL;
    }
}
