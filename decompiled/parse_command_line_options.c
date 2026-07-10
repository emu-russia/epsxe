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
      if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aBios) )
      {
        cmdline_set_bios_name(*(const char **)(a2 + 4 * (unsigned __int16)v3 + 4));
        v3 += 2;
      }
      else
      {
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aNosubchan) )
        {
          use_subchannel = 0;
LABEL_146:
          ++v3;
          goto LABEL_147;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aSubchan) )
        {
          use_subchannel = 1;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aExtsubchanhle) )
        {
          extsubchanhle = 1;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aPslib) )
        {
          BYTE1(dword_4F831C) = 1;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aNocdoverwrite) )
        {
          LOBYTE(word_455FA8[0]) = 1;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aNomdectiming) )
        {
          mdectiming = 0;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aMdectiming) )
        {
          mdectiming = 1;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aForcepad) )
        {
          forcepad = 128;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aNoforcepad) )
        {
          forcepad = 0;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aForcespu) )
        {
          forcespu = -1;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aNoforcespu) )
        {
          forcespu = 0;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aNocd) )
        {
          nocd = 0;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aNoaudiocd) )
        {
          sound_use_cdda = 0;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aAudiocd) )
        {
          sound_use_cdda = 0;
          goto LABEL_146;
        }
        if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aNogui) )
        {
          create_window_flag = 0;
          byte_44DD19 = 0;
          goto LABEL_146;
        }
        if ( !strncmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), Str2, 3u) )
        {
          LOBYTE(dword_455945) = atoi(*(const char **)(a2 + 4 * (unsigned __int16)v3 + 4));
          v3 += 2;
        }
        else
        {
          if ( !strncmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aI, 3u) )
          {
            dword_50C36C = 0;
            goto LABEL_146;
          }
          if ( !strncmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aV, 3u) )
            print_version();
          if ( !strncmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), asc_44BFC8, 3u)
            || !strncmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aFastboot, 3u) )
          {
            fastboot = 1;
            goto LABEL_146;
          }
          if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aSlowboot) )
          {
            fastboot = 0;
            goto LABEL_146;
          }
          if ( !strncmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aFl, 4u) )
          {
            byte_4FD995 = 1;
            goto LABEL_146;
          }
          if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aNosound) )
          {
            sound_enabled = 0;
            goto LABEL_146;
          }
          if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aSound) )
          {
            sound_enabled = 1;
            goto LABEL_146;
          }
          if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aNomdec) )
          {
            mdec_disable = 1;
            goto LABEL_146;
          }
          if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aMdec) )
          {
            mdec_disable = 0;
            goto LABEL_146;
          }
          if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aNomemcard) )
          {
            byte_4557A8 = 0;
            goto LABEL_146;
          }
          if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aMemcard) )
          {
            byte_4557A8 = 1;
            goto LABEL_146;
          }
          if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aXasound) )
          {
            sound_use_xa = 1;
            goto LABEL_146;
          }
          if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aNoxasound) )
          {
            sound_use_xa = 0;
            goto LABEL_146;
          }
          if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aXaread) )
          {
            xa_read_enable = 1;
            goto LABEL_146;
          }
          if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aNoxaread) )
          {
            xa_read_enable = 0;
            goto LABEL_146;
          }
          if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aSavefake) )
          {
            byte_456D70 = 1;
            strcpy(byte_505420, *(const char **)(a2 + 4 * (unsigned __int16)v3 + 4));
            v3 += 2;
          }
          else
          {
            if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aLegaia) )
            {
              byte_4FD881 = 1;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aFf9pal) )
            {
              BYTE1(dword_455945) = 0;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aPe2) )
            {
              byte_4FD860 = 1;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aNocputrick) )
            {
              BYTE1(dword_455945) = 0;
              goto LABEL_146;
            }
            if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aLoadfake) )
            {
              byte_456D70 = 0;
              strcpy(byte_505420, *(const char **)(a2 + 4 * (unsigned __int16)v3 + 4));
              v3 += 2;
            }
            else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aLoadppf) )
            {
              strcpy(unk_8B4580, *(const char **)(a2 + 4 * (unsigned __int16)v3 + 4));
              v3 += 2;
            }
            else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aLoadmemc0) )
            {
              strcpy((char *)byte_8B3180, *(const char **)(a2 + 4 * (unsigned __int16)v3 + 4));
              v3 += 2;
            }
            else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aLoadmemc1) )
            {
              strcpy((char *)byte_8B3580, *(const char **)(a2 + 4 * (unsigned __int16)v3 + 4));
              v3 += 2;
            }
            else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aLoadbin)
                   || !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aLoadiso) )
            {
              strcpy(bin_iso_file, *(const char **)(a2 + 4 * (unsigned __int16)v3 + 4));
              dword_50C37C = 3;
              v3 += 2;
            }
            else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aLoadcheat) )
            {
              strcpy(&unk_8B55A0, *(const char **)(a2 + 4 * (unsigned __int16)v3 + 4));
              v3 += 2;
            }
            else
            {
              if ( strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aLoadstate) )
              {
                if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aSsv0) )
                {
                  byte_44C0AC = 0;
                }
                else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aNocdstatus) )
                {
                  byte_4FD880 = 1;
                }
                else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aNoauto) )
                {
                  byte_45B8CA = 1;
                  BYTE1(dword_455945) = 0;
                }
                else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aMouse) )
                {
                  dword_456048[0] = 2;
                  dword_4FD8DC = 1;
                }
                else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aMouse2) )
                {
                  if ( dword_456048[0] == 2 )
                    dword_456048[0] = 1;
                  dword_45604C = 2;
                  dword_4FD8DC = 1;
                }
                else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aAnamouse) )
                {
                  dword_456048[0] = 6;
                  dword_4FD8E0[0] = 0;
                  dword_4FD8DC = 1;
                }
                else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aGun) )
                {
                  dword_456048[0] = 3;
                  dword_4FD8DC = 1;
                }
                else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aMultitap) )
                {
                  multitap_1 = 1;
                }
                else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aAnalog) )
                {
                  dword_456048[0] = 4;
                  dword_4FD8E0[0] = 0;
                }
                else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aAnalog1) )
                {
                  dword_456048[0] = 4;
                  dword_4FD8E0[0] = 0;
                }
                else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aAnalog2) )
                {
                  dword_45604C = 4;
                  dword_4FD8E4 = 0;
                }
                else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aAnalog3) )
                {
                  dword_456050 = 4;
                  dword_4FD8E8 = 0;
                }
                else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aAnalog4) )
                {
                  dword_456054 = 4;
                  dword_4FD8EC = 0;
                }
                else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aNoignorecmd) )
                {
                  byte_455FA3 = 0;
                }
                else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aNocdinc) )
                {
                  byte_455FA4 = 0;
                }
                else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aNoppf) )
                {
                  auto_ppf_load = 0;
                }
                else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aPpf) )
                {
                  auto_ppf_load = 1;
                }
                else if ( strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aNolog) )
                {
                  if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aGtrace) )
                  {
                    byte_4F8318 = 1;
                  }
                  else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aAdjusttiming) )
                  {
                    byte_4FC4E5 = 1;
                  }
                  else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aOldtiming) )
                  {
                    byte_45B8C9 = 1;
                  }
                  else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aNoadjusttiming) )
                  {
                    byte_4FC4E5 = 0;
                  }
                  else if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aDisablereportm) )
                  {
                    byte_455FA5 = 0;
                  }
                  else
                  {
                    if ( !strcmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), aHdev) )
                      print_develop_options();
                    if ( !strncmp(*(const char **)(a2 + 4 * (unsigned __int16)v3), asc_44BDA8, 2u) )
                      print_usage();
                    v4 = *(const char **)(a2 + 4 * (unsigned __int16)v3);
                    if ( *v4 == 45 )
                      fatal_error_with_message_box(" * ePSXe error: %s param incorrect \n", v4);
                    sub_41C010(v4);
                    dword_50C37C = 4;
                  }
                }
                goto LABEL_146;
              }
              strcpy(unk_8B5180, *(const char **)(a2 + 4 * (unsigned __int16)v3 + 4));
              v3 += 2;
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
