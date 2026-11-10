# Live ADB device audit

**Inspection date:** 2026-11-10  
**Target:** Motorola Moto G60 XT2135-2 (`hanoip`)  
**Method:** ordinary Android Debug Bridge (ADB), read-only commands; handset remained booted into Android.

This records owner-provided command output. It is runtime evidence for this handset, not a complete hardware inventory and not proof of a working Darwin/XNU port.

## Confirmed ADB observations

| Property / command | Reported value | Interpretation / limitation |
|---|---|---|
| `ro.product.device`, `ro.product.board` | `hanoip` | Runtime product identity |
| `ro.boot.hardware.sku` | `XT2135-2` | Runtime SKU matches target variant |
| `ro.board.platform` | `sm6150` | Qualcomm platform identifier used by this build |
| `ro.boot.hardware`, `ro.hardware` | `qcom` | Qualcomm hardware labels |
| `ro.boot.hardware.revision`, `ro.boot.revision` | `pvt` | Runtime revision string; does not map directly to EVT1/DVT1/DVT2 overlay labels |
| `ro.boot.dtbo_idx` | `1` | Bootloader-reported zero-based DTBO entry index; not an overlay filename or board revision |
| `ro.hardware.nfc_nci` | `pn54x` | Android NFC-NCI property label; insufficient to identify exact physical controller SKU |
| `ro.hardware.sensors` | `hanoip` | Vendor sensor implementation label |
| `ro.hardware.egl`, `ro.hardware.vulkan` | `adreno` | Android graphics vendor labels |
| `uname -a` | `Linux localhost 4.14.190-perf+ #1 SMP PREEMPT Fri Oct 27 13:02:24 CDT 2023 aarch64` | Running ARM64 Linux kernel version/build string |
| `ro.build.fingerprint` | `motorola/hanoip_retailenq/hanoip:12/S2RIS32.32-20-9-9-2-3/f495e7-429de:user/release-keys` | Android 12 build identity and build type |

The Android build `S2RIS32.32-20-9-9-2-3` matches the Motorola kernel source tag `MMI-S2RIS32.32-20-9-9-2-3` already used as the source baseline. The running kernel version `4.14.190-perf+` matches the source tag's Linux 4.14.190 baseline and `-perf` local version. The trailing `+` does not establish the exact source commit or local changes.

## Live device-tree access

- `/proc/device-tree` exists as a symbolic link to `/sys/firmware/devicetree/base`.
- The live device-tree root directory could be listed.
- Root entries included `qcom,board-id`, `qcom,msm-id`, `qcom,msm-name`, `chosen`, `hw`, and `utags`.
- Reading `/proc/device-tree/model`, `/proc/device-tree/qcom,board-id`, and `/proc/device-tree/qcom,msm-id` as the ordinary ADB shell user returned `Permission denied`.

No root access, permission changes, partition reads, reboot, bootloader operation, or flashing was performed.

## DTBO index interpretation

Android's [device-tree overlay verification documentation](https://source.android.com/docs/core/architecture/dto/compile) defines `androidboot.dtbo_idx` as the zero-based index or indices of DTBO entries selected by the bootloader and applied to the base device tree. The runtime property `ro.boot.dtbo_idx` is populated from that boot argument.

Therefore `ro.boot.dtbo_idx=1` is useful evidence that the bootloader reported DTBO entry index 1. It does **not** mean “DVT1,” and cannot be mapped to the Hanoip source overlay names without the exact stock DTBO image and entry ordering. The source audit lists EVT1, DVT1, and DVT2 overlay files; the selected overlay for this handset remains **unconfirmed**.

The runtime revision string `pvt` must not be conflated with the DTS overlay labels. It does not independently identify which source overlay was selected.

## Project impact

1. The matching Motorola Android 12 kernel tag is strongly corroborated by the handset's build fingerprint and running kernel version.
2. Runtime identity confirms `hanoip` and SKU `XT2135-2`.
3. Runtime properties add `sm6150`, `pvt`, DTBO index `1`, and NFC property label `pn54x` to the evidence record.
4. The exact DTBO overlay and exact NFC controller part remain unresolved.
5. No Darwin/XNU driver or boot support is demonstrated by these observations.

## Reproduction commands

These are read-only inspection commands used during this audit:

```cmd
adb devices
adb shell getprop | findstr /i "ro.boot.hardware ro.boot.board ro.boot.revision ro.boot.dtbo ro.product.board ro.product.device ro.board.platform ro.hardware"
adb shell getprop ro.boot.dtbo_idx
adb shell ls -ld /proc/device-tree /sys/firmware/devicetree/base
adb shell ls /proc/device-tree
adb shell uname -a
adb shell getprop ro.build.fingerprint
```

Some device-tree properties are restricted to privileged processes on this Android build. Do not change permissions or attempt privilege escalation for this research record.