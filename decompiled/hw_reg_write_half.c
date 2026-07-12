#include "pch.h"
void __cdecl hw_reg_write_half(unsigned int a1, unsigned __int16 a2)
{
  char v2; // cl

  if ( (dword_50C2A4 & 0x10000) == 0 )
  {
    if ( (a1 & 0xFF800000) == 0x1F800000 )
    {
      if ( a1 >= 0x1F801000 )
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
                sio_data_write(a1, a2);
                sio_data_write(a1, SHIBYTE(a2));
                break;
              case 0x1F801048u:
                HIWORD(sio0_mode_reg) = a2;
                break;
              case 0x1F80104Au:
                LOWORD(sio0_control_reg) = a2 & 0xFFEF;
                if ( (a2 & 0x10) != 0 )
                  BYTE1(sio0_mode_reg) &= ~2u;
                sub_421B10(a2);
                if ( (v2 & 1) != 0 )
                  LOWORD(sio0_mode_reg) = sio0_mode_reg | 1;
                byte_52670C[0] = 1 << (BYTE1(sio0_control_reg) & 3);
                byte_52670C[2] = 1 << (BYTE1(sio0_control_reg) & 3);
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
          rcnt_write_reg(a1, a2);
        }
      }
      else
      {
        *(_WORD *)&dcache[a1 & 0xFFF] = a2;
      }
    }
    else
    {
      *(_WORD *)((unsigned __int16)a1 + mem_write_hooks[HIWORD(a1)]) = a2;
    }
  }
}
