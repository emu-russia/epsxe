#include "pch.h"
char __cdecl ext_CDR_tarck_to_msf(__int16 a1, _BYTE *a2, _BYTE *a3, _BYTE *a4)
{
  char result; // al

  if ( a1 <= (int)HIBYTE(word_505540) )
  {
    if ( a1 )
    {
      *a2 = byte_50553F[3 * a1];
      *a3 = *((_BYTE *)&word_505540 + 3 * a1);
      result = *((_BYTE *)&word_505540 + 3 * a1 + 1);
      *a4 = result;
    }
    else
    {
      *a2 = byte_505542[3 * HIBYTE(word_505540)];
      *a3 = byte_505543[3 * HIBYTE(word_505540)];
      result = HIBYTE(word_505540);
      *a4 = byte_505544[3 * HIBYTE(word_505540)];
    }
  }
  else
  {
    *a2 = 0;
    *a3 = 2;
    *a4 = 0;
    return (char)a2;
  }
  return result;
}
