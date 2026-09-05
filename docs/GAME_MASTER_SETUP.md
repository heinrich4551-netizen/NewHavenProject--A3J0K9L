# Game Master Setup

## Purpose

The RHD Game Master mission layer is designed so a Game Master can compose missions from reusable scenario entities instead of editing mission source code.

## Current architecture

- `RHD_GM_MissionFramework` — persistent registry and mission definitions.
- `RHD_GM_MissionGameMasterComponent` — scenario-facing component that owns a mission controller.
- `RHD_GM_MissionController` — starts, ticks, completes, fails, times out, and cleans up active missions.
- `RHD_GM_MissionInstance` — runtime state for one mission execution.
- `RHD_GM_MissionTask` — reusable objective/task state.
- `RHD_GM_MissionAdapter` — scenario-specific integration contract.
- `RHD_GM_MissionConfig` — tunable mission parameters.

## Recommended Workbench setup

1. Create a persistent scenario entity for the RHD mission framework.
2. Add `RHD_GM_MissionFramework` to that entity.
3. Create a Game Master integration entity and add `RHD_GM_MissionGameMasterComponent`.
4. In the scenario-specific adapter, map mission IDs to the actual prefab/entity resources available in New Haven.
5. Keep faction, vehicle, AI, marker and task resources in Workbench configuration/adapter code rather than in generic mission scripts.
6. Ensure mission lifecycle calls occur on the authoritative server path.

## Game Master workflow

1. Place or activate a configured mission composition in Game Master.
2. Select the desired mission configuration/difficulty.
3. Start the mission through the scenario's GM integration.
4. The controller creates mission-owned entities through the adapter.
5. Runtime tasks can be added to the mission instance and updated by the adapter.
6. The controller checks timeout, failure and success conditions.
7. On completion/failure, the adapter is called to remove mission-owned entities.

## Why adapters are required

The generic layer must remain reusable. It must not assume a specific faction, vehicle, civilian AI, map position or prefab GUID. Those values belong to the New Haven scenario adapter and Workbench resources.

For civilian/job content, use existing civilian AI supplied by the scenario/framework rather than creating a separate population specifically for the mission.

## Important implementation note

This repository began empty. The source layer is now established, but binary Workbench resources (`.et` and related compiled resource data) cannot be safely fabricated through GitHub text-file operations. Create those resources in Workbench and attach the provided script components. The repository deliberately keeps the source/adapter contract text-based so it remains reviewable and versionable.
