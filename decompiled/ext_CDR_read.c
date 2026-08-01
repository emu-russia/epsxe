#include "pch.h"
int __cdecl ext_CDR_read(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3, char *Buffer)
{
  int v5; // eax
  const void *v6; // eax
  char *v7; // edx
  int v8; // eax
  _BYTE v9[16]; // [esp+14h] [ebp-10h] BYREF

  if ( !cd_savefake_flag )
  {
    cdrom_fake_read_portion(a1, a2, a3, Buffer);
    return 0;
  }
  if ( loaded_file_type == 3 )
  {
    iso_read_data(a1, a2, a3, (int)Buffer);
    if ( ppf_enabled )
    {
      v5 = cdr_msf_to_lba(a1, a2, a3);
      ppf_apply_patch_to_sector(v5, (int)Buffer);
    }
    if ( cd_savefake_flag == 1 )
    {
      cdrom_fake_write_portion(a1, a2, a3, Buffer);
      return 0;
    }
  }
  else
  {
    v9[0] = a1 % 10 + 16 * (a1 / 10);
    v9[1] = a2 % 10 + 16 * (a2 / 10);
    v9[2] = a3 % 10 + 16 * (a3 / 10);
    CDRreadTrack(v9);
    v6 = (const void *)CDRgetBuffer();
    v7 = Buffer;
    qmemcpy(Buffer + 12, v6, 0x930u);
    if ( ppf_enabled )
    {
      v8 = cdr_msf_to_lba(a1, a2, a3);
      ppf_apply_patch_to_sector(v8, (int)Buffer);
      v7 = Buffer;
    }
    if ( cd_savefake_flag == 1 )
      cdrom_fake_write_portion(a1, a2, a3, v7);
  }
  return 0;
}
