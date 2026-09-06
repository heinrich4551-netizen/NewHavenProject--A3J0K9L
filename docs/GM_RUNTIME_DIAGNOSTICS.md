# GM Runtime Diagnostics

`RHD_GM_MissionRuntimeDiagnostics` provides lightweight checks for the Game Master mission component.

## Checks

- `IsReady(component)` — bootstrapped and scenario-configured.
- `HasWorldAdapter(component)` — a mission adapter is assigned.
- `HasScenarioAdapter(component)` — the stock-asset scenario adapter is assigned.
- `GetAvailableMissionCount(component)` — number of registered mission compositions.
- `GetStatus(component)` — human-readable setup state.

## Expected setup states

### `Not bootstrapped`

The Game Master component has not completed initialization.

### `Awaiting stock Workbench scenario configuration`

The framework is loaded, but the scenario has not been connected to a concrete world adapter and stock-asset binding.

### `World adapter missing`

A scenario adapter exists but its world implementation is unavailable.

### `Ready`

The Game Master component has bootstrapped and a scenario adapter has been configured.

## Stock-only policy

Diagnostics do not create, substitute, or download any assets. The framework continues to require actual Arma Reforger assets selected in Workbench.

The diagnostics class is source-only and does not replace the required Workbench scenario wiring.
