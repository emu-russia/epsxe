#include "pch.h"
LRESULT __stdcall cheat_dialog_callback(HWND hDlg, int a2, __int16 a3, int a4)
{
  LRESULT v4; // eax
  LRESULT v5; // esi
  LRESULT result; // eax
  LRESULT v7; // eax
  LRESULT v8; // esi
  FILE *v9; // ebp
  FILE *v10; // edi
  LRESULT v11; // eax
  LRESULT v12; // esi
  unsigned int i; // esi
  int v14; // [esp+10h] [ebp-C08h] BYREF
  int v15; // [esp+14h] [ebp-C04h] BYREF
  char lParam[1024]; // [esp+18h] [ebp-C00h] BYREF
  CHAR String[1024]; // [esp+418h] [ebp-800h] BYREF
  CHAR Buffer[1024]; // [esp+818h] [ebp-400h] BYREF

  if ( a2 == 272 )
  {
    for ( i = 0; i < (unsigned __int8)active_mini_cheat_count; ++i )
    {
      sprintf(lParam, "  %06x    %08x", mini_cheat_id_array[2 * i], mini_cheat_attr_array[2 * i]);
      SendDlgItemMessageA(hDlg, 1142, 0x180u, 0, (LPARAM)lParam);
    }
    return 1;
  }
  else if ( a2 == 273 )
  {
    switch ( a3 )
    {
      case 1056:
        if ( !open_file_dialog("Open PSX CHEAT", "PSX CHEATs (*.CHT)", temp_path, "cheats\\", "CHT") )
          return 0;
        v9 = fopen(temp_path, "r");
        while ( (v9->_flag & 0x10) == 0 )
        {
          sprintf(lParam, asc_44E24C);
          fgets(lParam, 1024, v9);
          if ( lParam[0] != 35 && sscanf(lParam, "%x %x", &v15, &v14) == 2 )
          {
            sprintf(lParam, "  %06x    %08x", v15 & 0x1FFFFF, v14);
            SendDlgItemMessageA(hDlg, 1142, 0x180u, 0, (LPARAM)lParam);
          }
        }
        fclose(v9);
        result = 0;
        break;
      case 1057:
        if ( open_file_dialog("Save PSX CHEAT", "PSX CHEATs (*.CHT)", temp_path, "cheats\\", "CHT") )
        {
          v10 = fopen(temp_path, aW);
          v11 = SendDlgItemMessageA(hDlg, 1142, 0x18Bu, 0, 0);
          if ( v11 )
          {
            do
            {
              v12 = v11 - 1;
              SendDlgItemMessageA(hDlg, 1142, 0x189u, v11 - 1, (LPARAM)lParam);
              sscanf(lParam, "  %06x    %08x", &v15, &v14);
              sprintf(lParam, "%x %x\n", v15, v14);
              fputs(lParam, v10);
              v11 = v12;
            }
            while ( v12 );
          }
          fclose(v10);
        }
        return 0;
      case 1058:
        v4 = SendDlgItemMessageA(hDlg, 1142, 0x18Bu, 0, 0);
        active_mini_cheat_count = 0;
        if ( v4 )
        {
          do
          {
            v5 = v4 - 1;
            SendDlgItemMessageA(hDlg, 1142, 0x189u, v4 - 1, (LPARAM)lParam);
            sscanf(
              lParam,
              "  %06x    %08x",
              &mini_cheat_id_array[2 * (unsigned __int8)active_mini_cheat_count],
              &mini_cheat_attr_array[2 * (unsigned __int8)active_mini_cheat_count]);
            v4 = v5;
            ++active_mini_cheat_count;
          }
          while ( v5 );
        }
        EndDialog(hDlg, 1);
        result = 1;
        break;
      case 1059:
        EndDialog(hDlg, 1);
        result = 1;
        break;
      case 1143:
        result = SendDlgItemMessageA(hDlg, 1142, 0x18Bu, 0, 0);
        if ( !result )
          return 0;
        do
        {
          v8 = result - 1;
          SendDlgItemMessageA(hDlg, 1142, 0x182u, result - 1, 0);
          result = v8;
        }
        while ( v8 );
        break;
      case 1144:
        v7 = SendDlgItemMessageA(hDlg, 1142, 0x188u, 0, 0);
        if ( v7 == -1 )
          return 0;
        SendDlgItemMessageA(hDlg, 1142, 0x182u, v7, 0);
        result = 0;
        break;
      case 1145:
        GetDlgItemTextA(hDlg, 1055, String, 1024);
        GetDlgItemTextA(hDlg, 1146, Buffer, 1024);
        sscanf(String, "%x", &v14);
        sscanf(Buffer, "%x", &v15);
        sprintf(lParam, "  %06x    %08x", v15, v14);
        SendDlgItemMessageA(hDlg, 1142, 0x180u, 0, (LPARAM)lParam);
        result = 0;
        break;
      default:
        return 0;
    }
  }
  else
  {
    return 0;
  }
  return result;
}
