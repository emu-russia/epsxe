#include "pch.h"
char memcard_load()
{
  FILE *v0; // eax
  unsigned int i; // eax
  unsigned int j; // eax
  unsigned int k; // eax
  FILE *v4; // eax
  FILE *v5; // esi
  FILE *v6; // esi

  LOBYTE(v0) = byte_4FC460;
  if ( !byte_4FC460 )
  {
    if ( !strcmp((const char *)&ram[258248], aNull) )
      sprintf((char *const)&ram[258248], "%s", aMemcardsEpsxe0);
    if ( !strcmp((const char *)&ram[258504], aNull) )
      sprintf((char *const)&ram[258504], "%s", aMemcardsEpsxe0_0);
    for ( i = 0; i < 0x20000; ++i )
    {
      byte_546860[i] = 0;
      byte_526860[i] = 0;
    }
    byte_546860[0] = 77;
    byte_526860[0] = 77;
    byte_546861 = 67;
    byte_526861 = 67;
    byte_5468DF = 14;
    byte_5268DF = 14;
    for ( j = 0; j < 0x780; j += 128 )
    {
      byte_5468E0[j] = -96;
      byte_5268E0[j] = -96;
      byte_5468E8[j] = -1;
      byte_5268E8[j] = -1;
      byte_5468E9[j] = -1;
      byte_5268E9[j] = -1;
      byte_54695F[j] = -96;
      byte_52695F[j] = -96;
    }
    for ( k = 0; k < 0xA00; k += 128 )
    {
      byte_547060[k] = -1;
      byte_527060[k] = -1;
      byte_547060[k + 1] = -1;
      byte_527061[k] = -1;
      byte_547060[k + 2] = -1;
      byte_527062[k] = -1;
      byte_547060[k + 3] = -1;
      byte_527063[k] = -1;
      byte_547060[k + 8] = -1;
      byte_527068[k] = -1;
      byte_547060[k + 9] = -1;
      byte_527069[k] = -1;
    }
    v4 = fopen((const char *)&ram[258248], Mode);
    v5 = v4;
    if ( v4 )
    {
      fseek(v4, 0, 2);
      Offset = ftell(v5) - 0x20000;
      fseek(v5, Offset, 0);
      fread(byte_526860, 1u, 0x20000u, v5);
      fclose(v5);
    }
    else
    {
      Offset = 0;
    }
    v0 = fopen((const char *)&ram[258504], Mode);
    v6 = v0;
    if ( v0 )
    {
      fseek(v0, 0, 2);
      dword_4FC474 = ftell(v6) - 0x20000;
      fseek(v6, dword_4FC474, 0);
      fread(byte_546860, 1u, 0x20000u, v6);
      LOBYTE(v0) = fclose(v6);
    }
    else
    {
      dword_4FC474 = 0;
    }
    byte_4FC460 = 1;
  }
  return (char)v0;
}
