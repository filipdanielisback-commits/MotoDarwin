# Contributing to MotoDarwin

Thanks for helping with careful, evidence-based operating-system research.

## Before contributing

1. Read the project [README](README.md), [roadmap](ROADMAP.md), and [status](STATUS.md).
2. Keep work small and focused.
3. Cite primary sources for hardware and platform claims.
4. State the exact device variant, source revision, host OS, and toolchain for experiments.
5. Do not describe an untested feature as working.

## Pull request checklist

- [ ] The change has a clear purpose and scope.
- [ ] Hardware and API claims have sources.
- [ ] Third-party code retains its original notices and license.
- [ ] No proprietary firmware, private source, signing keys, credentials, or personal data are included.
- [ ] Build/test steps and results are recorded.
- [ ] Risks and limitations are documented.

## Code and licensing

Do not copy source from a repository without checking its license. XNU has its own upstream license and notices; see [xnu/README.md](xnu/README.md). Never imply that this project owns or can relicense Apple's code.

## Device safety

Do not ask contributors to disable security protections, bypass account locks, or flash unvalidated images. Keep early work in emulators, source analysis, and host-side builds. Any future device experiment needs a reviewed recovery plan and explicit warnings.

## Reporting results

Include:
- device model and regional variant;
- Android build fingerprint and kernel version, where relevant;
- source revision and patch identifiers;
- host OS and compiler/toolchain versions;
- exact test procedure and complete relevant logs;
- expected result, actual result, and limitations.
