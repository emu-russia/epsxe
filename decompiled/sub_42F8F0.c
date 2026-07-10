#include "pch.h"
void *__cdecl sub_42F8F0(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3, void *Buffer)
{
  int v4; // esi
  void *result; // eax

  v4 = sub_42C6D0(a1, a2, a3);
  if ( !a1 && a2 == 2 && a3 == 18 )
    printf("saved \n");
  result = dword_50A1A0;
  if ( *((_DWORD *)dword_50A1A0 + v4) == -1 )
  {
    fwrite(Buffer, 1u, 0x930u, FileHandle);
    *((_DWORD *)dword_50A1A0 + v4) = dword_5056E0;
    result = (void *)(dword_5056E0 + 2352);
    dword_5056E0 += 2352;
  }
  return result;
}
