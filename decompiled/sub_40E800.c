#include "pch.h"
int __userpurge sub_40E800@<eax>(int a1@<ebp>, _DWORD *a2, int a3)
{
  int v3; // edx
  int i; // eax
  int *v6; // eax
  int v7; // ecx
  int v8; // eax
  int v9; // eax
  bool v10; // sf
  int v11; // eax
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
  int v35; // ecx
  int *v36; // eax
  int v37; // eax
  int v38; // ebp
  char *v39; // [esp+C4h] [ebp-64h]
  _DWORD v40[4]; // [esp+D8h] [ebp-50h] BYREF
  int v41; // [esp+E8h] [ebp-40h] BYREF
  int v42; // [esp+ECh] [ebp-3Ch]
  int v43; // [esp+F0h] [ebp-38h]
  int v44; // [esp+F4h] [ebp-34h]
  int v45; // [esp+F8h] [ebp-30h]
  _DWORD v46[5]; // [esp+FCh] [ebp-2Ch] BYREF
  int v47; // [esp+110h] [ebp-18h] BYREF
  _DWORD v48[2]; // [esp+114h] [ebp-14h] BYREF
  int v49; // [esp+11Ch] [ebp-Ch]
  int v50; // [esp+120h] [ebp-8h]
  int v51; // [esp+124h] [ebp-4h]
  int v52; // [esp+12Ch] [ebp+4h]

  v3 = a2[2];
  v40[0] = a2[1];
  v40[2] = a2[3];
  v40[1] = v3;
  v40[3] = a2[4];
  v52 = -1;
  if ( (unsigned int)dword_4F82E8 <= 3 )
  {
    for ( i = 0; i < 4; ++i )
    {
      if ( dword_4FD8AC[i] == dword_4F82E8 + 1 )
        v52 = i;
    }
    if ( !(*(int (__stdcall **)(int, _DWORD *, void *, int, _DWORD))(*(_DWORD *)a3 + 36))(
            a3,
            v40,
            &unk_448500,
            4 * dword_4F82E8 + 5207916,
            0) )
    {
      if ( (*(int (__stdcall **)(int, void *))(*(_DWORD *)dword_4F776C[dword_4F82E8] + 44))(
             dword_4F776C[dword_4F82E8],
             &unk_448728)
        || ((v6 = (int *)dword_4F776C[dword_4F82E8], v7 = *v6, v52 == -1)
          ? (v8 = (*(int (__stdcall **)(int *, int, int))(v7 + 52))(v6, dword_4F7A60, 6))
          : (v8 = (*(int (__stdcall **)(int *, int, int))(v7 + 52))(v6, dword_4F7A60, 5)),
            v8) )
      {
        (*(void (__stdcall **)(int))(*(_DWORD *)dword_4F776C[dword_4F82E8] + 8))(dword_4F776C[dword_4F82E8]);
        return 1;
      }
      v9 = dword_4F776C[dword_4F82E8];
      v47 = 24;
      v48[0] = 16;
      v48[1] = 0;
      v49 = 1;
      v50 = -128;
      v51 = 127;
      v10 = (*(int (__stdcall **)(int, int, int *, int))(*(_DWORD *)v9 + 24))(v9, 4, &v47, a1) < 0;
      v11 = dword_4F82E8;
      if ( v10 )
      {
        dword_4F7A68[dword_4F82E8] = 1;
        dword_4F7AA8[v11] = 1;
      }
      v12 = dword_4F776C[v11];
      v49 = 4;
      v10 = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v12 + 24))(v12, 4, v48) < 0;
      v13 = dword_4F82E8;
      if ( v10 )
      {
        dword_4F7AE8[dword_4F82E8] = 1;
        dword_4F7B28[v13] = 1;
      }
      v14 = dword_4F776C[v13];
      v49 = 8;
      v10 = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v14 + 24))(v14, 4, v48) < 0;
      v15 = dword_4F82E8;
      if ( v10 )
      {
        dword_4F7B68[dword_4F82E8] = 1;
        dword_4F7BA8[v15] = 1;
      }
      v16 = dword_4F776C[v15];
      v49 = 12;
      v10 = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v16 + 24))(v16, 4, v48) < 0;
      v17 = dword_4F82E8;
      if ( v10 )
      {
        dword_4F7BE8[dword_4F82E8] = 1;
        dword_4F7C28[v17] = 1;
      }
      v18 = dword_4F776C[v17];
      v49 = 16;
      v10 = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v18 + 24))(v18, 4, v48) < 0;
      v19 = dword_4F82E8;
      if ( v10 )
      {
        dword_4F7C68[dword_4F82E8] = 1;
        dword_4F7CA8[v19] = 1;
      }
      v20 = dword_4F776C[v19];
      v49 = 20;
      v10 = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v20 + 24))(v20, 4, v48) < 0;
      v21 = dword_4F82E8;
      if ( v10 )
      {
        dword_4F7CE8[dword_4F82E8] = 1;
        dword_4F7D28[v21] = 1;
      }
      v22 = dword_4F776C[v21];
      v49 = 24;
      v10 = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v22 + 24))(v22, 4, v48) < 0;
      v23 = dword_4F82E8;
      if ( v10 )
      {
        dword_4F7D68[dword_4F82E8] = 1;
        dword_4F7DA8[v23] = 1;
      }
      v24 = dword_4F776C[v23];
      v49 = 28;
      v10 = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v24 + 24))(v24, 4, v48) < 0;
      v25 = dword_4F82E8;
      if ( v10 )
      {
        dword_4F7DE8[dword_4F82E8] = 1;
        dword_4F7E28[v25] = 1;
      }
      v26 = dword_4F776C[v25];
      v42 = 20;
      v43 = 16;
      v45 = 1;
      v46[0] = 2500;
      v44 = 0;
      (*(void (__stdcall **)(int, int))(*(_DWORD *)v26 + 24))(v26, 5);
      v27 = dword_4F776C[dword_4F82E8];
      v43 = 4;
      (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)v27 + 24))(v27, 5, &v41);
      v28 = dword_4F776C[dword_4F82E8];
      v43 = 8;
      (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)v28 + 24))(v28, 5, &v41);
      v29 = dword_4F776C[dword_4F82E8];
      v43 = 12;
      (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)v29 + 24))(v29, 5, &v41);
      v30 = dword_4F776C[dword_4F82E8];
      v43 = 16;
      (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)v30 + 24))(v30, 5, &v41);
      v31 = dword_4F776C[dword_4F82E8];
      v43 = 20;
      (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)v31 + 24))(v31, 5, &v41);
      v32 = dword_4F776C[dword_4F82E8];
      v43 = 24;
      (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)v32 + 24))(v32, 5, &v41);
      v33 = dword_4F776C[dword_4F82E8];
      v43 = 28;
      (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)v33 + 24))(v33, 5, &v41);
      v41 = 20;
      v42 = 16;
      v44 = 0;
      v45 = 0;
      v43 = 0;
      (*(void (__stdcall **)(int, int, int *))(*(_DWORD *)dword_4F776C[dword_4F82E8] + 24))(
        dword_4F776C[dword_4F82E8],
        2,
        &v41);
      if ( v52 != -1 )
      {
        v34 = dword_4F776C[dword_4F82E8];
        v46[0] = 20;
        v46[1] = 16;
        memset(&v46[2], 0, 12);
        (*(void (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v34 + 24))(v34, 9, v46);
        v35 = dword_4F82E8;
        v36 = &dword_4F78C8[25 * dword_4F82E8];
        v39 = (char *)&byte_4F75D0 + 100 * dword_4F82E8;
        dword_4F82F8[dword_4F82E8] = (int)v39;
        dword_4F8308[v35] = (int)v36;
        sub_40E700(v39);
        sub_40E700(dword_4F8308[dword_4F82E8]);
        *(_DWORD *)(dword_4F82F8[dword_4F82E8] + 24) = 100 * dword_44F888;
        *(_DWORD *)(dword_4F8308[dword_4F82E8] + 24) = 100 * dword_44F888;
        v37 = dword_4FD8CC[v52];
        if ( v37 == 1 )
        {
          sub_40E460(dword_4F82F8[dword_4F82E8], dword_4F776C[dword_4F82E8]);
        }
        else if ( v37 == 2 )
        {
          sub_40E510(dword_4F82F8[dword_4F82E8], dword_4F776C[dword_4F82E8]);
        }
        v38 = dword_4FD8BC[v52];
        if ( v38 == 1 )
        {
          sub_40E460(dword_4F8308[dword_4F82E8], dword_4F776C[dword_4F82E8]);
        }
        else if ( v38 == 2 )
        {
          sub_40E510(dword_4F8308[dword_4F82E8], dword_4F776C[dword_4F82E8]);
        }
      }
      ++dword_4F82E8;
    }
  }
  return 1;
}
