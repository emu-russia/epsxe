#include "pch.h"

/* Decompiled globals (previously generated in src/_gen) */
static unsigned int audio_buffer_delay = 0x1;
static unsigned int audio_buffer_size_bytes = 0x4800;
static unsigned int audio_sample_rate_mode = 0x3;
static unsigned int audio_stereo_flag = 0x1;
static unsigned char spu_gauss_kernel[10] = {0x1b, 0xe8, 0xea, 0x8a, 0xbb, 0xf6, 0xb0, 0x51, 0x19, 0xf1};
static unsigned char spu_gauss_table;
static unsigned char spu_xa_decoded_pcm[0x8004];
static unsigned char spu_dsound_write_cursor;
static unsigned char spu_xa_play_data[0x8000];
static unsigned char spu_output_samples[0x200];
static unsigned char spu_dsound_wave_format_ptr[0x14];
static unsigned int spu_adsr_attack_rate_table[9] = {0x1c3c00, 0x1c3c00, 0x1c3c00, 0x1c3c00, 0x1c3c00, 0x17be00, 0x13f6f8, 0x10c9cb, 0xe1e00};
static unsigned int spu_adsr_decay_rate_table[6] = {0x31b343, 0x1ddace, 0x11ef00, 0xac5cb, 0x67898, 0x3e31b};
static unsigned int spu_adsr_sustain_rate_table[6] = {0x5f8e2c, 0x505a27, 0x43915e, 0x38d14b, 0x2fc716, 0x282d13};
static unsigned int spu_adsr_sustain_level_table[6] = {0xfffff, 0x1fffff, 0x2fffff, 0x3fffff, 0x4fffff, 0x5fffff};
static unsigned int spu_adsr_release_rate_table[8] = {0x6666, 0x6666, 0x3333, 0x2222, 0x1999, 0x147a, 0x1111, 0xea0};
static unsigned int spu_xa_playback_rate = 0x1;
static unsigned int spu_adpcm_coeffs_a[1] = {0x0};
static unsigned int spu_adpcm_coeffs_b[9] = {0x0, 0x3c, 0x0, 0x73, 0xffffffcc, 0x62, 0xffffffc9, 0x7a, 0xffffffc4};
static unsigned int spu_ctrl_status;
static unsigned int spu_stereo_flag;
static unsigned int spu_dsound_play_cursor;
static unsigned int spu_reverb_enable;
unsigned int spu_xa_decode_buf_ptr[1];
static unsigned int spu_xa_stereo_flag;
unsigned int spu_xa_samples_left;
static unsigned int spu_enable;
static unsigned int spu_sample_rate_mode;
static unsigned int spu_output_samples_end[0x7f];
static unsigned int spu_ram_transfer_addr;
static unsigned int spu_dsound_desc_size;
static unsigned int spu_dsound_desc_flags;
static unsigned int spu_dsound_desc_buffer_bytes;
unsigned int spu_mute_flag;
static unsigned int spu_dsound_buffer_pos;
static unsigned int spu_irq_pending_flag;
static unsigned int spu_irq_counter;
static unsigned int spu_xa_playback_pos;
unsigned int spu_dma_mem_addr;
unsigned int spu_dma_block_size_count;
static unsigned int flt_4F75AC;
static unsigned int lock_ptr1;
static unsigned int lock_ptr2;
static unsigned int lock_size1;
static unsigned int lock_size2;
static unsigned int pDSBuffer = 0x0;
static unsigned int ppDS;
unsigned char spu_ram[0x80000];
static unsigned int spu_ram_ptr;
static SPU_VOICE_PARAM spu_voice_param[24];
static unsigned int spucore_init_flag;
static unsigned short spucore_mainvol_left;
static unsigned int spucore_mainvol_right;
static unsigned int spucore_noise_mode;
static unsigned int spucore_output_buffer;
static unsigned int spucore_pitchmod_enable;
static unsigned short spucore_reverb_vol_left;
static unsigned short spucore_reverb_vol_right;
static unsigned char temp_samples[0x1c20];
static unsigned short spu_dma_ctrl;
static unsigned short spu_cd_volume_left;
static unsigned short spu_cd_volume_right;
static unsigned short spu_xa_play_pcm[1];
static unsigned short spu_cnt;
static unsigned short spu_ext_volume_left;
static unsigned short spu_ext_volume_right;
static unsigned short spu_adpcm_error_count;


/* static prototypes for internal functions */
static unsigned int spucore_generate_samples();

static int spucore_init_dsound()
{
  int buffer_size;
  int sample_rate;
  int16_t wave_format_tag;

  spu_sample_rate_mode = audio_sample_rate_mode;
  spu_stereo_flag = audio_stereo_flag;
  if ( DirectSoundCreate(nullptr, (LPDIRECTSOUND *)&ppDS, nullptr) )
    return 0;
  ((LPDIRECTSOUND)ppDS)->lpVtbl->SetCooperativeLevel((LPDIRECTSOUND)ppDS, hOutputWnd, 1);
  wave_format_tag = 1;
  switch ( audio_sample_rate_mode )
  {
    case 0:
      buffer_size = 2048;
      sample_rate = 8000;
      audio_buffer_size_bytes = 2048;
      break;
    case 1:
      buffer_size = 2048;
      audio_buffer_size_bytes = 2048;
      goto LABEL_11;
    case 2:
      buffer_size = 4096;
      sample_rate = 22050;
      audio_buffer_size_bytes = 4096;
      break;
    case 3:
      buffer_size = 0x2000;
      sample_rate = 44100;
      audio_buffer_size_bytes = 0x2000;
      break;
    case 4:
      buffer_size = 4096;
      sample_rate = 16000;
      audio_buffer_size_bytes = 4096;
      break;
    case 5:
      buffer_size = 0x2000;
      sample_rate = 32000;
      audio_buffer_size_bytes = 0x2000;
      break;
    case 6:
      buffer_size = 0x2000;
      sample_rate = 48000;
      audio_buffer_size_bytes = 0x2000;
      break;
    default:
      buffer_size = audio_buffer_size_bytes;
LABEL_11:
      sample_rate = 11025;
      break;
  }
  if ( audio_stereo_flag == 1 )
  {
    buffer_size *= 2;
    audio_buffer_size_bytes = buffer_size;
  }
  memset(&spu_dsound_desc_size, 0, 0x24u);
  spu_dsound_desc_buffer_bytes = buffer_size;
  spu_dsound_desc_size = 36;
  spu_dsound_desc_flags = 16392;
  *(uint32_t *)spu_dsound_wave_format_ptr = &wave_format_tag;
  if ( ((LPDIRECTSOUND)ppDS)->lpVtbl->CreateSoundBuffer((LPDIRECTSOUND)ppDS, (LPCDSBUFFERDESC)&spu_dsound_desc_size, (LPDIRECTSOUNDBUFFER *)&pDSBuffer, nullptr)
    || ((LPDIRECTSOUNDBUFFER)pDSBuffer)->lpVtbl->Play((LPDIRECTSOUNDBUFFER)pDSBuffer, 0, 0, 1) )
  {
    return 0;
  }
  audio_buffer_delay = 0;
  return 1;
}

static int spucore_update_dsound()
{
  int ret;
  DWORD lock_offset;
  int bytes_pending;
  int mute;
  char *dst;
  int *src;
  int sample;
  char *lock2_ptr;
  char tail_size;
  unsigned int lock2_words;
  char *src2;

  if ( spu_irq_pending_flag == 1 )
  {
    ret = ++spu_irq_counter;
    spu_irq_pending_flag = (unsigned int)spu_irq_counter <= 0x40;
  }
  else
  {
    spu_irq_counter = 0;
    ((LPDIRECTSOUNDBUFFER)pDSBuffer)->lpVtbl->GetCurrentPosition((LPDIRECTSOUNDBUFFER)pDSBuffer, (LPDWORD)&spu_dsound_play_cursor, (LPDWORD)&spu_dsound_write_cursor);
    lock_offset = spu_dsound_buffer_pos;
    ret = spu_dsound_play_cursor;
    if ( spu_dsound_buffer_pos > (unsigned int)spu_dsound_play_cursor )
    {
      bytes_pending = spu_dsound_play_cursor + audio_buffer_size_bytes - spu_dsound_buffer_pos;
    }
    else
    {
      ret = spu_dsound_play_cursor - spu_dsound_buffer_pos;
      bytes_pending = spu_dsound_play_cursor - spu_dsound_buffer_pos;
    }
    for ( ; bytes_pending >= 256; bytes_pending -= 256 )
    {
      if ( spu_irq_pending_flag == 1 )
        break;
      mute = spu_mute_flag;
      if ( !spu_mute_flag )
      {
        spucore_generate_samples();
        lock_offset = spu_dsound_buffer_pos;
        mute = spu_mute_flag;
      }
      dst = temp_samples;
      src = &spucore_output_buffer;
      do
      {
        *(uint16_t *)dst = *(uint16_t *)src;
        sample = *src;
        if ( *src > 0x7FFF )
          *(uint16_t *)dst = 0x7FFF;
        if ( sample < -32767 )
          *(uint16_t *)dst = -32767;
        if ( mute )
          *(uint16_t *)dst = 0;
        ++src;
        dst += 2;
      }
      while ( (int)src < (int)&spu_output_samples[508] );
      ret = ((LPDIRECTSOUNDBUFFER)pDSBuffer)->lpVtbl->Lock(
               (LPDIRECTSOUNDBUFFER)pDSBuffer,
               lock_offset,
               256,
               (LPVOID *)&lock_ptr1,
               (LPDWORD)&lock_size1,
               (LPVOID *)&lock_ptr2,
               (LPDWORD)&lock_size2,
               0);
      if ( ret )
        break;
      qmemcpy((void *)lock_ptr1, temp_samples, lock_size1);
      lock2_ptr = (char *)lock_ptr2;
      if ( lock_ptr2 )
      {
        tail_size = lock_size2;
        lock2_words = (unsigned int)lock_size2 >> 2;
        src2 = (char *)(2 * lock_size1 + 4602128);
        qmemcpy((void *)lock_ptr2, src2, 4 * ((unsigned int)lock_size2 >> 2));
        qmemcpy(&lock2_ptr[4 * lock2_words], &src2[4 * lock2_words], tail_size & 3);
        lock2_ptr = (char *)lock_ptr2;
      }
      ret = ((LPDIRECTSOUNDBUFFER)pDSBuffer)->lpVtbl->Unlock((LPDIRECTSOUNDBUFFER)pDSBuffer, (LPVOID)lock_ptr1, lock_size1, lock2_ptr, lock_size2);
      if ( ret )
        break;
      ret = audio_buffer_size_bytes;
      lock_offset = spu_dsound_buffer_pos + 256;
      spu_dsound_buffer_pos += 256;
      if ( spu_dsound_buffer_pos >= (unsigned int)audio_buffer_size_bytes )
      {
        lock_offset = 0;
        spu_dsound_buffer_pos = 0;
      }
    }
  }
  return ret;
}

static int spucore_init_gauss_table()
{
  int i;
  int j;
  char *dst;
  int count;
  int inner;
  char value;

  i = 0;
  j = 0;
  dst = spu_gauss_table;
  count = 256;
  do
  {
    inner = 128;
    do
    {
      value = spu_gauss_kernel[(uint8_t)i++] + spu_gauss_kernel[(uint8_t)j--];
      *dst++ = value;
      --inner;
    }
    while ( inner );
    --j;
    --count;
  }
  while ( count );
  return j;
}

static int spucore_voice_key_on(int voice)
{
  uint32_t adsr_sustain_dir;

  adsr_sustain_dir = spu_voice_param[voice].adsr_sustain_dir;
  spu_voice_param[voice].current_block_addr = 1;
  spu_voice_param[voice].sample_history[1] = 0;
  spu_voice_param[voice].sample_history[2] = adsr_sustain_dir;
  spu_voice_param[voice].adpcm_s0 = 0;
  spu_voice_param[voice].unknown3E = 0;
  return voice * 296;
}

static int spucore_voice_key_off(int voice)
{
  int ret;

  ret = 296 * voice;
  if ( spu_voice_param[voice].current_block_addr )
  {
    spu_voice_param[voice].current_block_addr = 4;
  }
  else
  {
    spu_voice_param[voice].unknown17 = 0;
    spu_voice_param[voice].sample_history[1] = 0;
  }
  return ret;
}

static uint8_t spucore_decode_adpcm_block(int voice)
{
  uint16_t status;
  int32_t address;
  char flags;
  int next_addr;
  uint32_t pitch_multiplier;
  uint8_t header;
  int coeff_index;
  uint8_t ret;
  int16_t adpcm_byte;
  int sample1;
  int history_index;
  int32_t prev_sample;
  int sample2;
  int coeff_b;
  uint8_t index;
  int coeff_a;
  char shift;
  int32_t saved_addr;

  status = spu_ctrl_status;
  address = spu_voice_param[voice].sample_history[2];
  flags = BYTE1(spu_ram[2 * address]);
  saved_addr = address;
  if ( (uint16_t)spu_ctrl_status == address && (spu_cnt & 0x40) != 0 && !spu_irq_pending_flag )
  {
    spu_irq_pending_flag = 1;
    irq_spu_registered_callback();
    status = spu_ctrl_status;
  }
  if ( status == spu_voice_param[voice].sample_history[2] + 1 && (spu_cnt & 0x40) != 0 && !spu_irq_pending_flag )
  {
    spu_irq_pending_flag = 1;
    irq_spu_registered_callback();
    status = spu_ctrl_status;
  }
  next_addr = spu_voice_param[voice].sample_history[2] + 2;
  spu_voice_param[voice].sample_history[2] = next_addr;
  spu_voice_param[voice].unknown3E = 1;
  if ( (flags & 1) == 0 || (pitch_multiplier = spu_voice_param[voice].pitch_multiplier) == 0 || status != pitch_multiplier )
  {
    switch ( flags )
    {
      case 1:
      case 7:
        spu_voice_param[voice].unknown3E = 2;
        ret = 0;
        goto LABEL_26;
      case 3:
        spu_voice_param[voice].sample_history[2] = spu_voice_param[voice].pitch_multiplier;
        break;
      case 6:
        spu_voice_param[voice].pitch_multiplier = next_addr - 2;
        break;
      default:
        break;
    }
  }
  else
  {
    spu_voice_param[voice].sample_history[2] = pitch_multiplier;
  }
  header = spu_ram[2 * address];
  coeff_index = 2 * (header >> 4);
  coeff_a = spu_adpcm_coeffs_a[coeff_index];
  index = 0;
  coeff_b = spu_adpcm_coeffs_b[coeff_index];
  shift = header & 0xF;
  while ( 1 )
  {
    adpcm_byte = *((uint8_t *)&spu_ram[2 * address] + index + 2);
    sample1 = ((int16_t)(adpcm_byte << 12) >> shift)
        + (coeff_a * spu_voice_param[voice].sample_history[3] + coeff_b * spu_voice_param[voice].sample_history[4]) / 64;
    if ( sample1 > 0x7FFF )
      break;
    if ( sample1 < -32768 )
      break;
    spu_voice_param[voice].sample_history[4] = spu_voice_param[voice].sample_history[3];
    spu_voice_param[voice].sample_history[3] = sample1;
    history_index = 2 * (index + 37 * voice);
    spu_voice_param[0].sample_history[history_index + 5] = sample1;
    prev_sample = spu_voice_param[voice].sample_history[3];
    sample2 = ((int16_t)((adpcm_byte & 0xFFF0) << 8) >> shift) + (coeff_a * prev_sample + coeff_b * spu_voice_param[voice].sample_history[4]) / 64;
    if ( sample2 > 0x7FFF || sample2 < -32768 )
      break;
    spu_voice_param[voice].sample_history[3] = sample2;
    spu_voice_param[voice].sample_history[4] = prev_sample;
    spu_voice_param[0].sample_history[history_index + 6] = sample2;
    ret = ++index;
    if ( index >= 0xEu )
      return ret;
    address = saved_addr;
  }
  ret = 0;
  ++spu_adpcm_error_count;
LABEL_26:
  memset(&spu_voice_param[voice].sample_history[5], 0, 0x70u);
  return ret;
}

static unsigned int spucore_generate_samples()
{
  int xa_count;
  int16_t play_count;
  int limit;
  double pos_accum;
  char *dst;
  int pcm_index;
  int pcm_sample;
  int data_sample;
  int mono_sample;
  int16_t *voice_ptr;
  unsigned int ret;
  unsigned int vol_left;
  unsigned int vol_right;
  int attack_env;
  int decay_env;
  int sustain_level;
  int sustain_env;
  bool is_key_on;
  int voice_vol;
  int vol_l;
  int release_env;
  int vol_r_raw;
  int vol_r;
  char *out;
  unsigned int sample_pos;
  int block_status;
  int32_t sample;
  int out_l;
  int out_r;
  int pos;
  int voice;
  float pos_step;
  int voice_offset;

  xa_count = spu_xa_samples_left;
  play_count = HIWORD(spu_xa_playback_pos);
  limit = SHIWORD(spu_xa_playback_pos);
  pos_step = (double)spu_xa_playback_rate * 0.00002267573696145125;
  if ( spu_xa_samples_left | SHIWORD(spu_xa_playback_pos) )
  {
    pos_accum = flt_4F75AC;
    dst = spu_output_samples;
    if ( spu_xa_stereo_flag )
    {
      do
      {
        LOWORD(spu_xa_playback_pos) = (int64_t)pos_accum;
        if ( (uint16_t)spu_xa_playback_pos >= limit && play_count > 0 )
        {
          if ( !xa_count )
            spu_xa_playback_rate -= 250;
          if ( 2 * xa_count > 0 )
            qmemcpy(spu_xa_play_pcm, spu_xa_decoded_pcm, 4 * ((unsigned int)(2 * xa_count) >> 1));
          pos_accum = 0.0;
          play_count = xa_count;
          xa_count = 0;
          spu_xa_samples_left = 0;
          LOWORD(spu_xa_playback_pos) = 0;
        }
        limit = play_count;
        if ( (uint16_t)spu_xa_playback_pos >= play_count )
        {
          *((uint32_t *)dst - 1) = 0;
          *(uint32_t *)dst = 0;
        }
        else
        {
          pos_accum = pos_accum + pos_step;
          pcm_index = 2 * (spu_xa_playback_pos & 0x3FFE);
          pcm_sample = spu_xa_play_pcm[pcm_index];
          data_sample = spu_xa_play_data[pcm_index];
          *((uint32_t *)dst - 1) = pcm_sample;
          *(uint32_t *)dst = data_sample;
        }
        dst += 8;
      }
      while ( (int)dst < (int)spu_output_samples_end );
      flt_4F75AC = pos_accum;
      HIWORD(spu_xa_playback_pos) = play_count;
    }
    else
    {
      do
      {
        LOWORD(spu_xa_playback_pos) = (int64_t)pos_accum;
        if ( (uint16_t)spu_xa_playback_pos >= 2 * limit && play_count > 0 )
        {
          if ( !xa_count )
            spu_xa_playback_rate -= 250;
          if ( 2 * xa_count > 0 )
            qmemcpy(spu_xa_play_pcm, spu_xa_decoded_pcm, 4 * ((unsigned int)(2 * xa_count) >> 1));
          pos_accum = 0.0;
          play_count = xa_count;
          xa_count = 0;
          spu_xa_samples_left = 0;
          LOWORD(spu_xa_playback_pos) = 0;
        }
        limit = play_count;
        if ( (uint16_t)spu_xa_playback_pos >= 2 * play_count )
        {
          *((uint32_t *)dst - 1) = 0;
          *(uint32_t *)dst = 0;
        }
        else
        {
          pos_accum = pos_accum + pos_step;
          mono_sample = spu_xa_play_pcm[spu_xa_playback_pos & 0x3FFF];
          *((uint32_t *)dst - 1) = mono_sample;
          *(uint32_t *)dst = mono_sample;
        }
        dst += 8;
      }
      while ( (int)dst < (int)spu_output_samples_end );
      flt_4F75AC = pos_accum;
      HIWORD(spu_xa_playback_pos) = play_count;
    }
  }
  else
  {
    memset(&spucore_output_buffer, 0, 0x200u);
  }
  voice = 0;
  voice_offset = 0;
  for ( voice_ptr = (uint16_t *)(spu_voice_param + 94); (int)voice_ptr < 4616542; voice_ptr += 148 )
  {
    ret = *(uint32_t *)(voice_ptr + 3);
    if ( ret && (((unsigned int)spucore_pitchmod_enable >> (voice + 1)) & 1) == 0 )
    {
      vol_left = ((unsigned int)(uint16_t)spucore_mainvol_left * *(uint32_t *)(voice_ptr - 47)) >> 20;
      vol_right = ((unsigned int)(uint16_t)spucore_mainvol_right * *(uint32_t *)(voice_ptr - 45)) >> 20;
      switch ( ret )
      {
        case 1u:
          attack_env = (*(uint32_t *)(voice_ptr + 91) << 6) + *(uint32_t *)(voice_ptr - 1);
          *(uint32_t *)(voice_ptr - 1) = attack_env;
          if ( attack_env >= 0xFFFFFF )
          {
            *(uint32_t *)(voice_ptr - 1) = 0xFFFFFF;
            *(uint32_t *)(voice_ptr + 3) = 2;
          }
          break;
        case 2u:
          decay_env = (*(uint32_t *)(voice_ptr + 93) << 6) + *(uint32_t *)(voice_ptr - 1);
          sustain_level = *(uint32_t *)(voice_ptr + 95);
          *(uint32_t *)(voice_ptr - 1) = decay_env;
          if ( decay_env <= sustain_level )
          {
            *(uint32_t *)(voice_ptr - 1) = sustain_level;
            *(uint32_t *)(voice_ptr + 3) = 3;
          }
          break;
        case 3u:
          sustain_env = *(uint32_t *)(voice_ptr - 1) + (*(uint32_t *)(voice_ptr + 97) << 6);
          is_key_on = *(uint32_t *)(voice_ptr - 9) == 1;
          *(uint32_t *)(voice_ptr - 1) = sustain_env;
          if ( is_key_on )
          {
            if ( sustain_env <= 0 )
            {
              *(uint32_t *)(voice_ptr - 1) = 0;
              *(uint32_t *)(voice_ptr + 3) = 0;
            }
          }
          else if ( sustain_env >= 0xFFFFFF )
          {
            *(uint32_t *)(voice_ptr + 3) = 5;
            *(uint32_t *)(voice_ptr - 1) = 0xFFFFFF;
          }
          break;
        case 4u:
          release_env = (*(uint32_t *)(voice_ptr + 99) << 6) + *(uint32_t *)(voice_ptr - 1);
          *(uint32_t *)(voice_ptr - 1) = release_env;
          if ( release_env <= 0 )
          {
            *(uint32_t *)(voice_ptr - 1) = 0;
            *(uint32_t *)(voice_ptr + 3) = 0;
          }
          break;
        case 5u:
          *(uint32_t *)(voice_ptr - 1) = 0xFFFFFF;
          break;
        default:
          break;
      }
      voice_vol = *voice_ptr;
      if ( *(uint32_t *)(voice_ptr - 39) )
        vol_l = 0xFFFF - vol_left * voice_vol;
      else
        vol_l = vol_left * voice_vol;
      vol_r_raw = vol_right * voice_vol;
      if ( *(uint32_t *)(voice_ptr - 37) )
        vol_r = 0xFFFF - vol_r_raw;
      else
        vol_r = vol_r_raw;
      out = spu_output_samples;
      do
      {
        if ( !*(uint32_t *)(voice_ptr + 77) )
        {
          do
          {
            sample_pos = *(uint32_t *)(voice_ptr + 7);
            if ( sample_pos > 0x1BFFFF )
            {
              do
                sample_pos -= 1835008;
              while ( sample_pos > 0x1BFFFF );
              *(uint32_t *)(voice_ptr + 77) = 0;
              *(uint32_t *)(voice_ptr + 7) = sample_pos;
            }
            spucore_decode_adpcm_block(voice);
            block_status = *(uint32_t *)(voice_ptr + 77);
            if ( block_status == 2 )
              *(uint32_t *)(voice_ptr + 3) = 0;
          }
          while ( !block_status );
        }
        sample = spu_voice_param[0].sample_history[(uint16_t)voice_ptr[8] + 5 + voice_offset];
        out_l = ((vol_l * sample) >> 16) + *((uint32_t *)out - 1);
        out_r = ((vol_r * sample) >> 16) + *(uint32_t *)out;
        pos = *(uint32_t *)(voice_ptr + 7);
        *((uint32_t *)out - 1) = out_l;
        ret = *(uint32_t *)(voice_ptr + 11) + pos;
        *(uint32_t *)out = out_r;
        *(uint32_t *)(voice_ptr + 7) = ret;
        if ( ret > 0x1BFFFF )
        {
          ret -= 0x1C0000;
          *(uint32_t *)(voice_ptr + 77) = 0;
          *(uint32_t *)(voice_ptr + 7) = ret;
        }
        out += 8;
      }
      while ( (int)out < (int)spu_output_samples_end );
    }
    if ( !*(uint32_t *)(voice_ptr + 3) )
      *(uint32_t *)(voice_ptr - 1) = 0;
    ++voice;
    voice_offset += 74;
  }
  return ret;
}

static int spucore_set_voiceon(unsigned int voice_bits)
{
  int i;
  int ret;

  for ( i = 0; i < 24; ++i )
  {
    if ( (voice_bits & 1) != 0 )
      ret = spucore_voice_key_on(i);
    voice_bits >>= 1;
  }
  return ret;
}

static int spucore_set_pitchmod(unsigned int voice_bits)
{
  int i;
  int ret;

  for ( i = 0; i < 24; ++i )
  {
    if ( (voice_bits & 1) != 0 )
      ret = spucore_voice_key_off(i);
    voice_bits >>= 1;
  }
  return ret;
}

static int16_t spucore_write_cnt(int16_t value)
{
  spu_cnt = value;
  return value;
}

static int16_t spucore_write_dma_ctrl(int16_t value)
{
  spu_dma_ctrl = value;
  return value;
}

static int spucore_write_status_hi(int16_t value)
{
  HIWORD(spu_ctrl_status) = value & 0xF800;
  return value & 0xF800;
}

static int spucore_set_dma_address(uint16_t address)
{
  int byte_addr;

  byte_addr = 8 * address;
  spu_ram_transfer_addr = byte_addr;
  return byte_addr;
}

static int spucore_dma_write_fifo(int16_t value)
{
  int addr;
  int next_addr;

  addr = spu_ram_transfer_addr;
  *(uint16_t *)((char *)spu_ram + spu_ram_transfer_addr) = value;
  next_addr = (addr + 2) & 0x7FFFF;
  spu_ram_transfer_addr = next_addr;
  return next_addr;
}

static int16_t spucore_dma_read_fifo()
{
  int16_t value;

  value = *(uint16_t *)((char *)spu_ram + spu_ram_transfer_addr);
  spu_ram_transfer_addr = (spu_ram_transfer_addr + 2) & 0x7FFFF;
  return value;
}

static int16_t spucore_read_cnt()
{
  return spu_cnt;
}

static int16_t spucore_read_dma_ctrl()
{
  return spu_dma_ctrl;
}

static int16_t spucore_read_status_hi()
{
  return HIWORD(spu_ctrl_status);
}

static int spucore_write_voice_reg(int voice, int reg, uint16_t value)
{
  int64_t scratch;
  double sustain_vol;
  int decay_shift;
  int sustain_idx;
  uint32_t sustain_val;
  int sustain_shift;
  int release_shift;
  bool sustain_inc;
  uint32_t release_rate;
  int64_t sustain_level;

  LODWORD(scratch) = reg;
  switch ( reg )
  {
    case 0:
      spu_voice_param[voice].volume_left = value & 0x3FFF;
      HIDWORD(scratch) = (value >> 14) & 1;
      spu_voice_param[voice].adsr_lower = HIDWORD(scratch);
      spu_voice_param[voice].current_adsr_vol = HIDWORD(scratch);
      spu_voice_param[voice].adsr_attack_mode = (value >> 13) & 1;
      LODWORD(scratch) = value & 0x7F;
      spu_voice_param[voice].adsr_attack_step = value >> 15;
      spu_voice_param[voice].pitch = scratch;
      break;
    case 2:
      spu_voice_param[voice].volume_right = value & 0x3FFF;
      HIDWORD(scratch) = (value >> 14) & 1;
      spu_voice_param[voice].adsr_upper = HIDWORD(scratch);
      spu_voice_param[voice].repeat_addr = HIDWORD(scratch);
      spu_voice_param[voice].adsr_attack_shift = (value >> 13) & 1;
      LODWORD(scratch) = value & 0x7F;
      spu_voice_param[voice].adsr_decay_shift = value >> 15;
      spu_voice_param[voice].start_addr = scratch;
      break;
    case 4:
      sustain_level = value & 0x3FFF;
      spu_voice_param[voice].adsr_sustain_mode = sustain_level;
      sustain_vol = (double)sustain_level * 0.000244140625;
      *(float *)(voice * 296 + 4609456) = sustain_vol;
      scratch = (int64_t)(sustain_vol * 65536.0);
      spu_voice_param[voice].sample_history[0] = scratch;
      break;
    case 6:
      spu_voice_param[voice].adsr_sustain_dir = value;
      LODWORD(scratch) = value;
      break;
    case 8:
      LODWORD(scratch) = 296 * voice;
      *(uint32_t *)((char *)&spu_voice_param[0].adsr_sustain_shift + scratch) = value >> 15;
      HIDWORD(scratch) = HIBYTE(value) & 0x7F;
      *(uint32_t *)((char *)&spu_voice_param[0].adsr_sustain_step + scratch) = HIDWORD(scratch);
      decay_shift = (uint8_t)value >> 4;
      sustain_idx = value & 0xF;
      *(int32_t *)((char *)&spu_voice_param[0].pitch_mod_param + scratch) = spu_adsr_attack_rate_table[HIDWORD(scratch)];
      HIDWORD(scratch) = spu_adsr_decay_rate_table[decay_shift];
      *(uint32_t *)((char *)&spu_voice_param[0].adsr_release_mode + scratch) = sustain_idx;
      sustain_val = spu_adsr_sustain_level_table[sustain_idx];
      *(uint32_t *)((char *)&spu_voice_param[0].adsr_sustain_level + scratch) = decay_shift;
      *(int32_t *)((char *)&spu_voice_param[0].pitch_mod_param2 + scratch) = -HIDWORD(scratch);
      *(uint32_t *)((char *)&spu_voice_param[0].unknown47 + scratch) = sustain_val;
      break;
    case 10:
      LODWORD(scratch) = 296 * voice;
      *(uint32_t *)((char *)&spu_voice_param[0].adsr_release_shift + scratch) = value >> 15;
      HIDWORD(scratch) = (value >> 14) & 1;
      sustain_shift = (value >> 6) & 0x7F;
      release_shift = value & 0x1F;
      *(uint32_t *)((char *)&spu_voice_param[0].adsr_envelope + scratch) = HIDWORD(scratch);
      *(uint32_t *)((char *)&spu_voice_param[0].voice_state + scratch) = (value >> 5) & 1;
      sustain_inc = HIDWORD(scratch) == 0;
      HIDWORD(scratch) = spu_adsr_sustain_rate_table[sustain_shift];
      *(uint32_t *)((char *)&spu_voice_param[0].loop_start_addr + scratch) = sustain_shift;
      *(uint32_t *)((char *)&spu_voice_param[0].pitch_mod_factor + scratch) = release_shift;
      if ( !sustain_inc )
        HIDWORD(scratch) = -HIDWORD(scratch);
      release_rate = -spu_adsr_release_rate_table[release_shift];
      spu_voice_param[voice].unknown48 = HIDWORD(scratch);
      spu_voice_param[voice].unknown49 = release_rate;
      break;
    case 12:
      spu_voice_param[voice].unknown17 = value << 9;
      LODWORD(scratch) = 296 * voice;
      break;
    case 14:
      spu_voice_param[voice].pitch_multiplier = value;
      break;
    default:
      return scratch;
  }
  return scratch;
}

static int16_t spucore_read_voice_reg(int voice, int reg)
{
  int ret;
  signed int unknown17;
  uint32_t *p_unknown17;

  switch ( reg )
  {
    case 4:
      LOWORD(ret) = (int64_t)(*(float *)&spu_voice_param[voice].adpcm_s1 * 4096.0) & 0x3FFF;
      break;
    case 6:
      LOWORD(ret) = spu_voice_param[voice].adsr_sustain_dir;
      break;
    case 12:
      if ( unknown_cd_setting )
      {
        LOWORD(ret) = rand() & 1;
      }
      else
      {
        unknown17 = spu_voice_param[voice].unknown17;
        p_unknown17 = &spu_voice_param[voice].unknown17;
        if ( unknown17 <= 0xFFFFFF )
        {
          if ( unknown17 < 0 )
            *p_unknown17 = 0;
          return (int)*p_unknown17 >> 9;
        }
        else
        {
          *p_unknown17 = 0xFFFFFF;
          return (int)*p_unknown17 >> 9;
        }
      }
      break;
    default:
      LOWORD(ret) = 0;
      break;
  }
  return ret;
}

int spucore_init()
{
  int inited;
  int ret;

  dbg_print(" * Init core spu ... ");
  spu_ram_ptr = (int)spu_ram;
  spucore_init_gauss_table();
  inited = spucore_init_dsound();
  if ( forcespu == 1 )
    forcespu = 0;
  spu_xa_samples_left = 0;
  if ( !inited )
  {
    dbg_print("Error: can't open sound handler.\n");
    fatal_error_with_message_box(" * Error can't open sound handler. (try -nosound)\n");
  }
  ret = dbg_print(" ok \n");
  spucore_init_flag = 1;
  return ret;
}

int spucore_destroy()
{
  int ret;

  ret = spucore_init_flag;
  if ( spucore_init_flag )
  {
    ((LPDIRECTSOUNDBUFFER)pDSBuffer)->lpVtbl->Stop((LPDIRECTSOUNDBUFFER)pDSBuffer);
    while ( ((LPDIRECTSOUNDBUFFER)pDSBuffer)->lpVtbl->Release((LPDIRECTSOUNDBUFFER)pDSBuffer) )
      ;
    while ( ((LPDIRECTSOUND)ppDS)->lpVtbl->Release((LPDIRECTSOUND)ppDS) )
      ;
    return dbg_print(" * Closing core spu...\n");
  }
  return ret;
}

void spucore_dma()
{
  unsigned int addr;
  int block_count;
  int block_size;
  int *src;
  int word_count;
  int dst;
  unsigned int end_addr;
  int total_words;
  int halfwords_left;
  uint16_t fifo;

  addr = spu_dma_mem_addr;
  block_count = HIWORD(spu_dma_block_size_count);
  block_size = (uint16_t)spu_dma_block_size_count;
  if ( sound_enabled )
  {
    spu_irq_pending_flag = 0;
    if ( *(uint32_t *)spu_dma_chcr_ptr == 0x1000200 )
    {
      total_words = HIWORD(spu_dma_block_size_count) * (uint16_t)spu_dma_block_size_count;
      if ( 2 * total_words )
      {
        halfwords_left = 2 * total_words;
        do
        {
          fifo = spucore_dma_read_fifo();
          mem_hw_reg_write_half(addr, fifo);
          addr += 2;
          --halfwords_left;
        }
        while ( halfwords_left );
      }
      if ( dynarec_enabled == 1 && total_words )
        dynarec_invalidate_range(spu_dma_mem_addr, total_words);
    }
    else if ( *(uint32_t *)spu_dma_chcr_ptr == 0x1000201 )
    {
      src = (int *)mem_dma_read(spu_dma_mem_addr);
      word_count = block_count * block_size;
      dst = spu_ram_transfer_addr;
      end_addr = 4 * word_count + spu_ram_transfer_addr;
      if ( end_addr >= 0x80000 )
      {
        for ( ; word_count; spu_ram_transfer_addr = dst )
        {
          *(int *)((char *)spu_ram + dst) = *src;
          dst = (dst + 4) & 0x7FFFF;
          ++src;
          --word_count;
        }
      }
      else
      {
        qmemcpy((char *)spu_ram + spu_ram_transfer_addr, src, 4 * ((unsigned int)(4 * word_count) >> 2));
        spu_ram_transfer_addr = end_addr;
      }
    }
    else if ( (*(uint32_t *)spu_dma_chcr_ptr & 0x1000000) != 0 )
    {
      fatal_error_with_message_box(
        "DMA[4] mode NOT implemented (%08x)\n addr (%08x) num (%04x) size (%04x)\n",
        *(uint32_t *)spu_dma_chcr_ptr,
        spu_dma_mem_addr,
        HIWORD(spu_dma_block_size_count),
        (uint16_t)spu_dma_block_size_count);
    }
  }
}

int16_t spucore_write_register(int16_t address, int16_t value)
{
  unsigned int offset;
  int16_t ret;

  offset = (address & 0xFFF) - 3072;
  spu_irq_pending_flag = 0;
  if ( offset < 0x180 )
    return spucore_write_voice_reg(offset >> 4, address & 0xF, value);
  ret = (address & 0xFFF) - 3456;
  switch ( address & 0xFFF )
  {
    case 0xD80:
      spucore_mainvol_left = value & 0x3FFF;
      break;
    case 0xD82:
      LOWORD(spucore_mainvol_right) = value & 0x3FFF;
      ret = value & 0x3FFF;
      break;
    case 0xD84:
      spucore_reverb_vol_left = value;
      break;
    case 0xD86:
      spucore_reverb_vol_right = value;
      break;
    case 0xD88:
      ret = spucore_set_voiceon((uint16_t)value);
      break;
    case 0xD8A:
      ret = spucore_set_voiceon((uint16_t)value << 16);
      break;
    case 0xD8C:
      ret = spucore_set_pitchmod((uint16_t)value);
      break;
    case 0xD8E:
      ret = spucore_set_pitchmod((uint16_t)value << 16);
      break;
    case 0xD90:
      spucore_pitchmod_enable = (uint16_t)value + (spucore_pitchmod_enable & 0xFF0000);
      break;
    case 0xD92:
      ret = spucore_pitchmod_enable;
      spucore_pitchmod_enable = (uint16_t)spucore_pitchmod_enable + ((uint16_t)value << 16);
      break;
    case 0xD94:
      spucore_noise_mode = (uint16_t)value + (spucore_noise_mode & 0xFF0000);
      ret = value;
      break;
    case 0xD96:
      spucore_noise_mode = (uint16_t)spucore_noise_mode + ((uint16_t)value << 16);
      break;
    case 0xD98:
      spu_reverb_enable = (uint16_t)value + (spu_reverb_enable & 0xFF0000);
      ret = value;
      break;
    case 0xD9A:
      ret = spu_reverb_enable;
      spu_reverb_enable = (uint16_t)spu_reverb_enable + ((uint16_t)value << 16);
      break;
    case 0xD9C:
      spu_enable = (uint16_t)value + (spu_enable & 0xFF0000);
      break;
    case 0xD9E:
      ret = spu_enable;
      spu_enable = (uint16_t)spu_enable + ((uint16_t)value << 16);
      break;
    case 0xDA2:
      spu_xa_play_data[0x3FFF] = value;
      break;
    case 0xDA4:
      LOWORD(spu_ctrl_status) = value;
      ret = value;
      break;
    case 0xDA6:
      ret = spucore_set_dma_address(value);
      break;
    case 0xDA8:
      ret = spucore_dma_write_fifo(value);
      break;
    case 0xDAA:
      ret = spucore_write_cnt(value);
      break;
    case 0xDAC:
      ret = spucore_write_dma_ctrl(value);
      break;
    case 0xDAE:
      ret = spucore_write_status_hi(value);
      break;
    case 0xDB0:
      spu_cd_volume_left = value;
      ret = value;
      break;
    case 0xDB2:
      spu_cd_volume_right = value;
      break;
    case 0xDB4:
      spu_ext_volume_left = value;
      break;
    case 0xDB6:
      spu_ext_volume_right = value;
      ret = value;
      break;
    default:
      return ret;
  }
  return ret;
}

int16_t spucore_read_register(int16_t address)
{
  unsigned int offset;
  unsigned int value;

  offset = (address & 0xFFF) - 3072;
  spu_irq_pending_flag = 0;
  if ( offset >= 0x180 )
  {
    switch ( address & 0xFFF )
    {
      case 0xD80:
        LOWORD(value) = spucore_mainvol_left;
        break;
      case 0xD82:
        LOWORD(value) = spucore_mainvol_right;
        break;
      case 0xD84:
        LOWORD(value) = spucore_reverb_vol_left;
        break;
      case 0xD86:
        LOWORD(value) = spucore_reverb_vol_right;
        break;
      case 0xD90:
        LOWORD(value) = spucore_pitchmod_enable;
        break;
      case 0xD92:
        LOWORD(value) = HIWORD(spucore_pitchmod_enable);
        break;
      case 0xD94:
        LOWORD(value) = spucore_noise_mode;
        break;
      case 0xD96:
        LOWORD(value) = HIWORD(spucore_noise_mode);
        break;
      case 0xD98:
        LOWORD(value) = spu_reverb_enable;
        break;
      case 0xD9A:
        LOWORD(value) = HIWORD(spu_reverb_enable);
        break;
      case 0xD9C:
        LOWORD(value) = spu_enable;
        break;
      case 0xD9E:
        LOWORD(value) = HIWORD(spu_enable);
        break;
      case 0xDA2:
        LOWORD(value) = spu_xa_play_data[0x3FFF];
        break;
      case 0xDA4:
        LOWORD(value) = spu_ctrl_status;
        break;
      case 0xDA6:
        value = (unsigned int)spu_ram_transfer_addr >> 3;
        break;
      case 0xDA8:
        LOWORD(value) = spucore_dma_read_fifo();
        break;
      case 0xDAA:
        LOWORD(value) = spucore_read_cnt();
        break;
      case 0xDAC:
        LOWORD(value) = spucore_read_dma_ctrl();
        break;
      case 0xDAE:
        LOWORD(value) = spucore_read_status_hi();
        break;
      case 0xDB0:
        LOWORD(value) = spu_cd_volume_left;
        break;
      case 0xDB2:
        LOWORD(value) = spu_cd_volume_right;
        break;
      case 0xDB4:
        LOWORD(value) = spu_ext_volume_left;
        break;
      case 0xDB6:
        LOWORD(value) = spu_ext_volume_right;
        break;
      default:
        LOWORD(value) = 0;
        break;
    }
  }
  else
  {
    LOWORD(value) = spucore_read_voice_reg(offset >> 4, address & 0xF);
  }
  return value;
}

char spucore_play_adpcm(int pcm_addr)
{
  char ret;
  int samples;

  ret = sound_enabled;
  if ( sound_enabled )
  {
    ret = sound_use_xa;
    if ( sound_use_xa )
    {
      if ( xa_decode_wrapper(spu_xa_decode_buf_ptr, pcm_addr, spu_adpcm_flag) )
      {
        samples = spu_xa_samples_left;
      }
      else
      {
        samples = 2016;
        spu_xa_samples_left = 2016;
      }
      ret = spu_xa_decode_buf_ptr[0];
      if ( spu_adpcm_flag == 1 )
        spu_xa_playback_rate = *(uint32_t *)spu_xa_decode_buf_ptr;
      spu_adpcm_flag = 0;
      if ( HIWORD(spu_xa_playback_pos) )
      {
        if ( spu_xa_playback_rate < *(int *)spu_xa_decode_buf_ptr )
        {
          ret = spu_xa_playback_rate - 6;
          spu_xa_playback_rate += 250;
        }
      }
      else
      {
        if ( 2 * samples > 0 )
          qmemcpy(spu_xa_play_pcm, spu_xa_decoded_pcm, 4 * ((unsigned int)(2 * samples) >> 1));
        HIWORD(spu_xa_playback_pos) = samples;
        spu_xa_samples_left = 0;
      }
    }
  }
  return ret;
}


int spucore_update_thunk()
{
  return spucore_update_dsound();
}

int spucore_freeze(const char *filename, int file)
{
  int reg_value;
  char *dst;
  uint32_t *p_adsr_lower;
  int voice_count;
  int reg;
  int reg_count;
  int prev_value;
  int vol_reg;
  int vol_reg2;
  int adsr_reg;
  int16_t tmp;
  int16_t vol_left;
  int16_t vol_right;
  uint8_t pitchmod_hi;
  int16_t *dst2;
  int index;
  int count;
  uint32_t *saved_ptr;
  char Buffer[384];
  char reg_area;

  sprintf(Buffer, "%s", filename);
  *(uint32_t *)&Buffer[3] = 564744;
  gzwrite(file, (uint8_t *)Buffer, 7u);
  sprintf(Buffer, "ISPU");
  gzwrite(file, (uint8_t *)Buffer, 8u);
  *(uint64_t *)Buffer = 0x89DF800000002LL;
  gzwrite(file, (uint8_t *)Buffer, 8u);
  dst = &Buffer[2];
  p_adsr_lower = &spu_voice_param[0].adsr_lower;
  voice_count = 24;
  do
  {
    reg = 0;
    reg_count = 8;
    do
    {
      prev_value = reg_value;
      reg_value = 0;
      switch ( reg )
      {
        case 0:
          vol_reg = 2 * (uint16_t)(*(uint16_t *)p_adsr_lower | (2 * *((uint16_t *)p_adsr_lower + 12)));
          LOWORD(vol_reg) = *((uint16_t *)p_adsr_lower + 8) | vol_reg;
          reg_value = vol_reg << 13;
          LOWORD(reg_value) = *((uint16_t *)p_adsr_lower - 8) | reg_value;
          *((uint16_t *)dst - 1) = reg_value;
          break;
        case 2:
          vol_reg2 = 2 * (uint16_t)(*((uint16_t *)p_adsr_lower + 2) | (2 * *((uint16_t *)p_adsr_lower + 14)));
          LOWORD(vol_reg2) = *((uint16_t *)p_adsr_lower + 10) | vol_reg2;
          reg_value = vol_reg2 << 13;
          LOWORD(reg_value) = *((uint16_t *)p_adsr_lower - 6) | reg_value;
          *(uint16_t *)dst = reg_value;
          break;
        case 4:
          LOWORD(reg_value) = *((uint16_t *)p_adsr_lower + 16);
          *((uint16_t *)dst + 1) = reg_value;
          break;
        case 6:
          LOWORD(reg_value) = *((uint16_t *)p_adsr_lower + 18);
          *((uint16_t *)dst + 2) = reg_value;
          break;
        case 8:
          adsr_reg = 16 * (uint16_t)(*((uint16_t *)p_adsr_lower + 22) | (*((uint16_t *)p_adsr_lower + 20) << 7));
          LOWORD(adsr_reg) = *((uint16_t *)p_adsr_lower + 24) | adsr_reg;
          reg_value = 16 * adsr_reg;
          LOWORD(reg_value) = *((uint16_t *)p_adsr_lower + 26) | reg_value;
          *((uint16_t *)dst + 3) = reg_value;
          break;
        case 10:
          LOBYTE(reg_value) = *((uint8_t *)p_adsr_lower + 60) | (2 * *((uint8_t *)p_adsr_lower + 56));
          LOBYTE(tmp) = 0;
          HIBYTE(tmp) = reg_value;
          *((uint16_t *)dst + 4) = *((uint16_t *)p_adsr_lower + 36)
                             | (32 * (*((uint16_t *)p_adsr_lower + 34) | (2 * (*((uint16_t *)p_adsr_lower + 32) | tmp))));
          break;
        case 12:
          reg_value = (int)p_adsr_lower[19] >> 9;
          *((uint16_t *)dst + 5) = reg_value;
          break;
        case 14:
          LOWORD(reg_value) = *((uint16_t *)p_adsr_lower + 40);
          *((uint16_t *)dst + 6) = reg_value;
          break;
        default:
          reg_value = prev_value;
          break;
      }
      reg += 2;
      --reg_count;
    }
    while ( reg_count );
    p_adsr_lower += 74;
    dst += 16;
    --voice_count;
  }
  while ( voice_count );
  vol_left = spucore_mainvol_left;
  vol_right = spucore_mainvol_right;
  pitchmod_hi = BYTE2(spucore_pitchmod_enable);
  dst2 = (int16_t *)&reg_area;
  index = 0;
  count = 64;
  do
  {
    saved_ptr = p_adsr_lower;
    p_adsr_lower = nullptr;
    switch ( index )
    {
      case 0:
        *dst2 = vol_left;
        break;
      case 2:
        *dst2 = vol_right;
        break;
      case 4:
        LOWORD(p_adsr_lower) = spucore_reverb_vol_left;
        goto LABEL_37;
      case 6:
        LOWORD(p_adsr_lower) = spucore_reverb_vol_right;
        goto LABEL_37;
      case 16:
        LOWORD(p_adsr_lower) = spucore_pitchmod_enable;
        goto LABEL_37;
      case 18:
        p_adsr_lower = (uint32_t *)pitchmod_hi;
        goto LABEL_37;
      case 20:
        LOWORD(p_adsr_lower) = spucore_noise_mode;
        goto LABEL_37;
      case 22:
        p_adsr_lower = (uint32_t *)BYTE2(spucore_noise_mode);
        goto LABEL_37;
      case 24:
        LOWORD(p_adsr_lower) = spu_reverb_enable;
        goto LABEL_37;
      case 26:
        p_adsr_lower = (uint32_t *)BYTE2(spu_reverb_enable);
        goto LABEL_37;
      case 28:
        LOWORD(p_adsr_lower) = spu_enable;
        goto LABEL_37;
      case 30:
        p_adsr_lower = (uint32_t *)BYTE2(spu_enable);
        goto LABEL_37;
      case 34:
        LOWORD(p_adsr_lower) = spu_xa_play_data[0x3FFF];
        goto LABEL_37;
      case 36:
        LOWORD(p_adsr_lower) = spu_ctrl_status;
        goto LABEL_37;
      case 42:
        LOWORD(p_adsr_lower) = spucore_read_cnt();
        goto LABEL_37;
      case 44:
        LOWORD(p_adsr_lower) = spucore_read_dma_ctrl();
        goto LABEL_37;
      case 46:
        LOWORD(p_adsr_lower) = spucore_read_status_hi();
        goto LABEL_37;
      case 48:
        LOWORD(p_adsr_lower) = spu_cd_volume_left;
        goto LABEL_37;
      case 50:
        LOWORD(p_adsr_lower) = spu_cd_volume_right;
        goto LABEL_37;
      case 52:
        LOWORD(p_adsr_lower) = spu_ext_volume_left;
        goto LABEL_37;
      case 54:
        LOWORD(p_adsr_lower) = spu_ext_volume_right;
LABEL_37:
        *dst2 = (int16_t)p_adsr_lower;
        break;
      default:
        p_adsr_lower = saved_ptr;
        break;
    }
    index += 2;
    ++dst2;
    --count;
  }
  while ( count );
  gzwrite(file, (uint8_t *)Buffer, 0x200u);
  gzwrite(file, (uint8_t *)spu_ram, 0x80000u);
  gzwrite(file, (uint8_t *)spu_xa_decode_buf_ptr, 0x8020u);
  return gzwrite(file, (uint8_t *)spu_voice_param, 0x1BC0u);
}

int spucore_unfreeze(int unused, uint32_t *file)
{
  char *src;
  uint32_t *p_adsr_lower;
  unsigned int reg;
  uint16_t vol_reg;
  int sweep;
  int volume;
  uint16_t vol_reg2;
  int sweep2;
  double sustain_level;
  double sustain_vol;
  uint16_t adsr_reg;
  char flags;
  int attack_idx;
  int decay_idx;
  int attack_rate;
  int decay_rate;
  int sustain_idx;
  int sustain_val;
  uint16_t sustain_reg;
  int sustain_dir;
  int sustain_shift;
  int release_mode;
  int release_shift;
  int release_rate;
  int sustain_rate;
  int pitchmod_val;
  int noise_val;
  int reverb_val;
  int enable_val;
  int16_t *regs;
  int index;
  int ret;
  int voice_count;
  int count;
  int reg_count;
  int envelope;
  char magic[12];
  char buffer[384];
  char reg_area;

  gzread(file, buffer, 7);
  gzread(file, magic, 8);
  gzread(file, buffer, 8);
  gzread(file, buffer, 512);
  src = buffer;
  p_adsr_lower = &spu_voice_param[0].adsr_lower;
  voice_count = 24;
  do
  {
    reg = 0;
    reg_count = 8;
    do
    {
      if ( reg <= 0xE )
      {
        switch ( reg )
        {
          case 0u:
            vol_reg = *(uint16_t *)src;
            sweep = (*(uint16_t *)src >> 14) & 1;
            volume = *(uint16_t *)src & 0x3FFF;
            *p_adsr_lower = sweep;
            p_adsr_lower[2] = sweep;
            *(p_adsr_lower - 4) = volume;
            p_adsr_lower[4] = (vol_reg >> 13) & 1;
            p_adsr_lower[6] = vol_reg >> 15;
            *(p_adsr_lower - 2) = vol_reg & 0x7F;
            break;
          case 1u:
          case 3u:
          case 5u:
          case 7u:
          case 9u:
          case 0xBu:
          case 0xDu:
            break;
          case 2u:
            vol_reg2 = *((uint16_t *)src + 1);
            *(p_adsr_lower - 3) = vol_reg2 & 0x3FFF;
            sweep2 = (vol_reg2 >> 14) & 1;
            p_adsr_lower[1] = sweep2;
            p_adsr_lower[3] = sweep2;
            p_adsr_lower[5] = (vol_reg2 >> 13) & 1;
            p_adsr_lower[7] = vol_reg2 >> 15;
            *(p_adsr_lower - 1) = vol_reg2 & 0x7F;
            break;
          case 4u:
            sustain_level = (double)(*((uint16_t *)src + 2) & 0x3FFF);
            p_adsr_lower[8] = *((uint16_t *)src + 2) & 0x3FFF;
            sustain_vol = sustain_level * 0.000244140625;
            *((float *)p_adsr_lower + 24) = sustain_vol;
            p_adsr_lower[25] = (int64_t)(sustain_vol * 65536.0);
            break;
          case 6u:
            p_adsr_lower[9] = *((uint16_t *)src + 3);
            break;
          case 8u:
            adsr_reg = *((uint16_t *)src + 4);
            flags = src[9];
            p_adsr_lower[10] = adsr_reg >> 15;
            attack_idx = flags & 0x7F;
            decay_idx = (uint8_t)adsr_reg >> 4;
            p_adsr_lower[11] = attack_idx;
            attack_rate = spu_adsr_attack_rate_table[attack_idx];
            p_adsr_lower[12] = decay_idx;
            decay_rate = spu_adsr_decay_rate_table[decay_idx];
            sustain_idx = adsr_reg & 0xF;
            p_adsr_lower[65] = attack_rate;
            sustain_val = spu_adsr_sustain_level_table[sustain_idx];
            p_adsr_lower[13] = sustain_idx;
            p_adsr_lower[66] = -decay_rate;
            p_adsr_lower[67] = sustain_val;
            break;
          case 0xAu:
            sustain_reg = *((uint16_t *)src + 5);
            p_adsr_lower[14] = sustain_reg >> 15;
            sustain_dir = (sustain_reg >> 14) & 1;
            sustain_shift = (sustain_reg >> 6) & 0x7F;
            release_mode = (sustain_reg >> 5) & 1;
            release_shift = sustain_reg & 0x1F;
            p_adsr_lower[15] = sustain_dir;
            p_adsr_lower[16] = sustain_shift;
            p_adsr_lower[17] = release_mode;
            p_adsr_lower[18] = release_shift;
            if ( sustain_dir )
            {
              sustain_rate = -spu_adsr_sustain_rate_table[sustain_shift];
              release_rate = -spu_adsr_release_rate_table[release_shift];
              p_adsr_lower[68] = sustain_rate;
            }
            else
            {
              p_adsr_lower[68] = spu_adsr_sustain_rate_table[sustain_shift];
              release_rate = -spu_adsr_release_rate_table[release_shift];
            }
            p_adsr_lower[69] = release_rate;
            break;
          case 0xCu:
            envelope = *((uint16_t *)src + 6) << 9;
            p_adsr_lower[19] = envelope;
            *((float *)p_adsr_lower + 26) = (double)envelope * 0.000030517578125;
            break;
          case 0xEu:
            p_adsr_lower[20] = *((uint16_t *)src + 7);
            break;
        }
      }
      reg += 2;
      --reg_count;
    }
    while ( reg_count );
    src += 16;
    p_adsr_lower += 74;
    --voice_count;
  }
  while ( voice_count );
  pitchmod_val = spucore_pitchmod_enable;
  noise_val = spucore_noise_mode;
  reverb_val = spu_reverb_enable;
  enable_val = spu_enable;
  regs = (int16_t *)&reg_area;
  index = 0;
  count = 64;
  do
  {
    switch ( index )
    {
      case 0:
        spucore_mainvol_left = *regs;
        break;
      case 2:
        LOWORD(spucore_mainvol_right) = *regs;
        break;
      case 4:
        spucore_reverb_vol_left = *regs;
        break;
      case 6:
        spucore_reverb_vol_right = *regs;
        break;
      case 16:
        pitchmod_val = (uint16_t)*regs;
        break;
      case 18:
        pitchmod_val = ((uint16_t)*regs << 16) + (uint16_t)pitchmod_val;
        break;
      case 20:
        noise_val = (uint16_t)*regs;
        break;
      case 22:
        noise_val = ((uint16_t)*regs << 16) + (uint16_t)noise_val;
        break;
      case 24:
        reverb_val = (uint16_t)*regs;
        break;
      case 26:
        reverb_val = ((uint16_t)*regs << 16) + (uint16_t)reverb_val;
        break;
      case 28:
        enable_val = (uint16_t)*regs;
        break;
      case 30:
        enable_val = ((uint16_t)*regs << 16) + (uint16_t)enable_val;
        break;
      case 34:
        spu_xa_play_data[0x3FFF] = *regs;
        break;
      case 36:
        LOWORD(spu_ctrl_status) = *regs;
        break;
      case 42:
        spucore_write_cnt(*regs);
        break;
      case 44:
        spucore_write_dma_ctrl(*regs);
        break;
      case 46:
        spucore_write_status_hi(*regs);
        break;
      case 48:
        spu_cd_volume_left = *regs;
        break;
      case 50:
        spu_cd_volume_right = *regs;
        break;
      case 52:
        spu_ext_volume_left = *regs;
        break;
      case 54:
        spu_ext_volume_right = *regs;
        break;
      default:
        break;
    }
    index += 2;
    ++regs;
    --count;
  }
  while ( count );
  spu_reverb_enable = reverb_val;
  spu_enable = enable_val;
  spucore_noise_mode = noise_val;
  spucore_pitchmod_enable = pitchmod_val;
  gzread(file, (char *)spu_ram, 0x80000);
  gzread(file, spu_xa_decode_buf_ptr, 32800);
  spu_xa_playback_rate = *(uint32_t *)spu_xa_decode_buf_ptr;
  if ( spu_xa_samples_left > 4096 )
    spu_xa_samples_left = 0;
  ret = strncmp(magic, "ISPU", 4u);
  if ( !ret )
    return gzread(file, (char *)spu_voice_param, 7104);
  return ret;
}
