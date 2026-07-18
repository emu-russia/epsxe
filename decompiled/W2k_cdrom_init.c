#include "pch.h"
char W2k_cdrom_init()
{
  char result; // al
  void *v1; // esp
  _BYTE v2[8092]; // [esp+0h] [ebp-1F9Ch] BYREF

  if ( !cdrom_letter )
  {
    cdrom_letter = W2k_sub_433B20();
    if ( !cdrom_letter )
      fatal_error_with_message_box(" * cdrom not found \n");
  }
  if ( !cd_savefake_flag )
    return cdrom_load_fake_file(cdrom_fake_filename);
  if ( cd_savefake_flag == 1 )
    cdrom_create_fake_file(cdrom_fake_filename);
  if ( loaded_file_type == 3 )
  {
    result = iso_load(bin_iso_file);
    sound_use_cdda = 0;
  }
  else
  {
    dbg_print(" * Init Core W2k cdrom ... ");
    sub_433C10(cdrom_letter, &byte_457338, &byte_4FD9D0, &byte_4FD9D4);
    hObject = sub_433B70(cdrom_letter);
    if ( !hObject )
      sound_use_cdda = 0;
    W2k_cdrom_gettrackinfo();
    dbg_print("[%c] ok\n", cdrom_letter);
    v1 = alloca(8092);
    memset(v2, 0xAAu, sizeof(v2));
    dword_504C8C = 0;
    dword_4FFF80 = -1;
    sub_434EE0(0, 2u, 0x10u, 2u, (DWORD)v2);
    result = v2[12];
    if ( !v2[12] && v2[13] == 2 && v2[14] == 22 && (result = v2[2364]) == 0 && v2[2365] == 2 && v2[2366] == 23 )
    {
      dword_504C8C = 1;
      dword_504C88 = 2352;
    }
    else if ( dword_504C8C != 1 )
    {
      memset(v2, 0xAAu, sizeof(v2));
      sub_434D40(0, 2u, 0x10u, 2u, (DWORD)v2);
      result = v2[12];
      if ( !v2[12] && v2[13] == 2 && v2[14] == 22 )
      {
        result = v2[2364];
        if ( !v2[2364] && v2[2365] == 2 && v2[2366] == 23 )
        {
          dword_504C8C = 7;
          dword_504C88 = 2352;
        }
      }
    }
  }
  return result;
}
