class RHD_GM_MissionBootstrap
{
    static void RegisterDefaultMissions(RHD_GM_MissionActivation activation)
    {
        if (!activation)
            return;

        activation.RegisterMission(RHD_GM_MissionPresetFactory.CreateConvoyPreset());
        activation.RegisterMission(RHD_GM_MissionPresetFactory.CreateSecurePreset());
        activation.RegisterMission(RHD_GM_MissionPresetFactory.CreateRecoveryPreset());
        activation.RegisterMission(RHD_GM_MissionPresetFactory.CreateCivilianProtectionPreset());
    }
}
