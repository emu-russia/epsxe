#include "pch.h"
void __cdecl mem_write_half(unsigned int a1, unsigned __int16 a2)
{
  unsigned int v2; // eax
  int v3; // ecx
  LPVOID v4; // edi
  char v5; // cl

  hw_update_counter -= 4;
  if ( (a1 & 0x1FC00000) == 0x1F800000 )
  {
    if ( (unsigned __int16)a1 >= 0x1000u )
    {
      if ( a1 > 0x1F801138 || a1 < 0x1F801100 )
      {
        if ( a1 > 0x1F801EEF || a1 < 0x1F801C00 )
        {
          switch ( a1 )
          {
            case 0x1F801014u:
              *(_WORD *)&byte_516600[(unsigned __int16)a1] = a2;
              break;
            case 0x1F801040u:
              sio_write_data_byte(a1, a2);
              sio_write_data_byte(a1, SHIBYTE(a2));
              break;
            case 0x1F801048u:
              HIWORD(sio0_mode_reg) = a2;
              break;
            case 0x1F80104Au:
              LOWORD(sio0_control_reg) = a2 & 0xFFEF;
              if ( (a2 & 0x10) != 0 )
                BYTE1(sio0_mode_reg) &= ~2u;
              sio_controller_init(a2);
              if ( (v5 & 1) != 0 )
                LOWORD(sio0_mode_reg) = sio0_mode_reg | 1;
              sio_tx_fifo[0] = 1 << (BYTE1(sio0_control_reg) & 3);
              sio_tx_fifo[2] = 1 << (BYTE1(sio0_control_reg) & 3);
              break;
            case 0x1F80104Eu:
              HIWORD(sio0_control_reg) = a2;
              break;
            case 0x1F801070u:
              if ( *(_DWORD *)dword_4FD878 && (unsigned int)hw_update_counter < *(_DWORD *)dword_4FD870 )
              {
                *(_DWORD *)int_reg |= *(_DWORD *)dword_4FD878;
                *(_DWORD *)dword_4FD878 = 0;
              }
              *(_DWORD *)int_reg = (unsigned __int16)(int_mask & a2 & *(_WORD *)int_reg);
              break;
            case 0x1F801074u:
              int_mask = a2;
              break;
            default:
              dump_log(
                console_log_handle,
                "REG %s [%08x] <- %08x sizeof(%d) (%08x)\n",
                "UNK",
                a1,
                a2,
                2,
                *(_DWORD *)reg_pc);
              break;
          }
        }
        else
        {
          spu_write_register_cb(a1, a2);
        }
      }
      else
      {
        irq_rcnt_write_reg(a1, a2);
      }
    }
    else
    {
      *(_WORD *)&dcache[a1 & 0xFFF] = a2;
    }
  }
  else if ( (dword_50C2A4 & 0x10000) == 0 )
  {
    *(_WORD *)((unsigned __int16)a1 + mem_write_hooks[HIWORD(a1)]) = a2;
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
