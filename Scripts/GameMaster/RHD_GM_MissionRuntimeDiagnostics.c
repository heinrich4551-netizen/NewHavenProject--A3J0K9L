class RHD_GM_MissionRuntimeDiagnostics
{
    // Lightweight diagnostics for Game Master setup. This reports configuration
    // state only; it never creates or substitutes game assets.

    static bool IsReady(RHD_GM_MissionGameMasterComponent component)
    {
        if (!component)
            return false;

        return component.IsBootstrapped() && component.IsScenarioConfigured();
    }

    static bool HasWorldAdapter(RHD_GM_MissionGameMasterComponent component)
    {
        if (!component || !component.GetController())
            return false;

        return component.GetController().GetAdapter() != null;
    }

    static bool HasScenarioAdapter(RHD_GM_MissionGameMasterComponent component)
    {
        if (!component)
            return false;

        return component.GetScenarioAdapter() != null;
    }

    static int GetAvailableMissionCount(RHD_GM_MissionGameMasterComponent component)
    {
        if (!component)
            return 0;

        return component.GetAvailableMissionIds().Count();
    }

    static string GetStatus(RHD_GM_MissionGameMasterComponent component)
    {
        if (!component)
            return "Component missing";

        if (!component.IsBootstrapped())
            return "Not bootstrapped";

        if (!HasScenarioAdapter(component))
            return "Awaiting stock Workbench scenario configuration";

        if (!HasWorldAdapter(component))
            return "World adapter missing";

        return "Ready";
    }
}
