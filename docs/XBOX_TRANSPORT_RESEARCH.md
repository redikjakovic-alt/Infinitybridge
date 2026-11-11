# Xbox 360 transport investigation

## Findings so far

The Disney Infinity portal audit documents this Xbox 360 gateway path:

- OUT: `XInputBeyondSetRaw(32, buf)`
- IN: `XInputBeyondGetRaw`
- OUT frame prefix: `0B 15`
- The 32-byte Disney protocol packet starts at offset 2.

Reference: [DisneyInfinityPortal — technical audit](https://github.com/LucasLhomme/DisneyInfinityPortal/blob/31852bac27ae94baa6540b86fd388b0ff45332de/docs/AUDIT.md), section 3.6.

This establishes how the game-side transport is described in the audit, but **does not establish the import library, ordinal, complete C signatures, calling convention, or runtime lookup mechanism**.

## Important distinction

Xbox 360 executables are XEX2 containers around a big-endian PowerPC image. The XEX import metadata identifies imported libraries and ordinal-based imports. A textual function name is not guaranteed to appear in the executable's ordinary import table.

Useful format references:

- [XEX2 format notes](https://reverseengineering.wiki/index.php/Format%3AXEX2_%28Xbox_360_executable%29)
- [Free60 XEX format](https://free60.org/System-Software/Formats/XEX/)
- [XexTool](https://github.com/Team-Resurgent/XexTool) — `-l` prints extended info; `-b` dumps the basefile; `-i` emits an IDC description.
- [xex2ool](https://github.com/landaire/acceleration/tree/main/crates/xex2ool) — its `imports` command lists import libraries and imported ordinals/names.

## Why we need the actual game executable

The repository audit is for Disney Infinity 3.0 Gold Edition on PC, although it documents the engine's Xbox 360 gateway path. Our target is the user's Xbox 360 copy of Disney Infinity 1.0. We must inspect that exact title's `default.xex`; we must not assume that a function's import pattern is identical between releases.

The inspection must answer:

1. Which import libraries does this exact `default.xex` use?
2. Are any relevant Beyond/raw-input imports represented in the static imports?
3. Are there runtime module lookup calls that could resolve a function not listed as a named static import?
4. What call sites use the two-byte `0B 15` frame and the raw-input functions?
5. What argument and return conventions are supported by the actual call sites?

If the functions are resolved dynamically, the static import list alone will not identify their ordinals or addresses. The call sites and lookup code must then be traced in the PPC disassembly.

## Safe inspection workflow

1. Copy (do not patch) the game's `default.xex` from the console to removable USB storage.
2. Copy that file to a PC and retain the original unchanged.
3. Run the helper script `tools/inspect_default_xex.ps1` with a local XexTool binary.
4. Send the generated `default.idc` and, ideally, the original `default.xex` here for inspection.
5. If the import list is inconclusive, we will need a disassembly of the relevant call sites; do not patch or re-sign the game executable for this research.

## Current status

- [x] Confirm the documented Disney Infinity 360 framing (`0B 15`, inner packet at offset 2).
- [ ] Inspect the exact Disney Infinity 1.0 `default.xex` import libraries and call sites.
- [ ] Identify the actual Beyond API module/export resolution.
- [ ] Verify exact ABI and buffer semantics.
- [ ] Only then implement the Xbox hook/transport.

## Not yet claimed

There is no verified Xbox 360 hook, no confirmed Beyond ordinal, and no working DashLaunch XEX. The Skylanders `Kaos-byte` ordinals are not evidence for Disney Infinity and must not be copied into this project.
