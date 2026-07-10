#include "pch.h"
int __cdecl sub_442711(int a1)
{
  int v1; // eax
  int *v2; // eax

  unk_8B5D00 = HeapCreate(a1 == 0, 0x1000u, 0);
  if ( !unk_8B5D00 )
    return 0;
  v1 = sub_4425C9();
  unk_8B5D04 = v1;
  if ( v1 == 3 )
  {
    v2 = (int *)__sbh_heap_init(1016);
  }
  else
  {
    if ( v1 != 2 )
      return 1;
    v2 = sub_442FBF();
  }
  if ( !v2 )
  {
    HeapDestroy(unk_8B5D00);
    return 0;
  }
  return 1;
}
