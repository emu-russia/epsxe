#include "pch.h"
__int16 __cdecl spucore_write_register(__int16 a1, unsigned __int16 a2)
{
  unsigned int v2; // eax
  __int16 result; // ax

  v2 = (a1 & 0xFFF) - 3072;
  dword_4F75A0 = 0;
  if ( v2 < 0x180 )
    return sub_40CE20(v2 >> 4, a1 & 0xF, a2);
  result = (a1 & 0xFFF) - 3456;
  switch ( a1 & 0xFFF )
  {
    case 0xD80:
      word_4F7586 = a2 & 0x3FFF;
      break;
    case 0xD82:
      LOWORD(dword_4F7588) = a2 & 0x3FFF;
      result = a2 & 0x3FFF;
      break;
    case 0xD84:
      word_4EF130 = a2;
      break;
    case 0xD86:
      word_4EF132 = a2;
      break;
    case 0xD88:
      result = sub_40CCF0(a2);
      break;
    case 0xD8A:
      result = sub_40CCF0(a2 << 16);
      break;
    case 0xD8C:
      result = sub_40CD20(a2);
      break;
    case 0xD8E:
      result = sub_40CD20(a2 << 16);
      break;
    case 0xD90:
      dword_4F7558 = a2 + (dword_4F7558 & 0xFF0000);
      break;
    case 0xD92:
      result = dword_4F7558;
      dword_4F7558 = (unsigned __int16)dword_4F7558 + (a2 << 16);
      break;
    case 0xD94:
      dword_463900 = a2 + (dword_463900 & 0xFF0000);
      result = a2;
      break;
    case 0xD96:
      dword_463900 = (unsigned __int16)dword_463900 + (a2 << 16);
      break;
    case 0xD98:
      dword_4E7100 = a2 + (dword_4E7100 & 0xFF0000);
      result = a2;
      break;
    case 0xD9A:
      result = dword_4E7100;
      dword_4E7100 = (unsigned __int16)dword_4E7100 + (a2 << 16);
      break;
    case 0xD9C:
      dword_4EF138 = a2 + (dword_4EF138 & 0xFF0000);
      break;
    case 0xD9E:
      result = dword_4EF138;
      dword_4EF138 = (unsigned __int16)dword_4EF138 + (a2 << 16);
      break;
    case 0xDA2:
      byte_4EF142[0x3FFF] = a2;
      break;
    case 0xDA4:
      LOWORD(dword_463904) = a2;
      result = a2;
      break;
    case 0xDA6:
      result = sub_40CD80(a2);
      break;
    case 0xDA8:
      result = sub_40CDA0(a2);
      break;
    case 0xDAA:
      result = sub_40CD50(a2);
      break;
    case 0xDAC:
      result = sub_40CD60(a2);
      break;
    case 0xDAE:
      result = sub_40CD70(a2);
      break;
    case 0xDB0:
      word_4E7104 = a2;
      result = a2;
      break;
    case 0xDB2:
      word_4E7106 = a2;
      break;
    case 0xDB4:
      word_4F755C = a2;
      break;
    case 0xDB6:
      word_4F7584 = a2;
      result = a2;
      break;
    default:
      return result;
  }
  return result;
}
