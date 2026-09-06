# Workbench Adapter Setup

This is the boundary between the reusable Game Master mission framework and actual New Haven world resources.

## Stock-only runtime adapter

The repository now includes `RHD_GM_StockScenarioWorldAdapter`.

It is deliberately designed around **existing stock Arma Reforger entities supplied by the active Workbench scenario**. It does not invent prefab paths, GUIDs, factions, vehicles, civilians, markers, or map coordinates.

The adapter provides a concrete runtime state layer for:

- primary mission entities
- hostile entities
- existing civilian entities
- convoy destination state
- secure-location state
- recovery state
- elimination state
- civilian-protection state

## Required scenario pieces

Create a persistent scenario/framework entity and configure the Game Master component with the stock adapter.

Configure a `RHD_GM_MissionWorldBinding` using resources selected from the active Workbench project:

- Primary mission prefab, when applicable
- Hostile group prefab
- Reinforcement prefab
- Existing civilian group/population reference
- Objective marker prefab
- Destination marker prefab
- Human-readable marker labels

Do not put guessed GUIDs into the generic scripts.

## Stock entity registration

`RHD_GM_StockScenarioWorldAdapter` exposes registration methods for entities that already exist in the scenario:

- `RegisterPrimaryEntity(instance, entity)`
- `RegisterHostile(instance, entity)`
- `RegisterCivilian(instance, entity)`

Mission state can then be updated by authoritative scenario logic with:

- `SetDestinationReached(instance, true)`
- `SetLocationSecure(instance, true)`
- `SetRecoveryComplete(instance, true)`
- `SetObjectiveEliminated(instance, true)`
- `SetCivilianProtectionComplete(instance, true)`

These methods allow existing Reforger systems, scenario logic, or GM integrations to report world events without the framework manufacturing assets.

## Important spawning boundary

The stock adapter intentionally does **not** fake dynamic spawning by treating a prefab string as an already-created entity. The current source contract acknowledges configured stock resources, while actual entity creation must be performed by a Workbench/engine integration that uses the exact APIs available to the installed Arma Reforger version.

This avoids shipping unverified engine calls or fabricated resource identifiers.

## Mission conditions

- Convoy succeeds when the registered primary entity is alive and `SetDestinationReached()` has been reported.
- Secure/Defense/Patrol succeed when `SetLocationSecure()` has been reported and all required mission objectives are complete.
- Recovery succeeds when `SetRecoveryComplete()` has been reported and required objectives are complete.
- Elimination succeeds when the registered hostile entities are no longer alive, or `SetObjectiveEliminated()` has been reported.
- Civilian Protection succeeds when `SetCivilianProtectionComplete()` has been reported and required objectives are complete.
- Civilian Protection fails when a registered protected civilian reference is no longer valid.

## Cleanup

The stock adapter never deletes scenario-owned stock entities. It only releases its runtime tracking state when a mission ends. This prevents a mission cleanup operation from accidentally deleting unrelated scenario content.

## GM component

`RHD_GM_MissionGameMasterComponent.ConfigureStockScenario()` is the convenience entry point for assigning the stock world adapter and mission binding.

## Why this layer exists

Workbench resource references and exact world-spawn APIs vary by scenario composition and installed game version. Keeping resource selection and runtime state behind one adapter makes the mission definitions reusable without embedding fabricated or map-specific identifiers.

## GM workflow

1. Place the stock Reforger entities you want to use in the scenario.
2. Create the persistent mission/Game Master integration entity.
3. Configure the mission binding with stock resources using Workbench's resource picker.
4. Create/configure `RHD_GM_StockScenarioWorldAdapter` in the authoritative scenario integration.
5. Register the relevant existing stock entities with the active mission instance.
6. Report destination/security/recovery/elimination/protection events to the adapter.
7. Call `TickMissions(deltaSeconds)` from the authoritative runtime path.
8. Activate missions through `StartMissionById()`.

No new game assets are required by this adapter.
