# MotoDarwinWiFi

**Project:** MotoDarwinWiFi  
**Parent project:** MotoDarwin  
**Target device:** Motorola Moto G60 (XT2135-2, `hanoip`)  
**Status:** Architecture and hardware research only

MotoDarwinWiFi is the planned Darwin/XNU-native Wi-Fi driver effort for MotoDarwin. This directory establishes the project name and records its initial scope. It does not yet contain a functional driver.

## Goals

- Identify the exact WLAN silicon and hardware revision in the target device.
- Confirm the hardware transport/bus and device-tree integration.
- Document firmware, board-data, calibration and power-sequencing requirements.
- Design a driver architecture appropriate for the XNU version and networking interfaces used by MotoDarwin.
- Implement and validate components incrementally, with evidence for each capability.

## Non-goals and constraints

- Android/Linux `.ko` modules are not directly loadable by XNU.
- The Android configuration reference to `qca_cld3_wlan.ko` is a driver-family clue, not proof of the exact chip or runtime driver binding.
- No proprietary firmware or calibration data will be copied into this repository without confirming its source and redistribution rights.
- No working Wi-Fi support is claimed at this stage.

## Initial status

- [x] Project name established: **MotoDarwinWiFi**.
- [ ] Exact WLAN hardware identified.
- [ ] Bus/interface confirmed.
- [ ] Firmware and calibration requirements reviewed.
- [ ] XNU driver architecture designed.
- [ ] Driver implementation started.
- [ ] Build and validation completed.
- [ ] Device-level Wi-Fi tests passed.

See [the Wi-Fi hardware investigation](../../../docs/research/wifi-hardware-investigation.md) for current evidence and open questions.
