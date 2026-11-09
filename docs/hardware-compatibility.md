# Moto G60 hardware compatibility map

**Target:** Motorola Moto G60 XT2135-2 (codename `hanoip`)  
**Owner-reported firmware:** Android 12, build `S2RIS32.32-20-9-9-2-3`  
**Owner-reported running kernel:** `4.14.190-perf+`  
**Matching Motorola source tag:** `MMI-S2RIS32.32-20-9-9-2-3`

This is a source-based research map, not a hardware bring-up result. A Linux module listed by an Android device tree is evidence that the Android build expects that driver; it does not prove that the module is loaded on this handset, identify every chip revision, or provide a Darwin/XNU driver.

## Evidence key

- **Strong source evidence** — directly named in the Motorola kernel configuration or Hanoip device-tree build files.
- **Partial evidence** — a driver family, interface, or build setting is visible, but the exact physical component or active configuration is not.
- **Unknown** — not identified from the sources examined so far.
- **No Darwin driver** — no MotoDarwin/XNU implementation has been demonstrated.

## Platform baseline

| Item | Current finding | Confidence / caveat |
|---|---|---|
| Device identity | Motorola Moto G60 XT2135-2; codename `hanoip` | Device identity supplied by owner; community device tree covers Moto G40 Fusion/G60 family |
| Android build | `S2RIS32.32-20-9-9-2-3` | Owner-reported |
| Running kernel | `4.14.190-perf+` | Owner-reported; version and `-perf` suffix match Motorola source baseline/config |
| Motorola kernel source | Tag `MMI-S2RIS32.32-20-9-9-2-3`; Linux 4.14.190 | Strong source match |
| Board/platform naming | `hanoip`, `sm6150`; kernel config also enables SM6150 and SDMMAGPIE platform support | Strong build-source evidence; platform naming is not a complete silicon inventory |
| CPU architecture | ARM64 / armv8-2a build target | Strong device-tree build evidence |
| SoC/GPU | Snapdragon 732G family; Adreno 618 | Public device specification; exact stepping not identified |
| RAM | 6 GB | Owner-reported |
| Display build parameters | 1080 × 2460 target dimensions; density 440 | Community Hanoip `device.mk`; confirm against stock panel mode before treating as physical panel specification |
| Kernel image/DT layout | ARM64 Image; 4096-byte pages; separate DTBO; DTB included in boot image in this build recipe | Community build configuration, not proof of exact stock boot image layout |

## Hardware and driver matrix

| Subsystem | Evidence found | Current assessment | Darwin/XNU status |
|---|---|---|---|
| Display | Motorola kernel config enables Qualcomm MSM DSI Motorola extension (`CONFIG_DRM_MSM_DSI_MOT_EXT=y`); Hanoip build sets 1080 × 2460 and density 440 | Display path is Qualcomm MSM DRM/DSI. Exact panel model, DSI lane/timing data, backlight controller and calibration remain unknown | No MotoDarwin display driver |
| Touchscreen | Hanoip `modules.load` lists `ilitek_v3_mmi.ko`; Hanoip config disables several alternative Goodix/Himax/Synaptics options | Ilitek V3 driver family is indicated; exact controller part number, bus address and interrupt/reset wiring remain unknown | No MotoDarwin touch driver |
| Wi-Fi | `modules.load` lists `qca_cld3_wlan.ko`; `BoardConfig.mk` maps `wlan.ko` to that module | Qualcomm CLD3 WLAN software stack is indicated. Exact radio/SoC part and board revision are not established. Do not assume WCN3990 without further evidence | No MotoDarwin Wi-Fi driver |
| Bluetooth | Qualcomm platform and WLAN stack are present in the Android build sources, but the examined files do not identify the Bluetooth controller/interface | Unknown; requires separate firmware/device-tree evidence | No MotoDarwin Bluetooth driver |
| Cellular modem / telephony | Hanoip proprietary file list and product config include Qualcomm telephony, IMS and radio support components | Qualcomm modem software integration is indicated; modem model, RF front-end, bands and firmware details remain unknown | No MotoDarwin baseband/telephony integration |
| GPU | Adreno 618 device specification; Motorola defconfig enables `CONFIG_QCOM_KGSL=y` | Qualcomm KGSL/Adreno Linux path is indicated. Firmware and Android graphics userspace are separate dependencies | No MotoDarwin GPU driver |
| Audio | Module list includes Qualcomm ADSP/APR, Bolero, WCD934x/WCD937x, WSA881x and `snd_smartpa_aw882xx.ko` | Qualcomm audio DSP/codec-family support is indicated. Exact populated codec/amplifier combination and board routing are not confirmed | No MotoDarwin audio driver |
| Fingerprint | `modules.load` lists `fpc1020_mmi.ko` and `fpsensor_spi_tee.ko` | FPC1020-family fingerprint support is indicated; exact sensor revision and secure-world integration remain unknown | No MotoDarwin fingerprint driver |
| SAR / proximity-related sensing | `modules.load` lists `sx933x_sar.ko` | SX933x SAR driver family is indicated; exact sensor SKU and whether it exposes additional functions are unknown | No MotoDarwin sensor driver |
| General sensors | `sensors_class.ko` appears in module list | A vendor sensor class layer is present; accelerometer, gyroscope, magnetometer, light and proximity part numbers are not identified by this file | No MotoDarwin sensor stack |
| Battery / charging | Motorola kernel config enables `CONFIG_QPNP_QG=y` and `CONFIG_QPNP_SMB5=y`; module list includes `qpnp_adaptive_charge.ko` | Qualcomm PMIC gauge/SMB5 charging support is indicated. Exact PMIC, battery gauge and charger component SKUs are unknown | No MotoDarwin battery/charging driver |
| USB | Hanoip kernel command line names controller `a600000.dwc3` | Qualcomm DWC3 USB controller path is indicated by the community build recipe; connector and alternate-mode capabilities need separate evidence | No MotoDarwin USB driver |
| Storage | Device build uses dynamic partitions and ext4; f2fs is enabled as a filesystem option; `exfat.ko` is listed | Filesystem/build support is visible, but exact UFS/eMMC model, capacity, controller and partition map are not established here | No MotoDarwin storage controller driver |
| Camera | Hanoip proprietary file manifest includes Motorola camera framework and Qualcomm/ArcSoft camera-related components | Camera software stack is proprietary. Exact rear/front sensor models, ISP topology and calibration data remain unknown | No MotoDarwin camera pipeline |
| NFC | No conclusive NFC controller/module evidence in the files examined | Unknown; absence from this limited file sample is not proof the phone lacks NFC | No MotoDarwin NFC driver |
| GNSS | No conclusive GNSS hardware/driver identity in the files examined | Unknown; Qualcomm location software references alone would not identify the physical GNSS implementation | No MotoDarwin GNSS driver |
| Haptics / vibration | Not identified in the examined device-tree files | Unknown | No MotoDarwin haptics driver |

## Source set and important limitations

1. **Motorola kernel source, matching Android 12 tag:**  
   https://github.com/MotorolaMobilityLLC/kernel-msm/tree/MMI-S2RIS32.32-20-9-9-2-3
2. **Motorola Hanoip kernel config fragment:**  
   https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/arch/arm64/configs/vendor/ext_config/moto-sdmmagpie-hanoip.config
3. **Motorola base defconfig:**  
   https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/arch/arm64/configs/vendor/sdmsteppe-perf_defconfig
4. **Community Hanoip device tree, LineageOS 20 branch:**  
   https://github.com/motorola-sm6150-devs/device_motorola_hanoip/tree/lineage-20
5. **Hanoip BoardConfig.mk:**  
   https://github.com/motorola-sm6150-devs/device_motorola_hanoip/blob/lineage-20/BoardConfig.mk
6. **Hanoip modules.load:**  
   https://github.com/motorola-sm6150-devs/device_motorola_hanoip/blob/lineage-20/modules.load
7. **Hanoip device.mk:**  
   https://github.com/motorola-sm6150-devs/device_motorola_hanoip/blob/lineage-20/device.mk
8. **Hanoip proprietary-files manifest:**  
   https://github.com/motorola-sm6150-devs/device_motorola_hanoip/blob/lineage-20/proprietary-files.txt

**Critical caveat:** the community device tree is a LineageOS 20 / Android 13 build recipe shared across the Hanoip family. It is valuable corroborating evidence, but it is not the stock Android 12 build output for this specific XT2135-2 handset. The Motorola kernel tag is the closer match to the reported stock build. The final merged stock `.config`, exact DTB/DTBO contents, loaded module list and per-unit component revisions have not yet been captured.

Android device trees describe hardware to the kernel, including components that cannot be discovered automatically. A source-level device-tree audit is therefore a useful next step, but it must be tied to the correct device-tree revision and overlays before treating a property as confirmed hardware fact.

## Next research priorities

1. Inspect the matching Motorola kernel's Hanoip DTS/DTSI files and DTBO overlays for panel, touch, sensors, camera, PMIC and peripheral nodes.
2. Identify exact camera sensor and general sensor part numbers from device-tree compatible strings and board configuration.
3. Trace the fingerprint, SAR, touch and Wi-Fi module names to their source directories and dependencies.
4. Compare the community LineageOS device tree with the matching Motorola Android 12 kernel tag; record any differences.
5. Keep a separate Darwin feasibility column: CPU/platform support, interrupt controller, timers, memory map, IOMMU, DMA, clocks, power domains and device drivers. A Linux driver cannot be reused as an XNU driver without porting or reimplementation.

No hardware feature in this document is claimed to work under Darwin/XNU. No boot image has been built or tested.
