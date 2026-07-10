#include "pch.h"
int __cdecl sub_41BB00(unsigned __int8 a1, unsigned int a2)
{
  int result; // eax

  result = a2;
  unk_8A7F00[a1] = a2;
  if ( a1 >= 0x10u && a1 <= 0x13u )
    unk_8A7F00[a1] = (unsigned __int16)a2;
  switch ( a1 )
  {
    case 0xEu:
      unk_8A7F3C = a2;
      break;
    case 0xFu:
      unk_8A7F30 = unk_8A7F34;
      unk_8A7F34 = unk_8A7F38;
      unk_8A7F38 = a2;
      break;
    case 0x1Cu:
      result = ((a2 >> 10) & 0x1F) << 7;
      word_8A7F24 = (a2 & 0x1F) << 7;
      word_8A7F28 = ((a2 >> 5) & 0x1F) << 7;
      word_8A7F2C = result;
      break;
  }
  return result;
}
