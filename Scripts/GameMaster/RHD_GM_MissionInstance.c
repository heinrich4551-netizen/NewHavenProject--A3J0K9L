class RHD_GM_MissionInstance
{
    protected RHD_GM_MissionDefinition m_Definition;
    protected ref RHD_GM_MissionConfig m_Config;
    protected ref array<ref RHD_GM_MissionTask> m_Tasks;
    protected bool m_Running;
    protected float m_ElapsedSeconds;

    void RHD_GM_MissionInstance(RHD_GM_MissionDefinition definition, RHD_GM_MissionConfig config)
    {
        m_Definition = definition;
        m_Config = config;
        m_Tasks = new array<ref RHD_GM_MissionTask>();
        m_Running = false;
        m_ElapsedSeconds = 0.0;
    }

    RHD_GM_MissionDefinition GetDefinition()
    {
        return m_Definition;
    }

    RHD_GM_MissionConfig GetConfig()
    {
        return m_Config;
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

    void AddTask(RHD_GM_MissionTask task)
    {
        if (!task)
            return;

        m_Tasks.Insert(task);
    }

    void Start()
    {
        if (m_Running)
            return;

        m_Running = true;
        m_ElapsedSeconds = 0.0;
    }

    void Stop()
    {
        m_Running = false;
    }

    void Tick(float deltaSeconds)
    {
        if (!m_Running || deltaSeconds <= 0.0)
            return;

        m_ElapsedSeconds += deltaSeconds;
    }
}
