# MotoDarwin roadmap

This is a research roadmap, not a promise that every milestone is technically achievable.

## Phase 0 — Project hygiene and device inventory

- [x] Create repository structure and research documentation.
- [ ] Confirm exact Moto G60 model / regional variant and codename from the device itself.
- [ ] Record Android build fingerprint, bootloader state, kernel version, and firmware baseline.
- [ ] Collect authoritative hardware references and upstream source links.
- [ ] Establish contribution, attribution, and artifact provenance rules.

**Exit criteria:** device identity and baseline are documented with sources; no guessed hardware assumptions remain.

## Phase 1 — Upstream XNU build reproduction

- [ ] Select and pin a specific public XNU release/revision.
- [ ] Read its build instructions and license files.
- [ ] Reproduce a supported upstream build on a clean host.
- [ ] Save toolchain versions, commands, logs, and output hashes.
- [ ] Document which architectures and platforms the selected revision actually supports.

**Exit criteria:** another contributor can reproduce the same supported build. This does not mean it boots on Moto G60.

## Phase 2 — Platform feasibility

- [ ] Map Moto G60 boot flow and documented boot image format.
- [ ] Identify the SoC, interrupt controller, timers, memory map, clocks, and power domains from reliable sources.
- [ ] Compare the platform requirements with the selected XNU porting interfaces.
- [ ] Identify the missing platform adaptation and driver work.
- [ ] Decide whether emulation or a supported development board is a better first kernel target.

**Exit criteria:** a reviewed feasibility report with explicit blockers and unknowns.

## Phase 3 — Driver research

Track each subsystem independently: display, touchscreen, audio, GPU, Wi-Fi, Bluetooth, storage, battery/charging, cameras, sensors, USB, and suspend/resume.

**Exit criteria:** each item has a source-backed status, owner, test plan, and evidence. "Unknown" is an acceptable status.

## Phase 4 — Non-destructive prototype

- [ ] Prototype only in a supported emulator or development environment first.
- [ ] Add automated host-side checks and build reproducibility tests.
- [ ] Keep device recovery instructions and original firmware references documented.
- [ ] Require independent review before any experiment that writes to device partitions.

**Exit criteria:** repeatable test evidence and a recovery plan. No daily-driver flashing.

## Phase 5 — Device experiments (future / gated)

This phase is blocked until platform feasibility, legal review, hardware documentation, and recovery procedures are complete. No device image is considered safe merely because it compiles.

## Explicit non-goals

- Claiming this is an official Apple or Motorola project.
- Claiming to provide iOS 26, App Store, Apple ID, or proprietary Apple services.
- Redistributing proprietary Apple firmware, iOS images, signing keys, or private source.
- Promising that every Moto G60 hardware feature will work.
