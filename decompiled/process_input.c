#include "pch.h"
int sub_42D6E0()
{
  int v0; // esi
  int v1; // edi
  int v2; // esi
  int v3; // edx
  int *v4; // eax
  unsigned __int16 *v5; // ecx
  int v6; // esi
  unsigned __int16 v7; // dx
  int result; // eax
  char v9; // [esp+0h] [ebp-Ch]

  sub_40F340();
  dword_4FD8F0 = sub_40FA30();
  dword_4FD8F4 = sub_40FA70();
  dword_50AB60 = dword_4F7784;
  v0 = 0;
  v1 = 2;
  do
  {
    dword_4FD900[v0] = sub_40FB20(v0);
    dword_4FD910[v0] = sub_40FB40(v0);
    dword_4FD920[v0] = sub_40FB60(v0);
    dword_4FD930[v0] = sub_40FB80(v0);
    ++v0;
    --v1;
  }
  while ( v1 );
  if ( byte_50AA7B )
  {
    if ( !create_window_flag )
      ui_error(aUserHitEsc, v9);
    if ( dword_4FD99C )
    {
      dword_4FD9A0 = 1;
    }
    else
    {
      save_load_state();
      memset(&byte_50AA60, 0, 0x100u);
    }
  }
  if ( byte_50AA91 )
    byte_4FC4E4 = 1;
  if ( byte_50AA92 )
    sub_42CFE0(2);
  if ( byte_50AA93 )
    sub_42CFE0(3);
  if ( byte_50AA94 )
    sio_assert_int();
  if ( word_4FD986 )
  {
    if ( word_4FD986 == 1 )
      sub_42EDF0();
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
    dbg_print(aSavestateDone);
    byte_4FD984 = 25;
    goto LABEL_51;
  }
  if ( byte_50AAD1 )
  {
    v2 = gpu_freeze_with_counter();
    dbg_print(" * Increased SlotState! (%d)\n", v2);
    gpu_show_screen_pic(v2);
    byte_4FD984 = 25;
    word_4FD986 = 150;
    goto LABEL_51;
  }
  if ( byte_50AAD2 )
  {
    if ( dword_4FD99C )
    {
      dbg_print(aLoadstateDoesn);
    }
    else
    {
      state_load();
      dbg_print(aLoadstateDone);
      byte_4FC4E4 = 1;
    }
    byte_4FD984 = 25;
    goto LABEL_51;
  }
  if ( byte_50AAD3 )
  {
    if ( dword_4FD99C )
    {
      dbg_print(aSioTrickDoesnT);
      byte_4FD984 = 25;
    }
    else
    {
      forcepad ^= 0x80u;
      if ( forcepad )
        dbg_print(aSioIrqEnabled);
      else
        dbg_print(aSioIrqDisabled);
      byte_4FD984 = 25;
    }
    goto LABEL_51;
  }
  if ( byte_50AAD4 )
  {
    dword_4FD8E0[(unsigned __int8)dword_4FD988] ^= 1u;
    v3 = (unsigned __int8)dword_4FD988;
LABEL_42:
    sub_42D620(v3);
    byte_4FD984 = 25;
    goto LABEL_51;
  }
  if ( byte_50AAD5 )
  {
    v3 = ((unsigned __int8)dword_4FD988 + 1) % (2 * (multitap_1 != 0) + 2);
    LOBYTE(dword_4FD988) = v3;
    goto LABEL_42;
  }
  if ( byte_50AAD6 )
  {
    byte_455944 ^= 1u;
    if ( byte_455944 )
      dbg_print(aXenogearsTrick_0);
    else
      dbg_print(aXenogearsTrick);
    byte_4FD984 = 25;
  }
  else if ( byte_50AAD7 )
  {
    dbg_print(aPictureDone);
    gpu_make_snapshot();
    byte_4FD984 = 25;
  }
LABEL_51:
  v4 = &dword_455FB0;
  v5 = word_455FD0 + 2;
  v6 = 4;
  do
  {
    v7 = *(v5 - 5);
    *v4 = -1;
    if ( v7 )
    {
      if ( byte_50ABC0[v5[1]] )
        *v4 = -65;
      if ( byte_50ABC0[*v5] )
        *v4 &= ~0x20u;
      if ( byte_50ABC0[v5[2]] )
        *v4 &= ~0x80u;
      if ( byte_50ABC0[*(v5 - 1)] )
        *v4 &= ~0x10u;
      if ( byte_50ABC0[v5[7]] )
        *v4 &= ~0x800u;
      if ( byte_50ABC0[v5[8]] )
        *v4 &= ~0x100u;
      if ( byte_50ABC0[*(v5 - 3)] )
        *v4 &= ~0x1000u;
      if ( byte_50ABC0[*(v5 - 2)] )
        *v4 &= ~0x4000u;
      if ( byte_50ABC0[v7] )
        *v4 &= ~0x8000u;
      if ( byte_50ABC0[*(v5 - 4)] )
        *v4 &= ~0x2000u;
      if ( byte_50ABC0[v5[3]] )
        *v4 &= ~4u;
      if ( byte_50ABC0[v5[4]] )
        *v4 &= ~1u;
      if ( byte_50ABC0[v5[5]] )
        *v4 &= ~8u;
      if ( byte_50ABC0[v5[6]] )
        *v4 &= ~2u;
      if ( byte_50ABC0[v5[9]] )
        *v4 &= ~0x200u;
      if ( byte_50ABC0[v5[10]] )
        *v4 &= ~0x400u;
    }
    v5 += 16;
    ++v4;
    --v6;
  }
  while ( v6 );
  if ( LOBYTE(dword_4FD888[0]) )
  {
    LOBYTE(dword_4FD888[0]) = 0;
    dword_455FB0 &= 0xFFFFF7BF;
  }
  result = dword_4FD99C;
  if ( dword_4FD99C )
  {
    result = sub_42F630(v5);
    if ( result )
    {
      dword_4FD9A0 = 0;
      save_load_state();
      memset(&byte_50AA60, 0, 0x100u);
      return 0;
    }
  }
  return result;
}
