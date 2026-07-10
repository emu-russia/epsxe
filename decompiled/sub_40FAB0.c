#include "pch.h"
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
  while ( (int)v0 < (int)&unk_4F777C );
  result = (*(int (__stdcall **)(int))(*(_DWORD *)dword_4F7768 + 8))(dword_4F7768);
  dword_4F7768 = 0;
  dword_4F82E8 = 0;
  return result;
}
