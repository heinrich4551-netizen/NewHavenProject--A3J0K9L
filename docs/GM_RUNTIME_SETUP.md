# Game Master Runtime Setup

## Purpose

`RHD_GM_MissionGameMasterComponent` is the single scenario-facing entry point for the mission framework.

On initialization it creates the mission controller, creates the activation API, and registers the default mission library.

## Default missions

- `RHD_CONVOY`
- `RHD_SECURE`
- `RHD_RECOVERY`
- `RHD_CIVILIAN_PROTECTION`

## Workbench integration

1. Create or use a persistent scenario entity.
2. Add `RHD_GM_MissionFramework` to the persistent mission service entity.
3. Add `RHD_GM_MissionGameMasterComponent` to the Game Master/scenario integration entity.
4. Create a concrete `RHD_GM_MissionWorldAdapter` in the New Haven scenario layer.
5. Configure a `RHD_GM_MissionWorldBinding` with actual Workbench prefab/resource references.
6. Construct and assign `RHD_GM_MissionScenarioAdapter` using the world adapter and binding.
7. Assign the scenario adapter to the mission controller.
8. Call `TickMissions(deltaSeconds)` from the authoritative scenario update path.

## GM activation API

The component exposes:

- `GetAvailableMissionIds()` — list missions available to the GM layer.
- `StartMissionById(missionId)` — starts a registered mission composition.
- `StopMission(instance, failed)` — ends an active mission.
- `GetEventDispatcher()` — exposes mission lifecycle events to UI/admin consumers.

This keeps GM-facing code independent of individual mission implementation details.

## Important runtime boundary

The generic source framework does not fabricate New Haven prefab GUIDs, faction resources, map coordinates, or binary Workbench entities. Those values belong in the concrete scenario adapter and Workbench configuration.

The existing civilian population remains the civilian integration target. The generic mission framework does not create job-specific civilian AI populations.

## Server authority

Mission start, stop, objective state, reinforcement scheduling, success/failure evaluation, and cleanup should be driven by the authoritative server/scenario runtime. Client-facing GM UI should request actions through the scenario's authoritative integration rather than directly manipulating mission state.

## Current status

The source-level runtime architecture is implemented. Concrete Workbench resource instantiation remains scenario-specific and must be wired against actual New Haven resources in Workbench.
