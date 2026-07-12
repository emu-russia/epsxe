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
    sub_42F990(a1, a2, a3, Buffer);
    return 0;
  }
  if ( loaded_file_type == 3 )
  {
    sub_42FF60(a1, a2, a3, (int)Buffer);
    if ( auto_ppf_load )
    {
      v5 = sub_42C6D0(a1, a2, a3);
      sub_436F60(v5, (int)Buffer);
    }
    if ( cd_savefake_flag == 1 )
    {
      sub_42F8F0(a1, a2, a3, Buffer);
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
    if ( auto_ppf_load )
    {
      v8 = sub_42C6D0(a1, a2, a3);
      sub_436F60(v8, (int)Buffer);
      v7 = Buffer;
    }
    if ( cd_savefake_flag == 1 )
      sub_42F8F0(a1, a2, a3, v7);
  }
  return 0;
}
