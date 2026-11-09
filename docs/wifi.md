# Wi-Fi research — Moto G60 (hanoip)

**Track status: researching. No MotoDarwin Wi-Fi driver exists yet.**

## Initial chipset lead

A community mainline-development repository for the Moto G60 / hanoip contains a Wi-Fi loader script that links a board calibration file named `bdwlan_hanoip_ipa.bin` into:

```text
/lib/firmware/ath10k/WCN3990/hw1.0/board.bin
```

This is evidence that the hanoip Wi-Fi path is associated with Qualcomm WCN3990 / ath10k in that Linux development environment. It is not yet sufficient to declare the exact radio hardware revision or firmware set on every retail Moto G60 variant. Confirm against the exact handset's device tree, kernel configuration, runtime device inventory, and vendor firmware manifest before implementing anything.

Research reference:
- Community hanoip development tree: https://github.com/eng-brener/hanoip-mainline
- Moto G60 / G40 Fusion Android device tree: https://github.com/motorola-sm6150-devs/device_motorola_hanoip
- Qualcomm WCN3990 device-tree binding: https://android.googlesource.com/kernel/msm/+/ef85d528056e472b667607601cc6a7f7cccb82b1/Documentation/devicetree/bindings/net/wireless/qcom,wcn3990-wifi.txt

Treat community scripts and binaries as untrusted research inputs. Review source and licenses; do not blindly run scripts or redistribute proprietary calibration/firmware blobs.

## Linux reference stack

The research lead points to the Linux `ath10k_snoc` driver family for WCN3990, with Qualcomm platform support and firmware/calibration dependencies. Linux driver code is a reference for understanding the hardware protocol; it is not a drop-in XNU driver.

## What a Darwin implementation would need

1. Exact hardware and firmware inventory for the target retail variant.
2. A documented bus/platform integration path for the wireless device.
3. A driver implementation compatible with the chosen Darwin/XNU driver model.
4. Firmware loading and calibration handling using lawfully distributable files.
5. Network interface integration, scan/authentication/association, regulatory-domain handling, power management, and suspend/resume.
6. A user-space networking service stack and configuration interface.
7. Repeatable tests for scan, connect, DHCP, DNS, throughput, reconnect, sleep/wake, and regional compliance.

The Linux `ath10k` implementation uses Linux kernel interfaces and cannot simply be compiled into XNU. Porting it would require substantial adaptation or a new driver; no compatibility is assumed.

## Milestones

- [ ] Confirm exact Moto G60 variant and radio identifiers.
- [ ] Locate and review the matching device-tree WLAN node.
- [ ] Record the existing Android kernel driver and firmware file names (names and provenance only).
- [ ] Determine which firmware/calibration files are redistributable and which must remain device-provided.
- [ ] Write a Darwin driver feasibility design.
- [ ] Define a test matrix before implementation.
- [ ] Implement only after the platform and driver interfaces are understood.

## Current status

| Feature | Status |
|---|---|
| Chipset identification | Preliminary WCN3990 lead; verify per device |
| Darwin/XNU driver | Not implemented |
| Firmware integration | Not implemented |
| Wi-Fi scan/connect | Not tested |
| DHCP/DNS | Not tested |
| Suspend/resume | Not tested |

Never report Wi-Fi as working until it has been tested on the exact device and source revision.
