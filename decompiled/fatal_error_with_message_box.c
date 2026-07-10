#include "pch.h"
void __noreturn fatal_error_with_message_box(char *Format, ...)
{
  char *v1; // esi
  int v2; // ecx
  va_list va; // [esp+8h] [ebp+8h] BYREF

  va_start(va, Format);
  memcard2_save();
  net_close();
  nullsub_1();
  if ( spu_destroy_cb )
    spu_destroy_cb();
  if ( dword_50C36C == 1 )
    sub_429100();
  v1 = (char *)malloc(0x8000u);
  vsprintf(v1, Format, va);
  fprintf(&stru_458A00, "%s", v1);
  MessageBoxA(nullptr, v1, aErrorRunningEp, 0x10u);
  free(v1);
  gpu_destroy();
  if ( cdrom_deinit_cb )
    cdrom_deinit_cb(v2);
  sub_436F30();
  sub_437040();
  if ( dword_50AE68 )
    fclose(dword_50AE68);
  free_console();
  exit(1);
}
