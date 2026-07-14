#include "pch.h"
int sub_40F010()
{
  char *v0; // edi
  int i; // esi
  int result; // eax
  int v3; // eax

  v0 = byte_4F7788;
  for ( i = 0; ; ++i )
  {
    result = dword_4F776C[i];
    if ( result )
      break;
LABEL_97:
    v0 += 80;
    if ( (int)v0 >= (int)dword_4F78C8 )
      return result;
  }
  (*(void (__stdcall **)(int))(*(_DWORD *)result + 100))(dword_4F776C[i]);
  if ( (*(int (__stdcall **)(int, int, char *))(*(_DWORD *)dword_4F776C[i] + 36))(dword_4F776C[i], 80, v0) != -2147024866 )
    goto LABEL_8;
  v3 = dword_4F776C[i];
  if ( v3 )
    (*(void (__stdcall **)(int))(*(_DWORD *)v3 + 28))(dword_4F776C[i]);
  result = (*(int (__stdcall **)(int, int, char *))(*(_DWORD *)dword_4F776C[i] + 36))(dword_4F776C[i], 80, v0);
  if ( result >= 0 )
  {
LABEL_8:
    if ( !dword_4F7A68[i] && *(int *)v0 > 0 )
      dword_4F7A68[i] = 1;
    if ( !dword_4F7AA8[i] && *(int *)v0 < 0 )
      dword_4F7AA8[i] = 1;
    if ( !dword_4F7AE8[i] && *((int *)v0 + 1) > 0 )
      dword_4F7AE8[i] = 1;
    if ( !dword_4F7B28[i] && *((int *)v0 + 1) < 0 )
      dword_4F7B28[i] = 1;
    if ( !dword_4F7B68[i] && *((int *)v0 + 2) > 0 )
      dword_4F7B68[i] = 1;
    if ( !dword_4F7BA8[i] && *((int *)v0 + 2) < 0 )
      dword_4F7BA8[i] = 1;
    if ( !dword_4F7C68[i] && *((int *)v0 + 4) > 0 )
      dword_4F7C68[i] = 1;
    if ( !dword_4F7CA8[i] && *((int *)v0 + 4) < 0 )
      dword_4F7CA8[i] = 1;
    if ( !dword_4F7CE8[i] && *((int *)v0 + 5) > 0 )
      dword_4F7CE8[i] = 1;
    if ( !dword_4F7D28[i] && *((int *)v0 + 5) < 0 )
      dword_4F7D28[i] = 1;
    if ( !dword_4F7D68[i] && *((int *)v0 + 6) > 0 )
      dword_4F7D68[i] = 1;
    if ( !dword_4F7DA8[i] && *((int *)v0 + 6) < 0 )
      dword_4F7DA8[i] = 1;
    if ( !dword_4F7DE8[i] && *((int *)v0 + 7) > 0 )
      dword_4F7DE8[i] = 1;
    if ( !dword_4F7E28[i] && *((int *)v0 + 7) < 0 )
      dword_4F7E28[i] = 1;
    if ( !dword_4F7E68[i] && v0[48] )
      dword_4F7E68[i] = 1;
    if ( !dword_4F7EA8[i] && v0[49] )
      dword_4F7EA8[i] = 1;
    if ( !dword_4F7EE8[i] && v0[50] )
      dword_4F7EE8[i] = 1;
    if ( !dword_4F7F28[i] && v0[51] )
      dword_4F7F28[i] = 1;
    if ( !dword_4F7F68[i] && v0[52] )
      dword_4F7F68[i] = 1;
    if ( !dword_4F7FA8[i] && v0[53] )
      dword_4F7FA8[i] = 1;
    if ( !dword_4F7FE8[i] && v0[54] )
      dword_4F7FE8[i] = 1;
    if ( !dword_4F8028[i] && v0[55] )
      dword_4F8028[i] = 1;
    if ( !dword_4F8068[i] && v0[56] )
      dword_4F8068[i] = 1;
    if ( !dword_4F80A8[i] && v0[57] )
      dword_4F80A8[i] = 1;
    if ( !dword_4F80E8[i] && v0[58] )
      dword_4F80E8[i] = 1;
    if ( !dword_4F8128[i] && v0[59] )
      dword_4F8128[i] = 1;
    if ( !dword_4F8168[i] && v0[60] )
      dword_4F8168[i] = 1;
    if ( !dword_4F81A8[i] && v0[61] )
      dword_4F81A8[i] = 1;
    if ( !dword_4F81E8[i] && v0[62] )
      dword_4F81E8[i] = 1;
    result = dword_4F8228[i];
    if ( !result )
    {
      result = (unsigned __int8)v0[63];
      if ( (_BYTE)result )
        dword_4F8228[i] = 1;
    }
    goto LABEL_97;
  }
  return result;
}
