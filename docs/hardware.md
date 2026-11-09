# Moto G60 hardware inventory

Target variant: **Motorola Moto G60 XT2135-2, 6 GB RAM**.

This inventory distinguishes published specifications from components that still need handset-level verification.

| Component | Initial identification | Confidence / verification needed |
|---|---|---|
| Product | Motorola Moto G60 XT2135-2 | Confirmed by Motorola EU Declaration of Conformity |
| RAM | 6 GB | User-reported target configuration; verify runtime memory if needed |
| Device codename | hanoip | Reported in Android community sources; confirm on handset |
| SoC | Qualcomm Snapdragon 732G / SM7150 family | Published model specification; confirm board identifiers |
| CPU | Qualcomm Kryo CPU complex | Core topology, clocks, and firmware interfaces |
| GPU | Qualcomm Adreno 618 | Published model specification; driver and firmware requirements remain |
| Display | 6.8-inch class IPS LCD, 1080 × 2460, up to 120 Hz in published specs | Exact panel ID, DSI configuration, timing, backlight |
| Touch | Capacitive multi-touch | Exact controller model, bus, firmware |
| Audio | Qualcomm audio subsystem | Codec, DSP firmware, routing |
| Wi-Fi | IEEE 802.11a/b/g/n/ac supported | Exact radio chipset/revision not yet confirmed; WCN3990 is only a lead |
| Bluetooth | Bluetooth supported | Exact controller and coexistence integration to verify |
| Power | 6000 mAh battery listed in published specs | PMIC, battery gauge, charging path, thermal sensors |
| Camera | Multiple camera modules | Sensor IDs, ISP, calibration and firmware |

## Primary model reference

Motorola EU Declaration of Conformity for Moto G60 XT2135-2 (2021-03-05):
https://en-us.support.motorola.com/ci/fattach/get/79315385/1664922506/redirect/1/filename/XT2135-2_Moto%2BG60%2BVision%2BMC38C%2BRED%2BDoC.pdf

## Evidence policy

For every confirmed field, add:
- source URL and access date;
- exact device variant;
- source-tree path or hardware identifier;
- confidence level (confirmed / likely / unknown).

Do not infer the exact peripheral model from the SoC or Wi-Fi standard alone. Regional variants can differ.