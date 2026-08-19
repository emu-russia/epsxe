#include "pch.h"

/* static prototypes for internal functions */
static int W9x_disable_subchannel_mode();
static char W9x_read_cd_sectors(
        uint8_t a1,
        uint8_t a2,
        uint8_t a3,
        uint8_t a4,
        BYTE *a5);
static char W9x_read_cd_data_only(
        uint8_t a1,
        uint8_t a2,
        uint8_t a3,
        uint8_t a4,
        BYTE *a5);
static BOOL W9x_resume_cdda();

/* ASPI support: wnaspi32.lib is not shipped with modern SDKs, so load the
 * function from the system DLL at runtime. */
static DWORD GetASPI32SupportInfo(void)
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

static char W9x_exec_scsi_cmd(const void *a1, unsigned int a2, BYTE *a3, DWORD a4)
{
  HANDLE EventA;
  SRB_ExecSCSICmd v6;

  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(&v6, 0, sizeof(v6));
  v6.SRB_Target = cdrom_target;
  v6.SRB_BufPointer = a3;
  v6.SRB_CDBLen = a2;
  v6.SRB_Lun = cdrom_lun;
  v6.SRB_HaId = cdrom_haid;
  v6.SRB_Cmd = 2;
  v6.SRB_Flags = 72;
  v6.SRB_BufLen = a4;
  v6.SRB_SenseLen = 14;
  v6.SRB_PostProc = EventA;
  qmemcpy(v6.CDBByte, a1, a2);
  ResetEvent(EventA);
  if ( !SendASPI32Command_cb(&v6) )
    WaitForSingleObject(EventA, 0xFFFFFFFF);
  if ( v6.SRB_Status != 1 )
    return 1;
  CloseHandle(EventA);
  return 0;
}

static int W9x_add_cdrom_device_info(BYTE a1, BYTE a2, BYTE a3)
{
  HANDLE EventA;
  int result;
  char v5;
  int v6;
  char *v7;
  int v8;
  SRB_ExecSCSICmd v9;
  uint32_t v10[25];

  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(&v9, 0, sizeof(v9));
  memset(v10, 0, sizeof(v10));
  v9.SRB_Target = a2;
  v9.SRB_Cmd = 2;
  v9.SRB_HaId = a1;
  v9.SRB_Lun = a3;
  v9.SRB_Flags = 72;
  v9.SRB_BufLen = 100;
  v9.SRB_BufPointer = (BYTE *)v10;
  v9.SRB_SenseLen = 14;
  v9.SRB_CDBLen = 6;
  v9.SRB_PostProc = EventA;
  v9.CDBByte[0] = 18;
  v9.CDBByte[4] = 100;
  ResetEvent(EventA);
  if ( !SendASPI32Command_cb(&v9) )
    WaitForSingleObject(EventA, 0xFFFFFFFF);
  result = CloseHandle(EventA);
  if ( v9.SRB_Status == 1 )
  {
    v5 = HIBYTE(w9x_cdrom_info);
    v6 = v10[4];
    result = HIBYTE(w9x_cdrom_info) << 6;
    *(int *)((char *)&cd_device_vendor + result) = v10[2];
    *(int *)((char *)&cd_device_vendor2 + result) = v10[3];
    cd_device_reserved0[result] = 0;
    v7 = &cd_device_product[result];
    *(uint32_t *)v7 = v6;
    *((uint32_t *)v7 + 1) = v10[5];
    *((uint32_t *)v7 + 2) = v10[6];
    *((uint32_t *)v7 + 3) = v10[7];
    v8 = v10[8];
    cd_device_reserved1[result] = 0;
    *(int *)((char *)&cd_device_revision + result) = v8;
    cd_device_reserved2[result] = 0;
    qmemcpy(&cd_device_extra[result], &v10[9], 0x14u);
    cd_device_reserved3[result] = 0;
    *(int *)((char *)&cd_device_haid + result) = a1;
    *(int *)((char *)&cd_device_target + result) = a2;
    *(int *)((char *)cd_device_lun + result) = a3;
    HIBYTE(w9x_cdrom_info) = v5 + 1;
  }
  return result;
}

char W9x_init_aspi()
{
  char result;
  int16_t ASPI32SupportInfo;
  BYTE v2;
  char v3;
  uint8_t v4;
  BYTE v5;
  BYTE i;
  BYTE v7;
  uint32_t v8[2];
  BYTE v9;
  uint8_t v10;
  int16_t v11;
  uint8_t v12[60];

  result = HIBYTE(w9x_cdrom_info);
  if ( !HIBYTE(w9x_cdrom_info) )
  {
    ASPI32SupportInfo = GetASPI32SupportInfo();
    BYTE1(w9x_cdrom_info) = ASPI32SupportInfo;
    if ( HIBYTE(ASPI32SupportInfo) != 1 && HIBYTE(ASPI32SupportInfo) != 0xE8 )
      fatal_error_with_message_box(" * Error in init aspi (%d)\n", HIBYTE(ASPI32SupportInfo));
    result = BYTE1(w9x_cdrom_info);
    v2 = 0;
    for ( i = 0; v2 < BYTE1(w9x_cdrom_info); i = v2 )
    {
      memset(v12, 0, sizeof(v12));
      v12[0] = 0;
      v12[2] = v2;
      SendASPI32Command_cb(v12);
      if ( v12[1] == 1 )
      {
        v3 = v12[45];
        BYTE2(w9x_cdrom_info) = v12[45];
        if ( !v12[45] )
        {
          v3 = 8;
          BYTE2(w9x_cdrom_info) = 8;
        }
        v5 = 0;
        if ( v3 )
        {
          do
          {
            v4 = 0;
            v7 = 0;
            do
            {
              v8[0] = 1;
              v8[1] = 0;
              v11 = 0;
              BYTE2(v8[0]) = i;
              v9 = v5;
              v10 = v4;
              SendASPI32Command_cb(v8);
              if ( BYTE1(v8[0]) == 1 && (uint8_t)v11 == 5 )
                W9x_add_cdrom_device_info(i, v5, v7);
              v7 = ++v4;
            }
            while ( v4 < 8u );
            ++v5;
          }
          while ( v5 < BYTE2(w9x_cdrom_info) );
          v2 = i;
        }
      }
      result = BYTE1(w9x_cdrom_info);
      ++v2;
    }
  }
  return result;
}

uint32_t * W9x_bcd_to_dword(uint32_t *a1, uint8_t *a2)
{
  *a1 = a2[3] + ((a2[2] + ((a2[1] + (*a2 << 8)) << 8)) << 8);
  return a1;
}

static uint32_t *W9x_cdrom_gettrackinfo()
{
  char v0;
  bool v1;
  uint8_t v3;
  int v4;
  unsigned int v5;
  int v6;
  int v7;
  int v8;
  uint32_t v9[3];

  v9[0] = 0x43;
  v9[1] = 0x3000000;
  v9[2] = 0x24;
  v0 = 10;
  v1 = 1;
  while ( v1 )
  {
    memset(w9x_toc_buffer, 0, 0x324u);
    v1 = W9x_exec_scsi_cmd(v9, 0xAu, w9x_toc_buffer, 0x324u) != 0;
    if ( !++v0 )
    {
      if ( v1 )
        return (uint32_t *)dbg_print(" * Cdrom gettrackinfo error.\n");
      break;
    }
  }
  dbg_print(" * First/Last track: %d %d\n", (uint8_t)w9x_toc_first_track, (uint8_t)w9x_toc_last_track);
  v3 = 0;
  LOBYTE(v7) = w9x_toc_last_track - w9x_toc_first_track + 1;
  LOBYTE(w9x_cdrom_info) = v7;
  LOBYTE(v6) = 0;
  if ( w9x_toc_last_track - w9x_toc_first_track != 0xFF )
  {
    do
    {
      v4 = (uint8_t)v6;
      dbg_print(" * Track %d: ", (uint8_t)w9x_toc_track_entries[8 * (uint8_t)v6]);
      if ( (w9x_toc_track_control[8 * v4] & 4) != 0 )
      {
        dbg_print("(DATA)  -");
      }
      else
      {
        dbg_print("(AUDIO) -");
        if ( !v3 )
          nocd = 2;
      }
      W9x_bcd_to_dword(&v5, (uint8_t *)(8 * v4 + 5262504));
      v5 += 150;
      dbg_print(" Start %d: (%02d,%02d,%02d) - ", v4, (uint8_t)(v5 / 0x4B / 0x3C), v5 / 0x4B % 0x3C, v5 % 0x4B);
      W9x_bcd_to_dword(&v5, (uint8_t *)(8 * v4 + 5262504));
      W9x_bcd_to_dword(&v8, (uint8_t *)(8 * v4 + 5262512));
      dbg_print(" Length %02d:%02d\n", (v8 - v5) / 0x4B / 0x3C, (v8 - v5) / 0x4B % 0x3C);
      LOBYTE(v6) = ++v3;
    }
    while ( v3 < (uint8_t)v7 );
  }
  return W9x_bcd_to_dword(&v8, (uint8_t *)(8 * (uint8_t)v7 + 5262504));
}

int ( *W9x_load_winaspi_dll())(LPSRB)
{
  HMODULE LibraryA;
  int ( *result)(LPSRB);

  LibraryA = LoadLibraryA("WNASPI32.DLL");
  hCdrModule = LibraryA;
  if ( !LibraryA )
    fatal_error_with_message_box(" * Error loading WNASPI32.DLL\n");
  GetASPI32SupportInfo_cb = GetProcAddress(LibraryA, "GetASPI32SupportInfo");
  result = (int ( *)(LPSRB))GetProcAddress(hCdrModule, "SendASPI32Command");
  SendASPI32Command_cb = result;
  if ( !GetASPI32SupportInfo_cb || !result )
    fatal_error_with_message_box("Error loading WNASPI32.DLL\n");
  return result;
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
  void *v1;
  BYTE v2[8092];

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
    v1 = alloca(8092);
    memset(v2, 0xAAu, sizeof(v2));
    cd_read_mode = 0;
    cached_sector_lba = -1;
    W9x_read_cd_data_only(0, 2u, 0x10u, 2u, v2);
    result = v2[12];
    if ( !v2[12] && v2[13] == 2 && v2[14] == 22 && (result = v2[2364]) == 0 && v2[2365] == 2 && v2[2366] == 23 )
    {
      cd_read_mode = 1;
      sector_stride = 2352;
    }
    else if ( cd_read_mode != 1 )
    {
      memset(v2, 0xAAu, sizeof(v2));
      W9x_read_cd_sectors(0, 2u, 0x10u, 2u, v2);
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

char W9x_get_first_last_track(uint8_t *a1, uint8_t *a2)
{
  char result;

  *a1 = w9x_toc_first_track;
  result = w9x_cdrom_info;
  *a2 = w9x_cdrom_info;
  return result;
}

unsigned int W9x_track_to_msf(int16_t a1, uint8_t *a2, uint8_t *a3, uint8_t *a4)
{
  unsigned int result;
  unsigned int v5;
  unsigned int v6;
  int v7;

  result = (uint8_t)w9x_cdrom_info;
  v7 = 0;
  if ( a1 <= (int)(uint8_t)w9x_cdrom_info )
  {
    if ( a1 )
      W9x_bcd_to_dword(&v7, (uint8_t *)(8 * a1 + 5262496));
    else
      W9x_bcd_to_dword(&v7, (uint8_t *)(8 * (uint8_t)w9x_cdrom_info + 5262504));
    v5 = (v7 + 150) / 0x4Bu;
    *a4 = (v7 + 150) % 0x4Bu;
    v6 = v5 % 0x3C;
    result = v5 / 0x3C;
    *a3 = v6;
    *a2 = result;
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
  uint8_t v2[10];
  uint8_t v3[2];
  uint32_t v4[20];

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
  memset(v4, 0, sizeof(v4));
  BYTE2(v4[0]) = cdrom_haid;
  LOBYTE(v4[2]) = cdrom_target;
  LOBYTE(v4[0]) = 2;
  BYTE1(v4[2]) = cdrom_lun;
  HIBYTE(v4[0]) = 64;
  v4[3] = 12;
  v4[4] = v2;
  LOWORD(v4[5]) = 1550;
  v4[6] = EventA;
  LOBYTE(v4[12]) = 21;
  LOBYTE(v4[13]) = 12;
  ResetEvent(EventA);
  if ( !SendASPI32Command_cb(v4) )
    WaitForSingleObject(EventA, 0xFFFFFFFF);
  return BYTE1(v4[0]) != 1 ? 4 : 1;
}

static int W9x_disable_subchannel_mode()
{
  HANDLE EventA;
  uint8_t v2[4];
  char v3[8];
  uint32_t v4[20];

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
  memset(v4, 0, sizeof(v4));
  BYTE2(v4[0]) = cdrom_haid;
  LOBYTE(v4[2]) = cdrom_target;
  LOBYTE(v4[0]) = 2;
  BYTE1(v4[2]) = cdrom_lun;
  HIBYTE(v4[0]) = 68;
  v4[3] = 12;
  v4[4] = v2;
  LOWORD(v4[5]) = 1550;
  v4[6] = EventA;
  LOBYTE(v4[12]) = 21;
  LOBYTE(v4[13]) = 12;
  ResetEvent(EventA);
  if ( !SendASPI32Command_cb(v4) )
    WaitForSingleObject(EventA, 0xFFFFFFFF);
  return BYTE1(v4[0]) != 1 ? 4 : 1;
}

static char W9x_read_cd_sectors(
        uint8_t a1,
        uint8_t a2,
        uint8_t a3,
        uint8_t a4,
        BYTE *a5)
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
    if ( W9x_enable_subchannel_mode() != 1 )
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
  return W9x_exec_scsi_cmd(&v6, 0xAu, a5, 2352 * a4);
}

static char W9x_read_cd_with_subchannel(
        uint8_t a1,
        uint8_t a2,
        uint8_t a3,
        uint8_t a4,
        BYTE *a5,
        uint32_t *a6)
{
  char result;
  int v7;
  BYTE *v9;
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
    if ( W9x_enable_subchannel_mode() != 1 )
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
  result = W9x_exec_scsi_cmd(&v12, 0xCu, a5, 2368 * a4);
  if ( a4 )
  {
    v9 = a5 + 2352;
    do
    {
      v10 = a6;
      *a6 = *(uint32_t *)v9;
      a6[1] = *((uint32_t *)v9 + 1);
      a6[2] = *((uint32_t *)v9 + 2);
      v11 = *((uint32_t *)v9 + 3);
      v9 += 2368;
      a6 += 4;
      --v7;
      v10[3] = v11;
    }
    while ( v7 );
  }
  return result;
}

static char W9x_read_cd_data_only(
        uint8_t a1,
        uint8_t a2,
        uint8_t a3,
        uint8_t a4,
        BYTE *a5)
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
  return W9x_exec_scsi_cmd(&v6, 0xCu, a5, 2352 * a4);
}

static char W9x_read_cd_subchannel(
        uint8_t a1,
        uint8_t a2,
        uint8_t a3,
        uint8_t a4,
        BYTE *a5)
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
  return W9x_exec_scsi_cmd(&v6, 0xCu, a5, 2368 * a4);
}

static char W9x_read_cd_subchannel2(
        uint8_t a1,
        uint8_t a2,
        uint8_t a3,
        uint8_t a4,
        BYTE *a5)
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
  return W9x_exec_scsi_cmd(&v6, 0xCu, a5, 16 * a4);
}

static char W9x_seek_cd(int a1)
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
  return W9x_exec_scsi_cmd(&v2, 0xAu, nullptr, 0);
}

static char W9x_read_subchannel_status(BYTE *a1)
{
  uint32_t v2[2];
  char v3[4];

  v2[1] = 0;
  v3[1] = 0;
  *(uint32_t *)a1 = 0;
  *((uint32_t *)a1 + 1) = 0;
  *((uint32_t *)a1 + 2) = 0;
  *((uint32_t *)a1 + 3) = 0;
  v2[0] = 20972098;
  v3[0] = 16;
  return W9x_exec_scsi_cmd(v2, 0xAu, a1, 0x10u);
}

char W9x_cdrom_subchannel_read()
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
      if ( SubchannelW9xCachingLG )
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
            W9x_seek_cd(v3);
            v5 = 75;
            do
            {
              W9x_read_subchannel_status((BYTE *)v45);
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
      result = SubchannelW9xCdromEnabled;
      if ( !SubchannelW9xCdromEnabled )
        return result;
      dbg_print(" * Checking subchannel read from cdrom ... ");
      if ( cd_read_mode == 7 )
      {
        W9x_read_cd_with_subchannel(0, 2u, 0x10u, 2u, (BYTE *)v47, v45);
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
        if ( SubchannelW9xCaching )
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
              W9x_read_cd_with_subchannel(3u, v40, i, 5u, (BYTE *)v47, v45);
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
      W9x_read_cd_subchannel(0, 2u, 0x10u, 2u, (BYTE *)v47);
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
          if ( !SubchannelW9xCaching )
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
              W9x_read_cd_subchannel(3u, v41, v19, 5u, (BYTE *)v47);
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
          if ( !SubchannelW9xCaching )
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
              W9x_read_cd_subchannel(3u, v42, j, 5u, (BYTE *)v47);
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
      W9x_read_cd_subchannel2(0, 2u, 0x10u, 2u, (BYTE *)v47);
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
      if ( !SubchannelW9xCaching )
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
          W9x_read_cd_subchannel2(3u, v43, k, 0xFu, (BYTE *)v47);
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

int W9x_cdrom_read_data(uint8_t a1, uint8_t a2, uint8_t a3, char *Buffer)
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
        if ( w9x_cdda_resume_pending )
        {
          W9x_resume_cdda();
          v4 = a1;
          w9x_cdda_resume_pending = 0;
        }
        switch ( cd_read_mode )
        {
          case 1:
            if ( W9x_read_cd_data_only(v4, a2, a3, 8u, (BYTE *)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
            v28 = 0;
            sub_q_cur0 = 0;
            sub_q_cur1 = 0;
            sub_q_cur2 = 0;
            goto LABEL_65;
          case 2:
            if ( W9x_read_cd_subchannel(v4, a2, a3, 8u, (BYTE *)cd_sector_cache) )
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
            if ( W9x_read_cd_subchannel(v4, a2, a3, 8u, (BYTE *)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
            sub_q_cur0 = *(uint32_t *)sub_q_cache;
            sub_q_cur1 = sub_q_sec_frame;
            sub_q_cur2 = sub_q_asec_aframe;
            sub_q_cur3 = sub_q_rest[0];
            goto LABEL_66;
          case 4:
            if ( W9x_read_cd_data_only(v4, a2, a3, 8u, (BYTE *)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
            memset(sub_q_block_cache, 0, 0x80u);
            if ( a1 == 3
              && (cop0_bpc_value[0] & 0x1F000000) == 0x1F000000
              && W9x_read_cd_subchannel2(3u, a2, a3, 8u, (BYTE *)sub_q_block_cache) )
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
            if ( !W9x_read_cd_data_only(a1, a2, a3, 8u, (BYTE *)cd_sector_cache) )
              goto LABEL_56;
            dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
            sub_q_cur0 = sub_q_block_cache[0];
            sub_q_cur1 = sub_q_block_cache1;
            sub_q_cur2 = sub_q_block_cache2;
            sub_q_cur3 = sub_q_block_cache3[0];
            goto LABEL_66;
          case 6:
            if ( W9x_read_cd_data_only(v4, a2, a3, 8u, (BYTE *)cd_sector_cache) )
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
            if ( W9x_read_cd_sectors(v4, a2, a3, 8u, (BYTE *)cd_sector_cache) )
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
              if ( W9x_read_cd_with_subchannel(3u, a2, a3, 8u, (BYTE *)cd_sector_cache, sub_q_block_cache) )
                dbg_print(" * Error sub reading CD: %d,%d,%d\n", 3, a2, v7);
              v4 = a1;
            }
            if ( W9x_read_cd_sectors(v4, a2, a3, 8u, (BYTE *)cd_sector_cache) )
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
            if ( W9x_read_cd_sectors(a1, a2, a3, 8u, (BYTE *)cd_sector_cache) )
              dbg_print(" * Error reading CD: %d,%d,%d\n", a1, a2, v7);
LABEL_56:
            sub_q_cur0 = sub_q_block_cache[0];
            sub_q_cur1 = sub_q_block_cache1;
            sub_q_cur2 = sub_q_block_cache2;
            sub_q_cur3 = sub_q_block_cache3[0];
            goto LABEL_66;
          case 10:
            if ( W9x_read_cd_sectors(v4, a2, a3, 8u, (BYTE *)cd_sector_cache) )
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

static char W9x_find_track_by_msf(unsigned int a1, char a2)
{
  char v2;
  uint8_t v4;

  v4 = 0;
  if ( !(uint8_t)w9x_cdrom_info )
    return 0;
  v2 = a1;
  while ( 1 )
  {
    W9x_bcd_to_dword(&a1, (uint8_t *)(8 * v4 + 5262504));
    a1 += 150;
    if ( (uint8_t)(a1 / 0x4B / 0x3C) == v2 && a1 / 0x4B % 0x3C == a2 )
      break;
    if ( ++v4 >= (uint8_t)w9x_cdrom_info )
      return 0;
  }
  return a1 % 0x4B;
}

char W9x_play_cdda(unsigned int a1, int a2, uint8_t track_by_msf)
{
  char result;
  uint8_t v4;
  HANDLE EventA;
  uint32_t v6[20];

  result = sound_use_cdda;
  if ( sound_use_cdda )
  {
    v4 = a2;
    track_by_msf = W9x_find_track_by_msf(a1, a2);
    BYTE1(w9x_play_cdb2) = track_by_msf;
    HIBYTE(w9x_play_cdb) = a1;
    LOBYTE(w9x_play_cdb2) = v4;
    W9x_bcd_to_dword(&a2, (uint8_t *)(8 * (uint8_t)w9x_cdrom_info + 5262504));
    LOBYTE(w9x_play_cdb3) = (a2 + 150) % 0x4Bu;
    BYTE2(w9x_play_cdb2) = (a2 + 150) / 0x4Bu / 0x3C;
    HIBYTE(w9x_play_cdb2) = (a2 + 150) / 0x4Bu % 0x3C;
    EventA = CreateEventA(nullptr, 1, 0, nullptr);
    memset(v6, 0, sizeof(v6));
    BYTE2(v6[0]) = cdrom_haid;
    LOBYTE(v6[2]) = cdrom_target;
    BYTE1(v6[2]) = cdrom_lun;
    LOBYTE(v6[0]) = 2;
    HIBYTE(v6[0]) = 72;
    LOWORD(v6[5]) = 2574;
    v6[3] = 0;
    v6[4] = 0;
    v6[6] = EventA;
    v6[12] = w9x_play_cdb;
    v6[13] = w9x_play_cdb2;
    LOWORD(v6[14]) = w9x_play_cdb3;
    ResetEvent(EventA);
    if ( !SendASPI32Command_cb(v6) )
      WaitForSingleObject(EventA, 0xFFFFFFFF);
    result = CloseHandle(EventA);
    if ( BYTE1(v6[0]) == 1 )
      w9x_cdda_playing = 1;
    else
      return printf(" * Play cdda error (%d, %d, %d) \n", (uint8_t)a1, v4, track_by_msf);
  }
  return result;
}

char W9x_cdrom_stop()
{
  char result;
  HANDLE EventA;
  uint32_t v2[20];

  BYTE1(w9x_stop_cdb) = (32 * cdrom_lun) | 1;
  result = sound_use_cdda;
  if ( sound_use_cdda )
  {
    result = w9x_cdda_playing;
    if ( w9x_cdda_playing )
    {
      w9x_cdda_playing = 0;
      EventA = CreateEventA(nullptr, 1, 0, nullptr);
      memset(v2, 0, sizeof(v2));
      BYTE2(v2[0]) = cdrom_haid;
      LOBYTE(v2[2]) = cdrom_target;
      BYTE1(v2[2]) = cdrom_lun;
      LOBYTE(v2[0]) = 2;
      HIBYTE(v2[0]) = 80;
      LOWORD(v2[5]) = 2574;
      v2[3] = 0;
      v2[4] = 0;
      v2[6] = EventA;
      v2[12] = w9x_stop_cdb;
      v2[13] = w9x_stop_cdb2;
      LOWORD(v2[14]) = w9x_stop_cdb3;
      ResetEvent(EventA);
      if ( !SendASPI32Command_cb(v2) )
        WaitForSingleObject(EventA, 0xFFFFFFFF);
      if ( BYTE1(v2[0]) != 1 )
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
  uint32_t v2[20];

  BYTE1(w9x_resume_cdb) = (32 * cdrom_lun) | 1;
  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(v2, 0, sizeof(v2));
  BYTE2(v2[0]) = cdrom_haid;
  LOBYTE(v2[2]) = cdrom_target;
  BYTE1(v2[2]) = cdrom_lun;
  LOBYTE(v2[0]) = 2;
  HIBYTE(v2[0]) = 80;
  LOWORD(v2[5]) = 2574;
  v2[3] = 0;
  v2[4] = 0;
  v2[6] = EventA;
  v2[12] = w9x_resume_cdb;
  v2[13] = w9x_resume_cdb2;
  LOWORD(v2[14]) = w9x_resume_cdb3;
  ResetEvent(EventA);
  if ( !SendASPI32Command_cb(v2) )
    WaitForSingleObject(EventA, 0xFFFFFFFF);
  if ( BYTE1(v2[0]) != 1 )
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
        unsigned int a1,
        uint8_t a2,
        uint8_t a3,
        uint8_t *a4,
        uint8_t *a5,
        uint8_t *a6,
        uint8_t *a7)
{
  char v7;
  int v8;
  unsigned int v9;
  char result;
  unsigned int v11;
  uint8_t v12;

  v12 = 0;
  v7 = w9x_cdrom_info;
  v8 = (uint8_t)w9x_cdrom_info;
  v9 = (a3 & 0xF) % 10
     + 75
     * ((a2 & 0xF) % 10 + 10 * ((a2 >> 4) + 6 * ((uint8_t)(a1 & 0xF) % 10 + 10 * ((uint8_t)a1 >> 4))))
     + 10 * (a3 >> 4)
     - 150;
  W9x_bcd_to_dword(&a1, (uint8_t *)(8 * (uint8_t)w9x_cdrom_info + 5262504));
  result = a1;
  if ( a1 > v9 )
  {
    if ( v7 )
    {
      while ( 1 )
      {
        W9x_bcd_to_dword(&a1, (uint8_t *)(8 * v12 + 5262512));
        if ( v12 + 1 < v8 )
          a1 -= a1 % 0x4B;
        if ( a1 > v9 )
          break;
        if ( ++v12 >= (uint8_t)w9x_cdrom_info )
          goto LABEL_8;
      }
      W9x_bcd_to_dword(&a1, (uint8_t *)(8 * v12 + 5262504));
      v11 = v9 + a1 % 0x4B - a1;
      *a4 = (v12 + 1) % 10 + 16 * ((v12 + 1) / 10);
      *a5 = v11 / 0x4B / 0x3C % 0xA + 16 * (v11 / 0x4B / 0x3C / 0xA);
      *a6 = v11 / 0x4B % 0x3C % 0xA + 16 * (v11 / 0x4B % 0x3C / 0xA);
      result = v11 % 0x4B % 0xA + 16 * (v11 % 0x4B / 0xA);
      *a7 = result;
    }
    else
    {
LABEL_8:
      result = (char)a4;
      *a4 = -86;
    }
  }
  else
  {
    *a4 = -86;
  }
  return result;
}

uint8_t W9x_get_track_start_lba(
        uint8_t a1,
        uint8_t a2,
        uint8_t a3,
        uint8_t *a4,
        uint8_t *a5,
        uint8_t *a6)
{
  uint8_t v6;
  unsigned int v7;
  uint8_t result;
  unsigned int v9;
  unsigned int v10;
  unsigned int v11;
  int v12;

  v6 = 0;
  LOBYTE(v12) = 0;
  v7 = (a3 & 0xF) % 10
     + 75 * ((a2 & 0xF) % 10 + 10 * ((a2 >> 4) + 6 * ((a1 & 0xF) % 10 + 10 * (a1 >> 4))))
     + 10 * (a3 >> 4);
  W9x_bcd_to_dword(&v11, (uint8_t *)(8 * (uint8_t)w9x_cdrom_info + 5262504));
  if ( v11 > v7 )
  {
    result = w9x_cdrom_info;
    if ( (uint8_t)w9x_cdrom_info )
    {
      while ( 1 )
      {
        W9x_bcd_to_dword(&v11, (uint8_t *)(8 * (uint8_t)v12 + 5262512));
        if ( v11 > v7 )
          break;
        result = w9x_cdrom_info;
        LOBYTE(v12) = ++v6;
        if ( v6 >= (uint8_t)w9x_cdrom_info )
          return result;
      }
      v9 = v11 % 0x4B;
      v10 = v11 / 0x4B % 0x3C;
      *a4 = v11 / 0x4B / 0x3C;
      *a5 = v10;
      *a6 = v9;
      return (uint8_t)a5;
    }
  }
  else
  {
    *a4 = a1;
    *a5 = a2;
    *a6 = a3;
    return a2;
  }
  return result;
}

char W9x_verify_subchannel_data(unsigned int a1, uint8_t a2, uint8_t a3, int a4)
{
  char v4;
  char v5;
  char result;
  char v7;
  uint8_t v8;
  uint8_t v9;
  uint8_t v10;
  char v11;
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
    W9x_msf_to_lba(a1, v9, v12, (uint8_t *)a4, (uint8_t *)(a4 + 2), (uint8_t *)(a4 + 3), (uint8_t *)(a4 + 4));
    *(uint8_t *)(a4 + 1) = 1;
    *(uint8_t *)(a4 + 5) = a1;
    *(uint8_t *)(a4 + 6) = v9;
    *(uint8_t *)(a4 + 7) = v12;
    return v12;
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
