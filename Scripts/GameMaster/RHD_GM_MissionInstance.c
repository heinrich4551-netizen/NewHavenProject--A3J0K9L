class RHD_GM_MissionInstance
{
    protected RHD_GM_MissionDefinition m_Definition;
    protected ref RHD_GM_MissionConfig m_Config;
    protected ref array<ref RHD_GM_MissionTask> m_Tasks;
    protected ref array<ref RHD_GM_MissionObjective> m_Objectives;
    protected ref RHD_GM_MissionWorldState m_WorldState;
    protected ref RHD_GM_ReinforcementState m_Reinforcements;
    protected bool m_Running;
    protected float m_ElapsedSeconds;
    protected RHD_GM_MissionStatus m_Status;

    void RHD_GM_MissionInstance(RHD_GM_MissionDefinition definition, RHD_GM_MissionConfig config)
    {
        m_Definition = definition;
        m_Config = config;
        m_Tasks = new array<ref RHD_GM_MissionTask>();
        m_Objectives = new array<ref RHD_GM_MissionObjective>();
        m_WorldState = new RHD_GM_MissionWorldState();
        m_Reinforcements = new RHD_GM_ReinforcementState();
        m_Running = false;
        m_ElapsedSeconds = 0.0;
        m_Status = RHD_GM_MissionStatus.IDLE;
    }

    RHD_GM_MissionDefinition GetDefinition()
    {
        return m_Definition;
    }

    RHD_GM_MissionConfig GetConfig()
    {
        return m_Config;
    }

    RHD_GM_MissionWorldState GetWorldState()
    {
        return m_WorldState;
    }

    RHD_GM_ReinforcementState GetReinforcementState()
    {
        return m_Reinforcements;
    }

    RHD_GM_MissionStatus GetStatus()
    {
        return m_Status;
    }

    bool IsRunning()
    {
        return m_Running;
    }

    float GetElapsedSeconds()
    {
        return m_ElapsedSeconds;
    }

    array<ref RHD_GM_MissionTask> GetTasks()
    {
        return m_Tasks;
    }

    array<ref RHD_GM_MissionObjective> GetObjectives()
    {
        return m_Objectives;
    }

    void AddTask(RHD_GM_MissionTask task)
    {
        if (!task)
            return;

        m_Tasks.Insert(task);
    }

    void AddObjective(RHD_GM_MissionObjective objective)
    {
        if (!objective)
            return;

        m_Objectives.Insert(objective);
    }

    RHD_GM_MissionObjective FindObjective(string objectiveId)
    {
        foreach (RHD_GM_MissionObjective objective : m_Objectives)
        {
            if (objective && objective.Id == objectiveId)
                return objective;
        }

        return null;
    }

    bool CompleteObjective(string objectiveId)
    {
        RHD_GM_MissionObjective objective = FindObjective(objectiveId);
        if (!objective)
            return false;

        objective.Complete();
        return objective.Completed;
    }

    bool FailObjective(string objectiveId)
    {
        RHD_GM_MissionObjective objective = FindObjective(objectiveId);
        if (!objective)
            return false;

        objective.Fail();
        return objective.Failed;
    }

    bool AreRequiredObjectivesComplete()
    {
        foreach (RHD_GM_MissionObjective objective : m_Objectives)
        {
            if (!objective || !objective.Required)
                continue;

            if (!objective.Completed)
                return false;
        }

        return true;
    }

    bool HasRequiredObjectiveFailure()
    {
        foreach (RHD_GM_MissionObjective objective : m_Objectives)
        {
            if (!objective || !objective.Required)
                continue;

            if (objective.Failed)
                return true;
        }

        return false;
    }

    void Start()
    {
        if (m_Running)
            return;

        m_Running = true;
        m_ElapsedSeconds = 0.0;
        m_Status = RHD_GM_MissionStatus.RUNNING;

        if (m_Config && m_Reinforcements)
            m_Reinforcements.Configure(m_Config.ReinforcementGroups, m_Config.ReinforcementDelaySeconds);
    }

    void Stop(bool failed = false, bool timedOut = false)
    {
        m_Running = false;

        if (timedOut)
            m_Status = RHD_GM_MissionStatus.TIMED_OUT;
        else if (failed)
            m_Status = RHD_GM_MissionStatus.FAILED;
        else
            m_Status = RHD_GM_MissionStatus.COMPLETED;
    }

    void Tick(float deltaSeconds)
    {
        if (!m_Running || deltaSeconds <= 0.0)
            return;

        m_ElapsedSeconds += deltaSeconds;

        if (m_Reinforcements)
            m_Reinforcements.Tick(deltaSeconds);
    }
}
