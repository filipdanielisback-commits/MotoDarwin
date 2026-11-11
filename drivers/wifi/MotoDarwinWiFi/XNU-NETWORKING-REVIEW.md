# MotoDarwinWiFi — Public XNU Networking Review

**Purpose:** First-pass review of public XNU networking and I/O Kit sources  
**Status:** Research only; target XNU revision and networking ABI are not yet pinned

## 1. Sources reviewed

- [Apple open-source XNU repository](https://github.com/apple-oss-distributions/xnu)
- [XNU BSD networking source directory](https://github.com/apple-oss-distributions/xnu/tree/main/bsd/net)
- [Apple IONetworkingFamily network-controller header](https://github.com/apple-oss-distributions/IONetworkingFamily/blob/main/IOEthernetController.h)
- [Apple I/O Kit Network Family reference](https://developer.apple.com/library/archive/documentation/DeviceDrivers/Conceptual/IOKitFundamentals/Families_Ref/Families_Ref.html)

The XNU repository describes XNU as a hybrid kernel containing Mach, FreeBSD-derived components and IOKit. Its public source includes BSD networking code and IOKit support. The I/O Kit Network Family documentation describes a controller/interface split for network devices.

## 2. Relevant architectural layers

For MotoDarwinWiFi, the public source suggests these conceptual layers:

1. **Hardware/transport driver:** owns the actual WLAN device, bus operations, power sequencing, interrupts and firmware interaction. This cannot be designed until the exact chip and bus are identified.
2. **Device core:** manages hardware state, command lifecycle, event processing and TX/RX queues without exposing hardware details to higher layers.
3. **Network-facing adapter:** connects the device core to the networking interfaces available in the exact MotoDarwin XNU build.
4. **Userland services/configuration:** handles scan, authentication, association and network configuration only where the required operating-system services and APIs exist.

The controller/interface split in I/O Kit is a useful design concept, but it does not establish that a particular legacy network-controller API is suitable for this project.

## 3. Important Wi-Fi-specific limitation

Ethernet-style networking interfaces alone do not implement 802.11 Wi-Fi behavior. A real Wi-Fi solution also needs the appropriate 802.11 control plane: scanning, authentication, association, key management, regulatory handling, link state and related event/control requests.

Apple's Wi-Fi-specific IO80211 interfaces and implementation are not established by the public XNU BSD networking tree reviewed here. Their availability and compatibility must not be assumed. The project must identify a lawful, technically compatible Wi-Fi integration path for its selected Darwin/XNU environment before committing to a concrete adapter API.

## 4. Current design decision

Keep the MotoDarwinWiFi architecture split into:

- hardware transport (TBD);
- firmware/configuration provider (TBD);
- hardware-independent device core;
- Wi-Fi control-plane interface (TBD pending API review);
- network data-path adapter (TBD pending selected XNU revision).

Do not implement a generic Ethernet controller and label it Wi-Fi. Do not copy private Apple headers or rely on undocumented symbols without a compatible, reviewed target environment.

## 5. Required follow-up investigation

- Pin the exact XNU source revision and build configuration used by MotoDarwin.
- Inspect the corresponding IOKit and BSD network headers in that revision.
- Determine which networking APIs are actually built/exported for the target.
- Establish whether a compatible 802.11 control-plane interface exists in the chosen environment.
- Identify the exact WLAN chip and transport before designing hardware-specific code.
- Record any third-party code license and firmware redistribution requirements before reuse.

## 6. Conclusion

Public XNU source provides useful foundations for IOKit and BSD networking, but this review does not identify a complete, ready-to-use public Wi-Fi driver interface for MotoDarwin. The next implementation step should therefore remain a hardware-independent interface/design review, not a guessed hardware driver.

**No Wi-Fi driver implementation or working Wi-Fi support is claimed.**
