class RHD_GM_MissionWorldBinding
{
    // All references are intended to point at assets already shipped with
    // Arma Reforger and visible in the active Workbench project.
    // No prefab GUIDs are hard-coded here.
    string PrimaryPrefab;
    string HostileGroupPrefab;
    string ReinforcementPrefab;
    string CivilianGroupPrefab;

    string StartMarkerPrefab;
    string ObjectiveMarkerPrefab;
    string DestinationMarkerPrefab;

    string ObjectiveLabel;
    string DestinationLabel;

    bool BindExistingCivilians = true;
    bool SpawnObjectiveMarker = true;
    bool SpawnDestinationMarker = true;
    bool AllowMissingVehicle = true;
    bool AllowMissingHostiles = true;
    bool AllowMissingReinforcements = true;
    bool AllowMissingMarkers = true;

    void Validate()
    {
        if (!ObjectiveLabel)
            ObjectiveLabel = "Mission Objective";

        if (!DestinationLabel)
            DestinationLabel = "Mission Destination";
    }

    bool HasPrimaryAsset()
    {
        return PrimaryPrefab != "";
    }

    bool HasHostileAsset()
    {
        return HostileGroupPrefab != "";
    }

    bool HasReinforcementAsset()
    {
        return ReinforcementPrefab != "";
    }

    bool HasCivilianAsset()
    {
        return CivilianGroupPrefab != "";
    }

    bool HasMarkerAssets()
    {
        return StartMarkerPrefab != "" || ObjectiveMarkerPrefab != "" || DestinationMarkerPrefab != "";
    }
}
