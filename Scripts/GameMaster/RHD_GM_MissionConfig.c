class RHD_GM_MissionConfig
{
    bool Enabled = true;
    int Difficulty = 1;
    int EnemyGroups = 2;
    int EnemyUnitsPerGroup = 4;
    int ReinforcementGroups = 1;
    float ReinforcementDelaySeconds = 300.0;
    float MissionTimeoutSeconds = 1800.0;
    float SpawnDistance = 500.0;
    float CleanupDistance = 1500.0;

    void ClampValues()
    {
        if (Difficulty < 1) Difficulty = 1;
        if (Difficulty > 5) Difficulty = 5;
        if (EnemyGroups < 1) EnemyGroups = 1;
        if (EnemyGroups > 20) EnemyGroups = 20;
        if (EnemyUnitsPerGroup < 1) EnemyUnitsPerGroup = 1;
        if (EnemyUnitsPerGroup > 20) EnemyUnitsPerGroup = 20;
        if (ReinforcementGroups < 0) ReinforcementGroups = 0;
        if (ReinforcementGroups > 20) ReinforcementGroups = 20;
        if (ReinforcementDelaySeconds < 30.0) ReinforcementDelaySeconds = 30.0;
        if (MissionTimeoutSeconds < 60.0) MissionTimeoutSeconds = 60.0;
        if (SpawnDistance < 100.0) SpawnDistance = 100.0;
        if (CleanupDistance < SpawnDistance) CleanupDistance = SpawnDistance;
    }
}
