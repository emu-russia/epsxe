#include "pch.h"
char __cdecl sub_42FA70(char *FileName)
{
  FILE *v1; // eax
  char result; // al
  char v3; // al
  char *v4; // ecx
  char v5; // al
  int Offset; // [esp+4h] [ebp-404h] BYREF
  char Buffer[1024]; // [esp+8h] [ebp-400h] BYREF

  dbg_print(aLoadingIsoForm);
  v1 = fopen(FileName, Mode);
  dword_50A098 = v1;
  if ( !v1 )
    fatal_error_with_message_box(" * Error loading cdrombin [%s]\n", FileName);
  fseek(v1, 0, 2);
  dword_4FD9A8 = ftell(dword_50A098);
  dword_456D74 = -1;
  fseek(dword_50A098, 12, 0);
  fread(&Offset, 1u, 4u, dword_50A098);
  if ( Offset == 0x2000000 )
  {
    fseek(dword_50A098, 150 * dword_456D78 + 12, 0);
    fread(&Offset, 1u, 4u, dword_50A098);
    if ( Offset == 33554944 )
    {
      dword_4FD9AC = 150 * dword_456D78;
      dbg_print(aNrg2352);
    }
  }
  else
  {
    if ( Offset )
      goto LABEL_11;
    fseek(dword_50A098, 0, 0);
    fread(&Offset, 1u, 4u, dword_50A098);
    if ( Offset == 0x80000 )
    {
      dword_456D78 = 2336;
      dbg_print(aNrg2336);
      goto LABEL_12;
    }
    if ( Offset != 0x200000 )
    {
LABEL_11:
      dbg_print(aBinImg2352);
    }
    else
    {
      dbg_print(aCdi2336);
      dword_456D78 = 2336;
      dword_4FD9AC = 350400;
    }
  }
LABEL_12:
  fseek(dword_50A098, 0, 0);
  sprintf(Buffer, "%s", FileName);
  result = use_subchannel;
  if ( use_subchannel )
  {
    v3 = Buffer[strlen(Buffer) - 4];
    use_subchannel = 0;
    if ( v3 == 46 )
    {
      v4 = &Buffer[strlen(Buffer) - 3];
      v5 = byte_456E22;
      *(_WORD *)v4 = word_456E20;
      v4[2] = v5;
      dword_505400 = fopen(Buffer, Mode);
      if ( dword_505400 )
      {
        use_subchannel = 1;
        dbg_print(aSubchannel);
        BYTE1(dword_455945) = 0;
      }
    }
    return dbg_print(aOk_0);
  }
  return result;
}
