# XNU source and build research

MotoDarwin tracks Apple's public XNU source as a kernel research baseline. The upstream source is tracked separately from the MotoDarwin platform code; it is not a complete iOS source release.

## Official upstream

- Apple XNU repository: https://github.com/apple-oss-distributions/xnu
- Pinned source baseline and submodule plan: [UPSTREAM.md](UPSTREAM.md)
- Apple Open Source releases: https://opensource.apple.com/releases/
- iOS 26.2 release notes: https://developer.apple.com/documentation/ios-ipados-release-notes/ios-ipados-26_2-release-notes

## iOS 26.2 source status

Exact iOS 26.2 XNU source mapping is **not verified**. A public XNU snapshot is not automatically the exact iOS 26.2 kernel. Apple does not publish a complete iOS source tree containing all proprietary frameworks, drivers, firmware, signing infrastructure, and services.

## What a public XNU build proves

A successful build proves only that the selected source and build environment produced an artifact for the selected supported target. It does not prove that the artifact is an iOS 26.2 kernel, that it can boot on Moto G60, or that it includes Apple's proprietary platform components.

## Revision selection policy

1. Use the official Apple XNU repository.
2. Record a full commit or tag identifier.
3. Record what the selected revision is known to represent.
4. If the relationship to iOS 26.2 is unknown, explicitly say so.
5. Preserve all upstream copyright notices and license files.

Do not guess a tag based only on a similar version number.

## License

Read the exact `LICENSE` and `APPLE_LICENSE` files from the selected upstream revision before copying, modifying, or redistributing XNU files. Preserve all original notices. MotoDarwin does not relicense XNU.

## Build policy

- Follow the build instructions shipped with the selected upstream revision.
- Record host OS, compiler, SDK, dependencies, environment, and exact commands.
- Keep generated files out of source control unless they are intentional, documented artifacts.
- Do not claim a Moto G60 target exists unless required platform support has actually been implemented and tested.

A successful upstream build is a build-reproduction milestone, not evidence of Moto G60 boot support.