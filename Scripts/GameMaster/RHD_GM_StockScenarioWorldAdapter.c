class RHD_GM_StockMissionWorldState
{
    protected RHD_GM_MissionInstance m_Instance;
    protected IEntity m_PrimaryEntity;
    protected ref array<IEntity> m_Hostiles;
    protected ref array<IEntity> m_Civilians;
    protected bool m_DestinationReached;
    protected bool m_LocationSecure;
    protected bool m_RecoveryComplete;
    protected bool m_ObjectiveEliminated;
    protected bool m_CivilianProtectionComplete;

    void RHD_GM_StockMissionWorldState(RHD_GM_MissionInstance instance)
    {
        m_Instance = instance;
        m_Hostiles = new array<IEntity>();
        m_Civilians = new array<IEntity>();
        m_DestinationReached = false;
        m_LocationSecure = false;
        m_RecoveryComplete = false;
        m_ObjectiveEliminated = false;
        m_CivilianProtectionComplete = false;
    }

    RHD_GM_MissionInstance GetInstance()
    {
        return m_Instance;
    }

    void SetPrimaryEntity(IEntity entity)
    {
        m_PrimaryEntity = entity;
    }

    IEntity GetPrimaryEntity()
    {
        return m_PrimaryEntity;
    }

    void AddHostile(IEntity entity)
    {
        if (!entity)
            return;

        if (m_Hostiles.Find(entity) < 0)
            m_Hostiles.Insert(entity);
    }

    void AddCivilian(IEntity entity)
    {
        if (!entity)
            return;

        if (m_Civilians.Find(entity) < 0)
            m_Civilians.Insert(entity);
    }

    array<IEntity> GetHostiles()
    {
        return m_Hostiles;
    }

    array<IEntity> GetCivilians()
    {
        return m_Civilians;
    }

    void SetDestinationReached(bool value)
    {
        m_DestinationReached = value;
    }

    bool IsDestinationReached()
    {
        return m_DestinationReached;
    }

    void SetLocationSecure(bool value)
    {
        m_LocationSecure = value;
    }

    bool IsLocationSecure()
    {
        return m_LocationSecure;
    }

    void SetRecoveryComplete(bool value)
    {
        m_RecoveryComplete = value;
    }

    bool IsRecoveryComplete()
    {
        return m_RecoveryComplete;
    }

    void SetObjectiveEliminated(bool value)
    {
        m_ObjectiveEliminated = value;
    }

    bool IsObjectiveEliminated()
    {
        return m_ObjectiveEliminated;
    }

    void SetCivilianProtectionComplete(bool value)
    {
        m_CivilianProtectionComplete = value;
    }

    bool IsCivilianProtectionComplete()
    {
        return m_CivilianProtectionComplete;
    }
}

class RHD_GM_StockScenarioWorldAdapter : RHD_GM_MissionWorldAdapter
{
    protected ref array<ref RHD_GM_StockMissionWorldState> m_Missions;

    void RHD_GM_StockScenarioWorldAdapter()
    {
        m_Missions = new array<ref RHD_GM_StockMissionWorldState>();
    }

    RHD_GM_StockMissionWorldState FindState(RHD_GM_MissionInstance instance)
    {
        if (!instance)
            return null;

        foreach (RHD_GM_StockMissionWorldState state : m_Missions)
        {
            if (state && state.GetInstance() == instance)
                return state;
        }

        return null;
    }

    RHD_GM_StockMissionWorldState GetOrCreateState(RHD_GM_MissionInstance instance)
    {
        RHD_GM_StockMissionWorldState state = FindState(instance);
        if (state)
            return state;

        if (!instance)
            return null;

        state = new RHD_GM_StockMissionWorldState(instance);
        m_Missions.Insert(state);
        return state;
    }

    bool PrepareMission(RHD_GM_MissionInstance instance)
    {
        return GetOrCreateState(instance) != null;
    }

    bool SpawnHostileGroups(RHD_GM_MissionInstance instance, string groupPrefab, int groupCount, int unitsPerGroup)
    {
        // Dynamic resource spawning is intentionally left to the exact engine
        // integration for the installed Reforger version. This adapter never
        // pretends that a prefab string has created entities.
        return false;
    }

    bool SpawnReinforcementGroup(RHD_GM_MissionInstance instance, string groupPrefab, int unitsPerGroup)
    {
        return false;
    }

    bool SpawnMissionVehicle(RHD_GM_MissionInstance instance, string vehiclePrefab)
    {
        // Mission vehicles are existing stock entities registered with
        // RegisterPrimaryEntity().
        RHD_GM_StockMissionWorldState state = FindState(instance);
        return state != null && vehiclePrefab != "" && state.GetPrimaryEntity() != null;
    }

    bool BindExistingCivilianGroup(RHD_GM_MissionInstance instance, string civilianGroupPrefab)
    {
        RHD_GM_StockMissionWorldState state = FindState(instance);
        return state != null && civilianGroupPrefab != "" && state.GetCivilians().Count() > 0;
    }

    bool CreateMissionMarker(RHD_GM_MissionInstance instance, string markerPrefab, string label)
    {
        // Marker placement remains owned by Workbench/scenario integration.
        // No custom marker resource is created here.
        return false;
    }

    bool IsEntityAlive(IEntity entity)
    {
        return entity != null;
    }

    bool IsEntityAtDestination(IEntity entity)
    {
        RHD_GM_StockMissionWorldState state = FindStateForPrimaryEntity(entity);
        return state != null && state.IsDestinationReached() && IsEntityAlive(entity);
    }

    bool IsLocationSecure(RHD_GM_MissionInstance instance)
    {
        RHD_GM_StockMissionWorldState state = FindState(instance);
        return state != null && state.IsLocationSecure();
    }

    bool IsRecoveryComplete(RHD_GM_MissionInstance instance)
    {
        RHD_GM_StockMissionWorldState state = FindState(instance);
        return state != null && state.IsRecoveryComplete();
    }

    bool IsEliminationComplete(RHD_GM_MissionInstance instance)
    {
        RHD_GM_StockMissionWorldState state = FindState(instance);
        if (!state)
            return false;

        if (state.IsObjectiveEliminated())
            return true;

        foreach (IEntity hostile : state.GetHostiles())
        {
            if (IsEntityAlive(hostile))
                return false;
        }

        return state.GetHostiles().Count() > 0;
    }

    bool IsCivilianProtectionComplete(RHD_GM_MissionInstance instance)
    {
        RHD_GM_StockMissionWorldState state = FindState(instance);
        return state != null && state.IsCivilianProtectionComplete();
    }

    bool AreProtectedCiviliansAlive(RHD_GM_MissionInstance instance)
    {
        RHD_GM_StockMissionWorldState state = FindState(instance);
        if (!state || state.GetCivilians().Count() == 0)
            return false;

        foreach (IEntity civilian : state.GetCivilians())
        {
            if (!IsEntityAlive(civilian))
                return false;
        }

        return true;
    }

    void CleanupMissionEntities(RHD_GM_MissionInstance instance)
    {
        RHD_GM_StockMissionWorldState state = FindState(instance);
        if (!state)
            return;

        // Existing stock scenario entities are never deleted here.
        m_Missions.RemoveItem(state);
    }

    bool RegisterPrimaryEntity(RHD_GM_MissionInstance instance, IEntity entity)
    {
        RHD_GM_StockMissionWorldState state = GetOrCreateState(instance);
        if (!state || !entity)
            return false;

        state.SetPrimaryEntity(entity);
        instance.GetWorldState().SetPrimaryEntity(entity);
        return true;
    }

    bool RegisterHostile(RHD_GM_MissionInstance instance, IEntity entity)
    {
        RHD_GM_StockMissionWorldState state = GetOrCreateState(instance);
        if (!state || !entity)
            return false;

        state.AddHostile(entity);
        instance.GetWorldState().GetOwnership().Track(entity);
        return true;
    }

    bool RegisterCivilian(RHD_GM_MissionInstance instance, IEntity entity)
    {
        RHD_GM_StockMissionWorldState state = GetOrCreateState(instance);
        if (!state || !entity)
            return false;

        state.AddCivilian(entity);
        return true;
    }

    void SetDestinationReached(RHD_GM_MissionInstance instance, bool value = true)
    {
        RHD_GM_StockMissionWorldState state = GetOrCreateState(instance);
        if (state)
            state.SetDestinationReached(value);
    }

    void SetLocationSecure(RHD_GM_MissionInstance instance, bool value = true)
    {
        RHD_GM_StockMissionWorldState state = GetOrCreateState(instance);
        if (state)
            state.SetLocationSecure(value);
    }

    void SetRecoveryComplete(RHD_GM_MissionInstance instance, bool value = true)
    {
        RHD_GM_StockMissionWorldState state = GetOrCreateState(instance);
        if (state)
            state.SetRecoveryComplete(value);
    }

    void SetObjectiveEliminated(RHD_GM_MissionInstance instance, bool value = true)
    {
        RHD_GM_StockMissionWorldState state = GetOrCreateState(instance);
        if (state)
            state.SetObjectiveEliminated(value);
    }

    void SetCivilianProtectionComplete(RHD_GM_MissionInstance instance, bool value = true)
    {
        RHD_GM_StockMissionWorldState state = GetOrCreateState(instance);
        if (state)
            state.SetCivilianProtectionComplete(value);
    }

    protected RHD_GM_StockMissionWorldState FindStateForPrimaryEntity(IEntity entity)
    {
        if (!entity)
            return null;

        foreach (RHD_GM_StockMissionWorldState state : m_Missions)
        {
            if (state && state.GetPrimaryEntity() == entity)
                return state;
        }

        return null;
    }
}
