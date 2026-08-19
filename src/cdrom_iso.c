#include "pch.h"

/* Decompiled globals (previously generated in src/_gen) */
static unsigned char subchannel_buffer[0xd];
static unsigned char subchannel_q_rel_frame;
static unsigned char subchannel_q_abs_frame[0x4b];
static unsigned char iso_sector_buffer[0x1160];
static unsigned char subchannel_msf_minute;
static unsigned char subchannel_msf_second;
static unsigned char subchannel_msf_frame;
static unsigned int iso_cache_start_lba = 0xffffffff;
static unsigned int iso_sector_size = 0x930;
static unsigned int iso_file_size;
static unsigned int iso_data_start_offset;
static unsigned int subchannel_file_handle;
static unsigned int subchannel_q_track_rel;
static unsigned int iso_file_handle;
unsigned char use_subchannel = 0x1;
static unsigned short subchannel_q_abs_ms;

char iso_load(char *FileName)
{
  FILE *fp;
  char subchannel;
  char ext;
  int magic;
  char buffer[1024];

  dbg_print(" * Loading ISO Format ");
  fp = fopen(FileName, "rb");
  iso_file_handle = fp;
  if ( !fp )
    fatal_error_with_message_box(" * Error loading cdrombin [%s]\n", FileName);
  fseek(fp, 0, 2);
  iso_file_size = ftell(iso_file_handle);
  iso_cache_start_lba = -1;
  fseek(iso_file_handle, 12, 0);
  fread(&magic, 1u, 4u, iso_file_handle);
  if ( magic == 0x2000000 )
  {
    fseek(iso_file_handle, 150 * iso_sector_size + 12, 0);
    fread(&magic, 1u, 4u, iso_file_handle);
    if ( magic == 33554944 )
    {
      iso_data_start_offset = 150 * iso_sector_size;
      dbg_print("[NRG2352] ");
    }
  }
  else
  {
    if ( magic )
      goto LABEL_11;
    fseek(iso_file_handle, 0, 0);
    fread(&magic, 1u, 4u, iso_file_handle);
    if ( magic == 0x80000 )
    {
      iso_sector_size = 2336;
      dbg_print("[NRG2336] ");
      goto LABEL_12;
    }
    if ( magic != 0x200000 )
    {
LABEL_11:
      dbg_print("[BIN/IMG2352] ");
    }
    else
    {
      dbg_print("[CDI2336] ");
      iso_sector_size = 2336;
      iso_data_start_offset = 350400;
    }
  }
LABEL_12:
  fseek(iso_file_handle, 0, 0);
  sprintf(buffer, "%s", FileName);
  subchannel = use_subchannel;
  if ( use_subchannel )
  {
    ext = buffer[strlen(buffer) - 4];
    use_subchannel = 0;
    if ( ext == 46 )
    {
      qmemcpy(&buffer[strlen(buffer) - 3], "sub", 3);
      subchannel_file_handle = fopen(buffer, "rb");
      if ( subchannel_file_handle )
      {
        use_subchannel = 1;
        dbg_print("(+subchannel) ");
        cpu_overclock_setting = 0;
      }
    }
    return dbg_print("ok\n");
  }
  return subchannel;
}

char iso_verify_sub(uint8_t minute, uint8_t second, char frame, int buffer)
{
  int msf_min_bcd;
  uint8_t abs_frame;
  int sec_adj;
  int tmp;
  int err_total;
  uint8_t sec_bcd;
  uint8_t min_adj;
  int sec_lo;
  uint8_t err_count;
  uint8_t min_bcd;
  uint8_t frame_val;
  char frame_bcd;

  *(uint32_t *)buffer = 0;
  *(uint32_t *)(buffer + 4) = 0;
  if ( use_subchannel )
  {
    *(uint32_t *)buffer = subchannel_q_track_rel;
    *(uint8_t *)(buffer + 4) = subchannel_q_rel_frame;
    *(uint16_t *)(buffer + 5) = subchannel_q_abs_ms;
    *(uint8_t *)(buffer + 7) = subchannel_q_abs_frame[0];
    if ( (uint8_t)subchannel_msf_second - 2 < 0 )
    {
      err_count = (uint8_t)subchannel_msf_minute % 10 + 16 * ((uint8_t)subchannel_msf_minute / 10) != (uint8_t)subchannel_q_abs_ms;
      if ( ((uint8_t)subchannel_msf_minute - 1) % 10 + 16 * (((uint8_t)subchannel_msf_minute - 1) / 10) != BYTE2(subchannel_q_track_rel) )
        ++err_count;
      abs_frame = subchannel_q_abs_frame[0];
      if ( (uint8_t)subchannel_msf_second % 10 + 16 * ((uint8_t)subchannel_msf_second / 10) != HIBYTE(subchannel_q_abs_ms) )
        ++err_count;
      sec_adj = (uint8_t)subchannel_msf_second + 58;
    }
    else
    {
      msf_min_bcd = (uint8_t)subchannel_msf_minute % 10 + 16 * ((uint8_t)subchannel_msf_minute / 10);
      err_count = msf_min_bcd != (uint8_t)subchannel_q_abs_ms;
      if ( msf_min_bcd != BYTE2(subchannel_q_track_rel) )
        ++err_count;
      abs_frame = subchannel_q_abs_frame[0];
      if ( (uint8_t)subchannel_msf_second % 10 + 16 * ((uint8_t)subchannel_msf_second / 10) != HIBYTE(subchannel_q_abs_ms) )
        ++err_count;
      sec_adj = (uint8_t)subchannel_msf_second - 2;
    }
    if ( sec_adj % 10 + 16 * (sec_adj / 10) != HIBYTE(subchannel_q_track_rel) )
      ++err_count;
    tmp = (uint8_t)subchannel_msf_frame % 10 + 16 * ((uint8_t)subchannel_msf_frame / 10);
    err_total = err_count;
    if ( tmp != abs_frame )
      err_total = err_count + 1;
    if ( tmp != (uint8_t)subchannel_q_rel_frame )
      ++err_total;
    if ( err_total >= 2u && minute == 3 )
    {
      *(uint32_t *)(buffer + 2) = 0;
      *(uint16_t *)(buffer + 6) = 0;
      tmp = (uint8_t)subchannel_msf_minute % 10 + 16 * ((uint8_t)subchannel_msf_minute / 10);
      if ( tmp == 3 )
        xenogears_cd_detected = 1;
    }
  }
  else
  {
    if ( frame )
    {
      frame_val = frame - 1;
    }
    else
    {
      frame_val = 74;
      if ( second )
      {
        --second;
      }
      else
      {
        second = 59;
        --minute;
      }
    }
    *(uint8_t *)buffer = 1;
    *(uint8_t *)(buffer + 1) = 1;
    min_bcd = minute % 10 + 16 * (minute / 10);
    sec_bcd = second % 10 + 16 * (second / 10);
    frame_bcd = frame_val % 10 + 16 * (frame_val / 10);
    min_adj = min_bcd;
    if ( sec_bcd < 2u )
      min_adj = ((min_bcd & 0xF) + 10 * (min_bcd >> 4) - 1) % 10 + 16 * (((min_bcd & 0xF) + 10 * (min_bcd >> 4) - 1) / 10);
    *(uint8_t *)(buffer + 2) = min_adj;
    sec_lo = sec_bcd & 0xF;
    if ( sec_bcd < 2u )
      tmp = sec_lo + 10 * (sec_bcd >> 4) + 58;
    else
      tmp = sec_lo + 10 * (sec_bcd >> 4) - 2;
    *(uint8_t *)(buffer + 6) = sec_bcd;
    *(uint8_t *)(buffer + 3) = tmp % 10 + 16 * (tmp / 10);
    *(uint8_t *)(buffer + 4) = frame_bcd;
    *(uint8_t *)(buffer + 5) = min_bcd;
    *(uint8_t *)(buffer + 7) = frame_bcd;
    LOBYTE(tmp) = frame_bcd;
  }
  return tmp;
}

char iso_read_data(uint8_t minute, uint8_t second, uint8_t frame, int buffer)
{
  unsigned int lba;
  int dst;
  int size;
  char *src;
  char *cached_dst;
  unsigned int dwords;
  char *tail_dst;
  char *tail_src;
  char tail_size;
  unsigned int sector_size;
  unsigned int offset;
  unsigned int cache_size;
  size_t read_size;
  char *copy_dst;
  int header;

  lba = cdr_msf_to_lba(minute, second, frame);
  if ( subchannel_file_handle )
  {
    fseek(subchannel_file_handle, 96 * lba, 0);
    fread(subchannel_buffer, 1u, 0x60u, subchannel_file_handle);
    subchannel_msf_minute = minute;
    subchannel_msf_second = second;
    subchannel_msf_frame = frame;
  }
  if ( lba < iso_cache_start_lba || lba >= iso_cache_start_lba + 8 )
  {
    sector_size = iso_sector_size;
    offset = lba * iso_sector_size;
    cache_size = 8 * iso_sector_size;
    if ( lba * iso_sector_size < iso_file_size
      && (offset < iso_file_size - cache_size ? (read_size = 8 * iso_sector_size) : (read_size = iso_file_size - offset), read_size) )
    {
      fseek(iso_file_handle, iso_data_start_offset + offset, 0);
      fread(iso_sector_buffer, 1u, read_size, iso_file_handle);
      sector_size = iso_sector_size;
    }
    else
    {
      memset(iso_sector_buffer, 0, 4 * (cache_size >> 2));
    }
    dst = buffer;
    iso_cache_start_lba = lba;
    copy_dst = (char *)(buffer - sector_size + 2352);
    qmemcpy(copy_dst, iso_sector_buffer, 4 * (sector_size >> 2));
    tail_src = &iso_sector_buffer[4 * (sector_size >> 2)];
    tail_dst = &copy_dst[4 * (sector_size >> 2)];
    tail_size = sector_size;
  }
  else
  {
    dst = buffer;
    size = iso_sector_size;
    src = &iso_sector_buffer[iso_sector_size * (lba - iso_cache_start_lba)];
    cached_dst = (char *)(buffer - iso_sector_size + 2352);
    dwords = (unsigned int)iso_sector_size >> 2;
    qmemcpy(cached_dst, src, 4 * ((unsigned int)iso_sector_size >> 2));
    tail_src = &src[4 * dwords];
    tail_dst = &cached_dst[4 * dwords];
    tail_size = size;
  }
  qmemcpy(tail_dst, tail_src, tail_size & 3);
  header = *(uint32_t *)(dst + 13);
  if ( !header )
  {
    *(uint8_t *)(dst + 15) = 2;
    *(uint8_t *)(dst + 12) = minute % 10 + 16 * (minute / 10);
    *(uint8_t *)(dst + 13) = second % 10 + 16 * (second / 10);
    header = (uint8_t)(frame % 10 + 16 * (frame / 10));
    *(uint8_t *)(dst + 14) = header;
  }
  return header;
}

int iso_close()
{
  if ( iso_file_handle )
    _close((int)iso_file_handle);
  if ( subchannel_file_handle )
    _close((int)subchannel_file_handle);
  return dbg_print(" * Closing ISO system. \n");
}
