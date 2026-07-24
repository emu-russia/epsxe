#include "pch.h"
void __noreturn fatal_error_with_message_box(char *Format, ...)
{
  char *v1; // esi
  int v2; // ecx
  va_list ArgList; // [esp+8h] [ebp+8h] BYREF

  va_start(ArgList, Format);
  sio_memcard_both_save();
  net_close();
  nullsub_1();
  if ( spu_destroy_cb )
    spu_destroy_cb();
  if ( dword_50C36C == 1 )
    dynarec_deinit();
  v1 = (char *)malloc(0x8000u);
  vsprintf(v1, Format, ArgList);
  fprintf(&stru_458A00, "%s", v1);
  MessageBoxA(nullptr, v1, "Error running ePSXe", 0x10u);
  free(v1);
  gpu_destroy();
  if ( cdrom_deinit_cb )
    cdrom_deinit_cb(v2);
  ppf_free();
  sub_437040();
  if ( dword_50AE68 )
    fclose(dword_50AE68);
  free_console();
  exit(1);
}
