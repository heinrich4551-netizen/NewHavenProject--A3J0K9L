# Game Master Mission Library

The framework now provides reusable mission compositions for common Game Master scenarios.

| Mission | ID | Purpose |
|---|---|---|
| Dynamic Convoy | `RHD_CONVOY` | Escort a configured convoy to destination |
| Secure Location | `RHD_SECURE` | Clear and secure a location |
| Recovery | `RHD_RECOVERY` | Recover a configured objective |
| Civilian Protection | `RHD_CIVILIAN_PROTECTION` | Protect an existing civilian group |

## How the library is intended to work

1. Game Master selects a mission composition/preset.
2. The scenario adapter supplies the actual New Haven resources and locations.
3. The controller creates and tracks the runtime mission instance.
4. Objectives provide the mission state that the GM-facing layer can display.
5. Reinforcement state controls additional hostile group requests.
6. Mission-owned entities are tracked separately for safe cleanup.

## No hard-coded scenario assets

The preset factory intentionally does **not** contain prefab GUIDs, faction resource IDs, or map coordinates. Those values belong to Workbench-authored scenario configuration.

This keeps the same mission library reusable across different New Haven layouts and future scenarios.

## Civilian integration

Civilian Protection uses `UseExistingCivilianAI = true` and does not request a mission-specific civilian population. The scenario adapter is responsible for identifying an existing civilian group/population and attaching the mission objective to it.

## Production integration status

The reusable composition and state layer is now present in source. Actual spawning, marker creation, objective-world binding, and Workbench resource references still belong in the concrete scenario adapter. No fabricated prefab IDs are used.
