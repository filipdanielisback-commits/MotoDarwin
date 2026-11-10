[Defines]
  DSC_SPECIFICATION              = 0x0001001B
  PLATFORM_NAME                  = MotoDarwin
  PLATFORM_GUID                  = 5A6C8D10-7B2E-4F91-9C30-2D6E8A4B1F20
  PLATFORM_VERSION               = 0.1
  OUTPUT_DIRECTORY               = Build/MotoDarwin
  SUPPORTED_ARCHITECTURES        = AARCH64
  BUILD_TARGETS                  = DEBUG|RELEASE

[Packages]
  MdePkg/MdePkg.dec

[LibraryClasses]
  UefiApplicationEntryPoint|MdePkg/Library/UefiApplicationEntryPoint/UefiApplicationEntryPoint.inf
  UefiLib|MdePkg/Library/UefiLib/UefiLib.inf
  UefiBootServicesTableLib|MdePkg/Library/UefiBootServicesTableLib/UefiBootServicesTableLib.inf
  DebugLib|MdePkg/Library/BaseDebugLibNull/BaseDebugLibNull.inf

[Components]
  uefi/MotoDarwinUefi.inf
