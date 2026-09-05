# Mission Composition

The mission system now separates **what a mission is** from **how New Haven creates its entities**.

## Composition

`RHD_GM_MissionComposition` groups:

- Mission identity and description
- `RHD_GM_MissionConfig`
- `RHD_GM_MissionSpawnConfig`
- Required and optional objectives

This allows a Workbench-authored mission preset to be reused without changing mission controller code.

## Objectives

Use `RHD_GM_MissionObjective` for objectives such as:

- Escort convoy
- Reach destination
- Secure location
- Recover cargo
- Eliminate hostile force
- Protect civilian group

Required objectives control mission completion. Optional objectives can be used for bonus rewards or additional GM direction without blocking completion.

## Entity ownership

`RHD_GM_MissionOwnership` is the ownership boundary for mission-created entities. An adapter should track every entity it creates and only clean up entities tracked by that mission.

This prevents mission cleanup from accidentally removing unrelated Game Master compositions, ambient civilians, or other missions.

## Reinforcements

`RHD_GM_ReinforcementState` tracks requested groups, groups already deployed, and the next reinforcement delay. The scenario adapter decides how a reinforcement group is actually created.

## New Haven integration rule

The generic framework does not contain guessed prefab GUIDs or map-specific coordinates. Workbench resources and New Haven-specific entity creation remain in the adapter layer.

For civilian objectives, use existing civilian AI supplied by the scenario/framework whenever possible. Do not create a separate civilian population for each mission.
