# Architecture and feasibility notes

## Layers under investigation

A hypothetical Darwin-based system on this device would need much more than an XNU source build:

1. **Boot chain:** platform firmware, bootloader interfaces, image format, verified-boot policy, and a safe development path.
2. **Kernel platform layer:** ARM64 CPU setup, memory management, exception handling, interrupt controller, timers, clocks, and power management.
3. **Device drivers:** storage, display, touch, audio, GPU, radios, sensors, cameras, USB, and battery/charging.
4. **User space:** process and service environment, system libraries, launch/service management, and graphics/audio frameworks.
5. **Security and updates:** code signing, secure boot assumptions, permissions, update and recovery mechanisms.
6. **Applications and services:** app compatibility is a separate problem from kernel boot.

## XNU scope

XNU combines Mach, BSD, and I/O Kit components. The public source is valuable for research, but platform support is not universal. A successful build for an existing Apple target does not imply compatibility with Qualcomm mobile hardware.

## Recommended engineering approach

- Pin one upstream XNU revision; do not begin by mixing arbitrary branches.
- First reproduce a build for a target supported by that revision.
- Keep local patches isolated and explain each patch.
- Prefer emulation or a documented development board for early kernel experiments.
- Maintain a source-of-truth hardware inventory with links to device-tree, kernel, and vendor documentation.
- Treat each peripheral as a separate driver and validation project.

## Apple platform and service boundary

Open-source XNU is not the full iOS operating system. Proprietary frameworks, firmware, platform services, signing, activation, and App Store infrastructure are not supplied by XNU. This repository does not claim to reproduce them.
