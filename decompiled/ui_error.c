#include "pch.h"
void sub_4370D0(char *Format, ...)
{
  DWORD v1; // ecx
  int v2; // ecx
  char *v3; // esi
  char *v4; // esi
  DWORD NumberOfCharsWritten; // [esp+0h] [ebp-4h] BYREF
  va_list va; // [esp+Ch] [ebp+8h] BYREF

  va_start(va, Format);
  NumberOfCharsWritten = v1;
  memcard2_save();
  net_close(NumberOfCharsWritten);
  nullsub_1();
  if ( spu_destroy_cb )
    spu_destroy_cb();
  if ( dword_50C36C == 1 )
    sub_429100();
  gpu_destroy();
  if ( cdrom_deinit_cb )
    cdrom_deinit_cb(v2);
  sub_436F30();
  sub_437040();
  if ( byte_4FF9F0 )
  {
    v3 = (char *)malloc(0x8000u);
    vsprintf(v3, Format, va);
    fprintf(&stru_458A00, "%s", v3);
    if ( console_allocated )
      WriteConsoleA(hConsoleOutput, v3, strlen(v3), &NumberOfCharsWritten, nullptr);
    free(v3);
  }
  else
  {
    v4 = (char *)malloc(0x8000u);
    vsprintf(v4, Format, va);
    printf("%s", v4);
    free(v4);
  }
  sub_437040();
  if ( dword_50AE68 )
    fclose(dword_50AE68);
  nullsub_1();
  free_console();
  exit(0);
}
