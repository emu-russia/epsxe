#include "pch.h"

/* static prototypes for internal functions */
static int W2k_send_read_subchannel_command();
static bool W2k_read_raw_sector(
        uint8_t minute,
        uint8_t second,
        uint8_t frame,
        uint8_t sector_count,
        DWORD buffer);
static bool W2k_read_sector_mode1(
        uint8_t minute,
        uint8_t second,
        uint8_t frame,
        uint8_t sector_count,
        DWORD buffer);

static char W2k_find_cdrom_drive_letter()
{
  int drive_letter;
  CHAR RootPathName[4];

  drive_letter = 65;
  while ( 1 )
  {
    sprintf(RootPathName, "%c:\\", drive_letter);
    if ( GetDriveTypeA(RootPathName) == 5 )
      break;
    if ( (unsigned int)++drive_letter > 0x5A )
      return 0;
  }
  return drive_letter;
}

static HANDLE W2k_open_cdrom_device(uint8_t drive_letter)
{
  DWORD access;
  HANDLE result;
  CHAR FileName[12];
  struct _OSVERSIONINFOA VersionInformation;

  memset(&VersionInformation, 0, sizeof(VersionInformation));
  VersionInformation.dwOSVersionInfoSize = 148;
  GetVersionExA(&VersionInformation);
  access = 0x80000000;
  if ( VersionInformation.dwPlatformId == 2 && VersionInformation.dwMajorVersion > 4 )
    access = 0xC0000000;
  wsprintfA(FileName, "\\\\.\\%c:", drive_letter);
  result = CreateFileA(FileName, access, 1u, nullptr, 3u, 0, nullptr);
  if ( result == (HANDLE)-1 )
    return CreateFileA(FileName, access ^ 0x40000000, 1u, nullptr, 3u, 0, nullptr);
  return result;
}

static int W2k_get_scsi_address(uint8_t drive_letter, uint32_t *port, uint32_t *target, uint32_t *lun)
{
  HANDLE device;
  uint8_t target_val;
  uint8_t lun_val;
  DWORD BytesReturned;
  uint32_t OutBuffer[256];

  device = W2k_open_cdrom_device(drive_letter);
  if ( device == (HANDLE)-1 )
  {
    printf(" %c error handle \n", drive_letter);
    return -1;
  }
  else
  {
    memset(OutBuffer, 0, sizeof(OutBuffer));
    OutBuffer[0] = 8;
    if ( DeviceIoControl(device, IOCTL_SCSI_GET_ADDRESS, nullptr, 0, OutBuffer, 8u, &BytesReturned, nullptr) )
    {
      target_val = BYTE2(OutBuffer[1]);
      *port = LOBYTE(OutBuffer[1]);
      lun_val = HIBYTE(OutBuffer[1]);
      *target = target_val;
      *lun = lun_val;
      CloseHandle(device);
      return 0;
    }
    else
    {
      printf(" %c: error \n", drive_letter);
      return -1;
    }
  }
}

static int W2k_scsi_pass_through_direct(DWORD BytesReturned)
{
  DWORD buffer;
  int data_buffer;
  int timeout;
  uint32_t InBuffer[20];

  buffer = BytesReturned;
  data_buffer = *(uint32_t *)(BytesReturned + 16);
  memset(InBuffer, 0, sizeof(InBuffer));
  timeout = *(uint32_t *)(BytesReturned + 12);
  BYTE2(InBuffer[1]) = *(uint8_t *)(BytesReturned + 21);
  InBuffer[3] = timeout;
  InBuffer[5] = data_buffer;
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
    *(uint8_t *)(buffer + 1) = 1;
  }
  else
  {
    *(uint8_t *)(buffer + 1) = 4;
    *(uint8_t *)(buffer + 23) = 4;
    GetLastError();
  }
  return *(uint8_t *)(buffer + 1);
}

static char W2k_cdrom_gettrackinfo()
{
  HANDLE EventA;
  char result;
  uint8_t count;
  int track;
  char success;
  char retries;
  uint8_t total_tracks;
  unsigned int start_lba;
  int index;
  int end_lba;
  DWORD BytesReturned[20];

  retries = 10;
  success = 0;
  do
  {
    if ( success )
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
      success = 1;
    ++retries;
  }
  while ( retries );
  if ( BYTE1(BytesReturned[0]) != 1 )
    return dbg_print(" * gettrackinfo error[%d]\n", BYTE1(BytesReturned[0]));
  dbg_print(" * First/Last track: %d %d\n", (uint8_t)w2k_toc_first_track, (uint8_t)w2k_toc_last_track);
  result = w2k_toc_last_track - w2k_toc_first_track + 1;
  count = 0;
  total_tracks = result;
  track_count = result;
  LOBYTE(index) = 0;
  if ( w2k_toc_last_track - w2k_toc_first_track != 0xFF )
  {
    do
    {
      track = (uint8_t)index;
      dbg_print(" * Track %d: ", (uint8_t)w2k_toc_track_entries[8 * (uint8_t)index]);
      if ( (w2k_toc_track_control[8 * track] & 4) != 0 )
      {
        dbg_print("(DATA)  -");
      }
      else
      {
        dbg_print("(AUDIO) -");
        if ( !count )
          nocd = 2;
      }
      W9x_bcd_to_dword(&start_lba, (uint8_t *)(8 * track + 5241928));
      start_lba += 150;
      dbg_print(" Start %d: (%02d,%02d,%02d) - ", track, (uint8_t)(start_lba / 0x4B / 0x3C), start_lba / 0x4B % 0x3C, start_lba % 0x4B);
      W9x_bcd_to_dword(&start_lba, (uint8_t *)(8 * track + 5241928));
      W9x_bcd_to_dword(&end_lba, (uint8_t *)(8 * track + 5241936));
      dbg_print(" Length %02d:%02d\n", (end_lba - start_lba) / 0x4B / 0x3C, (end_lba - start_lba) / 0x4B % 0x3C);
      result = total_tracks;
      LOBYTE(index) = ++count;
    }
    while ( count < total_tracks );
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
  uint8_t sector_buffer[8092];

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
    memset(sector_buffer, 0xAAu, sizeof(sector_buffer));
    cd_read_mode = 0;
    cached_sector_lba = -1;
    W2k_read_sector_mode1(0, 2u, 0x10u, 2u, (DWORD)sector_buffer);
    result = sector_buffer[12];
    if ( !sector_buffer[12] && sector_buffer[13] == 2 && sector_buffer[14] == 22 && (result = sector_buffer[2364]) == 0 && sector_buffer[2365] == 2 && sector_buffer[2366] == 23 )
    {
      cd_read_mode = 1;
      sector_stride = 2352;
    }
    else if ( cd_read_mode != 1 )
    {
      memset(sector_buffer, 0xAAu, sizeof(sector_buffer));
      W2k_read_raw_sector(0, 2u, 0x10u, 2u, (DWORD)sector_buffer);
      result = sector_buffer[12];
      if ( !sector_buffer[12] && sector_buffer[13] == 2 && sector_buffer[14] == 22 )
      {
        result = sector_buffer[2364];
        if ( !sector_buffer[2364] && sector_buffer[2365] == 2 && sector_buffer[2366] == 23 )
        {
          cd_read_mode = 7;
          sector_stride = 2352;
        }
      }
    }
  }
  return result;
}

char W2k_get_first_last_track(uint8_t *first_track, uint8_t *last_track)
{
  char result;

  *first_track = w2k_toc_first_track;
  result = track_count;
  *last_track = track_count;
  return result;
}

unsigned int W2k_track_to_msf(int track, uint8_t *minute, uint8_t *second, uint8_t *frame)
{
  unsigned int result;
  unsigned int lba;
  unsigned int sec;

  result = (uint8_t)track_count;
  if ( (int16_t)track <= (int)(uint8_t)track_count )
  {
    if ( (uint16_t)track )
      W9x_bcd_to_dword(&track, (uint8_t *)(8 * (int16_t)track + 5241920));
    else
      W9x_bcd_to_dword(&track, (uint8_t *)(8 * (uint8_t)track_count + 5241928));
    lba = (track + 150) / 0x4Bu;
    *frame = (track + 150) % 0x4Bu;
    sec = lba % 0x3C;
    result = lba / 0x3C;
    *second = sec;
    *minute = result;
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

static char W2k_find_track_by_min_sec(unsigned int minute, char second)
{
  char minute_target;
  uint8_t track;

  track = 0;
  if ( !track_count )
    return 0;
  minute_target = minute;
  while ( 1 )
  {
    W9x_bcd_to_dword(&minute, (uint8_t *)(8 * track + 5241928));
    minute += 150;
    if ( (uint8_t)(minute / 0x4B / 0x3C) == minute_target && minute / 0x4B % 0x3C == second )
      break;
    if ( ++track >= (uint8_t)track_count )
      return 0;
  }
  return minute % 0x4B;
}

char W2k_cdrom_play_cdda(unsigned int minute, int second, uint8_t frame)
{
  char result;
  uint8_t second_copy;
  HANDLE EventA;
  DWORD BytesReturned[20];

  result = sound_use_cdda;
  if ( sound_use_cdda )
  {
    second_copy = second;
    frame = W2k_find_track_by_min_sec(minute, second);
    BYTE1(w2k_play_cdb2) = frame;
    HIBYTE(w2k_play_cdb) = minute;
    LOBYTE(w2k_play_cdb2) = second_copy;
    W9x_bcd_to_dword(&second, (uint8_t *)(8 * (uint8_t)track_count + 5241928));
    LOBYTE(w2k_play_cdb3) = (second + 150) % 0x4Bu;
    BYTE2(w2k_play_cdb2) = (second + 150) / 0x4Bu / 0x3C;
    HIBYTE(w2k_play_cdb2) = (second + 150) / 0x4Bu % 0x3C;
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
      return printf(" * W2k play cdda error (%d, %d, %d) \n", (uint8_t)minute, second_copy, frame);
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
        unsigned int minute,
        uint8_t second,
        uint8_t frame,
        uint8_t *out_track,
        uint8_t *out_minute,
        uint8_t *out_second,
        uint8_t *out_frame)
{
  uint8_t track_index;
  unsigned int lba;
  char result;
  unsigned int offset;
  uint8_t index;

  track_index = 0;
  index = 0;
  lba = (frame & 0xF) % 10
      + 75
      * ((second & 0xF) % 10 + 10 * ((second >> 4) + 6 * ((uint8_t)(minute & 0xF) % 10 + 10 * ((uint8_t)minute >> 4))))
      + 10 * (frame >> 4)
      - 150;
  W9x_bcd_to_dword(&minute, (uint8_t *)(8 * (uint8_t)track_count + 5241928));
  if ( minute > lba && track_count )
  {
    while ( 1 )
    {
      W9x_bcd_to_dword(&minute, (uint8_t *)(8 * index + 5241936));
      if ( index + 1 < (uint8_t)track_count )
        minute -= minute % 0x4B;
      if ( minute > lba )
        break;
      index = ++track_index;
      if ( track_index >= (uint8_t)track_count )
        goto LABEL_7;
    }
    W9x_bcd_to_dword(&minute, (uint8_t *)(8 * index + 5241928));
    offset = lba + minute % 0x4B - minute;
    *out_track = (index + 1) % 10 + 16 * ((index + 1) / 10);
    *out_minute = offset / 0x4B / 0x3C % 0xA + 16 * (offset / 0x4B / 0x3C / 0xA);
    *out_second = offset / 0x4B % 0x3C % 0xA + 16 * (offset / 0x4B % 0x3C / 0xA);
    result = offset % 0x4B % 0xA + 16 * (offset % 0x4B / 0xA);
    *out_frame = result;
  }
  else
  {
LABEL_7:
    result = (char)out_track;
    *out_track = -86;
  }
  return result;
}

char W2k_lba_to_msf(
        unsigned int minute,
        uint8_t second,
        uint8_t frame,
        uint8_t *out_minute,
        uint8_t *out_second,
        uint8_t *out_frame)
{
  char saved_minute;
  unsigned int lba;
  uint8_t *sec_out;
  uint8_t saved_second;
  uint8_t *tmp;
  unsigned int frame_out;
  unsigned int second_out;
  uint8_t track_index;

  saved_minute = minute;
  track_index = 0;
  lba = (frame & 0xF) % 10
      + 75
      * ((second & 0xF) % 10 + 10 * ((second >> 4) + 6 * ((uint8_t)(minute & 0xF) % 10 + 10 * ((uint8_t)minute >> 4))))
      + 10 * (frame >> 4);
  W9x_bcd_to_dword(&minute, (uint8_t *)(8 * (uint8_t)track_count + 5241928));
  if ( minute > lba )
  {
    LOBYTE(tmp) = track_count;
    if ( track_count )
    {
      while ( 1 )
      {
        W9x_bcd_to_dword(&minute, (uint8_t *)(8 * track_index + 5241936));
        if ( minute > lba )
          break;
        LOBYTE(tmp) = ++track_index;
        if ( track_index >= (uint8_t)track_count )
          return (char)tmp;
      }
      frame_out = minute % 0x4B;
      second_out = minute / 0x4B % 0x3C;
      *out_minute = minute / 0x4B / 0x3C;
      LOBYTE(tmp) = (uint8_t)out_second;
      *out_second = second_out;
      *out_frame = frame_out;
    }
  }
  else
  {
    sec_out = out_second;
    saved_second = second;
    *out_minute = saved_minute;
    tmp = out_frame;
    *sec_out = saved_second;
    *tmp = frame;
  }
  return (char)tmp;
}

uint8_t W2k_check_subchannel_data(unsigned int minute, uint8_t second, uint8_t frame, int out)
{
  char minute_bcd;
  char error_count;
  uint8_t result;
  char mismatches;
  uint8_t second_bcd;
  uint8_t sec_bcd;
  uint8_t prev_frame;
  uint8_t prev_frame_bcd;
  uint8_t frame_bcd;

  *(uint32_t *)out = 0;
  *(uint32_t *)(out + 4) = 0;
  mismatches = 0;
  if ( (uint8_t)sub_q_cur0 )
  {
    if ( frame )
    {
      prev_frame = frame - 1;
    }
    else
    {
      prev_frame = 74;
      if ( second )
      {
        --second;
      }
      else
      {
        second = 59;
        LOBYTE(minute) = minute - 1;
      }
    }
    minute_bcd = (uint8_t)minute % 10 + 16 * ((uint8_t)minute / 10);
    second_bcd = second % 10 + 16 * (second / 10);
    prev_frame_bcd = prev_frame % 10 + 16 * (prev_frame / 10);
    *(uint32_t *)out = *(int *)((char *)&sub_q_cur0 + 1);
    *(uint8_t *)(out + 4) = BYTE1(sub_q_cur1);
    *(uint16_t *)(out + 5) = *(uint16_t *)((char *)&sub_q_cur1 + 3);
    *(uint8_t *)(out + 7) = BYTE1(sub_q_cur2);
    if ( minute_bcd != *(uint8_t *)(out + 5) )
      mismatches = 1;
    if ( minute_bcd != *(uint8_t *)(out + 2) )
      ++mismatches;
    if ( second_bcd != *(uint8_t *)(out + 6) )
      ++mismatches;
    error_count = mismatches;
    if ( ((second_bcd & 0xF) % 10 + 10 * (second_bcd >> 4) - 2) % 10 + 16 * (((second_bcd & 0xF) % 10 + 10 * (second_bcd >> 4) - 2) / 10) != *(uint8_t *)(out + 3) )
      error_count = mismatches + 1;
    result = prev_frame_bcd;
    if ( prev_frame_bcd != *(uint8_t *)(out + 7) )
      ++error_count;
    if ( prev_frame_bcd != *(uint8_t *)(out + 4) )
      ++error_count;
    if ( (uint8_t)error_count >= 2u )
    {
      result = 0;
      *(uint32_t *)(out + 2) = 0;
      *(uint16_t *)(out + 6) = 0;
      if ( minute_bcd == 3 )
        xenogears_cd_detected = 1;
    }
  }
  else
  {
    LOBYTE(minute) = (uint8_t)minute % 10 + 16 * ((uint8_t)minute / 10);
    sec_bcd = second % 10 + 16 * (second / 10);
    frame_bcd = frame % 10 + 16 * (frame / 10);
    W2k_msf_to_lba(minute, sec_bcd, frame_bcd, (uint8_t *)out, (uint8_t *)(out + 2), (uint8_t *)(out + 3), (uint8_t *)(out + 4));
    *(uint8_t *)(out + 1) = 1;
    *(uint8_t *)(out + 5) = minute;
    *(uint8_t *)(out + 6) = sec_bcd;
    *(uint8_t *)(out + 7) = frame_bcd;
    return frame_bcd;
  }
  return result;
}

static bool W2k_send_scsi_command(const void *cdb, unsigned int cdb_length, DWORD buffer, DWORD length)
{
  HANDLE EventA;
  DWORD BytesReturned[20];

  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(BytesReturned, 0, sizeof(BytesReturned));
  LOBYTE(BytesReturned[2]) = scsi_target;
  BytesReturned[4] = buffer;
  BYTE1(BytesReturned[2]) = scsi_lun;
  BYTE2(BytesReturned[0]) = scsi_port;
  BytesReturned[3] = length;
  LOBYTE(BytesReturned[0]) = 2;
  HIBYTE(BytesReturned[0]) = 72;
  LOWORD(BytesReturned[5]) = 3086;
  BytesReturned[6] = (DWORD)EventA;
  qmemcpy(&BytesReturned[12], cdb, cdb_length);
  ResetEvent(EventA);
  if ( !W2k_scsi_pass_through_direct((DWORD)BytesReturned) )
    WaitForSingleObject(EventA, 0xFFFFFFFF);
  CloseHandle(EventA);
  return BYTE1(BytesReturned[0]) != 1;
}

static int W2k_send_read_toc_command()
{
  HANDLE EventA;
  uint8_t cdb[10];
  uint8_t control[2];
  DWORD BytesReturned[20];

  cdb[0] = 0;
  cdb[1] = 0;
  cdb[2] = 0;
  cdb[3] = 8;
  cdb[4] = 0;
  cdb[5] = 0;
  cdb[6] = 0;
  cdb[7] = 0;
  cdb[8] = 0;
  cdb[9] = 0;
  qmemcpy(control, "\t0", sizeof(control));
  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(BytesReturned, 0, sizeof(BytesReturned));
  BYTE2(BytesReturned[0]) = scsi_port;
  LOBYTE(BytesReturned[2]) = scsi_target;
  LOBYTE(BytesReturned[0]) = 2;
  BYTE1(BytesReturned[2]) = scsi_lun;
  HIBYTE(BytesReturned[0]) = 64;
  BytesReturned[3] = 12;
  BytesReturned[4] = (DWORD)cdb;
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
  uint8_t cdb[4];
  char param[8];
  DWORD BytesReturned[20];

  cdb[0] = 0;
  cdb[1] = 0;
  cdb[2] = 0;
  cdb[3] = 8;
  strcpy(param, "S");
  param[2] = 0;
  param[3] = 0;
  param[4] = 0;
  param[5] = 0;
  param[6] = 8;
  param[7] = 0;
  subchannel_mode_enabled = 0;
  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(BytesReturned, 0, sizeof(BytesReturned));
  BYTE2(BytesReturned[0]) = scsi_port;
  LOBYTE(BytesReturned[2]) = scsi_target;
  LOBYTE(BytesReturned[0]) = 2;
  BYTE1(BytesReturned[2]) = scsi_lun;
  HIBYTE(BytesReturned[0]) = 68;
  BytesReturned[3] = 12;
  BytesReturned[4] = (DWORD)cdb;
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
        uint8_t minute,
        uint8_t second,
        uint8_t frame,
        uint8_t sector_count,
        DWORD buffer)
{
  char opcode;
  int16_t cdb_word_1;
  char lba_hi;
  char lba_mid;
  int16_t lba_lo;
  char cdb_byte_1;
  int sectors;

  if ( !subchannel_mode_enabled )
  {
    if ( W2k_send_read_toc_command() != 1 )
      return 1;
    subchannel_mode_enabled = 1;
  }
  cdb_byte_1 = 0;
  cdb_word_1 = 0;
  sectors = sector_count;
  lba_hi = (75 * (second + 60 * minute) + (unsigned int)frame - 150) >> 16;
  opcode = 40;
  lba_mid = (uint16_t)(75 * (second + 60 * minute) + frame - 150) >> 8;
  lba_lo = (uint8_t)(75 * (second + 60 * minute) + frame + 106);
  return W2k_send_scsi_command(&opcode, 0xAu, buffer, 2352 * sector_count);
}

static bool W2k_read_sector_with_subchannel_output(
        uint8_t minute,
        uint8_t second,
        uint8_t frame,
        uint8_t sector_count,
        DWORD buffer,
        uint32_t *subchannel)
{
  bool result;
  int sectors;
  uint32_t *src;
  uint32_t *dst;
  int tmp;
  char opcode;
  int16_t cdb_word_1;
  char lba_hi;
  char lba_mid;
  int16_t lba_lo;
  char cdb_byte_1;
  int transfer_length;

  if ( !subchannel_mode_enabled )
  {
    if ( W2k_send_read_toc_command() != 1 )
      return 1;
    subchannel_mode_enabled = 1;
  }
  cdb_byte_1 = 0;
  lba_lo = (uint8_t)(75 * (second + 60 * minute) + frame + 106);
  transfer_length = 0x10000;
  cdb_word_1 = 0;
  sectors = sector_count;
  lba_hi = (75 * (second + 60 * minute) + (unsigned int)frame - 150) >> 16;
  opcode = -40;
  lba_mid = (uint16_t)(75 * (second + 60 * minute) + frame - 150) >> 8;
  BYTE1(transfer_length) = sector_count;
  result = W2k_send_scsi_command(&opcode, 0xCu, buffer, 2368 * sector_count);
  if ( sector_count )
  {
    src = (uint32_t *)(buffer + 2352);
    do
    {
      dst = subchannel;
      *subchannel = *src;
      subchannel[1] = src[1];
      subchannel[2] = src[2];
      tmp = src[3];
      src += 592;
      subchannel += 4;
      --sectors;
      dst[3] = tmp;
    }
    while ( sectors );
  }
  return result;
}

static bool W2k_read_sector_mode1(
        uint8_t minute,
        uint8_t second,
        uint8_t frame,
        uint8_t sector_count,
        DWORD buffer)
{
  char opcode;
  int16_t cdb_word_1;
  char lba_hi;
  char lba_mid;
  int16_t lba_lo;
  char cdb_byte_1;
  uint8_t sectors;
  char cdb_byte_2;
  int16_t cdb_word_2;

  cdb_byte_1 = 0;
  cdb_word_2 = 0;
  lba_lo = (uint8_t)(75 * (second + 60 * minute) + frame + 106);
  cdb_word_1 = 0;
  sectors = sector_count;
  lba_hi = (75 * (second + 60 * minute) + (unsigned int)frame - 150) >> 16;
  opcode = -66;
  lba_mid = (uint16_t)(75 * (second + 60 * minute) + frame - 150) >> 8;
  cdb_byte_2 = -8;
  return W2k_send_scsi_command(&opcode, 0xCu, buffer, 2352 * sector_count);
}

static bool W2k_read_sector_mode2(
        uint8_t minute,
        uint8_t second,
        uint8_t frame,
        uint8_t sector_count,
        DWORD buffer)
{
  char opcode;
  int16_t cdb_word_1;
  char lba_hi;
  char lba_mid;
  int16_t lba_lo;
  char cdb_byte_1;
  uint8_t sectors;
  char cdb_byte_2;
  int16_t cdb_word_2;

  cdb_byte_1 = 0;
  lba_lo = (uint8_t)(75 * (second + 60 * minute) + frame + 106);
  cdb_word_1 = 0;
  sectors = sector_count;
  lba_hi = (75 * (second + 60 * minute) + (unsigned int)frame - 150) >> 16;
  opcode = -66;
  lba_mid = (uint16_t)(75 * (second + 60 * minute) + frame - 150) >> 8;
  cdb_byte_2 = -8;
  cdb_word_2 = 2;
  return W2k_send_scsi_command(&opcode, 0xCu, buffer, 2368 * sector_count);
}

static bool W2k_read_sector_mode3(
        uint8_t minute,
        uint8_t second,
        uint8_t frame,
        uint8_t sector_count,
        DWORD buffer)
{
  char opcode;
  int16_t cdb_word_1;
  char lba_hi;
  char lba_mid;
  int16_t lba_lo;
  char cdb_byte_1;
  int16_t sectors;
  int16_t cdb_word_2;

  cdb_byte_1 = 0;
  lba_lo = (uint8_t)(75 * (second + 60 * minute) + frame + 106);
  sectors = sector_count;
  lba_hi = (75 * (second + 60 * minute) + (unsigned int)frame - 150) >> 16;
  opcode = -66;
  cdb_word_1 = 4;
  lba_mid = (uint16_t)(75 * (second + 60 * minute) + frame - 150) >> 8;
  cdb_word_2 = 2;
  return W2k_send_scsi_command(&opcode, 0xCu, buffer, 16 * sector_count);
}

static bool W2k_send_subchannel_command(int lba)
{
  int16_t opcode;
  char lba_msb;
  char lba_hi;
  char lba_mid;
  char lba_lo;
  int16_t cdb_word_1;
  int16_t cdb_word_2;

  cdb_word_1 = 0;
  cdb_word_2 = 0;
  lba_msb = HIBYTE(lba);
  lba_hi = BYTE2(lba);
  opcode = 43;
  lba_mid = BYTE1(lba);
  lba_lo = lba;
  return W2k_send_scsi_command(&opcode, 0xAu, 0, 0);
}

static bool W2k_get_subchannel_status(uint32_t *status)
{
  uint32_t cdb[2];
  char param[4];

  cdb[1] = 0;
  param[1] = 0;
  *status = 0;
  status[1] = 0;
  status[2] = 0;
  status[3] = 0;
  cdb[0] = 0x1400242;
  param[0] = 16;
  return W2k_send_scsi_command(cdb, 0xAu, (DWORD)status, 0x10u);
}

char W2k_cdrom_subchannel_read()
{
  char result;
  int pass;
  FILE *file;
  int lba;
  int seconds;
  int frames;
  uint32_t *dst;
  int fix_offset;
  int minutes;
  int frame_count;
  uint32_t *fix_dst;
  FILE *out_file;
  FILE *out_file_copy;
  int cache_offset;
  uint8_t i;
  char *cache_dst;
  FILE *out_file2;
  FILE *out_file2_copy;
  int offset;
  uint8_t frame;
  int offset_run;
  uint32_t *mode2_src;
  int count;
  uint32_t *mode2_dst;
  int tmp;
  bool more;
  FILE *out_file3;
  int offset2;
  uint8_t j;
  int offset_run2;
  uint32_t *mode3_src;
  int count2;
  uint32_t *mode3_dst;
  int tmp2;
  FILE *out_file4;
  int offset3;
  uint8_t k;
  char *mode4_dst;
  FILE *out_file5;
  int passes;
  uint8_t minute;
  uint8_t minute2;
  uint8_t minute3;
  uint8_t minute4;
  char prev_frame;
  uint32_t sub_status[256];
  char Buffer[1024];
  uint16_t sector_buffer[9472];

  result = cd_savefake_flag;
  cached_sector_lba = -1;
  if ( cd_savefake_flag && loaded_file_type != 3 )
  {
    pass = 1;
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
      file = fopen(Buffer, "rb");
      if ( file )
      {
        m3s_q_cache = malloc(0x11940u);
        fread(m3s_q_cache, 1u, 0x11940u, file);
        fclose(file);
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
        passes = 2;
        do
        {
          dbg_print(" * Cdrom precaching subchannel ... (step %d/2) ", pass);
          lba = 12600;
          seconds = 70;
          do
          {
            W2k_send_subchannel_command(lba);
            frames = 75;
            do
            {
              W2k_get_subchannel_status(sub_status);
              if ( BYTE1(sub_status[2]) % 10 + 16 * (BYTE1(sub_status[2]) / 10) == 3
                && BYTE2(sub_status[2]) < 0x3Cu
                && HIBYTE(sub_status[2]) < 0x4Bu )
              {
                dst = (char *)m3s_q_cache + 1200 * BYTE2(sub_status[2]) + 16 * HIBYTE(sub_status[2]);
                *dst = sub_status[0];
                dst[1] = sub_status[1];
                dst[2] = sub_status[2];
                dst[3] = sub_status[3];
              }
              --frames;
            }
            while ( frames );
            lba += 75;
            --seconds;
          }
          while ( seconds );
          dbg_print("ok\n");
          ++pass;
          --passes;
        }
        while ( passes );
        dbg_print(" * Fixating subchanel ... ");
        fix_offset = 0;
        minutes = 60;
        do
        {
          frame_count = 75;
          do
          {
            fix_dst = (char *)m3s_q_cache + fix_offset;
            sub_status[0] = *(uint32_t *)((char *)m3s_q_cache + fix_offset);
            sub_status[1] = *(uint32_t *)((char *)m3s_q_cache + fix_offset + 4);
            sub_status[2] = *(uint32_t *)((char *)m3s_q_cache + fix_offset + 8);
            sub_status[3] = *(uint32_t *)((char *)m3s_q_cache + fix_offset + 12);
            *fix_dst = 0;
            fix_dst[1] = 0;
            fix_dst[2] = 0;
            fix_dst[3] = 0;
            *((uint8_t *)m3s_q_cache + fix_offset) = 65;
            *(uint16_t *)((char *)m3s_q_cache + fix_offset + 1) = HIWORD(sub_status[1]);
            fix_offset += 16;
            *((char *)m3s_q_cache + fix_offset - 13) = BYTE1(sub_status[3]) % 10 + 16 * (BYTE1(sub_status[3]) / 10);
            *((char *)m3s_q_cache + fix_offset - 12) = BYTE2(sub_status[3]) % 10 + 16 * (BYTE2(sub_status[3]) / 10);
            *((char *)m3s_q_cache + fix_offset - 11) = HIBYTE(sub_status[3]) % 10 + 16 * (HIBYTE(sub_status[3]) / 10);
            *((char *)m3s_q_cache + fix_offset - 9) = BYTE1(sub_status[2]) % 10 + 16 * (BYTE1(sub_status[2]) / 10);
            *((char *)m3s_q_cache + fix_offset - 8) = BYTE2(sub_status[2]) % 10 + 16 * (BYTE2(sub_status[2]) / 10);
            --frame_count;
            *((char *)m3s_q_cache + fix_offset - 7) = HIBYTE(sub_status[2]) % 10 + 16 * (HIBYTE(sub_status[2]) / 10);
          }
          while ( frame_count );
          --minutes;
        }
        while ( minutes );
        cd_read_mode = 6;
        sprintf(Buffer, "%s%s.M3S", "patches\\", default_filename);
        out_file = fopen(Buffer, "wb");
        out_file_copy = out_file;
        if ( out_file )
        {
          fwrite(m3s_q_cache, 1u, 0x11940u, out_file);
          fclose(out_file_copy);
        }
        result = dbg_print("ok\n");
        BYTE1(cd_speed) = 0;
        return result;
      }
      result = SubchannelW2kCdromEnabled;
      if ( !SubchannelW2kCdromEnabled )
        return result;
      dbg_print(" * Checking subchannel read from cdrom ... ");
      if ( cd_read_mode == 7 )
      {
        W2k_read_sector_with_subchannel_output(0, 2u, 0x10u, 2u, (DWORD)sector_buffer, sub_status);
        result = HIBYTE(sub_status[1]);
        if ( HIBYTE(sub_status[1]) )
          return result;
        result = sub_status[2];
        if ( LOWORD(sub_status[2]) != 5634 )
          return result;
        result = HIBYTE(sub_status[5]);
        if ( *(uint16_t *)((char *)&sub_status[5] + 3) != 512 || BYTE1(sub_status[6]) != 23 )
          return result;
        cd_read_mode = 8;
        sector_stride = 2352;
        if ( SubchannelW2kCaching )
        {
          m3s_q_cache = malloc(0x11940u);
          dbg_print(" YES.\n");
          dbg_print(" * Cdrom precaching subchannel ... ");
          minute = 0;
          cache_offset = 0;
          do
          {
            for ( i = 0; i < 0x4Bu; i += 5 )
            {
              W2k_read_sector_with_subchannel_output(3u, minute, i, 5u, (DWORD)sector_buffer, sub_status);
              cache_dst = (char *)m3s_q_cache + cache_offset;
              cache_offset += 80;
              qmemcpy(cache_dst, sub_status, 0x50u);
            }
            ++minute;
          }
          while ( minute < 0x3Cu );
          sprintf(Buffer, "%s%s.M3S", "patches\\", default_filename);
          out_file2 = fopen(Buffer, "wb");
          out_file2_copy = out_file2;
          if ( out_file2 )
          {
            fwrite(m3s_q_cache, 1u, 0x11940u, out_file2);
            fclose(out_file2_copy);
          }
          cd_read_mode = 10;
          result = dbg_print("ok\n");
          BYTE1(cd_speed) = 0;
          return result;
        }
        result = dbg_print(" YES.\n");
        BYTE1(cd_speed) = 0;
        return result;
      }
      memset(sector_buffer, 0xAAu, 0x1F9Cu);
      W2k_read_sector_mode2(0, 2u, 0x10u, 2u, (DWORD)sector_buffer);
      if ( !LOBYTE(sector_buffer[6]) && *(uint16_t *)((char *)&sector_buffer[6] + 1) == 5634 )
      {
        if ( !(HIBYTE(sector_buffer[1179]) % 10 + 16 * (HIBYTE(sector_buffer[1179]) / 10))
          && LOBYTE(sector_buffer[1180]) % 10 + 16 * (LOBYTE(sector_buffer[1180]) / 10) == 2
          && HIBYTE(sector_buffer[1180]) % 10 + 16 * (HIBYTE(sector_buffer[1180]) / 10) == 22
          && !LOBYTE(sector_buffer[1190])
          && *(uint16_t *)((char *)&sector_buffer[1190] + 1) == 5890
          && !(HIBYTE(sector_buffer[2363]) % 10 + 16 * (HIBYTE(sector_buffer[2363]) / 10))
          && LOBYTE(sector_buffer[2364]) % 10 + 16 * (LOBYTE(sector_buffer[2364]) / 10) == 2
          && HIBYTE(sector_buffer[2364]) % 10 + 16 * (HIBYTE(sector_buffer[2364]) / 10) == 23 )
        {
          cd_read_mode = 2;
          sector_stride = 2368;
          if ( SubchannelW2kCaching )
          {
            m3s_q_cache = malloc(0x11940u);
            dbg_print(" YES.\n");
            dbg_print(" * Cdrom precaching subchannel ... ");
            minute2 = 0;
            offset = 0;
            do
            {
              frame = 0;
              prev_frame = 0;
              do
              {
                W2k_read_sector_mode2(3u, minute2, frame, 5u, (DWORD)sector_buffer);
                offset_run = offset;
                mode2_src = &sector_buffer[1176];
                count = 5;
                do
                {
                  mode2_dst = (char *)m3s_q_cache + offset_run;
                  *mode2_dst = *mode2_src;
                  mode2_dst[1] = mode2_src[1];
                  mode2_dst[2] = mode2_src[2];
                  mode2_dst[3] = mode2_src[3];
                  tmp = *((uint8_t *)m3s_q_cache + offset_run + 3);
                  offset_run += 16;
                  mode2_src += 592;
                  *((char *)m3s_q_cache + offset_run - 13) = tmp % 10 + 16 * (tmp / 10);
                  *((char *)m3s_q_cache + offset_run - 12) = (uint8_t)*((char *)m3s_q_cache + offset_run - 12) % 10
                                                             + 16 * ((uint8_t)*((char *)m3s_q_cache + offset_run - 12) / 10);
                  *((char *)m3s_q_cache + offset_run - 11) = (uint8_t)*((char *)m3s_q_cache + offset_run - 11) % 10
                                                             + 16 * ((uint8_t)*((char *)m3s_q_cache + offset_run - 11) / 10);
                  *((char *)m3s_q_cache + offset_run - 9) = (uint8_t)*((char *)m3s_q_cache + offset_run - 9) % 10
                                                           + 16 * ((uint8_t)*((char *)m3s_q_cache + offset_run - 9) / 10);
                  *((char *)m3s_q_cache + offset_run - 8) = (uint8_t)*((char *)m3s_q_cache + offset_run - 8) % 10
                                                           + 16 * ((uint8_t)*((char *)m3s_q_cache + offset_run - 8) / 10);
                  --count;
                  *((char *)m3s_q_cache + offset_run - 7) = (uint8_t)*((char *)m3s_q_cache + offset_run - 7) % 10
                                                           + 16 * ((uint8_t)*((char *)m3s_q_cache + offset_run - 7) / 10);
                }
                while ( count );
                frame = prev_frame + 5;
                more = (uint8_t)(prev_frame + 5) < 0x4Bu;
                prev_frame += 5;
                offset = offset_run;
              }
              while ( more );
              ++minute2;
            }
            while ( minute2 < 0x3Cu );
            sprintf(Buffer, "%s%s.M3S", "patches\\", default_filename);
            out_file3 = fopen(Buffer, "wb");
            if ( !out_file3 )
              goto LABEL_88;
            fwrite(m3s_q_cache, 1u, 0x11940u, out_file3);
            goto LABEL_87;
          }
          result = dbg_print(" YES.\n");
          BYTE1(cd_speed) = 0;
          return result;
        }
        if ( !HIBYTE(sector_buffer[1179])
          && sector_buffer[1180] == 5634
          && !LOBYTE(sector_buffer[1190])
          && HIBYTE(sector_buffer[1190]) == LOBYTE(sector_buffer[1180])
          && LOBYTE(sector_buffer[1191]) == 23
          && !HIBYTE(sector_buffer[2363])
          && LOBYTE(sector_buffer[2364]) == LOBYTE(sector_buffer[1180])
          && HIBYTE(sector_buffer[2364]) == 23 )
        {
          cd_read_mode = 3;
          sector_stride = 2368;
          if ( SubchannelW2kCaching )
          {
            m3s_q_cache = malloc(0x11940u);
            dbg_print(" YES.\n");
            dbg_print(" * Cdrom precaching subchannel ... ");
            minute3 = 0;
            offset2 = 0;
            do
            {
              for ( j = 0; j < 0x4Bu; j += 5 )
              {
                W2k_read_sector_mode2(3u, minute3, j, 5u, (DWORD)sector_buffer);
                offset_run2 = offset2;
                mode3_src = &sector_buffer[1176];
                count2 = 5;
                do
                {
                  mode3_dst = (char *)m3s_q_cache + offset_run2;
                  *mode3_dst = *mode3_src;
                  mode3_dst[1] = mode3_src[1];
                  mode3_dst[2] = mode3_src[2];
                  tmp2 = mode3_src[3];
                  offset_run2 += 16;
                  mode3_src += 592;
                  --count2;
                  mode3_dst[3] = tmp2;
                }
                while ( count2 );
                offset2 = offset_run2;
              }
              ++minute3;
            }
            while ( minute3 < 0x3Cu );
            sprintf(Buffer, "%s%s.M3S", "patches\\", default_filename);
            out_file4 = fopen(Buffer, "wb");
            out_file3 = out_file4;
            if ( !out_file4 )
              goto LABEL_88;
            fwrite(m3s_q_cache, 1u, 0x11940u, out_file4);
LABEL_87:
            fclose(out_file3);
LABEL_88:
            sector_stride = 2352;
            goto LABEL_100;
          }
          result = dbg_print(" YES.\n");
          BYTE1(cd_speed) = 0;
          return result;
        }
      }
      memset(sector_buffer, 0xAAu, 0x1F9Cu);
      W2k_read_sector_mode3(0, 2u, 0x10u, 2u, (DWORD)sector_buffer);
      if ( *(uint16_t *)((char *)&sector_buffer[3] + 1) != 512
        || HIBYTE(sector_buffer[4]) != 22
        || *(uint16_t *)((char *)&sector_buffer[11] + 1) != 512
        || HIBYTE(sector_buffer[12]) != 23 )
      {
        return dbg_print(" NO.\n");
      }
      cd_read_mode = 4;
      sector_stride = 2352;
      m3s_q_cache = malloc(0x11940u);
      if ( !SubchannelW2kCaching )
      {
        result = dbg_print(" YES.\n");
        BYTE1(cd_speed) = 0;
        return result;
      }
      m3s_q_cache = malloc(0x11940u);
      dbg_print(" YES.\n");
      dbg_print(" * Cdrom precaching subchannel ... ");
      minute4 = 0;
      offset3 = 0;
      do
      {
        for ( k = 0; k < 0x4Bu; k += 15 )
        {
          W2k_read_sector_mode3(3u, minute4, k, 0xFu, (DWORD)sector_buffer);
          mode4_dst = (char *)m3s_q_cache + offset3;
          offset3 += 240;
          qmemcpy(mode4_dst, sector_buffer, 0xF0u);
        }
        ++minute4;
      }
      while ( minute4 < 0x3Cu );
      sprintf(Buffer, "%s%s.M3S", "patches\\", default_filename);
      out_file5 = fopen(Buffer, "wb");
      if ( out_file5 )
      {
        fwrite(m3s_q_cache, 1u, 0x11940u, out_file5);
        fclose(out_file5);
      }
LABEL_100:
      cd_read_mode = 6;
      result = dbg_print("ok\n");
      BYTE1(cd_speed) = 0;
    }
  }
  return result;
}

int W2k_cdrom_read_data(uint8_t minute, uint8_t second, uint8_t frame, char *Buffer)
{
  uint8_t minute_copy;
  uint8_t second_copy;
  int frame_copy;
  int patch_lba;
  char *dst;
  unsigned int offset;
  int *sub_entry;
  int *sub_ptr;
  int q1;
  int q2;
  int64_t tmp1;
  int64_t tmp2;
  int64_t tmp3;
  int64_t tmp4;
  int *sub_ptr2;
  int q1b;
  int q2b;
  int q3b;
  int *block_ptr;
  int q1c;
  int q2c;
  int q3c;
  int cur3;
  int *sub_entry2;
  int *block_ptr2;
  char *src;
  int *sub_entry3;
  int *block_ptr3;
  char *src2;
  int patch_lba2;
  int count;
  int count2;
  unsigned int lba;

  minute_copy = minute;
  second_copy = second;
  frame_copy = frame;
  lba = 75 * (second + 60 * minute) + frame - 150;
  if ( cd_savefake_flag )
  {
    if ( loaded_file_type == 3 )
    {
      iso_read_data(minute, second, frame_copy, (int)Buffer);
      if ( ppf_enabled )
      {
        patch_lba = cdr_msf_to_lba(minute, second, frame_copy);
        ppf_apply_patch_to_sector(patch_lba, (int)Buffer);
      }
      if ( cd_savefake_flag == 1 )
        cdrom_fake_write_portion(minute, second, frame_copy, Buffer);
    }
    else
    {
      if ( lba < cached_sector_lba || lba >= cached_sector_lba + 8 )
      {
        if ( w2k_cdda_resume_pending )
        {
          W2k_resume_cdrom();
          minute_copy = minute;
          w2k_cdda_resume_pending = 0;
        }
        switch ( cd_read_mode )
        {
          case 1:
            if ( W2k_read_sector_mode1(minute_copy, second, frame, 8u, (DWORD)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", minute, second, frame_copy);
            cur3 = 0;
            sub_q_cur0 = 0;
            sub_q_cur1 = 0;
            sub_q_cur2 = 0;
            goto LABEL_65;
          case 2:
            if ( W2k_read_sector_mode2(minute_copy, second, frame, 8u, (DWORD)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", minute, second, frame_copy);
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
            if ( W2k_read_sector_mode2(minute_copy, second, frame, 8u, (DWORD)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", minute, second, frame_copy);
            sub_q_cur0 = *(uint32_t *)sub_q_cache;
            sub_q_cur1 = sub_q_sec_frame;
            sub_q_cur2 = sub_q_asec_aframe;
            sub_q_cur3 = sub_q_rest[0];
            goto LABEL_66;
          case 4:
            if ( W2k_read_sector_mode1(minute_copy, second, frame, 8u, (DWORD)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", minute, second, frame_copy);
            memset(sub_q_block_cache, 0, 0x80u);
            if ( minute == 3
              && (cop0_bpc_value[0] & 0x1F000000) == 0x1F000000
              && W2k_read_sector_mode3(3u, second, frame, 8u, (DWORD)sub_q_block_cache) )
            {
              dbg_print(" * Error sub reading CD: %d,%d,%d\n", 3, second, frame_copy);
            }
            goto LABEL_64;
          case 5:
            fseek(Stream, 96 * lba, 0);
            fread(cd_sector_cache, 1u, 0x300u, Stream);
            block_ptr2 = sub_q_block_cache;
            src = cd_sector_cache_cont;
            count = 8;
            do
            {
              *block_ptr2 = *(uint32_t *)src;
              block_ptr2[1] = *((uint32_t *)src + 1);
              block_ptr2[2] = *((uint32_t *)src + 2);
              block_ptr2[3] = *((uint32_t *)src + 3);
              src += 96;
              block_ptr2 += 4;
              --count;
            }
            while ( count );
            second_copy = second;
            if ( W2k_read_sector_mode1(minute, second, frame, 8u, (DWORD)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", minute, second, frame_copy);
            sub_q_cur0 = sub_q_block_cache[0];
            sub_q_cur1 = sub_q_block_cache1;
            sub_q_cur2 = sub_q_block_cache2;
            sub_q_cur3 = sub_q_block_cache3[0];
            goto LABEL_66;
          case 6:
            if ( W2k_read_sector_mode1(minute_copy, second, frame, 8u, (DWORD)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", minute, second, frame_copy);
            if ( minute != 3 )
              goto LABEL_46;
            sub_entry2 = (int *)((char *)m3s_q_cache + 1200 * second + 16 * frame_copy);
            sub_q_cur0 = *sub_entry2;
            sub_q_cur1 = sub_entry2[1];
            sub_q_cur2 = sub_entry2[2];
            sub_q_cur3 = sub_entry2[3];
            goto LABEL_66;
          case 7:
            if ( W2k_read_raw_sector(minute_copy, second, frame, 8u, (DWORD)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", minute, second, frame_copy);
LABEL_46:
            sub_q_cur0 = 0;
            sub_q_cur1 = 0;
            sub_q_cur2 = 0;
            sub_q_cur3 = 0;
            goto LABEL_66;
          case 8:
            memset(sub_q_block_cache, 0, 0x80u);
            if ( minute_copy == 3 && (cop0_bpc_value[0] & 0x1F000000) == 0x1F000000 )
            {
              if ( W2k_read_sector_with_subchannel_output(3u, second, frame, 8u, (DWORD)cd_sector_cache, sub_q_block_cache) )
                dbg_print(" * Error sub reading CD: %d,%d,%d\n", 3, second, frame_copy);
              minute_copy = minute;
            }
            if ( W2k_read_raw_sector(minute_copy, second, frame, 8u, (DWORD)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", minute, second, frame_copy);
LABEL_64:
            sub_q_cur0 = sub_q_block_cache[0];
            cur3 = sub_q_block_cache3[0];
            sub_q_cur1 = sub_q_block_cache1;
            sub_q_cur2 = sub_q_block_cache2;
            goto LABEL_65;
          case 9:
            fseek(Stream, 96 * lba, 0);
            fread(cd_sector_cache, 1u, 0x300u, Stream);
            block_ptr3 = sub_q_block_cache;
            src2 = cd_sector_cache_cont;
            count2 = 8;
            do
            {
              *block_ptr3 = *(uint32_t *)src2;
              block_ptr3[1] = *((uint32_t *)src2 + 1);
              block_ptr3[2] = *((uint32_t *)src2 + 2);
              block_ptr3[3] = *((uint32_t *)src2 + 3);
              src2 += 96;
              block_ptr3 += 4;
              --count2;
            }
            while ( count2 );
            second_copy = second;
            if ( W2k_read_raw_sector(minute, second, frame, 8u, (DWORD)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", minute, second, frame_copy);
            sub_q_cur0 = sub_q_block_cache[0];
            sub_q_cur1 = sub_q_block_cache1;
            sub_q_cur2 = sub_q_block_cache2;
            sub_q_cur3 = sub_q_block_cache3[0];
            goto LABEL_66;
          case 10:
            if ( W2k_read_raw_sector(minute_copy, second, frame, 8u, (DWORD)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", minute, second, frame_copy);
            if ( minute == 3 )
            {
              sub_entry3 = (int *)((char *)m3s_q_cache + 1200 * second + 16 * frame_copy);
              sub_q_cur0 = *sub_entry3;
              sub_q_cur1 = sub_entry3[1];
              sub_q_cur2 = sub_entry3[2];
              cur3 = sub_entry3[3];
LABEL_65:
              sub_q_cur3 = cur3;
            }
            else
            {
              sub_q_cur0 = 0;
              sub_q_cur1 = 0;
              sub_q_cur2 = 0;
              sub_q_cur3 = 0;
            }
LABEL_66:
            dst = Buffer;
            cached_sector_lba = lba;
            qmemcpy(Buffer, cd_sector_cache, 0x930u);
            break;
          default:
            goto LABEL_66;
        }
      }
      else
      {
        dst = Buffer;
        offset = lba - cached_sector_lba;
        qmemcpy(Buffer, &cd_sector_cache[(lba - cached_sector_lba) * sector_stride], 0x930u);
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
            sub_ptr = (int *)&sub_q_cache[offset * sector_stride];
            q1 = sub_ptr[1];
            q2 = sub_ptr[2];
            sub_q_cur0 = *sub_ptr;
            sub_q_cur3 = sub_ptr[3];
            sub_q_cur1 = q1;
            sub_q_cur2 = q2;
            HIBYTE(sub_q_cur0) = HIBYTE(sub_q_cur0) % 10 + 16 * (HIBYTE(sub_q_cur0) / 10);
            LOBYTE(sub_q_cur1) = (uint8_t)q1 % 10 + 16 * ((uint8_t)q1 / 10);
            tmp1 = (uint8_t)(16 * (BYTE1(q1) / 10));
            BYTE1(sub_q_cur1) = BYTE4(tmp1) + tmp1;
            tmp2 = (uint8_t)(16 * (HIBYTE(q1) / 10));
            HIBYTE(sub_q_cur1) = BYTE4(tmp2) + tmp2;
            tmp3 = (uint8_t)(16 * ((uint8_t)q2 / 10));
            LOBYTE(sub_q_cur2) = BYTE4(tmp3) + tmp3;
            tmp4 = (uint8_t)(16 * (BYTE1(q2) / 10));
            BYTE1(sub_q_cur2) = BYTE4(tmp4) + tmp4;
            break;
          case 3:
            sub_ptr2 = (int *)&sub_q_cache[offset * sector_stride];
            q1b = sub_ptr2[1];
            sub_q_cur0 = *sub_ptr2;
            q2b = sub_ptr2[2];
            sub_q_cur1 = q1b;
            q3b = sub_ptr2[3];
            sub_q_cur2 = q2b;
            sub_q_cur3 = q3b;
            break;
          case 4:
          case 5:
          case 8:
          case 9:
            block_ptr = &sub_q_block_cache[4 * offset];
            q1c = block_ptr[1];
            sub_q_cur0 = *block_ptr;
            q2c = block_ptr[2];
            q3c = block_ptr[3];
            sub_q_cur1 = q1c;
            sub_q_cur2 = q2c;
            sub_q_cur3 = q3c;
            break;
          case 6:
          case 10:
            if ( minute == 3 )
            {
              sub_entry = (int *)((char *)m3s_q_cache + 1200 * second + 16 * frame_copy);
              sub_q_cur0 = *sub_entry;
              sub_q_cur1 = sub_entry[1];
              sub_q_cur2 = sub_entry[2];
              sub_q_cur3 = sub_entry[3];
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
        patch_lba2 = cdr_msf_to_lba(minute, second_copy, frame_copy);
        ppf_apply_patch_to_sector(patch_lba2, (int)dst);
      }
      if ( cd_savefake_flag == 1 )
        cdrom_fake_write_portion(minute, second_copy, frame_copy, dst);
    }
    return 0;
  }
  else
  {
    cdrom_fake_read_portion(minute, second, frame_copy, Buffer);
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
