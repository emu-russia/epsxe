#include "pch.h"
LPVOID __cdecl sub_43FBA8(unsigned int a1)
{
  int v1; // esi
  LPVOID result; // eax
  SIZE_T v3; // esi

  v1 = a1;
  if ( unk_8B5D04 == 3 )
  {
    if ( a1 <= unk_8B5CFC )
    {
      result = (LPVOID)__sbh_alloc_block(a1);
      if ( result )
        return result;
    }
    goto LABEL_12;
  }
  if ( unk_8B5D04 != 2 )
  {
LABEL_12:
    if ( !a1 )
      v1 = 1;
    v3 = (v1 + 15) & 0xFFFFFFF0;
    return HeapAlloc(unk_8B5D00, 0, v3);
  }
  if ( a1 )
    v3 = (a1 + 15) & 0xFFFFFFF0;
  else
    v3 = 16;
  if ( v3 > dword_45AEE4 )
    return HeapAlloc(unk_8B5D00, 0, v3);
  result = (LPVOID)sub_4432B7(v3 >> 4);
  if ( !result )
    return HeapAlloc(unk_8B5D00, 0, v3);
  return result;
}
