class RHD_GM_MissionValidation
{
    static bool ValidateComposition(RHD_GM_MissionComposition composition)
    {
        if (!composition)
            return false;

        if (!composition.Id || !composition.DisplayName)
            return false;

        if (!composition.MissionConfig || !composition.SpawnConfig)
            return false;

        composition.MissionConfig.ClampValues();
        composition.SpawnConfig.ClampValues();

        if (composition.Objectives.Count() <= 0)
            return false;

        return true;
    }

    static bool ValidateBinding(RHD_GM_MissionWorldBinding binding)
    {
        if (!binding)
            return false;

        binding.Validate();

        if (!binding.PrimaryPrefab && !binding.HostileGroupPrefab && !binding.CivilianGroupPrefab)
            return false;

        return true;
    }
}
