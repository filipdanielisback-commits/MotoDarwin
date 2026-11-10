# Moto G60 Wi-Fi Driver Feasibility Report

**Device target:** Motorola Moto G60 XT2135-2 (hanoip)  
**Report status:** Preliminary research; exact WLAN silicon not confirmed  
**Date:** 2026-11-10

## Executive summary

The available Hanoip Android device-tree evidence lists a kernel module named `qca_cld3_wlan.ko` and maps it to the generic Android module alias `wlan.ko`. This is evidence that the Android software configuration for the Hanoip family uses a Qualcomm CLD3 WLAN driver module.

It is **not sufficient to identify the exact Wi-Fi chipset or silicon revision** in this specific XT2135-2 handset. The module name identifies a driver family, not a unique chip model. No Darwin/XNU driver exists in this project at this stage, and no Wi-Fi functionality has been implemented or tested.

## Evidence collected

### 1. Hanoip device-tree module inventory

The public `motorola-sm6150-devs/device_motorola_hanoip` device tree, branch `lineage-20`, includes `qca_cld3_wlan.ko` in `modules.load`.

Source: https://github.com/motorola-sm6150-devs/device_motorola_hanoip/blob/lineage-20/modules.load

### 2. Android module alias

The same device tree's `BoardConfig.mk` contains the mapping:

- Android alias: `wlan.ko`
- Vendor module: `qca_cld3_wlan.ko`

Source: https://github.com/motorola-sm6150-devs/device_motorola_hanoip/blob/lineage-20/BoardConfig.mk

This confirms the device-tree build configuration expects that vendor module. A module list alone does not prove it was loaded on every firmware build or identify the physical chip.

### 3. Device identity and radio capabilities

The target handset has been recorded in the project as XT2135-2 / hanoip, with Qualcomm SM6150-family platform identification. Motorola's EU Declaration of Conformity identifies the Moto G60 XT2135-2 and lists WLAN IEEE 802.11a/b/g/n/ac.

Source: https://en-us.support.motorola.com/ci/fattach/get/79315385/1664922506/redirect/1/filename/XT2135-2_Moto%2BG60%2BVision%2BMC38C%2BRED%2BDoC.pdf

The regulatory document establishes supported WLAN standards, not the WLAN chipset model.

## Current conclusion

| Question | Finding |
|---|---|
| Android WLAN module in Hanoip device tree | `qca_cld3_wlan.ko` |
| Generic Android module alias | `wlan.ko` |
| Driver family indication | Qualcomm CLD3 WLAN |
| Exact Wi-Fi chipset / silicon ID | **Unknown** |
| Exact bus and device-tree WLAN node | **Not yet verified** |
| Module loaded on this exact handset/build | **Not yet verified** |
| Darwin/XNU driver in MotoDarwin | **Does not exist yet** |
| Wi-Fi working in MotoDarwin | **Not implemented / not tested** |

## Darwin/XNU feasibility

The Android/Linux vendor module is not a drop-in XNU driver. Linux kernel modules depend on Linux kernel APIs, memory management, networking interfaces, bus frameworks, firmware loading and vendor integration. XNU has different driver and networking interfaces.

A future implementation would require a separately designed and reviewed Darwin-side driver or a carefully scoped compatibility strategy, with hardware documentation and a lawful firmware plan. The project must not redistribute proprietary firmware or calibration data.

## Open research questions

1. What exact WLAN chip/device ID is present in XT2135-2 hardware?
2. Which bus/interface and device-tree node describe it?
3. Which module is actually active in the stock Android build?
4. What firmware and calibration dependencies exist, and what can legally be redistributed?
5. Is there sufficient public hardware documentation to support an independent driver?
6. What XNU networking and device-driver interfaces would need to be implemented?

## Recommended next milestone

**Wi-Fi Research 0.1.2 — Hardware Identification**

Keep this as a documentation and compatibility-research milestone. Do not announce a released driver or working Wi-Fi until there is an independently implemented driver and repeatable test evidence.

## Public communication guidance

Accurate wording: “MotoDarwin has begun investigating Wi-Fi support. The Hanoip Android device tree references Qualcomm's CLD3 WLAN driver family; the exact chip identification and Darwin driver feasibility are still under research.”

Do not claim:
- that a MotoDarwin Wi-Fi driver has been released;
- that Wi-Fi works in MotoDarwin;
- that the exact WLAN chipset is confirmed;
- that the Android vendor module can run directly in XNU.
