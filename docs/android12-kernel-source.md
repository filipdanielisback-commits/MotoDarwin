# Android 12 kernel source match — Moto G60 XT2135-2

## Exact build reported for the target handset

- Device: Motorola Moto G60 XT2135-2
- Installed RAM: 6 GB
- Android version: Android 12
- Build number: `S2RIS32.32-20-9-9-2-3`
- Firmware package identified in Motorola's kernel-source request tracker: `XT2135-2_HANOIP_RETEU_12_S2RIS32.32-20-9-9-2-3_subsidy-DEFAULT_regulatory-XT2135-2-EUROPE_CFC.xml.zip`

## Matching Motorola kernel source

Motorola's official `kernel-msm` repository published the matching source release under the tag `MMI-S2RIS32.32-20-9-9-2-3`.

Release: https://github.com/MotorolaMobilityLLC/kernel-msm/releases/tag/MMI-S2RIS32.32-20-9-9-2-3

Motorola tracking issue: https://github.com/MotorolaMobilityLLC/kernel-msm/issues/574

## Kernel version and configuration findings

- The tag's top-level `Makefile` declares Linux **4.14.190**.
- The base ARM64 config is `arch/arm64/configs/vendor/sdmsteppe-perf_defconfig`.
- That base config sets `CONFIG_LOCALVERSION="-perf"`, `CONFIG_ARCH_QCOM=y`, `CONFIG_ARCH_SM6150=y`, `CONFIG_ARCH_SDMMAGPIE=y`, and `CONFIG_QCOM_KGSL=y`.
- The Hanoip-specific fragment is `arch/arm64/configs/vendor/ext_config/moto-sdmmagpie-hanoip.config`; it sets `CONFIG_HANOIP_DTB=y` and `CONFIG_DRM_MSM_DSI_MOT_EXT=y`.
- The exact final `.config` used by the stock Android 12 build has not yet been captured, so the running kernel release string and final merged config remain to be checked.

See [the component audit](kernel-audit.md) for Wi-Fi, display, touchscreen, audio, GPU, and battery/power findings with source links and confidence levels.

## Scope and safety

This stage is source review only. Do not flash images, alter boot partitions, unlock the bootloader, or run unknown scripts as part of this research. Do not copy proprietary firmware, calibration data, signing material, or private platform components into this repository.

## Current status

- [x] Exact Android 12 build supplied by device owner.
- [x] Matching Motorola kernel-source release identified.
- [x] Kernel source version and base/Hanoip config fragments inspected.
- [x] Initial driver/module inventory documented.
- [ ] Capture the exact running kernel release and final `.config`.
- [ ] Confirm exact peripheral IDs from the device tree or read-only runtime inventory.
- [ ] Draft Darwin/XNU feasibility report.