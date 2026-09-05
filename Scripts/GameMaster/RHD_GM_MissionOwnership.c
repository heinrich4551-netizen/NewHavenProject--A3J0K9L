class RHD_GM_MissionOwnership
{
    protected ref array<IEntity> m_Entities;

    void RHD_GM_MissionOwnership()
    {
        m_Entities = new array<IEntity>();
    }

    void Track(IEntity entity)
    {
        if (!entity)
            return;

        if (m_Entities.Find(entity) < 0)
            m_Entities.Insert(entity);
    }

    void Untrack(IEntity entity)
    {
        if (!entity)
            return;

        m_Entities.RemoveItem(entity);
    }

    array<IEntity> GetEntities()
    {
        return m_Entities;
    }

    void Clear()
    {
        m_Entities.Clear();
    }
}
