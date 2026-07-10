#include "pch.h"
void __cdecl sub_43FA19(LPVOID lpMem)
{
  LPVOID v1; // esi
  int block; // eax
  int v3; // eax
  void *v4; // [esp-4h] [ebp-Ch]
  int v5; // [esp+4h] [ebp-4h] BYREF

  v1 = lpMem;
  if ( lpMem )
  {
    if ( unk_8B5D04 == 3 )
    {
      block = __sbh_find_block(lpMem);
      v4 = v1;
      if ( block )
      {
        sub_4427E1(block, v1);
        return;
      }
    }
    else
    {
      if ( unk_8B5D04 == 2 )
      {
        v3 = sub_44321B(lpMem, &v5, &lpMem);
        if ( v3 )
        {
          sub_443272(v5, lpMem, v3);
          return;
        }
      }
      v4 = v1;
    }
    HeapFree(unk_8B5D00, 0, v4);
  }
}
