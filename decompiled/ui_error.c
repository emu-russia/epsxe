#include "pch.h"
void __noreturn ui_error(char *Format, ...)
{
  DWORD v1; // ecx
  int v2; // ecx
  char *v3; // esi
  char *v4; // esi
  DWORD NumberOfCharsWritten; // [esp+0h] [ebp-4h] BYREF
  va_list ArgList; // [esp+Ch] [ebp+8h] BYREF

  va_start(ArgList, Format);
  NumberOfCharsWritten = v1;
  sio_memcard_both_save();
  net_close();
  nullsub_1();
  if ( spu_destroy_cb )
    spu_destroy_cb(NumberOfCharsWritten);
  if ( dynarec_enabled == 1 )
    dynarec_deinit();
  gpu_destroy();
  if ( cdrom_deinit_cb )
    cdrom_deinit_cb(v2);
  ppf_free();
  check_and_clear_console_log_flush_pending();
  if ( console_log_flush_pending )
  {
    v3 = (char *)malloc(0x8000u);
    vsprintf(v3, Format, ArgList);
    fprintf(&console_out_file, "%s", v3);
    if ( console_allocated )
      WriteConsoleA(hConsoleOutput, v3, strlen(v3), &NumberOfCharsWritten, nullptr);
    free(v3);
  }
  else
  {
    v4 = (char *)malloc(0x8000u);
    vsprintf(v4, Format, ArgList);
    printf("%s", v4);
    free(v4);
  }
  check_and_clear_console_log_flush_pending();
  if ( dword_50AE68 )
    fclose(dword_50AE68);
  nullsub_1();
  free_console();
  exit(0);
}
