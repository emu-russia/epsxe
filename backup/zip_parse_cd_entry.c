int __cdecl sub_420A00(unsigned __int8 *a1, int a2)
{
  int result; // eax

  *(_DWORD *)a2 = sub_420CC0(a1);
  *(_BYTE *)(a2 + 4) = a1[4];
  *(_BYTE *)(a2 + 5) = a1[5];
  *(_BYTE *)(a2 + 6) = a1[6];
  *(_BYTE *)(a2 + 7) = a1[7];
  *(_WORD *)(a2 + 8) = sub_420CB0((int)(a1 + 8));
  *(_WORD *)(a2 + 10) = sub_420CB0((int)(a1 + 10));
  *(_WORD *)(a2 + 12) = sub_420CB0((int)(a1 + 12));
  *(_WORD *)(a2 + 14) = sub_420CB0((int)(a1 + 14));
  *(_DWORD *)(a2 + 16) = sub_420CC0(a1 + 16);
  *(_DWORD *)(a2 + 20) = sub_420CC0(a1 + 20);
  *(_DWORD *)(a2 + 24) = sub_420CC0(a1 + 24);
  *(_WORD *)(a2 + 28) = sub_420CB0((int)(a1 + 28));
  *(_WORD *)(a2 + 30) = sub_420CB0((int)(a1 + 30));
  *(_WORD *)(a2 + 32) = sub_420CB0((int)(a1 + 32));
  *(_WORD *)(a2 + 34) = sub_420CB0((int)(a1 + 34));
  *(_WORD *)(a2 + 36) = sub_420CB0((int)(a1 + 36));
  *(_DWORD *)(a2 + 40) = sub_420CC0(a1 + 38);
  result = sub_420CC0(a1 + 42);
  *(_DWORD *)(a2 + 48) = a1 + 46;
  *(_DWORD *)(a2 + 44) = result;
  return result;
}

__int16 __cdecl sub_420CB0(int a1)
{
  return *(_WORD *)a1;
}

int __cdecl sub_420CC0(unsigned __int8 *a1)
{
  return *a1 | ((a1[1] | (*((unsigned __int16 *)a1 + 1) << 8)) << 8);
}