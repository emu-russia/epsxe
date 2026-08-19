#include "pch.h"

/* static prototypes for internal functions */
static int W9x_disable_subchannel_mode();
static char W9x_read_cd_sectors(
        uint8_t minute,
        uint8_t second,
        uint8_t frame,
        uint8_t count,
        BYTE *buffer);
static char W9x_read_cd_data_only(
        uint8_t minute,
        uint8_t second,
        uint8_t frame,
        uint8_t count,
        BYTE *buffer);
static BOOL W9x_resume_cdda();

/* ASPI support: wnaspi32.lib is not shipped with modern SDKs, so load the
 * function from the system DLL at runtime. */
DWORD GetASPI32SupportInfo(void)
{
    static DWORD(WINAPI * real)(void) = NULL;
    if (!real)
    {
        HMODULE m = LoadLibraryA("WNASPI32.DLL");
        if (m)
            real = (DWORD(WINAPI*)(void))GetProcAddress(m, "GetASPI32SupportInfo");
    }
    if (!real)
        return 0;
    return real();
}

static char W9x_exec_scsi_cmd(const void *cdb, unsigned int cdb_len, BYTE *buffer, DWORD buffer_len)
{
  HANDLE EventA;
  SRB_ExecSCSICmd srb;

  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(&srb, 0, sizeof(srb));
  srb.SRB_Target = cdrom_target;
  srb.SRB_BufPointer = buffer;
  srb.SRB_CDBLen = cdb_len;
  srb.SRB_Lun = cdrom_lun;
  srb.SRB_HaId = cdrom_haid;
  srb.SRB_Cmd = 2;
  srb.SRB_Flags = 72;
  srb.SRB_BufLen = buffer_len;
  srb.SRB_SenseLen = 14;
  srb.SRB_PostProc = EventA;
  qmemcpy(srb.CDBByte, cdb, cdb_len);
  ResetEvent(EventA);
  if ( !SendASPI32Command_cb(&srb) )
    WaitForSingleObject(EventA, 0xFFFFFFFF);
  if ( srb.SRB_Status != 1 )
    return 1;
  CloseHandle(EventA);
  return 0;
}

static int W9x_add_cdrom_device_info(BYTE ha_id, BYTE target_id, BYTE lun)
{
  HANDLE EventA;
  int device_index;
  char device_count;
  int product_part;
  char *product_ptr;
  int revision;
  SRB_ExecSCSICmd srb;
  uint32_t buffer[25];

  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(&srb, 0, sizeof(srb));
  memset(buffer, 0, sizeof(buffer));
  srb.SRB_Target = target_id;
  srb.SRB_Cmd = 2;
  srb.SRB_HaId = ha_id;
  srb.SRB_Lun = lun;
  srb.SRB_Flags = 72;
  srb.SRB_BufLen = 100;
  srb.SRB_BufPointer = (BYTE *)buffer;
  srb.SRB_SenseLen = 14;
  srb.SRB_CDBLen = 6;
  srb.SRB_PostProc = EventA;
  srb.CDBByte[0] = 18;
  srb.CDBByte[4] = 100;
  ResetEvent(EventA);
  if ( !SendASPI32Command_cb(&srb) )
    WaitForSingleObject(EventA, 0xFFFFFFFF);
  device_index = CloseHandle(EventA);
  if ( srb.SRB_Status == 1 )
  {
    device_count = HIBYTE(w9x_cdrom_info);
    product_part = buffer[4];
    device_index = HIBYTE(w9x_cdrom_info) << 6;
    *(int *)((char *)&cd_device_vendor + device_index) = buffer[2];
    *(int *)((char *)&cd_device_vendor2 + device_index) = buffer[3];
    cd_device_reserved0[device_index] = 0;
    product_ptr = &cd_device_product[device_index];
    *(uint32_t *)product_ptr = product_part;
    *((uint32_t *)product_ptr + 1) = buffer[5];
    *((uint32_t *)product_ptr + 2) = buffer[6];
    *((uint32_t *)product_ptr + 3) = buffer[7];
    revision = buffer[8];
    cd_device_reserved1[device_index] = 0;
    *(int *)((char *)&cd_device_revision + device_index) = revision;
    cd_device_reserved2[device_index] = 0;
    qmemcpy(&cd_device_extra[device_index], &buffer[9], 0x14u);
    cd_device_reserved3[device_index] = 0;
    *(int *)((char *)&cd_device_haid + device_index) = ha_id;
    *(int *)((char *)&cd_device_target + device_index) = target_id;
    *(int *)((char *)cd_device_lun + device_index) = lun;
    HIBYTE(w9x_cdrom_info) = device_count + 1;
  }
  return device_index;
}

char W9x_init_aspi()
{
  char result;
  int16_t ASPI32SupportInfo;
  BYTE adapter;
  char target_count;
  uint8_t lun_index;
  BYTE target_id;
  BYTE ha_id;
  BYTE lun;
  uint32_t srb_inq[2];
  BYTE srb_target;
  uint8_t srb_lun;
  int16_t srb_scsi_id;
  uint8_t srb[60];

  result = HIBYTE(w9x_cdrom_info);
  if ( !HIBYTE(w9x_cdrom_info) )
  {
    ASPI32SupportInfo = GetASPI32SupportInfo();
    BYTE1(w9x_cdrom_info) = ASPI32SupportInfo;
    if ( HIBYTE(ASPI32SupportInfo) != 1 && HIBYTE(ASPI32SupportInfo) != 0xE8 )
      fatal_error_with_message_box(" * Error in init aspi (%d)\n", HIBYTE(ASPI32SupportInfo));
    result = BYTE1(w9x_cdrom_info);
    adapter = 0;
    for ( ha_id = 0; adapter < BYTE1(w9x_cdrom_info); ha_id = adapter )
    {
      memset(srb, 0, sizeof(srb));
      srb[0] = 0;
      srb[2] = adapter;
      SendASPI32Command_cb(srb);
      if ( srb[1] == 1 )
      {
        target_count = srb[45];
        BYTE2(w9x_cdrom_info) = srb[45];
        if ( !srb[45] )
        {
          target_count = 8;
          BYTE2(w9x_cdrom_info) = 8;
        }
        target_id = 0;
        if ( target_count )
        {
          do
          {
            lun_index = 0;
            lun = 0;
            do
            {
              srb_inq[0] = 1;
              srb_inq[1] = 0;
              srb_scsi_id = 0;
              BYTE2(srb_inq[0]) = ha_id;
              srb_target = target_id;
              srb_lun = lun_index;
              SendASPI32Command_cb(srb_inq);
              if ( BYTE1(srb_inq[0]) == 1 && (uint8_t)srb_scsi_id == 5 )
                W9x_add_cdrom_device_info(ha_id, target_id, lun);
              lun = ++lun_index;
            }
            while ( lun_index < 8u );
            ++target_id;
          }
          while ( target_id < BYTE2(w9x_cdrom_info) );
          adapter = ha_id;
        }
      }
      result = BYTE1(w9x_cdrom_info);
      ++adapter;
    }
  }
  return result;
}

uint32_t * W9x_bcd_to_dword(uint32_t *dest, uint8_t *src)
{
  *dest = src[3] + ((src[2] + ((src[1] + (*src << 8)) << 8)) << 8);
  return dest;
}

static uint32_t *W9x_cdrom_gettrackinfo()
{
  char retries;
  bool error;
  uint8_t index;
  int track_idx;
  unsigned int start_lba;
  int track;
  int track_count;
  int end_lba;
  uint32_t cdb[3];

  cdb[0] = 0x43;
  cdb[1] = 0x3000000;
  cdb[2] = 0x24;
  retries = 10;
  error = 1;
  while ( error )
  {
    memset(w9x_toc_buffer, 0, 0x324u);
    error = W9x_exec_scsi_cmd(cdb, 0xAu, w9x_toc_buffer, 0x324u) != 0;
    if ( !++retries )
    {
      if ( error )
        return (uint32_t *)dbg_print(" * Cdrom gettrackinfo error.\n");
      break;
    }
  }
  dbg_print(" * First/Last track: %d %d\n", (uint8_t)w9x_toc_first_track, (uint8_t)w9x_toc_last_track);
  index = 0;
  LOBYTE(track_count) = w9x_toc_last_track - w9x_toc_first_track + 1;
  LOBYTE(w9x_cdrom_info) = track_count;
  LOBYTE(track) = 0;
  if ( w9x_toc_last_track - w9x_toc_first_track != 0xFF )
  {
    do
    {
      track_idx = (uint8_t)track;
      dbg_print(" * Track %d: ", (uint8_t)w9x_toc_track_entries[8 * (uint8_t)track]);
      if ( (w9x_toc_track_control[8 * track_idx] & 4) != 0 )
      {
        dbg_print("(DATA)  -");
      }
      else
      {
        dbg_print("(AUDIO) -");
        if ( !index )
          nocd = 2;
      }
      W9x_bcd_to_dword(&start_lba, (uint8_t *)(8 * track_idx + 5262504));
      start_lba += 150;
      dbg_print(" Start %d: (%02d,%02d,%02d) - ", track_idx, (uint8_t)(start_lba / 0x4B / 0x3C), start_lba / 0x4B % 0x3C, start_lba % 0x4B);
      W9x_bcd_to_dword(&start_lba, (uint8_t *)(8 * track_idx + 5262504));
      W9x_bcd_to_dword(&end_lba, (uint8_t *)(8 * track_idx + 5262512));
      dbg_print(" Length %02d:%02d\n", (end_lba - start_lba) / 0x4B / 0x3C, (end_lba - start_lba) / 0x4B % 0x3C);
      LOBYTE(track) = ++index;
    }
    while ( index < (uint8_t)track_count );
  }
  return W9x_bcd_to_dword(&end_lba, (uint8_t *)(8 * (uint8_t)track_count + 5262504));
}

int ( *W9x_load_winaspi_dll())(LPSRB)
{
  HMODULE LibraryA;
  int ( *send_aspi)(LPSRB);

  LibraryA = LoadLibraryA("WNASPI32.DLL");
  hCdrModule = LibraryA;
  if ( !LibraryA )
    fatal_error_with_message_box(" * Error loading WNASPI32.DLL\n");
  GetASPI32SupportInfo_cb = GetProcAddress(LibraryA, "GetASPI32SupportInfo");
  send_aspi = (int ( *)(LPSRB))GetProcAddress(hCdrModule, "SendASPI32Command");
  SendASPI32Command_cb = send_aspi;
  if ( !GetASPI32SupportInfo_cb || !send_aspi )
    fatal_error_with_message_box("Error loading WNASPI32.DLL\n");
  return send_aspi;
}

int W9x_load_win_aspi_silent()
{
  HMODULE LibraryA;
  int ( *SendASPI32Command)(LPSRB);

  LibraryA = LoadLibraryA("WNASPI32.DLL");
  hCdrModule = LibraryA;
  if ( LibraryA
    && (GetASPI32SupportInfo_cb = GetProcAddress(LibraryA, "GetASPI32SupportInfo"),
        SendASPI32Command = (int ( *)(LPSRB))GetProcAddress(hCdrModule, "SendASPI32Command"),
        SendASPI32Command_cb = SendASPI32Command,
        GetASPI32SupportInfo_cb)
    && SendASPI32Command )
  {
    return 0;
  }
  else
  {
    return -1;
  }
}

HMODULE W9x_free_winaspi_dll()
{
  HMODULE result;

  result = hCdrModule;
  if ( hCdrModule )
  {
    FreeLibrary(hCdrModule);
    if ( GetASPI32SupportInfo_cb )
      GetASPI32SupportInfo_cb = 0;
    result = (HMODULE)SendASPI32Command_cb;
    if ( SendASPI32Command_cb )
      SendASPI32Command_cb = nullptr;
  }
  return result;
}

char W9x_cdrom_init()
{
  char result;
  BYTE buffer[8092];

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
    dbg_print(" * Init Core W9x cdrom ... ");
    W9x_load_winaspi_dll();
    dbg_print("ok\n");
    W9x_init_aspi();
    W9x_cdrom_gettrackinfo();
    memset(buffer, 0xAAu, sizeof(buffer));
    cd_read_mode = 0;
    cached_sector_lba = -1;
    W9x_read_cd_data_only(0, 2u, 0x10u, 2u, buffer);
    result = buffer[12];
    if ( !buffer[12] && buffer[13] == 2 && buffer[14] == 22 && (result = buffer[2364]) == 0 && buffer[2365] == 2 && buffer[2366] == 23 )
    {
      cd_read_mode = 1;
      sector_stride = 2352;
    }
    else if ( cd_read_mode != 1 )
    {
      memset(buffer, 0xAAu, sizeof(buffer));
      W9x_read_cd_sectors(0, 2u, 0x10u, 2u, buffer);
      result = buffer[12];
      if ( !buffer[12] && buffer[13] == 2 && buffer[14] == 22 )
      {
        result = buffer[2364];
        if ( !buffer[2364] && buffer[2365] == 2 && buffer[2366] == 23 )
        {
          cd_read_mode = 7;
          sector_stride = 2352;
        }
      }
    }
  }
  return result;
}

char W9x_get_first_last_track(uint8_t *first_track, uint8_t *last_track)
{
  char result;

  *first_track = w9x_toc_first_track;
  result = w9x_cdrom_info;
  *last_track = w9x_cdrom_info;
  return result;
}

unsigned int W9x_track_to_msf(int16_t track, uint8_t *minute, uint8_t *second, uint8_t *frame)
{
  unsigned int result;
  unsigned int total_seconds;
  unsigned int seconds;
  int lba;

  result = (uint8_t)w9x_cdrom_info;
  lba = 0;
  if ( track <= (int)(uint8_t)w9x_cdrom_info )
  {
    if ( track )
      W9x_bcd_to_dword(&lba, (uint8_t *)(8 * track + 5262496));
    else
      W9x_bcd_to_dword(&lba, (uint8_t *)(8 * (uint8_t)w9x_cdrom_info + 5262504));
    total_seconds = (lba + 150) / 0x4Bu;
    *frame = (lba + 150) % 0x4Bu;
    seconds = total_seconds % 0x3C;
    result = total_seconds / 0x3C;
    *second = seconds;
    *minute = result;
  }
  return result;
}

HMODULE W9x_cdrom_deinit()
{
  if ( cd_savefake_flag >= 0 )
    cdrom_fake_write();
  if ( loaded_file_type == 3 )
    iso_close();
  if ( m3s_q_cache )
    free(m3s_q_cache);
  if ( subchannel_mode_enabled )
    W9x_disable_subchannel_mode();
  if ( Stream )
    fclose(Stream);
  W9x_cdrom_stop();
  return W9x_free_winaspi_dll();
}

static int W9x_enable_subchannel_mode()
{
  HANDLE EventA;
  uint8_t cdb[10];
  uint8_t mode_data[2];
  uint32_t srb[20];

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
  qmemcpy(mode_data, "\t0", sizeof(mode_data));
  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(srb, 0, sizeof(srb));
  BYTE2(srb[0]) = cdrom_haid;
  LOBYTE(srb[2]) = cdrom_target;
  LOBYTE(srb[0]) = 2;
  BYTE1(srb[2]) = cdrom_lun;
  HIBYTE(srb[0]) = 64;
  srb[3] = 12;
  srb[4] = cdb;
  LOWORD(srb[5]) = 1550;
  srb[6] = EventA;
  LOBYTE(srb[12]) = 21;
  LOBYTE(srb[13]) = 12;
  ResetEvent(EventA);
  if ( !SendASPI32Command_cb(srb) )
    WaitForSingleObject(EventA, 0xFFFFFFFF);
  return BYTE1(srb[0]) != 1 ? 4 : 1;
}

static int W9x_disable_subchannel_mode()
{
  HANDLE EventA;
  uint8_t cdb[4];
  char mode_data[8];
  uint32_t srb[20];

  cdb[0] = 0;
  cdb[1] = 0;
  cdb[2] = 0;
  cdb[3] = 8;
  strcpy(mode_data, "S");
  mode_data[2] = 0;
  mode_data[3] = 0;
  mode_data[4] = 0;
  mode_data[5] = 0;
  mode_data[6] = 8;
  mode_data[7] = 0;
  subchannel_mode_enabled = 0;
  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(srb, 0, sizeof(srb));
  BYTE2(srb[0]) = cdrom_haid;
  LOBYTE(srb[2]) = cdrom_target;
  LOBYTE(srb[0]) = 2;
  BYTE1(srb[2]) = cdrom_lun;
  HIBYTE(srb[0]) = 68;
  srb[3] = 12;
  srb[4] = cdb;
  LOWORD(srb[5]) = 1550;
  srb[6] = EventA;
  LOBYTE(srb[12]) = 21;
  LOBYTE(srb[13]) = 12;
  ResetEvent(EventA);
  if ( !SendASPI32Command_cb(srb) )
    WaitForSingleObject(EventA, 0xFFFFFFFF);
  return BYTE1(srb[0]) != 1 ? 4 : 1;
}

static char W9x_read_cd_sectors(
        uint8_t minute,
        uint8_t second,
        uint8_t frame,
        uint8_t count,
        BYTE *buffer)
{
  char opcode;
  int16_t cdb_byte1;
  char lba_hi;
  char lba_mid;
  int16_t lba_lo;
  char cdb_byte5;
  int cdb_count;

  if ( !subchannel_mode_enabled )
  {
    if ( W9x_enable_subchannel_mode() != 1 )
      return 1;
    subchannel_mode_enabled = 1;
  }
  cdb_byte5 = 0;
  cdb_byte1 = 0;
  cdb_count = count;
  lba_hi = (75 * (second + 60 * minute) + (unsigned int)frame - 150) >> 16;
  opcode = 40;
  lba_mid = (uint16_t)(75 * (second + 60 * minute) + frame - 150) >> 8;
  lba_lo = (uint8_t)(75 * (second + 60 * minute) + frame + 106);
  return W9x_exec_scsi_cmd(&opcode, 0xAu, buffer, 2352 * count);
}

static char W9x_read_cd_with_subchannel(
        uint8_t minute,
        uint8_t second,
        uint8_t frame,
        uint8_t count,
        BYTE *buffer,
        uint32_t *subchannel)
{
  char result;
  int remaining;
  BYTE *src;
  uint32_t *sub_out;
  int dword;
  char opcode;
  int16_t cdb_byte1;
  char lba_hi;
  char lba_mid;
  int16_t lba_lo;
  char cdb_byte5;
  int cdb_count;

  if ( !subchannel_mode_enabled )
  {
    if ( W9x_enable_subchannel_mode() != 1 )
      return 1;
    subchannel_mode_enabled = 1;
  }
  cdb_byte5 = 0;
  lba_lo = (uint8_t)(75 * (second + 60 * minute) + frame + 106);
  cdb_count = 0x10000;
  cdb_byte1 = 0;
  remaining = count;
  lba_hi = (75 * (second + 60 * minute) + (unsigned int)frame - 150) >> 16;
  opcode = -40;
  lba_mid = (uint16_t)(75 * (second + 60 * minute) + frame - 150) >> 8;
  BYTE1(cdb_count) = count;
  result = W9x_exec_scsi_cmd(&opcode, 0xCu, buffer, 2368 * count);
  if ( count )
  {
    src = buffer + 2352;
    do
    {
      sub_out = subchannel;
      *subchannel = *(uint32_t *)src;
      subchannel[1] = *((uint32_t *)src + 1);
      subchannel[2] = *((uint32_t *)src + 2);
      dword = *((uint32_t *)src + 3);
      src += 2368;
      subchannel += 4;
      --remaining;
      sub_out[3] = dword;
    }
    while ( remaining );
  }
  return result;
}

static char W9x_read_cd_data_only(
        uint8_t minute,
        uint8_t second,
        uint8_t frame,
        uint8_t count,
        BYTE *buffer)
{
  char opcode;
  int16_t cdb_byte1;
  char lba_hi;
  char lba_mid;
  int16_t lba_lo;
  char cdb_byte7;
  uint8_t cdb_count;
  char cdb_byte9;
  int16_t cdb_byte10;

  cdb_byte7 = 0;
  cdb_byte10 = 0;
  lba_lo = (uint8_t)(75 * (second + 60 * minute) + frame + 106);
  cdb_byte1 = 0;
  cdb_count = count;
  lba_hi = (75 * (second + 60 * minute) + (unsigned int)frame - 150) >> 16;
  opcode = -66;
  lba_mid = (uint16_t)(75 * (second + 60 * minute) + frame - 150) >> 8;
  cdb_byte9 = -8;
  return W9x_exec_scsi_cmd(&opcode, 0xCu, buffer, 2352 * count);
}

static char W9x_read_cd_subchannel(
        uint8_t minute,
        uint8_t second,
        uint8_t frame,
        uint8_t count,
        BYTE *buffer)
{
  char opcode;
  int16_t cdb_byte1;
  char lba_hi;
  char lba_mid;
  int16_t lba_lo;
  char cdb_byte7;
  uint8_t cdb_count;
  char cdb_byte9;
  int16_t cdb_byte10;

  cdb_byte7 = 0;
  lba_lo = (uint8_t)(75 * (second + 60 * minute) + frame + 106);
  cdb_byte1 = 0;
  cdb_count = count;
  lba_hi = (75 * (second + 60 * minute) + (unsigned int)frame - 150) >> 16;
  opcode = -66;
  lba_mid = (uint16_t)(75 * (second + 60 * minute) + frame - 150) >> 8;
  cdb_byte9 = -8;
  cdb_byte10 = 2;
  return W9x_exec_scsi_cmd(&opcode, 0xCu, buffer, 2368 * count);
}

static char W9x_read_cd_subchannel2(
        uint8_t minute,
        uint8_t second,
        uint8_t frame,
        uint8_t count,
        BYTE *buffer)
{
  char opcode;
  int16_t cdb_byte1;
  char lba_hi;
  char lba_mid;
  int16_t lba_lo;
  char cdb_byte7;
  int16_t cdb_count;
  int16_t cdb_byte10;

  cdb_byte7 = 0;
  lba_lo = (uint8_t)(75 * (second + 60 * minute) + frame + 106);
  cdb_count = count;
  lba_hi = (75 * (second + 60 * minute) + (unsigned int)frame - 150) >> 16;
  opcode = -66;
  cdb_byte1 = 4;
  lba_mid = (uint16_t)(75 * (second + 60 * minute) + frame - 150) >> 8;
  cdb_byte10 = 2;
  return W9x_exec_scsi_cmd(&opcode, 0xCu, buffer, 16 * count);
}

static char W9x_seek_cd(int lba)
{
  int16_t opcode;
  char lba_b3;
  char lba_b2;
  char lba_b1;
  char lba_b0;
  int16_t cdb_byte6;
  int16_t cdb_byte8;

  cdb_byte6 = 0;
  cdb_byte8 = 0;
  lba_b3 = HIBYTE(lba);
  lba_b2 = BYTE2(lba);
  opcode = 43;
  lba_b1 = BYTE1(lba);
  lba_b0 = lba;
  return W9x_exec_scsi_cmd(&opcode, 0xAu, nullptr, 0);
}

static char W9x_read_subchannel_status(BYTE *buffer)
{
  uint32_t cdb[2];
  char cdb_extra[4];

  cdb[1] = 0;
  cdb_extra[1] = 0;
  *(uint32_t *)buffer = 0;
  *((uint32_t *)buffer + 1) = 0;
  *((uint32_t *)buffer + 2) = 0;
  *((uint32_t *)buffer + 3) = 0;
  cdb[0] = 20972098;
  cdb_extra[0] = 16;
  return W9x_exec_scsi_cmd(cdb, 0xAu, buffer, 0x10u);
}

char W9x_cdrom_subchannel_read()
{
  char result;
  int step;
  FILE *load_file;
  int lba;
  int seek_seconds;
  int frames;
  uint32_t *q_ptr;
  int fix_offset;
  int fix_seconds;
  int fix_frames;
  uint32_t *fix_ptr;
  FILE *fix_file;
  FILE *fix_file2;
  int precache_offset;
  uint8_t i;
  char *pre_ptr;
  FILE *pre_file;
  FILE *pre_file2;
  int cache_off;
  uint8_t frame;
  int cache_off_tmp;
  uint32_t *src_ptr;
  int sector_count;
  uint32_t *dst_ptr;
  int q_byte;
  bool more_frames;
  FILE *out_file;
  int cache_off2;
  uint8_t j;
  int cache_off_tmp2;
  uint32_t *src_ptr2;
  int sector_count2;
  uint32_t *dst_ptr2;
  int q_dword;
  FILE *m3_file;
  int cache_off3;
  uint8_t k;
  char *cache_ptr3;
  FILE *m4_file;
  int passes;
  uint8_t minute;
  uint8_t minute2;
  uint8_t minute3;
  uint8_t minute4;
  char frame_next;
  uint32_t sub_buf[256];
  char Buffer[1024];
  uint16_t sector_buf[9472];

  result = cd_savefake_flag;
  cached_sector_lba = -1;
  if ( cd_savefake_flag && loaded_file_type != 3 )
  {
    step = 1;
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
      load_file = fopen(Buffer, "rb");
      if ( load_file )
      {
        m3s_q_cache = malloc(0x11940u);
        fread(m3s_q_cache, 1u, 0x11940u, load_file);
        fclose(load_file);
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
      if ( SubchannelW9xCachingLG )
      {
        dbg_print(" * Checking subchannel read standard ... \n");
        m3s_q_cache = malloc(0x11940u);
        passes = 2;
        do
        {
          dbg_print(" * Cdrom precaching subchannel ... (step %d/2) ", step);
          lba = 12600;
          seek_seconds = 70;
          do
          {
            W9x_seek_cd(lba);
            frames = 75;
            do
            {
              W9x_read_subchannel_status((BYTE *)sub_buf);
              if ( BYTE1(sub_buf[2]) % 10 + 16 * (BYTE1(sub_buf[2]) / 10) == 3
                && BYTE2(sub_buf[2]) < 0x3Cu
                && HIBYTE(sub_buf[2]) < 0x4Bu )
              {
                q_ptr = (char *)m3s_q_cache + 1200 * BYTE2(sub_buf[2]) + 16 * HIBYTE(sub_buf[2]);
                *q_ptr = sub_buf[0];
                q_ptr[1] = sub_buf[1];
                q_ptr[2] = sub_buf[2];
                q_ptr[3] = sub_buf[3];
              }
              --frames;
            }
            while ( frames );
            lba += 75;
            --seek_seconds;
          }
          while ( seek_seconds );
          dbg_print("ok\n");
          ++step;
          --passes;
        }
        while ( passes );
        dbg_print(" * Fixating subchanel ... ");
        fix_offset = 0;
        fix_seconds = 60;
        do
        {
          fix_frames = 75;
          do
          {
            fix_ptr = (char *)m3s_q_cache + fix_offset;
            sub_buf[0] = *(uint32_t *)((char *)m3s_q_cache + fix_offset);
            sub_buf[1] = *(uint32_t *)((char *)m3s_q_cache + fix_offset + 4);
            sub_buf[2] = *(uint32_t *)((char *)m3s_q_cache + fix_offset + 8);
            sub_buf[3] = *(uint32_t *)((char *)m3s_q_cache + fix_offset + 12);
            *fix_ptr = 0;
            fix_ptr[1] = 0;
            fix_ptr[2] = 0;
            fix_ptr[3] = 0;
            *((uint8_t *)m3s_q_cache + fix_offset) = 65;
            *(uint16_t *)((char *)m3s_q_cache + fix_offset + 1) = HIWORD(sub_buf[1]);
            fix_offset += 16;
            *((char *)m3s_q_cache + fix_offset - 13) = BYTE1(sub_buf[3]) % 10 + 16 * (BYTE1(sub_buf[3]) / 10);
            *((char *)m3s_q_cache + fix_offset - 12) = BYTE2(sub_buf[3]) % 10 + 16 * (BYTE2(sub_buf[3]) / 10);
            *((char *)m3s_q_cache + fix_offset - 11) = HIBYTE(sub_buf[3]) % 10 + 16 * (HIBYTE(sub_buf[3]) / 10);
            *((char *)m3s_q_cache + fix_offset - 9) = BYTE1(sub_buf[2]) % 10 + 16 * (BYTE1(sub_buf[2]) / 10);
            *((char *)m3s_q_cache + fix_offset - 8) = BYTE2(sub_buf[2]) % 10 + 16 * (BYTE2(sub_buf[2]) / 10);
            --fix_frames;
            *((char *)m3s_q_cache + fix_offset - 7) = HIBYTE(sub_buf[2]) % 10 + 16 * (HIBYTE(sub_buf[2]) / 10);
          }
          while ( fix_frames );
          --fix_seconds;
        }
        while ( fix_seconds );
        cd_read_mode = 6;
        sprintf(Buffer, "%s%s.M3S", "patches\\", default_filename);
        fix_file = fopen(Buffer, "wb");
        fix_file2 = fix_file;
        if ( fix_file )
        {
          fwrite(m3s_q_cache, 1u, 0x11940u, fix_file);
          fclose(fix_file2);
        }
        goto LABEL_36;
      }
      result = SubchannelW9xCdromEnabled;
      if ( !SubchannelW9xCdromEnabled )
        return result;
      dbg_print(" * Checking subchannel read from cdrom ... ");
      if ( cd_read_mode == 7 )
      {
        W9x_read_cd_with_subchannel(0, 2u, 0x10u, 2u, (BYTE *)sector_buf, sub_buf);
        result = HIBYTE(sub_buf[1]);
        if ( HIBYTE(sub_buf[1]) )
          return result;
        result = sub_buf[2];
        if ( LOWORD(sub_buf[2]) != 5634 )
          return result;
        result = HIBYTE(sub_buf[5]);
        if ( *(uint16_t *)((char *)&sub_buf[5] + 3) != 512 || BYTE1(sub_buf[6]) != 23 )
          return result;
        cd_read_mode = 8;
        sector_stride = 2352;
        if ( SubchannelW9xCaching )
        {
          m3s_q_cache = malloc(0x11940u);
          dbg_print(" YES.\n");
          dbg_print(" * Cdrom precaching subchannel ... ");
          minute = 0;
          precache_offset = 0;
          do
          {
            for ( i = 0; i < 0x4Bu; i += 5 )
            {
              W9x_read_cd_with_subchannel(3u, minute, i, 5u, (BYTE *)sector_buf, sub_buf);
              pre_ptr = (char *)m3s_q_cache + precache_offset;
              precache_offset += 80;
              qmemcpy(pre_ptr, sub_buf, 0x50u);
            }
            ++minute;
          }
          while ( minute < 0x3Cu );
          sprintf(Buffer, "%s%s.M3S", "patches\\", default_filename);
          pre_file = fopen(Buffer, "wb");
          pre_file2 = pre_file;
          if ( pre_file )
          {
            fwrite(m3s_q_cache, 1u, 0x11940u, pre_file);
            fclose(pre_file2);
          }
          cd_read_mode = 10;
          goto LABEL_36;
        }
LABEL_101:
        result = dbg_print(" YES.\n");
        BYTE1(cd_speed) = 0;
        return result;
      }
      memset(sector_buf, 0xAAu, 0x1F9Cu);
      W9x_read_cd_subchannel(0, 2u, 0x10u, 2u, (BYTE *)sector_buf);
      if ( !LOBYTE(sector_buf[6]) && *(uint16_t *)((char *)&sector_buf[6] + 1) == 5634 )
      {
        if ( !(HIBYTE(sector_buf[1179]) % 10 + 16 * (HIBYTE(sector_buf[1179]) / 10))
          && LOBYTE(sector_buf[1180]) % 10 + 16 * (LOBYTE(sector_buf[1180]) / 10) == 2
          && HIBYTE(sector_buf[1180]) % 10 + 16 * (HIBYTE(sector_buf[1180]) / 10) == 22
          && !LOBYTE(sector_buf[1190])
          && *(uint16_t *)((char *)&sector_buf[1190] + 1) == 5890
          && !(HIBYTE(sector_buf[2363]) % 10 + 16 * (HIBYTE(sector_buf[2363]) / 10))
          && LOBYTE(sector_buf[2364]) % 10 + 16 * (LOBYTE(sector_buf[2364]) / 10) == 2
          && HIBYTE(sector_buf[2364]) % 10 + 16 * (HIBYTE(sector_buf[2364]) / 10) == 23 )
        {
          cd_read_mode = 2;
          sector_stride = 2368;
          if ( !SubchannelW9xCaching )
            goto LABEL_101;
          m3s_q_cache = malloc(0x11940u);
          dbg_print(" YES.\n");
          dbg_print(" * Cdrom precaching subchannel ... ");
          minute2 = 0;
          cache_off = 0;
          do
          {
            frame = 0;
            frame_next = 0;
            do
            {
              W9x_read_cd_subchannel(3u, minute2, frame, 5u, (BYTE *)sector_buf);
              cache_off_tmp = cache_off;
              src_ptr = &sector_buf[1176];
              sector_count = 5;
              do
              {
                dst_ptr = (char *)m3s_q_cache + cache_off_tmp;
                *dst_ptr = *src_ptr;
                dst_ptr[1] = src_ptr[1];
                dst_ptr[2] = src_ptr[2];
                dst_ptr[3] = src_ptr[3];
                q_byte = *((uint8_t *)m3s_q_cache + cache_off_tmp + 3);
                cache_off_tmp += 16;
                src_ptr += 592;
                *((char *)m3s_q_cache + cache_off_tmp - 13) = q_byte % 10 + 16 * (q_byte / 10);
                *((char *)m3s_q_cache + cache_off_tmp - 12) = (uint8_t)*((char *)m3s_q_cache + cache_off_tmp - 12) % 10
                                                              + 16 * ((uint8_t)*((char *)m3s_q_cache + cache_off_tmp - 12) / 10);
                *((char *)m3s_q_cache + cache_off_tmp - 11) = (uint8_t)*((char *)m3s_q_cache + cache_off_tmp - 11) % 10
                                                              + 16 * ((uint8_t)*((char *)m3s_q_cache + cache_off_tmp - 11) / 10);
                *((char *)m3s_q_cache + cache_off_tmp - 9) = (uint8_t)*((char *)m3s_q_cache + cache_off_tmp - 9) % 10
                                                             + 16 * ((uint8_t)*((char *)m3s_q_cache + cache_off_tmp - 9) / 10);
                *((char *)m3s_q_cache + cache_off_tmp - 8) = (uint8_t)*((char *)m3s_q_cache + cache_off_tmp - 8) % 10
                                                             + 16 * ((uint8_t)*((char *)m3s_q_cache + cache_off_tmp - 8) / 10);
                --sector_count;
                *((char *)m3s_q_cache + cache_off_tmp - 7) = (uint8_t)*((char *)m3s_q_cache + cache_off_tmp - 7) % 10
                                                             + 16 * ((uint8_t)*((char *)m3s_q_cache + cache_off_tmp - 7) / 10);
              }
              while ( sector_count );
              frame = frame_next + 5;
              more_frames = (uint8_t)(frame_next + 5) < 0x4Bu;
              frame_next += 5;
              cache_off = cache_off_tmp;
            }
            while ( more_frames );
            ++minute2;
          }
          while ( minute2 < 0x3Cu );
          sprintf(Buffer, "%s%s.M3S", "patches\\", default_filename);
          out_file = fopen(Buffer, "wb");
          if ( !out_file )
            goto LABEL_88;
          fwrite(m3s_q_cache, 1u, 0x11940u, out_file);
          goto LABEL_87;
        }
        if ( !HIBYTE(sector_buf[1179])
          && sector_buf[1180] == 5634
          && !LOBYTE(sector_buf[1190])
          && HIBYTE(sector_buf[1190]) == LOBYTE(sector_buf[1180])
          && LOBYTE(sector_buf[1191]) == 23
          && !HIBYTE(sector_buf[2363])
          && LOBYTE(sector_buf[2364]) == LOBYTE(sector_buf[1180])
          && HIBYTE(sector_buf[2364]) == 23 )
        {
          cd_read_mode = 3;
          sector_stride = 2368;
          if ( !SubchannelW9xCaching )
            goto LABEL_101;
          m3s_q_cache = malloc(0x11940u);
          dbg_print(" YES.\n");
          dbg_print(" * Cdrom precaching subchannel ... ");
          minute3 = 0;
          cache_off2 = 0;
          do
          {
            for ( j = 0; j < 0x4Bu; j += 5 )
            {
              W9x_read_cd_subchannel(3u, minute3, j, 5u, (BYTE *)sector_buf);
              cache_off_tmp2 = cache_off2;
              src_ptr2 = &sector_buf[1176];
              sector_count2 = 5;
              do
              {
                dst_ptr2 = (char *)m3s_q_cache + cache_off_tmp2;
                *dst_ptr2 = *src_ptr2;
                dst_ptr2[1] = src_ptr2[1];
                dst_ptr2[2] = src_ptr2[2];
                q_dword = src_ptr2[3];
                cache_off_tmp2 += 16;
                src_ptr2 += 592;
                --sector_count2;
                dst_ptr2[3] = q_dword;
              }
              while ( sector_count2 );
              cache_off2 = cache_off_tmp2;
            }
            ++minute3;
          }
          while ( minute3 < 0x3Cu );
          sprintf(Buffer, "%s%s.M3S", "patches\\", default_filename);
          m3_file = fopen(Buffer, "wb");
          out_file = m3_file;
          if ( !m3_file )
            goto LABEL_88;
          fwrite(m3s_q_cache, 1u, 0x11940u, m3_file);
LABEL_87:
          fclose(out_file);
LABEL_88:
          sector_stride = 2352;
          goto LABEL_100;
        }
      }
      memset(sector_buf, 0xAAu, 0x1F9Cu);
      W9x_read_cd_subchannel2(0, 2u, 0x10u, 2u, (BYTE *)sector_buf);
      if ( *(uint16_t *)((char *)&sector_buf[3] + 1) != 512
        || HIBYTE(sector_buf[4]) != 22
        || *(uint16_t *)((char *)&sector_buf[11] + 1) != 512
        || HIBYTE(sector_buf[12]) != 23 )
      {
        return dbg_print(" NO.\n");
      }
      cd_read_mode = 4;
      sector_stride = 2352;
      m3s_q_cache = malloc(0x11940u);
      if ( !SubchannelW9xCaching )
        goto LABEL_101;
      m3s_q_cache = malloc(0x11940u);
      dbg_print(" YES.\n");
      dbg_print(" * Cdrom precaching subchannel ... ");
      minute4 = 0;
      cache_off3 = 0;
      do
      {
        for ( k = 0; k < 0x4Bu; k += 15 )
        {
          W9x_read_cd_subchannel2(3u, minute4, k, 0xFu, (BYTE *)sector_buf);
          cache_ptr3 = (char *)m3s_q_cache + cache_off3;
          cache_off3 += 240;
          qmemcpy(cache_ptr3, sector_buf, 0xF0u);
        }
        ++minute4;
      }
      while ( minute4 < 0x3Cu );
      sprintf(Buffer, "%s%s.M3S", "patches\\", default_filename);
      m4_file = fopen(Buffer, "wb");
      if ( m4_file )
      {
        fwrite(m3s_q_cache, 1u, 0x11940u, m4_file);
        fclose(m4_file);
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

int W9x_cdrom_read_data(uint8_t minute, uint8_t second, uint8_t frame, char *Buffer)
{
  uint8_t minute_copy;
  uint8_t second_copy;
  int frame_copy;
  int patch_lba;
  char *dst;
  unsigned int cache_index;
  int *q_ptr;
  int *sub_ptr;
  int sub_q1;
  int sub_q2;
  int64_t bcd_tmp;
  int64_t bcd_tmp2;
  int64_t bcd_tmp3;
  int64_t bcd_tmp4;
  int *sub_ptr2;
  int sub_q3;
  int sub_q4;
  int sub_q5;
  int *blk_ptr;
  int sub_q6;
  int sub_q7;
  int sub_q8;
  int cur3;
  int *q_ptr2;
  int *blk_ptr2;
  char *src_ptr;
  int *q_ptr3;
  int *blk_ptr3;
  char *src_ptr2;
  int patch_lba2;
  int sector_count;
  int sector_count2;
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
        if ( w9x_cdda_resume_pending )
        {
          W9x_resume_cdda();
          minute_copy = minute;
          w9x_cdda_resume_pending = 0;
        }
        switch ( cd_read_mode )
        {
          case 1:
            if ( W9x_read_cd_data_only(minute_copy, second, frame, 8u, (BYTE *)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", minute, second, frame_copy);
            cur3 = 0;
            sub_q_cur0 = 0;
            sub_q_cur1 = 0;
            sub_q_cur2 = 0;
            goto LABEL_65;
          case 2:
            if ( W9x_read_cd_subchannel(minute_copy, second, frame, 8u, (BYTE *)cd_sector_cache) )
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
            if ( W9x_read_cd_subchannel(minute_copy, second, frame, 8u, (BYTE *)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", minute, second, frame_copy);
            sub_q_cur0 = *(uint32_t *)sub_q_cache;
            sub_q_cur1 = sub_q_sec_frame;
            sub_q_cur2 = sub_q_asec_aframe;
            sub_q_cur3 = sub_q_rest[0];
            goto LABEL_66;
          case 4:
            if ( W9x_read_cd_data_only(minute_copy, second, frame, 8u, (BYTE *)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", minute, second, frame_copy);
            memset(sub_q_block_cache, 0, 0x80u);
            if ( minute == 3
              && (cop0_bpc_value[0] & 0x1F000000) == 0x1F000000
              && W9x_read_cd_subchannel2(3u, second, frame, 8u, (BYTE *)sub_q_block_cache) )
            {
              dbg_print(" * Error sub reading CD: %d,%d,%d\n", 3, second, frame_copy);
            }
            goto LABEL_64;
          case 5:
            fseek(Stream, 96 * lba, 0);
            fread(cd_sector_cache, 1u, 0x300u, Stream);
            blk_ptr2 = sub_q_block_cache;
            src_ptr = cd_sector_cache_cont;
            sector_count = 8;
            do
            {
              *blk_ptr2 = *(uint32_t *)src_ptr;
              blk_ptr2[1] = *((uint32_t *)src_ptr + 1);
              blk_ptr2[2] = *((uint32_t *)src_ptr + 2);
              blk_ptr2[3] = *((uint32_t *)src_ptr + 3);
              src_ptr += 96;
              blk_ptr2 += 4;
              --sector_count;
            }
            while ( sector_count );
            second_copy = second;
            if ( !W9x_read_cd_data_only(minute, second, frame, 8u, (BYTE *)cd_sector_cache) )
              goto LABEL_56;
            dbg_print(" * Error reading CD: %d,%d,%d\n", minute, second, frame_copy);
            sub_q_cur0 = sub_q_block_cache[0];
            sub_q_cur1 = sub_q_block_cache1;
            sub_q_cur2 = sub_q_block_cache2;
            sub_q_cur3 = sub_q_block_cache3[0];
            goto LABEL_66;
          case 6:
            if ( W9x_read_cd_data_only(minute_copy, second, frame, 8u, (BYTE *)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", minute, second, frame_copy);
            if ( minute != 3 )
              goto LABEL_46;
            q_ptr2 = (int *)((char *)m3s_q_cache + 1200 * second + 16 * frame_copy);
            sub_q_cur0 = *q_ptr2;
            sub_q_cur1 = q_ptr2[1];
            sub_q_cur2 = q_ptr2[2];
            sub_q_cur3 = q_ptr2[3];
            goto LABEL_66;
          case 7:
            if ( W9x_read_cd_sectors(minute_copy, second, frame, 8u, (BYTE *)cd_sector_cache) )
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
              if ( W9x_read_cd_with_subchannel(3u, second, frame, 8u, (BYTE *)cd_sector_cache, sub_q_block_cache) )
                dbg_print(" * Error sub reading CD: %d,%d,%d\n", 3, second, frame_copy);
              minute_copy = minute;
            }
            if ( W9x_read_cd_sectors(minute_copy, second, frame, 8u, (BYTE *)cd_sector_cache) )
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
            blk_ptr3 = sub_q_block_cache;
            src_ptr2 = cd_sector_cache_cont;
            sector_count2 = 8;
            do
            {
              *blk_ptr3 = *(uint32_t *)src_ptr2;
              blk_ptr3[1] = *((uint32_t *)src_ptr2 + 1);
              blk_ptr3[2] = *((uint32_t *)src_ptr2 + 2);
              blk_ptr3[3] = *((uint32_t *)src_ptr2 + 3);
              src_ptr2 += 96;
              blk_ptr3 += 4;
              --sector_count2;
            }
            while ( sector_count2 );
            second_copy = second;
            if ( W9x_read_cd_sectors(minute, second, frame, 8u, (BYTE *)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", minute, second, frame_copy);
LABEL_56:
            sub_q_cur0 = sub_q_block_cache[0];
            sub_q_cur1 = sub_q_block_cache1;
            sub_q_cur2 = sub_q_block_cache2;
            sub_q_cur3 = sub_q_block_cache3[0];
            goto LABEL_66;
          case 10:
            if ( W9x_read_cd_sectors(minute_copy, second, frame, 8u, (BYTE *)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", minute, second, frame_copy);
            if ( minute == 3 )
            {
              q_ptr3 = (int *)((char *)m3s_q_cache + 1200 * second + 16 * frame_copy);
              sub_q_cur0 = *q_ptr3;
              sub_q_cur1 = q_ptr3[1];
              sub_q_cur2 = q_ptr3[2];
              cur3 = q_ptr3[3];
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
        cache_index = lba - cached_sector_lba;
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
            sub_ptr = (int *)&sub_q_cache[cache_index * sector_stride];
            sub_q1 = sub_ptr[1];
            sub_q2 = sub_ptr[2];
            sub_q_cur0 = *sub_ptr;
            sub_q_cur3 = sub_ptr[3];
            sub_q_cur1 = sub_q1;
            sub_q_cur2 = sub_q2;
            HIBYTE(sub_q_cur0) = HIBYTE(sub_q_cur0) % 10 + 16 * (HIBYTE(sub_q_cur0) / 10);
            LOBYTE(sub_q_cur1) = (uint8_t)sub_q1 % 10 + 16 * ((uint8_t)sub_q1 / 10);
            bcd_tmp = (uint8_t)(16 * (BYTE1(sub_q1) / 10));
            BYTE1(sub_q_cur1) = BYTE4(bcd_tmp) + bcd_tmp;
            bcd_tmp2 = (uint8_t)(16 * (HIBYTE(sub_q1) / 10));
            HIBYTE(sub_q_cur1) = BYTE4(bcd_tmp2) + bcd_tmp2;
            bcd_tmp3 = (uint8_t)(16 * ((uint8_t)sub_q2 / 10));
            LOBYTE(sub_q_cur2) = BYTE4(bcd_tmp3) + bcd_tmp3;
            bcd_tmp4 = (uint8_t)(16 * (BYTE1(sub_q2) / 10));
            BYTE1(sub_q_cur2) = BYTE4(bcd_tmp4) + bcd_tmp4;
            break;
          case 3:
            sub_ptr2 = (int *)&sub_q_cache[cache_index * sector_stride];
            sub_q3 = sub_ptr2[1];
            sub_q_cur0 = *sub_ptr2;
            sub_q4 = sub_ptr2[2];
            sub_q_cur1 = sub_q3;
            sub_q5 = sub_ptr2[3];
            sub_q_cur2 = sub_q4;
            sub_q_cur3 = sub_q5;
            break;
          case 4:
          case 5:
          case 8:
          case 9:
            blk_ptr = &sub_q_block_cache[4 * cache_index];
            sub_q6 = blk_ptr[1];
            sub_q_cur0 = *blk_ptr;
            sub_q7 = blk_ptr[2];
            sub_q8 = blk_ptr[3];
            sub_q_cur1 = sub_q6;
            sub_q_cur2 = sub_q7;
            sub_q_cur3 = sub_q8;
            break;
          case 6:
          case 10:
            if ( minute == 3 )
            {
              q_ptr = (int *)((char *)m3s_q_cache + 1200 * second + 16 * frame_copy);
              sub_q_cur0 = *q_ptr;
              sub_q_cur1 = q_ptr[1];
              sub_q_cur2 = q_ptr[2];
              sub_q_cur3 = q_ptr[3];
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

static char W9x_find_track_by_msf(unsigned int msf, char second)
{
  char target_minute;
  uint8_t track;

  track = 0;
  if ( !(uint8_t)w9x_cdrom_info )
    return 0;
  target_minute = msf;
  while ( 1 )
  {
    W9x_bcd_to_dword(&msf, (uint8_t *)(8 * track + 5262504));
    msf += 150;
    if ( (uint8_t)(msf / 0x4B / 0x3C) == target_minute && msf / 0x4B % 0x3C == second )
      break;
    if ( ++track >= (uint8_t)w9x_cdrom_info )
      return 0;
  }
  return msf % 0x4B;
}

char W9x_play_cdda(unsigned int minute, int second, uint8_t track)
{
  char result;
  uint8_t end_second;
  HANDLE EventA;
  uint32_t srb[20];

  result = sound_use_cdda;
  if ( sound_use_cdda )
  {
    end_second = second;
    track = W9x_find_track_by_msf(minute, second);
    BYTE1(w9x_play_cdb2) = track;
    HIBYTE(w9x_play_cdb) = minute;
    LOBYTE(w9x_play_cdb2) = end_second;
    W9x_bcd_to_dword(&second, (uint8_t *)(8 * (uint8_t)w9x_cdrom_info + 5262504));
    LOBYTE(w9x_play_cdb3) = (second + 150) % 0x4Bu;
    BYTE2(w9x_play_cdb2) = (second + 150) / 0x4Bu / 0x3C;
    HIBYTE(w9x_play_cdb2) = (second + 150) / 0x4Bu % 0x3C;
    EventA = CreateEventA(nullptr, 1, 0, nullptr);
    memset(srb, 0, sizeof(srb));
    BYTE2(srb[0]) = cdrom_haid;
    LOBYTE(srb[2]) = cdrom_target;
    BYTE1(srb[2]) = cdrom_lun;
    LOBYTE(srb[0]) = 2;
    HIBYTE(srb[0]) = 72;
    LOWORD(srb[5]) = 2574;
    srb[3] = 0;
    srb[4] = 0;
    srb[6] = EventA;
    srb[12] = w9x_play_cdb;
    srb[13] = w9x_play_cdb2;
    LOWORD(srb[14]) = w9x_play_cdb3;
    ResetEvent(EventA);
    if ( !SendASPI32Command_cb(srb) )
      WaitForSingleObject(EventA, 0xFFFFFFFF);
    result = CloseHandle(EventA);
    if ( BYTE1(srb[0]) == 1 )
      w9x_cdda_playing = 1;
    else
      return printf(" * Play cdda error (%d, %d, %d) \n", (uint8_t)minute, end_second, track);
  }
  return result;
}

char W9x_cdrom_stop()
{
  char result;
  HANDLE EventA;
  uint32_t srb[20];

  BYTE1(w9x_stop_cdb) = (32 * cdrom_lun) | 1;
  result = sound_use_cdda;
  if ( sound_use_cdda )
  {
    result = w9x_cdda_playing;
    if ( w9x_cdda_playing )
    {
      w9x_cdda_playing = 0;
      EventA = CreateEventA(nullptr, 1, 0, nullptr);
      memset(srb, 0, sizeof(srb));
      BYTE2(srb[0]) = cdrom_haid;
      LOBYTE(srb[2]) = cdrom_target;
      BYTE1(srb[2]) = cdrom_lun;
      LOBYTE(srb[0]) = 2;
      HIBYTE(srb[0]) = 80;
      LOWORD(srb[5]) = 2574;
      srb[3] = 0;
      srb[4] = 0;
      srb[6] = EventA;
      srb[12] = w9x_stop_cdb;
      srb[13] = w9x_stop_cdb2;
      LOWORD(srb[14]) = w9x_stop_cdb3;
      ResetEvent(EventA);
      if ( !SendASPI32Command_cb(srb) )
        WaitForSingleObject(EventA, 0xFFFFFFFF);
      if ( BYTE1(srb[0]) != 1 )
        printf(" * Stop cdrom error. \n");
      result = CloseHandle(EventA);
      w9x_cdda_resume_pending = 1;
    }
  }
  return result;
}

static BOOL W9x_resume_cdda()
{
  HANDLE EventA;
  uint32_t srb[20];

  BYTE1(w9x_resume_cdb) = (32 * cdrom_lun) | 1;
  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(srb, 0, sizeof(srb));
  BYTE2(srb[0]) = cdrom_haid;
  LOBYTE(srb[2]) = cdrom_target;
  BYTE1(srb[2]) = cdrom_lun;
  LOBYTE(srb[0]) = 2;
  HIBYTE(srb[0]) = 80;
  LOWORD(srb[5]) = 2574;
  srb[3] = 0;
  srb[4] = 0;
  srb[6] = EventA;
  srb[12] = w9x_resume_cdb;
  srb[13] = w9x_resume_cdb2;
  LOWORD(srb[14]) = w9x_resume_cdb3;
  ResetEvent(EventA);
  if ( !SendASPI32Command_cb(srb) )
    WaitForSingleObject(EventA, 0xFFFFFFFF);
  if ( BYTE1(srb[0]) != 1 )
    printf(" * Resume cdrom error. \n");
  return CloseHandle(EventA);
}

void W9x_reset_cdrom_state()
{
  w9x_cdda_playing = 0;
  cached_sector_lba = -1;
  cdr_spinup_motor();
}

static char W9x_msf_to_lba(
        unsigned int minute,
        uint8_t second,
        uint8_t frame,
        uint8_t *track_out,
        uint8_t *minute_out,
        uint8_t *second_out,
        uint8_t *frame_out)
{
  char num_tracks;
  int track_total;
  unsigned int lba;
  char result;
  unsigned int delta;
  uint8_t track;

  track = 0;
  num_tracks = w9x_cdrom_info;
  track_total = (uint8_t)w9x_cdrom_info;
  lba = (frame & 0xF) % 10
      + 75
      * ((second & 0xF) % 10 + 10 * ((second >> 4) + 6 * ((uint8_t)(minute & 0xF) % 10 + 10 * ((uint8_t)minute >> 4))))
      + 10 * (frame >> 4)
      - 150;
  W9x_bcd_to_dword(&minute, (uint8_t *)(8 * (uint8_t)w9x_cdrom_info + 5262504));
  result = minute;
  if ( minute > lba )
  {
    if ( num_tracks )
    {
      while ( 1 )
      {
        W9x_bcd_to_dword(&minute, (uint8_t *)(8 * track + 5262512));
        if ( track + 1 < track_total )
          minute -= minute % 0x4B;
        if ( minute > lba )
          break;
        if ( ++track >= (uint8_t)w9x_cdrom_info )
          goto LABEL_8;
      }
      W9x_bcd_to_dword(&minute, (uint8_t *)(8 * track + 5262504));
      delta = lba + minute % 0x4B - minute;
      *track_out = (track + 1) % 10 + 16 * ((track + 1) / 10);
      *minute_out = delta / 0x4B / 0x3C % 0xA + 16 * (delta / 0x4B / 0x3C / 0xA);
      *second_out = delta / 0x4B % 0x3C % 0xA + 16 * (delta / 0x4B % 0x3C / 0xA);
      result = delta % 0x4B % 0xA + 16 * (delta % 0x4B / 0xA);
      *frame_out = result;
    }
    else
    {
LABEL_8:
      result = (char)track_out;
      *track_out = -86;
    }
  }
  else
  {
    *track_out = -86;
  }
  return result;
}

uint8_t W9x_get_track_start_lba(
        uint8_t minute,
        uint8_t second,
        uint8_t frame,
        uint8_t *minute_out,
        uint8_t *second_out,
        uint8_t *frame_out)
{
  uint8_t track;
  unsigned int msf;
  uint8_t result;
  unsigned int lba;
  unsigned int second_val;
  unsigned int frame_val;
  int track_idx;

  track = 0;
  LOBYTE(track_idx) = 0;
  msf = (frame & 0xF) % 10
      + 75 * ((second & 0xF) % 10 + 10 * ((second >> 4) + 6 * ((minute & 0xF) % 10 + 10 * (minute >> 4))))
      + 10 * (frame >> 4);
  W9x_bcd_to_dword(&lba, (uint8_t *)(8 * (uint8_t)w9x_cdrom_info + 5262504));
  if ( lba > msf )
  {
    result = w9x_cdrom_info;
    if ( (uint8_t)w9x_cdrom_info )
    {
      while ( 1 )
      {
        W9x_bcd_to_dword(&lba, (uint8_t *)(8 * (uint8_t)track_idx + 5262512));
        if ( lba > msf )
          break;
        result = w9x_cdrom_info;
        LOBYTE(track_idx) = ++track;
        if ( track >= (uint8_t)w9x_cdrom_info )
          return result;
      }
      frame_val = lba % 0x4B;
      second_val = lba / 0x4B % 0x3C;
      *minute_out = lba / 0x4B / 0x3C;
      *second_out = second_val;
      *frame_out = frame_val;
      return (uint8_t)second_out;
    }
  }
  else
  {
    *minute_out = minute;
    *second_out = second;
    *frame_out = frame;
    return second;
  }
  return result;
}

char W9x_verify_subchannel_data(unsigned int minute, uint8_t second, uint8_t frame, int buffer)
{
  char bcd_minute;
  char errors2;
  char result;
  char errors;
  uint8_t bcd_second;
  uint8_t bcd_second2;
  uint8_t prev_frame;
  char bcd_frame;
  uint8_t bcd_frame2;

  *(uint32_t *)buffer = 0;
  *(uint32_t *)(buffer + 4) = 0;
  errors = 0;
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
    bcd_minute = (uint8_t)minute % 10 + 16 * ((uint8_t)minute / 10);
    bcd_second = second % 10 + 16 * (second / 10);
    bcd_frame = prev_frame % 10 + 16 * (prev_frame / 10);
    *(uint32_t *)buffer = *(int *)((char *)&sub_q_cur0 + 1);
    *(uint8_t *)(buffer + 4) = BYTE1(sub_q_cur1);
    *(uint16_t *)(buffer + 5) = *(uint16_t *)((char *)&sub_q_cur1 + 3);
    *(uint8_t *)(buffer + 7) = BYTE1(sub_q_cur2);
    if ( bcd_minute != *(uint8_t *)(buffer + 5) )
      errors = 1;
    if ( bcd_minute != *(uint8_t *)(buffer + 2) )
      ++errors;
    if ( bcd_second != *(uint8_t *)(buffer + 6) )
      ++errors;
    errors2 = errors;
    if ( ((bcd_second & 0xF) % 10 + 10 * (bcd_second >> 4) - 2) % 10 + 16 * (((bcd_second & 0xF) % 10 + 10 * (bcd_second >> 4) - 2) / 10) != *(uint8_t *)(buffer + 3) )
      errors2 = errors + 1;
    result = bcd_frame;
    if ( bcd_frame != *(uint8_t *)(buffer + 7) )
      ++errors2;
    if ( bcd_frame != *(uint8_t *)(buffer + 4) )
      ++errors2;
    if ( (uint8_t)errors2 >= 2u )
    {
      result = 0;
      *(uint32_t *)(buffer + 2) = 0;
      *(uint16_t *)(buffer + 6) = 0;
      if ( bcd_minute == 3 )
        xenogears_cd_detected = 1;
    }
  }
  else
  {
    LOBYTE(minute) = (uint8_t)minute % 10 + 16 * ((uint8_t)minute / 10);
    bcd_second2 = second % 10 + 16 * (second / 10);
    bcd_frame2 = frame % 10 + 16 * (frame / 10);
    W9x_msf_to_lba(minute, bcd_second2, bcd_frame2, (uint8_t *)buffer, (uint8_t *)(buffer + 2), (uint8_t *)(buffer + 3), (uint8_t *)(buffer + 4));
    *(uint8_t *)(buffer + 1) = 1;
    *(uint8_t *)(buffer + 5) = minute;
    *(uint8_t *)(buffer + 6) = bcd_second2;
    *(uint8_t *)(buffer + 7) = bcd_frame2;
    return bcd_frame2;
  }
  return result;
}




/* Decompiled globals (previously generated in src/_gen) */
DWORD (__stdcall *GetASPI32SupportInfo_cb)(void);
int ( *SendASPI32Command_cb)(LPSRB);
unsigned char SubchannelW9xCaching;
unsigned char w9x_toc_buffer;
unsigned char w9x_toc_first_track;
unsigned char w9x_toc_last_track;
unsigned char w9x_toc_track_control[1];
unsigned char w9x_toc_track_entries[0x33a];
unsigned char cd_device_reserved0[1];
unsigned char cd_device_product[0x10];
unsigned char cd_device_reserved1[1];
unsigned char cd_device_reserved2[1];
unsigned char cd_device_extra[0x14];
unsigned char cd_device_reserved3[1];
unsigned int cdrom_haid = 0xffffffff;
unsigned int cdrom_lun = 0xffffffff;
unsigned int cdrom_target = 0xffffffff;
unsigned int w9x_play_cdb = 0x47;
unsigned int w9x_play_cdb2 = 0x0;
unsigned int w9x_stop_cdb = 0x4b;
unsigned int w9x_stop_cdb2 = 0x0;
unsigned int w9x_resume_cdb = 0x4b;
unsigned int w9x_resume_cdb2 = 0x0;
unsigned int w9x_cdrom_info;
unsigned int w9x_cdda_playing;
unsigned int w9x_cdda_resume_pending;
unsigned int cached_sector_lba;
unsigned int cd_device_vendor;
unsigned int cd_device_vendor2;
unsigned int cd_device_revision;
unsigned int cd_device_haid;
unsigned int cd_device_target;
unsigned int cd_device_lun[0xf1];
unsigned short w9x_play_cdb3 = 0x0;
unsigned short w9x_stop_cdb3 = 0x0;
unsigned short w9x_resume_cdb3 = 0x1;
