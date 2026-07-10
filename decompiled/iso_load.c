#include "pch.h"
char __cdecl iso_load(char *FileName)
{
  FILE *v1; // eax
  char result; // al
  char v3; // al
  int Offset; // [esp+4h] [ebp-404h] BYREF
  char Buffer[1024]; // [esp+8h] [ebp-400h] BYREF

  dbg_print(" * Loading ISO Format ");
  v1 = fopen(FileName, "rb");
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
      dbg_print("[NRG2352] ");
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
      dbg_print("[NRG2336] ");
      goto LABEL_12;
    }
    if ( Offset != 0x200000 )
    {
LABEL_11:
      dbg_print("[BIN/IMG2352] ");
    }
    else
    {
      dbg_print("[CDI2336] ");
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
      qmemcpy(&Buffer[strlen(Buffer) - 3], "sub", 3);
      dword_505400 = fopen(Buffer, "rb");
      if ( dword_505400 )
      {
        use_subchannel = 1;
        dbg_print("(+subchannel) ");
        BYTE1(dword_455945) = 0;
      }
    }
    return dbg_print("ok\n");
  }
  return result;
}
