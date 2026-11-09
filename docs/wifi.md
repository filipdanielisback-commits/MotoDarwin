# Wi-Fi research — Moto G60 XT2135-2 (hanoip)

**Target:** XT2135-2, 6 GB RAM. **Track status: researching. No MotoDarwin Wi-Fi driver exists yet.**

## Current strongest device-family evidence

The Hanoip device tree's `modules.load` lists `qca_cld3_wlan.ko`, and its `BoardConfig.mk` maps the Android module alias `wlan.ko` to `qca_cld3_wlan.ko`. This identifies a Qualcomm CLD3 vendor WLAN software stack in the Hanoip build configuration.

References:
- Hanoip module list: https://github.com/motorola-sm6150-devs/device_motorola_hanoip/blob/lineage-20/modules.load
- Hanoip module aliases and kernel config recipe: https://github.com/motorola-sm6150-devs/device_motorola_hanoip/blob/lineage-20/BoardConfig.mk
- Motorola kernel source release: https://github.com/MotorolaMobilityLLC/kernel-msm/releases/tag/MMI-S2RIS32.32-20-9-9-2-3

**Exact Wi-Fi chipset and hardware revision are still unknown.** The module name identifies the driver stack, not the exact radio chip.

## Correction to the earlier WCN3990 lead

An earlier community mainline research lead pointed to WCN3990 / ath10k. The Motorola kernel source does contain generic `ath10k` WCN3990 SNOC support, but generic driver presence is not proof that the Moto G60 XT2135-2 uses that chip. The Hanoip module list instead names `qca_cld3_wlan.ko`. Treat WCN3990 as unverified and do not base implementation on it until the device tree or runtime hardware inventory confirms it.

Generic ath10k Kconfig reference: https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/drivers/net/wireless/ath/ath10k/Kconfig

## Linux reference stack versus Darwin

The Qualcomm CLD3 driver is part of the Android/Linux vendor stack. It cannot simply be compiled into XNU. A Darwin implementation would need its own compatible driver integration, bus and power management, firmware loading, regulatory behavior, network interface integration, and testing. Proprietary calibration and firmware files must not be redistributed without permission.

## Next evidence needed

- [ ] Locate the exact WLAN device-tree node for the XT2135-2 board.
- [ ] Identify the WLAN device compatible string / hardware ID and bus.
- [ ] Confirm which kernel module is actually loaded by the target firmware, rather than relying only on a community build list.
- [ ] Record firmware file names and provenance only; do not commit proprietary blobs.
- [ ] Write a Darwin driver feasibility design after the hardware is identified.
- [ ] Define scan, association, DHCP, DNS, reconnect, suspend/resume, and regulatory tests.

## Current status

| Feature | Status |
|---|---|
| Target variant | XT2135-2, 6 GB RAM |
| Wi-Fi standards | 802.11a/b/g/n/ac listed by Motorola |
| Driver stack | Qualcomm CLD3 module listed in Hanoip device tree |
| Exact radio chipset | Unknown |
| WCN3990 | Unverified; not treated as the target |
| Darwin/XNU driver | Not implemented |
| Firmware integration | Not implemented |
| Wi-Fi scan/connect | Not tested |

Never report Wi-Fi as working until it has been tested on the exact device and source revision.