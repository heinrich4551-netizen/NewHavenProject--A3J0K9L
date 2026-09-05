class RHD_GM_MissionGameMasterComponentClass : ScriptComponentClass
{
}

class RHD_GM_MissionGameMasterComponent : ScriptComponent
{
    protected RHD_GM_MissionController m_Controller;
    protected ref RHD_GM_MissionActivation m_Activation;
    protected ref RHD_GM_MissionRuntimeQuery m_Query;
    protected RHD_GM_MissionScenarioAdapter m_ScenarioAdapter;
    protected bool m_Bootstrapped;

    override void OnPostInit(IEntity owner)
    {
        super.OnPostInit(owner);

        m_Controller = new RHD_GM_MissionController();
        m_Activation = new RHD_GM_MissionActivation(m_Controller);
        m_Query = new RHD_GM_MissionRuntimeQuery(m_Controller);
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

    RHD_GM_MissionRuntimeQuery GetRuntimeQuery()
    {
        return m_Query;
    }

    RHD_GM_MissionScenarioAdapter GetScenarioAdapter()
    {
        return m_ScenarioAdapter;
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

    bool IsScenarioConfigured()
    {
        return m_ScenarioAdapter != null && m_Controller != null && m_Controller.GetAdapter() == m_ScenarioAdapter;
    }

    bool ConfigureScenario(RHD_GM_MissionWorldAdapter world, RHD_GM_MissionWorldBinding binding)
    {
        if (!m_Controller || !world || !RHD_GM_MissionValidation.ValidateBinding(binding))
            return false;

        RHD_GM_MissionScenarioAdapter adapter = new RHD_GM_MissionScenarioAdapter(world, binding);
        m_ScenarioAdapter = adapter;

        m_Controller.SetWorldAdapter(world);
        m_Controller.SetAdapter(adapter);
        return true;
    }

    void SetMissionAdapter(RHD_GM_MissionAdapter adapter)
    {
        if (m_Controller)
            m_Controller.SetAdapter(adapter);

        if (adapter != m_ScenarioAdapter)
            m_ScenarioAdapter = null;
    }

    void SetMissionWorldAdapter(RHD_GM_MissionWorldAdapter world)
    {
        if (m_Controller)
            m_Controller.SetWorldAdapter(world);
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

    bool CompleteObjective(RHD_GM_MissionInstance instance, string objectiveId)
    {
        if (!m_Controller)
            return false;

        return m_Controller.CompleteObjective(instance, objectiveId);
    }

    bool FailObjective(RHD_GM_MissionInstance instance, string objectiveId)
    {
        if (!m_Controller)
            return false;

        return m_Controller.FailObjective(instance, objectiveId);
    }

    array<string> GetAvailableMissionIds()
    {
        if (!m_Activation || !m_Activation.GetLibrary())
            return new array<string>();

        return m_Activation.GetLibrary().GetMissionIds();
    }

    RHD_GM_MissionInstance FindActiveMission(string missionId)
    {
        if (!m_Query)
            return null;

        return m_Query.FindActiveMission(missionId);
    }

    bool IsMissionActive(string missionId)
    {
        if (!m_Query)
            return false;

        return m_Query.IsMissionActive(missionId);
    }

    int GetActiveMissionCount()
    {
        if (!m_Query)
            return 0;

        return m_Query.GetActiveMissionCount();
    }

    // Call from the authoritative scenario/Game Master update path.
    void TickMissions(float deltaSeconds)
    {
        if (m_Controller)
            m_Controller.Tick(deltaSeconds);
    }
}
