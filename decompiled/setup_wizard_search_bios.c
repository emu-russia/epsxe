#include "pch.h"
INT_PTR __stdcall setup_wizard_search_bios(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  int v4; // eax
  char v5; // cl
  unsigned int v6; // eax
  int v8; // ebx
  FILE *v9; // edi
  uint8_t *v10; // esi
  int v11; // edi
  uint32_t v12; // eax
  _BIOS_DESCR *v13; // ecx
  LRESULT v14; // eax
  int v15; // ebp
  char *v16; // eax
  char *v17; // edx
  char v18; // cl
  char *v19; // edi
  int v20; // ebx
  char *v21; // ecx
  char v22; // dl
  char *v23; // ecx
  char *v24; // edx
  char v25; // al
  char v26[8]; // [esp+0h] [ebp-D4Ch] BYREF
  HANDLE hFindFile; // [esp+8h] [ebp-D44h]
  struct _WIN32_FIND_DATAA FindFileData; // [esp+Ch] [ebp-D40h] BYREF
  char Buffer[1024]; // [esp+14Ch] [ebp-C00h] BYREF
  CHAR FileName[1024]; // [esp+54Ch] [ebp-800h] BYREF
  char lParam[1024]; // [esp+94Ch] [ebp-400h] BYREF

  strcpy(v26, "bios\\");
  v4 = 0;
  do
  {
    v5 = v26[v4];
    FileName[v4++] = v5;
  }
  while ( v5 );
  strcat(FileName, "*.bin");
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
        v6 = SendDlgItemMessageA(hDlg, 1106, 0x188u, 0, 0);
        if ( v6 != -1 && v6 < dword_45B8E4 )
        {
          sprintf(byte_8A90C0, "%s", &byte_8A9540[1024 * v6]);
          ++setup_wizard_step;
          EndDialog(hDlg, 1);
          return 1;
        }
        MessageBoxA(
          nullptr,
          "ePSXe detected that you haven't selected a psx BIOS. Please, select some of the recommended psx BIOS and hit next button",
          "BIOS not selected",
          0x10u);
      }
    }
    return 0;
  }
  hFindFile = FindFirstFileA(FileName, &FindFileData);
  if ( hFindFile == (HANDLE)-1 )
    MessageBoxA(
      nullptr,
      "ePSXe wasn't able to find a psx bios in your epsxe\\bios directory. If you don't have a psx bios, enter either scp"
      "h1001.bin or scph7502 into your favorite internet search engine - but keep in mind that you can only have this fil"
      "e LEGALLY when you own a REAL Playstation",
      "psx bios not found",
      0x10u);
  dword_45B8E4 = 0;
  do
  {
    sprintf(Buffer, "%s%s", v26, FindFileData.cFileName);
    v8 = -1;
    v9 = fopen(Buffer, "rb");
    if ( v9 )
    {
      v10 = (uint8_t *)malloc(0x80000u);
      fread(v10, 0x80000u, 1u, v9);
      fclose(v9);
      v11 = calc_bios_checksum(v10, 0x80000);
      free(v10);
      v12 = 0;
      if ( debug_bios.crc )
      {
        v13 = retail_bioses;
        do
        {
          if ( v11 == v13->crc )
            v8 = v12;
          ++v12;
          ++v13;
        }
        while ( v12 < debug_bios.crc );
        if ( v8 != -1 )
        {
          sprintf(lParam, "%s", (const char *)(36 * v8 + 4513104));
          v14 = SendDlgItemMessageA(hDlg, 1106, 0x180u, 0, (LPARAM)lParam);
          v15 = dword_45B8E4;
          if ( v14 == dword_45B8E4 )
          {
            v16 = Buffer;
            v17 = &byte_8A9540[(dword_45B8E4 << 10) - (_DWORD)Buffer];
            do
            {
              v18 = *v16;
              v16[(_DWORD)v17] = *v16;
              ++v16;
            }
            while ( v18 );
          }
          else
          {
            if ( v14 < dword_45B8E4 )
            {
              v19 = &byte_8A9140[1024 * dword_45B8E4];
              v20 = dword_45B8E4 - v14;
              do
              {
                v21 = v19;
                do
                {
                  v22 = *v21;
                  v21[1024] = *v21;
                  ++v21;
                }
                while ( v22 );
                v19 -= 1024;
                --v20;
              }
              while ( v20 );
            }
            v23 = Buffer;
            v24 = &byte_8A9540[(v14 << 10) - (_DWORD)Buffer];
            do
            {
              v25 = *v23;
              v23[(_DWORD)v24] = *v23;
              ++v23;
            }
            while ( v25 );
          }
          dword_45B8E4 = v15 + 1;
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
