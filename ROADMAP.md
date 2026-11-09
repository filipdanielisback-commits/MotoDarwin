# MotoDarwin roadmap

This is a research roadmap, not a promise that every milestone is technically achievable.

## Phase 0 — Project hygiene and device inventory

- [x] Create repository structure and research documentation.
- [ ] Confirm exact Moto G60 model / regional variant and codename from the device itself.
- [ ] Record Android build fingerprint, bootloader state, kernel version, and firmware baseline.
- [ ] Collect authoritative hardware references and upstream source links.
- [ ] Establish contribution, attribution, and artifact provenance rules.

**Exit criteria:** device identity and baseline are documented with sources; no guessed hardware assumptions remain.

## Phase 1 — XNU source identification and build reproduction

- [ ] Review Apple's open-source release listings for iOS 26.2 and identify which components are actually published.
- [ ] Determine whether an exact iOS 26.2 XNU source revision is publicly available; do not infer a mapping from a macOS source tag.
- [ ] Select and pin a public XNU snapshot for general research if no iOS-specific source is published.
- [ ] Read the selected revision's build instructions and license files.
- [ ] Reproduce a supported upstream build on a clean host.
- [ ] Save toolchain versions, commands, logs, and output hashes.
- [ ] Document which architectures and platforms the selected revision actually supports.

**Exit criteria:** another contributor can reproduce a supported upstream build and the repository clearly distinguishes it from an iOS 26.2 device kernel or a Moto G60 port.

## Phase 2 — Wi-Fi hardware and driver feasibility

- [ ] Confirm exact Moto G60 model / regional variant and WLAN hardware identifiers.
- [ ] Review the hanoip device tree, kernel configuration, WLAN driver references, and firmware manifest.
- [ ] Validate the preliminary WCN3990 / ath10k lead against device-specific evidence.
- [ ] Document firmware and calibration provenance without committing proprietary blobs.
- [ ] Design a Darwin/XNU driver integration plan; Linux ath10k is a reference, not a drop-in XNU driver.
- [ ] Define scan, connect, DHCP, DNS, throughput, reconnect, regulatory, and suspend/resume tests.

**Exit criteria:** hardware identity and a reviewed driver feasibility report exist. No Wi-Fi functionality is claimed until tested on the exact device.

## Phase 3 — Platform feasibility

- [ ] Map Moto G60 boot flow and documented boot image format.
- [ ] Identify the SoC, interrupt controller, timers, memory map, clocks, and power domains from reliable sources.
- [ ] Compare the platform requirements with the selected XNU porting interfaces.
- [ ] Identify the missing platform adaptation and driver work.
- [ ] Decide whether emulation or a supported development board is a better first kernel target.

**Exit criteria:** a reviewed feasibility report with explicit blockers and unknowns.

## Phase 4 — Other driver research

Track display, touchscreen, audio, GPU, Bluetooth, storage, battery/charging, cameras, sensors, USB, and suspend/resume independently.

**Exit criteria:** each item has a source-backed status, owner, test plan, and evidence. "Unknown" is an acceptable status.

## Phase 5 — Non-destructive prototype

- [ ] Prototype only in a supported emulator or development environment first.
- [ ] Add automated host-side checks and build reproducibility tests.
- [ ] Keep device recovery instructions and original firmware references documented.
- [ ] Require independent review before any experiment that writes to device partitions.

**Exit criteria:** repeatable test evidence and a recovery plan. No daily-driver flashing.

## Phase 6 — Device experiments (future / gated)

This phase is blocked until platform feasibility, legal review, hardware documentation, and recovery procedures are complete. No device image is considered safe merely because it compiles.

## Explicit non-goals

- Claiming this is an official Apple or Motorola project.
- Claiming to provide a complete iOS 26.2 installation, App Store, Apple ID, or proprietary Apple services.
- Redistributing proprietary Apple firmware, iOS images, signing keys, or private source.
- Promising that every Moto G60 hardware feature will work.
