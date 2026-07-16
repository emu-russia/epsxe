#include "pch.h"
int sub_40E800(int a1, _DWORD *a2, int a3)
{
  int v3; // ebp
  int v4; // edx
  int i; // eax
  int *v7; // eax
  int v8; // ecx
  int v9; // eax
  int v10; // eax
  bool v11; // sf
  int v12; // eax
  int v13; // eax
  int v14; // eax
  int v15; // eax
  int v16; // eax
  int v17; // eax
  int v18; // eax
  int v19; // eax
  int v20; // eax
  int v21; // eax
  int v22; // eax
  int v23; // eax
  int v24; // eax
  int v25; // eax
  int v26; // eax
  int v27; // eax
  int v28; // eax
  int v29; // eax
  int v30; // eax
  int v31; // eax
  int v32; // eax
  int v33; // eax
  int v34; // eax
  int v35; // eax
  int v36; // ecx
  int *v37; // eax
  int v38; // eax
  int v39; // ebp
  char *v40; // [esp+C4h] [ebp-64h]
  _DWORD v41[4]; // [esp+D8h] [ebp-50h] BYREF
  int v42; // [esp+E8h] [ebp-40h] BYREF
  int v43; // [esp+ECh] [ebp-3Ch]
  int v44; // [esp+F0h] [ebp-38h]
  int v45; // [esp+F4h] [ebp-34h]
  int v46; // [esp+F8h] [ebp-30h]
  _DWORD v47[5]; // [esp+FCh] [ebp-2Ch] BYREF
  int v48; // [esp+110h] [ebp-18h] BYREF
  _DWORD v49[2]; // [esp+114h] [ebp-14h] BYREF
  int v50; // [esp+11Ch] [ebp-Ch]
  int v51; // [esp+120h] [ebp-8h]
  int v52; // [esp+124h] [ebp-4h]
  int a1a; // [esp+12Ch] [ebp+4h]

  v4 = *(_DWORD *)(a1 + 8);
  v41[0] = *(_DWORD *)(a1 + 4);
  v41[2] = *(_DWORD *)(a1 + 12);
  v41[1] = v4;
  v41[3] = *(_DWORD *)(a1 + 16);
  a1a = -1;
  if ( (unsigned int)dword_4F82E8 <= 3 )
  {
    for ( i = 0; i < 4; ++i )
    {
      if ( dword_4FD8AC[i] == dword_4F82E8 + 1 )
        a1a = i;
    }
    if ( !(*(int (__stdcall **)(_DWORD *, _DWORD *, char *, int, _DWORD))(*a2 + 36))(
            a2,
            v41,
            &byte_448500,
            4 * dword_4F82E8 + 5207916,
            0) )
    {
      if ( (*(int (__stdcall **)(int, char *))(*(_DWORD *)dword_4F776C[dword_4F82E8] + 44))(
             dword_4F776C[dword_4F82E8],
             &byte_448728)
        || ((v7 = (int *)dword_4F776C[dword_4F82E8], v8 = *v7, a1a == -1)
          ? (v9 = (*(int (__stdcall **)(int *, int, int))(v8 + 52))(v7, hDlgInput, 6))
          : (v9 = (*(int (__stdcall **)(int *, int, int))(v8 + 52))(v7, hDlgInput, 5)),
            v9) )
      {
        (*(void (__stdcall **)(int))(*(_DWORD *)dword_4F776C[dword_4F82E8] + 8))(dword_4F776C[dword_4F82E8]);
        return 1;
      }
      v10 = dword_4F776C[dword_4F82E8];
      v48 = 24;
      v49[0] = 16;
      v49[1] = 0;
      v50 = 1;
      v51 = -128;
      v52 = 127;
      v11 = (*(int (__stdcall **)(int, int, int *, int))(*(_DWORD *)v10 + 24))(v10, 4, &v48, v3) < 0;
      v12 = dword_4F82E8;
      if ( v11 )
      {
        dword_4F7A68[dword_4F82E8] = 1;
        dword_4F7AA8[v12] = 1;
      }
      v13 = dword_4F776C[v12];
      v50 = 4;
      v11 = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v13 + 24))(v13, 4, v49) < 0;
      v14 = dword_4F82E8;
      if ( v11 )
      {
        dword_4F7AE8[dword_4F82E8] = 1;
        dword_4F7B28[v14] = 1;
      }
      v15 = dword_4F776C[v14];
      v50 = 8;
      v11 = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v15 + 24))(v15, 4, v49) < 0;
      v16 = dword_4F82E8;
      if ( v11 )
      {
        dword_4F7B68[dword_4F82E8] = 1;
        dword_4F7BA8[v16] = 1;
      }
      v17 = dword_4F776C[v16];
      v50 = 12;
      v11 = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v17 + 24))(v17, 4, v49) < 0;
      v18 = dword_4F82E8;
      if ( v11 )
      {
        dword_4F7BE8[dword_4F82E8] = 1;
        dword_4F7C28[v18] = 1;
      }
      v19 = dword_4F776C[v18];
      v50 = 16;
      v11 = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v19 + 24))(v19, 4, v49) < 0;
      v20 = dword_4F82E8;
      if ( v11 )
      {
        dword_4F7C68[dword_4F82E8] = 1;
        dword_4F7CA8[v20] = 1;
      }
      v21 = dword_4F776C[v20];
      v50 = 20;
      v11 = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v21 + 24))(v21, 4, v49) < 0;
      v22 = dword_4F82E8;
      if ( v11 )
      {
        dword_4F7CE8[dword_4F82E8] = 1;
        dword_4F7D28[v22] = 1;
      }
      v23 = dword_4F776C[v22];
      v50 = 24;
      v11 = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v23 + 24))(v23, 4, v49) < 0;
      v24 = dword_4F82E8;
      if ( v11 )
      {
        dword_4F7D68[dword_4F82E8] = 1;
        dword_4F7DA8[v24] = 1;
      }
      v25 = dword_4F776C[v24];
      v50 = 28;
      v11 = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v25 + 24))(v25, 4, v49) < 0;
      v26 = dword_4F82E8;
      if ( v11 )
      {
        dword_4F7DE8[dword_4F82E8] = 1;
        dword_4F7E28[v26] = 1;
      }
      v27 = dword_4F776C[v26];
      v43 = 20;
      v44 = 16;
      v46 = 1;
      v47[0] = 2500;
      v45 = 0;
      (*(void (__stdcall **)(int, int))(*(_DWORD *)v27 + 24))(v27, 5);
      v28 = dword_4F776C[dword_4F82E8];
      v44 = 4;
      (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)v28 + 24))(v28, 5, &v42);
      v29 = dword_4F776C[dword_4F82E8];
      v44 = 8;
      (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)v29 + 24))(v29, 5, &v42);
      v30 = dword_4F776C[dword_4F82E8];
      v44 = 12;
      (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)v30 + 24))(v30, 5, &v42);
      v31 = dword_4F776C[dword_4F82E8];
      v44 = 16;
      (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)v31 + 24))(v31, 5, &v42);
      v32 = dword_4F776C[dword_4F82E8];
      v44 = 20;
      (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)v32 + 24))(v32, 5, &v42);
      v33 = dword_4F776C[dword_4F82E8];
      v44 = 24;
      (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)v33 + 24))(v33, 5, &v42);
      v34 = dword_4F776C[dword_4F82E8];
      v44 = 28;
      (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)v34 + 24))(v34, 5, &v42);
      v42 = 20;
      v43 = 16;
      v45 = 0;
      v46 = 0;
      v44 = 0;
      (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)dword_4F776C[dword_4F82E8] + 24))(
        dword_4F776C[dword_4F82E8],
        2,
        &v42);
      if ( a1a != -1 )
      {
        v35 = dword_4F776C[dword_4F82E8];
        v47[0] = 20;
        v47[1] = 16;
        memset(&v47[2], 0, 12);
        (*(void (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v35 + 24))(v35, 9, v47);
        v36 = dword_4F82E8;
        v37 = &dword_4F78C8[25 * dword_4F82E8];
        v40 = &byte_4F75D0[100 * dword_4F82E8];
        dword_4F82F8[dword_4F82E8] = (int)v40;
        dword_4F8308[v36] = (int)v37;
        sub_40E700(v40);
        sub_40E700((_DWORD *)dword_4F8308[dword_4F82E8]);
        *(_DWORD *)(dword_4F82F8[dword_4F82E8] + 24) = 100 * dword_44F888;
        *(_DWORD *)(dword_4F8308[dword_4F82E8] + 24) = 100 * dword_44F888;
        v38 = dword_4FD8CC[a1a];
        if ( v38 == 1 )
        {
          sub_40E460(dword_4F82F8[dword_4F82E8], dword_4F776C[dword_4F82E8]);
        }
        else if ( v38 == 2 )
        {
          sub_40E510((_DWORD *)dword_4F82F8[dword_4F82E8], dword_4F776C[dword_4F82E8]);
        }
        v39 = dword_4FD8BC[a1a];
        if ( v39 == 1 )
        {
          sub_40E460(dword_4F8308[dword_4F82E8], dword_4F776C[dword_4F82E8]);
        }
        else if ( v39 == 2 )
        {
          sub_40E510((_DWORD *)dword_4F8308[dword_4F82E8], dword_4F776C[dword_4F82E8]);
        }
      }
      ++dword_4F82E8;
    }
  }
  return 1;
}
