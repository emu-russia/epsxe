#include "pch.h"
char __cdecl rcnt_write_reg(unsigned __int16 a1, int a2)
{
  int v2; // eax
  bool v3; // zf

  LOBYTE(v2) = a1;
  switch ( a1 )
  {
    case 0x1100u:
    case 0x1110u:
    case 0x1120u:
    case 0x1130u:
      if ( !a2 )
      {
        v2 = 16 * ((a1 >> 4) & 3);
        *(int *)((char *)dword_50BFD0 + v2) = 0;
      }
      break;
    case 0x1104u:
    case 0x1114u:
    case 0x1124u:
    case 0x1134u:
      v2 = 16 * ((a1 >> 4) & 3);
      *(int *)((char *)dword_50BFD0 + v2) = 0;
      *(int *)((char *)dword_50BFD4 + v2) = a2 & 0x3FF | 0x1000;
      if ( (a2 & 8) != 0 && *(int *)((char *)dword_50BFD8 + v2) )
      {
        *(int *)((char *)dword_50BFDC + v2) = (unsigned __int16)*(int *)((char *)dword_50BFD8 + v2);
        v3 = a1 == 4388;
      }
      else
      {
        *(int *)((char *)dword_50BFDC + v2) = 0xFFFF;
        v3 = a1 == 4388;
      }
      goto LABEL_13;
    case 0x1108u:
    case 0x1118u:
    case 0x1128u:
    case 0x1138u:
      v2 = 16 * ((a1 >> 4) & 3);
      *(int *)((char *)dword_50BFD8 + v2) = a2;
      if ( (*((_BYTE *)dword_50BFD4 + v2) & 8) != 0 && a2 )
        *(int *)((char *)dword_50BFDC + v2) = (unsigned __int16)a2;
      else
        *(int *)((char *)dword_50BFDC + v2) = 0xFFFF;
      v3 = a1 == 4392;
LABEL_13:
      if ( v3 )
      {
        LOBYTE(v2) = parasite_eve_cheat;
        if ( parasite_eve_cheat )
          dword_50BFFC = (unsigned int)dword_50BFFC >> 2;
      }
      break;
    default:
      return v2;
  }
  return v2;
}
