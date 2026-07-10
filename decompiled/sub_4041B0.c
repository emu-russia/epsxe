#include "pch.h"
BOOL __cdecl sub_4041B0(HWND hDlg, unsigned __int16 a2)
{
  int v2; // ebp
  int *v3; // esi
  int v4; // ecx
  int v5; // ecx
  int v7; // [esp+10h] [ebp-404h]
  CHAR String[1024]; // [esp+14h] [ebp-400h] BYREF

  v2 = 0;
  v3 = &nIDDlgItem;
  v7 = 4;
  do
  {
    v4 = v2 + 4 * (unsigned __int8)byte_44DD1A;
    if ( *((_WORD *)dword_4FD884 + v4) >= 0x20u )
    {
      sprintf(String, "%d", *((unsigned __int16 *)dword_4FD884 + v4));
      SetDlgItemTextA(hDlg, *(unsigned __int16 *)v3, String);
    }
    else
    {
      SetDlgItemTextA(hDlg, *(unsigned __int16 *)v3, &aJ1None[14 * *((unsigned __int16 *)dword_4FD884 + v4)]);
    }
    ++v2;
    v3 = (int *)((char *)v3 + 2);
    --v7;
  }
  while ( v7 );
  v5 = a2 + 4 * (unsigned __int8)byte_44DD1A;
  if ( *((_WORD *)dword_4FD884 + v5) < 0x20u )
    return SetDlgItemTextA(
             hDlg,
             *((unsigned __int16 *)&nIDDlgItem + a2),
             &aJ1None[14 * *((unsigned __int16 *)dword_4FD884 + v5)]);
  sprintf(String, "%d", *((unsigned __int16 *)dword_4FD884 + v5));
  return SetDlgItemTextA(hDlg, *((unsigned __int16 *)&nIDDlgItem + a2), String);
}
