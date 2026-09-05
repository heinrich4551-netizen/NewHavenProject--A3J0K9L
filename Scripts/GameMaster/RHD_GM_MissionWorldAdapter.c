class RHD_GM_MissionWorldAdapter
{
    // Scenario-specific implementation boundary. The generic framework never
    // assumes prefab GUIDs, factions, coordinates, or map-specific entities.

    bool SpawnHostileGroups(RHD_GM_MissionInstance instance, string groupPrefab, int groupCount, int unitsPerGroup)
    {
        return false;
    }

    bool SpawnMissionVehicle(RHD_GM_MissionInstance instance, string vehiclePrefab)
    {
        return false;
    }

    bool BindExistingCivilianGroup(RHD_GM_MissionInstance instance, string civilianGroupPrefab)
    {
        return false;
    }

    bool CreateMissionMarker(RHD_GM_MissionInstance instance, string markerPrefab, string label)
    {
        return false;
    }

    bool IsEntityAlive(IEntity entity)
    {
        return entity != null;
    }

    bool IsEntityAtDestination(IEntity entity)
    {
        return false;
    }

    bool IsLocationSecure(RHD_GM_MissionInstance instance)
    {
        return false;
    }

    bool IsRecoveryComplete(RHD_GM_MissionInstance instance)
    {
        return false;
    }

    bool IsEliminationComplete(RHD_GM_MissionInstance instance)
    {
        return false;
    }

    bool AreProtectedCiviliansAlive(RHD_GM_MissionInstance instance)
    {
        return true;
    }

    void CleanupMissionEntities(RHD_GM_MissionInstance instance)
    {
    }
}
