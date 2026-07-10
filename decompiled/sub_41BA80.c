#include "pch.h"
int __cdecl sub_41BA80(unsigned __int8 a1)
{
  unsigned __int8 v2; // al
  int v3; // edx

  if ( a1 == 31 )
    return (unsigned __int8)sub_414EE0(unk_8A7F78);
  if ( a1 != 29 )
    return unk_8A7F00[a1];
  sub_410400((unsigned __int16)word_8A7F2C);
  sub_410400((unsigned __int16)word_8A7F28);
  v2 = sub_410400((unsigned __int16)word_8A7F24);
  return v3 | v2;
}
