# XNU GPU Driver Design — Adreno 618

**Status:** design proposal only; no driver implementation exists and nothing has been built or tested on the Moto G60.

## 1. Purpose

This document defines a research architecture for investigating graphics support for the Qualcomm Adreno 618 GPU in the Motorola Moto G60 (hanoip). The intended outcome is a small, independently testable prototype architecture—not an iOS port and not a claim of compatibility with Apple's graphics stack.

The current evidence is source-level: the matching Motorola kernel source enables Qualcomm KGSL and contains A6xx support. This is a useful reference for understanding the hardware responsibilities, but Linux KGSL is not an XNU driver and its interfaces cannot be copied directly.

## 2. Scope and non-goals

### In scope

- Map the responsibilities of the existing Linux KGSL implementation.
- Define OS-neutral interfaces for GPU resources, memory objects, synchronization and diagnostics.
- Separate kernel responsibilities from user-space graphics API work.
- Identify unknown hardware and platform dependencies.
- Specify mock-backed tests that do not require a phone.

### Out of scope

- A working or loadable kernel driver at this stage.
- Device boot, firmware replacement, partition changes or flashing.
- Reusing Linux ioctl interfaces as an XNU ABI.
- Claiming support for Metal, OpenGL, Vulkan, UIKit or other Apple frameworks.
- Bundling proprietary firmware or undocumented firmware-loading procedures.

## 3. Known target facts

| Item | Current evidence |
|---|---|
| Device | Motorola Moto G60, XT2135-2, codename hanoip |
| SoC family | Qualcomm SM6150 family reported by Android properties |
| GPU | Adreno 618, supported by the matching Motorola kernel source's A618 definitions |
| Kernel baseline | Motorola tag `MMI-S2RIS32.32-20-9-9-2-3`, Linux 4.14.190 |
| Linux GPU stack | Qualcomm KGSL enabled in the matching vendor defconfig |
| GPU generation support | KGSL source includes A6xx implementation paths |
| XNU support | Not established; no port exists in this repository |

These facts do not establish the exact runtime GPU firmware, final device configuration, or a complete hardware initialization sequence.

## 4. Layered architecture

A future prototype should keep the following layers distinct:

1. **Platform resource description** — identifies the GPU's resources and their ownership: register regions, interrupts, clocks, power domains, reset controls and IOMMU/SMMU relationships. Values must come from verified platform documentation/source, not guesses.
2. **XNU platform glue** — owns lifecycle and resource coordination using interfaces available in the chosen XNU-derived environment. The exact IOKit or other driver model must be validated against that environment; Apple's private frameworks must not be assumed to exist in generic open-source XNU.
3. **GPU core** — OS-neutral state and policy: device state, queues, memory-object bookkeeping, synchronization abstractions, fault reporting and diagnostics.
4. **Hardware-generation layer** — isolates Adreno 6xx-specific concepts from the generic core. It should initially be an interface with a mock implementation, not register-programming code.
5. **User-space graphics integration** — a separate project. OpenGL/Vulkan implementations and buffer-sharing/compositor integration are not the kernel driver's job. Mesa Freedreno/Turnip are useful architectural references, not drop-in Darwin components.
6. **Display pipeline** — separate from the GPU. Display controller, DSI panel, backlight, buffer formats and compositor integration need their own compatibility investigation.

## 5. Responsibility map from Linux KGSL

| Responsibility | Linux reference | Proposed design boundary |
|---|---|---|
| Device lifecycle and power state | KGSL core / platform integration | Platform adapter plus generic device-state interface |
| GPU generation support | Adreno-specific KGSL code | Hardware-generation interface |
| GPU virtual memory and mappings | KGSL memory/MMU code | Memory-object and address-space abstractions |
| Command execution and scheduling | KGSL submission/scheduler paths | Queue and submission model; protocol remains unresolved |
| Firmware interaction | KGSL/GMU-related code and platform firmware dependencies | Explicit capability boundary; no assumed compatibility |
| Interrupts and fault reporting | KGSL and platform interrupt paths | Event and fault interface |
| User API | Linux KGSL userspace ABI | New, documented prototype ABI if ever needed; do not reuse Linux ioctl ABI |

The table is a conceptual mapping, not an implementation recipe. A Linux subsystem's internal API, locking model, DMA assumptions and memory-management contracts are not automatically valid in XNU.

## 6. Core interface sketch

The first code should define narrow, mockable interfaces rather than touch hardware:

- `GpuPlatformResources`: descriptive resource inventory and ownership metadata.
- `GpuDeviceState`: abstract states such as unavailable, initialized, active, suspended and faulted.
- `GpuMemoryObject`: opaque allocation identity, size, access permissions and lifetime.
- `GpuAddressSpace`: abstract mapping ownership and mapping validity; no physical addresses hard-coded in the generic layer.
- `GpuQueue`: logical queue identity and lifecycle, without assuming a hardware packet format.
- `GpuFence`: synchronization state and completion/error reporting.
- `GpuFault`: structured fault category and diagnostic context, avoiding sensitive memory dumps.
- `GpuDiagnostics`: version, capabilities, state transitions and counters suitable for tests.

All interfaces should return explicit errors, define ownership/lifetime rules, and avoid exposing kernel pointers to user space. The mock backend should simulate success, timeout, invalid input, resource exhaustion and device-fault cases.

## 7. Memory and synchronization design questions

These are unresolved design requirements, not claims about the target implementation:

- Which address spaces are used by the GPU, CPU and secure-world components?
- What are the IOMMU/SMMU translation and isolation requirements?
- Which memory types and cache-coherency rules apply?
- How are buffers shared with the display controller?
- What synchronization primitives are available in the selected XNU environment?
- What are the required alignment, mapping lifetime and access-control rules?

Do not infer answers from the Linux driver names alone. Each answer needs matching source evidence or authoritative platform documentation.

## 8. Firmware and security boundary

The GPU may depend on firmware and secure-world services. Their exact responsibilities, versions, interfaces and licensing status are not established here. The design therefore treats firmware interaction as an unresolved platform dependency. It does not specify how to obtain, extract, replace or load firmware.

A future implementation must use only lawfully available, documented components and must preserve memory isolation and platform security boundaries.

## 9. Display and graphics API are separate workstreams

A functioning GPU core would not by itself produce a usable desktop or phone UI. The display controller, DSI panel, modesetting, buffer allocation/sharing, compositor and input stack are independent integration tasks.

Likewise, kernel command submission is not an OpenGL or Vulkan implementation. Mesa's Freedreno and Turnip projects can inform user-space architecture, but adapting them would require separate portability and licensing analysis. No Apple graphics API compatibility is implied.

## 10. Milestones and acceptance criteria

### M0 — Evidence inventory
- Record exact source paths and revisions for KGSL, A6xx support, platform resources and relevant build configuration.
- Mark every fact as confirmed, inferred or unknown.
- **Accept when:** each target-specific statement has a traceable source or is explicitly marked unknown.

### M1 — OS-neutral interface specification
- Define the interfaces in Section 6, ownership rules, error model and state machine.
- **Accept when:** the design can be reviewed without relying on Linux or Apple-private APIs.

### M2 — Mock-only prototype
- Implement a host-side mock of lifecycle, memory-object bookkeeping, queues, fences and fault reporting.
- Add deterministic tests for normal and failure paths.
- **Accept when:** tests run without a phone, device firmware or hardware access.

### M3 — XNU environment feasibility review
- Identify the exact open-source XNU-derived target and its supported driver framework, build environment and licensing constraints.
- **Accept when:** a documented compatibility matrix exists. No hardware driver is implied.

### M4 — Hardware feasibility review
- Resolve platform-resource, memory-isolation, firmware and display dependencies from authoritative documentation.
- **Accept when:** all critical unknowns have evidence-backed answers and a separate safety/security review has approved any future hardware work.

### M5 — Implementation proposal
- Only after M0–M4, write a separately reviewed implementation plan.
- **Accept when:** scope, test strategy, security model and limitations are explicit.

## 11. Risks and open questions

- Exact GPU revision and runtime capabilities are not independently confirmed.
- GPU clocks, power sequencing, reset ownership and interrupt routing need verified platform evidence.
- SMMU configuration, memory sharing and secure-world interactions are unresolved.
- Firmware interface and licensing constraints are unresolved.
- XNU driver-framework availability depends on the selected XNU-derived environment.
- Display and user-space graphics integration may be larger efforts than the kernel-facing abstraction.
- Linux KGSL licensing and code provenance must be reviewed before considering code reuse.

## 12. Current conclusion

The matching Motorola Linux source provides a meaningful reference for an Adreno 6xx research effort, but it does not provide an XNU driver. The appropriate first deliverable is a mockable, OS-neutral design and evidence inventory. **No working driver has been built, no hardware has been initialized, and no compatibility claim is made.**

## References

- [Motorola kernel source, matching Android 12 tag](https://github.com/MotorolaMobilityLLC/kernel-msm/tree/MMI-S2RIS32.32-20-9-9-2-3)
- [Motorola KGSL Kconfig](https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/drivers/gpu/msm/Kconfig)
- [Motorola KGSL Makefile](https://github.com/MotorolaMobilityLLC/kernel-msm/blob/MMI-S2RIS32.32-20-9-9-2-3/drivers/gpu/msm/Makefile)
- [Qualcomm KGSL project](https://github.com/qualcomm-linux/kgsl)
- [Mesa Freedreno documentation](https://docs.mesa3d.org/drivers/freedreno.html)
