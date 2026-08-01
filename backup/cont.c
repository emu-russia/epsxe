_BYTE *__cdecl sub_42D010(char a1, _BYTE *a2)
{
  _BYTE *result; // eax

  switch ( a1 )
  {
    case 0:
      *a2 = 0;
      a2[1] = 65;
      a2[2] = 90;
      a2[3] = BYTE1(dword_455FB0);
      a2[4] = dword_455FB0;
      result = a2;
      break;
    case 1:
      *a2 = 0;
      a2[1] = 65;
      a2[2] = 90;
      a2[3] = BYTE1(dword_455FB4);
      a2[4] = dword_455FB4;
      result = a2;
      break;
    case 2:
      *a2 = 0;
      a2[1] = 65;
      a2[2] = 90;
      a2[3] = byte_455FB9;
      a2[4] = byte_455FB8;
      result = a2;
      break;
    case 3:
      *a2 = 0;
      a2[1] = 65;
      a2[2] = 90;
      a2[3] = byte_455FBD;
      a2[4] = byte_455FBC;
      result = a2;
      break;
    default:
      *a2 = 0;
      a2[1] = -1;
      a2[2] = -1;
      a2[3] = -1;
      a2[4] = -1;
      result = a2;
      break;
  }
  return result;
}

char __cdecl sub_42D0E0(char a1, _BYTE *a2)
{
  char result; // al
  __int16 v3; // ax
  char v4; // al
  int v5; // eax
  int v6; // eax

  switch ( a1 )
  {
    case 0:
      *a2 = 0;
      a2[1] = 115;
      a2[2] = 90;
      a2[3] = BYTE1(dword_455FB0);
      a2[4] = dword_455FB0;
      a2[8] = 0x80;
      a2[7] = 0x80;
      a2[6] = 0x80;
      a2[5] = 0x80;
      if ( dword_456048[0] == 4 )
      {
        a2[7] = LOBYTE(dword_4FD900[0]) + 0x80;
        a2[8] = LOBYTE(dword_4FD910[0]) + 0x80;
        a2[5] = LOBYTE(dword_4FD920[0]) + 0x80;
        result = LOBYTE(dword_4FD930[0]) + 0x80;
        a2[6] = LOBYTE(dword_4FD930[0]) + 0x80;
        return result;
      }
      if ( dword_456048[0] != 5 )
      {
        result = LOBYTE(dword_456048[0]) - 6;
        if ( dword_456048[0] != 6 )
          return result;
        if ( (dword_50AB60 & 3) != 0 )
        {
          word_4FD8FA += dword_4FD8F0 / 3;
          LOBYTE(v3) = word_4FD8FA;
          if ( word_4FD8FA <= 127 )
          {
            if ( word_4FD8FA >= -128 )
              goto LABEL_12;
            v3 = -128;
          }
          else
          {
            v3 = 127;
          }
        }
        else
        {
          v3 = 0;
        }
        word_4FD8FA = v3;
LABEL_12:
        a2[7] = v3 + 0x80;
        if ( (dword_50AB60 & 3) != 0 )
        {
          word_4FD8FC += dword_4FD8F4 / 3;
          v4 = word_4FD8FC;
          if ( word_4FD8FC <= 127 )
          {
            if ( word_4FD8FC < -128 )
            {
              v4 = 0x80;
              word_4FD8FC = -128;
            }
            result = v4 + 0x80;
            a2[8] = result;
          }
          else
          {
            word_4FD8FC = 127;
            a2[8] = -1;
            return -1;
          }
        }
        else
        {
          word_4FD8FC = 0;
          a2[8] = 0x80;
          return 0x80;
        }
        return result;
      }
      v5 = 3 * dword_4FD8F0;
      dword_4FD8F0 *= 3;
      if ( dword_4FD8F0 <= 127 )
      {
        if ( v5 >= -128 )
          goto LABEL_24;
        v5 = -128;
      }
      else
      {
        v5 = 127;
      }
      dword_4FD8F0 = v5;
LABEL_24:
      a2[7] = v5 + 0x80;
      v6 = 3 * dword_4FD8F4;
      dword_4FD8F4 *= 3;
      if ( dword_4FD8F4 <= 127 )
      {
        if ( v6 < -128 )
        {
          LOBYTE(v6) = 0x80;
          dword_4FD8F4 = -128;
        }
        result = v6 + 0x80;
        a2[8] = result;
      }
      else
      {
        dword_4FD8F4 = 127;
        a2[8] = -1;
        return -1;
      }
      return result;
    case 1:
      *a2 = 0;
      a2[1] = 115;
      a2[2] = 90;
      a2[3] = BYTE1(dword_455FB4);
      a2[4] = dword_455FB4;
      a2[7] = byte_4FD904 + 0x80;
      a2[8] = byte_4FD914 + 0x80;
      a2[5] = byte_4FD924 + 0x80;
      a2[6] = byte_4FD934 + 0x80;
      return (char)a2;
    case 2:
      *a2 = 0;
      a2[1] = 115;
      a2[2] = 90;
      a2[3] = byte_455FB9;
      a2[4] = byte_455FB8;
      a2[7] = byte_4FD908 + 0x80;
      a2[8] = byte_4FD918 + 0x80;
      a2[5] = byte_4FD928 + 0x80;
      a2[6] = byte_4FD938 + 0x80;
      return (char)a2;
    case 3:
      *a2 = 0;
      a2[1] = 115;
      a2[2] = 90;
      a2[3] = byte_455FBD;
      a2[4] = byte_455FBC;
      a2[7] = byte_4FD90C + 0x80;
      a2[8] = byte_4FD91C + 0x80;
      a2[5] = byte_4FD92C + 0x80;
      a2[6] = byte_4FD93C + 0x80;
      return (char)a2;
    default:
      *a2 = 0;
      a2[1] = -1;
      a2[2] = 90;
      a2[3] = -1;
      a2[4] = -1;
      a2[8] = 0x80;
      a2[7] = 0x80;
      a2[6] = 0x80;
      a2[5] = 0x80;
      return (char)a2;
  }
}

_BYTE *__cdecl sub_42D3C0(char a1, _BYTE *a2)
{
  _BYTE *result; // eax

  if ( a1 )
  {
    result = a2;
    a2[3] = -1;
    a2[2] = 90;
    a2[1] = 18;
    *a2 = 0;
    if ( a1 != 1 )
    {
      a2[4] = -1;
      a2[6] = -1;
      a2[5] = -1;
      return result;
    }
  }
  else
  {
    result = a2;
    *a2 = 0;
    a2[1] = 18;
    a2[2] = 90;
    a2[3] = -1;
  }
  result[4] = -4;
  if ( (dword_50AB60 & 1) != 0 )
    result[4] = -12;
  if ( (dword_50AB60 & 2) != 0 )
    result[4] &= ~4u;
  result[5] = dword_4FD8F0;
  result[6] = dword_4FD8F4;
  return result;
}

_BYTE *__cdecl sub_42D440(char a1, _BYTE *a2)
{
  _BYTE *result; // eax
  __int16 v3; // ax
  int v4; // eax
  int v5; // ecx
  int v6; // ecx
  int v7; // eax

  if ( a1 )
  {
    result = a2;
    a2[7] = 0;
    a2[6] = 0;
    a2[5] = 0;
    a2[4] = -1;
    a2[3] = -1;
    a2[2] = 90;
    *a2 = 0;
    if ( a1 == 1 )
    {
      a2[1] = -1;
      a2[8] = -1;
    }
    else
    {
      a2[8] = 0;
      a2[1] = 99;
    }
  }
  else
  {
    *a2 = 0;
    a2[1] = 99;
    a2[2] = 90;
    *(_WORD *)(a2 + 3) = -1;
    a2[8] = 0;
    a2[7] = 0;
    a2[6] = 0;
    a2[5] = 0;
    v3 = dword_4FD8F4 / 2 + HIWORD(dword_4FD980);
    LOWORD(dword_4FD980) = dword_4FD8F0 / 2 + dword_4FD980;
    HIWORD(dword_4FD980) = v3;
    if ( (__int16)dword_4FD980 <= 511 )
    {
      if ( (dword_4FD980 & 0x8000u) != 0 )
        LOWORD(dword_4FD980) = 0;
    }
    else
    {
      LOWORD(dword_4FD980) = 511;
    }
    if ( v3 <= 255 )
    {
      if ( v3 < 0 )
        HIWORD(dword_4FD980) = 0;
    }
    else
    {
      HIWORD(dword_4FD980) = 255;
    }
    if ( (dword_50AB60 & 1) != 0 )
      a2[4] &= ~0x20u;
    if ( (dword_50AB60 & 2) != 0 )
      a2[3] &= ~8u;
    if ( (dword_50AB60 & 4) != 0 )
      a2[4] &= ~0x40u;
    *(_WORD *)(a2 + 5) = dword_4FD980;
    a2[7] = BYTE2(dword_4FD980);
    if ( (dword_4FD980 & 0x100) != 0 )
    {
      v4 = (__int16)dword_4FD980 + ((__int16)dword_4FD980 - 255) / 2;
      v5 = SHIWORD(dword_4FD980) - 40;
      if ( v4 <= 511 )
      {
        if ( v4 < 0 )
          v4 = 0;
      }
      else
      {
        v4 = 511;
      }
      if ( v5 <= 255 )
      {
        if ( v5 < 0 )
          v5 = 0;
        return gpu_cursor(0, v4, v5);
      }
      else
      {
        return gpu_cursor(0, v4, 255);
      }
    }
    else
    {
      v6 = (__int16)dword_4FD980 - (255 - (__int16)dword_4FD980) / 2;
      v7 = SHIWORD(dword_4FD980) - 40;
      if ( v6 <= 511 )
      {
        if ( v6 < 0 )
          v6 = 0;
      }
      else
      {
        v6 = 511;
      }
      if ( v7 <= 255 )
      {
        if ( v7 < 0 )
          v7 = 0;
        return gpu_cursor(0, v6, v7);
      }
      else
      {
        return gpu_cursor(0, v6, 255);
      }
    }
  }
  return result;
}

int (__stdcall *__cdecl sub_42D620(unsigned __int8 a1))(_DWORD)
{
  int v1; // eax
  int (__stdcall *result)(_DWORD); // eax

  v1 = dword_456048[a1];
  if ( v1 == 4 || v1 == 5 || v1 == 6 )
    gpu_display_flags(((a1 + 1) << 12) | ((dword_4FD8E0[a1] != 0) << 8));
  if ( dword_456048[a1] == 2 )
    gpu_display_flags(((a1 + 1) << 12) | ((dword_4FD8E0[a1] != 0 ? 2 : 0) << 8));
  if ( dword_456048[a1] == 3 )
    gpu_display_flags(((a1 + 1) << 12) | ((dword_4FD8E0[a1] != 0 ? 3 : 0) << 8));
  result = (int (__stdcall *)(_DWORD))dword_456048[a1];
  if ( (unsigned int)result <= 1 )
    return gpu_display_flags((a1 + 1) << 12);
  return result;
}

int cont_process_input()
{
  int v0; // esi
  int v1; // edi
  int v2; // eax
  unsigned __int8 v3; // si
  int v4; // edx
  int *v5; // eax
  unsigned __int16 *v6; // ecx
  int v7; // esi
  unsigned __int16 v8; // dx
  int result; // eax

  diUpdateDeviceStates();
  dword_4FD8F0 = diGetClampedMouseX();
  dword_4FD8F4 = diGetClampedMouseY();
  dword_50AB60 = g_MouseButtons;
  v0 = 0;
  v1 = 2;
  do
  {
    dword_4FD900[v0] = diGetJoystickButtonState1(v0);
    dword_4FD910[v0] = diGetJoystickButtonState2(v0);
    dword_4FD920[v0] = diGetJoystickButtonState3(v0);
    dword_4FD930[v0] = diGetJoystickButtonState4(v0);
    ++v0;
    --v1;
  }
  while ( v1 );
  if ( byte_50AA7B[0] )
  {
    if ( !create_window_flag )
      ui_error(" User   hit ESC ... \n");
    if ( network_enabled )
    {
      dword_4FD9A0 = 1;
    }
    else
    {
      save_load_state();
      memset(byte_50AA60, 0, 0x100u);
    }
  }
  if ( byte_50AA91 )
    byte_4FC4E4 = 1;
  if ( byte_50AA92 )
    cdr_get_status(2);
  if ( byte_50AA93 )
    cdr_get_status(3);
  if ( byte_50AA94[0] )
    irq_sio_assert_int();
  if ( word_4FD986 )
  {
    if ( word_4FD986 == 1 )
      gpu_hide_screen_pic();
    --word_4FD986;
  }
  if ( byte_4FD984 )
  {
    --byte_4FD984;
    goto LABEL_51;
  }
  if ( byte_50AAD0 )
  {
    state_save();
    dbg_print(" * SaveState Done! \n");
    byte_4FD984 = 25;
    goto LABEL_51;
  }
  if ( byte_50AAD1 )
  {
    LOBYTE(v2) = gpu_freeze_with_counter();
    v3 = v2;
    dbg_print(" * Increased SlotState! (%d)\n", v2);
    gpu_show_screen_pic(v3);
    byte_4FD984 = 25;
    word_4FD986 = 150;
    goto LABEL_51;
  }
  if ( byte_50AAD2 )
  {
    if ( network_enabled )
    {
      dbg_print(" * LoadState doesn't implemented yet with Netplay! \n");
    }
    else
    {
      state_load();
      dbg_print(" * LoadState Done! \n");
      byte_4FC4E4 = 1;
    }
    byte_4FD984 = 25;
    goto LABEL_51;
  }
  if ( byte_50AAD3 )
  {
    if ( network_enabled )
    {
      dbg_print(" * SIO trick doesn't implemented yet with Netplay! \n");
      byte_4FD984 = 25;
    }
    else
    {
      forcepad ^= 0x80u;
      if ( forcepad )
        dbg_print(" * SIO irq enabled. \n");
      else
        dbg_print(" * SIO irq disabled. \n");
      byte_4FD984 = 25;
    }
    goto LABEL_51;
  }
  if ( byte_50AAD4 )
  {
    dword_4FD8E0[(unsigned __int8)dword_4FD988] ^= 1u;
    LOBYTE(v4) = dword_4FD988;
LABEL_42:
    sub_42D620(v4);
    byte_4FD984 = 25;
    goto LABEL_51;
  }
  if ( byte_50AAD5 )
  {
    v4 = ((unsigned __int8)dword_4FD988 + 1) % (2 * (multitap_1 != 0) + 2);
    LOBYTE(dword_4FD988) = v4;
    goto LABEL_42;
  }
  if ( byte_50AAD6 )
  {
    xenogears_trick_enabled ^= 1u;
    if ( xenogears_trick_enabled )
      dbg_print(" * Xenogears trick disabled. \n");
    else
      dbg_print(" * Xenogears trick enabled. \n");
    byte_4FD984 = 25;
  }
  else if ( byte_50AAD7[0] )
  {
    dbg_print(" * Picture done. \n");
    gpu_make_snapshot();
    byte_4FD984 = 25;
  }
LABEL_51:
  v5 = &dword_455FB0;
  v6 = (unsigned __int16 *)(Keys1 + 10);
  v7 = 4;
  do
  {
    v8 = *(v6 - 5);
    *v5 = -1;
    if ( v8 )
    {
      if ( g_KeyboardStatePrev[v6[1]] )
        *v5 = -65;
      if ( g_KeyboardStatePrev[*v6] )
        *v5 &= ~0x20u;
      if ( g_KeyboardStatePrev[v6[2]] )
        *v5 &= ~0x80u;
      if ( g_KeyboardStatePrev[*(v6 - 1)] )
        *v5 &= ~0x10u;
      if ( g_KeyboardStatePrev[v6[7]] )
        *v5 &= ~0x800u;
      if ( g_KeyboardStatePrev[v6[8]] )
        *v5 &= ~0x100u;
      if ( g_KeyboardStatePrev[*(v6 - 3)] )
        *v5 &= ~0x1000u;
      if ( g_KeyboardStatePrev[*(v6 - 2)] )
        *v5 &= ~0x4000u;
      if ( g_KeyboardStatePrev[v8] )
        *v5 &= ~0x8000u;
      if ( g_KeyboardStatePrev[*(v6 - 4)] )
        *v5 &= ~0x2000u;
      if ( g_KeyboardStatePrev[v6[3]] )
        *v5 &= ~4u;
      if ( g_KeyboardStatePrev[v6[4]] )
        *v5 &= ~1u;
      if ( g_KeyboardStatePrev[v6[5]] )
        *v5 &= ~8u;
      if ( g_KeyboardStatePrev[v6[6]] )
        *v5 &= ~2u;
      if ( g_KeyboardStatePrev[v6[9]] )
        *v5 &= ~0x200u;
      if ( g_KeyboardStatePrev[v6[10]] )
        *v5 &= ~0x400u;
    }
    v6 += 16;
    ++v5;
    --v7;
  }
  while ( v7 );
  if ( LOBYTE(mdec_disable_flag[0]) )
  {
    LOBYTE(mdec_disable_flag[0]) = 0;
    dword_455FB0 &= 0xFFFFF7BF;
  }
  result = network_enabled;
  if ( network_enabled )
  {
    result = net_fill_input();
    if ( result )
    {
      dword_4FD9A0 = 0;
      save_load_state();
      memset(byte_50AA60, 0, 0x100u);
      return 0;
    }
  }
  return result;
}

__int16 __cdecl sub_42DBC0(unsigned __int16 a1, __int16 a2)
{
  __int16 result; // ax

  result = a2;
  if ( a2 )
    *((_WORD *)GamepadAxis + a1) = a2;
  return result;
}

__int16 __cdecl sub_42DBE0(unsigned __int16 a1, __int16 a2)
{
  __int16 result; // ax

  result = a2;
  if ( a2 != 1 )
    Keys1[a1] = a2;
  return result;
}

int __cdecl cont_set_default(unsigned __int8 a1)
{
  int result; // eax

  if ( a1 == 1 )
  {
    Keys1[0] = 203;
    Keys1[1] = 205;
    Keys1[2] = 200;
    Keys1[3] = 208;
    Keys1[4] = 32;
    Keys1[5] = 45;
    Keys1[6] = 44;
    Keys1[7] = 31;
    Keys1[8] = 17;
    Keys1[9] = 18;
    Keys1[10] = 19;
    Keys1[11] = 20;
    Keys1[12] = 47;
    Keys1[13] = 46;
    Keys1[14] = 16;
    Keys1[15] = 21;
  }
  else if ( a1 > 1u && a1 < 4u )
  {
    memset(&word_455FA8[16 * a1], 0, 0x20u);
    return 0;
  }
  return result;
}

int __cdecl cont_sub_42DCC0(unsigned __int8 a1)
{
  _DWORD *v2; // ecx

  memset(&word_455FA8[16 * a1], 0, 0x20u);
  v2 = (_DWORD *)(8 * a1 + 5232772);
  *v2 = 0;
  v2[1] = 0;
  return 0;
}