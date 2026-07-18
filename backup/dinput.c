int sub_40E1D0()
{
  if ( dword_4F776C[0] )
    (*(void (__stdcall **)(int))(*(_DWORD *)dword_4F776C[0] + 28))(dword_4F776C[0]);
  if ( dword_4F7770 )
    (*(void (__stdcall **)(int))(*(_DWORD *)dword_4F7770 + 28))(dword_4F7770);
  if ( dword_4F7774 )
    (*(void (__stdcall **)(int))(*(_DWORD *)dword_4F7774 + 28))(dword_4F7774);
  if ( dword_4F7778 )
    (*(void (__stdcall **)(int))(*(_DWORD *)dword_4F7778 + 28))(dword_4F7778);
  if ( dword_4F75C8 )
    (*(void (__stdcall **)(int))(*(_DWORD *)dword_4F75C8 + 28))(dword_4F75C8);
  if ( dword_4F7A5C )
    (*(void (__stdcall **)(int))(*(_DWORD *)dword_4F7A5C + 28))(dword_4F7A5C);
  dword_4F82EC = 1;
  return 1;
}

int sub_40E240()
{
  if ( dword_4F75C8 && point_device_enabled )
    (*(void (__stdcall **)(int))(*(_DWORD *)dword_4F75C8 + 32))(dword_4F75C8);
  if ( dword_4F7A5C )
    (*(void (__stdcall **)(int))(*(_DWORD *)dword_4F7A5C + 32))(dword_4F7A5C);
  if ( dword_4F776C[0] )
    (*(void (__stdcall **)(int))(*(_DWORD *)dword_4F776C[0] + 32))(dword_4F776C[0]);
  if ( dword_4F7770 )
    (*(void (__stdcall **)(int))(*(_DWORD *)dword_4F7770 + 32))(dword_4F7770);
  if ( dword_4F7774 )
    (*(void (__stdcall **)(int))(*(_DWORD *)dword_4F7774 + 32))(dword_4F7774);
  if ( dword_4F7778 )
    (*(void (__stdcall **)(int))(*(_DWORD *)dword_4F7778 + 32))(dword_4F7778);
  dword_4F82EC = 0;
  return 1;
}

int sub_40E2C0()
{
  if ( dword_4F75C8 && point_device_enabled )
    (*(void (__stdcall **)(int))(*(_DWORD *)dword_4F75C8 + 28))(dword_4F75C8);
  return 1;
}

int sub_40E2E0()
{
  int v1; // eax
  int v2; // eax
  _DWORD v3[3]; // [esp+Ch] [ebp-14h] BYREF
  _BYTE v4[8]; // [esp+18h] [ebp-8h]

  if ( !point_device_enabled )
    return 0;
  v1 = dword_4F75C8;
  dword_4F82F0 = 0;
  dword_4F82F4[0] = 0;
  if ( dword_4F75C8 && dword_4F82EC == 1 )
  {
    while ( 1 )
    {
      v2 = (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)v1 + 36))(v1, 16, v3);
      if ( v2 != DIERR_INPUTLOST )
        break;
      if ( (*(int (__stdcall **)(int))(*(_DWORD *)dword_4F75C8 + 28))(dword_4F75C8) < 0 )
        return 0;
      v1 = dword_4F75C8;
    }
    if ( v2 < 0 )
      return 0;
    dword_4F82F0 = 3 * v3[0];
    dword_4F82F4[0] = 3 * v3[1];
    dword_4F7784 = (v4[3] | ((v4[2] | ((unsigned int)(v4[1] | (v4[0] >> 1)) >> 1)) >> 1)) >> 4;
  }
  return 1;
}

int __stdcall sub_40E3C0(_DWORD *a1, _DWORD *a2)
{
  if ( a2 )
  {
    *a2 = a1[1];
    a2[1] = a1[2];
    a2[2] = a1[3];
    a2[3] = a1[4];
  }
  return 0;
}

unsigned int __cdecl sub_40E3F0(int a1, _DWORD *a2)
{
  int v3; // [esp+8h] [ebp-1Ch]
  _BYTE v4[16]; // [esp+14h] [ebp-10h] BYREF

  if ( *a2 )
    (*(void (__stdcall **)(_DWORD))(*(_DWORD *)*a2 + 8))(*a2);
  v3 = a2[1];
  *a2 = 0;
  if ( (*(int (__stdcall **)(int, int (__stdcall *)(_DWORD *, _DWORD *), _BYTE *, int))(*(_DWORD *)a1 + 76))(
         a1,
         sub_40E3C0,
         v4,
         v3) >= 0 )
    return (*(int (__stdcall **)(int, _BYTE *, _DWORD *, _DWORD *, _DWORD))(*(_DWORD *)a1 + 72))(a1, v4, a2 + 2, a2, 0) >= 0
         ? 0
         : 0x80004005;
  else
    return 0x80004005;
}

unsigned int __cdecl sub_40E460(int a1, int a2)
{
  _DWORD *v2; // eax
  int v3; // edx
  _DWORD v5[2]; // [esp+0h] [ebp-10h] BYREF
  _DWORD v6[2]; // [esp+8h] [ebp-8h] BYREF

  v2 = (_DWORD *)a1;
  if ( !a1 )
    return E_FAIL;
  v3 = a2;
  if ( !a2 )
    return E_FAIL;
  *(_DWORD *)(a1 + 40) = v5;
  v2[5] = 0;
  v2[8] = 0;
  v2[11] = v6;
  v5[0] = 0;
  v6[0] = 0;
  v6[1] = 0;
  v2[12] = 0;
  v2[7] = -1;
  a1 = 10000;
  v5[1] = 4;
  v2[3] = 34;
  v2[4] = 20000;
  v2[9] = 2;
  v2[13] = 4;
  v2[14] = &a1;
  v2[1] = 1;
  return (sub_40E3F0(v3, v2) & 0x80000000) == 0 ? 0 : 0x80004005;
}

unsigned int __cdecl sub_40E510(_DWORD *a1, int a2)
{
  int v3; // [esp+0h] [ebp-20h] BYREF
  int v4; // [esp+8h] [ebp-18h] BYREF
  _DWORD v5[4]; // [esp+10h] [ebp-10h] BYREF

  if ( !a1 || !a2 )
    return E_FAIL;
  a1[5] = 0;
  a1[8] = 0;
  a1[17] = 0;
  a1[18] = 0;
  a1[19] = 0;
  v5[1] = 0;
  v5[2] = 0;
  v3 = 0;
  v4 = 0;
  a1[10] = &v3;
  a1[12] = a1 + 16;
  a1[7] = -1;
  a1[11] = &v4;
  a1[20] = 1000000;
  v5[0] = 10000;
  v5[3] = 100000;
  a1[3] = 18;
  a1[4] = 20000;
  a1[9] = 1;
  a1[13] = 16;
  a1[14] = v5;
  a1[1] = 3;
  return (sub_40E3F0(a2, a1) & 0x80000000) == 0 ? 0 : E_FAIL;
}

int __cdecl sub_40E5E0(int a1, int a2)
{
  _DWORD *v2; // ebx
  int v3; // esi
  _DWORD v5[14]; // [esp+8h] [ebp-38h] BYREF

  v2 = (_DWORD *)a1;
  if ( !a1 )
    return E_INVALIDARG;
  v3 = *(_DWORD *)a1;
  if ( !*(_DWORD *)a1 )
    return E_INVALIDARG;
  memset(v5, 0, sizeof(v5));
  a1 = 10000 * a2 / 255;
  v5[0] = 56;
  v5[11] = 4;
  v5[12] = &a1;
  (*(void (__stdcall **)(int, _DWORD *, int))(*(_DWORD *)v3 + 24))(v3, v5, 256);
  return (*(int (__stdcall **)(_DWORD, int, _DWORD))(*(_DWORD *)*v2 + 28))(*v2, 1, 0);
}

int __cdecl sub_40E670(_DWORD *a1, int a2)
{
  int v2; // esi
  int v4; // [esp+8h] [ebp-48h] BYREF
  _DWORD v5[14]; // [esp+18h] [ebp-38h] BYREF

  if ( !a1 )
    return E_INVALIDARG;
  v2 = *a1;
  if ( !*a1 )
    return E_INVALIDARG;
  memset(v5, 0, sizeof(v5));
  v4 = 10000 * a2 / 255;
  v5[0] = 56;
  v5[11] = 16;
  v5[12] = &v4;
  (*(void (__stdcall **)(int, _DWORD *, int))(*(_DWORD *)v2 + 24))(v2, v5, 256);
  return (*(int (__stdcall **)(_DWORD, int, _DWORD))(*(_DWORD *)*a1 + 28))(*a1, 1, 0);
}

_DWORD *__cdecl sub_40E700(_DWORD *a1)
{
  memset(a1 + 2, 0, 0x38u);
  a1[2] = 56;
  a1[6] = 7500;
  a1[16] = 0;
  a1[17] = 0;
  a1[18] = 0;
  a1[19] = 0;
  a1[20] = 0;
  a1[16] = 20;
  *a1 = 0;
  return a1 + 16;
}

int __cdecl sub_40E750(int a1, int a2, int a3, int a4)
{
  int result; // eax

  if ( a1 )
  {
    result = dword_4FD8CC[a4];
    if ( result == 1 )
    {
      return sub_40E5E0(dword_4F82F4[dword_4FD8AC[a4]], a2);
    }
    else if ( result == 2 )
    {
      return sub_40E670((_DWORD *)dword_4F82F4[dword_4FD8AC[a4]], a2);
    }
  }
  else
  {
    result = dword_4FD8BC[a4];
    if ( result == 1 )
    {
      return sub_40E5E0(dword_4F8304[dword_4FD8AC[a4]], a2);
    }
    else if ( result == 2 )
    {
      return sub_40E670((_DWORD *)dword_4F8304[dword_4FD8AC[a4]], a2);
    }
  }
  return result;
}

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
            &stru_448500,
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

int init_direct_input()
{
  HRESULT hr; // edi
  CHAR Text[256]; // [esp+8h] [ebp-100h] BYREF

  hr = DirectInputCreateA(hInst_For_DInput, 0x700, (int)&dword_4F7768, 0);
  if ( hr >= 0 )
  {
    if ( (*(int (__stdcall **)(int, GUID *, int *, _DWORD))(*(_DWORD *)dword_4F7768 + 12))(
           dword_4F7768,
           &stru_4485E0,
           &dword_4F7A5C,
           0) < 0 )
      return 0;
    if ( (*(int (__stdcall **)(int, char *))(*(_DWORD *)dword_4F7A5C + 44))(dword_4F7A5C, &byte_448758) < 0 )
      return 0;
    (*(void (__stdcall **)(int, int, int))(*(_DWORD *)dword_4F7A5C + 52))(dword_4F7A5C, hDlgInput, 6);
    if ( !point_device_enabled || byte_44DD19 )
      goto LABEL_25;
    if ( (*(int (__stdcall **)(int, GUID *, int *, _DWORD))(*(_DWORD *)dword_4F7768 + 12))(
           dword_4F7768,
           &stru_4485D0,
           &dword_4F75C8,
           0) < 0 )
      return 0;
    if ( (*(int (__stdcall **)(int, char *))(*(_DWORD *)dword_4F75C8 + 44))(dword_4F75C8, &byte_448740) < 0 )
      return 0;
    if ( (*(int (__stdcall **)(int, int, int))(*(_DWORD *)dword_4F75C8 + 52))(dword_4F75C8, hDlgInput, 5) >= 0 )
    {
LABEL_25:
      dword_4F776C[0] = 0;
      dword_4F7770 = 0;
      dword_4F7774 = 0;
      dword_4F7778 = 0;
      (*(void (__stdcall **)(int, int, int (*)(int, _DWORD *, int), int, int))(*(_DWORD *)dword_4F7768 + 16))(
        dword_4F7768,
        4,
        sub_40E800,
        dword_4F7768,
        1);
      if ( (dword_4FD8AC[0] && dword_4FD8AC[0] <= 4u
         || dword_4FD8B0 && (unsigned int)dword_4FD8B0 <= 4
         || dword_4FD8B4 && (unsigned int)dword_4FD8B4 <= 4
         || dword_4FD8B8[0] && dword_4FD8B8[0] <= 4u)
        && (*(int (__stdcall **)(int, int, int (*)(int, _DWORD *, int), int, int))(*(_DWORD *)dword_4F7768 + 16))(
             dword_4F7768,
             4,
             sub_40E800,
             dword_4F7768,
             257) < 0 )
      {
        printf(" * No force-feedback joysticks available. \n");
      }
      sub_40E1D0();
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    sprintf(Text, "Error initializing DirectInput\n");
    MessageBoxA(nullptr, Text, "Init Error", 0x10u);
    if ( hr > DIERR_OLDDIRECTINPUTVERSION )
    {
      if ( hr != DIERR_BETADIRECTINPUTVERSION )
      {
LABEL_10:
        sprintf(Text, "UNKNOWN %X\n", hr);
        MessageBoxA(nullptr, Text, "Init", 0x10u);
        return 0;
      }
      sprintf(Text, "Beta %X\n", DIERR_BETADIRECTINPUTVERSION);
    }
    else
    {
      if ( hr == DIERR_OLDDIRECTINPUTVERSION )
      {
        sprintf(Text, "OLDDIRECTINPUTVERSION %X\n", DIERR_OLDDIRECTINPUTVERSION);
        MessageBoxA(nullptr, Text, "Init", 0x10u);
        return 0;
      }
      if ( hr != DIERR_OUTOFMEMORY )
      {
        if ( hr == DIERR_INVALIDPARAM )
        {
          sprintf(Text, "Invalid %X\n", DIERR_INVALIDPARAM);
          MessageBoxA(nullptr, Text, "Init", 0x10u);
          return 0;
        }
        goto LABEL_10;
      }
      sprintf(Text, "OUTOFMEMORY %X\n", DIERR_OUTOFMEMORY);
    }
    MessageBoxA(nullptr, Text, "Init", 0x10u);
    return 0;
  }
}

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

int sub_40FA30()
{
  int result; // eax

  if ( !point_device_enabled )
    return 0;
  sub_40E2E0();
  result = dword_4F82F0;
  if ( dword_4F82F0 < dword_44F878 )
  {
    result = dword_44F878;
    dword_4F82F0 = dword_44F878;
  }
  if ( result > dword_44F87C )
  {
    dword_4F82F0 = dword_44F87C;
    return dword_44F87C;
  }
  return result;
}

int sub_40FA70()
{
  int result; // eax

  if ( !point_device_enabled )
    return 0;
  result = dword_4F82F4[0];
  if ( dword_4F82F4[0] < dword_44F880 )
  {
    result = dword_44F880;
    dword_4F82F4[0] = dword_44F880;
  }
  if ( result > dword_44F884 )
  {
    dword_4F82F4[0] = dword_44F884;
    return dword_44F884;
  }
  return result;
}

int sub_40FAB0()
{
  int *v0; // esi
  int result; // eax

  sub_40E240();
  if ( dword_4F7A5C )
    (*(void (__stdcall **)(int))(*(_DWORD *)dword_4F7A5C + 8))(dword_4F7A5C);
  dword_4F7A5C = 0;
  v0 = dword_4F776C;
  do
  {
    if ( *v0 )
      (*(void (__stdcall **)(int))(*(_DWORD *)*v0 + 8))(*v0);
    *v0++ = 0;
  }
  while ( (int)v0 < (int)&byte_4F777C );
  result = (*(int (__stdcall **)(int))(*(_DWORD *)dword_4F7768 + 8))(dword_4F7768);
  dword_4F7768 = 0;
  dword_4F82E8 = 0;
  return result;
}

int __cdecl sub_40FB20(int a1)
{
  return word_50AE00[LOWORD(word_4FD88C[2 * a1])];
}

int __cdecl sub_40FB40(int a1)
{
  return word_50AE00[(unsigned __int16)word_4FD88E[4 * a1]];
}

int __cdecl sub_40FB60(int a1)
{
  return word_50AE00[LOWORD(word_4FD890[2 * a1])];
}

int __cdecl sub_40FB80(int a1)
{
  return word_50AE00[(unsigned __int16)word_4FD892[4 * a1]];
}