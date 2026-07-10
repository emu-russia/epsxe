#include "pch.h"
_UNKNOWN **__cdecl sub_443103(LPVOID *lpMem)
{
  _UNKNOWN **result; // eax

  result = (_UNKNOWN **)VirtualFree(lpMem[4], 0, 0x8000u);
  if ( off_45AEE0 == (_UNKNOWN **)lpMem )
  {
    result = (_UNKNOWN **)lpMem[1];
    off_45AEE0 = result;
  }
  if ( lpMem == (LPVOID *)&off_458EC0 )
  {
    dword_458ED0 = -1;
  }
  else
  {
    *(_DWORD *)lpMem[1] = *lpMem;
    *((_DWORD *)*lpMem + 1) = lpMem[1];
    return (_UNKNOWN **)HeapFree(unk_8B5D00, 0, lpMem);
  }
  return result;
}
