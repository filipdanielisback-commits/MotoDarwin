# XNU source and build research

MotoDarwin intends to study and reproduce builds of Apple's publicly available XNU source. This directory currently contains project notes only; upstream XNU has not been imported or modified here.

## Upstream source

- Apple OSS XNU: https://github.com/apple-oss-distributions/xnu
- Apple Open Source: https://opensource.apple.com/

Choose a specific upstream tag or commit before building. Record the exact revision and preserve every upstream license, copyright notice, and accompanying file.

## License

XNU is made available under the Apple Public Source License (APSL). The exact license text and notices must be taken from the selected upstream revision. Read and comply with those terms before copying, modifying, or redistributing XNU files. This repository does not relicense XNU.

## Build policy

- Follow the build instructions shipped with the selected upstream revision.
- Record host OS, compiler, SDK, dependencies, environment, and exact commands.
- Keep generated files out of source control unless they are intentional, documented artifacts.
- Do not claim a Moto G60 target exists unless the required platform support has actually been implemented and tested.

A successful upstream build is a build-reproduction milestone, not evidence of Moto G60 boot support.
