class RHD_GM_ReinforcementState
{
    protected int m_GroupsRequested;
    protected int m_GroupsSpawned;
    protected float m_NextReinforcementSeconds;

    void Configure(int groups, float delaySeconds)
    {
        m_GroupsRequested = Math.Clamp(groups, 0, 20);
        m_GroupsSpawned = 0;
        m_NextReinforcementSeconds = Math.Max(0.0, delaySeconds);
    }

    bool CanSpawn()
    {
        return m_GroupsSpawned < m_GroupsRequested;
    }

    void MarkSpawned()
    {
        if (m_GroupsSpawned < m_GroupsRequested)
            m_GroupsSpawned++;
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
