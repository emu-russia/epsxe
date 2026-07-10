#include "pch.h"
char init_aspi()
{
  char result; // al
  __int16 v1; // ax
  unsigned __int8 v2; // bl
  char v3; // al
  unsigned __int8 v4; // bl
  unsigned __int8 v5; // [esp+4h] [ebp-54h]
  unsigned __int8 i; // [esp+8h] [ebp-50h]
  unsigned __int8 v7; // [esp+Ch] [ebp-4Ch]
  _DWORD v8[2]; // [esp+10h] [ebp-48h] BYREF
  unsigned __int8 v9; // [esp+18h] [ebp-40h]
  unsigned __int8 v10; // [esp+19h] [ebp-3Fh]
  __int16 v11; // [esp+1Ah] [ebp-3Eh]
  _BYTE v12[60]; // [esp+1Ch] [ebp-3Ch] BYREF

  result = HIBYTE(dword_4FD9BC);
  if ( !HIBYTE(dword_4FD9BC) )
  {
    v1 = GetASPI32SupportInfo();
    BYTE1(dword_4FD9BC) = v1;
    if ( HIBYTE(v1) != 1 && HIBYTE(v1) != 0xE8 )
      fatal_error_with_message_box(" * Error in init aspi (%d)\n", HIBYTE(v1));
    result = BYTE1(dword_4FD9BC);
    v2 = 0;
    for ( i = 0; v2 < BYTE1(dword_4FD9BC); i = v2 )
    {
      memset(v12, 0, sizeof(v12));
      v12[0] = 0;
      v12[2] = v2;
      dword_4FFF68(v12);
      if ( v12[1] == 1 )
      {
        v3 = v12[45];
        BYTE2(dword_4FD9BC) = v12[45];
        if ( !v12[45] )
        {
          v3 = 8;
          BYTE2(dword_4FD9BC) = 8;
        }
        v5 = 0;
        if ( v3 )
        {
          do
          {
            v4 = 0;
            v7 = 0;
            do
            {
              v8[0] = 1;
              v8[1] = 0;
              v11 = 0;
              BYTE2(v8[0]) = i;
              v9 = v5;
              v10 = v4;
              dword_4FFF68(v8);
              if ( BYTE1(v8[0]) == 1 && (_BYTE)v11 == 5 )
                sub_430E40(i, v5, v7);
              v7 = ++v4;
            }
            while ( v4 < 8u );
            ++v5;
          }
          while ( v5 < BYTE2(dword_4FD9BC) );
          v2 = i;
        }
      }
      result = BYTE1(dword_4FD9BC);
      ++v2;
    }
  }
  return result;
}
