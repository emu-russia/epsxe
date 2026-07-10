#include "pch.h"
INT_PTR __stdcall search_bios(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  int v4; // eax
  char v5; // cl
  __int16 v6; // ax
  CHAR *v7; // edi
  unsigned int v8; // eax
  int v10; // ebx
  FILE *v11; // edi
  void *v12; // esi
  int v13; // edi
  unsigned int v14; // eax
  _DWORD *v15; // ecx
  LRESULT v16; // eax
  int v17; // ebp
  char *v18; // eax
  char *v19; // edx
  char v20; // cl
  char *v21; // edi
  int v22; // ebx
  char *v23; // ecx
  char v24; // dl
  char *v25; // ecx
  char *v26; // edx
  char v27; // al
  char v28[8]; // [esp+0h] [ebp-D4Ch] BYREF
  HANDLE hFindFile; // [esp+8h] [ebp-D44h]
  struct _WIN32_FIND_DATAA FindFileData; // [esp+Ch] [ebp-D40h] BYREF
  char Buffer[1024]; // [esp+14Ch] [ebp-C00h] BYREF
  CHAR FileName[1024]; // [esp+54Ch] [ebp-800h] BYREF
  char lParam[1024]; // [esp+94Ch] [ebp-400h] BYREF

  strcpy(v28, "bios\\");
  v4 = 0;
  do
  {
    v5 = v28[v4];
    FileName[v4++] = v5;
  }
  while ( v5 );
  v6 = MEMORY[0x44E80C];
  v7 = &FileName[strlen(FileName)];
  *(_DWORD *)v7 = aBin_0;
  *((_WORD *)v7 + 2) = v6;
  if ( a2 == 16 )
  {
    setup_wizard_step = 8;
    EndDialog(hDlg, 1);
    return 1;
  }
  if ( a2 != 272 )
  {
    if ( a2 == 273 )
    {
      if ( (unsigned __int16)a3 == 1107 )
      {
        --setup_wizard_step;
        EndDialog(hDlg, 1);
        return 1;
      }
      if ( (unsigned __int16)a3 == 1108 )
      {
        v8 = SendDlgItemMessageA(hDlg, 1106, 0x188u, 0, 0);
        if ( v8 != -1 && v8 < dword_45B8E4 )
        {
          sprintf(byte_8A90C0, "%s", (const char *)&byte_8A9540[256 * v8]);
          ++setup_wizard_step;
          EndDialog(hDlg, 1);
          return 1;
        }
        MessageBoxA(nullptr, aEpsxeDetectedT, aBiosNotSelecte, 0x10u);
      }
    }
    return 0;
  }
  hFindFile = FindFirstFileA(FileName, &FindFileData);
  if ( hFindFile == (HANDLE)-1 )
    MessageBoxA(nullptr, aEpsxeWasnTAble, aPsxBiosNotFoun, 0x10u);
  dword_45B8E4 = 0;
  do
  {
    sprintf(Buffer, "%s%s", v28, FindFileData.cFileName);
    v10 = -1;
    v11 = fopen(Buffer, Mode);
    if ( v11 )
    {
      v12 = malloc(0x80000u);
      fread(v12, 0x80000u, 1u, v11);
      fclose(v11);
      v13 = sub_407FA0(v12, 0x80000);
      free(v12);
      v14 = 0;
      if ( debug_bios )
      {
        v15 = &retail_bioses;
        do
        {
          if ( v13 == *v15 )
            v10 = v14;
          ++v14;
          v15 += 9;
        }
        while ( v14 < debug_bios );
        if ( v10 != -1 )
        {
          sprintf(lParam, "%s", (const char *)(36 * v10 + 4513104));
          v16 = SendDlgItemMessageA(hDlg, 1106, 0x180u, 0, (LPARAM)lParam);
          v17 = dword_45B8E4;
          if ( v16 == dword_45B8E4 )
          {
            v18 = Buffer;
            v19 = (char *)byte_8A9540 + (dword_45B8E4 << 10) - (_DWORD)Buffer;
            do
            {
              v20 = *v18;
              v18[(_DWORD)v19] = *v18;
              ++v18;
            }
            while ( v20 );
          }
          else
          {
            if ( v16 < dword_45B8E4 )
            {
              v21 = (char *)&byte_8A9140 + 1024 * dword_45B8E4;
              v22 = dword_45B8E4 - v16;
              do
              {
                v23 = v21;
                do
                {
                  v24 = *v23;
                  v23[1024] = *v23;
                  ++v23;
                }
                while ( v24 );
                v21 -= 1024;
                --v22;
              }
              while ( v22 );
            }
            v25 = Buffer;
            v26 = (char *)byte_8A9540 + (v16 << 10) - (_DWORD)Buffer;
            do
            {
              v27 = *v25;
              v25[(_DWORD)v26] = *v25;
              ++v25;
            }
            while ( v27 );
          }
          dword_45B8E4 = v17 + 1;
        }
      }
    }
  }
  while ( FindNextFileA(hFindFile, &FindFileData) );
  if ( dword_45B8E4 == 1 )
  {
    SendDlgItemMessageA(hDlg, 1106, 0x186u, 0, 0);
    return 1;
  }
  return 1;
}
