# Game Master setup

## Goal

The framework is intentionally configured around a small number of persistent scenario entities. The Game Master should not need to edit mission script source code for normal operation.

## Initial Workbench setup

1. Open the New Haven scenario in Reforger Workbench.
2. Create or use a persistent framework entity in the scenario.
3. Add the `RHD_GM_MissionFramework` ScriptComponent to that entity.
4. Save the scenario.
5. Create the Game Master-facing mission prefabs/entities in Workbench and connect their configuration to the framework.

## Recommended GM workflow

- Place the mission entity at the desired objective/start area.
- Configure difficulty and mission parameters in the entity/component properties.
- Start the mission from the Game Master workflow.
- The mission controller owns state and cleanup; the GM does not need to manually manage every spawned unit.

## Important architecture rule

Mission-specific choices must be adapter/config driven. Do not hard-code faction, vehicle, civilian, or map-specific prefab identifiers into the generic mission controller.

For jobs that involve civilians, reference existing civilian AI supplied by the scenario/framework instead of spawning job-specific civilian populations.

## Current implementation status

The repository was empty when development started. The initial script layer now contains:

- central framework component
- mission definition model
- mission registry
- configurable mission settings
- dynamic convoy mission lifecycle template

The next implementation step is the Workbench prefab/resource layer that exposes these controls directly to Game Master, followed by concrete spawn/task/marker adapters for the New Haven scenario.
