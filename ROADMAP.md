# MotoDarwin roadmap

This is a research roadmap, not a promise that every milestone is technically achievable.

## Phase 0 — Project hygiene and device inventory

- [x] Create repository structure and research documentation.
- [x] Record exact Moto G60 XT2135-2 variant, 6 GB RAM, Android 12 build number.
- [x] Identify matching Motorola kernel source tag.
- [x] Record Linux kernel source version and initial driver/module inventory.
- [ ] Capture running kernel release, Android build fingerprint, and final merged kernel config.
- [ ] Confirm exact peripheral IDs from matching device-tree nodes or read-only runtime inventory.

**Exit criteria:** device identity and software baseline are documented with sources; no guessed hardware assumptions remain.

## Phase 1 — XNU source identification and build reproduction

- [x] Record official Apple XNU upstream repository.
- [x] Pin a public XNU source snapshot for reproducible research; exact iOS 26.2 mapping remains unverified.
- [ ] Add the pinned upstream source as a Git submodule and review its license notices.
- [ ] Read the selected revision's build instructions and dependencies.
- [ ] Reproduce a supported upstream build on a clean host.
- [ ] Save toolchain versions, commands, logs, and output hashes.
- [ ] Document which architectures and platforms the selected revision actually supports.

**Exit criteria:** another contributor can reproduce a supported upstream build and the repository clearly distinguishes it from an iOS 26.2 device kernel or a Moto G60 port.

## Phase 2 — Wi-Fi hardware and driver feasibility

- [x] Identify the Hanoip device-tree WLAN module reference (`qca_cld3_wlan.ko`).
- [ ] Confirm exact Moto G60 XT2135-2 WLAN device-tree node, chipset ID, and bus.
- [ ] Verify which WLAN module is actually loaded by the stock firmware.
- [ ] Document firmware and calibration provenance without committing proprietary blobs.
- [ ] Design a Darwin/XNU driver integration plan; the Android/Linux vendor driver is a reference, not a drop-in XNU driver.
- [ ] Define scan, connect, DHCP, DNS, throughput, reconnect, regulatory, and suspend/resume tests.

**Exit criteria:** hardware identity and a reviewed driver feasibility report exist. No Wi-Fi functionality is claimed until tested on the exact device.

## Phase 3 — Platform feasibility

- [ ] Map the SoC platform interfaces: interrupts, timers, memory map, clocks, power domains, and IOMMU.
- [ ] Compare those requirements with the selected XNU porting interfaces.
- [ ] Identify missing platform adaptation and driver work.
- [ ] Decide whether emulation or a supported development board is a better first kernel target.

**Exit criteria:** a reviewed feasibility report with explicit blockers and unknowns.

## Phase 4 — Other driver research

Track display/DSI panel, Ilitek touchscreen, Qualcomm audio, Adreno GPU, Bluetooth, storage, battery/charging, cameras, sensors, USB, and suspend/resume independently. See [docs/kernel-audit.md](docs/kernel-audit.md).

**Exit criteria:** each item has a source-backed status, owner, test plan, and evidence. "Unknown" is an acceptable status.

## Phase 5 — Non-destructive prototype

- [x] Build the AARCH64 UEFI application locally.
- [ ] Run the UEFI application in an emulator and capture a reproducible test log.
- [ ] Add automated host-side checks and build reproducibility tests.
- [ ] Keep device recovery documentation and official firmware references documented.
- [ ] Require independent review before any experiment that writes to device partitions.

**Exit criteria:** repeatable emulator/host test evidence and a recovery plan. No daily-driver flashing.

## Phase 6 — Device experiments (future / gated)

This phase is blocked until platform feasibility, legal review, hardware documentation, and recovery procedures are complete. No device image is considered safe merely because it compiles.

## Explicit non-goals

- Claiming this is an official Apple or Motorola project.
- Claiming to provide a complete iOS 26.2 installation, App Store, Apple ID, or proprietary Apple services.
- Redistributing proprietary Apple firmware, iOS images, signing keys, or private source.
- Promising that every Moto G60 hardware feature will work.
