# Game Master Mission Presets

These presets are configuration targets for Workbench. They keep normal GM setup fast while allowing scenario authors to override individual values.

## Convoy — Easy

- Difficulty: 1
- Escort groups: 1
- Reinforcement groups: 0
- Mission timeout: 1800 seconds
- Escort spawn radius: 75 meters
- Civilian AI: existing scenario population only

## Convoy — Standard

- Difficulty: 2
- Escort groups: 2
- Reinforcement groups: 1
- Mission timeout: 1800 seconds
- Escort spawn radius: 100 meters
- Reinforcement delay: 300 seconds
- Civilian AI: existing scenario population only

## Convoy — Hard

- Difficulty: 4
- Escort groups: 4
- Reinforcement groups: 2
- Mission timeout: 2400 seconds
- Escort spawn radius: 150 meters
- Reinforcement delay: 180 seconds
- Civilian AI: existing scenario population only

## Convoy — Extreme

- Difficulty: 5
- Escort groups: 6
- Reinforcement groups: 4
- Mission timeout: 2700 seconds
- Escort spawn radius: 200 meters
- Reinforcement delay: 120 seconds
- Civilian AI: existing scenario population only

## Resource mapping

The following fields are deliberately strings because the generic source layer must not guess New Haven resource identifiers:

- `ConvoyVehiclePrefab`
- `EscortGroupPrefab`
- `ReinforcementGroupPrefab`
- `CivilianAIGroupPrefab`
- `StartMarkerPrefab`
- `ObjectiveMarkerPrefab`
- `DestinationMarkerPrefab`

Populate these from actual Workbench resources when building the New Haven scenario adapter.
