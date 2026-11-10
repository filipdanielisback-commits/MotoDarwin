#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/SimpleTextIn.h>

#define COLOR(R, G, B) { (B), (G), (R), 0 }

STATIC EFI_GRAPHICS_OUTPUT_PROTOCOL *mGop = NULL;

STATIC
EFI_STATUS
FillRect (
  IN UINTN X,
  IN UINTN Y,
  IN UINTN Width,
  IN UINTN Height,
  IN EFI_GRAPHICS_OUTPUT_BLT_PIXEL Color
  )
{
  if (mGop == NULL || Width == 0 || Height == 0) {
    return EFI_UNSUPPORTED;
  }

  return mGop->Blt (
                 mGop,
                 &Color,
                 EfiBltVideoFill,
                 0,
                 0,
                 X,
                 Y,
                 Width,
                 Height,
                 0
                 );
}

STATIC
VOID
DrawScreen (
  VOID
  )
{
  EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;
  UINTN Width;
  UINTN Height;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL Background = COLOR (12, 20, 35);
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL Panel      = COLOR (27, 42, 64);
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL Accent     = COLOR (48, 115, 170);
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL Disabled   = COLOR (54, 65, 82);

  if (mGop == NULL || mGop->Mode == NULL || mGop->Mode->Info == NULL) {
    return;
  }

  Info = mGop->Mode->Info;
  Width = Info->HorizontalResolution;
  Height = Info->VerticalResolution;

  FillRect (0, 0, Width, Height, Background);
  FillRect (Width / 8, Height / 8, (Width * 3) / 4, (Height * 3) / 4, Panel);
  FillRect (Width / 8, Height / 8, (Width * 3) / 4, 5, Accent);

  FillRect (Width / 5, Height / 2 - 70, (Width * 3) / 5, 48, Disabled);
  FillRect (Width / 5, Height / 2 - 10, (Width * 3) / 5, 48, Disabled);
  FillRect (Width / 5, Height / 2 + 50, (Width * 3) / 5, 40, Accent);
}

EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS Status;
  EFI_INPUT_KEY Key;

  Status = gBS->LocateProtocol (
                  &gEfiGraphicsOutputProtocolGuid,
                  NULL,
                  (VOID **)&mGop
                  );

  if (EFI_ERROR (Status)) {
    Print (L"MotoDarwin UEFI: GOP unavailable; using text fallback.\r\n");
  } else {
    DrawScreen ();
  }

  gST->ConOut->ClearScreen (gST->ConOut);
  Print (L"\r\n");
  Print (L"  MotoDarwin UEFI  |  ARM64 research build\r\n");
  Print (L"  ----------------------------------------\r\n\r\n");
  Print (L"  [ IN DEVELOPMENT ]  Boot into iOS 26\r\n");
  Print (L"  Disabled: no compatible XNU/iOS payload.\r\n\r\n");
  Print (L"  [ IN DEVELOPMENT ]  Boot into Stock Original Android\r\n");
  Print (L"  Disabled: no validated Android handoff.\r\n\r\n");
  Print (L"  UEFI Information: view-only\r\n");
  Print (L"  Graphics: %s\r\n", (mGop != NULL) ? L"GOP detected" : L"text fallback");
  Print (L"\r\n  Press ESC to return to the UEFI environment.\r\n");
  Print (L"  No operating-system boot action is enabled.\r\n");

  while (TRUE) {
    Status = gBS->WaitForEvent (1, &gST->ConIn->WaitForKey, NULL);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    Status = gST->ConIn->ReadKeyStroke (gST->ConIn, &Key);
    if (!EFI_ERROR (Status) && Key.ScanCode == SCAN_ESC) {
      break;
    }
  }

  return EFI_SUCCESS;
}
