# Core integration

## Dependency

InfinityBridge uses the portable protocol core from:

- Repository: https://github.com/Space-Raler/FlipBase
- Inspected revision: `7ed9399ba5cfe7766c9b39a501788f18f07704a8`
- Required files: `infinity_core.h` and `infinity_core.c`
- Upstream license: GPL-2.0-only

The adapter in `src/core/` is written against the public API in that revision. Keep the upstream files separate from original InfinityBridge glue and preserve their copyright/license notices.

For a local checkout, one possible layout is:

```
third_party/FlipBase/infinity_core.h
third_party/FlipBase/infinity_core.c
src/core/infinity_bridge.h
src/core/infinity_bridge.c
```

Copy or clone the pinned upstream revision into `third_party/FlipBase`; do not silently track a moving branch when building reproducible binaries.

## Adapter contract

`InfinityBridge` owns one `InfBase` protocol state object. The adapter intentionally does not implement locking or platform synchronization.

**Important:** FlipBase explicitly states that its core is not thread-safe. The Xbox transport must serialize every call that touches the same `InfinityBridge` instance. If the game callbacks can run concurrently, protect calls with an appropriate Xbox critical section or other verified synchronization primitive. Do not assume a generic compiler atomic primitive is available or correct for the target PPC toolchain.

## Packet boundary

The adapter accepts only the 32-byte inner Disney Infinity packet. It does not parse the Xbox-facing two-byte outer framing header. The Xbox transport layer is responsible for validating and stripping the outer header before calling `ib_handle_out`, and for restoring the expected outer framing on IN data.

## Current limitations

- No Xbox hooks or raw-input ABI are implemented here.
- No USB file I/O is implemented here.
- No figure file format conversion is implemented here.
- No thread synchronization is implemented here.
- No build system or Xbox binary is claimed yet.
