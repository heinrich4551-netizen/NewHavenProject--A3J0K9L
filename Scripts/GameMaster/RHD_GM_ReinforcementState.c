class RHD_GM_ReinforcementState
{
    protected int m_GroupsRequested;
    protected int m_GroupsSpawned;
    protected float m_NextReinforcementSeconds;
    protected float m_ReinforcementDelaySeconds;

    void Configure(int groups, float delaySeconds)
    {
        m_GroupsRequested = Math.Clamp(groups, 0, 20);
        m_GroupsSpawned = 0;
        m_ReinforcementDelaySeconds = Math.Max(0.0, delaySeconds);
        m_NextReinforcementSeconds = m_ReinforcementDelaySeconds;
    }

    bool CanSpawn()
    {
        return m_GroupsSpawned < m_GroupsRequested;
    }

    void MarkSpawned()
    {
        if (m_GroupsSpawned < m_GroupsRequested)
        {
            m_GroupsSpawned++;
            m_NextReinforcementSeconds = m_ReinforcementDelaySeconds;
        }
    }

    int GetGroupsRequested()
    {
        return m_GroupsRequested;
    }

    int GetGroupsSpawned()
    {
        return m_GroupsSpawned;
    }

    float GetNextReinforcementSeconds()
    {
        return m_NextReinforcementSeconds;
    }

    float GetReinforcementDelaySeconds()
    {
        return m_ReinforcementDelaySeconds;
    }

    void Tick(float deltaSeconds)
    {
        if (deltaSeconds <= 0.0 || !CanSpawn())
            return;

        m_NextReinforcementSeconds -= deltaSeconds;
    }

    bool IsReady()
    {
        return CanSpawn() && m_NextReinforcementSeconds <= 0.0;
    }
}
