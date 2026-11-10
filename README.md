# MotoDarwin

**Experimental Darwin/XNU research for the Motorola Moto G60 (hanoip).**

MotoDarwin is an independent research project investigating what would be required to bring selected components of Apple's open-source Darwin/XNU stack to the Motorola Moto G60. The first goal is reproducible research and a documented feasibility study—not a claim that iOS 26 can currently boot on this device.

> **Status: pre-alpha research. Nothing in this repository is a working phone port yet.**
>
> Do not flash experimental images or replace your phone's boot chain. There are no validated Moto G60 boot images here.

## Latest release

[**MotoDarwin 0.1.0-dev1 — Development Preview (Non-Bootable)**](https://github.com/filipdanielisback-commits/MotoDarwin/releases/tag/v0.1.0-dev1)

This pre-release contains a 1 MiB development placeholder only. It is not firmware, an installer, a boot image, or a usable operating system. **Do not flash it to any device.** No physical-device compatibility has been established.

## Project status and roadmap

See [ROADMAP.md](ROADMAP.md) for milestones, evidence requirements, and current blockers. The UEFI application has been built locally, but emulator execution has not yet been verified. No Darwin/XNU kernel is currently booted by this project.

## Project goals

- Establish a reproducible ARM64 XNU build environment.
- Track Apple's public XNU source as a pinned upstream dependency.
- Document Moto G60 hardware, firmware boundaries, and driver requirements.
- Build a safe, staged feasibility plan using emulation and host-side tests first.
- Record evidence for each hardware feature; never label an untested feature as working.

## Target device

| Item | Current research target |
|---|---|
| Device | Motorola Moto G60 XT2135-2 |
| RAM | 6 GB |
| Device codename | hanoip |
| Android build | `S2RIS32.32-20-9-9-2-3` |
| Android kernel source | Motorola `MMI-S2RIS32.32-20-9-9-2-3` (Linux 4.14.190) |
| SoC | Qualcomm Snapdragon 732G family |
| CPU architecture | ARM64 |
| GPU | Qualcomm Adreno 618 |

## Repository map

- `docs/` — architecture, feasibility, [hardware compatibility map](docs/hardware-compatibility.md), [DTS/DTBO audit](docs/dts-dtbo-audit.md), [kernel audit](docs/kernel-audit.md), [Wi-Fi research](docs/wifi.md), and Android kernel source match
- `xnu/` — Apple upstream tracking and XNU build research
- `bootloader/` — boot-chain research; no flashing payloads
- `devices/moto-g60/` — device-specific notes
- `drivers/` — driver investigation and status
- `userland/` — user-space research
- `tests/` — validation plans and test records
- `tools/` — reproducibility helpers

## Reality check: XNU is not iOS

XNU is one component of Darwin. A complete iOS installation also depends on proprietary Apple components, platform-specific drivers, firmware, a trusted boot chain, code-signing infrastructure, and Apple services. Rebuilding open-source XNU does not recreate iOS, make an Android phone iOS-compatible, or provide App Store / Apple ID functionality.

MotoDarwin is a Darwin/XNU research prototype, not a fake or official iOS build. It will not redistribute proprietary Apple firmware, iOS images, signing keys, private source code, or circumvention tools.

## License and attribution

This repository does not change the license of Apple or third-party code. Read the selected upstream XNU revision's license and notices before copying, modifying, or redistributing files. See [xnu/README.md](xnu/README.md) and [xnu/UPSTREAM.md](xnu/UPSTREAM.md).

Project documentation has no blanket license declaration yet. Do not assume that third-party code or assets in this repository are relicensed.

### Live ADB observations (2026-11-10)

Read-only ADB output from the handset reports `ro.product.device=hanoip`, `ro.product.board=hanoip`, `ro.boot.hardware.sku=XT2135-2`, `ro.board.platform=sm6150`, hardware revision `pvt`, and `ro.boot.dtbo_idx=1`. `uname -a` reports Linux `4.14.190-perf+`, `aarch64`, build date `Fri Oct 27 13:02:24 CDT 2023`. The Android build fingerprint is `motorola/hanoip_retailenq/hanoip:12/S2RIS32.32-20-9-9-2-3/f495e7-429de:user/release-keys`. See [live ADB device audit](docs/adb-device-audit.md). The DTBO index has not been mapped to a specific source overlay.
