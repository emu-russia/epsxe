#include "pch.h"
void __cdecl hw_reg_write_byte(unsigned int a1, unsigned __int8 a2)
{
  unsigned int v2; // eax
  int v3; // ecx
  LPVOID v4; // edi

  dword_50C270 -= 4;
  if ( (a1 & 0x1FC00000) == 0x1F800000 )
  {
    if ( (unsigned __int16)a1 < 0x1000u )
    {
      dcache[a1 & 0xFFF] = a2;
      return;
    }
    if ( a1 <= 0x1F801801 )
    {
      switch ( a1 )
      {
        case 0x1F801801u:
          cdrom_reg1_write(a2);
          return;
        case 0x1F801040u:
          sio_data_write(0x1F801040, a2);
          return;
        case 0x1F8010F6u:
          dword_50BFC8 = dword_50BFC8 & 0xFF00FFFF | (a2 << 16);
          return;
        case 0x1F801800u:
          cdrom_reg0_write(a2);
          return;
      }
      goto LABEL_27;
    }
    switch ( a1 )
    {
      case 0x1F801802u:
        cdrom_reg2_write(a2);
        break;
      case 0x1F801803u:
        cdrom_reg3_write(a2);
        break;
      case 0x1F802041u:
        byte_516600[8257] = a2;
        break;
      default:
LABEL_27:
        dump_log(console_log_handle, "REG %s [%08x] <- %08x sizeof(%d) (%08x)\n", "UNK", a1, a2, 1, reg_pc);
        return;
    }
  }
  else if ( (dword_50C2A4 & 0x10000) == 0 )
  {
    *(_BYTE *)((unsigned __int16)a1 + mem_write_hooks[HIWORD(a1)]) = a2;
    if ( dword_5164C0 )
    {
      v2 = (a1 & 0xFFF00000) == 0xBFC00000 ? (a1 & 0x7FFFC) + 0x200000 : a1 & 0x1FFFFC;
      if ( *(LPVOID *)((char *)dword_5164C4 + v2) != dword_5164C0 )
      {
        v3 = ((_BYTE *)dword_5164C0 - (_BYTE *)dword_5164C8) >> 2;
        for ( *(_DWORD *)((char *)dword_5164C4 + v2) = dword_5164C0;
              v3;
              *(_DWORD *)((char *)dword_5164C4 + v2) = dword_5164C0 )
        {
          v4 = *(LPVOID *)((char *)dword_5164C4 + v2 - 4);
          v2 -= 4;
          if ( v4 == dword_5164C0 )
            break;
          --v3;
        }
      }
    }
  }
}
