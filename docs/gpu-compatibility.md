# GPU compatibility research — Moto G60 (Hanoip)

**Status:** Source audit only. No GPU driver has been ported, built, or tested under Darwin/XNU.

## Target and evidence

- Device: Motorola Moto G60 XT2135-2, codename `hanoip`.
- Reported platform: Qualcomm Snapdragon 732G family; Adreno 618.
- Matching Motorola kernel source tag: `MMI-S2RIS32.32-20-9-9-2-3`.
- The matching source tree's `arch/arm64/configs/vendor/sdmsteppe-perf_defconfig` enables `CONFIG_QCOM_KGSL=y`.
- In that source tag, `drivers/gpu/msm/Kconfig` describes KGSL as Qualcomm's Adreno 3D graphics driver and states it provides GPU power management, memory management and scheduling.
- `drivers/gpu/msm/Makefile` builds two objects under `CONFIG_QCOM_KGSL`: `msm_kgsl_core.o` and `msm_adreno.o`. The core includes memory management, MMU, power-control, GMU/HFI and related support; the Adreno side includes A3xx–A6xx generation-specific code, including `adreno_a6xx.o` and A6xx GMU support.

**Evidence limitation:** The defconfig is a build configuration, not the final merged runtime kernel configuration. It shows that the matching kernel source is configured to include KGSL; it does not by itself prove which GPU firmware was loaded or which userspace graphics stack is active on this particular handset.

## What the Linux graphics stack is responsible for

The source layout and Qualcomm's public KGSL documentation show several distinct responsibilities:

1. **Kernel GPU driver (KGSL/Adreno):** device management, GPU memory allocation and mapping, command submission, scheduling, synchronization, power/frequency management, interrupts and fault handling.
2. **GPU firmware:** the A6xx path has GPU microcontroller/GMU-related firmware dependencies. Firmware filenames and exact firmware package contents must be checked against the matching target-specific source and firmware manifest before treating them as confirmed for this handset.
3. **Userspace graphics drivers:** OpenGL ES/Vulkan implementations translate graphics API calls into GPU work. Qualcomm's proprietary userspace stack and open-source Mesa/Freedreno are separate from the kernel driver.
4. **Display integration:** rendering also needs a working display controller, buffer sharing, synchronization and compositor/window-system integration. A GPU driver alone does not provide a complete graphical operating system.

## Open-source reference: Mesa Freedreno / Turnip

Mesa documents Freedreno as an OpenGL/GLES driver for Adreno 2xx–6xx GPUs and Turnip as its Vulkan driver for Adreno 6xx GPUs. This is useful evidence that there is an open-source userspace graphics implementation for the broad Adreno generation.

It is **not** evidence of a ready-made Moto G60 Darwin driver. Mesa's Linux integration relies on operating-system kernel interfaces and surrounding graphics infrastructure. Reusing its userspace components would require an appropriate kernel interface and memory/synchronization/display integration on the target OS.

## Darwin/XNU compatibility assessment

| Area | Linux/Moto G60 evidence | What a Darwin port would still need |
|---|---|---|
| GPU identification | Adreno 618 is the target GPU family reported for this platform | Confirm exact GPU core/revision from reliable target-specific evidence |
| Kernel device driver | Qualcomm KGSL and Adreno A6xx implementation in the matching Linux source | A Darwin/XNU driver or carefully designed compatibility layer for device discovery, resources, interrupts, synchronization and lifecycle |
| GPU memory | KGSL contains GPU memory and MMU management | XNU-compatible memory allocation, IOMMU/SMMU mappings, cache coherency and safe buffer lifetime handling |
| Command submission | KGSL/Adreno kernel path schedules and submits work | A new XNU-facing submission and synchronization path; Linux ioctl interfaces cannot simply be assumed to exist |
| Firmware | A6xx code includes GMU/HFI and firmware support paths | Verify exact required firmware and lawful availability; implement safe loading and power-on sequencing in a suitable driver |
| Graphics APIs | Mesa Freedreno/Turnip provide open-source Adreno userspace drivers on supported systems | Port/integration work for the target OS, plus a supported kernel interface and graphics runtime |
| Display/compositor | Separate display and buffer-sharing components are required | Display driver, buffer sharing, compositor and window-system integration |

## Current conclusion

**GPU acceleration is a major, separate engineering project.** The matching Motorola source gives us a useful Linux reference implementation, but it is not portable to XNU by changing a few build flags. The safest and most realistic research path is to map interfaces and dependencies first, without attempting to load drivers, alter firmware, or change the phone's boot configuration.

For MotoDarwin planning, classify the GPU as:

- **Linux reference implementation identified:** Qualcomm KGSL + Adreno A6xx code in the matching Motorola source.
- **Open-source userspace reference identified:** Mesa Freedreno/Turnip for Adreno families, subject to exact chip support and platform integration.
- **Darwin/XNU implementation:** not present; new driver and graphics-stack integration required.
- **Hardware bring-up:** not attempted.

## Sources

1. Motorola kernel source, matching tag: https://github.com/MotorolaMobilityLLC/kernel-msm/tree/MMI-S2RIS32.32-20-9-9-2-3
2. KGSL Kconfig: https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/drivers/gpu/msm/Kconfig
3. KGSL build composition: https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/drivers/gpu/msm/Makefile
4. Qualcomm KGSL public overview: https://github.com/qualcomm-linux/kgsl
5. Mesa Freedreno documentation: https://docs.mesa3d.org/drivers/freedreno.html
6. Qualcomm graphics documentation: https://docs.qualcomm.com/bundle/publicresource/topics/80-80020-19
