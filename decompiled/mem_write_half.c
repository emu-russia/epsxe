#include "pch.h"
char __cdecl mem_write_half(unsigned int a1, unsigned __int16 a2)
{
  unsigned int v2; // eax
  int v3; // ecx
  LPVOID v4; // edi
  char v5; // cl

  dword_50C270 -= 4;
  LOBYTE(v2) = a1;
  if ( (a1 & 0x1FC00000) == 0x1F800000 )
  {
    if ( (unsigned __int16)a1 >= 0x1000u )
    {
      if ( a1 > 0x1F801138 || a1 < 0x1F801100 )
      {
        if ( a1 > 0x1F801EEF || a1 < 0x1F801C00 )
        {
          LOBYTE(v2) = a1 - 20;
          switch ( a1 )
          {
            case 0x1F801014u:
              *(_WORD *)&byte_516600[(unsigned __int16)a1] = a2;
              LOBYTE(v2) = a2;
              break;
            case 0x1F801040u:
              sio_data_write(a1, a2);
              LOBYTE(v2) = sio_data_write(a1, SHIBYTE(a2));
              break;
            case 0x1F801048u:
              HIWORD(sio0_mode_reg) = a2;
              break;
            case 0x1F80104Au:
              LOWORD(sio0_control_reg) = a2 & 0xFFEF;
              if ( (a2 & 0x10) != 0 )
                BYTE1(sio0_mode_reg) &= ~2u;
              sub_421B10(a2);
              if ( (v5 & 1) != 0 )
                LOWORD(sio0_mode_reg) = sio0_mode_reg | 1;
              LOBYTE(v2) = 1 << (BYTE1(sio0_control_reg) & 3);
              LOBYTE(byte_52670C) = v2;
              BYTE2(byte_52670C) = v2;
              break;
            case 0x1F80104Eu:
              HIWORD(sio0_control_reg) = a2;
              break;
            case 0x1F801070u:
              if ( dword_4FD878 && dword_50C270 < (unsigned int)dword_4FD870 )
              {
                int_reg |= dword_4FD878;
                dword_4FD878 = 0;
              }
              v2 = (unsigned __int16)(int_mask & a2);
              int_reg &= v2;
              break;
            case 0x1F801074u:
              int_mask = a2;
              break;
            default:
              LOBYTE(v2) = dump_log(
                             console_log_handle,
                             "REG %s [%08x] <- %08x sizeof(%d) (%08x)\n",
                             (const char *)&off_455894,
                             a1,
                             a2,
                             2,
                             reg_pc);
              break;
          }
        }
        else
        {
          LOBYTE(v2) = spu_write_register_cb(a1, a2);
        }
      }
      else
      {
        LOBYTE(v2) = rcnt_write_reg((unsigned __int16)a1, a2);
      }
    }
    else
    {
      *(_WORD *)((char *)&dcache + (a1 & 0xFFF)) = a2;
      LOBYTE(v2) = a1;
    }
  }
  else if ( (dword_50C2A4 & 0x10000) == 0 )
  {
    *(_WORD *)((unsigned __int16)a1 + mem_hooks[HIWORD(a1)]) = a2;
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
  return v2;
}
