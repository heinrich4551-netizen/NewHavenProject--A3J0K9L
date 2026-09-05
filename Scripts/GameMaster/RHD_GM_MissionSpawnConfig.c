class RHD_GM_MissionSpawnConfig
{
    string ConvoyVehiclePrefab;
    string EscortGroupPrefab;
    string ReinforcementGroupPrefab;
    string CivilianAIGroupPrefab;
    string StartMarkerPrefab;
    string ObjectiveMarkerPrefab;
    string DestinationMarkerPrefab;

    int EscortGroups = 2;
    int ReinforcementGroups = 1;
    int CivilianUnits = 0;

    float EscortSpawnRadius = 100.0;
    float ReinforcementDelaySeconds = 300.0;

    bool UseExistingCivilianAI = true;
    bool SpawnObjectiveMarker = true;
    bool SpawnDestinationMarker = true;

    void ClampValues()
    {
        if (EscortGroups < 0)
            EscortGroups = 0;

        if (EscortGroups > 20)
            EscortGroups = 20;

        if (ReinforcementGroups < 0)
            ReinforcementGroups = 0;

        if (ReinforcementGroups > 20)
            ReinforcementGroups = 20;

        if (CivilianUnits < 0)
            CivilianUnits = 0;

        if (CivilianUnits > 100)
            CivilianUnits = 100;

        if (EscortSpawnRadius < 25.0)
            EscortSpawnRadius = 25.0;

        if (ReinforcementDelaySeconds < 30.0)
            ReinforcementDelaySeconds = 30.0;
    }
}
