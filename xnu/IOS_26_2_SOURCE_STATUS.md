# XNU source and build research

MotoDarwin studies Apple's publicly available XNU source as one component of a much larger operating system. The public source repository is not a complete iOS source release.

## Official upstream sources

- Apple OSS XNU: https://github.com/apple-oss-distributions/xnu
- Apple Open Source releases: https://opensource.apple.com/releases/
- iOS 26.2 release notes: https://developer.apple.com/documentation/ios-ipados-release-notes/ios-ipados-26_2-release-notes

Apple's release portal says operating-system and developer-tool source distributions are provided through their respective GitHub pages. It does not mean every component of iOS is published.

## iOS 26.2 source status

Do not label a public XNU snapshot as "the exact iOS 26.2 kernel" unless Apple publishes a verifiable mapping between that source revision and iOS 26.2. A similarly numbered macOS XNU snapshot is not proof of an exact iOS build match.

The iOS 26.2 release notes describe the SDK and app-facing changes; they are not the source code for the iOS kernel or the complete operating system.

For this project, the current status is:

- Exact iOS 26.2 XNU source revision: **not verified**.
- Complete iOS 26.2 source tree: **not publicly provided as a complete source release**.
- Public XNU source: available for independent kernel research.
- Moto G60 XNU platform support: **not implemented**.

## What a public XNU build proves

A successful build for an upstream-supported target proves only that the selected source and build environment produced an artifact for that target. It does not prove that the artifact is an iOS 26.2 kernel, that it can boot on Moto G60, or that it includes Apple's proprietary drivers, firmware, frameworks, signing, and services.

## Revision selection policy

1. Inspect the official Apple XNU repository and its published source history.
2. Choose a concrete tag or commit and record its full identifier.
3. Record why that revision was selected and what Apple platform/release it is known to correspond to.
4. If its exact iOS 26.2 relationship is unknown, explicitly record "relationship unverified".
5. Preserve all upstream copyright notices and license files.

Do not guess a tag based only on a similar version number.

## License

XNU is distributed under the Apple Public Source License (APSL) for covered portions, alongside other notices where applicable. The exact license text and notices must be taken from the selected upstream revision. Read and comply with those terms before copying, modifying, or redistributing XNU files. This repository does not relicense XNU.

## Build policy

- Follow the build instructions shipped with the selected upstream revision.
- Record host OS, compiler, SDK, dependencies, environment, and exact commands.
- Keep generated files out of source control unless they are intentional, documented artifacts.
- Do not claim a Moto G60 target exists unless the required platform support has actually been implemented and tested.

A successful upstream build is a build-reproduction milestone, not evidence of Moto G60 boot support.
