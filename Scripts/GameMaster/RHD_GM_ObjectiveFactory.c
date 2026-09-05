class RHD_GM_ObjectiveFactory
{
    static RHD_GM_MissionObjective CreateEscortObjective()
    {
        return new RHD_GM_MissionObjective(
            "ESCORT",
            "Escort the group",
            "Protect the assigned group until it reaches its destination."
        );
    }

    static RHD_GM_MissionObjective CreateSecureObjective()
    {
        return new RHD_GM_MissionObjective(
            "SECURE",
            "Secure the location",
            "Clear hostile forces and secure the configured objective area."
        );
    }

    static RHD_GM_MissionObjective CreateRecoveryObjective()
    {
        return new RHD_GM_MissionObjective(
            "RECOVERY",
            "Recover the objective",
            "Locate and recover the configured cargo, person, or mission item."
        );
    }

    static RHD_GM_MissionObjective CreateEliminationObjective()
    {
        return new RHD_GM_MissionObjective(
            "ELIMINATION",
            "Eliminate the hostile force",
            "Eliminate the configured hostile objective."
        );
    }

    static RHD_GM_MissionObjective CreateCivilianProtectionObjective()
    {
        return new RHD_GM_MissionObjective(
            "CIVILIAN_PROTECTION",
            "Protect civilians",
            "Keep the existing civilian group alive until the mission is resolved."
        );
    }

    static RHD_GM_MissionObjective CreateDefenseObjective()
    {
        return new RHD_GM_MissionObjective(
            "DEFENSE",
            "Defend the position",
            "Hold the configured position until the defense condition is satisfied."
        );
    }

    static RHD_GM_MissionObjective CreatePatrolObjective()
    {
        return new RHD_GM_MissionObjective(
            "PATROL",
            "Complete the patrol",
            "Visit the configured patrol objectives and return or complete the assigned route."
        );
    }
}
