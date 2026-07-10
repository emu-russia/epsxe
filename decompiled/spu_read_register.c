#include "pch.h"
__int16 __cdecl sub_40BF40(unsigned int a1)
{
  int v1; // eax

  if ( !byte_4F75AA || (a1 & 0xF) != 0xC )
  {
    if ( spu_use_external_plugin == 1 )
    {
      LOWORD(v1) = SPUreadRegister(a1);
      return v1;
    }
    if ( a1 > 0x1F801DA8 )
    {
      if ( a1 != 528489902 )
        goto LABEL_15;
    }
    else
    {
      if ( a1 != 528489896 )
      {
        if ( a1 == 528489484 )
        {
          LOWORD(v1) = dword_50C270;
          return v1;
        }
        if ( a1 == 528489894 )
          return (unsigned int)unk_8A8080 >> 3;
LABEL_15:
        LOWORD(v1) = *(__int16 *)((char *)&unk_8A8084 + (a1 & 0x1FF));
        return v1;
      }
      if ( sound_enabled )
      {
        LOWORD(v1) = SPUgetOne(unk_8A8080);
        unk_8A8080 += 2;
        return v1;
      }
    }
    LOWORD(v1) = 0;
    return v1;
  }
  LOWORD(v1) = rand() & 1;
  return v1;
}
