# Development status

**Overall:** pre-alpha / source audit and hardware feasibility research.

No Moto G60 XNU port has been built, booted, or validated by this repository.

| Area | Status | Evidence required before changing status |
|---|---|---|
| Device identification | XT2135-2, 6 GB RAM, Android 12 build recorded | Runtime identity/build fingerprint verification |
| Android kernel source | Matching Motorola tag identified; Linux 4.14.190 | Capture running kernel release and final merged `.config` |
| Kernel config family | sdmsteppe perf defconfig + Hanoip fragment inspected | Verify actual stock Android 12 merged config |
| iOS 26.2 XNU source mapping | Not verified | Apple-published revision explicitly mapped to iOS 26.2 |
| Public upstream XNU research | Pinned source baseline recorded | Add/pin submodule and review exact license notices |
| Upstream XNU build | Not started | Reproducible build log and pinned revision |
| Moto G60 boot support | Not started | Reviewed platform design and safe test evidence |
| Wi-Fi stack | Hanoip device tree lists `qca_cld3_wlan.ko`; exact radio chip unknown | Exact WLAN device-tree node / runtime hardware ID |
| Darwin Wi-Fi driver | Not implemented | Driver code and hardware test evidence |
| Display | Qualcomm MSM DRM/DSI path; exact panel unknown | Panel ID, timings, driver implementation and physical test |
| Touchscreen | `ilitek_v3_mmi.ko` listed; exact controller unknown | Controller ID and bus details |
| Audio | WCD937x/WCD934x/WSA881x/AW882xx modules listed | Exact physical codec/amplifier mapping and playback/capture tests |
| GPU | Adreno 618 target; Qualcomm KGSL Linux driver enabled | Darwin graphics design and rendering tests |
| Battery / power | QPNP QG + SMB5 config; exact PMIC unknown | Exact PMIC/gauge IDs and telemetry/charging tests |
| Bluetooth | Not started | Chipset identification and connectivity tests |
| Storage / USB | Not started | Read/write and device enumeration tests |
| Camera / sensors | Not started | Per-device functional tests |
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