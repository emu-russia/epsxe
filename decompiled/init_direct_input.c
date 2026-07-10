#include "pch.h"
int init_direct_input()
{
  int v0; // edi
  CHAR Text[256]; // [esp+8h] [ebp-100h] BYREF

  v0 = DirectInputCreateA(dword_4F7A58, 1792, &dword_4F7768, 0);
  if ( v0 >= 0 )
  {
    if ( (*(int (__stdcall **)(int, void *, int *, _DWORD))(*(_DWORD *)dword_4F7768 + 12))(
           dword_4F7768,
           &unk_4485E0,
           &dword_4F7A5C,
           0) < 0 )
      return 0;
    if ( (*(int (__stdcall **)(int, void *))(*(_DWORD *)dword_4F7A5C + 44))(dword_4F7A5C, &unk_448758) < 0 )
      return 0;
    (*(void (__stdcall **)(int, int, int))(*(_DWORD *)dword_4F7A5C + 52))(dword_4F7A5C, dword_4F7A60, 6);
    if ( !dword_4FD8DC || byte_44DD19 )
      goto LABEL_25;
    if ( (*(int (__stdcall **)(int, void *, int *, _DWORD))(*(_DWORD *)dword_4F7768 + 12))(
           dword_4F7768,
           &unk_4485D0,
           &dword_4F75C8,
           0) < 0 )
      return 0;
    if ( (*(int (__stdcall **)(int, void *))(*(_DWORD *)dword_4F75C8 + 44))(dword_4F75C8, &unk_448740) < 0 )
      return 0;
    if ( (*(int (__stdcall **)(int, int, int))(*(_DWORD *)dword_4F75C8 + 52))(dword_4F75C8, dword_4F7A60, 5) >= 0 )
    {
LABEL_25:
      dword_4F776C[0] = 0;
      dword_4F7770 = 0;
      dword_4F7774 = 0;
      dword_4F7778 = 0;
      (*(void (__stdcall **)(int, int, int (__userpurge *)@<eax>(int@<ebp>, _DWORD *, int), int, int))(*(_DWORD *)dword_4F7768 + 16))(
        dword_4F7768,
        4,
        sub_40E800,
        dword_4F7768,
        1);
      if ( (dword_4FD8AC[0] && dword_4FD8AC[0] <= 4u
         || dword_4FD8B0 && (unsigned int)dword_4FD8B0 <= 4
         || dword_4FD8B4 && (unsigned int)dword_4FD8B4 <= 4
         || dword_4FD8B8[0] && dword_4FD8B8[0] <= 4u)
        && (*(int (__stdcall **)(int, int, int (__userpurge *)@<eax>(int@<ebp>, _DWORD *, int), int, int))(*(_DWORD *)dword_4F7768 + 16))(
             dword_4F7768,
             4,
             sub_40E800,
             dword_4F7768,
             257) < 0 )
      {
        printf(" * No force-feedback joysticks available. \n");
      }
      sub_40E1D0();
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    sprintf(Text, aErrorInitializ);
    MessageBoxA(nullptr, Text, aInitError, 0x10u);
    if ( v0 > -2147023746 )
    {
      if ( v0 != -2147023743 )
      {
LABEL_10:
        sprintf(Text, "UNKNOWN %X\n", v0);
        MessageBoxA(nullptr, Text, aInit, 0x10u);
        return 0;
      }
      sprintf(Text, "Beta %X\n", -2147023743);
    }
    else
    {
      if ( v0 == -2147023746 )
      {
        sprintf(Text, "OLDDIRECTINPUTVERSION %X\n", -2147023746);
        MessageBoxA(nullptr, Text, aInit, 0x10u);
        return 0;
      }
      if ( v0 != -2147024882 )
      {
        if ( v0 == -2147024809 )
        {
          sprintf(Text, "Invalid %X\n", -2147024809);
          MessageBoxA(nullptr, Text, aInit, 0x10u);
          return 0;
        }
        goto LABEL_10;
      }
      sprintf(Text, "OUTOFMEMORY %X\n", -2147024882);
    }
    MessageBoxA(nullptr, Text, aInit, 0x10u);
    return 0;
  }
}
