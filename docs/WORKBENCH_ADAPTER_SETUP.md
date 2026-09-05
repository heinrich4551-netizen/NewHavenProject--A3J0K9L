# Workbench Adapter Setup

This is the boundary between the reusable Game Master mission framework and actual New Haven world resources.

## Required scenario pieces

Create a persistent scenario/framework entity and provide a concrete implementation of `RHD_GM_MissionWorldAdapter`.

Configure a `RHD_GM_MissionWorldBinding` for each mission family with:

- Primary mission prefab, when applicable
- Hostile group prefab
- Reinforcement prefab
- Existing civilian group/population reference
- Objective marker prefab
- Destination marker prefab
- Human-readable marker labels

Do not put guessed GUIDs into the generic scripts.

## World adapter responsibilities

The concrete adapter is responsible for the actual engine/resource operations:

1. Spawn the configured hostile groups.
2. Spawn the configured mission vehicle/object.
3. Bind to existing civilian AI when a civilian objective is used.
4. Create the configured mission markers.
5. Determine whether the mission entity is alive.
6. Determine whether a destination was reached.
7. Determine whether a location is secure.
8. Determine whether a recovery objective is complete.
9. Determine whether an elimination objective is complete.
10. Determine whether protected civilians remain alive.
11. Remove only entities owned by the completed/failed mission.

## Why this layer exists

Workbench resource references and exact world-spawn APIs vary by scenario composition. Keeping those operations behind one adapter makes the mission definitions reusable and prevents the framework from depending on fabricated or map-specific identifiers.

## GM workflow

After the adapter/resource layer is configured, a Game Master should only need to select a mission preset, choose the configured scenario location/resources, adjust difficulty if desired, and activate it. The runtime controller then owns timeout, objective state, success/failure checks, reinforcement state, and cleanup.

## Important

The source repository can define the contracts and reusable logic, but Workbench-authored prefabs/resources must still be created and wired in the actual Arma Reforger project. This repository does not pretend that text files alone create those binary Workbench assets.
