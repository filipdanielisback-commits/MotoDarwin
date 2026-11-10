# Development status

**Overall:** pre-alpha / source audit and hardware feasibility research.

No Moto G60 XNU port has been built, booted, or validated by this repository.

| Area | Status | Evidence required before changing status |
|---|---|---|
| Device identification | XT2135-2, 6 GB RAM, Android 12 build recorded | Runtime identity/build fingerprint verification |
| Android kernel source | Matching Motorola tag identified; running `4.14.190-perf+` matches Linux 4.14.190 baseline | Capture final merged stock `.config` and selected DTBO |
| Kernel config family | sdmsteppe perf defconfig + Hanoip fragment inspected | Verify actual stock Android 12 merged config |
| iOS 26.2 XNU source mapping | Not verified | Apple-published revision explicitly mapped to iOS 26.2 |
| Public upstream XNU research | Pinned source baseline recorded | Add/pin submodule and review exact license notices |
| Upstream XNU build | Not started | Reproducible build log and pinned revision |
| Moto G60 boot support | Not started; source DTS/DTBO audit completed for Hanoip family | Identify handset-selected DTBO and complete platform feasibility design |
| Wi-Fi stack | Hanoip module list identifies Qualcomm CLD3 WLAN software; exact radio chip still unknown | Exact WLAN node / runtime hardware ID |
| Darwin Wi-Fi driver | Not implemented | Driver code and hardware test evidence |
| Display | Motorola DTS identifies Tianma ILI7807S panel family, 1080 × 2460, 60/120 Hz config | Exact fitted panel revision and Darwin display driver/test |
| Touchscreen | DTS identifies Ilitek-compatible SPI SE6, reset GPIO 8, IRQ GPIO 9 | Exact controller part and Darwin touch driver/test |
| Audio | DTS enables WCD937x/Bolero and AW882xx at I²C 0x34; WSA macro disabled | Exact physical variants and Darwin audio driver/test |
| GPU | Adreno 618 target; Qualcomm KGSL Linux driver enabled | Darwin graphics design and rendering tests |
| Battery / power | QPNP QG + SMB5 config; exact PMIC unknown | Exact PMIC/gauge IDs and telemetry/charging tests |
| Bluetooth | Physical controller still unidentified; DTS audit has not resolved radio hardware | Exact controller/interface and connectivity tests |
| Storage / USB | UFS host path identified in SDMMAGPIE DTS; USB controller path previously identified | Exact storage device and Darwin controller support/tests |
| Camera / sensors | DTS identifies camera positions/candidate sensors and Semtech SX933x SAR; exact camera variants unresolved | Exact per-unit sensor IDs and Darwin driver/test evidence |
| Sleep / wake | Not started | Repeated suspend/resume tests |
| App Store / Apple services | Unsupported / out of scope | Requires proprietary Apple infrastructure |

## Status vocabulary

- **Not started** — no implementation work.
- **Researching** — collecting sources and evaluating feasibility.
- **In progress** — code or experiments exist but are not validated.
- **Built** — a reproducible artifact exists; not necessarily bootable.
- **Boot-tested** — boot evidence exists for a named target and revision.
- **Working** — acceptance tests pass on the exact named device variant.
- **Blocked** — a documented technical, legal, or hardware blocker exists.

A status change must include links to commits, logs, test steps, device variant, and known limitations.