#include "pch.h"
int __cdecl spucore_voice_key_on(int a1)
{
  int result; // eax
  int v2; // edx

  result = 74 * a1;
  v2 = dword_465574[74 * a1];
  dword_4655A4[result] = 1;
  dword_4655B8[result] = 0;
  dword_4655BC[result] = v2;
  dword_4655AC[result] = 0;
  dword_465638[result] = 0;
  return result * 4;
}
