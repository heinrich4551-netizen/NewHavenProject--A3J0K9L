# RHD Game Master — Stock Asset Workflow

## Purpose

The RHD Game Master mission framework is source/configuration driven. It does not create replacement game assets and does not require custom vehicles, weapons, factions, infantry, civilian models, markers, or map objects.

All concrete world resources must come from assets already shipped with Arma Reforger and selected in the active Workbench project.

## Workbench workflow

1. Open the RHD project in Arma Reforger Workbench.
2. Add the Game Master mission component to the persistent scenario entity used by the mission.
3. Provide a concrete `RHD_GM_MissionWorldAdapter` implementation for the scenario.
4. Create/configure an `RHD_GM_MissionWorldBinding` instance in the scenario integration layer.
5. Use the Workbench resource picker to select existing Arma Reforger resources for the binding fields:
   - `PrimaryPrefab`
   - `HostileGroupPrefab`
   - `ReinforcementPrefab`
   - `CivilianGroupPrefab`
   - `StartMarkerPrefab`
   - `ObjectiveMarkerPrefab`
   - `DestinationMarkerPrefab`
6. Do not paste invented GUIDs or paths into the binding. The resource picker is the source of truth for the installed Reforger version.
7. Keep civilian integration pointed at existing civilian AI/groups. The framework does not create a replacement civilian system.
8. Configure the mission's positions, destinations, and other map-specific references in the scenario/Workbench layer rather than hard-coding them in generic scripts.

## Missing-resource policy

`RHD_GM_MissionWorldBinding` exposes explicit controls for optional stock resources:

- `AllowMissingVehicle`
- `AllowMissingHostiles`
- `AllowMissingReinforcements`
- `AllowMissingMarkers`

These options prevent the generic framework from silently inventing an asset when a stock resource is not selected.

A mission may therefore be used in an existing-entity scenario when the scenario adapter supports that mode. The generic source layer still does not discover or manufacture arbitrary map entities by itself.

## Mission types

The default catalog contains:

- `RHD_CONVOY`
- `RHD_SECURE`
- `RHD_RECOVERY`
- `RHD_CIVILIAN_PROTECTION`
- `RHD_DEFENSE`
- `RHD_PATROL`
- `RHD_ELIMINATION`

Their mission behavior is intentionally delegated to `RHD_GM_MissionWorldAdapter`. This allows the same mission framework to operate with different stock Reforger resources without embedding version-specific resource IDs in the generic scripts.

## Server authority

Mission start, objective completion/failure, reinforcement state, timeout handling, success checks, failure checks, and cleanup should be driven from the authoritative scenario/Game Master update path.

Only entities created or explicitly tracked by the mission integration should be cleaned up. Existing civilian and scenario entities must not be deleted merely because a mission ends.

## Important limitation

The repository contains the script contracts and plug-and-play configuration boundary, but a concrete Workbench adapter is still required to connect these contracts to actual stock Reforger entities. The repository intentionally does not fabricate prefab GUIDs or binary Workbench resources.
