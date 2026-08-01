#include "pch.h"
char __cdecl ext_CDR_get_first_last_track(_BYTE *a1, _BYTE *a2)
{
  char result; // al

  *a1 = word_505540;
  result = HIBYTE(word_505540);
  *a2 = HIBYTE(word_505540);
  return result;
}
