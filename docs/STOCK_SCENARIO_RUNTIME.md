# Stock Scenario Runtime Integration

The Game Master framework now includes a stock-only runtime adapter: `RHD_GM_StockScenarioWorldAdapter`.

## What it does

The adapter tracks entities and mission state without inventing resources or dynamically creating custom assets.

It supports registration of:

- Existing stock mission/vehicle entities
- Existing stock hostile entities
- Existing stock civilian entities

It also tracks:

- Convoy destination reached
- Secure-location state
- Recovery completion
- Elimination completion
- Civilian-protection completion

## Game Master setup

1. Add `RHD_GM_MissionGameMasterComponent` to the persistent Game Master/scenario entity.
2. Create an `RHD_GM_MissionWorldBinding` in the scenario configuration.
3. Select the required resources with the Arma Reforger Workbench resource picker.
4. Call `ConfigureStockScenario(binding)` from the authoritative scenario setup path.
5. When a stock scenario entity is selected/created by the scenario, register it with the component:
   - `RegisterStockPrimaryEntity()` for the primary mission entity.
   - `RegisterStockHostile()` for hostile entities.
   - `RegisterExistingStockCivilian()` for protected civilians.
6. Drive mission conditions from authoritative scenario logic using the stock state setters.
7. Call `TickMissions(deltaSeconds)` from the authoritative update path.

## Condition setters

The component exposes:

- `SetStockMissionDestinationReached()`
- `SetStockMissionLocationSecure()`
- `SetStockMissionRecoveryComplete()`
- `SetStockMissionEliminationComplete()`
- `SetStockCivilianProtectionComplete()`

These setters only update mission state. They do not spawn, delete, or replace game assets.

## Stock-only rule

No custom vehicles, weapons, factions, infantry, civilian populations, markers, map objects, or fabricated resource GUIDs are included by this runtime layer.

Actual resource selection remains a Workbench operation. The framework deliberately does not claim that a string field alone can instantiate an engine resource.

## Cleanup

The stock adapter releases its mission tracking state when a mission ends. Existing scenario entities are not automatically deleted. This prevents the framework from removing stock entities that it did not create or explicitly own.
