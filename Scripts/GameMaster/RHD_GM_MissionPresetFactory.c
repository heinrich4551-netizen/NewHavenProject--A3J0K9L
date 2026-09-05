class RHD_GM_MissionPresetFactory
{
    static RHD_GM_MissionComposition CreateConvoyPreset()
    {
        RHD_GM_MissionComposition composition = new RHD_GM_MissionComposition(
            "RHD_CONVOY",
            "Dynamic Convoy",
            "Escort a configured convoy through hostile territory using existing scenario assets."
        );

        composition.MissionConfig.Difficulty = 2;
        composition.MissionConfig.EnemyGroups = 2;
        composition.MissionConfig.EnemyUnitsPerGroup = 4;
        composition.MissionConfig.ReinforcementGroups = 1;
        composition.MissionConfig.MissionTimeoutSeconds = 1800.0;

        composition.SpawnConfig.EscortGroups = 2;
        composition.SpawnConfig.ReinforcementGroups = 1;
        composition.SpawnConfig.ReinforcementDelaySeconds = 300.0;
        composition.SpawnConfig.UseExistingCivilianAI = true;

        composition.AddObjective(RHD_GM_ObjectiveFactory.CreateEscortObjective());
        composition.AddObjective(new RHD_GM_MissionObjective(
            "DESTINATION",
            "Reach the destination",
            "Get the convoy to the configured destination."
        ));

        return composition;
    }

    static RHD_GM_MissionComposition CreateSecurePreset()
    {
        RHD_GM_MissionComposition composition = new RHD_GM_MissionComposition(
            "RHD_SECURE",
            "Secure Location",
            "Clear and hold a configured location using existing scenario assets."
        );

        composition.MissionConfig.Difficulty = 2;
        composition.MissionConfig.EnemyGroups = 3;
        composition.MissionConfig.EnemyUnitsPerGroup = 5;
        composition.MissionConfig.ReinforcementGroups = 1;
        composition.MissionConfig.MissionTimeoutSeconds = 1800.0;
        composition.MissionConfig.SpawnDistance = 400.0;

        composition.SpawnConfig.EscortGroups = 0;
        composition.SpawnConfig.ReinforcementGroups = 1;
        composition.SpawnConfig.ReinforcementDelaySeconds = 240.0;
        composition.SpawnConfig.UseExistingCivilianAI = true;

        composition.AddObjective(RHD_GM_ObjectiveFactory.CreateSecureObjective());
        return composition;
    }

    static RHD_GM_MissionComposition CreateRecoveryPreset()
    {
        RHD_GM_MissionComposition composition = new RHD_GM_MissionComposition(
            "RHD_RECOVERY",
            "Recovery",
            "Recover a configured mission objective and leave the area using existing scenario assets."
        );

        composition.MissionConfig.Difficulty = 3;
        composition.MissionConfig.EnemyGroups = 2;
        composition.MissionConfig.EnemyUnitsPerGroup = 5;
        composition.MissionConfig.ReinforcementGroups = 2;
        composition.MissionConfig.MissionTimeoutSeconds = 1500.0;

        composition.SpawnConfig.ReinforcementGroups = 2;
        composition.SpawnConfig.ReinforcementDelaySeconds = 180.0;
        composition.SpawnConfig.UseExistingCivilianAI = true;

        composition.AddObjective(RHD_GM_ObjectiveFactory.CreateRecoveryObjective());
        return composition;
    }

    static RHD_GM_MissionComposition CreateCivilianProtectionPreset()
    {
        RHD_GM_MissionComposition composition = new RHD_GM_MissionComposition(
            "RHD_CIVILIAN_PROTECTION",
            "Civilian Protection",
            "Protect an existing civilian group during a hostile incident."
        );

        composition.MissionConfig.Difficulty = 2;
        composition.MissionConfig.EnemyGroups = 2;
        composition.MissionConfig.EnemyUnitsPerGroup = 4;
        composition.MissionConfig.ReinforcementGroups = 1;
        composition.MissionConfig.MissionTimeoutSeconds = 1200.0;

        composition.SpawnConfig.ReinforcementGroups = 1;
        composition.SpawnConfig.ReinforcementDelaySeconds = 300.0;
        composition.SpawnConfig.UseExistingCivilianAI = true;
        composition.SpawnConfig.CivilianUnits = 0;

        composition.AddObjective(RHD_GM_ObjectiveFactory.CreateCivilianProtectionObjective());
        return composition;
    }

    static RHD_GM_MissionComposition CreateDefensePreset()
    {
        RHD_GM_MissionComposition composition = new RHD_GM_MissionComposition(
            "RHD_DEFENSE",
            "Defense",
            "Defend an existing scenario position against escalating attacks."
        );

        composition.MissionConfig.Difficulty = 3;
        composition.MissionConfig.EnemyGroups = 3;
        composition.MissionConfig.EnemyUnitsPerGroup = 5;
        composition.MissionConfig.ReinforcementGroups = 2;
        composition.MissionConfig.ReinforcementDelaySeconds = 180.0;
        composition.MissionConfig.MissionTimeoutSeconds = 1800.0;
        composition.MissionConfig.SpawnDistance = 400.0;

        composition.SpawnConfig.EscortGroups = 0;
        composition.SpawnConfig.ReinforcementGroups = 2;
        composition.SpawnConfig.ReinforcementDelaySeconds = 180.0;
        composition.SpawnConfig.UseExistingCivilianAI = true;

        composition.AddObjective(RHD_GM_ObjectiveFactory.CreateDefenseObjective());
        return composition;
    }

    static RHD_GM_MissionComposition CreatePatrolPreset()
    {
        RHD_GM_MissionComposition composition = new RHD_GM_MissionComposition(
            "RHD_PATROL",
            "Patrol",
            "Conduct a patrol through an existing scenario area and complete the patrol objective."
        );

        composition.MissionConfig.Difficulty = 1;
        composition.MissionConfig.EnemyGroups = 2;
        composition.MissionConfig.EnemyUnitsPerGroup = 4;
        composition.MissionConfig.ReinforcementGroups = 1;
        composition.MissionConfig.ReinforcementDelaySeconds = 300.0;
        composition.MissionConfig.MissionTimeoutSeconds = 1200.0;

        composition.SpawnConfig.EscortGroups = 0;
        composition.SpawnConfig.ReinforcementGroups = 1;
        composition.SpawnConfig.ReinforcementDelaySeconds = 300.0;
        composition.SpawnConfig.UseExistingCivilianAI = true;

        composition.AddObjective(RHD_GM_ObjectiveFactory.CreatePatrolObjective());
        return composition;
    }

    static RHD_GM_MissionComposition CreateEliminationPreset()
    {
        RHD_GM_MissionComposition composition = new RHD_GM_MissionComposition(
            "RHD_ELIMINATION",
            "Elimination",
            "Eliminate the configured hostile force using existing scenario assets."
        );

        composition.MissionConfig.Difficulty = 3;
        composition.MissionConfig.EnemyGroups = 3;
        composition.MissionConfig.EnemyUnitsPerGroup = 5;
        composition.MissionConfig.ReinforcementGroups = 2;
        composition.MissionConfig.ReinforcementDelaySeconds = 180.0;
        composition.MissionConfig.MissionTimeoutSeconds = 1500.0;

        composition.SpawnConfig.EscortGroups = 0;
        composition.SpawnConfig.ReinforcementGroups = 2;
        composition.SpawnConfig.ReinforcementDelaySeconds = 180.0;
        composition.SpawnConfig.UseExistingCivilianAI = true;

        composition.AddObjective(RHD_GM_ObjectiveFactory.CreateEliminationObjective());
        return composition;
    }
}
