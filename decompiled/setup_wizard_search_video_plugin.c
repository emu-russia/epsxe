#include "pch.h"
INT_PTR __stdcall search_video_plugin2(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4)
{
  int v4; // eax
  char v5; // cl
  CHAR *v6; // edi
  __int16 v7; // cx
  unsigned int v8; // eax
  INT_PTR result; // eax
  unsigned int v10; // eax
  HMODULE v11; // esi
  char v12; // al
  unsigned int v13; // eax
  HMODULE v14; // esi
  unsigned int v15; // eax
  HMODULE v16; // esi
  HMODULE LibraryA; // eax
  HMODULE v18; // esi
  FARPROC PSEgetLibVersion; // eax
  unsigned __int8 v20; // al
  int v21; // eax
  const char *v22; // eax
  LRESULT v23; // ebp
  int v24; // ebx
  CHAR *cFileName; // eax
  char *v26; // edx
  CHAR v27; // cl
  char *v28; // esi
  int v29; // edi
  char *v30; // eax
  char v31; // cl
  int v32; // ebp
  CHAR *v33; // eax
  CHAR v34; // cl
  int v35; // [esp-18h] [ebp-D68h]
  int v36; // [esp-14h] [ebp-D64h]
  char v37[12]; // [esp+0h] [ebp-D50h] BYREF
  HANDLE hFindFile; // [esp+Ch] [ebp-D44h]
  struct _WIN32_FIND_DATAA FindFileData; // [esp+10h] [ebp-D40h] BYREF
  CHAR LibFileName[1024]; // [esp+150h] [ebp-C00h] BYREF
  CHAR FileName[1024]; // [esp+550h] [ebp-800h] BYREF
  char lParam[1024]; // [esp+950h] [ebp-400h] BYREF

  strcpy(v37, "plugins\\");
  v4 = 0;
  do
  {
    v5 = v37[v4];
    FileName[v4++] = v5;
  }
  while ( v5 );
  v6 = &FileName[strlen(FileName) + 1];
  v7 = word_44E400;
  *(_DWORD *)--v6 = dword_44E3FC;
  *((_WORD *)v6 + 2) = v7;
  if ( a2 == 16 )
  {
    setup_wizard_step = 8;
    EndDialog(hDlg, 1);
    return 1;
  }
  if ( a2 == 272 )
  {
    hFindFile = FindFirstFileA(FileName, &FindFileData);
    if ( hFindFile == (HANDLE)-1 )
      MessageBoxA(nullptr, aEpsxeWasnTAble_0, aGpuPluginNotFo, 0x10u);
    dword_45B8E4 = 0;
    do
    {
      sprintf(LibFileName, "%s%s", v37, FindFileData.cFileName);
      LibraryA = LoadLibraryA(LibFileName);
      v18 = LibraryA;
      if ( LibraryA )
      {
        PSEgetLibType = GetProcAddress(LibraryA, aPsegetlibtype);
        PSEgetLibName = (int (__cdecl *)(_DWORD))GetProcAddress(v18, aPsegetlibname);
        PSEgetLibVersion = GetProcAddress(v18, aPsegetlibversi);
        unk_8A94C4 = (int (__cdecl *)(_DWORD))PSEgetLibVersion;
        if ( PSEgetLibType )
        {
          if ( PSEgetLibName )
          {
            if ( PSEgetLibVersion )
            {
              v20 = PSEgetLibVersion();
              v21 = unk_8A94C4(v20);
              v22 = (const char *)PSEgetLibName(BYTE1(v21));
              sprintf(lParam, "%s %d.%d", v22, v35, v36);
              if ( PSEgetLibType() == 2 )
              {
                v23 = SendDlgItemMessageA(hDlg, 1124, 0x180u, 0, (LPARAM)lParam);
                if ( !strcmp((const char *)&byte_8B1980, FindFileData.cFileName) )
                  SendDlgItemMessageA(hDlg, 1124, 0x186u, v23, 0);
                v24 = dword_45B8E4;
                if ( v23 == dword_45B8E4 )
                {
                  cFileName = FindFileData.cFileName;
                  v26 = (char *)byte_8A9540 + (dword_45B8E4 << 10) - (_DWORD)FindFileData.cFileName;
                  do
                  {
                    v27 = *cFileName;
                    cFileName[(_DWORD)v26] = *cFileName;
                    ++cFileName;
                  }
                  while ( v27 );
                }
                else
                {
                  if ( v23 < dword_45B8E4 )
                  {
                    v28 = (char *)&byte_8A9140 + 1024 * dword_45B8E4;
                    v29 = dword_45B8E4 - v23;
                    do
                    {
                      v30 = v28;
                      do
                      {
                        v31 = *v30;
                        v30[1024] = *v30;
                        ++v30;
                      }
                      while ( v31 );
                      v28 -= 1024;
                      --v29;
                    }
                    while ( v29 );
                  }
                  v32 = (v23 << 10) - (_DWORD)FindFileData.cFileName;
                  v33 = FindFileData.cFileName;
                  do
                  {
                    v34 = *v33;
                    v33[(_DWORD)byte_8A9540 + v32] = *v33;
                    ++v33;
                  }
                  while ( v34 );
                }
                dword_45B8E4 = v24 + 1;
              }
            }
          }
        }
      }
    }
    while ( FindNextFileA(hFindFile, &FindFileData) );
    if ( dword_45B8E4 == 1 )
    {
      SendDlgItemMessageA(hDlg, 1124, 0x186u, 0, 0);
      return 1;
    }
    return 1;
  }
  if ( a2 != 273 )
    return 0;
  switch ( (__int16)a3 )
  {
    case 1125:
      if ( !dword_45B8E4 )
        return 0;
      v13 = SendDlgItemMessageA(hDlg, 1124, 0x188u, 0, 0);
      if ( v13 == -1 || v13 >= dword_45B8E4 )
        return 0;
      sprintf(LibFileName, "%s%s", v37, (const char *)&byte_8A9540[256 * v13]);
      v14 = LoadLibraryA(LibFileName);
      GPUinit_0 = GetProcAddress(v14, ProcName);
      GPUconfigure_0 = GetProcAddress(v14, aGpuconfigure);
      GPUshutdown_0 = GetProcAddress(v14, aGpushutdown);
      GPUinit_0();
      GPUconfigure_0();
      GPUshutdown_0();
      return 0;
    case 1126:
      if ( !dword_45B8E4 )
        return 0;
      v10 = SendDlgItemMessageA(hDlg, 1124, 0x188u, 0, 0);
      if ( v10 == -1 || v10 >= dword_45B8E4 )
        return 0;
      sprintf(LibFileName, "%s%s", v37, (const char *)&byte_8A9540[256 * v10]);
      v11 = LoadLibraryA(LibFileName);
      GPUinit_0 = GetProcAddress(v11, ProcName);
      GPUtest_0 = GetProcAddress(v11, aGputest);
      GPUshutdown_0 = GetProcAddress(v11, aGpushutdown);
      GPUinit_0();
      v12 = GPUtest_0();
      if ( v12 )
      {
        if ( v12 == -1 )
          MessageBoxA(nullptr, aPluginNotWorki, aTestingGpuPlug, 0x10u);
        else
          MessageBoxA(nullptr, aUnkValue, aTestingGpuPlug, 0x40u);
        GPUshutdown_0();
        return 0;
      }
      else
      {
        MessageBoxA(nullptr, aPluginWorkingC, aTestingGpuPlug, 0x40u);
        GPUshutdown_0();
        return 0;
      }
    case 1127:
      --setup_wizard_step;
      EndDialog(hDlg, 1);
      return 1;
    case 1128:
      if ( !dword_45B8E4 )
        return 1;
      v8 = SendDlgItemMessageA(hDlg, 1124, 0x188u, 0, 0);
      if ( v8 != -1 && v8 < dword_45B8E4 )
      {
        sprintf(byte_8A84C0, "%s", (const char *)&byte_8A9540[256 * v8]);
        ++setup_wizard_step;
        EndDialog(hDlg, 1);
        return 1;
      }
      MessageBoxA(nullptr, aEpsxeDetectedT_0, aGpuPluginNotSe, 0x10u);
      result = 0;
      break;
    case 1129:
      if ( dword_45B8E4 )
      {
        v15 = SendDlgItemMessageA(hDlg, 1124, 0x188u, 0, 0);
        if ( v15 != -1 && v15 < dword_45B8E4 )
        {
          sprintf(LibFileName, "%s%s", v37, (const char *)&byte_8A9540[256 * v15]);
          v16 = LoadLibraryA(LibFileName);
          GPUinit_0 = GetProcAddress(v16, ProcName);
          GPUabout_0 = GetProcAddress(v16, aGpuabout);
          GPUshutdown_0 = GetProcAddress(v16, aGpushutdown);
          GPUinit_0();
          GPUabout_0();
          GPUshutdown_0();
        }
      }
      return 0;
    default:
      return 0;
  }
  return result;
}
