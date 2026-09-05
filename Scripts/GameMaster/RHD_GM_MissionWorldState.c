class RHD_GM_MissionWorldState
{
    protected ref RHD_GM_MissionOwnership m_Ownership;
    protected IEntity m_PrimaryEntity;
    protected bool m_ObjectiveComplete;
    protected bool m_ObjectiveFailed;

    void RHD_GM_MissionWorldState()
    {
        m_Ownership = new RHD_GM_MissionOwnership();
        m_ObjectiveComplete = false;
        m_ObjectiveFailed = false;
    }

    RHD_GM_MissionOwnership GetOwnership()
    {
        return m_Ownership;
    }

    void SetPrimaryEntity(IEntity entity)
    {
        m_PrimaryEntity = entity;
        if (m_Ownership)
            m_Ownership.Track(entity);
    }

    IEntity GetPrimaryEntity()
    {
        return m_PrimaryEntity;
    }

    void SetObjectiveComplete(bool value)
    {
        m_ObjectiveComplete = value;
    }

    bool IsObjectiveComplete()
    {
        return m_ObjectiveComplete;
    }

    void SetObjectiveFailed(bool value)
    {
        m_ObjectiveFailed = value;
    }

    bool IsObjectiveFailed()
    {
        return m_ObjectiveFailed;
    }
}
