# Exter Mod Menu

Exter is a DirectX 11 and ImGui based GTA V menu focused on a clean interface, responsive keyboard/controller navigation, and modular submenu driven features.

## Highlights

- Elegant dark glass interface with cyan and violet accents.
- Keyboard and controller navigation.
- Modular submenu structure for self, protections, network, weapons, vehicles, teleport, spawner, recovery, miscellaneous, and settings.
- Runtime appearance controls for width, position, colors, sizing, fonts, and scroll speed.
- Built-in command engine with autocomplete and direct-match behavior.
- Vehicle spawner grouped by GTA vehicle classes.
- Feature toggles for player survivability, movement, weapon modifiers, vehicle utility, and world/session helpers.

## Controls

| Action | Keyboard | Controller |
| --- | --- | --- |
| Open or close menu | Insert | RB + Right |
| Select | Enter | A |
| Back | Backspace | B |
| Navigate | Arrow keys | D-pad |

## Feature Overview

### Self

- God Mode
- Beast Jump
- Graceful Landing
- Never Wanted
- No Ragdoll
- Invisible Player
- Super Run
- Heal Player
- Clear Wanted Level

### Weapons

- Infinite Ammo
- Infinite Clip
- Explosive Ammo
- Fire Ammo
- Explosive Melee
- Give Core Loadout
- Remove All Weapons

### Vehicle

- Vehicle God Mode
- Repair Vehicle
- Clean Vehicle
- Max Engine Health

### Teleport

- Save Current Position
- Teleport To Saved Position
- Teleport Forward
- Teleport Up

### Protections

- Block Wanted Level
- Hide Police Radar Blips
- Passive Collision Guard

### Recovery

- Fast Wanted Reset
- Reset Escape Timer
- Restore Wanted Cap

### Miscellaneous

- Disable Phone
- Quiet HUD Helpers
- Clear Area Effects

## Building

1. Open `Exter.sln` in Visual Studio.
2. Select a supported x64 configuration.
3. Build the `Exter` project.

The project vendors its ImGui and MinHook sources under `Exter/src`, so the solution is intended to build from the repository contents without additional source checkouts.

## Project Layout

```text
Exter/
  src/
    commands/        Command registration and tick features
    gui/             Menu drawing, layout types, and input handling
    hooking/         Runtime hooks
    rage/            Native invoker declarations and game class definitions
    renderer/        DirectX and ImGui renderer integration
    script/          Submenu definitions
    util/            Utility helpers
```

## Custom Headers

Custom menu headers can be placed in the storage folder created by the Header settings submenu:

```text
<storage-root>/Exter/Headers
```

Supported image extensions include `.png`, `.jpg`, `.jpeg`, `.bmp`, `.psd`, `.tga`, `.gif`, `.hdr`, `.pic`, `.ppm`, and `.pgm`.

## Notes

- Use only in environments where you are authorized to run modifications.
- Online use may violate game or platform terms. Review applicable rules before use.
- Keep features modular by registering commands in `commands::features::init()` and exposing them through the appropriate submenu.
