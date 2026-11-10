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
| Display | Motorola DTS includes Tianma ILI7807S panel definition for 1080 × 2460, 60/120 Hz; PM6150L WLED backlight | Panel family and reset/TE/enable control lines are identified in source; exact fitted panel revision still unconfirmed | No MotoDarwin display driver |
| Touchscreen | Motorola DTS declares `tchip,ilitek` on QUPv3 SPI SE6 at up to 12 MHz; reset GPIO 8 and IRQ GPIO 9 | Ilitek SPI interface and board connections identified; exact controller part number remains unknown | No MotoDarwin touch driver |
| Wi-Fi | `modules.load` lists `qca_cld3_wlan.ko`; `BoardConfig.mk` maps `wlan.ko` to that module | Qualcomm CLD3 WLAN software stack is indicated. Exact radio/SoC part and board revision are not established. Do not assume WCN3990 without further evidence | No MotoDarwin Wi-Fi driver |
| Bluetooth | Qualcomm platform and WLAN stack are present in the Android build sources, but the examined files do not identify the Bluetooth controller/interface | Unknown; requires separate firmware/device-tree evidence | No MotoDarwin Bluetooth driver |
| Cellular modem / telephony | Hanoip proprietary file list and product config include Qualcomm telephony, IMS and radio support components | Qualcomm modem software integration is indicated; modem model, RF front-end, bands and firmware details remain unknown | No MotoDarwin baseband/telephony integration |
| GPU | Adreno 618 device specification; Motorola defconfig enables `CONFIG_QCOM_KGSL=y` | Qualcomm KGSL/Adreno Linux path is indicated. Firmware and Android graphics userspace are separate dependencies | No MotoDarwin GPU driver |
| Audio | Hanoip DTS enables Bolero and WCD937x; AW882xx smart amp on I²C SE2 address 0x34; WSA macro is disabled | WCD937x + AW882xx is the best-supported active path in this overlay; module presence alone does not prove WSA881x/WCD934x is active | No MotoDarwin audio driver |
| Fingerprint | `modules.load` lists `fpc1020_mmi.ko` and `fpsensor_spi_tee.ko` | FPC1020-family fingerprint support is indicated; exact sensor revision and secure-world integration remain unknown | No MotoDarwin fingerprint driver |
| SAR / proximity-related sensing | Motorola DTS declares Semtech SX933x on I²C SE7 at address 0x28, IRQ GPIO 84 | Device family, bus and interrupt line identified; exact silicon revision and function set remain unknown | No MotoDarwin sensor driver |
| General sensors | `sensors_class.ko` appears in module list | A vendor sensor class layer is present; accelerometer, gyroscope, magnetometer, light and proximity part numbers are not identified by this file | No MotoDarwin sensor stack |
| Battery / charging | Motorola kernel config enables `CONFIG_QPNP_QG=y` and `CONFIG_QPNP_SMB5=y`; module list includes `qpnp_adaptive_charge.ko` | Qualcomm PMIC gauge/SMB5 charging support is indicated. Exact PMIC, battery gauge and charger component SKUs are unknown | No MotoDarwin battery/charging driver |
| USB | Hanoip kernel command line names controller `a600000.dwc3` | Qualcomm DWC3 USB controller path is indicated by the community build recipe; connector and alternate-mode capabilities need separate evidence | No MotoDarwin USB driver |
| Storage | SDMMAGPIE DTS exposes UFS host controller alias `ufshc1` and vendor partition path `1d84000.ufshc` | UFS controller path identified; exact storage package/model and capacity remain unknown | No MotoDarwin storage controller driver |
| Camera | Motorola camera overlays define rear main, rear depth, rear wide and front positions; comments name S5KHM2/OV64B, OV02B1B, S5K4H7, OV16A1Q/OV32B candidates | Camera topology and candidate sensor families identified; comments list alternatives and do not prove the exact fitted sensor | No MotoDarwin camera pipeline |
| NFC | Hanoip common DTS overlay declares `qcom,nq-nci` on I²C SE2 at address 0x28 with IRQ/enable/firmware/clock-request GPIOs | NFC interface is present in the Hanoip source; exact commercial controller part number remains unknown | No MotoDarwin NFC driver |
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

## DTS/DTBO audit update

The matching Motorola kernel tag has now been inspected directly. See [DTS/DTBO source audit](dts-dtbo-audit.md) for the Hanoip overlays, board IDs, panel, touch, NFC, SAR, audio, camera candidates, and platform-level interfaces. The exact selected overlay for this handset remains unconfirmed.

No hardware feature in this document is claimed to work under Darwin/XNU. No boot image has been built or tested.


## Live ADB observations (2026-11-10)

The handset was inspected using ordinary, read-only ADB commands while Android remained booted. `adb devices` succeeded. Runtime properties report `hanoip`, SKU `XT2135-2`, platform `sm6150`, hardware revision `pvt`, DTBO index `1`, and NFC property label `pn54x`. `uname -a` reports `Linux localhost 4.14.190-perf+ #1 SMP PREEMPT Fri Oct 27 13:02:24 CDT 2023 aarch64`. The build fingerprint is `motorola/hanoip_retailenq/hanoip:12/S2RIS32.32-20-9-9-2-3/f495e7-429de:user/release-keys`.

The live device-tree root exists at `/sys/firmware/devicetree/base` (`/proc/device-tree` is a symlink to it), and its root directory listing includes `qcom,board-id`, `qcom,msm-id`, `qcom,msm-name`, `chosen`, `hw`, and `utags`. Reading `model`, `qcom,board-id`, and `qcom,msm-id` as the ordinary ADB shell user returned `Permission denied`; no permission changes or privilege escalation were attempted.

Android documents `androidboot.dtbo_idx` as the zero-based index or indices of overlays selected from the DTBO partition and applied to the base device tree. Thus `ro.boot.dtbo_idx=1` is a DTBO entry index, not an EVT/DVT label. The exact stock DTBO image and entry ordering have not been correlated with the Motorola source overlays. The selected EVT1/DVT1/DVT2 overlay remains **unconfirmed**. See [live ADB device audit](adb-device-audit.md).
