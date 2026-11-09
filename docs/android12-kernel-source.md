# Android 12 kernel source match — Moto G60 XT2135-2

## Exact build reported for the target handset

- Device: Motorola Moto G60 XT2135-2
- Android version: Android 12
- Build number: `S2RIS32.32-20-9-9-2-3`
- Firmware package identified in Motorola's kernel-source request tracker: `XT2135-2_HANOIP_RETEU_12_S2RIS32.32-20-9-9-2-3_subsidy-DEFAULT_regulatory-XT2135-2-EUROPE_CFC.xml.zip`

## Matching Motorola kernel source

Motorola's official `kernel-msm` repository published the matching source release under the tag:

`MMI-S2RIS32.32-20-9-9-2-3`

Release: https://github.com/MotorolaMobilityLLC/kernel-msm/releases/tag/MMI-S2RIS32.32-20-9-9-2-3

Motorola tracking issue confirming the exact XT2135-2 firmware build and source publication: https://github.com/MotorolaMobilityLLC/kernel-msm/issues/574

The release is described as a Hanoip push for Android 12. This is the Android/Linux kernel source corresponding to the reported firmware build; it is **not** XNU source and does not make iOS or Darwin compatible with this phone.

## Research plan

1. Record the release tag and commit metadata in the research log.
2. Review the source tree's top-level README, build configuration, defconfig, and device-specific files.
3. Identify the kernel base/version and enabled platform drivers from source, not guesswork.
4. Compare the matching source with the hanoip device tree and vendor manifests.
5. Extract a hardware/driver inventory for WLAN, display, touch, audio, GPU, power, sensors, and storage.
6. Use the inventory to write a Darwin/XNU feasibility assessment; do not claim Linux drivers can be loaded by XNU.

## Scope and safety

This stage is source review only. Do not flash images, alter boot partitions, unlock the bootloader, or run unknown scripts as part of this research. Do not copy proprietary firmware, calibration data, signing material, or private platform components into this repository.

## Current status

- [x] Exact Android 12 build supplied by device owner.
- [x] Matching Motorola kernel-source release identified.
- [ ] Inspect and document the release's kernel version and configuration.
- [ ] Audit device-specific driver and device-tree coverage.
- [ ] Draft Darwin/XNU feasibility report.