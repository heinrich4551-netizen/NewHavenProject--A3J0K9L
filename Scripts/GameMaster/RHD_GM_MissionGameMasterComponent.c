class RHD_GM_MissionGameMasterComponentClass : ScriptComponentClass
{
}

class RHD_GM_MissionGameMasterComponent : ScriptComponent
{
    protected RHD_GM_MissionController m_Controller;

    override void OnPostInit(IEntity owner)
    {
        super.OnPostInit(owner);

        m_Controller = new RHD_GM_MissionController();
    }

    RHD_GM_MissionController GetController()
    {
        return m_Controller;
    }

    // Scenario/Game Master integration should call this from its authoritative
    // update path. Keeping the controller independent of frame/update APIs
    // makes it reusable across scenarios and mission compositions.
    void TickMissions(float deltaSeconds)
    {
        if (m_Controller)
            m_Controller.Tick(deltaSeconds);
    }
}
