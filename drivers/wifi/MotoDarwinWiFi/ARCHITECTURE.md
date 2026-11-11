# MotoDarwinWiFi Architecture

**Phase:** 2 — Architecture  
**Status:** Initial hardware-agnostic design; pending Phase 1 hardware identification  
**Target:** Motorola Moto G60 (XT2135-2, `hanoip`)

## 1. Purpose

Define the software boundaries for a Darwin/XNU-native Wi-Fi implementation. This document is a design proposal, not a claim that a driver exists or that Wi-Fi works.

The design deliberately keeps hardware-specific transport and firmware details unresolved until the exact WLAN device, bus and device-tree description are verified.

## 2. Evidence and assumptions

### Verified project evidence

- The target is identified by the project as Moto G60 XT2135-2 (`hanoip`).
- The public Hanoip Android device-tree configuration references `qca_cld3_wlan.ko`.
- That reference indicates an Android/Linux Qualcomm CLD3 WLAN driver-family dependency.

### Not yet established

- Exact WLAN silicon model and revision.
- Actual host interface/bus and device enumeration mechanism.
- Runtime module binding on this handset.
- Firmware/board-data/calibration format and loading sequence.
- The exact XNU version, available networking interfaces and required compatibility layer.

No component below may assume these unknowns as facts.

## 3. Proposed component boundaries

The implementation should be separated into layers so that hardware discoveries do not leak throughout the networking code.

| Component | Responsibility | Status |
|---|---|---|
| Device discovery / matching | Match the verified hardware identity and transport | Pending hardware evidence |
| Bus transport | Read/write device registers or messages using the confirmed bus | Unspecified |
| Power and reset | Coordinate regulators, clocks, reset and wake signals where required | Unspecified |
| Firmware provider | Locate and validate permitted firmware and board data | Requirements unknown |
| Device core | Own device state, initialization sequencing, command lifecycle and error handling | Design only |
| TX/RX data path | Move network frames between XNU networking and device transport | Design only |
| Interrupt/event handling | Process device events and receive notifications | Transport-dependent |
| Network interface adapter | Expose the device through the networking APIs available in the selected XNU tree | API/version review required |
| Diagnostics | Provide bounded logs and counters for bring-up and testing | Design only |
| Power management | Handle stop, sleep, wake and resume transitions | Hardware-dependent |

## 4. Initialization lifecycle

The intended lifecycle is:

1. XNU discovers a device matching a verified hardware identifier.
2. The driver validates that the expected transport and resources are present.
3. Required power, clock and reset sequencing is performed through supported platform interfaces.
4. The firmware provider supplies only verified, legally redistributable firmware and board data.
5. The device core performs the documented hardware initialization and checks readiness.
6. The network adapter is attached only after initialization succeeds.
7. TX/RX and asynchronous event processing begin after the interface is ready.
8. On stop or failure, queues are stopped, outstanding work is drained, interrupts are quiesced and resources are released in a defined order.

Every hardware-specific step remains a placeholder until supported by device documentation or source evidence.

## 5. TX/RX and command model

The design separates control operations from network data:

- **Control path:** serialized device configuration, initialization commands, status and recovery.
- **Data path:** bounded transmit and receive queues with explicit ownership and lifetime rules.
- **Event path:** interrupt or transport notifications delivered to a safe deferred-work context.

The concrete framing, descriptors, queue count, DMA rules and concurrency model must come from the identified chipset and transport documentation. They must not be guessed from the Android module name.

## 6. Firmware and calibration policy

- Do not copy firmware, board files or calibration blobs from a handset into the repository.
- Identify the exact file names, formats, versions and loading requirements from authoritative source evidence.
- Review license and redistribution terms before packaging any binary.
- Keep firmware acquisition separate from the driver implementation.
- Fail initialization clearly when required firmware or board data is unavailable or invalid.

## 7. XNU integration strategy

Before implementation, inspect the exact XNU source revision used by MotoDarwin and determine which driver and networking abstractions are available in that tree. Do not assume that APIs from another Darwin/macOS release exist in this target.

The network adapter should be a narrow boundary between the device core and the selected XNU networking interface. Hardware transport should not directly own user-facing network configuration.

## 8. Error handling and recovery

The driver design must account for:

- device not present or not matching;
- missing or invalid firmware;
- initialization timeout;
- transport I/O failure;
- transmit queue exhaustion;
- receive-path errors;
- device reset or loss of power;
- stop/suspend during outstanding work.

Recovery must quiesce asynchronous activity before resetting or releasing resources. Avoid unbounded retries and avoid logging sensitive payload data.

## 9. Validation plan

Validation will proceed in layers:

1. Static review of component boundaries and ownership.
2. Compile-only checks against the selected XNU headers and build configuration.
3. Unit tests for hardware-independent state machines and queue logic where feasible.
4. Emulator tests for only those components that can be meaningfully represented without the physical WLAN device.
5. Hardware bring-up only after the exact device and transport are established.

An emulator cannot prove that the Moto G60 Wi-Fi hardware works. A successful build alone is not evidence of connectivity.

## 10. Phase 2 exit criteria

Phase 2 is complete when:

- [x] Component boundaries and responsibilities are documented.
- [x] Initialization, control, data and event paths are outlined.
- [x] Firmware and redistribution policy is documented.
- [ ] Exact XNU revision and networking integration point are confirmed.
- [ ] Exact WLAN hardware and transport are confirmed by Phase 1.
- [ ] Hardware-specific initialization and transport design is reviewed against evidence.

**Current result:** The high-level architecture is documented. Hardware-specific architecture and implementation are blocked on Phase 1 identification and XNU source/API review. No driver source implementation or working Wi-Fi is claimed.
