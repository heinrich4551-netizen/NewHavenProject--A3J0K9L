class RHD_GM_MissionFrameworkClass : ScriptComponentClass
{
}

class RHD_GM_MissionFramework : ScriptComponent
{
    protected static RHD_GM_MissionFramework s_Instance;
    protected ref RHD_GM_MissionRegistry m_Registry;
    protected bool m_Initialized;

    static RHD_GM_MissionFramework GetInstance()
    {
        return s_Instance;
    }

    override void OnPostInit(IEntity owner)
    {
        super.OnPostInit(owner);

        if (!m_Registry)
            m_Registry = new RHD_GM_MissionRegistry();

        s_Instance = this;
        m_Initialized = true;
    }

    RHD_GM_MissionRegistry GetRegistry()
    {
        return m_Registry;
    }

    bool IsInitialized()
    {
        return m_Initialized;
    }

    void RegisterMission(RHD_GM_MissionDefinition definition)
    {
        if (!definition || !m_Registry)
            return;

        m_Registry.Register(definition);
    }

    bool StartMission(string missionId)
    {
        if (!m_Registry)
            return false;

        return m_Registry.Start(missionId);
    }

    bool StopMission(string missionId)
    {
        if (!m_Registry)
            return false;

        return m_Registry.Stop(missionId);
    }
}
