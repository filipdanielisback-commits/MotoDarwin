# Wi-Fi research — Moto G60 XT2135-2 (hanoip)

**Target:** XT2135-2, 6 GB RAM. **Track status: researching. No MotoDarwin Wi-Fi driver exists yet.**

## What is confirmed

Motorola's EU Declaration of Conformity identifies XT2135-2 as the Moto G60 and lists WLAN support for IEEE 802.11a/b/g/n/ac. This confirms the supported Wi-Fi standards, not the exact radio chipset or its hardware revision.

Primary reference (Motorola, 2021-03-05):
https://en-us.support.motorola.com/ci/fattach/get/79315385/1664922506/redirect/1/filename/XT2135-2_Moto%2BG60%2BVision%2BMC38C%2BRED%2BDoC.pdf

## Preliminary chipset lead — not yet confirmed

A community mainline-development repository for Moto G60 / hanoip contains a Wi-Fi loader script that links a board calibration file named `bdwlan_hanoip_ipa.bin` into the ath10k WCN3990 firmware directory. This is evidence that the hanoip Linux development path is associated with Qualcomm WCN3990 / ath10k. It is not sufficient to prove that the exact XT2135-2 handset has that radio revision or uses the same firmware arrangement. Confirm against the matching device tree, kernel configuration, runtime device inventory, and vendor firmware manifest before designing a driver.

Research references:
- Community hanoip development tree: https://github.com/eng-brener/hanoip-mainline
- Moto G60 / G40 Fusion Android device tree: https://github.com/motorola-sm6150-devs/device_motorola_hanoip
- Qualcomm WCN3990 device-tree binding: https://android.googlesource.com/kernel/msm/+/ef85d528056e472b667607601cc6a7f7cccb82b1/Documentation/devicetree/bindings/net/wireless/qcom,wcn3990-wifi.txt

Treat community scripts and binaries as untrusted research inputs. Review source and licenses; do not blindly run scripts or redistribute proprietary calibration/firmware blobs.

## Linux reference stack

The research lead points to the Linux `ath10k_snoc` driver family for WCN3990, with Qualcomm platform support and firmware/calibration dependencies. Linux driver code is a reference for understanding the hardware protocol; it is not a drop-in XNU driver.

## Darwin implementation requirements

1. Confirm the exact radio hardware and firmware inventory for XT2135-2.
2. Document the bus/platform integration path for the wireless device.
3. Design a driver compatible with the selected Darwin/XNU driver model.
4. Handle firmware loading and calibration using lawfully distributable files.
5. Integrate networking, scanning, authentication, association, regulatory handling, power management, and suspend/resume.
6. Provide the required user-space networking/configuration integration.
7. Define repeatable tests before implementation.

The Linux `ath10k` implementation uses Linux kernel interfaces and cannot simply be compiled into XNU. Porting it would require substantial adaptation or a new driver; no compatibility is assumed.

## Current status

| Feature | Status |
|---|---|
| Target variant | XT2135-2, 6 GB RAM |
| Wi-Fi standards | 802.11a/b/g/n/ac listed by Motorola |
| Chipset identification | Preliminary WCN3990 lead; exact handset not confirmed |
| Darwin/XNU driver | Not implemented |
| Firmware integration | Not implemented |
| Wi-Fi scan/connect | Not tested |
| DHCP/DNS | Not tested |
| Suspend/resume | Not tested |

Never report Wi-Fi as working until it has been tested on the exact device and source revision.