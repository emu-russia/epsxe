#include "pch.h"
void load_bios()
{
  FILE *v0; // eax
  FILE *v1; // esi
  char Buffer[256]; // [esp+4h] [ebp-100h] BYREF

  sprintf(Buffer, "%s", (const char *)bios_name);
  v0 = fopen(Buffer, "rb");
  v1 = v0;
  if ( !v0 )
    fatal_error_with_message_box(" * !Error: PSX BIOS not found [%s]. \n", (const char *)bios_name);
  fread(bios_image, 1u, 0x80000u, v0);
  fclose(v1);
  dbg_print_no_flush(" * ePSXe: PSX BIOS loaded [%s]. \n", (const char *)bios_name);
}
