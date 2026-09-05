# Dynamic Convoy Mission

## Purpose

A reusable Game Master mission template where the GM chooses the mission location and configuration while the framework owns mission state.

## Planned player flow

1. GM activates a convoy mission.
2. A configured convoy package is created through the scenario adapter.
3. Players receive the convoy objective.
4. Enemy pressure is created from configured groups and reinforcement settings.
5. The convoy is considered successful when it reaches its destination.
6. The mission fails when the convoy is destroyed or the configured timeout expires.
7. Mission-owned entities are cleaned up by the scenario adapter.

## Configuration

`RHD_GM_MissionConfig` exposes:

- Enabled
- Difficulty: 1–5
- Enemy groups: 1–20
- Units per group: 1–20
- Reinforcement groups: 0–20
- Mission timeout
- Spawn distance
- Cleanup distance

## Adapter boundary

The generic mission does not assume a particular faction, vehicle class, weapon, map coordinate, or civilian prefab. Those values belong in the New Haven scenario adapter/prefab configuration.

This keeps the mission reusable and prevents scenario-specific identifiers from breaking the framework.
