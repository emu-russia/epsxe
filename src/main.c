#include "pch.h"

uint8_t cd_savefake_flag = 0xff;

void memset32(void* dst, unsigned int value, unsigned int count)
{
    unsigned int* p = (unsigned int*)dst;
    while (count--)
        *p++ = value;
}

static void epsxe_main_loop_runner()
{
  if ( create_window_flag )
    create_main_window();
  alloc_console();
  dbg_print(" * Running %s emulator version %1.1f.%d. %s\n", "ePSXe", 1.6, 0, &current_dir_path);
  old_auto_ppf_load = ppf_enabled;
  while ( 1 )
  {
    ppf_enabled = 0;
    mem_init_memory_handlers();
    mem_clear_memory();
    loader_load_cheats();
    loader_load_bios();
    cpu_clear_regs();
    select_plugins_backend();
    irq_clear_hw_regs();
    if ( !reset_flag )
    {
      if ( loaded_file_type == 3 || loaded_file_type == 1 )
        cdrom_init_cb();
      loader_cdrom_detect_region();
      if ( loaded_file_type == 1 )
        cdrom_subchannel_read_cb();
      gpu_load_plugin();
      gpu_open_with_input();
      spu_init_cb();
      nullsub_1();
    }
    cdr_reset_controller();
    gte_clear_regs();
    sio_reset_all();
    reopen_console_log();
    nullsub_1();
    gpu_init_performance_counter();
    mdec_init();
    if ( dynarec_enabled == 1 )
      dynarec_init();
    reset_flag = 0;
    ppf_enabled = old_auto_ppf_load;
    ppf_load_patch();
    cpu_load_bios_shell();
    if ( loaded_file_type == 1 || loaded_file_type == 3 )
    {
      if ( fastboot )
        *(uint32_t *)reg_pc = cpu_gpr[31];
    }
    else if ( loaded_file_type == 4 )
    {
      if ( BYTE1(active_mini_cheat_count) )
        loader_load_demo("libps.exe");
      if ( loader_touch_demo_file() )
        loader_load_zip();
    }
    get_tick_count();
    if ( dynarec_enabled )
    {
      if ( dynarec_enabled == 1 )
        dynarec_execute();
      else
        nullsub_1();
    }
    else
    {
      cpu_execute();
    }
  }
}

static void print_usage()
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

static void print_develop_options()
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

static void print_version()
{
  dbg_print_no_flush(" * %s emulator version %1.1f.%d. %s\n", "ePSXe", 1.6, 0, &current_dir_path);
  exit(0);
}

static int parse_command_line_options(int a1, int a2)
{
  int result;
  int v3;
  const char *v4;

  result = a1;
  v3 = 1;
  if ( a1 > 1 )
  {
    do
    {
      if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-bios") )
      {
        loader_set_bios_name(*(const char **)(a2 + 4 * (uint16_t)v3 + 4));
        v3 += 2;
      }
      else
      {
        if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-nosubchan") )
        {
          use_subchannel = 0;
LABEL_146:
          ++v3;
          goto LABEL_147;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-subchan") )
        {
          use_subchannel = 1;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-extsubchanhle") )
        {
          extsubchanhle = 1;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-pslib") )
        {
          load_pslib_flag = 1;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-nocdoverwrite") )
        {
          LOBYTE(pad_key_assignments[0]) = 1;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-nomdectiming") )
        {
          mdectiming = 0;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-mdectiming") )
        {
          mdectiming = 1;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-forcepad") )
        {
          forcepad = 128;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-noforcepad") )
        {
          forcepad = 0;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-forcespu") )
        {
          forcespu = -1;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-noforcespu") )
        {
          forcespu = 0;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-nocd") )
        {
          nocd = 0;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-noaudiocd") )
        {
          sound_use_cdda = 0;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-audiocd") )
        {
          sound_use_cdda = 0;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-nogui") )
        {
          create_window_flag = 0;
          g_bDisableMouse = 0;
          goto LABEL_146;
        }
        if ( !strncmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-p", 3u) )
        {
          cd_speed = atoi(*(const char **)(a2 + 4 * (uint16_t)v3 + 4));
          v3 += 2;
        }
        else
        {
          if ( !strncmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-i", 3u) )
          {
            dynarec_enabled = 0;
            goto LABEL_146;
          }
          if ( !strncmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-v", 3u) )
          {
            print_version();
          }
          else
          {
            if ( !strncmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-f", 3u)
              || !strncmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-fastboot", 3u) )
            {
              fastboot = 1;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-slowboot") )
            {
              fastboot = 0;
              goto LABEL_146;
            }
            if ( !strncmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-fl", 4u) )
            {
              use_performance_counters = 1;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-nosound") )
            {
              sound_enabled = 0;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-sound") )
            {
              sound_enabled = 1;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-nomdec") )
            {
              mdec_disable = 1;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-mdec") )
            {
              mdec_disable = 0;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-nomemcard") )
            {
              memcard_enabled = 0;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-memcard") )
            {
              memcard_enabled = 1;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-xasound") )
            {
              sound_use_xa = 1;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-noxasound") )
            {
              sound_use_xa = 0;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-xaread") )
            {
              xa_read_enable = 1;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-noxaread") )
            {
              xa_read_enable = 0;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-savefake") )
            {
              cd_savefake_flag = 1;
              strcpy(cdrom_fake_filename, *(const char **)(a2 + 4 * (uint16_t)v3 + 4));
              v3 += 2;
            }
            else
            {
              if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-legaia") )
              {
                cdr_randomize_response_flag = 1;
                goto LABEL_146;
              }
              if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-ff9pal") )
              {
                cpu_overclock_setting = 0;
                goto LABEL_146;
              }
              if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-pe2") )
              {
                parasite_eve_cheat = 1;
                goto LABEL_146;
              }
              if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-nocputrick") )
              {
                cpu_overclock_setting = 0;
                goto LABEL_146;
              }
              if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-loadfake") )
              {
                cd_savefake_flag = 0;
                strcpy(cdrom_fake_filename, *(const char **)(a2 + 4 * (uint16_t)v3 + 4));
                v3 += 2;
              }
              else if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-loadppf") )
              {
                strcpy(ppf_filename, *(const char **)(a2 + 4 * (uint16_t)v3 + 4));
                v3 += 2;
              }
              else if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-loadmemc0") )
              {
                strcpy((char *)Memcard1, *(const char **)(a2 + 4 * (uint16_t)v3 + 4));
                v3 += 2;
              }
              else if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-loadmemc1") )
              {
                strcpy((char *)Memcard2, *(const char **)(a2 + 4 * (uint16_t)v3 + 4));
                v3 += 2;
              }
              else if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-loadbin")
                     || !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-loadiso") )
              {
                strcpy(bin_iso_file, *(const char **)(a2 + 4 * (uint16_t)v3 + 4));
                loaded_file_type = 3;
                v3 += 2;
              }
              else if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-loadcheat") )
              {
                strcpy((char *)cheat_file_from_cmdline, *(const char **)(a2 + 4 * (uint16_t)v3 + 4));
                v3 += 2;
              }
              else if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-loadstate") )
              {
                strcpy(state_file_from_cmdline, *(const char **)(a2 + 4 * (uint16_t)v3 + 4));
                v3 += 2;
              }
              else
              {
                if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-ssv0") )
                {
                  save_state_ver = 0;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-nocdstatus") )
                {
                  nocdstatus = 1;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-noauto") )
                {
                  noauto = 1;
                  cpu_overclock_setting = 0;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-mouse") )
                {
                  controller_port_modes[0] = 2;
                  point_device_enabled = 1;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-mouse2") )
                {
                  if ( controller_port_modes[0] == 2 )
                    controller_port_modes[0] = 1;
                  controller_port_modes[1] = 2;
                  point_device_enabled = 1;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-anamouse") )
                {
                  controller_port_modes[0] = 6;
                  pad_analog_mode_flags[0] = 0;
                  point_device_enabled = 1;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-gun") )
                {
                  controller_port_modes[0] = 3;
                  point_device_enabled = 1;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-multitap") )
                {
                  multitap_1 = 1;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-analog") )
                {
                  controller_port_modes[0] = 4;
                  pad_analog_mode_flags[0] = 0;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-analog1") )
                {
                  controller_port_modes[0] = 4;
                  pad_analog_mode_flags[0] = 0;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-analog2") )
                {
                  controller_port_modes[1] = 4;
                  pad2_analog_mode_flag = 0;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-analog3") )
                {
                  controller_port_modes[2] = 4;
                  pad3_analog_mode_flag = 0;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-analog4") )
                {
                  controller_port_modes[3] = 4;
                  pad4_analog_mode_flag = 0;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-noignorecmd") )
                {
                  ignore_cmd = 0;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-nocdinc") )
                {
                  cd_inc = 0;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-noppf") )
                {
                  ppf_enabled = 0;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-ppf") )
                {
                  ppf_enabled = 1;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-nolog") )
                  goto LABEL_146;
                if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-gtrace") )
                {
                  gtrace = 1;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-adjusttiming") )
                {
                  adjust_timing = 1;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-oldtiming") )
                {
                  old_timing = 1;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-noadjusttiming") )
                {
                  adjust_timing = 0;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-disablereportmode") )
                {
                  report_mode_enabled = 0;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-hdev") )
                {
                  print_develop_options();
                }
                else
                {
                  if ( strncmp(*(const char **)(a2 + 4 * (uint16_t)v3), "-h", 2u) )
                  {
                    v4 = *(const char **)(a2 + 4 * (uint16_t)v3);
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
    while ( (uint16_t)v3 < a1 );
  }
  return result;
}

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  unsigned int v4;
  unsigned int v5;
  int v6;
  int v7;
  unsigned int v8;
  CHAR v9;
  CHAR v10;
  CHAR v11;
  CHAR v13;
  int v14;
  uint32_t v15[256];

  v4 = (unsigned int)strlen(lpCmdLine) + 1;
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
    sprintf(default_cdrom_plugin_name, "INTERNAL");
    sprintf(state_file_from_cmdline, "NULL");
    sprintf((char *const)NetPlugin, "DISABLED");
    version_setting = 0;
    dynarec_enabled = 1;
    unused_startup_flag = 0;
    forcepad = 0;
    country_setting = 255;
    loaded_file_type = 1;
    reset_flag = 0;
    video_scanlines = 312;
    cpu_speed_scale = 2171;
    cheat_file_from_cmdline[0] = 0;
    cfg_load_settings();
    parse_command_line_options(v14, (int)v15);
    set_console_log_flush_pending();
    select_cdrom_core();
    dbg_print(" * Running %s emulator version %1.1f.%d. %s\n", "ePSXe", 1.6, 0, &current_dir_path);
    if ( strlen((const char *)cheat_file_from_cmdline) )
      loader_load_cheat_file((char *)cheat_file_from_cmdline);
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


/* Decompiled globals (previously generated in src/_gen) */
unsigned char memcard_enabled = 0x1;
unsigned char current_dir_path = 0x0;
unsigned char load_pslib_flag;
unsigned char default_cdrom_plugin_name[0x400];
unsigned char cheat_file_from_cmdline[0x400];
unsigned char cpu_overclock_setting = 0x1;
unsigned int unused_startup_flag;
unsigned int dynarec_enabled;
unsigned char extsubchanhle;
unsigned char fastboot = 0x1;
unsigned int forcepad;
unsigned char forcespu = 0x0;
unsigned char gtrace;
unsigned char ignore_cmd = 0x1;
unsigned int loaded_file_type;
unsigned int mdectiming = 0x1;
unsigned char nocd = 0x1;
unsigned char old_auto_ppf_load;
unsigned int reset_flag;
unsigned char xa_read_enable = 0x1;
