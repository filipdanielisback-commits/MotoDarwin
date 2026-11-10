# MotoDarwin UEFI GUI — emulator-first foundation

**Status: IN DEVELOPMENT. This is a source/design milestone, not a built EFI executable.**

## Objective

Create an original ARM64 UEFI application with a graphical boot-selection screen, developed and tested in an emulator before any device-specific work is considered.

The initial GUI is informational only. It must not load kernels, modify boot variables, write storage, chainload another operating system, or attempt to alter the Moto G60 boot process.

## Initial screen

Title: **MotoDarwin UEFI**

Menu entries:
- **Boot into iOS 26** — IN DEVELOPMENT; disabled; no compatible payload exists.
- **Boot into Stock Original Android** — IN DEVELOPMENT; disabled; no validated Android handoff exists.
- **UEFI Information** — view-only system information.
- **Restart / Exit** — only after the emulator behavior is tested and specified.

The two operating-system entries are roadmap labels, not functional buttons. The interface must make disabled state obvious and must never imply that either operating system is bootable.

## Implementation target

- Architecture: AArch64 / ARM64 UEFI application.
- Development environment: EDK II, using its documented UEFI application model.
- Graphics: UEFI Graphics Output Protocol (GOP), with a text-mode fallback.
- Input: UEFI Simple Text Input initially; richer pointer support is optional and later.
- First execution target: emulator only, with a documented virtual machine configuration.
- Device target: none at this stage. Moto G60 firmware compatibility is unknown.

## Module boundaries

- `App/`: application entry point and lifecycle.
- `Ui/`: drawing, layout, focus, and disabled menu state.
- `Input/`: keyboard navigation and input abstraction.
- `Platform/`: read-only firmware and protocol discovery.
- `Payload/`: future format specification only; no payload execution in the first milestone.
- `Tests/`: host-side logic tests and emulator test cases.

Keep UI and menu-state logic independent from UEFI calls so it can be tested on a desktop. All UEFI protocol access must be checked for errors. If GOP is unavailable, fall back to text output. If input is unavailable, display the menu without pretending it is interactive.

## Milestones

### U0 — GUI specification
- [x] Define menu entries and disabled status.
- [x] Require graphical output with text fallback.
- [x] Restrict first target to emulation.
- [ ] Choose and pin an EDK II revision and document reproducible build environment.

### U1 — GUI application
- [ ] Implement GOP-based rendering and text fallback.
- [ ] Implement keyboard focus movement for informational UI.
- [ ] Keep OS boot entries disabled and non-actionable.
- [ ] Add error handling for missing protocols and unsupported resolutions.

### U2 — Emulator validation
- [ ] Build an AArch64 EFI application using the pinned EDK II toolchain.
- [ ] Run in a documented AArch64 UEFI emulator environment.
- [ ] Verify rendering, fallback, input, and clean exit.
- [ ] Record logs and exact toolchain revisions.

### U3 — Payload format design
- [ ] Specify metadata, architecture, versioning, integrity checks, and failure behavior.
- [ ] Use a harmless test fixture only.
- [ ] Do not execute or chainload an OS payload in this milestone.

### U4 — Driver feasibility
- [ ] Inventory platform interfaces and required drivers from authoritative sources.
- [ ] Keep UEFI drivers distinct from XNU kernel drivers.
- [ ] Use mock implementations for tests.
- [ ] Do not claim Moto G60 hardware support without verified evidence.

### U5 — Platform feasibility review
- [ ] Determine whether the Moto G60 firmware exposes a compatible UEFI environment.
- [ ] Review platform security, compatibility, and recovery constraints.
- [ ] Publish a separate reviewed proposal before any device-specific implementation is considered.

## Driver scope clarification

UEFI drivers and XNU drivers serve different environments. UEFI drivers provide services during firmware/application execution; XNU drivers operate after the kernel starts. A UEFI graphics protocol does not provide an Adreno 618 XNU driver, and a UEFI menu does not establish display, touch, GPU, storage, Wi-Fi, audio, or sensor support in XNU.

## Safety and release policy

- Emulator-only artifacts must be clearly named and documented as emulator artifacts.
- No phone-flashable image is produced by this project at this stage.
- Do not unlock, replace, or modify the phone's boot chain as part of these milestones.
- Do not describe a build as working unless the exact artifact and test environment are recorded.
- Never publish a placeholder file with an `.img` extension as a bootable image.

## References

- [EDK II project](https://github.com/tianocore/edk2)
- [UEFI Forum specifications](https://uefi.org/specifications)
- [UEFI Graphics Output Protocol overview](https://uefi.org/specs/UEFI/2.10/12_Protocols_Console_Support.html)
- [MotoDarwin XNULoader design](../bootloader/XNULOADER-DESIGN.md)
- [MotoDarwin GPU design](../docs/xnu-gpu-driver-design.md)

**Current result:** design foundation only. No EFI executable, firmware image, bootable `.img`, device driver, or phone support is being claimed.
