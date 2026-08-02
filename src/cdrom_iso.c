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
        cpu_overclock_setting = 0;
      }
    }
    return dbg_print("ok\n");
  }
  return result;
}

char __cdecl iso_verify_sub(unsigned __int8 a1, unsigned __int8 a2, char a3, int a4)
{
  int v4; // eax
  unsigned __int8 v5; // bh
  int v6; // eax
  int v7; // eax
  unsigned __int8 v8; // dl
  unsigned __int8 v9; // bl
  unsigned __int8 v10; // al
  int v11; // eax
  unsigned __int8 v13; // [esp+Bh] [ebp-1h]
  unsigned __int8 v14; // [esp+10h] [ebp+4h]
  unsigned __int8 v15; // [esp+18h] [ebp+Ch]
  char v16; // [esp+18h] [ebp+Ch]

  *(_DWORD *)a4 = 0;
  *(_DWORD *)(a4 + 4) = 0;
  if ( use_subchannel )
  {
    *(_DWORD *)a4 = dword_50568D;
    *(_BYTE *)(a4 + 4) = byte_505691;
    *(_WORD *)(a4 + 5) = word_505693;
    *(_BYTE *)(a4 + 7) = byte_505695[0];
    if ( (unsigned __int8)byte_50A1A5 - 2 < 0 )
    {
      v13 = (unsigned __int8)byte_50A1A4 % 10 + 16 * ((unsigned __int8)byte_50A1A4 / 10) != (unsigned __int8)word_505693;
      if ( ((unsigned __int8)byte_50A1A4 - 1) % 10 + 16 * (((unsigned __int8)byte_50A1A4 - 1) / 10) != BYTE2(dword_50568D) )
        ++v13;
      v5 = byte_505695[0];
      if ( (unsigned __int8)byte_50A1A5 % 10 + 16 * ((unsigned __int8)byte_50A1A5 / 10) != HIBYTE(word_505693) )
        ++v13;
      v6 = (unsigned __int8)byte_50A1A5 + 58;
    }
    else
    {
      v4 = (unsigned __int8)byte_50A1A4 % 10 + 16 * ((unsigned __int8)byte_50A1A4 / 10);
      v13 = v4 != (unsigned __int8)word_505693;
      if ( v4 != BYTE2(dword_50568D) )
        ++v13;
      v5 = byte_505695[0];
      if ( (unsigned __int8)byte_50A1A5 % 10 + 16 * ((unsigned __int8)byte_50A1A5 / 10) != HIBYTE(word_505693) )
        ++v13;
      v6 = (unsigned __int8)byte_50A1A5 - 2;
    }
    if ( v6 % 10 + 16 * (v6 / 10) != HIBYTE(dword_50568D) )
      ++v13;
    v7 = (unsigned __int8)byte_50A1A6 % 10 + 16 * ((unsigned __int8)byte_50A1A6 / 10);
    v8 = v13;
    if ( v7 != v5 )
      v8 = v13 + 1;
    if ( v7 != (unsigned __int8)byte_505691 )
      ++v8;
    if ( v8 >= 2u && a1 == 3 )
    {
      *(_DWORD *)(a4 + 2) = 0;
      *(_WORD *)(a4 + 6) = 0;
      v7 = (unsigned __int8)byte_50A1A4 % 10 + 16 * ((unsigned __int8)byte_50A1A4 / 10);
      if ( v7 == 3 )
        byte_4F8320 = 1;
    }
  }
  else
  {
    if ( a3 )
    {
      v15 = a3 - 1;
    }
    else
    {
      v15 = 74;
      if ( a2 )
      {
        --a2;
      }
      else
      {
        a2 = 59;
        --a1;
      }
    }
    *(_BYTE *)a4 = 1;
    *(_BYTE *)(a4 + 1) = 1;
    v14 = a1 % 10 + 16 * (a1 / 10);
    v9 = a2 % 10 + 16 * (a2 / 10);
    v16 = v15 % 10 + 16 * (v15 / 10);
    v10 = v14;
    if ( v9 < 2u )
      v10 = ((v14 & 0xF) + 10 * (v14 >> 4) - 1) % 10 + 16 * (((v14 & 0xF) + 10 * (v14 >> 4) - 1) / 10);
    *(_BYTE *)(a4 + 2) = v10;
    v11 = v9 & 0xF;
    if ( v9 < 2u )
      v7 = v11 + 10 * (v9 >> 4) + 58;
    else
      v7 = v11 + 10 * (v9 >> 4) - 2;
    *(_BYTE *)(a4 + 6) = v9;
    *(_BYTE *)(a4 + 3) = v7 % 10 + 16 * (v7 / 10);
    *(_BYTE *)(a4 + 4) = v16;
    *(_BYTE *)(a4 + 5) = v14;
    *(_BYTE *)(a4 + 7) = v16;
    LOBYTE(v7) = v16;
  }
  return v7;
}

char __cdecl iso_read_data(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3, int a4)
{
  unsigned int v4; // esi
  int v5; // ebx
  char v6; // al
  char *v7; // esi
  char *v8; // edi
  unsigned int v9; // ecx
  char *v10; // edi
  char *v11; // esi
  char v12; // cl
  unsigned int v13; // edx
  unsigned int v14; // eax
  unsigned int v15; // ecx
  size_t v16; // edi
  char *v17; // edi
  int v18; // eax

  v4 = cdr_msf_to_lba(a1, a2, a3);
  if ( dword_505400 )
  {
    fseek(dword_505400, 96 * v4, 0);
    fread(byte_505680, 1u, 0x60u, dword_505400);
    byte_50A1A4 = a1;
    byte_50A1A5 = a2;
    byte_50A1A6 = a3;
  }
  if ( v4 < dword_456D74 || v4 >= dword_456D74 + 8 )
  {
    v13 = dword_456D78;
    v14 = v4 * dword_456D78;
    v15 = 8 * dword_456D78;
    if ( v4 * dword_456D78 < dword_4FD9A8
      && (v14 < dword_4FD9A8 - v15 ? (v16 = 8 * dword_456D78) : (v16 = dword_4FD9A8 - v14), v16) )
    {
      fseek(dword_50A098, dword_4FD9AC + v14, 0);
      fread(byte_505700, 1u, v16, dword_50A098);
      v13 = dword_456D78;
    }
    else
    {
      memset(byte_505700, 0, 4 * (v15 >> 2));
    }
    v5 = a4;
    dword_456D74 = v4;
    v17 = (char *)(a4 - v13 + 2352);
    qmemcpy(v17, byte_505700, 4 * (v13 >> 2));
    v11 = &byte_505700[4 * (v13 >> 2)];
    v10 = &v17[4 * (v13 >> 2)];
    v12 = v13;
  }
  else
  {
    v5 = a4;
    v6 = dword_456D78;
    v7 = &byte_505700[dword_456D78 * (v4 - dword_456D74)];
    v8 = (char *)(a4 - dword_456D78 + 2352);
    v9 = (unsigned int)dword_456D78 >> 2;
    qmemcpy(v8, v7, 4 * ((unsigned int)dword_456D78 >> 2));
    v11 = &v7[4 * v9];
    v10 = &v8[4 * v9];
    v12 = v6;
  }
  qmemcpy(v10, v11, v12 & 3);
  v18 = *(_DWORD *)(v5 + 13);
  if ( !v18 )
  {
    *(_BYTE *)(v5 + 15) = 2;
    *(_BYTE *)(v5 + 12) = a1 % 10 + 16 * (a1 / 10);
    *(_BYTE *)(v5 + 13) = a2 % 10 + 16 * (a2 / 10);
    v18 = (unsigned __int8)(a3 % 10 + 16 * (a3 / 10));
    *(_BYTE *)(v5 + 14) = v18;
  }
  return v18;
}

int iso_close()
{
  if ( dword_50A098 )
    _close((int)dword_50A098);
  if ( dword_505400 )
    _close((int)dword_505400);
  return dbg_print(" * Closing ISO system. \n");
}

