#include "pch.h"
char __cdecl sub_41BEA0(const char *a1, char *Buffer)
{
  int v2; // edi
  const char *i; // ebp
  char v5; // cl
  char v6; // cl
  char v7; // cl
  const char *v8; // eax

  if ( byte_45B8CA )
    return 0;
  v2 = 0;
  if ( !dword_450C70 )
    return 0;
  for ( i = aSces02105; strcmp(a1, i); i += 81 )
  {
    if ( ++v2 >= (unsigned int)dword_450C70 )
      return 0;
  }
  v5 = byte_450CBE[81 * v2];
  if ( v5 != -1 )
    mdectiming = v5;
  v6 = byte_450CBF[81 * v2];
  if ( v6 != -1 )
    dword_50C374 = v6;
  if ( byte_450CC0[81 * v2] != -1 )
    forcespu = byte_450CC0[81 * v2];
  v7 = byte_450CC1[81 * v2];
  if ( v7 != -1 )
    forcepad = v7;
  if ( byte_450CC2[81 * v2] != -1 )
    BYTE1(dword_455945) = byte_450CC2[81 * v2];
  if ( byte_450CC3[81 * v2] != -1 )
    byte_4FD860 = byte_450CC3[81 * v2];
  if ( byte_450CC4[81 * v2] != -1 )
    byte_455FA4 = byte_450CC4[81 * v2];
  if ( byte_450CC5[81 * v2] != -1 )
    byte_4F75AA = byte_450CC5[81 * v2];
  if ( byte_450CC6[81 * v2] != -1 )
    byte_4FD880 = byte_450CC6[81 * v2];
  if ( byte_450CC8[81 * v2] != -1 )
    byte_4FC4E6 = byte_450CC8[81 * v2];
  v8 = &aNull_1[81 * v2];
  if ( !strcmp(aNull, v8) )
    return 0;
  sprintf(Buffer, "%s", v8);
  return 1;
}
