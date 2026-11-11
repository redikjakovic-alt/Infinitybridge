# Roadmap

Legend: [ ] not started, [~] in progress, [x] verified complete.

## 0. Research and setup
- [x] Create public repository.
- [x] Record target Xbox 360 environment and constraints.
- [x] Record audited Xbox packet framing.
- [ ] Pin the exact FlipBase revision.
- [ ] Review third-party licenses before copying or linking code.

## 1. Portable adapter
- [ ] Add a thin adapter around the verified FlipBase API.
- [ ] Serialize all access to the non-thread-safe core.
- [ ] Add host-side tests for packet forwarding and slot operations.
- [ ] Validate a known 320-byte figure image.

## 2. Xbox transport research
- [ ] Identify raw-input exports, ordinals, signatures, and ABI used by Disney Infinity 1.0.
- [ ] Determine static imports versus runtime lookup.
- [ ] Validate a safe hook strategy on the target dashboard.
- [ ] Build a diagnostic DashLaunch plugin before adding emulation.

## 3. First in-game response
- [ ] Route captured OUT packets into the core.
- [ ] Return queued IN packets through the expected game path.
- [ ] Confirm that the game detects the virtual base.

## 4. One virtual figure
- [ ] Load one test figure from USB storage.
- [ ] Confirm recognition in Disney Infinity 1.0.
- [ ] Verify removal/reinsertion and dirty-data persistence.

## 5. Usable emulator
- [ ] Add USB figure library management.
- [ ] Support all protocol slots.
- [ ] Add diagnostics and safe save/load behavior.
- [ ] Document installation and recovery.

## Non-goals for the first prototype
- No NAND modifications.
- No physical portal dependency.
- No assumption that Skylanders hooks are compatible.
- No compatibility claims for later Disney Infinity games until tested.
