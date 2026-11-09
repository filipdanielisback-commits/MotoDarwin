# Android 12 kernel audit — Moto G60 XT2135-2

## Target and source provenance

- Device: Motorola Moto G60 XT2135-2
- RAM configuration: 6 GB (reported by device owner)
- Android build: `S2RIS32.32-20-9-9-2-3`
- Motorola kernel source tag: `MMI-S2RIS32.32-20-9-9-2-3`
- Official source release: https://github.com/MotorolaMobilityLLC/kernel-msm/releases/tag/MMI-S2RIS32.32-20-9-9-2-3
- Matching source tag is described by Motorola as a Hanoip push for Android 12.

## Kernel version and configuration

The `Makefile` in that exact source tag sets:

- `VERSION = 4`
- `PATCHLEVEL = 14`
- `SUBLEVEL = 190`
- Kernel source base: **Linux 4.14.190**

Source: https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/Makefile

The source tag contains `arch/arm64/configs/vendor/sdmsteppe-perf_defconfig`. It sets `CONFIG_LOCALVERSION="-perf"`, `CONFIG_ARCH_QCOM=y`, `CONFIG_ARCH_SM6150=y`, `CONFIG_ARCH_SDMMAGPIE=y`, `CONFIG_NR_CPUS=8`, and `CONFIG_QCOM_KGSL=y`. It also enables the QPNP gauge/charger options noted below.

Base defconfig: https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/arch/arm64/configs/vendor/sdmsteppe-perf_defconfig

The Motorola Hanoip fragment `arch/arm64/configs/vendor/ext_config/moto-sdmmagpie-hanoip.config` sets `CONFIG_HANOIP_DTB=y`, `CONFIG_DRM_MSM_DSI_MOT_EXT=y`, and `CONFIG_PANEL_NOTIFICATIONS=y`. It explicitly disables the Goodix GTX8, Himax, and Synaptics DSX touchscreen options, as well as SMB1355 and SMB1390 charger options.

Hanoip fragment: https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/arch/arm64/configs/vendor/ext_config/moto-sdmmagpie-hanoip.config

**Configuration caveat:** the community Hanoip device tree's `BoardConfig.mk` names the base `vendor/sdmsteppe-perf_defconfig` and Motorola fragments as its kernel configuration inputs. That device tree is a LineageOS 20 build tree, not the stock Android 12 build output from this handset. The exact final `.config` used by the phone has not been extracted. A separate Motorola config fragment sets `CONFIG_HZ_300=y` while the base defconfig contains `CONFIG_HZ_100=y`; the final merged setting must be checked rather than guessed. The running kernel release string also remains to be read from the device.

Community build recipe: https://github.com/motorola-sm6150-devs/device_motorola_hanoip/blob/lineage-20/BoardConfig.mk

## Hardware and driver findings

### Wi-Fi

The Hanoip device tree's `modules.load` lists `qca_cld3_wlan.ko`, and `BoardConfig.mk` maps the Android module alias `wlan.ko` to `qca_cld3_wlan.ko`. This is stronger device-family evidence for a Qualcomm CLD3 vendor WLAN software stack than the earlier generic WCN3990 lead.

- Driver/module family: Qualcomm CLD3 WLAN (`qca_cld3_wlan.ko`) — listed in the Hanoip module load list.
- Exact radio chipset and revision: **not identified yet**.
- The Motorola kernel tree also contains generic `ath10k` / WCN3990 SNOC support, but that alone does not connect WCN3990 to this handset. Do not label the XT2135-2 as WCN3990 without device-specific evidence.
- No MotoDarwin/XNU Wi-Fi driver exists; no Wi-Fi functionality has been tested under Darwin.

References:
- https://github.com/motorola-sm6150-devs/device_motorola_hanoip/blob/lineage-20/modules.load
- https://github.com/motorola-sm6150-devs/device_motorola_hanoip/blob/lineage-20/BoardConfig.mk
- Generic ath10k Kconfig in Motorola source: https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/drivers/net/wireless/ath/ath10k/Kconfig

### Display

The Hanoip config enables `CONFIG_DRM_MSM_DSI_MOT_EXT=y`; the kernel source contains Qualcomm MSM DRM/DSI support. The Hanoip Android device tree sets a 1080 × 2460 display mode and density 440. The exact LCD panel identifier, DSI timing table, backlight controller, and panel-specific initialization sequence are **not yet identified**.

References:
- https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/arch/arm64/configs/vendor/ext_config/moto-sdmmagpie-hanoip.config
- https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/drivers/gpu/drm/msm/Kconfig
- https://github.com/motorola-sm6150-devs/device_motorola_hanoip/blob/lineage-20/device.mk

### Touchscreen

The Hanoip `modules.load` file lists `ilitek_v3_mmi.ko`. Its Hanoip config fragment disables Goodix GTX8, Himax, and Synaptics DSX options. This points to an Ilitek V3 Motorola touchscreen module in the Hanoip software stack, but the exact touch-controller part number and bus configuration remain **unknown**. The public kernel source location for the exact module has not yet been confirmed.

Reference: https://github.com/motorola-sm6150-devs/device_motorola_hanoip/blob/lineage-20/modules.load

### Audio

The Hanoip module list includes Qualcomm audio DSP/platform modules and codec/amplifier modules such as `audio_wcd937x.ko`, `audio_wcd937x_slave.ko`, `audio_wcd934x.ko`, `audio_wsa881x.ko`, `audio_wsa_macro.ko`, and `snd_smartpa_aw882xx.ko`. The build file maps these module names to the corresponding Android audio module aliases.

This indicates support for a Qualcomm audio DSP and WCD/WSA audio-driver family plus an AW882xx smart-amplifier module. It does **not** by itself prove which codec/amplifier chips are physically populated or active on every XT2135-2 unit.

Reference: https://github.com/motorola-sm6150-devs/device_motorola_hanoip/blob/lineage-20/modules.load

### GPU

The target handset's published SoC specification identifies an Adreno 618 GPU. The Motorola kernel base defconfig enables `CONFIG_QCOM_KGSL=y`; the source includes the Qualcomm KGSL/Adreno driver stack under `drivers/gpu/msm/`. This is the Android/Linux GPU path. It is not an XNU graphics driver and does not supply Apple's graphics frameworks or a Darwin userspace graphics stack.

References:
- https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/arch/arm64/configs/vendor/sdmsteppe-perf_defconfig
- https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/drivers/gpu/msm/Kconfig

### Battery and power

The base defconfig enables `CONFIG_QPNP_QG=y` and `CONFIG_QPNP_SMB5=y`; the Hanoip module list includes `qpnp_adaptive_charge.ko`. The Hanoip-specific config disables SMB1355 and SMB1390 options. This identifies the QPNP fuel-gauge / SMB5 charging software families used in the platform configuration. The exact PMIC part number and battery-gauge hardware revision still require device-tree or runtime confirmation.

References:
- https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/arch/arm64/configs/vendor/sdmsteppe-perf_defconfig
- https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/arch/arm64/configs/vendor/ext_config/moto-sdmmagpie-hanoip.config
- https://github.com/motorola-sm6150-devs/device_motorola_hanoip/blob/lineage-20/modules.load

## Confidence and remaining work

| Area | Finding | Confidence |
|---|---|---|
| Kernel source version | Linux 4.14.190 in matching Motorola tag | Confirmed from tag Makefile |
| Kernel config family | sdmsteppe perf defconfig + Hanoip fragment | Source confirmed; exact stock merged `.config` not captured |
| Wi-Fi stack | `qca_cld3_wlan.ko` listed | Device-tree evidence; exact radio chip unknown |
| Display path | Qualcomm MSM DRM/DSI with Motorola DSI extension | Config/source confirmed; exact panel unknown |
| Touch | `ilitek_v3_mmi.ko` listed; generic Goodix/Himax/Synaptics options disabled | Device-tree evidence; exact controller unknown |
| Audio | WCD937x/WCD934x/WSA881x/AW882xx modules listed | Device-tree evidence; physical component mapping unknown |
| GPU | Adreno 618 target; QCOM KGSL enabled | SoC spec + kernel config; no Darwin driver |
| Battery/power | QPNP QG + SMB5 config; adaptive-charge module listed | Config/module evidence; exact PMIC unknown |

## Next read-only checks

1. Capture the running kernel release string (`uname -r`) and Android build fingerprint.
2. If available, read `/proc/config.gz` or the kernel's exported configuration to compare the actual running configuration with the source defconfig fragments.
3. Inspect the matching Hanoip device-tree nodes and module metadata for exact WLAN, display panel, touch controller, codec, and PMIC identifiers.
4. Record only filenames, IDs, and provenance. Do not copy proprietary firmware, calibration data, or vendor binaries into this repository.

All findings here are source research, not evidence that any MotoDarwin driver works.