# Driver research

Each driver must have its own source references, implementation plan, and test evidence. The presence of a directory or a research note does not mean a driver exists.

| Subsystem | Questions to answer |
|---|---|
| Display | Panel, DSI host, modes, backlight, display controller |
| Touch | Controller, bus, interrupts, firmware |
| GPU | Adreno 618 interface, firmware, memory management, graphics APIs |
| Audio | Codec, DSP, routing, microphone and speaker paths |
| Wi-Fi | Chipset, firmware, regulatory behavior, network stack integration |
| Bluetooth | Controller, firmware, transport, profiles |
| Storage | UFS/eMMC variant, controller, filesystem support |
| Battery | Fuel gauge, PMIC, charging and thermal telemetry |
| Camera | Sensors, ISP, calibration, camera pipeline |
| Sensors | Accelerometer, gyroscope, proximity, ambient light |
| USB | Controller, Type-C / OTG behavior, charging interactions |
| Power | Clocks, regulators, suspend, wake sources, thermal limits |

For every claimed working driver, include exact device variant, code revision, test procedure, logs, and known limitations.
