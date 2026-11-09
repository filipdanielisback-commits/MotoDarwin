# Apple XNU upstream source

## Official upstream

- Repository: https://github.com/apple-oss-distributions/xnu
- Apple Open Source releases: https://opensource.apple.com/releases/
- Repository description: XNU is the kernel used as part of Darwin for macOS and iOS. It combines Mach, BSD components, and IOKit.

## Pinned research snapshot

- Commit: `f6217f891ac0bb64f3d375211650a4c1ff8ca1ea`
- Upstream commit title: `xnu-12377.1.9`
- Commit URL: https://github.com/apple-oss-distributions/xnu/commit/f6217f891ac0bb64f3d375211650a4c1ff8ca1ea
- Selection purpose: reproducible public XNU source baseline for code study.
- Relationship to iOS 26.2: **not verified**. Do not describe this as the exact iOS 26.2 kernel.

This is a real public Apple XNU source snapshot, not a fake or recreated iOS tree. XNU is only the kernel component; it is not the complete iOS operating system.

## How the full source should be included

Keep Apple's source as an upstream Git submodule rather than copying the entire repository into MotoDarwin. This preserves the original history and makes the selected revision explicit.

From a fresh clone of MotoDarwin, the intended setup is:

```sh
git submodule add https://github.com/apple-oss-distributions/xnu xnu/upstream
git -C xnu/upstream checkout f6217f891ac0bb64f3d375211650a4c1ff8ca1ea
git add .gitmodules xnu/upstream
git commit -m "Track pinned Apple XNU upstream source"
```

Until that submodule commit is made, this file records the official source location and pinned commit; the full XNU source is not vendored in this repository.

## Licensing and scope

Read the `LICENSE` and `APPLE_LICENSE` files from the selected upstream revision before modifying or redistributing source. Preserve Apple and third-party notices. MotoDarwin does not relicense XNU.

Public XNU source does not include the complete iOS userland, all proprietary frameworks, device firmware, Apple signing infrastructure, or Apple services. A successful XNU build does not make a phone run iOS.