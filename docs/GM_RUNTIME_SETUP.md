# Game Master Runtime Setup

## Purpose

`RHD_GM_MissionGameMasterComponent` is the single scenario-facing entry point for the mission framework.

On initialization it creates the mission controller, creates the activation API, and registers the default mission library.

## Default missions

- `RHD_CONVOY`
- `RHD_SECURE`
- `RHD_RECOVERY`
- `RHD_CIVILIAN_PROTECTION`
- `RHD_DEFENSE`
- `RHD_PATROL`
- `RHD_ELIMINATION`

## Stock Arma Reforger asset policy

The framework is designed to use **only assets already shipped with Arma Reforger and available to the active Workbench project**.

It does not require or invent:

- custom vehicle prefabs
- custom infantry/faction prefabs
- custom civilian AI populations
- fabricated prefab GUIDs
- custom marker resources
- custom map objects

Use the `RHD_GM_ArmaReforgerAssetCatalog` as a configuration boundary. Select the actual stock resources from Workbench and assign them to the profile/binding used by the scenario adapter.

The framework intentionally does not guess resource paths or GUIDs because those references must match the exact Arma Reforger version and installed project content.

## Workbench integration

1. Create or use a persistent scenario entity.
2. Add `RHD_GM_MissionFramework` to the persistent mission service entity.
3. Add `RHD_GM_MissionGameMasterComponent` to the Game Master/scenario integration entity.
4. Use a concrete `RHD_GM_MissionWorldAdapter` in the scenario layer.
5. Configure `RHD_GM_MissionWorldBinding` with **stock Arma Reforger** prefab/resource references selected in Workbench.
6. Do not enter fabricated GUIDs. Use the resource picker and select resources actually present in the project.
7. Construct and assign `RHD_GM_MissionScenarioAdapter` using the world adapter and binding.
8. Assign the scenario adapter to the mission controller.
9. Call `TickMissions(deltaSeconds)` from the authoritative scenario update path.

## Existing civilian AI

Civilian missions use the existing civilian population/AI supplied by the scenario rather than creating a separate job-specific civilian population. The world adapter should bind to already-existing civilian entities or groups.

## GM activation API

The component exposes:

- `GetAvailableMissionIds()` — list missions available to the GM layer.
- `StartMissionById(missionId)` — starts a registered mission composition.
- `StopMission(instance, failed)` — ends an active mission.
- `CompleteObjective(instance, objectiveId)` — authoritatively completes an objective and emits its event.
- `FailObjective(instance, objectiveId)` — authoritatively fails an objective and emits its event.
- `GetEventDispatcher()` — exposes mission lifecycle events to UI/admin consumers.

This keeps GM-facing code independent of individual mission implementation details.

## Important runtime boundary

The generic source framework does not fabricate New Haven prefab GUIDs, faction resources, map coordinates, or binary Workbench entities. All concrete resources must be selected from the existing Arma Reforger content available in Workbench.

## Server authority

Mission start, stop, objective state, reinforcement scheduling, success/failure evaluation, and cleanup should be driven by the authoritative server/scenario runtime. Client-facing GM UI should request actions through the scenario's authoritative integration rather than directly manipulating mission state.

## Current status

The source-level runtime architecture and seven default mission definitions are implemented. The remaining scenario-side step is selecting and wiring the appropriate **existing Arma Reforger stock resources** in Workbench; no new game assets are required by the framework.