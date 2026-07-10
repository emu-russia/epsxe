#include "pch.h"
int __cdecl sub_438BF0(LPVOID lpMem)
{
  int v1; // edi
  char v3; // al
  int v4; // eax

  v1 = 0;
  if ( !lpMem )
    return -2;
  if ( *((_DWORD *)lpMem + 20) )
    free(*((LPVOID *)lpMem + 20));
  if ( *((_DWORD *)lpMem + 7) )
  {
    v3 = *((_BYTE *)lpMem + 92);
    if ( v3 == 119 )
    {
      v4 = sub_43A510(lpMem);
    }
    else
    {
      if ( v3 != 114 )
        goto LABEL_11;
      v4 = sub_4395F0(lpMem);
    }
    v1 = v4;
  }
LABEL_11:
  if ( *((_DWORD *)lpMem + 16) && fclose(*((FILE **)lpMem + 16)) && dword_4FFA10 != 29 )
    v1 = -1;
  if ( *((int *)lpMem + 14) < 0 )
    v1 = *((_DWORD *)lpMem + 14);
  if ( *((_DWORD *)lpMem + 17) )
    free(*((LPVOID *)lpMem + 17));
  if ( *((_DWORD *)lpMem + 18) )
    free(*((LPVOID *)lpMem + 18));
  if ( *((_DWORD *)lpMem + 21) )
    free(*((LPVOID *)lpMem + 21));
  free(lpMem);
  return v1;
}
