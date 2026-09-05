class RHD_GM_MissionGameMasterComponentClass : ScriptComponentClass
{
}

class RHD_GM_MissionGameMasterComponent : ScriptComponent
{
    protected RHD_GM_MissionController m_Controller;
    protected ref RHD_GM_MissionActivation m_Activation;
    protected bool m_Bootstrapped;

    override void OnPostInit(IEntity owner)
    {
        super.OnPostInit(owner);

        m_Controller = new RHD_GM_MissionController();
        m_Activation = new RHD_GM_MissionActivation(m_Controller);
        RHD_GM_MissionBootstrap.RegisterDefaultMissions(m_Activation);
        m_Bootstrapped = true;
    }

    RHD_GM_MissionController GetController()
    {
        return m_Controller;
    }

    RHD_GM_MissionActivation GetActivation()
    {
        return m_Activation;
    }

    RHD_GM_MissionEventDispatcher GetEventDispatcher()
    {
        if (!m_Activation)
            return null;

        return m_Activation.GetEvents();
    }

    bool IsBootstrapped()
    {
        return m_Bootstrapped;
    }

    bool RegisterMission(RHD_GM_MissionComposition composition)
    {
        if (!m_Activation)
            return false;

        return m_Activation.RegisterMission(composition);
    }

    RHD_GM_MissionInstance StartMissionById(string missionId)
    {
        if (!m_Activation)
            return null;

        return m_Activation.StartMission(missionId);
    }

    bool StopMission(RHD_GM_MissionInstance instance, bool failed = false)
    {
        if (!m_Activation)
            return false;

        return m_Activation.StopMission(instance, failed);
    }

    array<string> GetAvailableMissionIds()
    {
        if (!m_Activation || !m_Activation.GetLibrary())
            return new array<string>();

        return m_Activation.GetLibrary().GetMissionIds();
    }

    // Call from the authoritative scenario/Game Master update path.
    void TickMissions(float deltaSeconds)
    {
        if (m_Controller)
            m_Controller.Tick(deltaSeconds);
    }
}
