# InfinityBridge

A software-only Disney Infinity Portal emulator for Xbox 360.

## Goal
Allow Disney Infinity 1.0 to communicate with a virtual base through an Xbox 360 DashLaunch plugin, without the physical USB portal.

## Target environment
- Xbox 360 Fat
- Dashboard 2.0.17559.0
- RGH / DashLaunch, Aurora
- USB storage for figure images

## Architecture
1. Xbox raw-input transport and hook layer.
2. Adapter between Xbox packets and the portable protocol core.
3. FlipBase protocol core for portal state, queues, slots, and figure images.
4. USB-based figure storage.

## Research references
- [DisneyInfinityPortal](https://github.com/LucasLhomme/DisneyInfinityPortal) — Xbox 360 raw-input call-path research.
- [FlipBase](https://github.com/Space-Raler/FlipBase) — portable Disney Infinity protocol core.
- [Kaos-byte](https://github.com/vwpzjjkbnk-hash/Kaos-byte) — DashLaunch plugin framework reference only; it implements Skylanders, not Disney Infinity.

## Current status
Research and scaffolding only. No working Xbox plugin or confirmed raw-input hook is claimed yet.

## Open questions
- Exact exports, ordinals, calling conventions, and ABI for `XInputBeyondGetRaw` / `XInputBeyondSetRaw`.
- Whether the game imports these statically or resolves them dynamically.
- Safe hook strategy for the target dashboard.
- Figure format details beyond the core's 320-byte image representation.

See [docs/PROTOCOL.md](docs/PROTOCOL.md) and [docs/ROADMAP.md](docs/ROADMAP.md).

## Licensing
Third-party code retains its upstream license. See [THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md).