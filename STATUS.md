# Development status

**Overall:** pre-alpha / documentation and feasibility research.

No Moto G60 XNU port has been built, booted, or validated by this repository at this stage.

| Area | Status | Evidence required before changing status |
|---|---|---|
| Device identification | Research pending | Exact model and software baseline |
| Upstream XNU build | Not started | Reproducible build log and pinned revision |
| Moto G60 boot support | Not started | Reviewed platform design and safe test evidence |
| CPU / ARM64 | Research pending | Supported platform integration and tests |
| Display | Not started | Driver implementation and physical test |
| Touchscreen | Not started | Driver implementation and physical test |
| Audio | Not started | Playback and capture tests |
| GPU | Not started | Documented graphics stack and rendering tests |
| Wi-Fi / Bluetooth | Not started | Connectivity and stability tests |
| Storage / USB | Not started | Read/write and device enumeration tests |
| Battery / charging | Not started | Telemetry and charging tests |
| Camera / sensors | Not started | Per-device functional tests |
| Sleep / wake | Not started | Repeated suspend/resume tests |
| App Store / Apple services | Unsupported / out of scope | Depends on proprietary Apple infrastructure |

## Status vocabulary

- **Not started** — no implementation work.
- **Researching** — collecting sources and evaluating feasibility.
- **In progress** — code or experiments exist but are not validated.
- **Built** — a reproducible artifact exists; not necessarily bootable.
- **Boot-tested** — boot evidence exists for a named target and revision.
- **Working** — acceptance tests pass on the exact named device variant.
- **Blocked** — a documented technical, legal, or hardware blocker exists.

A status change must include links to commits, logs, test steps, device variant, and known limitations.
