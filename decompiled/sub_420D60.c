#include "pch.h"
char __cdecl sub_420D60(char a1, char *a2)
{
  int v2; // eax

  LOBYTE(v2) = a1;
  if ( !a1 )
    LOBYTE(sio0_mode_reg) = sio0_mode_reg | 2;
  byte_52670C[(unsigned __int8)dword_526810 + 3] = *a2;
  LOBYTE(dword_526810) = dword_526810 + 1;
  if ( a1 )
  {
    LOBYTE(v2) = sio0_control_reg;
    if ( (sio0_control_reg & 0x1000) != 0 )
    {
      sub_42AFD0();
      v2 = hw_update_counter;
      if ( hw_update_counter >= 0 )
      {
        if ( (unsigned int)hw_update_counter > 0x1F9 )
        {
          dword_4FD864 = hw_update_counter - 505;
          dword_4FD86C = 128;
          LOBYTE(v2) = hw_update_counter + 7;
          return v2;
        }
      }
      else
      {
        v2 = 0;
        hw_update_counter = 0;
      }
      dword_4FD868 = dword_455940 + v2 - 505;
      dword_4FD86C = 0;
    }
  }
  return v2;
}
