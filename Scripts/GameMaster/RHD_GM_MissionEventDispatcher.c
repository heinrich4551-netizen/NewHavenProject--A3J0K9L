class RHD_GM_MissionEventDispatcher
{
    protected ref array<RHD_GM_MissionEventListener> m_Listeners;

    void RHD_GM_MissionEventDispatcher()
    {
        m_Listeners = new array<RHD_GM_MissionEventListener>();
    }

    void AddListener(RHD_GM_MissionEventListener listener)
    {
        if (!listener)
            return;

        if (m_Listeners.Find(listener) < 0)
            m_Listeners.Insert(listener);
    }

    void RemoveListener(RHD_GM_MissionEventListener listener)
    {
        if (!listener)
            return;

        m_Listeners.RemoveItem(listener);
    }

    void Dispatch(RHD_GM_MissionEvent eventData)
    {
        if (!eventData)
            return;

        foreach (RHD_GM_MissionEventListener listener : m_Listeners)
        {
            if (listener)
                listener.OnMissionEvent(eventData);
        }
    }
}
