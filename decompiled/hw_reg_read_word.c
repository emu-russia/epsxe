#include "pch.h"
unsigned int __cdecl hw_reg_read_word(unsigned int a1)
{
  int register_cb; // edi
  unsigned int result; // eax
  int v3; // esi
  unsigned int v4; // esi
  unsigned int v5; // esi
  int v6; // ecx
  int v7; // esi
  int v8; // eax
  int v9; // ecx
  unsigned int v10; // ecx
  unsigned int v11; // esi
  int v12; // eax
  int v13; // esi
  unsigned int v14; // eax
  unsigned int v15; // ecx

  if ( a1 < 0x1F801C00 || a1 > 0x1F801E2F )
  {
    if ( a1 > 0x1F8010E8 )
    {
      if ( a1 > 0x1F801124 )
      {
        if ( a1 > 0x1F801810 )
        {
          switch ( a1 )
          {
            case 0x1F801814u:
              return j_GPUreadStatus();
            case 0x1F801820u:
              return 0;
            case 0x1F801824u:
              result = dword_4FC4F4 | dword_4FC504 | dword_4FC4F8;
              dword_4FC4F8 = 0;
              break;
            default:
LABEL_44:
              dump_log(console_log_handle, "REG %s [%08x] -> %08x sizeof(%d)\n", (const char *)&off_455894, a1, 0, 4);
              return 0;
          }
        }
        else if ( a1 == 0x1F801810 )
        {
          return j_GPUreadData();
        }
        else
        {
          switch ( a1 )
          {
            case 0x1F801128u:
            case 0x1F801138u:
LABEL_39:
              result = dword_50BFD8[4 * ((a1 >> 4) & 3)];
              break;
            case 0x1F801130u:
              return 0;
            case 0x1F801134u:
              return dword_50BFD4[4 * ((a1 >> 4) & 3)];
            default:
              goto LABEL_44;
          }
        }
      }
      else if ( a1 == 0x1F801124 )
      {
        return dword_50BFD4[4 * ((a1 >> 4) & 3)];
      }
      else
      {
        switch ( a1 )
        {
          case 0x1F8010F0u:
            result = dword_5164D0;
            break;
          case 0x1F8010F4u:
            result = dword_50BFC8;
            break;
          case 0x1F801100u:
            v5 = 4 * ((a1 >> 4) & 3);
            v6 = dword_50BFD0[v5];
            v7 = dword_50BFD4[v5] & 0x100;
            v8 = 512;
            if ( !v7 )
              v8 = dword_455940;
            v9 = v8 + v6;
            if ( v7 )
              result = v9 - (dword_50C270 << 9) / (unsigned int)dword_455940;
            else
              result = v9 - dword_50C270;
            break;
          case 0x1F801104u:
          case 0x1F801114u:
            return dword_50BFD4[4 * ((a1 >> 4) & 3)];
          case 0x1F801108u:
          case 0x1F801118u:
            goto LABEL_39;
          case 0x1F801110u:
            result = ((dword_50BFD4[4 * ((a1 >> 4) & 3)] & 0x100) != 0 ? 0 : dword_455940)
                   - ((dword_50BFD4[4 * ((a1 >> 4) & 3)] & 0x100) != 0 ? 0 : dword_50C270)
                   + dword_50BFD0[4 * ((a1 >> 4) & 3)];
            break;
          case 0x1F801120u:
            v10 = dword_455940;
            v11 = 4 * ((a1 >> 4) & 3);
            v12 = dword_50BFD0[v11];
            v13 = dword_50BFD4[v11] & 0x200;
            if ( v13 )
              v10 = (unsigned int)dword_455940 >> 3;
            v14 = v10 + v12;
            v15 = dword_50C270;
            if ( v13 )
              v15 = (unsigned int)dword_50C270 >> 3;
            result = v14 - v15;
            break;
          default:
            goto LABEL_44;
        }
      }
    }
    else if ( a1 == 0x1F8010E8 )
    {
LABEL_15:
      v3 = (unsigned __int8)a1 >> 4;
      result = dword_5164E8[3 * v3 - 24];
      if ( v3 == 10 && byte_50C216 <= 0 )
      {
        v4 = *(_DWORD *)dword_516500 & 0xFEFFFFFF;
        *(_DWORD *)dword_516500 &= ~0x1000000u;
        if ( byte_50C216 <= -2 )
          return v4;
      }
    }
    else
    {
      switch ( a1 )
      {
        case 0x1F801014u:
        case 0x1F801060u:
          result = *(_DWORD *)&byte_516600[(unsigned __int16)a1];
          break;
        case 0x1F801040u:
        case 0x1F801044u:
          result = sio_read(a1, 4);
          break;
        case 0x1F801070u:
          if ( dword_4FD878 )
          {
            if ( dword_50C270 < (unsigned int)dword_4FD870 )
            {
              int_reg |= dword_4FD878;
              dword_4FD878 = 0;
            }
          }
          result = int_reg | forcepad;
          break;
        case 0x1F801074u:
          result = int_mask;
          break;
        case 0x1F801080u:
        case 0x1F801090u:
        case 0x1F8010A0u:
        case 0x1F8010B0u:
        case 0x1F8010C0u:
        case 0x1F8010D0u:
        case 0x1F8010E0u:
          result = dword_5164E0[3 * ((unsigned __int8)a1 >> 4) - 24];
          break;
        case 0x1F801088u:
        case 0x1F801098u:
        case 0x1F8010A8u:
        case 0x1F8010B8u:
        case 0x1F8010C8u:
        case 0x1F8010D8u:
          goto LABEL_15;
        default:
          goto LABEL_44;
      }
    }
  }
  else
  {
    register_cb = (unsigned __int16)spu_read_register_cb(a1);
    return register_cb | ((unsigned __int16)spu_read_register_cb(a1 + 2) << 16);
  }
  return result;
}
