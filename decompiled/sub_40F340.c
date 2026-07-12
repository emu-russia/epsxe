#include "pch.h"
int sub_40F340()
{
  int result; // eax
  int i; // eax
  int j; // esi
  int v3; // ecx
  char *v4; // edx
  int *v5; // ebp
  int v6; // eax
  unsigned int v7; // edi
  char *v8; // ecx
  char *v9; // [esp+2Ch] [ebp-104h]
  _BYTE v10[256]; // [esp+30h] [ebp-100h] BYREF

  memset(word_50AE00, 0, 0x40u);
  memset(v10, 0, sizeof(v10));
  result = dword_4F7A5C;
  if ( dword_4F7A5C )
  {
    if ( dword_4F82EC == 1 )
    {
      result = (*(int (__stdcall **)(int, int, _BYTE *))(*(_DWORD *)dword_4F7A5C + 36))(dword_4F7A5C, 256, v10);
      if ( result >= 0 )
      {
        for ( i = 0; i < 256; ++i )
        {
          if ( v10[i] )
          {
            if ( !byte_50ABC0[i] )
              byte_50ABC0[i] = 1;
          }
          else
          {
            byte_50ABC0[i] = 0;
          }
        }
        byte_50ABC0[0] = 0;
        for ( j = 0; j < 4; ++j )
        {
          v3 = dword_4F776C[j];
          result = 0;
          if ( v3 )
          {
            v4 = &byte_50AD40[32 * j];
            v9 = v4;
            do
            {
              v4[result - 128] = 0;
              v4[result++] = 0;
            }
            while ( result < 32 );
            (*(void (__stdcall **)(int))(*(_DWORD *)v3 + 100))(v3);
            v5 = (int *)&byte_4F7788[80 * j];
            result = (*(int (__stdcall **)(int, int, int *))(*(_DWORD *)dword_4F776C[j] + 36))(dword_4F776C[j], 80, v5);
            if ( result == -2147024866 )
            {
              v6 = dword_4F776C[j];
              if ( v6 )
                (*(void (__stdcall **)(int))(*(_DWORD *)v6 + 28))(dword_4F776C[j]);
              result = (*(int (__stdcall **)(int, int, char *))(*(_DWORD *)dword_4F776C[j] + 36))(
                         dword_4F776C[j],
                         80,
                         &byte_4F7788[80 * j]);
              if ( result < 0 )
                return result;
            }
            if ( !dword_4F7A68[j] )
            {
              result = *v5;
              if ( *v5 > 0 )
              {
                byte_50ACC0[32 * j] = 1;
                result = 16 * j;
                word_50AE02[8 * j] = *(_WORD *)v5;
              }
            }
            if ( !dword_4F7AA8[j] )
            {
              result = *v5;
              if ( *v5 < 0 )
              {
                byte_50ACC1[32 * j] = 1;
                result = 16 * j;
                word_50AE02[8 * j] = *(_WORD *)v5;
              }
            }
            if ( !dword_4F7AE8[j] )
            {
              result = dword_4F778C[20 * j];
              if ( result > 0 )
              {
                byte_50ACC2[32 * j] = 1;
                result = 16 * j;
                word_50AE04[8 * j] = dword_4F778C[20 * j];
              }
            }
            if ( !dword_4F7B28[j] )
            {
              result = dword_4F778C[20 * j];
              if ( result < 0 )
              {
                byte_50ACC3[32 * j] = 1;
                result = 16 * j;
                word_50AE04[8 * j] = dword_4F778C[20 * j];
              }
            }
            if ( !dword_4F7B68[j] )
            {
              result = dword_4F7790[20 * j];
              if ( result > 0 )
              {
                byte_50ACC4[32 * j] = 1;
                result = 16 * j;
                word_50AE06[8 * j] = dword_4F7790[20 * j];
              }
            }
            if ( !dword_4F7BA8[j] )
            {
              result = dword_4F7790[20 * j];
              if ( result < 0 )
              {
                byte_50ACC5[32 * j] = 1;
                result = 16 * j;
                word_50AE06[8 * j] = dword_4F7790[20 * j];
              }
            }
            if ( !dword_4F7C68[j] )
            {
              result = dword_4F7798[20 * j];
              if ( result > 0 )
              {
                byte_50ACC6[32 * j] = 1;
                result = 16 * j;
                word_50AE08[8 * j] = dword_4F7798[20 * j];
              }
            }
            if ( !dword_4F7CA8[j] )
            {
              result = dword_4F7798[20 * j];
              if ( result < 0 )
              {
                byte_50ACC7[32 * j] = 1;
                result = 16 * j;
                word_50AE08[8 * j] = dword_4F7798[20 * j];
              }
            }
            if ( !dword_4F7CE8[j] )
            {
              result = dword_4F779C[20 * j];
              if ( result > 0 )
              {
                byte_50ACC8[32 * j] = 1;
                result = 16 * j;
                word_50AE0A[8 * j] = dword_4F779C[20 * j];
              }
            }
            if ( !dword_4F7D28[j] )
            {
              result = dword_4F779C[20 * j];
              if ( result < 0 )
              {
                byte_50ACC9[32 * j] = 1;
                result = 16 * j;
                word_50AE0A[8 * j] = dword_4F779C[20 * j];
              }
            }
            if ( !dword_4F7D68[j] )
            {
              result = dword_4F77A0[20 * j];
              if ( result > 0 )
              {
                byte_50ACCA[32 * j] = 1;
                result = 16 * j;
                word_50AE0C[8 * j] = dword_4F77A0[20 * j];
              }
            }
            if ( !dword_4F7DA8[j] )
            {
              result = dword_4F77A0[20 * j];
              if ( result < 0 )
              {
                byte_50ACCB[32 * j] = 1;
                result = 16 * j;
                word_50AE0C[8 * j] = dword_4F77A0[20 * j];
              }
            }
            if ( !dword_4F7DE8[j] )
            {
              result = dword_4F77A4[20 * j];
              if ( result > 0 )
              {
                byte_50ACCC[32 * j] = 1;
                result = 16 * j;
                word_50AE0E[8 * j] = dword_4F77A4[20 * j];
              }
            }
            if ( !dword_4F7E28[j] )
            {
              result = dword_4F77A4[20 * j];
              if ( result < 0 )
              {
                byte_50ACCD[32 * j] = 1;
                result = 16 * j;
                word_50AE0E[8 * j] = dword_4F77A4[20 * j];
              }
            }
            if ( !dword_4F7E68[j] && byte_4F77B8[80 * j] )
              byte_50ACD0[32 * j] = 1;
            if ( !dword_4F7EA8[j] && byte_4F77B9[80 * j] )
            {
              result = 32 * j;
              byte_50ACD1[32 * j] = 1;
            }
            if ( !dword_4F7EE8[j] && byte_4F77BA[80 * j] )
              byte_50ACD2[32 * j] = 1;
            if ( !dword_4F7F28[j] && byte_4F77BB[80 * j] )
              byte_50ACD3[32 * j] = 1;
            if ( !dword_4F7F68[j] && byte_4F77BC[80 * j] )
            {
              result = 32 * j;
              byte_50ACD4[32 * j] = 1;
            }
            if ( !dword_4F7FA8[j] && byte_4F77BD[80 * j] )
              byte_50ACD5[32 * j] = 1;
            if ( !dword_4F7FE8[j] && byte_4F77BE[80 * j] )
              byte_50ACD6[32 * j] = 1;
            if ( !dword_4F8028[j] && byte_4F77BF[80 * j] )
            {
              result = 32 * j;
              byte_50ACD7[32 * j] = 1;
            }
            if ( !dword_4F8068[j] && byte_4F77C0[80 * j] )
              byte_50ACD8[32 * j] = 1;
            if ( !dword_4F80A8[j] && byte_4F77C1[80 * j] )
              byte_50ACD9[32 * j] = 1;
            if ( !dword_4F80E8[j] && byte_4F77C2[80 * j] )
            {
              result = 32 * j;
              byte_50ACDA[32 * j] = 1;
            }
            if ( !dword_4F8128[j] && byte_4F77C3[80 * j] )
              byte_50ACDB[32 * j] = 1;
            if ( !dword_4F8168[j] && byte_4F77C4[80 * j] )
              byte_50ACDC[32 * j] = 1;
            if ( !dword_4F81A8[j] && byte_4F77C5[80 * j] )
            {
              result = 32 * j;
              byte_50ACDD[32 * j] = 1;
            }
            if ( !dword_4F81E8[j] && byte_4F77C6[80 * j] )
              byte_50ACDE[32 * j] = 1;
            if ( !dword_4F8228[j] && byte_4F77C7[80 * j] )
              byte_50ACDF[32 * j] = 1;
            v7 = dword_4F77A8[20 * j];
            if ( v7 > 0x4650 )
            {
              switch ( v7 )
              {
                case 0x57E4u:
                  result = (int)&byte_50ABC0[32 * j];
                  *(_BYTE *)(result + 386) = 1;
                  *(_BYTE *)(result + 387) = 1;
                  break;
                case 0x6978u:
                  byte_50AD43[32 * j] = 1;
                  break;
                case 0x7B0Cu:
                  result = 32 * j;
                  byte_50AD43[32 * j] = 1;
                  *v9 = 1;
                  break;
              }
            }
            else if ( v7 == 18000 )
            {
              byte_50AD42[32 * j] = 1;
            }
            else if ( v7 > 0x2328 )
            {
              if ( v7 == 13500 )
              {
                result = (int)&byte_50ABC0[32 * j];
                *(_BYTE *)(result + 385) = 1;
                *(_BYTE *)(result + 386) = 1;
              }
            }
            else if ( v7 == 9000 )
            {
              result = 32 * j;
              byte_50AD41[32 * j] = 1;
            }
            else if ( v7 )
            {
              if ( v7 == 4500 )
              {
                result = (int)&byte_50AD40[32 * j];
                *v9 = 1;
                byte_50AD41[32 * j] = 1;
              }
            }
            else
            {
              *v9 = 1;
            }
          }
          else
          {
            v8 = &byte_50AD40[32 * j];
            do
            {
              v8[result - 128] = 0;
              v8[result++] = 0;
            }
            while ( result < 32 );
          }
        }
      }
    }
  }
  return result;
}
