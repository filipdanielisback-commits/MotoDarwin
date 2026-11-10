# MotoDarwin XNULoader — design proposal

**Status: IN DEVELOPMENT — design only. No executable loader, bootable image, or device support is available.**

## Purpose

MotoDarwin needs an independently designed boot-selection interface and, eventually, a loader appropriate to a verified device platform. This document records the intended user-facing concept and the engineering gates that must be met before any executable artifact can be called a loader.

This is not a fork of HakiOS. HakiOS is an architectural reference only. MotoDarwin must have its own implementation, source history, interface design, tests, and documented attribution for any external interfaces or libraries it later uses.

## Proposed boot menu

The first menu concept has two visible entries:

| Menu entry | Display state | Action state |
|---|---|---|
| **Boot into iOS 26** | IN DEVELOPMENT | Disabled — no iOS 26 payload or compatible Moto G60 XNU platform exists |
| **Boot into Stock Original Android** | IN DEVELOPMENT | Disabled in this prototype — stock Android handoff has not been implemented or validated |

The labels are placeholders for the project's long-term research direction. They do not imply that iOS 26 can run on this phone, that an iOS image is available, or that Android can currently be selected through MotoDarwin.

Until a verified platform implementation exists, the safest behavior for any future experimental menu is to expose no active boot action and leave the device's existing startup path untouched.

## Architecture boundaries

The project separates these concerns:

1. **Firmware/platform layer:** device-specific firmware and platform initialization. Moto G60 compatibility is unknown.
2. **Loader application:** a future independently written component that would validate a payload description, present status, and coordinate a handoff only after platform support is proven.
3. **Payload format:** a documented, versioned description of kernel and supporting data. No format is implemented here.
4. **XNU kernel:** a separate deliverable; the current repository does not contain a working Moto G60 kernel port.
5. **Android compatibility:** preserving the original Android startup path is a requirement, not an assumed feature.

## HakiOS research notes

The public HakiOS project describes a UEFI application called XNULoader, a separate UEFI/platform layer, and a payload containing kernel-related data. Its public release notes describe a device-specific boot artifact for its own supported target. Its UEFI documentation distinguishes QEMU validation from phone-specific validation.

MotoDarwin will not copy HakiOS source, branding, menu assets, device configuration, or implementation. Any future use of third-party code must be separately reviewed for license compatibility and attribution. General concepts such as separating firmware, loader, payload, and kernel are not a substitute for original implementation.

References:
- https://github.com/oosexgang/hakios-xnu-kernel
- https://github.com/oosexgang/hakios-uefi
- https://github.com/oosexgang/hakios-xnu-kernel/releases
- https://hackios-web.vercel.app/en/docs/uefi-boot

## Readiness gates

A future implementation proposal must first establish:

- A documented, supported development target and a safe emulator-based test environment.
- A complete understanding of the target platform's firmware interfaces from authoritative sources.
- A reviewed payload specification and explicit validation/error behavior.
- A mock menu whose entries cannot trigger real boot actions.
- Tests proving invalid or missing payloads fail closed.
- A documented recovery and rollback plan reviewed by qualified maintainers.
- Independent review of licenses, security assumptions, and device compatibility claims.

No device-specific boot procedure, firmware replacement, or storage modification is part of this design document.

## Release policy

Do not publish a file with an `.img` extension or call any artifact bootable unless it has been built from reviewed source for a named target, its format and contents are verified, and its functionality has been validated in an appropriate test environment. A design document, mock UI, or placeholder file must never be represented as a boot image.

## Current project status

- [x] Record the proposed menu labels and their development status.
- [x] Record the independent-design and attribution policy.
- [x] Record the separation between firmware, loader, payload, kernel, and Android.
- [ ] Implement a mock-only menu for a desktop/emulator preview.
- [ ] Define and review a platform-neutral payload specification.
- [ ] Establish a validated emulator test target.
- [ ] Complete a Moto G60 platform feasibility review.
- [ ] Consider any hardware-specific implementation only after all prior gates pass.

**Current result:** documentation only. There is no XNULoader binary, no bootable `.img`, no GitHub release artifact, and no working iOS 26 or Android boot-menu action.
