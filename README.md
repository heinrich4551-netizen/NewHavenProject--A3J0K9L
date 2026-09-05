# New Haven Project — RHD Game Master Mission Framework

A plug-and-play Arma Reforger mission scripting foundation designed for Game Master workflows.

## Design goals

- Game Master friendly mission activation.
- Configuration/adapter driven mission behavior.
- Multiplayer/server authoritative mission state.
- Reusable mission definitions rather than one-off scripts.
- Existing civilian AI can be referenced by adapters; mission jobs do not require job-specific civilian spawning.
- Clear separation between mission logic, configuration, and Game Master integration.

## Current module

`RHD_GM_MissionFramework` provides the central mission registry and lifecycle API. It is intended to be attached to a persistent mission/framework entity in the scenario.

The first mission template is the Dynamic Convoy framework documented in `docs/DYNAMIC_CONVOY.md`.

## Repository layout

```text
Scripts/
  GameMaster/
    RHD_GM_MissionFramework.c
    RHD_GM_MissionDefinition.c
    RHD_GM_MissionRegistry.c
    RHD_GM_ConvoyMission.c
    RHD_GM_MissionConfig.c

docs/
  GAME_MASTER_SETUP.md
  DYNAMIC_CONVOY.md
```

## Important

This repository starts empty, so this commit establishes the script architecture and implementation contract. Reforger Workbench prefab/resource files should be created in the mod project and linked to these scripts rather than relying on generated binary resources.
