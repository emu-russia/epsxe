#include "pch.h"
char __cdecl sub_44259C(int a1)
{
  HMODULE ModuleHandleA; // eax
  int v2; // ecx

  *(_DWORD *)a1 = 0;
  ModuleHandleA = GetModuleHandleA(nullptr);
  if ( *(_WORD *)ModuleHandleA == 23117 )
  {
    v2 = *((_DWORD *)ModuleHandleA + 15);
    if ( v2 )
    {
      ModuleHandleA = (HMODULE)((char *)ModuleHandleA + v2);
      *(_BYTE *)a1 = *((_BYTE *)ModuleHandleA + 26);
      LOBYTE(ModuleHandleA) = *((_BYTE *)ModuleHandleA + 27);
      *(_BYTE *)(a1 + 1) = (_BYTE)ModuleHandleA;
    }
  }
  return (char)ModuleHandleA;
}
