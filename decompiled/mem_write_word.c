#include "pch.h"
void __cdecl mem_write_word(unsigned int a1, unsigned int a2)
{
  unsigned int v2; // eax
  int v3; // ecx
  LPVOID v4; // edi

  hw_update_counter -= 4;
  if ( (a1 & 0x1FC00000) == 0x1F800000 )
  {
    if ( (unsigned __int16)a1 >= 0x1000u )
      hw_reg_write_word(a1, a2);
    else
      *(_DWORD *)&dcache[a1 & 0xFFF] = a2;
  }
  else if ( (dword_50C2A4 & 0x10000) == 0 )
  {
    *(_DWORD *)((unsigned __int16)a1 + mem_write_hooks[HIWORD(a1)]) = a2;
    if ( recomp_buffer )
    {
      v2 = (a1 & 0xFFF00000) == 0xBFC00000 ? (a1 & 0x7FFFC) + 0x200000 : a1 & 0x1FFFFC;
      if ( *(LPVOID *)((char *)recomp_code_base + v2) != recomp_buffer )
      {
        v3 = ((_BYTE *)recomp_buffer - (_BYTE *)recomp_metadata) >> 2;
        for ( *(_DWORD *)((char *)recomp_code_base + v2) = recomp_buffer;
              v3;
              *(_DWORD *)((char *)recomp_code_base + v2) = recomp_buffer )
        {
          v4 = *(LPVOID *)((char *)recomp_code_base + v2 - 4);
          v2 -= 4;
          if ( v4 == recomp_buffer )
            break;
          --v3;
        }
      }
    }
  }
}
