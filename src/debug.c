#include "pch.h"

char alloc_console()
{
  HANDLE StdHandle; // eax

  LOBYTE(StdHandle) = console_allocated;
  if ( console_allocated )
  {
    AllocConsole();
    SetConsoleTitleA("ePSXe - Enhanced PSX emulator");
    StdHandle = GetStdHandle(0xFFFFFFF5);
    hConsoleOutput = StdHandle;
  }
  return (char)StdHandle;
}

char free_console()
{
  char result; // al

  result = console_allocated;
  if ( console_allocated )
    return FreeConsole();
  return result;
}

DWORD get_tick_count()
{
  DWORD result; // eax

  result = GetTickCount();
  last_tick_count = result;
  return result;
}

void sub_437030()
{
  byte_4FF9F0 = 1;
}

char sub_437040()
{
  char result; // al

  result = byte_4FF9F0;
  if ( byte_4FF9F0 )
    byte_4FF9F0 = 0;
  return result;
}

void dbg_print_no_flush(char *Format, ...)
{
  char *v1; // esi
  DWORD NumberOfCharsWritten; // [esp+4h] [ebp-4h] BYREF
  va_list ArgList; // [esp+10h] [ebp+8h] BYREF

  va_start(ArgList, Format);
  v1 = (char *)malloc(0x8000u);
  vsprintf(v1, Format, ArgList);
  fprintf(&stru_458A00, "%s", v1);
  if ( console_allocated )
    WriteConsoleA(hConsoleOutput, v1, strlen(v1), &NumberOfCharsWritten, nullptr);
  free(v1);
}

void ui_error(char *Format, ...)
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
  if ( dword_50C36C == 1 )
    dynarec_deinit();
  gpu_destroy();
  if ( cdrom_deinit_cb )
    cdrom_deinit_cb(v2);
  ppf_free();
  sub_437040();
  if ( byte_4FF9F0 )
  {
    v3 = (char *)malloc(0x8000u);
    vsprintf(v3, Format, ArgList);
    fprintf(&stru_458A00, "%s", v3);
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
  sub_437040();
  if ( dword_50AE68 )
    fclose(dword_50AE68);
  nullsub_1();
  free_console();
  exit(0);
}

void fatal_error_with_message_box(char *Format, ...)
{
  char *v1; // esi
  int v2; // ecx
  va_list ArgList; // [esp+8h] [ebp+8h] BYREF

  va_start(ArgList, Format);
  memcard2_save();
  net_close();
  nullsub_1();
  if ( spu_destroy_cb )
    spu_destroy_cb();
  if ( dword_50C36C == 1 )
    sub_429100();
  v1 = (char *)malloc(0x8000u);
  vsprintf(v1, Format, ArgList);
  fprintf(&stru_458A00, "%s", v1);
  MessageBoxA(nullptr, v1, "Error running ePSXe", 0x10u);
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

int dbg_print(const char *Format, ...)
{
  char *v1; // esi
  DWORD NumberOfCharsWritten; // [esp+4h] [ebp-4h] BYREF
  va_list ArgList; // [esp+10h] [ebp+8h] BYREF

  va_start(ArgList, Format);
  v1 = (char *)malloc(0x8000u);
  vsprintf(v1, Format, ArgList);
  fprintf(&stru_458A00, "%s", v1);
  if ( console_allocated )
    WriteConsoleA(hConsoleOutput, v1, strlen(v1), &NumberOfCharsWritten, nullptr);
  free(v1);
  return fflush(&stru_458A00);
}

char reopen_console_log()
{
  FILE *v0; // eax

  LOBYTE(v0) = byte_4FF9F2;
  if ( byte_4FF9F2 )
  {
    LOBYTE(v0) = (_BYTE)console_log_handle;
    if ( !console_log_handle )
    {
      v0 = fopen(aConsoleLog, aW);
      console_log_handle = v0;
    }
  }
  return (char)v0;
}

void dump_log(FILE *Stream, char *Format, ...)
{
  char *v2; // esi
  va_list ArgList; // [esp+10h] [ebp+Ch] BYREF

  va_start(ArgList, Format);
  v2 = (char *)malloc(0x8000u);
  vsprintf(v2, Format, ArgList);
  if ( Stream && byte_4FF9F2 )
    fprintf(Stream, "%s", v2);
  free(v2);
}