#include "pch.h"
char __cdecl sub_40D820(int a1)
{
  char result; // al
  int v2; // edx

  result = sound_enabled;
  if ( sound_enabled )
  {
    result = sound_use_xa;
    if ( sound_use_xa )
    {
      if ( sub_403BF0(&dword_4E7108, a1, spu_adpcm_flag) )
      {
        v2 = dword_4E7114;
      }
      else
      {
        v2 = 2016;
        dword_4E7114 = 2016;
      }
      result = dword_4E7108;
      if ( spu_adpcm_flag == 1 )
        dword_44F7A0 = dword_4E7108;
      spu_adpcm_flag = 0;
      if ( HIWORD(dword_4F75B0) )
      {
        if ( dword_44F7A0 < dword_4E7108 )
        {
          result = dword_44F7A0 - 6;
          dword_44F7A0 += 250;
        }
      }
      else
      {
        if ( 2 * v2 > 0 )
          qmemcpy(word_4EF140, &byte_4E7128, 4 * ((unsigned int)(2 * v2) >> 1));
        HIWORD(dword_4F75B0) = v2;
        dword_4E7114 = 0;
      }
    }
  }
  return result;
}
