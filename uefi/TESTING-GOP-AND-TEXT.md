# MotoDarwin UEFI — GOP and text fallback test plan

**Status: test plan written; tests have not yet been executed.**

## Test goals

Validate the initial UEFI application's two console paths in an AArch64 UEFI emulator:

1. Graphics Output Protocol (GOP) is present and can provide a valid graphics mode.
2. GOP is absent or unavailable and the application remains usable through UEFI text output.

These are emulator application tests only. They do not validate Moto G60 firmware or hardware compatibility.

## Preconditions

- Pin an EDK II revision and record the compiler/toolchain version.
- Build the application as an AArch64 UEFI application using the project's INF.
- Use a disposable emulator configuration with AArch64 UEFI firmware.
- Keep the test environment isolated from physical devices and physical storage.
- Record the exact command lines, firmware build, emulator version and application hash in the test report.

## GOP test cases

| ID | Setup | Expected result |
|---|---|---|
| GOP-01 | Emulator exposes GOP | Protocol discovery succeeds |
| GOP-02 | GOP mode information is valid | Resolution and pixel format are read without invalid access |
| GOP-03 | GOP supports BLT | Test rectangles render within screen bounds |
| GOP-04 | Small or unusual resolution | Drawing is skipped safely if layout constraints are not met |
| GOP-05 | GOP BLT returns an error | Application reports/handles failure without hanging |
| GOP-06 | Exit key pressed | Application returns cleanly to the firmware environment |

## Text fallback test cases

| ID | Setup | Expected result |
|---|---|---|
| TXT-01 | GOP protocol unavailable | Text menu is displayed |
| TXT-02 | Text input available | Application waits for input |
| TXT-03 | ESC pressed | Application returns EFI_SUCCESS |
| TXT-04 | Input protocol returns an error | Application exits or reports the error without an infinite wait |
| TXT-05 | Menu displayed | Both OS entries remain explicitly disabled |

## Required code-quality checks

- Check every UEFI protocol lookup result.
- Check the GOP mode pointer and mode information before reading fields.
- Check GOP BLT return statuses.
- Avoid unsigned-coordinate underflow for small display modes.
- Do not clear or redraw the text console after painting the GOP test screen.
- Ensure a GOP failure selects text fallback rather than treating graphics as available.
- Keep both operating-system menu entries non-actionable.
- Avoid boot services or protocol use after the UEFI application returns.

## Test report template

Record one row per test:

| Field | Value |
|---|---|
| Commit | |
| EDK II revision | |
| Compiler/toolchain | |
| Emulator and version | |
| Firmware image/version | |
| GOP test result | NOT RUN |
| Text fallback result | NOT RUN |
| Build result | NOT RUN |
| Logs/artifact hashes | |

A test is **PASS** only after the behavior is observed in the emulator and evidence is recorded. Source inspection alone is not a pass.

## Scope boundary

Passing these tests proves only that the UEFI application behaves as expected in the recorded emulator configuration. It does not prove that the Moto G60 firmware implements UEFI, that an XNU payload exists, or that any Moto G60 hardware driver works.
