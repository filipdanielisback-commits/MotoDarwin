# Moto G60 DTS / DTBO source audit

**Target:** Motorola Moto G60 XT2135-2 / `hanoip`  
**Kernel source:** Motorola `kernel-msm`, tag `MMI-S2RIS32.32-20-9-9-2-3`  
**Kernel version reported by owner:** `4.14.190-perf+`

This audit reads the source Device Tree (DTS/DTSI) and Device Tree Overlay (DTBO) definitions. It is a source-level map, not a dump of the exact live device tree from the handset. The exact DTBO selected by the bootloader on this particular phone has not yet been identified.

## 1. Overlay selection and board-revision caveat

The Motorola kernel's Qualcomm DTS Makefile lists three Hanoip overlays:

| Overlay | MSM ID | Board ID |
|---|---:|---:|
| `sdmmagpie-hanoip-evt1-overlay.dts` | `365 0x0` | `0x4C 0xA100` |
| `sdmmagpie-hanoip-dvt1-overlay.dts` | `365 0x0` | `0x4C 0xB100` |
| `sdmmagpie-hanoip-dvt2-overlay.dts` | `365 0x0` | `0x4C 0xB200` |

All three include `sdmmagpie-hanoip-common-overlay.dtsi`, and each includes a corresponding camera-sensor overlay. The Makefile associates them with the shared base `sdmmagpie-hanoi-base.dtb`.

**Important:** we have not established which board ID / overlay the user's XT2135-2 selects. Do not arbitrarily choose EVT1, DVT1 or DVT2 as the exact handset configuration. Common-overlay findings below are strong evidence for the Hanoip family; revision-specific details remain provisional until the selected DTBO is known.

## 2. Findings from the Hanoip common overlay

### Display

The common overlay includes `hanoi-panel.dtsi`. That file includes:

`dsi-panel-mot-tianma-ili7807s-678-1080x2460-video.dtsi`

The panel configuration identifies a Tianma supplier (`tm`) and ILI7807S panel family, with a 1080 × 2460 mode in the panel definition. The Hanoip panel settings include dynamic refresh support for **60 Hz and 120 Hz**, HDR-related properties and a WLED backlight path.

Notable control connections in the panel definition:
- Reset: PM6150L GPIO 9
- Tearing-effect (TE) signal: TLMM GPIO 10
- Panel enable: TLMM GPIO 55
- Backlight: PM6150L WLED

**Assessment:** panel family and control path are identified in the Hanoip source. The exact panel assembly/revision fitted to this individual phone still needs confirmation from its selected DTB/DTBO or runtime panel identity.

Source: [hanoi-panel.dtsi](https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/arch/arm64/boot/dts/qcom/hanoi-panel.dtsi)

### Touchscreen

The included `sdmmagpie-hanoi-touchscreen.dtsi` enables Qualcomm QUPv3 SPI controller SE6 and declares:

- Compatible: `tchip,ilitek`
- SPI maximum frequency: 12 MHz
- Reset GPIO: TLMM GPIO 8
- Interrupt GPIO: TLMM GPIO 9

This is much more specific than the module name alone: the source identifies an Ilitek-family SPI touchscreen connection and its board-level control signals.

**Assessment:** strong evidence for the Ilitek SPI touchscreen path; exact controller part number and hardware revision remain unknown.

Source: [sdmmagpie-hanoi-touchscreen.dtsi](https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/arch/arm64/boot/dts/qcom/sdmmagpie-hanoi-touchscreen.dtsi)

### NFC

The Hanoip common overlay defines an NFC node on QUPv3 I²C SE2:

- Compatible: `qcom,nq-nci`
- I²C address: `0x28`
- IRQ: TLMM GPIO 37
- VEN / enable: TLMM GPIO 12
- Firmware control: TLMM GPIO 36
- Clock request: TLMM GPIO 31
- eSE power signal: TLMM GPIO 94

This upgrades NFC from “unknown” to **NFC controller interface present in the Hanoip device-tree source**. The compatible string identifies the NQ-NCI software interface, not the exact commercial controller part number.

Source: [sdmmagpie-hanoip-common-overlay.dtsi](https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/arch/arm64/boot/dts/qcom/sdmmagpie-hanoip-common-overlay.dtsi)

### SAR sensing

The Hanoip sensor overlay declares:

- Compatible: `Semtech,sx933x`
- Bus: QUPv3 I²C SE7
- I²C address: `0x28`
- Interrupt: TLMM GPIO 84
- Supply: PM6150 L16 regulator node

The source also includes device-specific register initialization and reference-phase settings.

**Assessment:** strong evidence for an SX933x-family SAR sensor path. The exact component revision and its full runtime function set remain unconfirmed.

Source: [sdmmagpie-hanoip-sensor-overlay.dtsi](https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/arch/arm64/boot/dts/qcom/sdmmagpie-hanoip-sensor-overlay.dtsi)

### Audio

The Hanoip audio overlay provides more precise information than the module list:

- `&bolero` is enabled.
- `&wcd937x_codec` is enabled.
- `&sm6150_snd` is enabled with model `sm6150-awinic-snd-card`.
- The sound-card node sets `aw,have-882xx = <1>`.
- An Awinic `aw882xx_smartpa` node is declared on QUPv3 I²C SE2 at address `0x34`.
- The AW882xx node uses TLMM GPIO 43 for reset and GPIO 91 for IRQ.
- The overlay disables `wsa_macro`, WSA speaker-enable GPIO nodes and several alternate/legacy audio paths.

**Assessment:** WCD937x + Bolero and an AW882xx smart-amplifier path are the best-supported active audio configuration in this source. The mere presence of WSA881x or WCD934x kernel modules in a module list does not mean those components are enabled in this Hanoip audio overlay.

Source: [sdmmagpie-hanoi-audio-overlay.dtsi](https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/arch/arm64/boot/dts/qcom/sdmmagpie-hanoi-audio-overlay.dtsi)

## 3. Camera source evidence

Each Hanoip board-revision overlay includes a matching camera file:

- EVT1: `sdmmagpie-camera-sensor-mot-hanoip-evt1-overlay.dtsi`
- DVT1: `sdmmagpie-camera-sensor-mot-hanoip-dvt1-overlay.dtsi`
- DVT2: `sdmmagpie-camera-sensor-mot-hanoip-dvt2-overlay.dtsi`

The camera definitions describe four logical sensor positions and their clock, reset, regulator and CCI connections. Comments in the files name these sensor candidates:

| Position | Comment in source | Interpretation |
|---|---|---|
| Rear main | `S5KHM2` compatible with `OV64B` | Candidate sensor families / alternatives; not a unique confirmed part |
| Rear depth | `OV02B1B` | Named candidate |
| Rear wide | `S5K4H7` | Named candidate |
| Front | `OV16A1Q` and `OV32B` | Explicit alternatives in source comments and power configuration |

The camera nodes use Qualcomm camera-sensor / CCI framework nodes rather than identifying each physical sensor with a unique standard `compatible` string. The comments and supply alternatives are therefore useful clues, not definitive proof of the exact sensor installed in every handset.

**Assessment:** the camera topology and several likely sensor families are identified; exact physical sensor SKUs remain provisional. Camera operation also depends on proprietary tuning, calibration, firmware and userspace components.

Sources:
- [EVT1 camera overlay](https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/arch/arm64/boot/dts/qcom/sdmmagpie-camera-sensor-mot-hanoip-evt1-overlay.dtsi)
- [DVT1 camera overlay](https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/arch/arm64/boot/dts/qcom/sdmmagpie-camera-sensor-mot-hanoip-dvt1-overlay.dtsi)
- [DVT2 camera overlay](https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/arch/arm64/boot/dts/qcom/sdmmagpie-camera-sensor-mot-hanoip-dvt2-overlay.dtsi)

## 4. Platform-level details relevant to XNU feasibility

The shared SDMMAGPIE platform DTSI exposes several foundational interfaces:

| Platform feature | Source evidence | Why it matters to an OS port |
|---|---|---|
| CPU topology | Eight ARMv8 CPU nodes | CPU bring-up, topology and interrupt routing |
| Interrupt controller | ARM GICv3 plus Qualcomm PDC | XNU needs compatible interrupt-controller support |
| Timer | ARMv8 generic timer | Kernel clock and scheduling |
| Firmware interface | PSCI 1.0 using SMC | CPU start/stop and platform power transitions |
| Storage | UFS host controller node / alias `ufshc1`; vendor partition path uses `1d84000.ufshc` | Storage-controller and block-device support |
| Memory reservations | Reserved regions for modem, camera, video, GPU, secure-world and shared-memory use | Memory map and DMA reservations must be understood |
| Clock/power framework | Qualcomm RPMh, GCC, camera/display/GPU clock-controller nodes | Clock, reset and power-domain dependencies |

These entries are platform-level source definitions. They are not a ready-made XNU platform implementation. In particular, Linux's device-tree bindings, Qualcomm firmware interfaces and Linux drivers cannot simply be assumed to work in XNU.

Source: [sdmmagpie.dtsi](https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/arch/arm64/boot/dts/qcom/sdmmagpie.dtsi)

## 5. Updated compatibility conclusions

| Subsystem | DTS/DTBO conclusion | Confidence |
|---|---|---|
| Display | Tianma ILI7807S panel family; 1080 × 2460; 60/120 Hz configuration | Strong source evidence; exact panel assembly not independently confirmed |
| Touch | Ilitek-compatible SPI device on SE6; GPIO 8 reset / GPIO 9 IRQ | Strong source evidence |
| NFC | NQ-NCI I²C node on SE2, address 0x28 | Strong source evidence |
| SAR | Semtech SX933x I²C node on SE7, address 0x28 | Strong source evidence |
| Audio | WCD937x + Bolero enabled; AW882xx I²C smart amp at 0x34 | Strong source evidence |
| Camera | Four logical positions; likely sensor families named in comments, with alternatives | Partial |
| CPU / interrupt / timer / PSCI | ARMv8, GICv3/PDC, ARM generic timer, PSCI 1.0 | Strong platform-source evidence |
| UFS | UFS host controller referenced by DTS aliases and vendor path | Strong platform-source evidence |
| Wi-Fi / Bluetooth | This overlay set does not uniquely identify the physical radio part | Still unresolved |
| Exact selected board revision | EVT1/DVT1/DVT2 overlay candidates found; handset selection unknown | Unresolved |

No Darwin/XNU driver has been implemented or tested for any of these devices.

## 6. Next evidence needed

The remaining key question is **which board-revision DTBO is actually selected on the XT2135-2**. The source offers three Hanoip board IDs, but the phone's live selection is not established by its Android build number or kernel version alone.

After that, the highest-value research tasks are:
1. Compare the selected overlay with the stock Android 12 build's DTBO metadata, if a trustworthy stock build manifest or device-tree dump is available.
2. Identify the exact camera sensor variant from sensor ID / calibration metadata, without assuming the comments uniquely identify it.
3. Trace the WLAN and Bluetooth device-tree / firmware nodes to identify the actual radio hardware.
4. Convert the platform-level requirements into a Darwin bring-up checklist: CPU topology, GICv3/PDC, timer, PSCI, memory map, UFS, clocks, power domains and DMA/IOMMU.
5. Keep all device investigation read-only; no boot-chain changes or experimental flashing are part of this research phase.

## 7. Source and scope notes

The kernel source is the Motorola Android 12 release tag matching the owner's reported build and kernel baseline. The Hanoip community device tree used in the earlier audit is a separate LineageOS 20 build recipe. Findings in this document come from the Motorola kernel source tag itself, which makes them stronger evidence for this firmware family, but the exact stock merged DTB/DTBO selection for this specific handset remains unverified.

The source DTS/DTSI files are published in Motorola's kernel repository. This document records findings and links to source; it does not copy the kernel source into MotoDarwin.


## 8. Follow-up: Motorola DTBO build-list ordering (2026-11-10)

The matching tag's `arch/arm64/boot/dts/qcom/Makefile` lists the Hanoip DTBO targets under `dtbo-$(CONFIG_HANOIP_DTB)` in this local order:

1. `sdmmagpie-hanoip-evt1-overlay.dtbo`
2. `sdmmagpie-hanoip-dvt1-overlay.dtbo`
3. `sdmmagpie-hanoip-dvt2-overlay.dtbo`

The same Makefile maps each of these three overlay targets to the shared base `sdmmagpie-hanoi-base.dtb`. The matching Hanoip config fragment sets `CONFIG_HANOIP_DTB=y`. This confirms that the Hanoip family DTBO targets are enabled in the source configuration and documents their order in this Makefile section.

**This local Makefile order is not enough to map the handset's `ro.boot.dtbo_idx=1` to DVT1.** The runtime index refers to an entry in the final DTBO image/table. The full generated table, its global entry ordering, and the exact stock firmware artifact have not been inspected. Other DTBO targets/configuration and packaging steps may affect the final table order. Therefore DVT1 is only a hypothesis suggested by the local list position, not a confirmed selection. Do not label the handset as DVT1 on this evidence.

Sources:
- [Motorola DTS Makefile at matching tag](https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/arch/arm64/boot/dts/qcom/Makefile)
- [Hanoip config fragment at matching tag](https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/arch/arm64/configs/vendor/ext_config/moto-sdmmagpie-hanoip.config)
