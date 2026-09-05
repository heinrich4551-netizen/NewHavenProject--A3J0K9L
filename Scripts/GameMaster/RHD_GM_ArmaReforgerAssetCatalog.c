// Stock-asset configuration boundary for RHD Game Master missions.
// This file intentionally contains no fabricated prefab GUIDs or custom assets.
// Populate the string fields in Workbench using assets already shipped with
// the active Arma Reforger installation/project.

class RHD_GM_ArmaReforgerAssetProfile
{
    string Name;
    string VehiclePrefab;
    string HostileGroupPrefab;
    string ReinforcementGroupPrefab;
    string CivilianGroupPrefab;
    string StartMarkerPrefab;
    string ObjectiveMarkerPrefab;
    string DestinationMarkerPrefab;

    bool UseExistingCivilianAI = true;

    void RHD_GM_ArmaReforgerAssetProfile(string name)
    {
        Name = name;
    }

    bool HasMissionAssets()
    {
        return VehiclePrefab || HostileGroupPrefab || CivilianGroupPrefab;
    }

    void ClearCustomReferences()
    {
        VehiclePrefab = "";
        HostileGroupPrefab = "";
        ReinforcementGroupPrefab = "";
        CivilianGroupPrefab = "";
        StartMarkerPrefab = "";
        ObjectiveMarkerPrefab = "";
        DestinationMarkerPrefab = "";
    }
}

class RHD_GM_ArmaReforgerAssetCatalog
{
    // These profiles are configuration slots, not invented game resources.
    // The framework never assumes a GUID, faction, vehicle, or civilian prefab.
    static RHD_GM_ArmaReforgerAssetProfile CreateDefaultProfile()
    {
        return new RHD_GM_ArmaReforgerAssetProfile("Arma Reforger Stock Assets");
    }

    static RHD_GM_ArmaReforgerAssetProfile CreateInfantryProfile()
    {
        RHD_GM_ArmaReforgerAssetProfile profile = new RHD_GM_ArmaReforgerAssetProfile("Stock Infantry");
        profile.UseExistingCivilianAI = true;
        return profile;
    }

    static RHD_GM_ArmaReforgerAssetProfile CreateVehicleProfile()
    {
        RHD_GM_ArmaReforgerAssetProfile profile = new RHD_GM_ArmaReforgerAssetProfile("Stock Vehicle");
        profile.UseExistingCivilianAI = true;
        return profile;
    }

    static bool ValidateProfile(RHD_GM_ArmaReforgerAssetProfile profile)
    {
        if (!profile)
            return false;

        // At least one stock asset reference must be supplied by Workbench.
        return profile.HasMissionAssets();
    }
}
