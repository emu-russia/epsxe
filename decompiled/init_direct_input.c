#include "pch.h"
int init_direct_input()
{
  HRESULT hr; // edi
  CHAR Text[256]; // [esp+8h] [ebp-100h] BYREF

  hr = DirectInputCreateA(hInst_For_DInput, 0x700, (int)&dword_4F7768, 0);
  if ( hr >= 0 )
  {
    if ( (*(int (__stdcall **)(int, void *, int *, _DWORD))(*(_DWORD *)dword_4F7768 + 12))(
           dword_4F7768,
           &unk_4485E0,
           &dword_4F7A5C,
           0) < 0 )
      return 0;
    if ( (*(int (__stdcall **)(int, void *))(*(_DWORD *)dword_4F7A5C + 44))(dword_4F7A5C, &unk_448758) < 0 )
      return 0;
    (*(void (__stdcall **)(int, int, int))(*(_DWORD *)dword_4F7A5C + 52))(dword_4F7A5C, hDlgInput, 6);
    if ( !point_device_enabled || byte_44DD19 )
      goto LABEL_25;
    if ( (*(int (__stdcall **)(int, void *, int *, _DWORD))(*(_DWORD *)dword_4F7768 + 12))(
           dword_4F7768,
           &unk_4485D0,
           &dword_4F75C8,
           0) < 0 )
      return 0;
    if ( (*(int (__stdcall **)(int, void *))(*(_DWORD *)dword_4F75C8 + 44))(dword_4F75C8, &unk_448740) < 0 )
      return 0;
    if ( (*(int (__stdcall **)(int, int, int))(*(_DWORD *)dword_4F75C8 + 52))(dword_4F75C8, hDlgInput, 5) >= 0 )
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
    sprintf(Text, "Error initializing DirectInput\n");
    MessageBoxA(nullptr, Text, "Init Error", 0x10u);
    if ( hr > DIERR_OLDDIRECTINPUTVERSION )
    {
      if ( hr != DIERR_BETADIRECTINPUTVERSION )
      {
LABEL_10:
        sprintf(Text, "UNKNOWN %X\n", hr);
        MessageBoxA(nullptr, Text, "Init", 0x10u);
        return 0;
      }
      sprintf(Text, "Beta %X\n", DIERR_BETADIRECTINPUTVERSION);
    }
    else
    {
      if ( hr == DIERR_OLDDIRECTINPUTVERSION )
      {
        sprintf(Text, "OLDDIRECTINPUTVERSION %X\n", DIERR_OLDDIRECTINPUTVERSION);
        MessageBoxA(nullptr, Text, "Init", 0x10u);
        return 0;
      }
      if ( hr != DIERR_OUTOFMEMORY )
      {
        if ( hr == DIERR_INVALIDPARAM )
        {
          sprintf(Text, "Invalid %X\n", DIERR_INVALIDPARAM);
          MessageBoxA(nullptr, Text, "Init", 0x10u);
          return 0;
        }
        goto LABEL_10;
      }
      sprintf(Text, "OUTOFMEMORY %X\n", DIERR_OUTOFMEMORY);
    }
    MessageBoxA(nullptr, Text, "Init", 0x10u);
    return 0;
  }
}
