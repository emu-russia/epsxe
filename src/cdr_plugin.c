#include "pch.h"

/* Decompiled globals (previously generated in src/_gen) */
static int ( *CDRclose)();
static int ( *CDRgetBuffer)();
static int ( *CDRgetBufferSub)();
static int ( *CDRgetTD)();
static unsigned int CDRgetTN;
static int ( *CDRinit)();
static int ( *CDRopen)();
static unsigned int CDRplay;
static int ( *CDRreadTrack)();
static int ( *CDRshutdown)();
static int ( *CDRstop)();
static unsigned int CDRtest;
unsigned char cdrom_fake_filename[0x100];
static unsigned short current_position_low;
static unsigned int current_position_msf;
static unsigned short first_last_tracks;
unsigned int hCdrModule;
static unsigned int track_info_buffer;
static unsigned char track_minutes_table[1];
static unsigned char track_msf_minutes[1];
static unsigned char track_msf_seconds[1];
static unsigned char track_msf_sectors[1];
static unsigned char track_msf_table[1];
static unsigned char track_seconds_table[1];
static unsigned char track_sectors_table[0x139];

char ext_cdrom_load_plugin()
{
  uint8_t track_index;
  int table_index;
  char sector;
  char last_sector;
  int (*proc)(void);
  HMODULE LibraryA;
  int value;
  CHAR LibFileName[1004];
  int last_value;
  int track_time;
  int track_num;

  sprintf(LibFileName, "%s%s", "plugins\\", (const char *)CdromPlugin);
  if ( cd_savefake_flag )
  {
    if ( cd_savefake_flag == 1 )
      cdrom_fake_create_file(cdrom_fake_filename);
    if ( loaded_file_type == 3 )
    {
      iso_load(bin_iso_file);
      sound_use_cdda = 0;
      track_msf_minutes[0] = 0;
      track_msf_sectors[0] = 0;
      first_last_tracks = 257;
      track_msf_seconds[0] = 2;
      LOBYTE(proc) = 1;
    }
    else
    {
      if ( !strcmp((const char *)CdromPlugin, "NULL") )
        fatal_error_with_message_box(" * !Error cdrom doesn't configurated \n"
                                     " * !Go Config->Cdrom and choose a plugin. \n");
      LibraryA = LoadLibraryA(LibFileName);
      hCdrModule = LibraryA;
      if ( !LibraryA )
        fatal_error_with_message_box(" * Error loading [%s] \n", LibFileName);
      proc = GetProcAddress(LibraryA, "CDRconfigure");
      if ( proc )
      {
        proc = GetProcAddress(hCdrModule, "CDRtest");
        CDRtest = (int)proc;
        if ( proc )
        {
          proc = GetProcAddress(hCdrModule, "CDRinit");
          CDRinit = proc;
          if ( proc )
          {
            proc = GetProcAddress(hCdrModule, "CDRshutdown");
            CDRshutdown = (int ( *)(void))proc;
            if ( proc )
            {
              proc = GetProcAddress(hCdrModule, "CDRopen");
              CDRopen = proc;
              if ( proc )
              {
                proc = GetProcAddress(hCdrModule, "CDRclose");
                CDRclose = proc;
                if ( proc )
                {
                  proc = GetProcAddress(hCdrModule, "CDRgetTN");
                  CDRgetTN = (int ( *)(uint32_t, uint32_t, uint32_t))proc;
                  if ( proc )
                  {
                    proc = GetProcAddress(hCdrModule, "CDRgetTD");
                    CDRgetTD = (int ( *)(uint32_t, uint32_t, uint32_t))proc;
                    if ( proc )
                    {
                      proc = GetProcAddress(hCdrModule, "CDRreadTrack");
                      CDRreadTrack = (int ( *)(uint32_t))proc;
                      if ( proc )
                      {
                        proc = GetProcAddress(hCdrModule, "CDRgetBuffer");
                        CDRgetBuffer = proc;
                        if ( proc )
                        {
                          CDRplay = (int ( *)(void))GetProcAddress(hCdrModule, "CDRplay");
                          CDRstop = (int ( *)(void))GetProcAddress(hCdrModule, "CDRstop");
                          if ( use_subchannel )
                          {
                            CDRgetBufferSub = GetProcAddress(hCdrModule, "CDRgetBufferSub");
                            if ( CDRgetBufferSub )
                              cpu_overclock_setting = 0;
                          }
                          else
                          {
                            CDRgetBufferSub = nullptr;
                          }
                          dbg_print(" * Init cdrom ... ");
                          CDRinit();
                          dbg_print("ok\n");
                          if ( nocd )
                          {
                            dbg_print(" * Cdrom open... ");
                            ShowCursor(1);
                            CDRopen();
                            ShowCursor(0);
                            dbg_print(" ok \n");
                          }
                          LOBYTE(proc) = (uint8_t)hCdrModule;
                          if ( hCdrModule )
                          {
                            current_position_msf = 0;
                            current_position_low = 0;
                            ((void ( *)(int *))CDRgetTN)(&current_position_msf);
                            track_index = 0;
                            first_last_tracks = current_position_msf;
                            LOBYTE(track_num) = 0;
                            if ( BYTE1(current_position_msf) )
                            {
                              track_time = value;
                              do
                              {
                                table_index = (uint8_t)track_num;
                                track_info_buffer = 0;
                                CDRgetTD((uint8_t)track_num + 1, &track_info_buffer, track_time);
                                track_msf_minutes[3 * table_index] = BYTE2(track_info_buffer);
                                sector = track_info_buffer;
                                track_msf_seconds[3 * table_index] = BYTE1(track_info_buffer);
                                track_msf_sectors[3 * table_index] = sector;
                                LOBYTE(track_time) = ++track_index;
                              }
                              while ( track_index < HIBYTE(first_last_tracks) );
                            }
                            track_info_buffer = 0;
                            CDRgetTD(0, &track_info_buffer, last_value);
                            track_msf_minutes[3 * HIBYTE(first_last_tracks)] = BYTE2(track_info_buffer);
                            last_sector = track_info_buffer;
                            track_msf_seconds[3 * HIBYTE(first_last_tracks)] = BYTE1(track_info_buffer);
                            LOBYTE(proc) = HIBYTE(first_last_tracks);
                            track_msf_sectors[3 * HIBYTE(first_last_tracks)] = last_sector;
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  else
  {
    LOBYTE(proc) = cdrom_fake_load_file(cdrom_fake_filename);
  }
  return (char)proc;
}

char ext_CDR_get_first_last_track(uint8_t *first_track, uint8_t *last_track)
{
  char last_track_value;

  *first_track = first_last_tracks;
  last_track_value = HIBYTE(first_last_tracks);
  *last_track = HIBYTE(first_last_tracks);
  return last_track_value;
}

char ext_CDR_track_to_msf(int16_t track, uint8_t *min, uint8_t *sec, uint8_t *frame)
{
  char frame_value;

  if ( track <= (int)HIBYTE(first_last_tracks) )
  {
    if ( track )
    {
      *min = track_msf_table[3 * track];
      *sec = *((uint8_t *)&first_last_tracks + 3 * track);
      frame_value = *((uint8_t *)&first_last_tracks + 3 * track + 1);
      *frame = frame_value;
    }
    else
    {
      *min = track_msf_minutes[3 * HIBYTE(first_last_tracks)];
      *sec = track_msf_seconds[3 * HIBYTE(first_last_tracks)];
      frame_value = HIBYTE(first_last_tracks);
      *frame = track_msf_sectors[3 * HIBYTE(first_last_tracks)];
    }
  }
  else
  {
    *min = 0;
    *sec = 2;
    *frame = 0;
    return (char)min;
  }
  return frame_value;
}

int ext_CDR_read(uint8_t min, uint8_t sec, uint8_t frame, char *Buffer)
{
  int lba;
  const void *src;
  char *dest;
  int sector_lba;
  uint8_t msf_bcd[16];

  if ( !cd_savefake_flag )
  {
    cdrom_fake_read_portion(min, sec, frame, Buffer);
    return 0;
  }
  if ( loaded_file_type == 3 )
  {
    iso_read_data(min, sec, frame, (int)Buffer);
    if ( ppf_enabled )
    {
      lba = cdr_msf_to_lba(min, sec, frame);
      ppf_apply_patch_to_sector(lba, (int)Buffer);
    }
    if ( cd_savefake_flag == 1 )
    {
      cdrom_fake_write_portion(min, sec, frame, Buffer);
      return 0;
    }
  }
  else
  {
    msf_bcd[0] = min % 10 + 16 * (min / 10);
    msf_bcd[1] = sec % 10 + 16 * (sec / 10);
    msf_bcd[2] = frame % 10 + 16 * (frame / 10);
    CDRreadTrack(msf_bcd);
    src = (const void *)CDRgetBuffer();
    dest = Buffer;
    qmemcpy(Buffer + 12, src, 0x930u);
    if ( ppf_enabled )
    {
      sector_lba = cdr_msf_to_lba(min, sec, frame);
      ppf_apply_patch_to_sector(sector_lba, (int)Buffer);
      dest = Buffer;
    }
    if ( cd_savefake_flag == 1 )
      cdrom_fake_write_portion(min, sec, frame, dest);
  }
  return 0;
}

int (*ext_cdrom_deinit())(void)
{
  int (*shutdown_fn)(void);

  if ( cd_savefake_flag >= 0 )
    cdrom_fake_write();
  if ( loaded_file_type == 3 )
    iso_close();
  ext_CDRstop();
  if ( CDRclose )
    CDRclose();
  shutdown_fn = (int (*)(void))CDRshutdown;
  if ( CDRshutdown )
    return CDRshutdown();
  return shutdown_fn;
}

static char ext_CDR_bcd_to_binary(char min, char sec)
{
  uint8_t index;

  index = 0;
  if ( !HIBYTE(first_last_tracks) )
    return 0;
  while ( min != track_msf_minutes[3 * index] || sec != track_msf_seconds[3 * index] )
  {
    if ( ++index >= HIBYTE(first_last_tracks) )
      return 0;
  }
  return track_msf_sectors[3 * index];
}

char ext_CDRplay(int track_msf, char sec)
{
  char status;
  char (__stdcall *play_fn)(int *);

  status = sound_use_cdda;
  if ( sound_use_cdda )
  {
    play_fn = (char (__stdcall *)(int *))CDRplay;
    if ( CDRplay )
    {
      BYTE1(track_msf) = sec;
      BYTE2(track_msf) = ext_CDR_bcd_to_binary(track_msf, sec);
      return play_fn(&track_msf);
    }
  }
  return status;
}

char ext_CDRstop()
{
  char status;

  status = sound_use_cdda;
  if ( sound_use_cdda )
  {
    status = (char)CDRstop;
    if ( CDRstop )
      return CDRstop();
  }
  return status;
}


void ext_CDR_reset_state()
{
  cdr_spinup_motor();
}

static char ext_CDR_lba_to_msf_with_track(
        uint8_t min,
        uint8_t sec,
        uint8_t frame,
        uint8_t *out_track,
        uint8_t *out_min,
        uint8_t *out_sec,
        uint8_t *out_frame)
{
  unsigned int lba;
  uint8_t last_track;
  int frame_value;
  unsigned int track_lba;
  unsigned int offset;
  uint8_t track_index;

  lba = 75 * ((sec & 0xF) + 10 * ((sec >> 4) + 6 * ((min & 0xF) + 10 * (min >> 4)))) + 10 * (frame >> 4) + (frame & 0xF) - 150;
  last_track = HIBYTE(first_last_tracks);
  track_index = 0;
  frame_value = (uint8_t)track_msf_sectors[3 * HIBYTE(first_last_tracks)];
  if ( 75
     * ((uint8_t)track_msf_seconds[3 * HIBYTE(first_last_tracks)]
      + 60 * (unsigned int)(uint8_t)track_msf_minutes[3 * HIBYTE(first_last_tracks)])
     + frame_value
     - 150 > lba )
  {
    if ( HIBYTE(first_last_tracks) )
    {
      while ( 1 )
      {
        track_lba = 75 * ((uint8_t)track_seconds_table[3 * track_index] + 60 * (uint8_t)track_minutes_table[3 * track_index])
            + (uint8_t)track_sectors_table[3 * track_index]
            - 150;
        if ( track_index + 1 < HIBYTE(first_last_tracks) )
        {
          track_lba -= track_lba % 0x4B;
          last_track = HIBYTE(first_last_tracks);
        }
        if ( track_lba > lba )
          break;
        if ( ++track_index >= last_track )
          goto LABEL_8;
      }
      offset = 75 * ((sec & 0xF) + 10 * ((sec >> 4) + 6 * ((min & 0xF) + 10 * (min >> 4))))
          + 10 * (frame >> 4)
          + (frame & 0xF)
          + (75 * ((uint8_t)track_msf_seconds[3 * track_index] + 60 * (uint8_t)track_msf_minutes[3 * track_index])
           + (unsigned int)(uint8_t)track_msf_sectors[3 * track_index]
           - 150)
          % 0x4B
          - (75 * ((uint8_t)track_msf_seconds[3 * track_index] + 60 * (uint8_t)track_msf_minutes[3 * track_index])
           + (uint8_t)track_msf_sectors[3 * track_index]);
      *out_track = (track_index + 1) % 10 + 16 * ((track_index + 1) / 10);
      *out_min = offset / 0x4B / 0x3C % 0xA + 16 * (offset / 0x4B / 0x3C / 0xA);
      *out_sec = offset / 0x4B % 0x3C % 0xA + 16 * (offset / 0x4B % 0x3C / 0xA);
      LOBYTE(frame_value) = offset % 0x4B % 0xA + 16 * (offset % 0x4B / 0xA);
      *out_frame = frame_value;
    }
    else
    {
LABEL_8:
      *out_track = -86;
      LOBYTE(frame_value) = (uint8_t)out_track;
    }
  }
  else
  {
    *out_track = -86;
  }
  return frame_value;
}

uint8_t ext_CDR_lba_to_msf(
        uint8_t min,
        uint8_t sec,
        uint8_t frame,
        uint8_t *out_min,
        uint8_t *out_sec,
        uint8_t *out_frame)
{
  uint8_t next_index;
  unsigned int lba;
  uint8_t last_track;
  unsigned int track_lba;
  uint8_t index;

  next_index = 0;
  lba = (frame & 0xF) + 75 * ((sec & 0xF) + 10 * ((sec >> 4) + 6 * ((min & 0xF) + 10 * (min >> 4)))) + 10 * (frame >> 4);
  index = 0;
  if ( 75
     * ((uint8_t)track_msf_seconds[3 * HIBYTE(first_last_tracks)]
      + 60 * (uint8_t)track_msf_minutes[3 * HIBYTE(first_last_tracks)])
     + (unsigned int)(uint8_t)track_msf_sectors[3 * HIBYTE(first_last_tracks)]
     - 150 > lba )
  {
    last_track = HIBYTE(first_last_tracks);
    if ( HIBYTE(first_last_tracks) )
    {
      while ( 1 )
      {
        track_lba = 75 * ((uint8_t)track_seconds_table[3 * index] + 60 * (uint8_t)track_minutes_table[3 * index])
           + (uint8_t)track_sectors_table[3 * index]
           - 150;
        if ( track_lba > lba )
          break;
        last_track = HIBYTE(first_last_tracks);
        index = ++next_index;
        if ( next_index >= HIBYTE(first_last_tracks) )
          return last_track;
      }
      *out_min = track_lba / 0x4B / 0x3C;
      *out_sec = track_lba / 0x4B % 0x3C;
      *out_frame = track_lba % 0x4B;
      return (uint8_t)out_sec;
    }
  }
  else
  {
    *out_min = min;
    *out_sec = sec;
    *out_frame = frame;
    return sec;
  }
  return last_track;
}

char ext_CDR_verify_subchannel_data(uint8_t min, uint8_t sec, uint8_t frame, int buffer)
{
  int sub_data;
  char min_bcd;
  char total_errors;
  char status;
  char errors;
  uint8_t sec_bcd;
  uint8_t bcd_sec;
  uint8_t frame_adj;
  char frame_bcd;
  uint8_t bcd_frame;

  *(uint32_t *)buffer = 0;
  *(uint32_t *)(buffer + 4) = 0;
  errors = 0;
  if ( CDRgetBufferSub
    && ((sub_data = CDRgetBufferSub(), !extsubchanhle) || (cop0_bpc_value[0] & 0x1F000000) != 0x1F000000 || min == 3)
    && sub_data )
  {
    if ( frame )
    {
      frame_adj = frame - 1;
    }
    else
    {
      frame_adj = 74;
      if ( sec )
      {
        --sec;
      }
      else
      {
        sec = 59;
        --min;
      }
    }
    min_bcd = min % 10 + 16 * (min / 10);
    sec_bcd = sec % 10 + 16 * (sec / 10);
    frame_bcd = frame_adj % 10 + 16 * (frame_adj / 10);
    *(uint32_t *)buffer = *(uint32_t *)(sub_data + 13);
    *(uint8_t *)(buffer + 4) = *(uint8_t *)(sub_data + 17);
    *(uint16_t *)(buffer + 5) = *(uint16_t *)(sub_data + 19);
    *(uint8_t *)(buffer + 7) = *(uint8_t *)(sub_data + 21);
    if ( min_bcd != *(uint8_t *)(sub_data + 19) )
      errors = 1;
    if ( min_bcd != *(uint8_t *)(sub_data + 15) )
      ++errors;
    if ( sec_bcd != *(uint8_t *)(sub_data + 20) )
      ++errors;
    total_errors = errors;
    if ( (((sec_bcd - 2) & 0xF) + 10 * ((sec_bcd - 2) >> 4)) % 10 + 16 * ((((sec_bcd - 2) & 0xF) + 10 * ((sec_bcd - 2) >> 4)) / 10) != *(uint8_t *)(sub_data + 16) )
      total_errors = errors + 1;
    status = frame_bcd;
    if ( frame_bcd != *(uint8_t *)(sub_data + 21) )
      ++total_errors;
    if ( frame_bcd != *(uint8_t *)(sub_data + 17) )
      ++total_errors;
    if ( (uint8_t)total_errors >= 2u )
    {
      status = 0;
      *(uint32_t *)(buffer + 2) = 0;
      *(uint16_t *)(buffer + 6) = 0;
      if ( min_bcd == 3 )
        xenogears_cd_detected = 1;
    }
  }
  else
  {
    bcd_sec = sec % 10 + 16 * (sec / 10);
    bcd_frame = frame % 10 + 16 * (frame / 10);
    ext_CDR_lba_to_msf_with_track(
      min % 10 + 16 * (min / 10),
      bcd_sec,
      bcd_frame,
      (uint8_t *)buffer,
      (uint8_t *)(buffer + 2),
      (uint8_t *)(buffer + 3),
      (uint8_t *)(buffer + 4));
    *(uint8_t *)(buffer + 1) = 1;
    *(uint8_t *)(buffer + 5) = min % 10 + 16 * (min / 10);
    *(uint8_t *)(buffer + 6) = bcd_sec;
    *(uint8_t *)(buffer + 7) = bcd_frame;
    return bcd_frame;
  }
  return status;
}
