#include "pch.h"

/* Decompiled globals (previously generated in src/_gen) */
unsigned char memcard_enabled = 0x1;
unsigned char current_dir_path = 0x0;
static unsigned char load_pslib_flag;
static unsigned char default_cdrom_plugin_name[0x400];
static unsigned char cheat_file_from_cmdline[0x400];
unsigned char cpu_overclock_setting = 0x1;
static unsigned int unused_startup_flag;
unsigned int dynarec_enabled;
unsigned char extsubchanhle;
unsigned char fastboot = 0x1;
unsigned int forcepad;
unsigned char forcespu = 0x0;
unsigned char gtrace;
static unsigned char ignore_cmd = 0x1;
unsigned int loaded_file_type;
unsigned int mdectiming = 0x1;
unsigned char nocd = 0x1;
static unsigned char old_auto_ppf_load;
unsigned int reset_flag;
unsigned char xa_read_enable = 0x1;


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

static int parse_command_line_options(int argc, int argv)
{
  int arg_index;
  const char *arg;

  arg_index = 1;
  if ( argc > 1 )
  {
    do
    {
      if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-bios") )
      {
        loader_set_bios_name(*(const char **)(argv + 4 * (uint16_t)arg_index + 4));
        arg_index += 2;
      }
      else
      {
        if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-nosubchan") )
        {
          use_subchannel = 0;
          arg_index++; continue;
        }
        if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-subchan") )
        {
          use_subchannel = 1;
          arg_index++; continue;
        }
        if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-extsubchanhle") )
        {
          extsubchanhle = 1;
          arg_index++; continue;
        }
        if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-pslib") )
        {
          load_pslib_flag = 1;
          arg_index++; continue;
        }
        if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-nocdoverwrite") )
        {
          LOBYTE(pad_key_assignments[0]) = 1;
          arg_index++; continue;
        }
        if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-nomdectiming") )
        {
          mdectiming = 0;
          arg_index++; continue;
        }
        if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-mdectiming") )
        {
          mdectiming = 1;
          arg_index++; continue;
        }
        if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-forcepad") )
        {
          forcepad = 128;
          arg_index++; continue;
        }
        if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-noforcepad") )
        {
          forcepad = 0;
          arg_index++; continue;
        }
        if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-forcespu") )
        {
          forcespu = -1;
          arg_index++; continue;
        }
        if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-noforcespu") )
        {
          forcespu = 0;
          arg_index++; continue;
        }
        if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-nocd") )
        {
          nocd = 0;
          arg_index++; continue;
        }
        if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-noaudiocd") )
        {
          sound_use_cdda = 0;
          arg_index++; continue;
        }
        if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-audiocd") )
        {
          sound_use_cdda = 0;
          arg_index++; continue;
        }
        if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-nogui") )
        {
          create_window_flag = 0;
          g_bDisableMouse = 0;
          arg_index++; continue;
        }
        if ( !strncmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-p", 3u) )
        {
          cd_speed = atoi(*(const char **)(argv + 4 * (uint16_t)arg_index + 4));
          arg_index += 2;
        }
        else
        {
          if ( !strncmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-i", 3u) )
          {
            dynarec_enabled = 0;
            arg_index++; continue;
          }
          if ( !strncmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-v", 3u) )
          {
            print_version();
          }
          else
          {
            if ( !strncmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-f", 3u)
              || !strncmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-fastboot", 3u) )
            {
              fastboot = 1;
              arg_index++; continue;
            }
            if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-slowboot") )
            {
              fastboot = 0;
              arg_index++; continue;
            }
            if ( !strncmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-fl", 4u) )
            {
              use_performance_counters = 1;
              arg_index++; continue;
            }
            if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-nosound") )
            {
              sound_enabled = 0;
              arg_index++; continue;
            }
            if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-sound") )
            {
              sound_enabled = 1;
              arg_index++; continue;
            }
            if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-nomdec") )
            {
              mdec_disable = 1;
              arg_index++; continue;
            }
            if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-mdec") )
            {
              mdec_disable = 0;
              arg_index++; continue;
            }
            if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-nomemcard") )
            {
              memcard_enabled = 0;
              arg_index++; continue;
            }
            if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-memcard") )
            {
              memcard_enabled = 1;
              arg_index++; continue;
            }
            if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-xasound") )
            {
              sound_use_xa = 1;
              arg_index++; continue;
            }
            if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-noxasound") )
            {
              sound_use_xa = 0;
              arg_index++; continue;
            }
            if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-xaread") )
            {
              xa_read_enable = 1;
              arg_index++; continue;
            }
            if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-noxaread") )
            {
              xa_read_enable = 0;
              arg_index++; continue;
            }
            if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-savefake") )
            {
              cd_savefake_flag = 1;
              strcpy(cdrom_fake_filename, *(const char **)(argv + 4 * (uint16_t)arg_index + 4));
              arg_index += 2;
            }
            else
            {
              if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-legaia") )
              {
                cdr_randomize_response_flag = 1;
                arg_index++; continue;
              }
              if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-ff9pal") )
              {
                cpu_overclock_setting = 0;
                arg_index++; continue;
              }
              if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-pe2") )
              {
                parasite_eve_cheat = 1;
                arg_index++; continue;
              }
              if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-nocputrick") )
              {
                cpu_overclock_setting = 0;
                arg_index++; continue;
              }
              if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-loadfake") )
              {
                cd_savefake_flag = 0;
                strcpy(cdrom_fake_filename, *(const char **)(argv + 4 * (uint16_t)arg_index + 4));
                arg_index += 2;
              }
              else if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-loadppf") )
              {
                strcpy(ppf_filename, *(const char **)(argv + 4 * (uint16_t)arg_index + 4));
                arg_index += 2;
              }
              else if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-loadmemc0") )
              {
                strcpy((char *)Memcard1, *(const char **)(argv + 4 * (uint16_t)arg_index + 4));
                arg_index += 2;
              }
              else if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-loadmemc1") )
              {
                strcpy((char *)Memcard2, *(const char **)(argv + 4 * (uint16_t)arg_index + 4));
                arg_index += 2;
              }
              else if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-loadbin")
                     || !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-loadiso") )
              {
                strcpy(bin_iso_file, *(const char **)(argv + 4 * (uint16_t)arg_index + 4));
                loaded_file_type = 3;
                arg_index += 2;
              }
              else if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-loadcheat") )
              {
                strcpy((char *)cheat_file_from_cmdline, *(const char **)(argv + 4 * (uint16_t)arg_index + 4));
                arg_index += 2;
              }
              else if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-loadstate") )
              {
                strcpy(state_file_from_cmdline, *(const char **)(argv + 4 * (uint16_t)arg_index + 4));
                arg_index += 2;
              }
              else
              {
                if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-ssv0") )
                {
                  save_state_ver = 0;
                  arg_index++; continue;
                }
                if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-nocdstatus") )
                {
                  nocdstatus = 1;
                  arg_index++; continue;
                }
                if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-noauto") )
                {
                  noauto = 1;
                  cpu_overclock_setting = 0;
                  arg_index++; continue;
                }
                if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-mouse") )
                {
                  controller_port_modes[0] = 2;
                  point_device_enabled = 1;
                  arg_index++; continue;
                }
                if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-mouse2") )
                {
                  if ( controller_port_modes[0] == 2 )
                    controller_port_modes[0] = 1;
                  controller_port_modes[1] = 2;
                  point_device_enabled = 1;
                  arg_index++; continue;
                }
                if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-anamouse") )
                {
                  controller_port_modes[0] = 6;
                  pad_analog_mode_flags[0] = 0;
                  point_device_enabled = 1;
                  arg_index++; continue;
                }
                if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-gun") )
                {
                  controller_port_modes[0] = 3;
                  point_device_enabled = 1;
                  arg_index++; continue;
                }
                if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-multitap") )
                {
                  multitap_1 = 1;
                  arg_index++; continue;
                }
                if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-analog") )
                {
                  controller_port_modes[0] = 4;
                  pad_analog_mode_flags[0] = 0;
                  arg_index++; continue;
                }
                if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-analog1") )
                {
                  controller_port_modes[0] = 4;
                  pad_analog_mode_flags[0] = 0;
                  arg_index++; continue;
                }
                if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-analog2") )
                {
                  controller_port_modes[1] = 4;
                  pad2_analog_mode_flag = 0;
                  arg_index++; continue;
                }
                if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-analog3") )
                {
                  controller_port_modes[2] = 4;
                  pad3_analog_mode_flag = 0;
                  arg_index++; continue;
                }
                if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-analog4") )
                {
                  controller_port_modes[3] = 4;
                  pad4_analog_mode_flag = 0;
                  arg_index++; continue;
                }
                if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-noignorecmd") )
                {
                  ignore_cmd = 0;
                  arg_index++; continue;
                }
                if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-nocdinc") )
                {
                  cd_inc = 0;
                  arg_index++; continue;
                }
                if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-noppf") )
                {
                  ppf_enabled = 0;
                  arg_index++; continue;
                }
                if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-ppf") )
                {
                  ppf_enabled = 1;
                  arg_index++; continue;
                }
                if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-nolog") )
                  arg_index++; continue;
                if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-gtrace") )
                {
                  gtrace = 1;
                  arg_index++; continue;
                }
                if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-adjusttiming") )
                {
                  adjust_timing = 1;
                  arg_index++; continue;
                }
                if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-oldtiming") )
                {
                  old_timing = 1;
                  arg_index++; continue;
                }
                if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-noadjusttiming") )
                {
                  adjust_timing = 0;
                  arg_index++; continue;
                }
                if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-disablereportmode") )
                {
                  report_mode_enabled = 0;
                  arg_index++; continue;
                }
                if ( !strcmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-hdev") )
                {
                  print_develop_options();
                }
                else
                {
                  if ( strncmp(*(const char **)(argv + 4 * (uint16_t)arg_index), "-h", 2u) )
                  {
                    arg = *(const char **)(argv + 4 * (uint16_t)arg_index);
                    if ( *arg == '-' )
                      fatal_error_with_message_box(" * ePSXe error: %s param incorrect \n", arg);
                    loader_set_filename(arg);
                    loaded_file_type = 4;
                    arg_index++; continue;
                  }
                  print_usage();
                }
              }
            }
          }
        }
      }
    }
    while ( (uint16_t)arg_index < argc );
  }
  return argc;
}

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  unsigned int cmdline_len;
  unsigned int cmdline_end;
  int in_quotes;
  int count;
  unsigned int pos;
  CHAR ch;
  CHAR cur_ch;
  CHAR skip_ch;
  CHAR prev_ch;
  int argc;
  uint32_t argv[256];

#ifdef _DEBUG
  install_crash_handler();
#endif

  cmdline_len = (unsigned int)strlen(lpCmdLine) + 1;
  argc = 1;
  cmdline_end = cmdline_len - 1;
  in_quotes = 0;
  prev_ch = 0;
  count = 256;
  do
  {
    --count;
    argv[0] = 0;
  }
  while ( count );
  pos = 0;
  if ( cmdline_len == 1 )
    goto LABEL_16;
  if ( *lpCmdLine == 32 )
  {
    while ( pos < cmdline_end )
    {
      ch = lpCmdLine[++pos];
      if ( ch != 32 )
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
    parse_command_line_options(argc, (int)argv);
    set_console_log_flush_pending();
    select_cdrom_core();
    dbg_print(" * Running %s emulator version %1.1f.%d. %s\n", "ePSXe", 1.6, 0, &current_dir_path);
    if ( strlen((const char *)cheat_file_from_cmdline) )
      loader_load_cheat_file((char *)cheat_file_from_cmdline);
    epsxe_main_loop_runner();
  }
LABEL_7:
  if ( pos >= cmdline_end )
    goto LABEL_16;
  if ( lpCmdLine[pos] == 34 )
  {
    ++pos;
    in_quotes = 1;
  }
  argv[1] = &lpCmdLine[pos];
  argc = 2;
  if ( pos >= cmdline_end )
    goto LABEL_16;
  while ( 1 )
  {
    cur_ch = lpCmdLine[pos];
    if ( in_quotes == 1 )
    {
      if ( cur_ch == 34 && prev_ch != 92 )
        goto LABEL_21;
    }
    else if ( cur_ch == 32 && prev_ch != 92 )
    {
LABEL_21:
      in_quotes = 0;
      lpCmdLine[pos] = 0;
      if ( ++pos < cmdline_end )
      {
        if ( lpCmdLine[pos] == 32 )
        {
          while ( pos < cmdline_end )
          {
            skip_ch = lpCmdLine[++pos];
            if ( skip_ch != 32 )
              goto LABEL_25;
          }
        }
        else
        {
LABEL_25:
          if ( pos < cmdline_end )
          {
            if ( lpCmdLine[pos] == 34 )
            {
              ++pos;
              in_quotes = 1;
            }
            argv[argc] = &lpCmdLine[pos];
            cur_ch = lpCmdLine[pos];
            if ( pos < cmdline_end )
              ++argc;
          }
        }
      }
      goto LABEL_15;
    }
    ++pos;
LABEL_15:
    prev_ch = cur_ch;
    if ( pos >= cmdline_end )
      goto LABEL_16;
  }
}
