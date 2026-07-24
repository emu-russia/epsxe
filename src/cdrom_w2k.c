#include "pch.h"

char W2k_find_cdrom_drive_letter()
{
  int v0; // ebx
  CHAR RootPathName[4]; // [esp+8h] [ebp-4h] BYREF

  v0 = 65;
  while ( 1 )
  {
    sprintf(RootPathName, "%c:\\", v0);
    if ( GetDriveTypeA(RootPathName) == 5 )
      break;
    if ( (unsigned int)++v0 > 0x5A )
      return 0;
  }
  return v0;
}

HANDLE __cdecl W2k_open_cdrom_device(unsigned __int8 a1)
{
  DWORD v1; // esi
  HANDLE result; // eax
  CHAR FileName[12]; // [esp+8h] [ebp-A0h] BYREF
  struct _OSVERSIONINFOA VersionInformation; // [esp+14h] [ebp-94h] BYREF

  memset(&VersionInformation, 0, sizeof(VersionInformation));
  VersionInformation.dwOSVersionInfoSize = 148;
  GetVersionExA(&VersionInformation);
  v1 = 0x80000000;
  if ( VersionInformation.dwPlatformId == 2 && VersionInformation.dwMajorVersion > 4 )
    v1 = 0xC0000000;
  wsprintfA(FileName, "\\\\.\\%c:", a1);
  result = CreateFileA(FileName, v1, 1u, nullptr, 3u, 0, nullptr);
  if ( result == (HANDLE)-1 )
    return CreateFileA(FileName, v1 ^ 0x40000000, 1u, nullptr, 3u, 0, nullptr);
  return result;
}

int __cdecl W2k_get_scsi_address(unsigned __int8 a1, _DWORD *a2, _DWORD *a3, _DWORD *a4)
{
  HANDLE v4; // ebx
  unsigned __int8 v6; // cl
  unsigned __int8 v7; // al
  DWORD BytesReturned; // [esp+8h] [ebp-404h] BYREF
  _DWORD OutBuffer[256]; // [esp+Ch] [ebp-400h] BYREF

  v4 = W2k_open_cdrom_device(a1);
  if ( v4 == (HANDLE)-1 )
  {
    printf(" %c error handle \n", a1);
    return -1;
  }
  else
  {
    memset(OutBuffer, 0, sizeof(OutBuffer));
    OutBuffer[0] = 8;
    if ( DeviceIoControl(v4, IOCTL_SCSI_GET_ADDRESS, nullptr, 0, OutBuffer, 8u, &BytesReturned, nullptr) )
    {
      v6 = BYTE2(OutBuffer[1]);
      *a2 = LOBYTE(OutBuffer[1]);
      v7 = HIBYTE(OutBuffer[1]);
      *a3 = v6;
      *a4 = v7;
      CloseHandle(v4);
      return 0;
    }
    else
    {
      printf(" %c: error \n", a1);
      return -1;
    }
  }
}

int __cdecl W2k_scsi_pass_through_direct(DWORD BytesReturned)
{
  DWORD v1; // ebp
  int v2; // edx
  int v3; // eax
  _DWORD InBuffer[20]; // [esp+Ch] [ebp-50h] BYREF

  v1 = BytesReturned;
  v2 = *(_DWORD *)(BytesReturned + 16);
  memset(InBuffer, 0, sizeof(InBuffer));
  v3 = *(_DWORD *)(BytesReturned + 12);
  BYTE2(InBuffer[1]) = *(_BYTE *)(BytesReturned + 21);
  InBuffer[3] = v3;
  InBuffer[5] = v2;
  LOWORD(InBuffer[0]) = 44;
  LOBYTE(InBuffer[2]) = 1;
  InBuffer[4] = 5;
  InBuffer[6] = 48;
  qmemcpy(&InBuffer[7], (const void *)(BytesReturned + 48), BYTE2(InBuffer[1]));
  if ( DeviceIoControl(
         hObject,
         IOCTL_SCSI_PASS_THROUGH_DIRECT,
         InBuffer,
         0x50u,
         InBuffer,
         0x50u,
         &BytesReturned,
         nullptr) )
  {
    *(_BYTE *)(v1 + 1) = 1;
  }
  else
  {
    *(_BYTE *)(v1 + 1) = 4;
    *(_BYTE *)(v1 + 23) = 4;
    GetLastError();
  }
  return *(unsigned __int8 *)(v1 + 1);
}

char W2k_cdrom_gettrackinfo()
{
  HANDLE EventA; // esi
  char result; // al
  unsigned __int8 v2; // bl
  int v3; // esi
  char v4; // [esp+12h] [ebp-5Eh]
  char v5; // [esp+13h] [ebp-5Dh]
  unsigned __int8 v6; // [esp+13h] [ebp-5Dh]
  unsigned int v7; // [esp+14h] [ebp-5Ch] BYREF
  int v8; // [esp+18h] [ebp-58h]
  int v9; // [esp+1Ch] [ebp-54h] BYREF
  DWORD BytesReturned[20]; // [esp+20h] [ebp-50h] BYREF

  v5 = 10;
  v4 = 0;
  do
  {
    if ( v4 )
      break;
    memset(BytesReturned, 0, sizeof(BytesReturned));
    memset(&byte_4FFC40, 0, 0x324u);
    EventA = CreateEventA(nullptr, 1, 0, nullptr);
    LOBYTE(BytesReturned[0]) = 2;
    BYTE2(BytesReturned[0]) = byte_457338;
    LOBYTE(BytesReturned[2]) = byte_4FD9D0;
    BYTE1(BytesReturned[2]) = byte_4FD9D4;
    HIBYTE(BytesReturned[0]) = 72;
    BytesReturned[3] = 804;
    BytesReturned[4] = (DWORD)&byte_4FFC40;
    LOWORD(BytesReturned[5]) = 2574;
    BytesReturned[6] = (DWORD)EventA;
    LOWORD(BytesReturned[12]) = 67;
    HIBYTE(BytesReturned[13]) = 3;
    LOBYTE(BytesReturned[14]) = 36;
    ResetEvent(EventA);
    if ( !W2k_scsi_pass_through_direct((DWORD)BytesReturned) )
      WaitForSingleObject(EventA, 0xFFFFFFFF);
    CloseHandle(EventA);
    if ( BYTE1(BytesReturned[0]) == 1 )
      v4 = 1;
    ++v5;
  }
  while ( v5 );
  if ( BYTE1(BytesReturned[0]) != 1 )
    return dbg_print(" * gettrackinfo error[%d]\n", BYTE1(BytesReturned[0]));
  dbg_print(" * First/Last track: %d %d\n", (unsigned __int8)byte_4FFC42, (unsigned __int8)byte_4FFC43);
  result = byte_4FFC43 - byte_4FFC42 + 1;
  v2 = 0;
  v6 = result;
  byte_4FD9E3 = result;
  LOBYTE(v8) = 0;
  if ( byte_4FFC43 - byte_4FFC42 != 0xFF )
  {
    do
    {
      v3 = (unsigned __int8)v8;
      dbg_print(" * Track %d: ", (unsigned __int8)byte_4FFC46[8 * (unsigned __int8)v8]);
      if ( (byte_4FFC45[8 * v3] & 4) != 0 )
      {
        dbg_print("(DATA)  -");
      }
      else
      {
        dbg_print("(AUDIO) -");
        if ( !v2 )
          nocd = 2;
      }
      W9x_bcd_to_dword(&v7, (unsigned __int8 *)(8 * v3 + 5241928));
      v7 += 150;
      dbg_print(" Start %d: (%02d,%02d,%02d) - ", v3, (unsigned __int8)(v7 / 0x4B / 0x3C), v7 / 0x4B % 0x3C, v7 % 0x4B);
      W9x_bcd_to_dword(&v7, (unsigned __int8 *)(8 * v3 + 5241928));
      W9x_bcd_to_dword(&v9, (unsigned __int8 *)(8 * v3 + 5241936));
      dbg_print(" Length %02d:%02d\n", (v9 - v7) / 0x4B / 0x3C, (v9 - v7) / 0x4B % 0x3C);
      result = v6;
      LOBYTE(v8) = ++v2;
    }
    while ( v2 < v6 );
  }
  return result;
}

BOOL W2k_resume_cdrom()
{
  HANDLE EventA; // esi
  DWORD BytesReturned[20]; // [esp+8h] [ebp-50h] BYREF

  BYTE1(dword_45733C) = (32 * byte_4FD9D4) | 1;
  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(BytesReturned, 0, sizeof(BytesReturned));
  BYTE2(BytesReturned[0]) = byte_457338;
  LOBYTE(BytesReturned[2]) = byte_4FD9D0;
  BYTE1(BytesReturned[2]) = byte_4FD9D4;
  LOBYTE(BytesReturned[0]) = 2;
  HIBYTE(BytesReturned[0]) = 80;
  LOWORD(BytesReturned[5]) = 2574;
  BytesReturned[3] = 0;
  BytesReturned[4] = 0;
  BytesReturned[6] = (DWORD)EventA;
  BytesReturned[12] = dword_45733C;
  BytesReturned[13] = dword_457340;
  LOWORD(BytesReturned[14]) = word_457344;
  ResetEvent(EventA);
  if ( !W2k_scsi_pass_through_direct((DWORD)BytesReturned) )
    WaitForSingleObject(EventA, 0xFFFFFFFF);
  if ( BYTE1(BytesReturned[0]) != 1 )
    printf(" * Resume cdrom error. \n");
  return CloseHandle(EventA);
}

char W2k_cdrom_init()
{
  char result; // al
  void *v1; // esp
  _BYTE v2[8092]; // [esp+0h] [ebp-1F9Ch] BYREF

  if ( !cdrom_letter )
  {
    cdrom_letter = W2k_find_cdrom_drive_letter();
    if ( !cdrom_letter )
      fatal_error_with_message_box(" * cdrom not found \n");
  }
  if ( !cd_savefake_flag )
    return cdrom_fake_load_file(cdrom_fake_filename);
  if ( cd_savefake_flag == 1 )
    cdrom_fake_create_file(cdrom_fake_filename);
  if ( loaded_file_type == 3 )
  {
    result = iso_load(bin_iso_file);
    sound_use_cdda = 0;
  }
  else
  {
    dbg_print(" * Init Core W2k cdrom ... ");
    W2k_get_scsi_address(cdrom_letter, &byte_457338, &byte_4FD9D0, &byte_4FD9D4);
    hObject = W2k_open_cdrom_device(cdrom_letter);
    if ( !hObject )
      sound_use_cdda = 0;
    W2k_cdrom_gettrackinfo();
    dbg_print("[%c] ok\n", cdrom_letter);
    v1 = alloca(8092);
    memset(v2, 0xAAu, sizeof(v2));
    dword_504C8C = 0;
    dword_4FFF80 = -1;
    W2k_read_sector_mode1(0, 2u, 0x10u, 2u, (DWORD)v2);
    result = v2[12];
    if ( !v2[12] && v2[13] == 2 && v2[14] == 22 && (result = v2[2364]) == 0 && v2[2365] == 2 && v2[2366] == 23 )
    {
      dword_504C8C = 1;
      dword_504C88 = 2352;
    }
    else if ( dword_504C8C != 1 )
    {
      memset(v2, 0xAAu, sizeof(v2));
      W2k_read_raw_sector(0, 2u, 0x10u, 2u, (DWORD)v2);
      result = v2[12];
      if ( !v2[12] && v2[13] == 2 && v2[14] == 22 )
      {
        result = v2[2364];
        if ( !v2[2364] && v2[2365] == 2 && v2[2366] == 23 )
        {
          dword_504C8C = 7;
          dword_504C88 = 2352;
        }
      }
    }
  }
  return result;
}

char __cdecl W2k_get_first_last_track(_BYTE *a1, _BYTE *a2)
{
  char result; // al

  *a1 = byte_4FFC42;
  result = byte_4FD9E3;
  *a2 = byte_4FD9E3;
  return result;
}

unsigned int __cdecl W2k_track_to_msf(int a1, _BYTE *a2, _BYTE *a3, _BYTE *a4)
{
  unsigned int result; // eax
  unsigned int v5; // eax
  unsigned int v6; // et2

  result = (unsigned __int8)byte_4FD9E3;
  if ( (__int16)a1 <= (int)(unsigned __int8)byte_4FD9E3 )
  {
    if ( (_WORD)a1 )
      W9x_bcd_to_dword(&a1, (unsigned __int8 *)(8 * (__int16)a1 + 5241920));
    else
      W9x_bcd_to_dword(&a1, (unsigned __int8 *)(8 * (unsigned __int8)byte_4FD9E3 + 5241928));
    v5 = (a1 + 150) / 0x4Bu;
    *a4 = (a1 + 150) % 0x4Bu;
    v6 = v5 % 0x3C;
    result = v5 / 0x3C;
    *a3 = v6;
    *a2 = result;
  }
  return result;
}

HANDLE W2k_cdrom_deinit()
{
  HANDLE result; // eax

  if ( cd_savefake_flag >= 0 )
    cdrom_fake_write();
  if ( loaded_file_type == 3 )
    iso_close();
  if ( dword_504C84 )
    free(dword_504C84);
  if ( byte_4FD9C8 && hObject )
    W2k_send_read_subchannel_command();
  if ( Stream )
    fclose(Stream);
  result = hObject;
  if ( hObject )
  {
    W2k_cdrom_stop();
    result = hObject;
    if ( hObject )
      return (HANDLE)CloseHandle(hObject);
  }
  return result;
}

char __cdecl W2k_find_track_by_min_sec(unsigned int a1, char a2)
{
  char v2; // bl
  unsigned __int8 v4; // [esp+8h] [ebp-4h]

  v4 = 0;
  if ( !byte_4FD9E3 )
    return 0;
  v2 = a1;
  while ( 1 )
  {
    W9x_bcd_to_dword(&a1, (unsigned __int8 *)(8 * v4 + 5241928));
    a1 += 150;
    if ( (unsigned __int8)(a1 / 0x4B / 0x3C) == v2 && a1 / 0x4B % 0x3C == a2 )
      break;
    if ( ++v4 >= (unsigned __int8)byte_4FD9E3 )
      return 0;
  }
  return a1 % 0x4B;
}

char __cdecl W2k_cdrom_play_cdda(unsigned int a1, int a2, unsigned __int8 a3)
{
  char result; // al
  unsigned __int8 v4; // bl
  HANDLE EventA; // esi
  DWORD BytesReturned[20]; // [esp+4h] [ebp-50h] BYREF

  result = sound_use_cdda;
  if ( sound_use_cdda )
  {
    v4 = a2;
    a3 = W2k_find_track_by_min_sec(a1, a2);
    BYTE1(dword_457350) = a3;
    HIBYTE(dword_45734C) = a1;
    LOBYTE(dword_457350) = v4;
    W9x_bcd_to_dword(&a2, (unsigned __int8 *)(8 * (unsigned __int8)byte_4FD9E3 + 5241928));
    LOBYTE(word_457354) = (a2 + 150) % 0x4Bu;
    BYTE2(dword_457350) = (a2 + 150) / 0x4Bu / 0x3C;
    HIBYTE(dword_457350) = (a2 + 150) / 0x4Bu % 0x3C;
    EventA = CreateEventA(nullptr, 1, 0, nullptr);
    memset(BytesReturned, 0, sizeof(BytesReturned));
    BYTE2(BytesReturned[0]) = byte_457338;
    LOBYTE(BytesReturned[2]) = byte_4FD9D0;
    BYTE1(BytesReturned[2]) = byte_4FD9D4;
    LOBYTE(BytesReturned[0]) = 2;
    HIBYTE(BytesReturned[0]) = 72;
    LOWORD(BytesReturned[5]) = 2574;
    BytesReturned[3] = 0;
    BytesReturned[4] = 0;
    BytesReturned[6] = (DWORD)EventA;
    BytesReturned[12] = dword_45734C;
    BytesReturned[13] = dword_457350;
    LOWORD(BytesReturned[14]) = word_457354;
    ResetEvent(EventA);
    if ( !W2k_scsi_pass_through_direct((DWORD)BytesReturned) )
      WaitForSingleObject(EventA, 0xFFFFFFFF);
    result = CloseHandle(EventA);
    if ( BYTE1(BytesReturned[0]) == 1 )
      dword_4FD9D8 = 1;
    else
      return printf(" * W2k play cdda error (%d, %d, %d) \n", (unsigned __int8)a1, v4, a3);
  }
  return result;
}

char W2k_cdrom_stop()
{
  char result; // al
  HANDLE EventA; // esi
  DWORD BytesReturned[20]; // [esp+0h] [ebp-50h] BYREF

  BYTE1(dword_457358) = (32 * byte_4FD9D4) | 1;
  result = sound_use_cdda;
  if ( sound_use_cdda )
  {
    result = dword_4FD9D8;
    if ( dword_4FD9D8 )
    {
      dword_4FD9D8 = 0;
      EventA = CreateEventA(nullptr, 1, 0, nullptr);
      memset(BytesReturned, 0, sizeof(BytesReturned));
      BYTE2(BytesReturned[0]) = byte_457338;
      LOBYTE(BytesReturned[2]) = byte_4FD9D0;
      BYTE1(BytesReturned[2]) = byte_4FD9D4;
      LOBYTE(BytesReturned[0]) = 2;
      HIBYTE(BytesReturned[0]) = 80;
      LOWORD(BytesReturned[5]) = 2574;
      BytesReturned[3] = 0;
      BytesReturned[4] = 0;
      BytesReturned[6] = (DWORD)EventA;
      BytesReturned[12] = dword_457358;
      BytesReturned[13] = dword_45735C;
      LOWORD(BytesReturned[14]) = word_457360;
      ResetEvent(EventA);
      if ( !W2k_scsi_pass_through_direct((DWORD)BytesReturned) )
        WaitForSingleObject(EventA, 0xFFFFFFFF);
      if ( BYTE1(BytesReturned[0]) != 1 )
        printf(" * W2k stop cdrom error. \n");
      result = CloseHandle(EventA);
      dword_4FD9DC = 1;
    }
  }
  return result;
}

void W2k_reset_cdda_state()
{
  dword_4FD9D8 = 0;
  dword_457348 = -1;
  sub_42CDE0();
}

char __cdecl W2k_msf_to_lba(
        unsigned int a1,
        unsigned __int8 a2,
        unsigned __int8 a3,
        _BYTE *a4,
        _BYTE *a5,
        _BYTE *a6,
        _BYTE *a7)
{
  unsigned __int8 v7; // bl
  unsigned int v8; // ebp
  char result; // al
  unsigned int v10; // ecx
  unsigned __int8 v11; // [esp+10h] [ebp-4h]

  v7 = 0;
  v11 = 0;
  v8 = (a3 & 0xF) % 10
     + 75
     * ((a2 & 0xF) % 10 + 10 * ((a2 >> 4) + 6 * ((unsigned __int8)(a1 & 0xF) % 10 + 10 * ((unsigned __int8)a1 >> 4))))
     + 10 * (a3 >> 4)
     - 150;
  W9x_bcd_to_dword(&a1, (unsigned __int8 *)(8 * (unsigned __int8)byte_4FD9E3 + 5241928));
  if ( a1 > v8 && byte_4FD9E3 )
  {
    while ( 1 )
    {
      W9x_bcd_to_dword(&a1, (unsigned __int8 *)(8 * v11 + 5241936));
      if ( v11 + 1 < (unsigned __int8)byte_4FD9E3 )
        a1 -= a1 % 0x4B;
      if ( a1 > v8 )
        break;
      v11 = ++v7;
      if ( v7 >= (unsigned __int8)byte_4FD9E3 )
        goto LABEL_7;
    }
    W9x_bcd_to_dword(&a1, (unsigned __int8 *)(8 * v11 + 5241928));
    v10 = v8 + a1 % 0x4B - a1;
    *a4 = (v11 + 1) % 10 + 16 * ((v11 + 1) / 10);
    *a5 = v10 / 0x4B / 0x3C % 0xA + 16 * (v10 / 0x4B / 0x3C / 0xA);
    *a6 = v10 / 0x4B % 0x3C % 0xA + 16 * (v10 / 0x4B % 0x3C / 0xA);
    result = v10 % 0x4B % 0xA + 16 * (v10 % 0x4B / 0xA);
    *a7 = result;
  }
  else
  {
LABEL_7:
    result = (char)a4;
    *a4 = -86;
  }
  return result;
}

char __cdecl W2k_lba_to_msf(
        unsigned int a1,
        unsigned __int8 a2,
        unsigned __int8 a3,
        _BYTE *a4,
        unsigned __int8 *a5,
        unsigned __int8 *a6)
{
  char v6; // bl
  unsigned int v7; // esi
  unsigned __int8 *v8; // ecx
  unsigned __int8 v9; // dl
  unsigned __int8 *v10; // eax
  unsigned int v11; // ecx
  unsigned int v12; // et2
  unsigned __int8 v14; // [esp+10h] [ebp-4h]

  v6 = a1;
  v14 = 0;
  v7 = (a3 & 0xF) % 10
     + 75
     * ((a2 & 0xF) % 10 + 10 * ((a2 >> 4) + 6 * ((unsigned __int8)(a1 & 0xF) % 10 + 10 * ((unsigned __int8)a1 >> 4))))
     + 10 * (a3 >> 4);
  W9x_bcd_to_dword(&a1, (unsigned __int8 *)(8 * (unsigned __int8)byte_4FD9E3 + 5241928));
  if ( a1 > v7 )
  {
    LOBYTE(v10) = byte_4FD9E3;
    if ( byte_4FD9E3 )
    {
      while ( 1 )
      {
        W9x_bcd_to_dword(&a1, (unsigned __int8 *)(8 * v14 + 5241936));
        if ( a1 > v7 )
          break;
        LOBYTE(v10) = ++v14;
        if ( v14 >= (unsigned __int8)byte_4FD9E3 )
          return (char)v10;
      }
      v11 = a1 % 0x4B;
      v12 = a1 / 0x4B % 0x3C;
      *a4 = a1 / 0x4B / 0x3C;
      LOBYTE(v10) = (_BYTE)a5;
      *a5 = v12;
      *a6 = v11;
    }
  }
  else
  {
    v8 = a5;
    v9 = a2;
    *a4 = v6;
    v10 = a6;
    *v8 = v9;
    *v10 = a3;
  }
  return (char)v10;
}

unsigned __int8 __cdecl W2k_check_subchannel_data(unsigned int a1, unsigned __int8 a2, unsigned __int8 a3, int a4)
{
  char v4; // bl
  char v5; // cl
  unsigned __int8 result; // al
  char v7; // [esp+Fh] [ebp-1h]
  unsigned __int8 v8; // [esp+18h] [ebp+8h]
  unsigned __int8 v9; // [esp+18h] [ebp+8h]
  unsigned __int8 v10; // [esp+1Ch] [ebp+Ch]
  unsigned __int8 v11; // [esp+1Ch] [ebp+Ch]
  unsigned __int8 v12; // [esp+1Ch] [ebp+Ch]

  *(_DWORD *)a4 = 0;
  *(_DWORD *)(a4 + 4) = 0;
  v7 = 0;
  if ( (_BYTE)dword_5053E0 )
  {
    if ( a3 )
    {
      v10 = a3 - 1;
    }
    else
    {
      v10 = 74;
      if ( a2 )
      {
        --a2;
      }
      else
      {
        a2 = 59;
        LOBYTE(a1) = a1 - 1;
      }
    }
    v4 = (unsigned __int8)a1 % 10 + 16 * ((unsigned __int8)a1 / 10);
    v8 = a2 % 10 + 16 * (a2 / 10);
    v11 = v10 % 10 + 16 * (v10 / 10);
    *(_DWORD *)a4 = *(int *)((char *)&dword_5053E0 + 1);
    *(_BYTE *)(a4 + 4) = BYTE1(dword_5053E4);
    *(_WORD *)(a4 + 5) = *(_WORD *)((char *)&dword_5053E4 + 3);
    *(_BYTE *)(a4 + 7) = BYTE1(dword_5053E8);
    if ( v4 != *(_BYTE *)(a4 + 5) )
      v7 = 1;
    if ( v4 != *(_BYTE *)(a4 + 2) )
      ++v7;
    if ( v8 != *(_BYTE *)(a4 + 6) )
      ++v7;
    v5 = v7;
    if ( ((v8 & 0xF) % 10 + 10 * (v8 >> 4) - 2) % 10 + 16 * (((v8 & 0xF) % 10 + 10 * (v8 >> 4) - 2) / 10) != *(unsigned __int8 *)(a4 + 3) )
      v5 = v7 + 1;
    result = v11;
    if ( v11 != *(_BYTE *)(a4 + 7) )
      ++v5;
    if ( v11 != *(_BYTE *)(a4 + 4) )
      ++v5;
    if ( (unsigned __int8)v5 >= 2u )
    {
      result = 0;
      *(_DWORD *)(a4 + 2) = 0;
      *(_WORD *)(a4 + 6) = 0;
      if ( v4 == 3 )
        byte_4F8320 = 1;
    }
  }
  else
  {
    LOBYTE(a1) = (unsigned __int8)a1 % 10 + 16 * ((unsigned __int8)a1 / 10);
    v9 = a2 % 10 + 16 * (a2 / 10);
    v12 = a3 % 10 + 16 * (a3 / 10);
    W2k_msf_to_lba(a1, v9, v12, (_BYTE *)a4, (_BYTE *)(a4 + 2), (_BYTE *)(a4 + 3), (_BYTE *)(a4 + 4));
    *(_BYTE *)(a4 + 1) = 1;
    *(_BYTE *)(a4 + 5) = a1;
    *(_BYTE *)(a4 + 6) = v9;
    *(_BYTE *)(a4 + 7) = v12;
    return v12;
  }
  return result;
}

bool __cdecl W2k_send_scsi_command(const void *a1, unsigned int a2, DWORD a3, DWORD a4)
{
  HANDLE EventA; // ebx
  DWORD BytesReturned[20]; // [esp+Ch] [ebp-50h] BYREF

  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(BytesReturned, 0, sizeof(BytesReturned));
  LOBYTE(BytesReturned[2]) = byte_4FD9D0;
  BytesReturned[4] = a3;
  BYTE1(BytesReturned[2]) = byte_4FD9D4;
  BYTE2(BytesReturned[0]) = byte_457338;
  BytesReturned[3] = a4;
  LOBYTE(BytesReturned[0]) = 2;
  HIBYTE(BytesReturned[0]) = 72;
  LOWORD(BytesReturned[5]) = 3086;
  BytesReturned[6] = (DWORD)EventA;
  qmemcpy(&BytesReturned[12], a1, a2);
  ResetEvent(EventA);
  if ( !W2k_scsi_pass_through_direct((DWORD)BytesReturned) )
    WaitForSingleObject(EventA, 0xFFFFFFFF);
  CloseHandle(EventA);
  return BYTE1(BytesReturned[0]) != 1;
}

int W2k_send_read_toc_command()
{
  HANDLE EventA; // esi
  _BYTE v2[10]; // [esp+8h] [ebp-5Ch] BYREF
  _BYTE v3[2]; // [esp+12h] [ebp-52h] BYREF
  DWORD BytesReturned[20]; // [esp+14h] [ebp-50h] BYREF

  v2[0] = 0;
  v2[1] = 0;
  v2[2] = 0;
  v2[3] = 8;
  v2[4] = 0;
  v2[5] = 0;
  v2[6] = 0;
  v2[7] = 0;
  v2[8] = 0;
  v2[9] = 0;
  qmemcpy(v3, "\t0", sizeof(v3));
  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(BytesReturned, 0, sizeof(BytesReturned));
  BYTE2(BytesReturned[0]) = byte_457338;
  LOBYTE(BytesReturned[2]) = byte_4FD9D0;
  LOBYTE(BytesReturned[0]) = 2;
  BYTE1(BytesReturned[2]) = byte_4FD9D4;
  HIBYTE(BytesReturned[0]) = 64;
  BytesReturned[3] = 12;
  BytesReturned[4] = (DWORD)v2;
  LOWORD(BytesReturned[5]) = 1550;
  BytesReturned[6] = (DWORD)EventA;
  LOBYTE(BytesReturned[12]) = 21;
  LOBYTE(BytesReturned[13]) = 12;
  ResetEvent(EventA);
  if ( !W2k_scsi_pass_through_direct((DWORD)BytesReturned) )
    WaitForSingleObject(EventA, 0xFFFFFFFF);
  return BYTE1(BytesReturned[0]) != 1 ? 4 : 1;
}

int W2k_send_read_subchannel_command()
{
  HANDLE EventA; // esi
  _BYTE v2[4]; // [esp+8h] [ebp-5Ch] BYREF
  char v3[8]; // [esp+Ch] [ebp-58h] BYREF
  DWORD BytesReturned[20]; // [esp+14h] [ebp-50h] BYREF

  v2[0] = 0;
  v2[1] = 0;
  v2[2] = 0;
  v2[3] = 8;
  strcpy(v3, "S");
  v3[2] = 0;
  v3[3] = 0;
  v3[4] = 0;
  v3[5] = 0;
  v3[6] = 8;
  v3[7] = 0;
  byte_4FD9C8 = 0;
  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(BytesReturned, 0, sizeof(BytesReturned));
  BYTE2(BytesReturned[0]) = byte_457338;
  LOBYTE(BytesReturned[2]) = byte_4FD9D0;
  LOBYTE(BytesReturned[0]) = 2;
  BYTE1(BytesReturned[2]) = byte_4FD9D4;
  HIBYTE(BytesReturned[0]) = 68;
  BytesReturned[3] = 12;
  BytesReturned[4] = (DWORD)v2;
  LOWORD(BytesReturned[5]) = 1550;
  BytesReturned[6] = (DWORD)EventA;
  LOBYTE(BytesReturned[12]) = 21;
  LOBYTE(BytesReturned[13]) = 12;
  ResetEvent(EventA);
  if ( !W2k_scsi_pass_through_direct((DWORD)BytesReturned) )
    WaitForSingleObject(EventA, 0xFFFFFFFF);
  return BYTE1(BytesReturned[0]) != 1 ? 4 : 1;
}

bool __cdecl W2k_read_raw_sector(
        unsigned __int8 a1,
        unsigned __int8 a2,
        unsigned __int8 a3,
        unsigned __int8 a4,
        DWORD a5)
{
  char v6; // [esp+4h] [ebp-Ch] BYREF
  __int16 v7; // [esp+5h] [ebp-Bh]
  char v8; // [esp+7h] [ebp-9h]
  char v9; // [esp+8h] [ebp-8h]
  __int16 v10; // [esp+9h] [ebp-7h]
  char v11; // [esp+Bh] [ebp-5h]
  int v12; // [esp+Ch] [ebp-4h]

  if ( !byte_4FD9C8 )
  {
    if ( W2k_send_read_toc_command() != 1 )
      return 1;
    byte_4FD9C8 = 1;
  }
  v11 = 0;
  v7 = 0;
  v12 = a4;
  v8 = (75 * (a2 + 60 * a1) + (unsigned int)a3 - 150) >> 16;
  v6 = 40;
  v9 = (unsigned __int16)(75 * (a2 + 60 * a1) + a3 - 150) >> 8;
  v10 = (unsigned __int8)(75 * (a2 + 60 * a1) + a3 + 106);
  return W2k_send_scsi_command(&v6, 0xAu, a5, 2352 * a4);
}

bool __cdecl W2k_read_sector_with_subchannel_output(
        unsigned __int8 a1,
        unsigned __int8 a2,
        unsigned __int8 a3,
        unsigned __int8 a4,
        DWORD a5,
        _DWORD *a6)
{
  bool result; // al
  int v7; // esi
  _DWORD *v9; // ecx
  _DWORD *v10; // ebx
  int v11; // edi
  char v12; // [esp+4h] [ebp-Ch] BYREF
  __int16 v13; // [esp+5h] [ebp-Bh]
  char v14; // [esp+7h] [ebp-9h]
  char v15; // [esp+8h] [ebp-8h]
  __int16 v16; // [esp+9h] [ebp-7h]
  char v17; // [esp+Bh] [ebp-5h]
  int v18; // [esp+Ch] [ebp-4h]

  if ( !byte_4FD9C8 )
  {
    if ( W2k_send_read_toc_command() != 1 )
      return 1;
    byte_4FD9C8 = 1;
  }
  v17 = 0;
  v16 = (unsigned __int8)(75 * (a2 + 60 * a1) + a3 + 106);
  v18 = 0x10000;
  v13 = 0;
  v7 = a4;
  v14 = (75 * (a2 + 60 * a1) + (unsigned int)a3 - 150) >> 16;
  v12 = -40;
  v15 = (unsigned __int16)(75 * (a2 + 60 * a1) + a3 - 150) >> 8;
  BYTE1(v18) = a4;
  result = W2k_send_scsi_command(&v12, 0xCu, a5, 2368 * a4);
  if ( a4 )
  {
    v9 = (_DWORD *)(a5 + 2352);
    do
    {
      v10 = a6;
      *a6 = *v9;
      a6[1] = v9[1];
      a6[2] = v9[2];
      v11 = v9[3];
      v9 += 592;
      a6 += 4;
      --v7;
      v10[3] = v11;
    }
    while ( v7 );
  }
  return result;
}

bool __cdecl W2k_read_sector_mode1(
        unsigned __int8 a1,
        unsigned __int8 a2,
        unsigned __int8 a3,
        unsigned __int8 a4,
        DWORD a5)
{
  char v6; // [esp+0h] [ebp-Ch] BYREF
  __int16 v7; // [esp+1h] [ebp-Bh]
  char v8; // [esp+3h] [ebp-9h]
  char v9; // [esp+4h] [ebp-8h]
  __int16 v10; // [esp+5h] [ebp-7h]
  char v11; // [esp+7h] [ebp-5h]
  unsigned __int8 v12; // [esp+8h] [ebp-4h]
  char v13; // [esp+9h] [ebp-3h]
  __int16 v14; // [esp+Ah] [ebp-2h]

  v11 = 0;
  v14 = 0;
  v10 = (unsigned __int8)(75 * (a2 + 60 * a1) + a3 + 106);
  v7 = 0;
  v12 = a4;
  v8 = (75 * (a2 + 60 * a1) + (unsigned int)a3 - 150) >> 16;
  v6 = -66;
  v9 = (unsigned __int16)(75 * (a2 + 60 * a1) + a3 - 150) >> 8;
  v13 = -8;
  return W2k_send_scsi_command(&v6, 0xCu, a5, 2352 * a4);
}

bool __cdecl W2k_read_sector_mode2(
        unsigned __int8 a1,
        unsigned __int8 a2,
        unsigned __int8 a3,
        unsigned __int8 a4,
        DWORD a5)
{
  char v6; // [esp+0h] [ebp-Ch] BYREF
  __int16 v7; // [esp+1h] [ebp-Bh]
  char v8; // [esp+3h] [ebp-9h]
  char v9; // [esp+4h] [ebp-8h]
  __int16 v10; // [esp+5h] [ebp-7h]
  char v11; // [esp+7h] [ebp-5h]
  unsigned __int8 v12; // [esp+8h] [ebp-4h]
  char v13; // [esp+9h] [ebp-3h]
  __int16 v14; // [esp+Ah] [ebp-2h]

  v11 = 0;
  v10 = (unsigned __int8)(75 * (a2 + 60 * a1) + a3 + 106);
  v7 = 0;
  v12 = a4;
  v8 = (75 * (a2 + 60 * a1) + (unsigned int)a3 - 150) >> 16;
  v6 = -66;
  v9 = (unsigned __int16)(75 * (a2 + 60 * a1) + a3 - 150) >> 8;
  v13 = -8;
  v14 = 2;
  return W2k_send_scsi_command(&v6, 0xCu, a5, 2368 * a4);
}

bool __cdecl W2k_read_sector_mode3(
        unsigned __int8 a1,
        unsigned __int8 a2,
        unsigned __int8 a3,
        unsigned __int8 a4,
        DWORD a5)
{
  char v6; // [esp+0h] [ebp-Ch] BYREF
  __int16 v7; // [esp+1h] [ebp-Bh]
  char v8; // [esp+3h] [ebp-9h]
  char v9; // [esp+4h] [ebp-8h]
  __int16 v10; // [esp+5h] [ebp-7h]
  char v11; // [esp+7h] [ebp-5h]
  __int16 v12; // [esp+8h] [ebp-4h]
  __int16 v13; // [esp+Ah] [ebp-2h]

  v11 = 0;
  v10 = (unsigned __int8)(75 * (a2 + 60 * a1) + a3 + 106);
  v12 = a4;
  v8 = (75 * (a2 + 60 * a1) + (unsigned int)a3 - 150) >> 16;
  v6 = -66;
  v7 = 4;
  v9 = (unsigned __int16)(75 * (a2 + 60 * a1) + a3 - 150) >> 8;
  v13 = 2;
  return W2k_send_scsi_command(&v6, 0xCu, a5, 16 * a4);
}

bool __cdecl W2k_send_subchannel_command(int a1)
{
  __int16 v2; // [esp+0h] [ebp-Ch] BYREF
  char v3; // [esp+2h] [ebp-Ah]
  char v4; // [esp+3h] [ebp-9h]
  char v5; // [esp+4h] [ebp-8h]
  char v6; // [esp+5h] [ebp-7h]
  __int16 v7; // [esp+6h] [ebp-6h]
  __int16 v8; // [esp+8h] [ebp-4h]

  v7 = 0;
  v8 = 0;
  v3 = HIBYTE(a1);
  v4 = BYTE2(a1);
  v2 = 43;
  v5 = BYTE1(a1);
  v6 = a1;
  return W2k_send_scsi_command(&v2, 0xAu, 0, 0);
}

bool __cdecl W2k_get_subchannel_status(_DWORD *a1)
{
  _DWORD v2[2]; // [esp+0h] [ebp-Ch] BYREF
  char v3[4]; // [esp+8h] [ebp-4h]

  v2[1] = 0;
  v3[1] = 0;
  *a1 = 0;
  a1[1] = 0;
  a1[2] = 0;
  a1[3] = 0;
  v2[0] = 0x1400242;
  v3[0] = 16;
  return W2k_send_scsi_command(v2, 0xAu, (DWORD)a1, 0x10u);
}

char W2k_cdrom_subchannel_read()
{
  char result; // al
  int v1; // ebp
  FILE *v2; // esi
  int v3; // esi
  int v4; // ebx
  int v5; // edi
  _DWORD *v6; // eax
  int v7; // ecx
  int v8; // edi
  int v9; // esi
  _DWORD *v10; // eax
  FILE *v11; // eax
  FILE *v12; // esi
  int v13; // ebp
  unsigned __int8 i; // bl
  char *v15; // edi
  FILE *v16; // eax
  FILE *v17; // esi
  int v18; // esi
  unsigned __int8 v19; // al
  int v20; // ecx
  _DWORD *v21; // esi
  int v22; // ebp
  _DWORD *v23; // edx
  int v24; // eax
  bool v25; // cf
  FILE *v26; // esi
  int v27; // esi
  unsigned __int8 j; // bl
  int v29; // eax
  _DWORD *v30; // ecx
  int v31; // edx
  _DWORD *v32; // esi
  int v33; // edi
  FILE *v34; // eax
  int v35; // ebp
  unsigned __int8 k; // bl
  char *v37; // edi
  FILE *v38; // esi
  int v39; // [esp+10h] [ebp-5208h]
  unsigned __int8 v40; // [esp+10h] [ebp-5208h]
  unsigned __int8 v41; // [esp+10h] [ebp-5208h]
  unsigned __int8 v42; // [esp+10h] [ebp-5208h]
  unsigned __int8 v43; // [esp+10h] [ebp-5208h]
  char v44; // [esp+14h] [ebp-5204h]
  _DWORD v45[256]; // [esp+18h] [ebp-5200h] BYREF
  char Buffer[1024]; // [esp+418h] [ebp-4E00h] BYREF
  _WORD v47[9472]; // [esp+818h] [ebp-4A00h] BYREF

  result = cd_savefake_flag;
  dword_4FFF80 = -1;
  if ( cd_savefake_flag && loaded_file_type != 3 )
  {
    v1 = 1;
    if ( dword_504C8C != 7 && dword_504C8C != 1 )
    {
      result = dbg_print(" * Warning: cdrom read mode unknown. \n");
      dword_504C8C = 1;
      return result;
    }
    result = use_subchannel;
    if ( use_subchannel )
    {
      sprintf(Buffer, "%s%s.SUB", "patches\\", ppf_default_filename);
      Stream = fopen(Buffer, "rb");
      if ( Stream )
      {
        if ( dword_504C8C == 1 )
        {
          dword_504C8C = 5;
          result = dbg_print(" * Subchannel support from clonecd .sub file. \n");
          BYTE1(byte_455945) = 0;
        }
        else
        {
          if ( dword_504C8C == 7 )
            dword_504C8C = 9;
          result = dbg_print(" * Subchannel support from clonecd .sub file. \n");
          BYTE1(byte_455945) = 0;
        }
        return result;
      }
      sprintf(Buffer, "%s%s.M3S", "patches\\", ppf_default_filename);
      v2 = fopen(Buffer, "rb");
      if ( v2 )
      {
        dword_504C84 = malloc(0x11940u);
        fread(dword_504C84, 1u, 0x11940u, v2);
        fclose(v2);
        if ( dword_504C8C == 1 )
        {
          dword_504C8C = 6;
          result = dbg_print(" * Subchannel support from .m3s file. \n");
          BYTE1(byte_455945) = 0;
        }
        else
        {
          if ( dword_504C8C == 7 )
            dword_504C8C = 10;
          result = dbg_print(" * Subchannel support from .m3s file. \n");
          BYTE1(byte_455945) = 0;
        }
        return result;
      }
      if ( SubchannelW2kCaching )
      {
        dbg_print(" * Checking subchannel read standard ... \n");
        dword_504C84 = malloc(0x11940u);
        v39 = 2;
        do
        {
          dbg_print(" * Cdrom precaching subchannel ... (step %d/2) ", v1);
          v3 = 12600;
          v4 = 70;
          do
          {
            W2k_send_subchannel_command(v3);
            v5 = 75;
            do
            {
              W2k_get_subchannel_status(v45);
              if ( BYTE1(v45[2]) % 10 + 16 * (BYTE1(v45[2]) / 10) == 3
                && BYTE2(v45[2]) < 0x3Cu
                && HIBYTE(v45[2]) < 0x4Bu )
              {
                v6 = (char *)dword_504C84 + 1200 * BYTE2(v45[2]) + 16 * HIBYTE(v45[2]);
                *v6 = v45[0];
                v6[1] = v45[1];
                v6[2] = v45[2];
                v6[3] = v45[3];
              }
              --v5;
            }
            while ( v5 );
            v3 += 75;
            --v4;
          }
          while ( v4 );
          dbg_print("ok\n");
          ++v1;
          --v39;
        }
        while ( v39 );
        dbg_print(" * Fixating subchanel ... ");
        v7 = 0;
        v8 = 60;
        do
        {
          v9 = 75;
          do
          {
            v10 = (char *)dword_504C84 + v7;
            v45[0] = *(_DWORD *)((char *)dword_504C84 + v7);
            v45[1] = *(_DWORD *)((char *)dword_504C84 + v7 + 4);
            v45[2] = *(_DWORD *)((char *)dword_504C84 + v7 + 8);
            v45[3] = *(_DWORD *)((char *)dword_504C84 + v7 + 12);
            *v10 = 0;
            v10[1] = 0;
            v10[2] = 0;
            v10[3] = 0;
            *((_BYTE *)dword_504C84 + v7) = 65;
            *(_WORD *)((char *)dword_504C84 + v7 + 1) = HIWORD(v45[1]);
            v7 += 16;
            *((char *)dword_504C84 + v7 - 13) = BYTE1(v45[3]) % 10 + 16 * (BYTE1(v45[3]) / 10);
            *((char *)dword_504C84 + v7 - 12) = BYTE2(v45[3]) % 10 + 16 * (BYTE2(v45[3]) / 10);
            *((char *)dword_504C84 + v7 - 11) = HIBYTE(v45[3]) % 10 + 16 * (HIBYTE(v45[3]) / 10);
            *((char *)dword_504C84 + v7 - 9) = BYTE1(v45[2]) % 10 + 16 * (BYTE1(v45[2]) / 10);
            *((char *)dword_504C84 + v7 - 8) = BYTE2(v45[2]) % 10 + 16 * (BYTE2(v45[2]) / 10);
            --v9;
            *((char *)dword_504C84 + v7 - 7) = HIBYTE(v45[2]) % 10 + 16 * (HIBYTE(v45[2]) / 10);
          }
          while ( v9 );
          --v8;
        }
        while ( v8 );
        dword_504C8C = 6;
        sprintf(Buffer, "%s%s.M3S", "patches\\", ppf_default_filename);
        v11 = fopen(Buffer, "wb");
        v12 = v11;
        if ( v11 )
        {
          fwrite(dword_504C84, 1u, 0x11940u, v11);
          fclose(v12);
        }
        goto LABEL_36;
      }
      result = SubchannelW2kCdromEnabled;
      if ( !SubchannelW2kCdromEnabled )
        return result;
      dbg_print(" * Checking subchannel read from cdrom ... ");
      if ( dword_504C8C == 7 )
      {
        W2k_read_sector_with_subchannel_output(0, 2u, 0x10u, 2u, (DWORD)v47, v45);
        result = HIBYTE(v45[1]);
        if ( HIBYTE(v45[1]) )
          return result;
        result = v45[2];
        if ( LOWORD(v45[2]) != 5634 )
          return result;
        result = HIBYTE(v45[5]);
        if ( *(_WORD *)((char *)&v45[5] + 3) != 512 || BYTE1(v45[6]) != 23 )
          return result;
        dword_504C8C = 8;
        dword_504C88 = 2352;
        if ( SubchannelW2kCaching )
        {
          dword_504C84 = malloc(0x11940u);
          dbg_print(" YES.\n");
          dbg_print(" * Cdrom precaching subchannel ... ");
          v40 = 0;
          v13 = 0;
          do
          {
            for ( i = 0; i < 0x4Bu; i += 5 )
            {
              W2k_read_sector_with_subchannel_output(3u, v40, i, 5u, (DWORD)v47, v45);
              v15 = (char *)dword_504C84 + v13;
              v13 += 80;
              qmemcpy(v15, v45, 0x50u);
            }
            ++v40;
          }
          while ( v40 < 0x3Cu );
          sprintf(Buffer, "%s%s.M3S", "patches\\", ppf_default_filename);
          v16 = fopen(Buffer, "wb");
          v17 = v16;
          if ( v16 )
          {
            fwrite(dword_504C84, 1u, 0x11940u, v16);
            fclose(v17);
          }
          dword_504C8C = 10;
          goto LABEL_36;
        }
LABEL_101:
        result = dbg_print(" YES.\n");
        BYTE1(byte_455945) = 0;
        return result;
      }
      memset(v47, 0xAAu, 0x1F9Cu);
      W2k_read_sector_mode2(0, 2u, 0x10u, 2u, (DWORD)v47);
      if ( !LOBYTE(v47[6]) && *(_WORD *)((char *)&v47[6] + 1) == 5634 )
      {
        if ( !(HIBYTE(v47[1179]) % 10 + 16 * (HIBYTE(v47[1179]) / 10))
          && LOBYTE(v47[1180]) % 10 + 16 * (LOBYTE(v47[1180]) / 10) == 2
          && HIBYTE(v47[1180]) % 10 + 16 * (HIBYTE(v47[1180]) / 10) == 22
          && !LOBYTE(v47[1190])
          && *(_WORD *)((char *)&v47[1190] + 1) == 5890
          && !(HIBYTE(v47[2363]) % 10 + 16 * (HIBYTE(v47[2363]) / 10))
          && LOBYTE(v47[2364]) % 10 + 16 * (LOBYTE(v47[2364]) / 10) == 2
          && HIBYTE(v47[2364]) % 10 + 16 * (HIBYTE(v47[2364]) / 10) == 23 )
        {
          dword_504C8C = 2;
          dword_504C88 = 2368;
          if ( !SubchannelW2kCaching )
            goto LABEL_101;
          dword_504C84 = malloc(0x11940u);
          dbg_print(" YES.\n");
          dbg_print(" * Cdrom precaching subchannel ... ");
          v41 = 0;
          v18 = 0;
          do
          {
            v19 = 0;
            v44 = 0;
            do
            {
              W2k_read_sector_mode2(3u, v41, v19, 5u, (DWORD)v47);
              v20 = v18;
              v21 = &v47[1176];
              v22 = 5;
              do
              {
                v23 = (char *)dword_504C84 + v20;
                *v23 = *v21;
                v23[1] = v21[1];
                v23[2] = v21[2];
                v23[3] = v21[3];
                v24 = *((unsigned __int8 *)dword_504C84 + v20 + 3);
                v20 += 16;
                v21 += 592;
                *((char *)dword_504C84 + v20 - 13) = v24 % 10 + 16 * (v24 / 10);
                *((char *)dword_504C84 + v20 - 12) = (unsigned __int8)*((char *)dword_504C84 + v20 - 12) % 10
                                                   + 16 * ((unsigned __int8)*((char *)dword_504C84 + v20 - 12) / 10);
                *((char *)dword_504C84 + v20 - 11) = (unsigned __int8)*((char *)dword_504C84 + v20 - 11) % 10
                                                   + 16 * ((unsigned __int8)*((char *)dword_504C84 + v20 - 11) / 10);
                *((char *)dword_504C84 + v20 - 9) = (unsigned __int8)*((char *)dword_504C84 + v20 - 9) % 10
                                                  + 16 * ((unsigned __int8)*((char *)dword_504C84 + v20 - 9) / 10);
                *((char *)dword_504C84 + v20 - 8) = (unsigned __int8)*((char *)dword_504C84 + v20 - 8) % 10
                                                  + 16 * ((unsigned __int8)*((char *)dword_504C84 + v20 - 8) / 10);
                --v22;
                *((char *)dword_504C84 + v20 - 7) = (unsigned __int8)*((char *)dword_504C84 + v20 - 7) % 10
                                                  + 16 * ((unsigned __int8)*((char *)dword_504C84 + v20 - 7) / 10);
              }
              while ( v22 );
              v19 = v44 + 5;
              v25 = (unsigned __int8)(v44 + 5) < 0x4Bu;
              v44 += 5;
              v18 = v20;
            }
            while ( v25 );
            ++v41;
          }
          while ( v41 < 0x3Cu );
          sprintf(Buffer, "%s%s.M3S", "patches\\", ppf_default_filename);
          v26 = fopen(Buffer, "wb");
          if ( !v26 )
            goto LABEL_88;
          fwrite(dword_504C84, 1u, 0x11940u, v26);
          goto LABEL_87;
        }
        if ( !HIBYTE(v47[1179])
          && v47[1180] == 5634
          && !LOBYTE(v47[1190])
          && HIBYTE(v47[1190]) == LOBYTE(v47[1180])
          && LOBYTE(v47[1191]) == 23
          && !HIBYTE(v47[2363])
          && LOBYTE(v47[2364]) == LOBYTE(v47[1180])
          && HIBYTE(v47[2364]) == 23 )
        {
          dword_504C8C = 3;
          dword_504C88 = 2368;
          if ( !SubchannelW2kCaching )
            goto LABEL_101;
          dword_504C84 = malloc(0x11940u);
          dbg_print(" YES.\n");
          dbg_print(" * Cdrom precaching subchannel ... ");
          v42 = 0;
          v27 = 0;
          do
          {
            for ( j = 0; j < 0x4Bu; j += 5 )
            {
              W2k_read_sector_mode2(3u, v42, j, 5u, (DWORD)v47);
              v29 = v27;
              v30 = &v47[1176];
              v31 = 5;
              do
              {
                v32 = (char *)dword_504C84 + v29;
                *v32 = *v30;
                v32[1] = v30[1];
                v32[2] = v30[2];
                v33 = v30[3];
                v29 += 16;
                v30 += 592;
                --v31;
                v32[3] = v33;
              }
              while ( v31 );
              v27 = v29;
            }
            ++v42;
          }
          while ( v42 < 0x3Cu );
          sprintf(Buffer, "%s%s.M3S", "patches\\", ppf_default_filename);
          v34 = fopen(Buffer, "wb");
          v26 = v34;
          if ( !v34 )
            goto LABEL_88;
          fwrite(dword_504C84, 1u, 0x11940u, v34);
LABEL_87:
          fclose(v26);
LABEL_88:
          dword_504C88 = 2352;
          goto LABEL_100;
        }
      }
      memset(v47, 0xAAu, 0x1F9Cu);
      W2k_read_sector_mode3(0, 2u, 0x10u, 2u, (DWORD)v47);
      if ( *(_WORD *)((char *)&v47[3] + 1) != 512
        || HIBYTE(v47[4]) != 22
        || *(_WORD *)((char *)&v47[11] + 1) != 512
        || HIBYTE(v47[12]) != 23 )
      {
        return dbg_print(" NO.\n");
      }
      dword_504C8C = 4;
      dword_504C88 = 2352;
      dword_504C84 = malloc(0x11940u);
      if ( !SubchannelW2kCaching )
        goto LABEL_101;
      dword_504C84 = malloc(0x11940u);
      dbg_print(" YES.\n");
      dbg_print(" * Cdrom precaching subchannel ... ");
      v43 = 0;
      v35 = 0;
      do
      {
        for ( k = 0; k < 0x4Bu; k += 15 )
        {
          W2k_read_sector_mode3(3u, v43, k, 0xFu, (DWORD)v47);
          v37 = (char *)dword_504C84 + v35;
          v35 += 240;
          qmemcpy(v37, v47, 0xF0u);
        }
        ++v43;
      }
      while ( v43 < 0x3Cu );
      sprintf(Buffer, "%s%s.M3S", "patches\\", ppf_default_filename);
      v38 = fopen(Buffer, "wb");
      if ( v38 )
      {
        fwrite(dword_504C84, 1u, 0x11940u, v38);
        fclose(v38);
      }
LABEL_100:
      dword_504C8C = 6;
LABEL_36:
      result = dbg_print("ok\n");
      BYTE1(byte_455945) = 0;
    }
  }
  return result;
}

int __cdecl W2k_cdrom_read_data(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3, char *Buffer)
{
  unsigned __int8 v4; // dl
  unsigned __int8 v6; // bl
  int v7; // edi
  int v9; // eax
  char *v10; // ebp
  unsigned int v11; // eax
  int *v12; // eax
  int *v13; // edx
  int v14; // ecx
  int v15; // esi
  __int64 v16; // rax
  __int64 v17; // rax
  __int64 v18; // rax
  __int64 v19; // rax
  int *v20; // edx
  int v21; // ecx
  int v22; // eax
  int v23; // ecx
  int *v24; // eax
  int v25; // ecx
  int v26; // edx
  int v27; // eax
  int v28; // edx
  int *v29; // ecx
  int *v30; // ecx
  char *v31; // eax
  int *v32; // eax
  int *v33; // ecx
  char *v34; // eax
  int v35; // eax
  int v36; // [esp+18h] [ebp-4h]
  int v37; // [esp+18h] [ebp-4h]
  unsigned int v38; // [esp+28h] [ebp+Ch]

  v4 = a1;
  v6 = a2;
  v7 = a3;
  v38 = 75 * (a2 + 60 * a1) + a3 - 150;
  if ( cd_savefake_flag )
  {
    if ( loaded_file_type == 3 )
    {
      iso_read_data(a1, a2, v7, (int)Buffer);
      if ( ppf_enabled )
      {
        v9 = sub_42C6D0(a1, a2, v7);
        ppf_apply_patch_to_sector(v9, (int)Buffer);
      }
      if ( cd_savefake_flag == 1 )
        cdrom_fake_write_portion(a1, a2, v7, Buffer);
    }
    else
    {
      if ( v38 < dword_4FFF80 || v38 >= dword_4FFF80 + 8 )
      {
        if ( dword_4FD9DC )
        {
          W2k_resume_cdrom();
          v4 = a1;
          dword_4FD9DC = 0;
        }
        switch ( dword_504C8C )
        {
          case 1:
            if ( W2k_read_sector_mode1(v4, a2, a3, 8u, (DWORD)byte_4FFF84) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
            v28 = 0;
            dword_5053E0 = 0;
            dword_5053E4 = 0;
            dword_5053E8 = 0;
            goto LABEL_65;
          case 2:
            if ( W2k_read_sector_mode2(v4, a2, a3, 8u, (DWORD)byte_4FFF84) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
            dword_5053EC = dword_5008C0[0];
            dword_5053E0 = *(_DWORD *)byte_5008B4;
            dword_5053E4 = dword_5008B8;
            dword_5053E8 = dword_5008BC;
            HIBYTE(dword_5053E0) = (unsigned __int8)byte_5008B7 % 10 + 16 * ((unsigned __int8)byte_5008B7 / 10);
            LOBYTE(dword_5053E4) = (unsigned __int8)dword_5008B8 % 10 + 16 * ((unsigned __int8)dword_5008B8 / 10);
            BYTE1(dword_5053E4) = BYTE1(dword_5008B8) % 10 + 16 * (BYTE1(dword_5008B8) / 10);
            HIBYTE(dword_5053E4) = HIBYTE(dword_5008B8) % 10 + 16 * (HIBYTE(dword_5008B8) / 10);
            LOBYTE(dword_5053E8) = (unsigned __int8)dword_5008BC % 10 + 16 * ((unsigned __int8)dword_5008BC / 10);
            BYTE1(dword_5053E8) = BYTE1(dword_5008BC) % 10 + 16 * (BYTE1(dword_5008BC) / 10);
            goto LABEL_66;
          case 3:
            if ( W2k_read_sector_mode2(v4, a2, a3, 8u, (DWORD)byte_4FFF84) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
            dword_5053E0 = *(_DWORD *)byte_5008B4;
            dword_5053E4 = dword_5008B8;
            dword_5053E8 = dword_5008BC;
            dword_5053EC = dword_5008C0[0];
            goto LABEL_66;
          case 4:
            if ( W2k_read_sector_mode1(v4, a2, a3, 8u, (DWORD)byte_4FFF84) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
            memset(dword_504C04, 0, 0x80u);
            if ( a1 == 3
              && (dword_50C280[0] & 0x1F000000) == 0x1F000000
              && W2k_read_sector_mode3(3u, a2, a3, 8u, (DWORD)dword_504C04) )
            {
              dbg_print(" * Error sub reading CD: %d,%d,%d\n", 3, a2, v7);
            }
            goto LABEL_64;
          case 5:
            fseek(Stream, 96 * v38, 0);
            fread(byte_4FFF84, 1u, 0x300u, Stream);
            v30 = dword_504C04;
            v31 = byte_4FFF90;
            v36 = 8;
            do
            {
              *v30 = *(_DWORD *)v31;
              v30[1] = *((_DWORD *)v31 + 1);
              v30[2] = *((_DWORD *)v31 + 2);
              v30[3] = *((_DWORD *)v31 + 3);
              v31 += 96;
              v30 += 4;
              --v36;
            }
            while ( v36 );
            v6 = a2;
            if ( !W2k_read_sector_mode1(a1, a2, a3, 8u, (DWORD)byte_4FFF84) )
              goto LABEL_56;
            dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
            dword_5053E0 = dword_504C04[0];
            dword_5053E4 = dword_504C08;
            dword_5053E8 = dword_504C0C;
            dword_5053EC = dword_504C10[0];
            goto LABEL_66;
          case 6:
            if ( W2k_read_sector_mode1(v4, a2, a3, 8u, (DWORD)byte_4FFF84) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
            if ( a1 != 3 )
              goto LABEL_46;
            v29 = (int *)((char *)dword_504C84 + 1200 * a2 + 16 * v7);
            dword_5053E0 = *v29;
            dword_5053E4 = v29[1];
            dword_5053E8 = v29[2];
            dword_5053EC = v29[3];
            goto LABEL_66;
          case 7:
            if ( W2k_read_raw_sector(v4, a2, a3, 8u, (DWORD)byte_4FFF84) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
LABEL_46:
            dword_5053E0 = 0;
            dword_5053E4 = 0;
            dword_5053E8 = 0;
            dword_5053EC = 0;
            goto LABEL_66;
          case 8:
            memset(dword_504C04, 0, 0x80u);
            if ( v4 == 3 && (dword_50C280[0] & 0x1F000000) == 0x1F000000 )
            {
              if ( W2k_read_sector_with_subchannel_output(3u, a2, a3, 8u, (DWORD)byte_4FFF84, dword_504C04) )
                dbg_print(" * Error sub reading CD: %d,%d,%d\n", 3, a2, v7);
              v4 = a1;
            }
            if ( W2k_read_raw_sector(v4, a2, a3, 8u, (DWORD)byte_4FFF84) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
LABEL_64:
            dword_5053E0 = dword_504C04[0];
            v28 = dword_504C10[0];
            dword_5053E4 = dword_504C08;
            dword_5053E8 = dword_504C0C;
            goto LABEL_65;
          case 9:
            fseek(Stream, 96 * v38, 0);
            fread(byte_4FFF84, 1u, 0x300u, Stream);
            v33 = dword_504C04;
            v34 = byte_4FFF90;
            v37 = 8;
            do
            {
              *v33 = *(_DWORD *)v34;
              v33[1] = *((_DWORD *)v34 + 1);
              v33[2] = *((_DWORD *)v34 + 2);
              v33[3] = *((_DWORD *)v34 + 3);
              v34 += 96;
              v33 += 4;
              --v37;
            }
            while ( v37 );
            v6 = a2;
            if ( W2k_read_raw_sector(a1, a2, a3, 8u, (DWORD)byte_4FFF84) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
LABEL_56:
            dword_5053E0 = dword_504C04[0];
            dword_5053E4 = dword_504C08;
            dword_5053E8 = dword_504C0C;
            dword_5053EC = dword_504C10[0];
            goto LABEL_66;
          case 10:
            if ( W2k_read_raw_sector(v4, a2, a3, 8u, (DWORD)byte_4FFF84) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
            if ( a1 == 3 )
            {
              v32 = (int *)((char *)dword_504C84 + 1200 * a2 + 16 * v7);
              dword_5053E0 = *v32;
              dword_5053E4 = v32[1];
              dword_5053E8 = v32[2];
              v28 = v32[3];
LABEL_65:
              dword_5053EC = v28;
            }
            else
            {
              dword_5053E0 = 0;
              dword_5053E4 = 0;
              dword_5053E8 = 0;
              dword_5053EC = 0;
            }
LABEL_66:
            v10 = Buffer;
            dword_4FFF80 = v38;
            qmemcpy(Buffer, byte_4FFF84, 0x930u);
            break;
          default:
            goto LABEL_66;
        }
      }
      else
      {
        v10 = Buffer;
        v11 = v38 - dword_4FFF80;
        qmemcpy(Buffer, &byte_4FFF84[(v38 - dword_4FFF80) * dword_504C88], 0x930u);
        switch ( dword_504C8C )
        {
          case 1:
          case 7:
            dword_5053E0 = 0;
            dword_5053E4 = 0;
            dword_5053E8 = 0;
            dword_5053EC = 0;
            break;
          case 2:
            v13 = (int *)&byte_5008B4[v11 * dword_504C88];
            v14 = v13[1];
            v15 = v13[2];
            dword_5053E0 = *v13;
            dword_5053EC = v13[3];
            dword_5053E4 = v14;
            dword_5053E8 = v15;
            HIBYTE(dword_5053E0) = HIBYTE(dword_5053E0) % 10 + 16 * (HIBYTE(dword_5053E0) / 10);
            LOBYTE(dword_5053E4) = (unsigned __int8)v14 % 10 + 16 * ((unsigned __int8)v14 / 10);
            v16 = (unsigned __int8)(16 * (BYTE1(v14) / 10));
            BYTE1(dword_5053E4) = BYTE4(v16) + v16;
            v17 = (unsigned __int8)(16 * (HIBYTE(v14) / 10));
            HIBYTE(dword_5053E4) = BYTE4(v17) + v17;
            v18 = (unsigned __int8)(16 * ((unsigned __int8)v15 / 10));
            LOBYTE(dword_5053E8) = BYTE4(v18) + v18;
            v19 = (unsigned __int8)(16 * (BYTE1(v15) / 10));
            BYTE1(dword_5053E8) = BYTE4(v19) + v19;
            break;
          case 3:
            v20 = (int *)&byte_5008B4[v11 * dword_504C88];
            v21 = v20[1];
            dword_5053E0 = *v20;
            v22 = v20[2];
            dword_5053E4 = v21;
            v23 = v20[3];
            dword_5053E8 = v22;
            dword_5053EC = v23;
            break;
          case 4:
          case 5:
          case 8:
          case 9:
            v24 = &dword_504C04[4 * v11];
            v25 = v24[1];
            dword_5053E0 = *v24;
            v26 = v24[2];
            v27 = v24[3];
            dword_5053E4 = v25;
            dword_5053E8 = v26;
            dword_5053EC = v27;
            break;
          case 6:
          case 10:
            if ( a1 == 3 )
            {
              v12 = (int *)((char *)dword_504C84 + 1200 * a2 + 16 * v7);
              dword_5053E0 = *v12;
              dword_5053E4 = v12[1];
              dword_5053E8 = v12[2];
              dword_5053EC = v12[3];
            }
            else
            {
              dword_5053E0 = 0;
              dword_5053E4 = 0;
              dword_5053E8 = 0;
              dword_5053EC = 0;
            }
            break;
          default:
            break;
        }
      }
      if ( ppf_enabled )
      {
        v35 = sub_42C6D0(a1, v6, v7);
        ppf_apply_patch_to_sector(v35, (int)v10);
      }
      if ( cd_savefake_flag == 1 )
        cdrom_fake_write_portion(a1, v6, v7, v10);
    }
    return 0;
  }
  else
  {
    cdrom_fake_read_portion(a1, a2, v7, Buffer);
    return 0;
  }
}