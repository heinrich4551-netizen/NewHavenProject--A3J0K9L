class RHD_GM_MissionCatalog
{
    static array<string> GetDefaultMissionIds()
    {
        ref array<string> ids = new array<string>();
        ids.Insert("RHD_CONVOY");
        ids.Insert("RHD_SECURE");
        ids.Insert("RHD_RECOVERY");
        ids.Insert("RHD_CIVILIAN_PROTECTION");
        ids.Insert("RHD_DEFENSE");
        ids.Insert("RHD_PATROL");
        ids.Insert("RHD_ELIMINATION");
        return ids;
    }

    static RHD_GM_MissionComposition CreateById(string missionId)
    {
        if (missionId == "RHD_CONVOY")
            return RHD_GM_MissionPresetFactory.CreateConvoyPreset();

        if (missionId == "RHD_SECURE")
            return RHD_GM_MissionPresetFactory.CreateSecurePreset();

        if (missionId == "RHD_RECOVERY")
            return RHD_GM_MissionPresetFactory.CreateRecoveryPreset();

        if (missionId == "RHD_CIVILIAN_PROTECTION")
            return RHD_GM_MissionPresetFactory.CreateCivilianProtectionPreset();

        if (missionId == "RHD_DEFENSE")
            return RHD_GM_MissionPresetFactory.CreateDefensePreset();

        if (missionId == "RHD_PATROL")
            return RHD_GM_MissionPresetFactory.CreatePatrolPreset();

        if (missionId == "RHD_ELIMINATION")
            return RHD_GM_MissionPresetFactory.CreateEliminationPreset();

        return null;
    }
}
