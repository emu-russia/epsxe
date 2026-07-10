#include "pch.h"
void *__cdecl sub_4406FF(size_t Size, int a2)
{
  size_t v2; // esi
  void *v3; // edi
  size_t Sizea; // [esp+10h] [ebp+8h]

  v2 = a2 * Size;
  Sizea = a2 * Size;
  if ( Sizea <= 0xFFFFFFE0 )
  {
    if ( !v2 )
      v2 = 1;
    v2 = (v2 + 15) & 0xFFFFFFF0;
  }
  do
  {
    v3 = nullptr;
    if ( v2 > 0xFFFFFFE0 )
      goto LABEL_14;
    if ( unk_8B5D04 == 3 )
    {
      if ( Sizea > unk_8B5CFC )
        goto LABEL_13;
      v3 = (void *)__sbh_alloc_block(Sizea);
      if ( !v3 )
        goto LABEL_13;
      memset(v3, 0, Sizea);
      return v3;
    }
    if ( unk_8B5D04 == 2 && v2 <= dword_45AEE4 )
    {
      v3 = (void *)sub_4432B7(v2 >> 4);
      if ( v3 )
      {
        memset(v3, 0, v2);
        return v3;
      }
    }
LABEL_13:
    v3 = HeapAlloc(unk_8B5D00, 8u, v2);
    if ( v3 )
      return v3;
LABEL_14:
    if ( !dword_4FFA8C )
      return v3;
  }
  while ( _callnewh(v2) );
  return nullptr;
}
