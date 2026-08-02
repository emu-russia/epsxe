#include "pch.h"
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
          byte_4F831D = 1;
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
          byte_455945 = atoi(*(const char **)(a2 + 4 * (unsigned __int16)v3 + 4));
          v3 += 2;
        }
        else
        {
          if ( !strncmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-i", 3u) )
          {
            dynarec_enabled = 0;
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
                cpu_overclock_setting = 0;
                goto LABEL_146;
              }
              if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-pe2") )
              {
                parasite_eve_cheat = 1;
                goto LABEL_146;
              }
              if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-nocputrick") )
              {
                cpu_overclock_setting = 0;
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
                  cpu_overclock_setting = 0;
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
                  ignore_cmd = 0;
                  goto LABEL_146;
                }
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), "-nocdinc") )
                {
                  cd_inc = 0;
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
                  report_mode_enabled = 0;
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
