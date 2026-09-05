class RHD_GM_MissionController
{
    protected ref array<ref RHD_GM_MissionInstance> m_ActiveMissions;
    protected RHD_GM_MissionAdapter m_Adapter;
    protected RHD_GM_MissionWorldAdapter m_World;
    protected ref RHD_GM_MissionEventDispatcher m_Events;

    void RHD_GM_MissionController(RHD_GM_MissionAdapter adapter = null, RHD_GM_MissionWorldAdapter world = null)
    {
        m_ActiveMissions = new array<ref RHD_GM_MissionInstance>();
        m_Adapter = adapter;
        m_World = world;
        m_Events = new RHD_GM_MissionEventDispatcher();
    }

    void SetAdapter(RHD_GM_MissionAdapter adapter)
    {
        m_Adapter = adapter;
    }

    void SetWorldAdapter(RHD_GM_MissionWorldAdapter world)
    {
        m_World = world;
    }

    RHD_GM_MissionAdapter GetAdapter()
    {
        return m_Adapter;
    }

    RHD_GM_MissionEventDispatcher GetEventDispatcher()
    {
        return m_Events;
    }

    array<ref RHD_GM_MissionInstance> GetActiveMissions()
    {
        return m_ActiveMissions;
    }

    RHD_GM_MissionInstance StartMission(RHD_GM_MissionDefinition definition, RHD_GM_MissionConfig config)
    {
        if (!definition || !config || !definition.Enabled || !config.Enabled)
            return null;

        if (FindActiveMission(definition.Id))
            return null;

        config.ClampValues();

        RHD_GM_MissionInstance instance = new RHD_GM_MissionInstance(definition, config);

        if (!m_Adapter)
            return null;

        if (!m_Adapter.CreateMissionEntities(instance))
            return null;

        instance.Start();
        m_ActiveMissions.Insert(instance);

        m_Adapter.OnMissionStarted(instance);
        Dispatch(new RHD_GM_MissionEvent(RHD_GM_MissionEventType.STARTED, GetMissionId(instance), "Mission started"));
        return instance;
    }

    RHD_GM_MissionInstance FindActiveMission(string missionId)
    {
        if (!missionId)
            return null;

        foreach (RHD_GM_MissionInstance instance : m_ActiveMissions)
        {
            if (instance && instance.IsRunning() && instance.GetDefinition() && instance.GetDefinition().Id == missionId)
                return instance;
        }

        return null;
    }

    void StopMission(RHD_GM_MissionInstance instance, bool failed = false, bool timedOut = false)
    {
        if (!instance || !instance.IsRunning())
            return;

        instance.Stop(failed, timedOut);

        if (m_Adapter)
        {
            if (failed)
                m_Adapter.OnMissionFailed(instance);
            else
                m_Adapter.OnMissionCompleted(instance);

            m_Adapter.CleanupMissionEntities(instance);
        }

        RHD_GM_MissionEventType eventType = RHD_GM_MissionEventType.COMPLETED;
        string message = "Mission completed";

        if (timedOut)
        {
            eventType = RHD_GM_MissionEventType.TIMED_OUT;
            message = "Mission timed out";
        }
        else if (failed)
        {
            eventType = RHD_GM_MissionEventType.FAILED;
            message = "Mission failed";
        }

        Dispatch(new RHD_GM_MissionEvent(eventType, GetMissionId(instance), message));
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

            RHD_GM_MissionObjective failedObjective = FindFailedRequiredObjective(instance);
            if (failedObjective)
            {
                DispatchObjectiveEvent(instance, failedObjective, false);
                StopMission(instance, true);
                continue;
            }

            RHD_GM_MissionConfig config = instance.GetConfig();
            if (config && instance.GetElapsedSeconds() >= config.MissionTimeoutSeconds)
            {
                StopMission(instance, true, true);
                continue;
            }

            TryDeployReinforcement(instance);

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

            if (instance.AreRequiredObjectivesComplete())
            {
                StopMission(instance, false);
                continue;
            }
        }
    }

    protected void TryDeployReinforcement(RHD_GM_MissionInstance instance)
    {
        if (!instance || !m_World)
            return;

        RHD_GM_ReinforcementState state = instance.GetReinforcementState();
        if (!state || !state.IsReady())
            return;

        RHD_GM_MissionWorldBinding binding = GetWorldBinding();
        if (!binding || !binding.ReinforcementPrefab)
            return;

        RHD_GM_MissionConfig config = instance.GetConfig();
        if (!config)
            return;

        if (!m_World.SpawnReinforcementGroup(instance, binding.ReinforcementPrefab, config.EnemyUnitsPerGroup))
            return;

        state.MarkSpawned();
        Dispatch(new RHD_GM_MissionEvent(RHD_GM_MissionEventType.REINFORCEMENT_DEPLOYED, GetMissionId(instance), "Reinforcement deployed"));
    }

    protected RHD_GM_MissionWorldBinding GetWorldBinding()
    {
        RHD_GM_MissionScenarioAdapter scenarioAdapter = RHD_GM_MissionScenarioAdapter.Cast(m_Adapter);
        if (!scenarioAdapter)
            return null;

        return scenarioAdapter.GetBinding();
    }

    protected RHD_GM_MissionObjective FindFailedRequiredObjective(RHD_GM_MissionInstance instance)
    {
        foreach (RHD_GM_MissionObjective objective : instance.GetObjectives())
        {
            if (objective && objective.Required && objective.Failed)
                return objective;
        }

        return null;
    }

    protected void DispatchObjectiveEvent(RHD_GM_MissionInstance instance, RHD_GM_MissionObjective objective, bool completed)
    {
        if (!instance || !objective)
            return;

        RHD_GM_MissionEventType eventType = completed ? RHD_GM_MissionEventType.OBJECTIVE_COMPLETED : RHD_GM_MissionEventType.OBJECTIVE_FAILED;
        RHD_GM_MissionEvent eventData = new RHD_GM_MissionEvent(eventType, GetMissionId(instance), objective.Title);
        eventData.ObjectiveId = objective.Id;
        Dispatch(eventData);
    }

    protected void Dispatch(RHD_GM_MissionEvent eventData)
    {
        if (m_Events)
            m_Events.Dispatch(eventData);
    }

    protected string GetMissionId(RHD_GM_MissionInstance instance)
    {
        if (!instance || !instance.GetDefinition())
            return "";

        return instance.GetDefinition().Id;
    }
}
