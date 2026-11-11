# Protocol notes

## Xbox 360 framing
The audit in [DisneyInfinityPortal](https://github.com/LucasLhomme/DisneyInfinityPortal/blob/31852bac27ae94baa6540b86fd388b0ff45332de/docs/AUDIT.md) records this call path:

- OUT: `XInputBeyondSetRaw(32, buf)`.
- IN: `XInputBeyondGetRaw`.
- OUT outer header: `0x0B 0x15`.
- The 32-byte inner packet begins at offset 2.
- IN payload is read beginning at offset 2.

Treat this as the audited observation; do not infer undocumented packet fields from it.

## FlipBase core API
The upstream [FlipBase](https://github.com/Space-Raler/FlipBase) header declares:

- `inf_base_init(InfBase*)`
- `inf_base_handle_out(InfBase*, const uint8_t packet[32])`
- `inf_base_next_in(InfBase*, uint8_t out[32])`
- `inf_base_load_figure(InfBase*, slot, data[320])`
- `inf_base_remove_figure(InfBase*, slot)`
- `inf_base_take_dirty(InfBase*, slot, out[320])`

The core models 9 slots and 320-byte figure images. It is not thread-safe; serialize all access.

## Unverified Xbox details
Still to determine experimentally or from authoritative symbols:

- Exact export ordinals, signatures, calling conventions, and ABI for the raw functions.
- Whether the game statically imports them or resolves them dynamically.
- A safe DashLaunch hook strategy for this title and dashboard.

Do not reuse Kaos-byte's Skylanders hook ordinals as if they were confirmed for Disney Infinity. Kaos-byte uses a different protocol header (`0B 14`); the audited Disney Infinity header is `0B 15`.

## Initial tests
1. Capture raw OUT and IN buffers from the game.
2. Verify framing and offset handling.
3. Feed captured inner packets to FlipBase and log responses.
4. Test one 320-byte figure image in one slot.
5. Test removal/reinsertion and dirty data handling.
