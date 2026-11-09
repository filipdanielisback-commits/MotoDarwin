# Moto G60 hardware inventory

This file is intentionally conservative. Verify all entries against the exact handset variant and authoritative sources before using them in code.

| Component | Initial identification | Verification needed |
|---|---|---|
| Product | Motorola Moto G60 | Exact XT model / region |
| Device codename | hanoip (reported in Android community sources) | Confirm against device properties and source tree |
| SoC | Qualcomm Snapdragon 732G family | Confirm board revision and platform identifiers |
| CPU | ARM64-capable Qualcomm Kryo CPU complex | Core topology, clocks, and firmware interfaces |
| GPU | Qualcomm Adreno 618 | Driver and firmware requirements |
| Display | Integrated mobile display path | Panel ID, DSI configuration, timing, backlight |
| Touch | Dedicated touch controller | Controller model, bus, firmware |
| Audio | Qualcomm audio subsystem | Codec, DSP firmware, routing |
| Wireless | Qualcomm / vendor radio stack | Exact Wi-Fi and Bluetooth chipsets and firmware |
| Power | PMIC and battery gauge | Exact components, charging path, thermal sensors |
| Camera | Multiple camera modules | Sensor IDs, ISP, calibration and firmware |

## Evidence policy

For every confirmed field, add:
- source URL and access date;
- exact device variant;
- source-tree path or hardware identifier;
- confidence level (confirmed / likely / unknown).

Do not infer the exact peripheral model from the SoC alone. Regional variants can differ.
