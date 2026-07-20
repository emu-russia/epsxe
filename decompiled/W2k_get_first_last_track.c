#include "pch.h"
char __cdecl W2k_get_first_last_track(_BYTE *a1, _BYTE *a2)
{
  char result; // al

  *a1 = byte_4FFC42;
  result = byte_4FD9E3;
  *a2 = byte_4FD9E3;
  return result;
}
