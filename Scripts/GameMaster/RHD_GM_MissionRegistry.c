class RHD_GM_MissionRegistry
{
    protected ref array<ref RHD_GM_MissionDefinition> m_Definitions;
    protected ref map<string, bool> m_Active;

    void RHD_GM_MissionRegistry()
    {
        m_Definitions = new array<ref RHD_GM_MissionDefinition>();
        m_Active = new map<string, bool>();
    }

    void Register(RHD_GM_MissionDefinition definition)
    {
        if (!definition || definition.Id.IsEmpty())
            return;

        for (int i = 0; i < m_Definitions.Count(); i++)
        {
            if (m_Definitions[i].Id == definition.Id)
            {
                m_Definitions[i] = definition;
                return;
            }
        }

        m_Definitions.Insert(definition);
        m_Active.Set(definition.Id, false);
    }

    RHD_GM_MissionDefinition Find(string missionId)
    {
        for (int i = 0; i < m_Definitions.Count(); i++)
        {
            if (m_Definitions[i].Id == missionId)
                return m_Definitions[i];
        }

        return null;
    }

    bool Start(string missionId)
    {
        RHD_GM_MissionDefinition definition = Find(missionId);
        if (!definition || !definition.Enabled)
            return false;

        m_Active.Set(missionId, true);
        return true;
    }

    bool Stop(string missionId)
    {
        if (!Find(missionId))
            return false;

        m_Active.Set(missionId, false);
        return true;
    }

    bool IsActive(string missionId)
    {
        bool active;
        if (!m_Active.Find(missionId, active))
            return false;

        return active;
    }
}
