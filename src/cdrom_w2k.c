#include "pch.h"

/* static prototypes for internal functions */
static int W2k_send_read_subchannel_command();
static bool W2k_read_raw_sector(
        uint8_t a1,
        uint8_t a2,
        uint8_t a3,
        uint8_t a4,
        DWORD a5);
static bool W2k_read_sector_mode1(
        uint8_t a1,
        uint8_t a2,
        uint8_t a3,
        uint8_t a4,
        DWORD a5);

static char W2k_find_cdrom_drive_letter()
{
  int v0;
  CHAR RootPathName[4];

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

static HANDLE W2k_open_cdrom_device(uint8_t a1)
{
  DWORD v1;
  HANDLE result;
  CHAR FileName[12];
  struct _OSVERSIONINFOA VersionInformation;

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

static int W2k_get_scsi_address(uint8_t a1, uint32_t *a2, uint32_t *a3, uint32_t *a4)
{
  HANDLE v4;
  uint8_t v6;
  uint8_t v7;
  DWORD BytesReturned;
  uint32_t OutBuffer[256];

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

static int W2k_scsi_pass_through_direct(DWORD BytesReturned)
{
  DWORD v1;
  int v2;
  int v3;
  uint32_t InBuffer[20];

  v1 = BytesReturned;
  v2 = *(uint32_t *)(BytesReturned + 16);
  memset(InBuffer, 0, sizeof(InBuffer));
  v3 = *(uint32_t *)(BytesReturned + 12);
  BYTE2(InBuffer[1]) = *(uint8_t *)(BytesReturned + 21);
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
    *(uint8_t *)(v1 + 1) = 1;
  }
  else
  {
    *(uint8_t *)(v1 + 1) = 4;
    *(uint8_t *)(v1 + 23) = 4;
    GetLastError();
  }
  return *(uint8_t *)(v1 + 1);
}

static char W2k_cdrom_gettrackinfo()
{
  HANDLE EventA;
  char result;
  uint8_t v2;
  int v3;
  char v4;
  char v5;
  uint8_t v6;
  unsigned int v7;
  int v8;
  int v9;
  DWORD BytesReturned[20];

  v5 = 10;
  v4 = 0;
  do
  {
    if ( v4 )
      break;
    memset(BytesReturned, 0, sizeof(BytesReturned));
    memset(&w2k_toc_buffer, 0, 0x324u);
    EventA = CreateEventA(nullptr, 1, 0, nullptr);
    LOBYTE(BytesReturned[0]) = 2;
    BYTE2(BytesReturned[0]) = scsi_port;
    LOBYTE(BytesReturned[2]) = scsi_target;
    BYTE1(BytesReturned[2]) = scsi_lun;
    HIBYTE(BytesReturned[0]) = 72;
    BytesReturned[3] = 804;
    BytesReturned[4] = (DWORD)&w2k_toc_buffer;
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
  dbg_print(" * First/Last track: %d %d\n", (uint8_t)w2k_toc_first_track, (uint8_t)w2k_toc_last_track);
  result = w2k_toc_last_track - w2k_toc_first_track + 1;
  v2 = 0;
  v6 = result;
  track_count = result;
  LOBYTE(v8) = 0;
  if ( w2k_toc_last_track - w2k_toc_first_track != 0xFF )
  {
    do
    {
      v3 = (uint8_t)v8;
      dbg_print(" * Track %d: ", (uint8_t)w2k_toc_track_entries[8 * (uint8_t)v8]);
      if ( (w2k_toc_track_control[8 * v3] & 4) != 0 )
      {
        dbg_print("(DATA)  -");
      }
      else
      {
        dbg_print("(AUDIO) -");
        if ( !v2 )
          nocd = 2;
      }
      W9x_bcd_to_dword(&v7, (uint8_t *)(8 * v3 + 5241928));
      v7 += 150;
      dbg_print(" Start %d: (%02d,%02d,%02d) - ", v3, (uint8_t)(v7 / 0x4B / 0x3C), v7 / 0x4B % 0x3C, v7 % 0x4B);
      W9x_bcd_to_dword(&v7, (uint8_t *)(8 * v3 + 5241928));
      W9x_bcd_to_dword(&v9, (uint8_t *)(8 * v3 + 5241936));
      dbg_print(" Length %02d:%02d\n", (v9 - v7) / 0x4B / 0x3C, (v9 - v7) / 0x4B % 0x3C);
      result = v6;
      LOBYTE(v8) = ++v2;
    }
    while ( v2 < v6 );
  }
  return result;
}

static BOOL W2k_resume_cdrom()
{
  HANDLE EventA;
  DWORD BytesReturned[20];

  BYTE1(w2k_resume_cdb) = (32 * scsi_lun) | 1;
  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(BytesReturned, 0, sizeof(BytesReturned));
  BYTE2(BytesReturned[0]) = scsi_port;
  LOBYTE(BytesReturned[2]) = scsi_target;
  BYTE1(BytesReturned[2]) = scsi_lun;
  LOBYTE(BytesReturned[0]) = 2;
  HIBYTE(BytesReturned[0]) = 80;
  LOWORD(BytesReturned[5]) = 2574;
  BytesReturned[3] = 0;
  BytesReturned[4] = 0;
  BytesReturned[6] = (DWORD)EventA;
  BytesReturned[12] = w2k_resume_cdb;
  BytesReturned[13] = w2k_resume_cdb2;
  LOWORD(BytesReturned[14]) = w2k_resume_cdb3;
  ResetEvent(EventA);
  if ( !W2k_scsi_pass_through_direct((DWORD)BytesReturned) )
    WaitForSingleObject(EventA, 0xFFFFFFFF);
  if ( BYTE1(BytesReturned[0]) != 1 )
    printf(" * Resume cdrom error. \n");
  return CloseHandle(EventA);
}

char W2k_cdrom_init()
{
  char result;
  void *v1;
  uint8_t v2[8092];

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
    W2k_get_scsi_address(cdrom_letter, &scsi_port, &scsi_target, &scsi_lun);
    hObject = W2k_open_cdrom_device(cdrom_letter);
    if ( !hObject )
      sound_use_cdda = 0;
    W2k_cdrom_gettrackinfo();
    dbg_print("[%c] ok\n", cdrom_letter);
    v1 = alloca(8092);
    memset(v2, 0xAAu, sizeof(v2));
    cd_read_mode = 0;
    cached_sector_lba = -1;
    W2k_read_sector_mode1(0, 2u, 0x10u, 2u, (DWORD)v2);
    result = v2[12];
    if ( !v2[12] && v2[13] == 2 && v2[14] == 22 && (result = v2[2364]) == 0 && v2[2365] == 2 && v2[2366] == 23 )
    {
      cd_read_mode = 1;
      sector_stride = 2352;
    }
    else if ( cd_read_mode != 1 )
    {
      memset(v2, 0xAAu, sizeof(v2));
      W2k_read_raw_sector(0, 2u, 0x10u, 2u, (DWORD)v2);
      result = v2[12];
      if ( !v2[12] && v2[13] == 2 && v2[14] == 22 )
      {
        result = v2[2364];
        if ( !v2[2364] && v2[2365] == 2 && v2[2366] == 23 )
        {
          cd_read_mode = 7;
          sector_stride = 2352;
        }
      }
    }
  }
  return result;
}

char W2k_get_first_last_track(uint8_t *a1, uint8_t *a2)
{
  char result;

  *a1 = w2k_toc_first_track;
  result = track_count;
  *a2 = track_count;
  return result;
}

unsigned int W2k_track_to_msf(int a1, uint8_t *a2, uint8_t *a3, uint8_t *a4)
{
  unsigned int result;
  unsigned int v5;
  unsigned int v6;

  result = (uint8_t)track_count;
  if ( (int16_t)a1 <= (int)(uint8_t)track_count )
  {
    if ( (uint16_t)a1 )
      W9x_bcd_to_dword(&a1, (uint8_t *)(8 * (int16_t)a1 + 5241920));
    else
      W9x_bcd_to_dword(&a1, (uint8_t *)(8 * (uint8_t)track_count + 5241928));
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
  HANDLE result;

  if ( cd_savefake_flag >= 0 )
    cdrom_fake_write();
  if ( loaded_file_type == 3 )
    iso_close();
  if ( m3s_q_cache )
    free(m3s_q_cache);
  if ( subchannel_mode_enabled && hObject )
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

static char W2k_find_track_by_min_sec(unsigned int a1, char a2)
{
  char v2;
  uint8_t v4;

  v4 = 0;
  if ( !track_count )
    return 0;
  v2 = a1;
  while ( 1 )
  {
    W9x_bcd_to_dword(&a1, (uint8_t *)(8 * v4 + 5241928));
    a1 += 150;
    if ( (uint8_t)(a1 / 0x4B / 0x3C) == v2 && a1 / 0x4B % 0x3C == a2 )
      break;
    if ( ++v4 >= (uint8_t)track_count )
      return 0;
  }
  return a1 % 0x4B;
}

char W2k_cdrom_play_cdda(unsigned int a1, int a2, uint8_t a3)
{
  char result;
  uint8_t v4;
  HANDLE EventA;
  DWORD BytesReturned[20];

  result = sound_use_cdda;
  if ( sound_use_cdda )
  {
    v4 = a2;
    a3 = W2k_find_track_by_min_sec(a1, a2);
    BYTE1(w2k_play_cdb2) = a3;
    HIBYTE(w2k_play_cdb) = a1;
    LOBYTE(w2k_play_cdb2) = v4;
    W9x_bcd_to_dword(&a2, (uint8_t *)(8 * (uint8_t)track_count + 5241928));
    LOBYTE(w2k_play_cdb3) = (a2 + 150) % 0x4Bu;
    BYTE2(w2k_play_cdb2) = (a2 + 150) / 0x4Bu / 0x3C;
    HIBYTE(w2k_play_cdb2) = (a2 + 150) / 0x4Bu % 0x3C;
    EventA = CreateEventA(nullptr, 1, 0, nullptr);
    memset(BytesReturned, 0, sizeof(BytesReturned));
    BYTE2(BytesReturned[0]) = scsi_port;
    LOBYTE(BytesReturned[2]) = scsi_target;
    BYTE1(BytesReturned[2]) = scsi_lun;
    LOBYTE(BytesReturned[0]) = 2;
    HIBYTE(BytesReturned[0]) = 72;
    LOWORD(BytesReturned[5]) = 2574;
    BytesReturned[3] = 0;
    BytesReturned[4] = 0;
    BytesReturned[6] = (DWORD)EventA;
    BytesReturned[12] = w2k_play_cdb;
    BytesReturned[13] = w2k_play_cdb2;
    LOWORD(BytesReturned[14]) = w2k_play_cdb3;
    ResetEvent(EventA);
    if ( !W2k_scsi_pass_through_direct((DWORD)BytesReturned) )
      WaitForSingleObject(EventA, 0xFFFFFFFF);
    result = CloseHandle(EventA);
    if ( BYTE1(BytesReturned[0]) == 1 )
      w2k_cdda_playing = 1;
    else
      return printf(" * W2k play cdda error (%d, %d, %d) \n", (uint8_t)a1, v4, a3);
  }
  return result;
}

char W2k_cdrom_stop()
{
  char result;
  HANDLE EventA;
  DWORD BytesReturned[20];

  BYTE1(w2k_stop_cdb) = (32 * scsi_lun) | 1;
  result = sound_use_cdda;
  if ( sound_use_cdda )
  {
    result = w2k_cdda_playing;
    if ( w2k_cdda_playing )
    {
      w2k_cdda_playing = 0;
      EventA = CreateEventA(nullptr, 1, 0, nullptr);
      memset(BytesReturned, 0, sizeof(BytesReturned));
      BYTE2(BytesReturned[0]) = scsi_port;
      LOBYTE(BytesReturned[2]) = scsi_target;
      BYTE1(BytesReturned[2]) = scsi_lun;
      LOBYTE(BytesReturned[0]) = 2;
      HIBYTE(BytesReturned[0]) = 80;
      LOWORD(BytesReturned[5]) = 2574;
      BytesReturned[3] = 0;
      BytesReturned[4] = 0;
      BytesReturned[6] = (DWORD)EventA;
      BytesReturned[12] = w2k_stop_cdb;
      BytesReturned[13] = w2k_stop_cdb2;
      LOWORD(BytesReturned[14]) = w2k_stop_cdb3;
      ResetEvent(EventA);
      if ( !W2k_scsi_pass_through_direct((DWORD)BytesReturned) )
        WaitForSingleObject(EventA, 0xFFFFFFFF);
      if ( BYTE1(BytesReturned[0]) != 1 )
        printf(" * W2k stop cdrom error. \n");
      result = CloseHandle(EventA);
      w2k_cdda_resume_pending = 1;
    }
  }
  return result;
}

void W2k_reset_cdda_state()
{
  w2k_cdda_playing = 0;
  w2k_cdda_pause_pos = -1;
  cdr_spinup_motor();
}

static char W2k_msf_to_lba(
        unsigned int a1,
        uint8_t a2,
        uint8_t a3,
        uint8_t *a4,
        uint8_t *a5,
        uint8_t *a6,
        uint8_t *a7)
{
  uint8_t v7;
  unsigned int v8;
  char result;
  unsigned int v10;
  uint8_t v11;

  v7 = 0;
  v11 = 0;
  v8 = (a3 & 0xF) % 10
     + 75
     * ((a2 & 0xF) % 10 + 10 * ((a2 >> 4) + 6 * ((uint8_t)(a1 & 0xF) % 10 + 10 * ((uint8_t)a1 >> 4))))
     + 10 * (a3 >> 4)
     - 150;
  W9x_bcd_to_dword(&a1, (uint8_t *)(8 * (uint8_t)track_count + 5241928));
  if ( a1 > v8 && track_count )
  {
    while ( 1 )
    {
      W9x_bcd_to_dword(&a1, (uint8_t *)(8 * v11 + 5241936));
      if ( v11 + 1 < (uint8_t)track_count )
        a1 -= a1 % 0x4B;
      if ( a1 > v8 )
        break;
      v11 = ++v7;
      if ( v7 >= (uint8_t)track_count )
        goto LABEL_7;
    }
    W9x_bcd_to_dword(&a1, (uint8_t *)(8 * v11 + 5241928));
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

char W2k_lba_to_msf(
        unsigned int a1,
        uint8_t a2,
        uint8_t a3,
        uint8_t *a4,
        uint8_t *a5,
        uint8_t *a6)
{
  char v6;
  unsigned int v7;
  uint8_t *v8;
  uint8_t v9;
  uint8_t *v10;
  unsigned int v11;
  unsigned int v12;
  uint8_t v14;

  v6 = a1;
  v14 = 0;
  v7 = (a3 & 0xF) % 10
     + 75
     * ((a2 & 0xF) % 10 + 10 * ((a2 >> 4) + 6 * ((uint8_t)(a1 & 0xF) % 10 + 10 * ((uint8_t)a1 >> 4))))
     + 10 * (a3 >> 4);
  W9x_bcd_to_dword(&a1, (uint8_t *)(8 * (uint8_t)track_count + 5241928));
  if ( a1 > v7 )
  {
    LOBYTE(v10) = track_count;
    if ( track_count )
    {
      while ( 1 )
      {
        W9x_bcd_to_dword(&a1, (uint8_t *)(8 * v14 + 5241936));
        if ( a1 > v7 )
          break;
        LOBYTE(v10) = ++v14;
        if ( v14 >= (uint8_t)track_count )
          return (char)v10;
      }
      v11 = a1 % 0x4B;
      v12 = a1 / 0x4B % 0x3C;
      *a4 = a1 / 0x4B / 0x3C;
      LOBYTE(v10) = (uint8_t)a5;
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

uint8_t W2k_check_subchannel_data(unsigned int a1, uint8_t a2, uint8_t a3, int a4)
{
  char v4;
  char v5;
  uint8_t result;
  char v7;
  uint8_t v8;
  uint8_t v9;
  uint8_t v10;
  uint8_t v11;
  uint8_t v12;

  *(uint32_t *)a4 = 0;
  *(uint32_t *)(a4 + 4) = 0;
  v7 = 0;
  if ( (uint8_t)sub_q_cur0 )
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
    v4 = (uint8_t)a1 % 10 + 16 * ((uint8_t)a1 / 10);
    v8 = a2 % 10 + 16 * (a2 / 10);
    v11 = v10 % 10 + 16 * (v10 / 10);
    *(uint32_t *)a4 = *(int *)((char *)&sub_q_cur0 + 1);
    *(uint8_t *)(a4 + 4) = BYTE1(sub_q_cur1);
    *(uint16_t *)(a4 + 5) = *(uint16_t *)((char *)&sub_q_cur1 + 3);
    *(uint8_t *)(a4 + 7) = BYTE1(sub_q_cur2);
    if ( v4 != *(uint8_t *)(a4 + 5) )
      v7 = 1;
    if ( v4 != *(uint8_t *)(a4 + 2) )
      ++v7;
    if ( v8 != *(uint8_t *)(a4 + 6) )
      ++v7;
    v5 = v7;
    if ( ((v8 & 0xF) % 10 + 10 * (v8 >> 4) - 2) % 10 + 16 * (((v8 & 0xF) % 10 + 10 * (v8 >> 4) - 2) / 10) != *(uint8_t *)(a4 + 3) )
      v5 = v7 + 1;
    result = v11;
    if ( v11 != *(uint8_t *)(a4 + 7) )
      ++v5;
    if ( v11 != *(uint8_t *)(a4 + 4) )
      ++v5;
    if ( (uint8_t)v5 >= 2u )
    {
      result = 0;
      *(uint32_t *)(a4 + 2) = 0;
      *(uint16_t *)(a4 + 6) = 0;
      if ( v4 == 3 )
        xenogears_cd_detected = 1;
    }
  }
  else
  {
    LOBYTE(a1) = (uint8_t)a1 % 10 + 16 * ((uint8_t)a1 / 10);
    v9 = a2 % 10 + 16 * (a2 / 10);
    v12 = a3 % 10 + 16 * (a3 / 10);
    W2k_msf_to_lba(a1, v9, v12, (uint8_t *)a4, (uint8_t *)(a4 + 2), (uint8_t *)(a4 + 3), (uint8_t *)(a4 + 4));
    *(uint8_t *)(a4 + 1) = 1;
    *(uint8_t *)(a4 + 5) = a1;
    *(uint8_t *)(a4 + 6) = v9;
    *(uint8_t *)(a4 + 7) = v12;
    return v12;
  }
  return result;
}

static bool W2k_send_scsi_command(const void *a1, unsigned int a2, DWORD a3, DWORD a4)
{
  HANDLE EventA;
  DWORD BytesReturned[20];

  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(BytesReturned, 0, sizeof(BytesReturned));
  LOBYTE(BytesReturned[2]) = scsi_target;
  BytesReturned[4] = a3;
  BYTE1(BytesReturned[2]) = scsi_lun;
  BYTE2(BytesReturned[0]) = scsi_port;
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

static int W2k_send_read_toc_command()
{
  HANDLE EventA;
  uint8_t v2[10];
  uint8_t v3[2];
  DWORD BytesReturned[20];

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
  BYTE2(BytesReturned[0]) = scsi_port;
  LOBYTE(BytesReturned[2]) = scsi_target;
  LOBYTE(BytesReturned[0]) = 2;
  BYTE1(BytesReturned[2]) = scsi_lun;
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

static int W2k_send_read_subchannel_command()
{
  HANDLE EventA;
  uint8_t v2[4];
  char v3[8];
  DWORD BytesReturned[20];

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
  subchannel_mode_enabled = 0;
  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(BytesReturned, 0, sizeof(BytesReturned));
  BYTE2(BytesReturned[0]) = scsi_port;
  LOBYTE(BytesReturned[2]) = scsi_target;
  LOBYTE(BytesReturned[0]) = 2;
  BYTE1(BytesReturned[2]) = scsi_lun;
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

static bool W2k_read_raw_sector(
        uint8_t a1,
        uint8_t a2,
        uint8_t a3,
        uint8_t a4,
        DWORD a5)
{
  char v6;
  int16_t v7;
  char v8;
  char v9;
  int16_t v10;
  char v11;
  int v12;

  if ( !subchannel_mode_enabled )
  {
    if ( W2k_send_read_toc_command() != 1 )
      return 1;
    subchannel_mode_enabled = 1;
  }
  v11 = 0;
  v7 = 0;
  v12 = a4;
  v8 = (75 * (a2 + 60 * a1) + (unsigned int)a3 - 150) >> 16;
  v6 = 40;
  v9 = (uint16_t)(75 * (a2 + 60 * a1) + a3 - 150) >> 8;
  v10 = (uint8_t)(75 * (a2 + 60 * a1) + a3 + 106);
  return W2k_send_scsi_command(&v6, 0xAu, a5, 2352 * a4);
}

static bool W2k_read_sector_with_subchannel_output(
        uint8_t a1,
        uint8_t a2,
        uint8_t a3,
        uint8_t a4,
        DWORD a5,
        uint32_t *a6)
{
  bool result;
  int v7;
  uint32_t *v9;
  uint32_t *v10;
  int v11;
  char v12;
  int16_t v13;
  char v14;
  char v15;
  int16_t v16;
  char v17;
  int v18;

  if ( !subchannel_mode_enabled )
  {
    if ( W2k_send_read_toc_command() != 1 )
      return 1;
    subchannel_mode_enabled = 1;
  }
  v17 = 0;
  v16 = (uint8_t)(75 * (a2 + 60 * a1) + a3 + 106);
  v18 = 0x10000;
  v13 = 0;
  v7 = a4;
  v14 = (75 * (a2 + 60 * a1) + (unsigned int)a3 - 150) >> 16;
  v12 = -40;
  v15 = (uint16_t)(75 * (a2 + 60 * a1) + a3 - 150) >> 8;
  BYTE1(v18) = a4;
  result = W2k_send_scsi_command(&v12, 0xCu, a5, 2368 * a4);
  if ( a4 )
  {
    v9 = (uint32_t *)(a5 + 2352);
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

static bool W2k_read_sector_mode1(
        uint8_t a1,
        uint8_t a2,
        uint8_t a3,
        uint8_t a4,
        DWORD a5)
{
  char v6;
  int16_t v7;
  char v8;
  char v9;
  int16_t v10;
  char v11;
  uint8_t v12;
  char v13;
  int16_t v14;

  v11 = 0;
  v14 = 0;
  v10 = (uint8_t)(75 * (a2 + 60 * a1) + a3 + 106);
  v7 = 0;
  v12 = a4;
  v8 = (75 * (a2 + 60 * a1) + (unsigned int)a3 - 150) >> 16;
  v6 = -66;
  v9 = (uint16_t)(75 * (a2 + 60 * a1) + a3 - 150) >> 8;
  v13 = -8;
  return W2k_send_scsi_command(&v6, 0xCu, a5, 2352 * a4);
}

static bool W2k_read_sector_mode2(
        uint8_t a1,
        uint8_t a2,
        uint8_t a3,
        uint8_t a4,
        DWORD a5)
{
  char v6;
  int16_t v7;
  char v8;
  char v9;
  int16_t v10;
  char v11;
  uint8_t v12;
  char v13;
  int16_t v14;

  v11 = 0;
  v10 = (uint8_t)(75 * (a2 + 60 * a1) + a3 + 106);
  v7 = 0;
  v12 = a4;
  v8 = (75 * (a2 + 60 * a1) + (unsigned int)a3 - 150) >> 16;
  v6 = -66;
  v9 = (uint16_t)(75 * (a2 + 60 * a1) + a3 - 150) >> 8;
  v13 = -8;
  v14 = 2;
  return W2k_send_scsi_command(&v6, 0xCu, a5, 2368 * a4);
}

static bool W2k_read_sector_mode3(
        uint8_t a1,
        uint8_t a2,
        uint8_t a3,
        uint8_t a4,
        DWORD a5)
{
  char v6;
  int16_t v7;
  char v8;
  char v9;
  int16_t v10;
  char v11;
  int16_t v12;
  int16_t v13;

  v11 = 0;
  v10 = (uint8_t)(75 * (a2 + 60 * a1) + a3 + 106);
  v12 = a4;
  v8 = (75 * (a2 + 60 * a1) + (unsigned int)a3 - 150) >> 16;
  v6 = -66;
  v7 = 4;
  v9 = (uint16_t)(75 * (a2 + 60 * a1) + a3 - 150) >> 8;
  v13 = 2;
  return W2k_send_scsi_command(&v6, 0xCu, a5, 16 * a4);
}

static bool W2k_send_subchannel_command(int a1)
{
  int16_t v2;
  char v3;
  char v4;
  char v5;
  char v6;
  int16_t v7;
  int16_t v8;

  v7 = 0;
  v8 = 0;
  v3 = HIBYTE(a1);
  v4 = BYTE2(a1);
  v2 = 43;
  v5 = BYTE1(a1);
  v6 = a1;
  return W2k_send_scsi_command(&v2, 0xAu, 0, 0);
}

static bool W2k_get_subchannel_status(uint32_t *a1)
{
  uint32_t v2[2];
  char v3[4];

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
  char result;
  int v1;
  FILE *v2;
  int v3;
  int v4;
  int v5;
  uint32_t *v6;
  int v7;
  int v8;
  int v9;
  uint32_t *v10;
  FILE *v11;
  FILE *v12;
  int v13;
  uint8_t i;
  char *v15;
  FILE *v16;
  FILE *v17;
  int v18;
  uint8_t v19;
  int v20;
  uint32_t *v21;
  int v22;
  uint32_t *v23;
  int v24;
  bool v25;
  FILE *v26;
  int v27;
  uint8_t j;
  int v29;
  uint32_t *v30;
  int v31;
  uint32_t *v32;
  int v33;
  FILE *v34;
  int v35;
  uint8_t k;
  char *v37;
  FILE *v38;
  int v39;
  uint8_t v40;
  uint8_t v41;
  uint8_t v42;
  uint8_t v43;
  char v44;
  uint32_t v45[256];
  char Buffer[1024];
  uint16_t v47[9472];

  result = cd_savefake_flag;
  cached_sector_lba = -1;
  if ( cd_savefake_flag && loaded_file_type != 3 )
  {
    v1 = 1;
    if ( cd_read_mode != 7 && cd_read_mode != 1 )
    {
      result = dbg_print(" * Warning: cdrom read mode unknown. \n");
      cd_read_mode = 1;
      return result;
    }
    result = use_subchannel;
    if ( use_subchannel )
    {
      sprintf(Buffer, "%s%s.SUB", "patches\\", default_filename);
      Stream = fopen(Buffer, "rb");
      if ( Stream )
      {
        if ( cd_read_mode == 1 )
        {
          cd_read_mode = 5;
          result = dbg_print(" * Subchannel support from clonecd .sub file. \n");
          BYTE1(cd_speed) = 0;
        }
        else
        {
          if ( cd_read_mode == 7 )
            cd_read_mode = 9;
          result = dbg_print(" * Subchannel support from clonecd .sub file. \n");
          BYTE1(cd_speed) = 0;
        }
        return result;
      }
      sprintf(Buffer, "%s%s.M3S", "patches\\", default_filename);
      v2 = fopen(Buffer, "rb");
      if ( v2 )
      {
        m3s_q_cache = malloc(0x11940u);
        fread(m3s_q_cache, 1u, 0x11940u, v2);
        fclose(v2);
        if ( cd_read_mode == 1 )
        {
          cd_read_mode = 6;
          result = dbg_print(" * Subchannel support from .m3s file. \n");
          BYTE1(cd_speed) = 0;
        }
        else
        {
          if ( cd_read_mode == 7 )
            cd_read_mode = 10;
          result = dbg_print(" * Subchannel support from .m3s file. \n");
          BYTE1(cd_speed) = 0;
        }
        return result;
      }
      if ( SubchannelW2kCaching )
      {
        dbg_print(" * Checking subchannel read standard ... \n");
        m3s_q_cache = malloc(0x11940u);
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
                v6 = (char *)m3s_q_cache + 1200 * BYTE2(v45[2]) + 16 * HIBYTE(v45[2]);
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
            v10 = (char *)m3s_q_cache + v7;
            v45[0] = *(uint32_t *)((char *)m3s_q_cache + v7);
            v45[1] = *(uint32_t *)((char *)m3s_q_cache + v7 + 4);
            v45[2] = *(uint32_t *)((char *)m3s_q_cache + v7 + 8);
            v45[3] = *(uint32_t *)((char *)m3s_q_cache + v7 + 12);
            *v10 = 0;
            v10[1] = 0;
            v10[2] = 0;
            v10[3] = 0;
            *((uint8_t *)m3s_q_cache + v7) = 65;
            *(uint16_t *)((char *)m3s_q_cache + v7 + 1) = HIWORD(v45[1]);
            v7 += 16;
            *((char *)m3s_q_cache + v7 - 13) = BYTE1(v45[3]) % 10 + 16 * (BYTE1(v45[3]) / 10);
            *((char *)m3s_q_cache + v7 - 12) = BYTE2(v45[3]) % 10 + 16 * (BYTE2(v45[3]) / 10);
            *((char *)m3s_q_cache + v7 - 11) = HIBYTE(v45[3]) % 10 + 16 * (HIBYTE(v45[3]) / 10);
            *((char *)m3s_q_cache + v7 - 9) = BYTE1(v45[2]) % 10 + 16 * (BYTE1(v45[2]) / 10);
            *((char *)m3s_q_cache + v7 - 8) = BYTE2(v45[2]) % 10 + 16 * (BYTE2(v45[2]) / 10);
            --v9;
            *((char *)m3s_q_cache + v7 - 7) = HIBYTE(v45[2]) % 10 + 16 * (HIBYTE(v45[2]) / 10);
          }
          while ( v9 );
          --v8;
        }
        while ( v8 );
        cd_read_mode = 6;
        sprintf(Buffer, "%s%s.M3S", "patches\\", default_filename);
        v11 = fopen(Buffer, "wb");
        v12 = v11;
        if ( v11 )
        {
          fwrite(m3s_q_cache, 1u, 0x11940u, v11);
          fclose(v12);
        }
        goto LABEL_36;
      }
      result = SubchannelW2kCdromEnabled;
      if ( !SubchannelW2kCdromEnabled )
        return result;
      dbg_print(" * Checking subchannel read from cdrom ... ");
      if ( cd_read_mode == 7 )
      {
        W2k_read_sector_with_subchannel_output(0, 2u, 0x10u, 2u, (DWORD)v47, v45);
        result = HIBYTE(v45[1]);
        if ( HIBYTE(v45[1]) )
          return result;
        result = v45[2];
        if ( LOWORD(v45[2]) != 5634 )
          return result;
        result = HIBYTE(v45[5]);
        if ( *(uint16_t *)((char *)&v45[5] + 3) != 512 || BYTE1(v45[6]) != 23 )
          return result;
        cd_read_mode = 8;
        sector_stride = 2352;
        if ( SubchannelW2kCaching )
        {
          m3s_q_cache = malloc(0x11940u);
          dbg_print(" YES.\n");
          dbg_print(" * Cdrom precaching subchannel ... ");
          v40 = 0;
          v13 = 0;
          do
          {
            for ( i = 0; i < 0x4Bu; i += 5 )
            {
              W2k_read_sector_with_subchannel_output(3u, v40, i, 5u, (DWORD)v47, v45);
              v15 = (char *)m3s_q_cache + v13;
              v13 += 80;
              qmemcpy(v15, v45, 0x50u);
            }
            ++v40;
          }
          while ( v40 < 0x3Cu );
          sprintf(Buffer, "%s%s.M3S", "patches\\", default_filename);
          v16 = fopen(Buffer, "wb");
          v17 = v16;
          if ( v16 )
          {
            fwrite(m3s_q_cache, 1u, 0x11940u, v16);
            fclose(v17);
          }
          cd_read_mode = 10;
          goto LABEL_36;
        }
LABEL_101:
        result = dbg_print(" YES.\n");
        BYTE1(cd_speed) = 0;
        return result;
      }
      memset(v47, 0xAAu, 0x1F9Cu);
      W2k_read_sector_mode2(0, 2u, 0x10u, 2u, (DWORD)v47);
      if ( !LOBYTE(v47[6]) && *(uint16_t *)((char *)&v47[6] + 1) == 5634 )
      {
        if ( !(HIBYTE(v47[1179]) % 10 + 16 * (HIBYTE(v47[1179]) / 10))
          && LOBYTE(v47[1180]) % 10 + 16 * (LOBYTE(v47[1180]) / 10) == 2
          && HIBYTE(v47[1180]) % 10 + 16 * (HIBYTE(v47[1180]) / 10) == 22
          && !LOBYTE(v47[1190])
          && *(uint16_t *)((char *)&v47[1190] + 1) == 5890
          && !(HIBYTE(v47[2363]) % 10 + 16 * (HIBYTE(v47[2363]) / 10))
          && LOBYTE(v47[2364]) % 10 + 16 * (LOBYTE(v47[2364]) / 10) == 2
          && HIBYTE(v47[2364]) % 10 + 16 * (HIBYTE(v47[2364]) / 10) == 23 )
        {
          cd_read_mode = 2;
          sector_stride = 2368;
          if ( !SubchannelW2kCaching )
            goto LABEL_101;
          m3s_q_cache = malloc(0x11940u);
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
                v23 = (char *)m3s_q_cache + v20;
                *v23 = *v21;
                v23[1] = v21[1];
                v23[2] = v21[2];
                v23[3] = v21[3];
                v24 = *((uint8_t *)m3s_q_cache + v20 + 3);
                v20 += 16;
                v21 += 592;
                *((char *)m3s_q_cache + v20 - 13) = v24 % 10 + 16 * (v24 / 10);
                *((char *)m3s_q_cache + v20 - 12) = (uint8_t)*((char *)m3s_q_cache + v20 - 12) % 10
                                                   + 16 * ((uint8_t)*((char *)m3s_q_cache + v20 - 12) / 10);
                *((char *)m3s_q_cache + v20 - 11) = (uint8_t)*((char *)m3s_q_cache + v20 - 11) % 10
                                                   + 16 * ((uint8_t)*((char *)m3s_q_cache + v20 - 11) / 10);
                *((char *)m3s_q_cache + v20 - 9) = (uint8_t)*((char *)m3s_q_cache + v20 - 9) % 10
                                                  + 16 * ((uint8_t)*((char *)m3s_q_cache + v20 - 9) / 10);
                *((char *)m3s_q_cache + v20 - 8) = (uint8_t)*((char *)m3s_q_cache + v20 - 8) % 10
                                                  + 16 * ((uint8_t)*((char *)m3s_q_cache + v20 - 8) / 10);
                --v22;
                *((char *)m3s_q_cache + v20 - 7) = (uint8_t)*((char *)m3s_q_cache + v20 - 7) % 10
                                                  + 16 * ((uint8_t)*((char *)m3s_q_cache + v20 - 7) / 10);
              }
              while ( v22 );
              v19 = v44 + 5;
              v25 = (uint8_t)(v44 + 5) < 0x4Bu;
              v44 += 5;
              v18 = v20;
            }
            while ( v25 );
            ++v41;
          }
          while ( v41 < 0x3Cu );
          sprintf(Buffer, "%s%s.M3S", "patches\\", default_filename);
          v26 = fopen(Buffer, "wb");
          if ( !v26 )
            goto LABEL_88;
          fwrite(m3s_q_cache, 1u, 0x11940u, v26);
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
          cd_read_mode = 3;
          sector_stride = 2368;
          if ( !SubchannelW2kCaching )
            goto LABEL_101;
          m3s_q_cache = malloc(0x11940u);
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
                v32 = (char *)m3s_q_cache + v29;
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
          sprintf(Buffer, "%s%s.M3S", "patches\\", default_filename);
          v34 = fopen(Buffer, "wb");
          v26 = v34;
          if ( !v34 )
            goto LABEL_88;
          fwrite(m3s_q_cache, 1u, 0x11940u, v34);
LABEL_87:
          fclose(v26);
LABEL_88:
          sector_stride = 2352;
          goto LABEL_100;
        }
      }
      memset(v47, 0xAAu, 0x1F9Cu);
      W2k_read_sector_mode3(0, 2u, 0x10u, 2u, (DWORD)v47);
      if ( *(uint16_t *)((char *)&v47[3] + 1) != 512
        || HIBYTE(v47[4]) != 22
        || *(uint16_t *)((char *)&v47[11] + 1) != 512
        || HIBYTE(v47[12]) != 23 )
      {
        return dbg_print(" NO.\n");
      }
      cd_read_mode = 4;
      sector_stride = 2352;
      m3s_q_cache = malloc(0x11940u);
      if ( !SubchannelW2kCaching )
        goto LABEL_101;
      m3s_q_cache = malloc(0x11940u);
      dbg_print(" YES.\n");
      dbg_print(" * Cdrom precaching subchannel ... ");
      v43 = 0;
      v35 = 0;
      do
      {
        for ( k = 0; k < 0x4Bu; k += 15 )
        {
          W2k_read_sector_mode3(3u, v43, k, 0xFu, (DWORD)v47);
          v37 = (char *)m3s_q_cache + v35;
          v35 += 240;
          qmemcpy(v37, v47, 0xF0u);
        }
        ++v43;
      }
      while ( v43 < 0x3Cu );
      sprintf(Buffer, "%s%s.M3S", "patches\\", default_filename);
      v38 = fopen(Buffer, "wb");
      if ( v38 )
      {
        fwrite(m3s_q_cache, 1u, 0x11940u, v38);
        fclose(v38);
      }
LABEL_100:
      cd_read_mode = 6;
LABEL_36:
      result = dbg_print("ok\n");
      BYTE1(cd_speed) = 0;
    }
  }
  return result;
}

int W2k_cdrom_read_data(uint8_t a1, uint8_t a2, uint8_t a3, char *Buffer)
{
  uint8_t v4;
  uint8_t v6;
  int v7;
  int v9;
  char *v10;
  unsigned int v11;
  int *v12;
  int *v13;
  int v14;
  int v15;
  int64_t v16;
  int64_t v17;
  int64_t v18;
  int64_t v19;
  int *v20;
  int v21;
  int v22;
  int v23;
  int *v24;
  int v25;
  int v26;
  int v27;
  int v28;
  int *v29;
  int *v30;
  char *v31;
  int *v32;
  int *v33;
  char *v34;
  int v35;
  int v36;
  int v37;
  unsigned int v38;

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
        v9 = cdr_msf_to_lba(a1, a2, v7);
        ppf_apply_patch_to_sector(v9, (int)Buffer);
      }
      if ( cd_savefake_flag == 1 )
        cdrom_fake_write_portion(a1, a2, v7, Buffer);
    }
    else
    {
      if ( v38 < cached_sector_lba || v38 >= cached_sector_lba + 8 )
      {
        if ( w2k_cdda_resume_pending )
        {
          W2k_resume_cdrom();
          v4 = a1;
          w2k_cdda_resume_pending = 0;
        }
        switch ( cd_read_mode )
        {
          case 1:
            if ( W2k_read_sector_mode1(v4, a2, a3, 8u, (DWORD)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
            v28 = 0;
            sub_q_cur0 = 0;
            sub_q_cur1 = 0;
            sub_q_cur2 = 0;
            goto LABEL_65;
          case 2:
            if ( W2k_read_sector_mode2(v4, a2, a3, 8u, (DWORD)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
            sub_q_cur3 = sub_q_rest[0];
            sub_q_cur0 = *(uint32_t *)sub_q_cache;
            sub_q_cur1 = sub_q_sec_frame;
            sub_q_cur2 = sub_q_asec_aframe;
            HIBYTE(sub_q_cur0) = (uint8_t)sub_q_minute % 10 + 16 * ((uint8_t)sub_q_minute / 10);
            LOBYTE(sub_q_cur1) = (uint8_t)sub_q_sec_frame % 10 + 16 * ((uint8_t)sub_q_sec_frame / 10);
            BYTE1(sub_q_cur1) = BYTE1(sub_q_sec_frame) % 10 + 16 * (BYTE1(sub_q_sec_frame) / 10);
            HIBYTE(sub_q_cur1) = HIBYTE(sub_q_sec_frame) % 10 + 16 * (HIBYTE(sub_q_sec_frame) / 10);
            LOBYTE(sub_q_cur2) = (uint8_t)sub_q_asec_aframe % 10 + 16 * ((uint8_t)sub_q_asec_aframe / 10);
            BYTE1(sub_q_cur2) = BYTE1(sub_q_asec_aframe) % 10 + 16 * (BYTE1(sub_q_asec_aframe) / 10);
            goto LABEL_66;
          case 3:
            if ( W2k_read_sector_mode2(v4, a2, a3, 8u, (DWORD)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
            sub_q_cur0 = *(uint32_t *)sub_q_cache;
            sub_q_cur1 = sub_q_sec_frame;
            sub_q_cur2 = sub_q_asec_aframe;
            sub_q_cur3 = sub_q_rest[0];
            goto LABEL_66;
          case 4:
            if ( W2k_read_sector_mode1(v4, a2, a3, 8u, (DWORD)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
            memset(sub_q_block_cache, 0, 0x80u);
            if ( a1 == 3
              && (cop0_bpc_value[0] & 0x1F000000) == 0x1F000000
              && W2k_read_sector_mode3(3u, a2, a3, 8u, (DWORD)sub_q_block_cache) )
            {
              dbg_print(" * Error sub reading CD: %d,%d,%d\n", 3, a2, v7);
            }
            goto LABEL_64;
          case 5:
            fseek(Stream, 96 * v38, 0);
            fread(cd_sector_cache, 1u, 0x300u, Stream);
            v30 = sub_q_block_cache;
            v31 = cd_sector_cache_cont;
            v36 = 8;
            do
            {
              *v30 = *(uint32_t *)v31;
              v30[1] = *((uint32_t *)v31 + 1);
              v30[2] = *((uint32_t *)v31 + 2);
              v30[3] = *((uint32_t *)v31 + 3);
              v31 += 96;
              v30 += 4;
              --v36;
            }
            while ( v36 );
            v6 = a2;
            if ( !W2k_read_sector_mode1(a1, a2, a3, 8u, (DWORD)cd_sector_cache) )
              goto LABEL_56;
            dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
            sub_q_cur0 = sub_q_block_cache[0];
            sub_q_cur1 = sub_q_block_cache1;
            sub_q_cur2 = sub_q_block_cache2;
            sub_q_cur3 = sub_q_block_cache3[0];
            goto LABEL_66;
          case 6:
            if ( W2k_read_sector_mode1(v4, a2, a3, 8u, (DWORD)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
            if ( a1 != 3 )
              goto LABEL_46;
            v29 = (int *)((char *)m3s_q_cache + 1200 * a2 + 16 * v7);
            sub_q_cur0 = *v29;
            sub_q_cur1 = v29[1];
            sub_q_cur2 = v29[2];
            sub_q_cur3 = v29[3];
            goto LABEL_66;
          case 7:
            if ( W2k_read_raw_sector(v4, a2, a3, 8u, (DWORD)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
LABEL_46:
            sub_q_cur0 = 0;
            sub_q_cur1 = 0;
            sub_q_cur2 = 0;
            sub_q_cur3 = 0;
            goto LABEL_66;
          case 8:
            memset(sub_q_block_cache, 0, 0x80u);
            if ( v4 == 3 && (cop0_bpc_value[0] & 0x1F000000) == 0x1F000000 )
            {
              if ( W2k_read_sector_with_subchannel_output(3u, a2, a3, 8u, (DWORD)cd_sector_cache, sub_q_block_cache) )
                dbg_print(" * Error sub reading CD: %d,%d,%d\n", 3, a2, v7);
              v4 = a1;
            }
            if ( W2k_read_raw_sector(v4, a2, a3, 8u, (DWORD)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
LABEL_64:
            sub_q_cur0 = sub_q_block_cache[0];
            v28 = sub_q_block_cache3[0];
            sub_q_cur1 = sub_q_block_cache1;
            sub_q_cur2 = sub_q_block_cache2;
            goto LABEL_65;
          case 9:
            fseek(Stream, 96 * v38, 0);
            fread(cd_sector_cache, 1u, 0x300u, Stream);
            v33 = sub_q_block_cache;
            v34 = cd_sector_cache_cont;
            v37 = 8;
            do
            {
              *v33 = *(uint32_t *)v34;
              v33[1] = *((uint32_t *)v34 + 1);
              v33[2] = *((uint32_t *)v34 + 2);
              v33[3] = *((uint32_t *)v34 + 3);
              v34 += 96;
              v33 += 4;
              --v37;
            }
            while ( v37 );
            v6 = a2;
            if ( W2k_read_raw_sector(a1, a2, a3, 8u, (DWORD)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
LABEL_56:
            sub_q_cur0 = sub_q_block_cache[0];
            sub_q_cur1 = sub_q_block_cache1;
            sub_q_cur2 = sub_q_block_cache2;
            sub_q_cur3 = sub_q_block_cache3[0];
            goto LABEL_66;
          case 10:
            if ( W2k_read_raw_sector(v4, a2, a3, 8u, (DWORD)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
            if ( a1 == 3 )
            {
              v32 = (int *)((char *)m3s_q_cache + 1200 * a2 + 16 * v7);
              sub_q_cur0 = *v32;
              sub_q_cur1 = v32[1];
              sub_q_cur2 = v32[2];
              v28 = v32[3];
LABEL_65:
              sub_q_cur3 = v28;
            }
            else
            {
              sub_q_cur0 = 0;
              sub_q_cur1 = 0;
              sub_q_cur2 = 0;
              sub_q_cur3 = 0;
            }
LABEL_66:
            v10 = Buffer;
            cached_sector_lba = v38;
            qmemcpy(Buffer, cd_sector_cache, 0x930u);
            break;
          default:
            goto LABEL_66;
        }
      }
      else
      {
        v10 = Buffer;
        v11 = v38 - cached_sector_lba;
        qmemcpy(Buffer, &cd_sector_cache[(v38 - cached_sector_lba) * sector_stride], 0x930u);
        switch ( cd_read_mode )
        {
          case 1:
          case 7:
            sub_q_cur0 = 0;
            sub_q_cur1 = 0;
            sub_q_cur2 = 0;
            sub_q_cur3 = 0;
            break;
          case 2:
            v13 = (int *)&sub_q_cache[v11 * sector_stride];
            v14 = v13[1];
            v15 = v13[2];
            sub_q_cur0 = *v13;
            sub_q_cur3 = v13[3];
            sub_q_cur1 = v14;
            sub_q_cur2 = v15;
            HIBYTE(sub_q_cur0) = HIBYTE(sub_q_cur0) % 10 + 16 * (HIBYTE(sub_q_cur0) / 10);
            LOBYTE(sub_q_cur1) = (uint8_t)v14 % 10 + 16 * ((uint8_t)v14 / 10);
            v16 = (uint8_t)(16 * (BYTE1(v14) / 10));
            BYTE1(sub_q_cur1) = BYTE4(v16) + v16;
            v17 = (uint8_t)(16 * (HIBYTE(v14) / 10));
            HIBYTE(sub_q_cur1) = BYTE4(v17) + v17;
            v18 = (uint8_t)(16 * ((uint8_t)v15 / 10));
            LOBYTE(sub_q_cur2) = BYTE4(v18) + v18;
            v19 = (uint8_t)(16 * (BYTE1(v15) / 10));
            BYTE1(sub_q_cur2) = BYTE4(v19) + v19;
            break;
          case 3:
            v20 = (int *)&sub_q_cache[v11 * sector_stride];
            v21 = v20[1];
            sub_q_cur0 = *v20;
            v22 = v20[2];
            sub_q_cur1 = v21;
            v23 = v20[3];
            sub_q_cur2 = v22;
            sub_q_cur3 = v23;
            break;
          case 4:
          case 5:
          case 8:
          case 9:
            v24 = &sub_q_block_cache[4 * v11];
            v25 = v24[1];
            sub_q_cur0 = *v24;
            v26 = v24[2];
            v27 = v24[3];
            sub_q_cur1 = v25;
            sub_q_cur2 = v26;
            sub_q_cur3 = v27;
            break;
          case 6:
          case 10:
            if ( a1 == 3 )
            {
              v12 = (int *)((char *)m3s_q_cache + 1200 * a2 + 16 * v7);
              sub_q_cur0 = *v12;
              sub_q_cur1 = v12[1];
              sub_q_cur2 = v12[2];
              sub_q_cur3 = v12[3];
            }
            else
            {
              sub_q_cur0 = 0;
              sub_q_cur1 = 0;
              sub_q_cur2 = 0;
              sub_q_cur3 = 0;
            }
            break;
          default:
            break;
        }
      }
      if ( ppf_enabled )
      {
        v35 = cdr_msf_to_lba(a1, v6, v7);
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


/* Decompiled globals (previously generated in src/_gen) */
unsigned char SubchannelW2kCaching;
unsigned char cd_speed = 0x5;
unsigned char scsi_port = 0x2;
unsigned char subchannel_mode_enabled;
unsigned char scsi_target;
unsigned char scsi_lun;
unsigned char track_count;
unsigned char w2k_toc_buffer;
unsigned char w2k_toc_first_track;
unsigned char w2k_toc_last_track;
unsigned char w2k_toc_track_control[1];
unsigned char w2k_toc_track_entries[0x31e];
unsigned char cd_sector_cache[1];
unsigned char cd_sector_cache_cont[0x924];
unsigned char sub_q_cache[1];
unsigned char sub_q_minute;
unsigned char cdrom_letter;
unsigned int w2k_resume_cdb = 0x4b;
unsigned int w2k_resume_cdb2 = 0x0;
unsigned int w2k_cdda_pause_pos = 0xffffffff;
unsigned int w2k_play_cdb = 0x47;
unsigned int w2k_play_cdb2 = 0x0;
unsigned int w2k_stop_cdb = 0x4b;
unsigned int w2k_stop_cdb2 = 0x0;
unsigned int w2k_cdda_playing;
unsigned int w2k_cdda_resume_pending;
unsigned int sub_q_sec_frame;
unsigned int sub_q_asec_aframe;
unsigned int sub_q_rest[0x10d1];
unsigned int sub_q_block_cache[1];
unsigned int sub_q_block_cache1;
unsigned int sub_q_block_cache2;
unsigned int sub_q_block_cache3[0x1d];
unsigned int m3s_q_cache;
unsigned int sector_stride;
unsigned int cd_read_mode;
unsigned int sub_q_cur0;
unsigned int sub_q_cur1;
unsigned int sub_q_cur2;
unsigned int sub_q_cur3;
unsigned int cop0_bpc_value[0x9];
unsigned int hObject;
unsigned char sound_use_cdda = 0x1;
unsigned short w2k_resume_cdb3 = 0x1;
unsigned short w2k_play_cdb3 = 0x0;
unsigned short w2k_stop_cdb3 = 0x0;
