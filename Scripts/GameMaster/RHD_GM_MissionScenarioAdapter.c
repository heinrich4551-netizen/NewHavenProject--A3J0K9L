class RHD_GM_MissionScenarioAdapter : RHD_GM_MissionAdapter
{
    protected ref RHD_GM_MissionWorldAdapter m_World;
    protected ref RHD_GM_MissionWorldBinding m_Binding;

    void RHD_GM_MissionScenarioAdapter(RHD_GM_MissionWorldAdapter world = null, RHD_GM_MissionWorldBinding binding = null)
    {
        m_World = world;
        m_Binding = binding;

        if (m_Binding)
            m_Binding.Validate();
    }

    void SetWorldAdapter(RHD_GM_MissionWorldAdapter world)
    {
        m_World = world;
    }

    void SetBinding(RHD_GM_MissionWorldBinding binding)
    {
        m_Binding = binding;
        if (m_Binding)
            m_Binding.Validate();
    }

    RHD_GM_MissionWorldAdapter GetWorldAdapter()
    {
        return m_World;
    }

    RHD_GM_MissionWorldBinding GetBinding()
    {
        return m_Binding;
    }

    override bool CreateMissionEntities(RHD_GM_MissionInstance instance)
    {
        if (!instance || !m_World || !m_Binding)
            return false;

        RHD_GM_MissionConfig config = instance.GetConfig();
        if (!config)
            return false;

        RHD_GM_MissionTypeDefinition definition = RHD_GM_MissionTypeDefinition.Cast(instance.GetDefinition());
        if (!definition)
            return false;

        if (!ValidateMissionAssetRequirements(definition.Type, config))
            return false;

        RHD_GM_StockScenarioWorldAdapter stockWorld = RHD_GM_StockScenarioWorldAdapter.Cast(m_World);
        if (stockWorld && !stockWorld.PrepareMission(instance))
            return false;

        if (m_Binding.PrimaryPrefab)
        {
            if (!m_World.SpawnMissionVehicle(instance, m_Binding.PrimaryPrefab) && !m_Binding.AllowMissingVehicle)
                return false;
        }

        if (config.EnemyGroups > 0 && m_Binding.HostileGroupPrefab)
        {
            if (!m_World.SpawnHostileGroups(instance, m_Binding.HostileGroupPrefab, config.EnemyGroups, config.EnemyUnitsPerGroup) && !m_Binding.AllowMissingHostiles)
                return false;
        }

        if (m_Binding.BindExistingCivilians && m_Binding.CivilianGroupPrefab)
        {
            if (!m_World.BindExistingCivilianGroup(instance, m_Binding.CivilianGroupPrefab))
                return false;
        }

        if (m_Binding.SpawnObjectiveMarker && m_Binding.ObjectiveMarkerPrefab)
        {
            if (!m_World.CreateMissionMarker(instance, m_Binding.ObjectiveMarkerPrefab, m_Binding.ObjectiveLabel) && !m_Binding.AllowMissingMarkers)
                return false;
        }

        if (m_Binding.SpawnDestinationMarker && m_Binding.DestinationMarkerPrefab)
        {
            if (!m_World.CreateMissionMarker(instance, m_Binding.DestinationMarkerPrefab, m_Binding.DestinationLabel) && !m_Binding.AllowMissingMarkers)
                return false;
        }

        return true;
    }

    protected bool ValidateMissionAssetRequirements(RHD_GM_MissionType type, RHD_GM_MissionConfig config)
    {
        if (!m_Binding || !config)
            return false;

        if (type == RHD_GM_MissionType.CONVOY && !m_Binding.PrimaryPrefab && !m_Binding.AllowMissingVehicle)
            return false;

        if (config.EnemyGroups > 0 && !m_Binding.HostileGroupPrefab && !m_Binding.AllowMissingHostiles)
            return false;

        if (config.ReinforcementGroups > 0 && !m_Binding.ReinforcementPrefab && !m_Binding.AllowMissingReinforcements)
            return false;

        return true;
    }

    override bool IsMissionSuccessful(RHD_GM_MissionInstance instance)
    {
        if (!instance || !m_World || !instance.AreRequiredObjectivesComplete())
            return false;

        RHD_GM_MissionTypeDefinition definition = RHD_GM_MissionTypeDefinition.Cast(instance.GetDefinition());
        if (!definition)
            return false;

        switch (definition.Type)
        {
            case RHD_GM_MissionType.CONVOY:
                return m_World.IsEntityAtDestination(instance.GetWorldState().GetPrimaryEntity());

            case RHD_GM_MissionType.SECURE:
                return m_World.IsLocationSecure(instance);

            case RHD_GM_MissionType.RECOVERY:
                return m_World.IsRecoveryComplete(instance);

            case RHD_GM_MissionType.ELIMINATION:
                return m_World.IsEliminationComplete(instance);

            case RHD_GM_MissionType.CIVILIAN_PROTECTION:
                return m_World.IsCivilianProtectionComplete(instance);

            case RHD_GM_MissionType.DEFENSE:
                return m_World.IsLocationSecure(instance);

            case RHD_GM_MissionType.PATROL:
                return m_World.IsLocationSecure(instance);
        }

        return false;
    }

    override bool IsMissionFailed(RHD_GM_MissionInstance instance)
    {
        if (!instance || !m_World)
            return false;

        RHD_GM_MissionTypeDefinition definition = RHD_GM_MissionTypeDefinition.Cast(instance.GetDefinition());
        if (!definition)
            return false;

        if (definition.Type == RHD_GM_MissionType.CIVILIAN_PROTECTION)
            return !m_World.AreProtectedCiviliansAlive(instance);

        return false;
    }

    override void CleanupMissionEntities(RHD_GM_MissionInstance instance)
    {
        if (m_World)
            m_World.CleanupMissionEntities(instance);
    }
}
