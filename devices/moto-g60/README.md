# Motorola Moto G60 (hanoip)

## Target handset

- **Retail model:** Moto G60 XT2135-2
- **Installed RAM:** 6 GB
- **SoC:** Qualcomm Snapdragon 732G (SM7150 family), based on published model specifications
- **GPU:** Qualcomm Adreno 618, based on published model specifications
- **Wi-Fi capability:** IEEE 802.11a/b/g/n/ac is listed in Motorola's EU declaration for XT2135-2
- **Exact Wi-Fi chipset:** not yet confirmed from this handset's device inventory; WCN3990 remains a research lead, not a verified fact

Primary model evidence: Motorola EU Declaration of Conformity for XT2135-2 / Moto G60 (2021-03-05):
https://en-us.support.motorola.com/ci/fattach/get/79315385/1664922506/redirect/1/filename/XT2135-2_Moto%2BG60%2BVision%2BMC38C%2BRED%2BDoC.pdf

## Current state

No Moto G60-specific XNU platform code, boot image, or validated driver is provided by this repository. The 6 GB RAM configuration is the target for research and does not establish driver or kernel compatibility.

## Required inventory

- Exact retail model and region (XT2135-2 recorded)
- Android build fingerprint and current kernel version/source provenance
- Device tree and board configuration
- Partition layout (document only; do not modify)
- Exact Wi-Fi/BT chipset and firmware identifiers
- PMIC, display panel, touch controller, audio codec, sensors, and camera modules
- Recovery documentation and official firmware references

## Safety

Keep early work to read-only inspection, source analysis, and supported emulation. Do not flash experimental images or overwrite boot-critical partitions. Any future device test requires a verified recovery plan and appropriate expert review.