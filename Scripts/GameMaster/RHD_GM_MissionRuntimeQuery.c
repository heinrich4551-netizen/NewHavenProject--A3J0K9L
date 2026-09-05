class RHD_GM_MissionRuntimeQuery
{
    protected RHD_GM_MissionController m_Controller;

    void RHD_GM_MissionRuntimeQuery(RHD_GM_MissionController controller = null)
    {
        m_Controller = controller;
    }

    void SetController(RHD_GM_MissionController controller)
    {
        m_Controller = controller;
    }

    int GetActiveMissionCount()
    {
        if (!m_Controller)
            return 0;

        return m_Controller.GetActiveMissions().Count();
    }

    RHD_GM_MissionInstance FindActiveMission(string missionId)
    {
        if (!m_Controller)
            return null;

        return m_Controller.FindActiveMission(missionId);
    }

    bool IsMissionActive(string missionId)
    {
        return FindActiveMission(missionId) != null;
    }

    RHD_GM_MissionResult GetResult(RHD_GM_MissionInstance instance)
    {
        return new RHD_GM_MissionResult(instance);
    }
}
