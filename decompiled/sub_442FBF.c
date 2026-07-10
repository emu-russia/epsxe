#include "pch.h"
int *sub_442FBF()
{
  int *v0; // esi
  _DWORD *v1; // eax
  _DWORD *v2; // edi
  int *v3; // eax
  int v4; // ebp
  int v5; // edx

  if ( dword_458ED0 == -1 )
  {
    v0 = (int *)&off_458EC0;
  }
  else
  {
    v0 = (int *)HeapAlloc(unk_8B5D00, 0, 0x2020u);
    if ( !v0 )
      return nullptr;
  }
  v1 = VirtualAlloc(nullptr, 0x400000u, 0x2000u, 4u);
  v2 = v1;
  if ( !v1 )
  {
LABEL_19:
    if ( v0 != (int *)&off_458EC0 )
      HeapFree(unk_8B5D00, 0, v0);
    return nullptr;
  }
  if ( !VirtualAlloc(v1, 0x10000u, 0x1000u, 4u) )
  {
    VirtualFree(v2, 0, 0x8000u);
    goto LABEL_19;
  }
  if ( v0 == (int *)&off_458EC0 )
  {
    if ( !off_458EC0 )
      off_458EC0 = &off_458EC0;
    if ( !off_458EC4 )
      off_458EC4 = &off_458EC0;
  }
  else
  {
    *v0 = (int)&off_458EC0;
    v0[1] = (int)off_458EC4;
    off_458EC4 = v0;
    *(_DWORD *)v0[1] = v0;
  }
  v0[5] = (int)(v2 + 0x100000);
  v3 = v0 + 6;
  v0[3] = (int)(v0 + 38);
  v0[4] = (int)v2;
  v0[2] = (int)(v0 + 6);
  v4 = 0;
  do
  {
    v5 = v4++ >= 16 ? -1 : 240;
    *v3 = v5;
    v3[1] = 241;
    v3 += 2;
  }
  while ( v4 < 1024 );
  memset(v2, 0, 0x10000u);
  while ( (unsigned int)v2 < v0[4] + 0x10000 )
  {
    *((_BYTE *)v2 + 248) = -1;
    *v2 = v2 + 2;
    v2[1] = 240;
    v2 += 1024;
  }
  return v0;
}
