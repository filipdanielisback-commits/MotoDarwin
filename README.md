# MotoDarwin

**Experimental Darwin/XNU research for the Motorola Moto G60 (hanoip).**

MotoDarwin is an independent research project investigating what would be required to bring selected components of Apple's open-source Darwin/XNU stack to the Motorola Moto G60. The first goal is reproducible research and a documented feasibility study—not a claim that iOS 26 can currently boot on this device.

> **Status: pre-alpha research. Nothing in this repository is a working phone port yet.**
>
> Do not flash experimental images or replace your phone's boot chain. There are no validated Moto G60 boot images here.

## Project goals

- Establish a reproducible ARM64 XNU build environment.
- Track upstream XNU and preserve its original licensing and notices.
- Document Moto G60 hardware, firmware boundaries, and driver requirements.
- Build a safe, staged feasibility plan using emulation and host-side tests first.
- Record evidence for each hardware feature; never label an untested feature as working.

## Target device

| Item | Current research target |
|---|---|
| Device | Motorola Moto G60 |
| Device codename | hanoip |
| SoC | Qualcomm Snapdragon 732G family |
| CPU architecture | ARM64 |
| GPU | Qualcomm Adreno 618 |
| Kernel target | Apple open-source XNU (research only) |

Hardware details must be verified against the exact device variant and its kernel/device-tree sources before implementation.

## Repository map

- `docs/` — architecture, feasibility, hardware, and [Wi-Fi research](docs/wifi.md)
- `xnu/` — upstream XNU tracking, [iOS 26.2 source status](xnu/IOS_26_2_SOURCE_STATUS.md), and local patch policy
- `bootloader/` — boot-chain research; no flashing payloads
- `devices/moto-g60/` — device-specific notes
- `drivers/` — driver investigation and status
- `userland/` — user-space research
- `tests/` — validation plans and test records
- `tools/` — reproducibility helpers

## Reality check: XNU is not iOS

XNU is one component of Darwin. A complete iOS installation also depends on proprietary Apple components, platform-specific drivers, firmware, a trusted boot chain, code-signing infrastructure, and Apple services. Rebuilding open-source XNU does not recreate iOS, make an Android phone iOS-compatible, or provide App Store / Apple ID functionality.

MotoDarwin will not redistribute proprietary Apple firmware, iOS images, signing keys, private source code, or circumvention tools. Any future compatibility work must use lawfully obtained materials and respect applicable licenses and platform security.

## First milestones

1. Inventory the exact Moto G60 variant and its existing Android software baseline.
2. Establish a clean host build environment and pin an upstream XNU revision.
3. Reproduce an upstream XNU build for a supported development target.
4. Document the differences between that target and Moto G60's Qualcomm platform.
5. Evaluate emulation and non-destructive experiments before any device-specific boot work.
6. Create driver feasibility reports for display, touch, audio, GPU, Wi-Fi, Bluetooth, storage, battery, cameras, and power management.

See [ROADMAP.md](ROADMAP.md), [STATUS.md](STATUS.md), and [CONTRIBUTING.md](CONTRIBUTING.md).

## Contributing

Research notes, source references, build logs, and carefully scoped experiments are welcome. Read [CONTRIBUTING.md](CONTRIBUTING.md) before opening a pull request.

## License and attribution

This repository does not change the license of Apple or third-party code. XNU is distributed by Apple under the Apple Public Source License (APSL); consult the exact upstream revision's license and notices before copying, modifying, or redistributing files. See [xnu/README.md](xnu/README.md).

Project documentation has no blanket license declaration yet. Do not assume that third-party code or assets in this repository are relicensed.
