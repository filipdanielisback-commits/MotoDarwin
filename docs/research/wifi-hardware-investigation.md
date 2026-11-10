# Moto G60 Wi-Fi Hardware Investigation

**Status:** Research in progress  
**Target:** Motorola Moto G60 (XT2135-2, codename `hanoip`)  
**Scope:** Evidence collection and driver feasibility. This document does not claim working Wi-Fi support.

## Confirmed device context

The project’s current device notes identify the target as the Moto G60 XT2135-2 (`hanoip`), based on the device’s reported Android properties. The reported platform is Qualcomm SM6150-family.

## Android device-tree evidence

The public Hanoip Android device tree contains:

- `modules.load` with a reference to `qca_cld3_wlan.ko`
- `BoardConfig.mk` mapping the generic WLAN module name to `qca_cld3_wlan.ko`

This is evidence that the Android software configuration uses the Qualcomm CLD3 WLAN driver family. It does **not** by itself identify the exact Wi-Fi silicon fitted to every XT2135-2 unit, prove that the module is loaded on this specific handset, or establish its bus/interface.

References:
- [Hanoip modules.load](https://github.com/motorola-sm6150-devs/device_motorola_hanoip/blob/lineage-20/modules.load)
- [Hanoip BoardConfig.mk](https://github.com/motorola-sm6150-devs/device_motorola_hanoip/blob/lineage-20/BoardConfig.mk)
- [Qualcomm CLD3 Android build integration example](https://github.com/EssentialOpenSource/qcacld-3.0/blob/master/Android.mk)

## What remains unknown

The following items require direct device evidence or device-specific source review:

1. Exact WLAN chip model and hardware/revision identifier.
2. Host interface and bus (for example, SDIO or another platform-specific transport).
3. Device-tree node, power sequencing, clocks, regulators, reset and interrupt wiring.
4. Whether the WLAN kernel module is actually loaded and bound on the target handset.
5. Required firmware, board data, calibration data and their locations.
6. Licensing and redistribution constraints for any firmware or vendor components.

## Why the Android driver is not an XNU driver

The Android `.ko` is a Linux kernel module. It cannot be loaded directly by XNU. A Darwin implementation would need an appropriate XNU driver and networking integration, plus a supported way to communicate with the WLAN hardware and supply any required firmware/configuration data.

The Qualcomm driver build files are useful architectural research material, not proof that their Linux implementation can be reused as an XNU driver.

## Investigation plan

### Phase 1 — Read-only device identification

When the development notebook is available, collect non-invasive ADB properties and diagnostic information to determine:

- WLAN-related device identifiers, if exposed;
- loaded module and driver binding evidence, if readable without elevated privileges;
- device-tree and bus references available through public source or ordinary diagnostic interfaces.

Do not infer a chip model from the module filename alone. If Android does not expose the required identifier, record it as unknown rather than guessing.

### Phase 2 — Source and firmware review

Trace the Hanoip device-tree configuration into the corresponding kernel/vendor source revisions. Record the firmware and board-data dependencies only when supported by source evidence. Review redistribution terms before including any third-party code or binary data.

### Phase 3 — Darwin feasibility design

After the hardware identity and transport are established, prepare a design covering device discovery, power management, firmware loading, command/data transport, interrupt handling and integration with the XNU networking stack. Keep this as a design until it is reviewed against the actual hardware.

### Phase 4 — Implementation and validation

Implement only components supported by the evidence and project architecture. Validate in an appropriate development environment first. Do not describe Wi-Fi as supported or working until the driver has been built for the intended target and repeatable tests demonstrate device detection, association and data transfer.

## Current status

- [x] Hanoip Android device-tree WLAN module reference found.
- [x] Qualcomm CLD3 driver-family clue recorded.
- [ ] Exact WLAN silicon identified.
- [ ] Bus/interface confirmed.
- [ ] Runtime module loading/binding confirmed on the target handset.
- [ ] Firmware and calibration requirements documented.
- [ ] XNU driver architecture reviewed.
- [ ] Darwin driver implemented.
- [ ] Wi-Fi functionality tested.

**Current conclusion:** MotoDarwin Wi-Fi is in the hardware-research stage. No MotoDarwin Wi-Fi driver has been implemented, and working Wi-Fi is not available yet.
