#include "pch.h"
void __noreturn epsxe_main_loop_runner()
{
  if ( create_window_flag )
    create_main_window();
  alloc_console();
  dbg_print(" * Running %s emulator version %1.1f.%d. %s\n", "ePSXe", 1.6, 0, &byte_45B8CC);
  old_auto_ppf_load = ppf_enabled;
  while ( 1 )
  {
    ppf_enabled = 0;
    mem_init_memory_handlers();
    mem_clear_memory();
    loader_load_cheats();
    loader_load_bios();
    clear_cpu_regs();
    select_plugins_backend();
    clear_hw_regs();
    if ( !reset_flag )
    {
      if ( loaded_file_type == 3 || loaded_file_type == 1 )
        cdrom_init_cb();
      loader_cdrom_detect_region();
      if ( loaded_file_type == 1 )
        cdrom_subchannel_read_cb();
      gpu_load_plugin();
      gpu_sub_42E3A0();
      spu_init_cb();
      nullsub_1();
    }
    sub_42C830();
    gte_clear_regs();
    sio_reset_all();
    reopen_console_log();
    nullsub_1();
    gpu_init_performance_counter();
    mdec_init();
    if ( dword_50C36C == 1 )
      dynarec_init();
    reset_flag = 0;
    ppf_enabled = old_auto_ppf_load;
    ppf_load_patch();
    sub_42B1E0();
    if ( loaded_file_type == 1 || loaded_file_type == 3 )
    {
      if ( fastboot )
        *(_DWORD *)reg_pc = cpu_gpr[31];
    }
    else if ( loaded_file_type == 4 )
    {
      if ( BYTE1(dword_4F831C) )
        loader_load_demo("libps.exe");
      if ( loader_touch_demo_file() )
        loader_load_zip();
    }
    get_tick_count();
    if ( dword_50C36C )
    {
      if ( dword_50C36C == 1 )
        dynarec_execute();
      else
        nullsub_1();
    }
    else
    {
      sub_42B2A0();
    }
  }
}

void print_usage()
{
  printf(" %s v.%1.1f.%d emulator by ePSXe team. Copyright 2000/2002. \n\n", "ePSXe", 1.6, 0);
  printf("      epsxe [options] [PS-EXE] \n");
  printf("      options: \n\n");
  printf("        -pslib                     -   Load libpsx.exe.\n");
  printf("        -nocd                      -   Disable CDR emulation.\n");
  printf("        -sound/-nosound            -   Enable/Disable sound.\n");
  printf("        -xasound/-noxasound        -   Enable/Disable XA sound.\n");
  printf("        -audiocd/noaudiocd         -   Enable/Disable CDDA audio.\n");
  printf("        -forcespu/-noforcespu      -   Enable/Disable SPU irq always ON.\n");
  printf("        -nosubchan/-subchan        -   Enable/Disable subchannel support.\n");
  printf("        -forcepad/-noforcepad      -   Enable/Disable SIO irq always ON.\n");
  printf("        -memcard/-nomemcard        -   Enable/Disable memcard emulation.\n");
  printf("        -mdec/-nomdec              -   Enable/Disable MDEC emulation.\n");
  printf("        -mdectiming/-nomdectiming  -   Enable/Disable MDEC accurate timing.\n");
  printf("        -adjusttiming              -   On the fly re-adjust timing.\n");
  printf("    [Press a key to continue] \n");
  _getch();
  printf("        -oldtiming                 -   Use pre-1.5.1 timing. \n");
  printf("        -fastboot/slowboot         -   Fast/Slow boot cdrom (psx logo).\n");
  printf("        -nogui                     -   Disable internal GUI.\n");
  printf("        -loadiso <file>            -   Load iso file. (Cdrwin/Clonecd)\n");
  printf("        -loadcheat <file>          -   Load internal cheat file.\n");
  printf("        -loadppf <file>            -   Load ppf file.\n");
  printf("        -ppf/-noppf                -   Enable/Disable ppf patches.\n");
  printf("        -loadmemc0 <file>          -   Map file to memcard 0.\n");
  printf("        -loadmemc1 <file>          -   Map file to memcard 1.\n");
  printf("        -ssv0                      -   Save sstate version v.0\n");
  printf("        -gun                       -   Enable namco gun emulation\n");
  printf("        -mouse                     -   Enable mouse emulation.\n");
  printf("        -analogN                   -   Enable dualshock emulation in pad N.\n");
  printf("        -p <num>                   -   Mem access penalty (d.5).\n");
  printf("        -pe2                       -   Parasite eve 2 cheat.\n");
  printf("        -help                      -   Where are you now? ;-)\n");
  exit(0);
}

void print_develop_options()
{
  printf("      develop options: \n\n");
  printf("        -nocdstatus                -   No return cdstatus.\n");
  printf("        -noauto                    -   Disable autoconf/patch.\n");
  printf("        -noignorecmd               -   No Ignore cdrom commands.\n");
  printf("        -frc1                      -   Faster rootcounter1.\n");
  printf("        -nocputrick                -   Disable a old cpu trick.\n");
  printf("        -extsubchanhle             -   Enable subchannel hle (extplug).\n");
  exit(0);
}

void print_version()
{
  dbg_print_no_flush(" * %s emulator version %1.1f.%d. %s\n", "ePSXe", 1.6, 0, &byte_45B8CC);
  exit(0);
}

int __cdecl parse_command_line_options(int a1, int a2)
{
  int result; // eax
  int v3; // ebx
  const char *v4; // [esp-10h] [ebp-14h]

  result = a1;
  v3 = 1;
  if ( a1 > 1 )
  {
    do
    {
      if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-bios") )
      {
        loader_set_bios_name(*(const char **)(a2 + 4 * (unsigned __int16)v3 + 4));
        v3 += 2;
      }
      else
      {
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-nosubchan") )
        {
          use_subchannel = 0;
LABEL_146:
          ++v3;
          goto LABEL_147;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-subchan") )
        {
          use_subchannel = 1;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-extsubchanhle") )
        {
          extsubchanhle = 1;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-pslib") )
        {
          BYTE1(dword_4F831C) = 1;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-nocdoverwrite") )
        {
          LOBYTE(word_455FA8[0]) = 1;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-nomdectiming") )
        {
          mdectiming = 0;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-mdectiming") )
        {
          mdectiming = 1;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-forcepad") )
        {
          forcepad = 128;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-noforcepad") )
        {
          forcepad = 0;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-forcespu") )
        {
          forcespu = -1;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-noforcespu") )
        {
          forcespu = 0;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-nocd") )
        {
          nocd = 0;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-noaudiocd") )
        {
          sound_use_cdda = 0;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-audiocd") )
        {
          sound_use_cdda = 0;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-nogui") )
        {
          create_window_flag = 0;
          g_bDisableMouse = 0;
          goto LABEL_146;
        }
        if ( !strncmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-p", 3u) )
        {
          LOBYTE(byte_455945) = atoi(*(const char **)(a2 + 4 * (unsigned __int16)v3 + 4));
          v3 += 2;
        }
        else
        {
          if ( !strncmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-i", 3u) )
          {
            dword_50C36C = 0;
            goto LABEL_146;
          }
          if ( !strncmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-v", 3u) )
          {
            print_version();
          }
          else
          {
            if ( !strncmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-f", 3u)
              || !strncmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-fastboot", 3u) )
            {
              fastboot = 1;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-slowboot") )
            {
              fastboot = 0;
              goto LABEL_146;
            }
            if ( !strncmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-fl", 4u) )
            {
              use_performance_counters = 1;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-nosound") )
            {
              sound_enabled = 0;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-sound") )
            {
              sound_enabled = 1;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-nomdec") )
            {
              mdec_disable = 1;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-mdec") )
            {
              mdec_disable = 0;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-nomemcard") )
            {
              byte_4557A8 = 0;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-memcard") )
            {
              byte_4557A8 = 1;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-xasound") )
            {
              sound_use_xa = 1;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-noxasound") )
            {
              sound_use_xa = 0;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-xaread") )
            {
              xa_read_enable = 1;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-noxaread") )
            {
              xa_read_enable = 0;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-savefake") )
            {
              cd_savefake_flag = 1;
              strcpy(cdrom_fake_filename, *(const char **)(a2 + 4 * (unsigned __int16)v3 + 4));
              v3 += 2;
            }
            else
            {
              if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-legaia") )
              {
                byte_4FD881 = 1;
                goto LABEL_146;
              }
              if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-ff9pal") )
              {
                BYTE1(byte_455945) = 0;
                goto LABEL_146;
              }
              if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-pe2") )
              {
                parasite_eve_cheat = 1;
                goto LABEL_146;
              }
              if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-nocputrick") )
              {
                BYTE1(byte_455945) = 0;
                goto LABEL_146;
              }
              if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-loadfake") )
              {
                cd_savefake_flag = 0;
                strcpy(cdrom_fake_filename, *(const char **)(a2 + 4 * (unsigned __int16)v3 + 4));
                v3 += 2;
              }
              else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-loadppf") )
              {
                strcpy(ppf_filename, *(const char **)(a2 + 4 * (unsigned __int16)v3 + 4));
                v3 += 2;
              }
              else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-loadmemc0") )
              {
                strcpy((char *)Memcard1, *(const char **)(a2 + 4 * (unsigned __int16)v3 + 4));
                v3 += 2;
              }
              else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-loadmemc1") )
              {
                strcpy((char *)Memcard2, *(const char **)(a2 + 4 * (unsigned __int16)v3 + 4));
                v3 += 2;
              }
              else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-loadbin")
                     || !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-loadiso") )
              {
                strcpy(bin_iso_file, *(const char **)(a2 + 4 * (unsigned __int16)v3 + 4));
                loaded_file_type = 3;
                v3 += 2;
              }
              else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-loadcheat") )
              {
                strcpy(&cheat_file_from_cmdline, *(const char **)(a2 + 4 * (unsigned __int16)v3 + 4));
                v3 += 2;
              }
              else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-loadstate") )
              {
                strcpy(state_file_from_cmdline, *(const char **)(a2 + 4 * (unsigned __int16)v3 + 4));
                v3 += 2;
              }
              else
              {
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-ssv0") )
                {
                  save_state_ver = 0;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-nocdstatus") )
                {
                  nocdstatus = 1;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-noauto") )
                {
                  noauto = 1;
                  BYTE1(byte_455945) = 0;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-mouse") )
                {
                  dword_456048[0] = 2;
                  point_device_enabled = 1;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-mouse2") )
                {
                  if ( dword_456048[0] == 2 )
                    dword_456048[0] = 1;
                  dword_456048[1] = 2;
                  point_device_enabled = 1;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-anamouse") )
                {
                  dword_456048[0] = 6;
                  dword_4FD8E0[0] = 0;
                  point_device_enabled = 1;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-gun") )
                {
                  dword_456048[0] = 3;
                  point_device_enabled = 1;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-multitap") )
                {
                  multitap_1 = 1;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-analog") )
                {
                  dword_456048[0] = 4;
                  dword_4FD8E0[0] = 0;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-analog1") )
                {
                  dword_456048[0] = 4;
                  dword_4FD8E0[0] = 0;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-analog2") )
                {
                  dword_456048[1] = 4;
                  dword_4FD8E4 = 0;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-analog3") )
                {
                  dword_456048[2] = 4;
                  dword_4FD8E8 = 0;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-analog4") )
                {
                  dword_456048[3] = 4;
                  dword_4FD8EC = 0;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-noignorecmd") )
                {
                  byte_455FA3 = 0;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-nocdinc") )
                {
                  byte_455FA4 = 0;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-noppf") )
                {
                  ppf_enabled = 0;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-ppf") )
                {
                  ppf_enabled = 1;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-nolog") )
                  goto LABEL_146;
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-gtrace") )
                {
                  gtrace = 1;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-adjusttiming") )
                {
                  adjust_timing = 1;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-oldtiming") )
                {
                  old_timing = 1;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-noadjusttiming") )
                {
                  adjust_timing = 0;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-disablereportmode") )
                {
                  byte_455FA5 = 0;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-hdev") )
                {
                  print_develop_options();
                }
                else
                {
                  if ( strncmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-h", 2u) )
                  {
                    v4 = *(const char **)(a2 + 4 * (unsigned __int16)v3);
                    if ( *v4 == '-' )
                      fatal_error_with_message_box(" * ePSXe error: %s param incorrect \n", v4);
                    loader_set_filename(v4);
                    loaded_file_type = 4;
                    goto LABEL_146;
                  }
                  print_usage();
                }
              }
            }
          }
        }
      }
LABEL_147:
      result = a1;
    }
    while ( (unsigned __int16)v3 < a1 );
  }
  return result;
}

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
    dword_50C36C = 1;
    dword_50C370 = 0;
    forcepad = 0;
    country_setting = 255;
    loaded_file_type = 1;
    reset_flag = 0;
    dword_45593C = 312;
    cpu_speed_scale = 2171;
    cheat_file_from_cmdline = 0;
    cfg_load_settings();
    parse_command_line_options(v14, (int)v15);
    sub_437030();
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

