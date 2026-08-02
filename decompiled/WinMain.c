#include "pch.h"
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  unsigned int v4; // kr04_4
  unsigned int v5; // edi
  int v6; // ebp
  int v7; // eax
  unsigned int v8; // eax
  CHAR v9; // cl
  CHAR v10; // cl
  CHAR v11; // bl
  CHAR v13; // [esp+Fh] [ebp-405h]
  int v14; // [esp+10h] [ebp-404h]
  _DWORD v15[256]; // [esp+14h] [ebp-400h] BYREF

  v4 = strlen(lpCmdLine) + 1;
  v14 = 1;
  v5 = v4 - 1;
  v6 = 0;
  v13 = 0;
  v7 = 256;
  do
  {
    --v7;
    v15[0] = 0;
  }
  while ( v7 );
  v8 = 0;
  if ( v4 == 1 )
    goto LABEL_16;
  if ( *lpCmdLine == 32 )
  {
    while ( v8 < v5 )
    {
      v9 = lpCmdLine[++v8];
      if ( v9 != 32 )
        goto LABEL_7;
    }
LABEL_16:
    sprintf(ppf_filename, "NULL");
    sprintf((char *const)Memcard1, "NULL");
    sprintf((char *const)Memcard2, "NULL");
    sprintf(byte_8B2580, "INTERNAL");
    sprintf(state_file_from_cmdline, "NULL");
    sprintf((char *const)NetPlugin, "DISABLED");
    version_setting = 0;
    dynarec_enabled = 1;
    dword_50C370 = 0;
    forcepad = 0;
    country_setting = 255;
    loaded_file_type = 1;
    reset_flag = 0;
    video_scanlines = 312;
    cpu_speed_scale = 2171;
    cheat_file_from_cmdline = 0;
    cfg_load_settings();
    parse_command_line_options(v14, (int)v15);
    set_console_log_flush_pending();
    select_cdrom_core();
    dbg_print(" * Running %s emulator version %1.1f.%d. %s\n", "ePSXe", 1.6, 0, &byte_45B8CC);
    if ( strlen(&cheat_file_from_cmdline) )
      loader_load_cheat_file(&cheat_file_from_cmdline);
    epsxe_main_loop_runner();
  }
LABEL_7:
  if ( v8 >= v5 )
    goto LABEL_16;
  if ( lpCmdLine[v8] == 34 )
  {
    ++v8;
    v6 = 1;
  }
  v15[1] = &lpCmdLine[v8];
  v14 = 2;
  if ( v8 >= v5 )
    goto LABEL_16;
  while ( 1 )
  {
    v10 = lpCmdLine[v8];
    if ( v6 == 1 )
    {
      if ( v10 == 34 && v13 != 92 )
        goto LABEL_21;
    }
    else if ( v10 == 32 && v13 != 92 )
    {
LABEL_21:
      v6 = 0;
      lpCmdLine[v8] = 0;
      if ( ++v8 < v5 )
      {
        if ( lpCmdLine[v8] == 32 )
        {
          while ( v8 < v5 )
          {
            v11 = lpCmdLine[++v8];
            if ( v11 != 32 )
              goto LABEL_25;
          }
        }
        else
        {
LABEL_25:
          if ( v8 < v5 )
          {
            if ( lpCmdLine[v8] == 34 )
            {
              ++v8;
              v6 = 1;
            }
            v15[v14] = &lpCmdLine[v8];
            v10 = lpCmdLine[v8];
            if ( v8 < v5 )
              ++v14;
          }
        }
      }
      goto LABEL_15;
    }
    ++v8;
LABEL_15:
    v13 = v10;
    if ( v8 >= v5 )
      goto LABEL_16;
  }
}
