class RHD_GM_MissionWorldBinding
{
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

    void Validate()
    {
        if (!ObjectiveLabel)
            ObjectiveLabel = "Mission Objective";

        if (!DestinationLabel)
            DestinationLabel = "Mission Destination";
    }
}
