#include "pch.h"
int __cdecl controller_set_keyboard(HWND hDlg, unsigned __int16 a2)
{
  int v2; // ebp
  int *v3; // esi
  CHAR *v4; // eax
  int result; // eax
  int v6; // edx
  int v7; // [esp+10h] [ebp-404h]
  CHAR String[1024]; // [esp+14h] [ebp-400h] BYREF

  v2 = 0;
  v3 = &word_44DD1C;
  v7 = 16;
  do
  {
    if ( (unsigned __int16)word_455FA8[16 * (unsigned __int8)pad_number_menu_selection + v2] >= 0x200u )
    {
      sprintf(String, "%d", (unsigned __int16)word_455FA8[16 * (unsigned __int8)pad_number_menu_selection + v2]);
      v4 = String;
    }
    else
    {
      v4 = &aNone_0[13 * (unsigned __int16)word_455FA8[16 * (unsigned __int8)pad_number_menu_selection + v2]];
    }
    SetDlgItemTextA(hDlg, *(unsigned __int16 *)v3, v4);
    ++v2;
    v3 = (int *)((char *)v3 + 2);
    result = --v7;
  }
  while ( v7 );
  if ( a2 < 0xFFu )
  {
    v6 = a2 + 16 * (unsigned __int8)pad_number_menu_selection;
    if ( (unsigned __int16)word_455FA8[v6] >= 0x200u )
    {
      sprintf(String, "%d", (unsigned __int16)word_455FA8[v6]);
      return SetDlgItemTextA(hDlg, *((unsigned __int16 *)&word_44DD1C + a2), String);
    }
    else
    {
      return SetDlgItemTextA(
               hDlg,
               *((unsigned __int16 *)&word_44DD1C + a2),
               &aNone_0[13 * (unsigned __int16)word_455FA8[v6]]);
    }
  }
  return result;
}
