#include "pch.h"
int spucore_init_dsound()
{
  int v0; // edx
  int v1; // eax
  __int16 v3; // [esp+Ch] [ebp-14h] BYREF
  __int16 v4; // [esp+Eh] [ebp-12h]
  int v5; // [esp+10h] [ebp-10h]
  int v6; // [esp+14h] [ebp-Ch]
  unsigned __int16 v7; // [esp+18h] [ebp-8h]
  __int16 v8; // [esp+1Ah] [ebp-6h]
  __int16 v9; // [esp+1Ch] [ebp-4h]

  dword_4F7148 = audio_sample_rate_mode;
  dword_465530 = audio_stereo_flag;
  if ( DirectSoundCreate(nullptr, &ppDS, nullptr) )
    return 0;
  ppDS->lpVtbl->SetCooperativeLevel(ppDS, hOutputWnd, 1);
  v3 = 1;
  switch ( audio_sample_rate_mode )
  {
    case 0:
      v0 = 2048;
      v1 = 8000;
      audio_buffer_size_bytes = 2048;
      break;
    case 1:
      v0 = 2048;
      audio_buffer_size_bytes = 2048;
      goto LABEL_11;
    case 2:
      v0 = 4096;
      v1 = 22050;
      audio_buffer_size_bytes = 4096;
      break;
    case 3:
      v0 = 0x2000;
      v1 = 44100;
      audio_buffer_size_bytes = 0x2000;
      break;
    case 4:
      v0 = 4096;
      v1 = 16000;
      audio_buffer_size_bytes = 4096;
      break;
    case 5:
      v0 = 0x2000;
      v1 = 32000;
      audio_buffer_size_bytes = 0x2000;
      break;
    case 6:
      v0 = 0x2000;
      v1 = 48000;
      audio_buffer_size_bytes = 0x2000;
      break;
    default:
      v0 = audio_buffer_size_bytes;
LABEL_11:
      v1 = 11025;
      break;
  }
  v5 = v1;
  if ( audio_stereo_flag == 1 )
  {
    v0 *= 2;
    v4 = 2;
    v7 = 4;
    audio_buffer_size_bytes = v0;
  }
  else
  {
    v4 = 1;
    v7 = 2;
  }
  v8 = 16;
  v6 = v1 * v7;
  memset(&dword_4F7560, 0, 0x24u);
  dword_4F7568 = v0;
  v9 = 0;
  dword_4F7560 = 36;
  dword_4F7564 = 16392;
  *(_DWORD *)byte_4F7570 = &v3;
  if ( ppDS->lpVtbl->CreateSoundBuffer(ppDS, (LPCDSBUFFERDESC)&dword_4F7560, &pDSBuffer, nullptr)
    || pDSBuffer->lpVtbl->Play(pDSBuffer, 0, 0, 1) )
  {
    return 0;
  }
  audio_buffer_delay = 0;
  return 1;
}

int spucore_update_dsound()
{
  int result; // eax
  DWORD v1; // esi
  int v2; // ebx
  int v3; // edi
  char *v4; // ecx
  int *v5; // eax
  int v6; // edx
  char *v7; // edi
  char v8; // dl
  unsigned int v9; // ecx
  char *v10; // esi

  if ( dword_4F75A0 == 1 )
  {
    result = ++dword_4F75A4;
    dword_4F75A0 = (unsigned int)dword_4F75A4 <= 0x40;
  }
  else
  {
    dword_4F75A4 = 0;
    pDSBuffer->lpVtbl->GetCurrentPosition(pDSBuffer, (LPDWORD)&dword_465534, (LPDWORD)&byte_4EF134);
    v1 = dword_4F7598;
    result = dword_465534;
    if ( dword_4F7598 > (unsigned int)dword_465534 )
    {
      v2 = dword_465534 + audio_buffer_size_bytes - dword_4F7598;
    }
    else
    {
      result = dword_465534 - dword_4F7598;
      v2 = dword_465534 - dword_4F7598;
    }
    for ( ; v2 >= 256; v2 -= 256 )
    {
      if ( dword_4F75A0 == 1 )
        break;
      v3 = dword_4F7594;
      if ( !dword_4F7594 )
      {
        spucore_generate_samples();
        v1 = dword_4F7598;
        v3 = dword_4F7594;
      }
      v4 = temp_samples;
      v5 = &spucore_output_buffer;
      do
      {
        *(_WORD *)v4 = *(_WORD *)v5;
        v6 = *v5;
        if ( *v5 > 0x7FFF )
          *(_WORD *)v4 = 0x7FFF;
        if ( v6 < -32767 )
          *(_WORD *)v4 = -32767;
        if ( v3 )
          *(_WORD *)v4 = 0;
        ++v5;
        v4 += 2;
      }
      while ( (int)v5 < (int)&byte_4F7154[508] );
      result = pDSBuffer->lpVtbl->Lock(
                 pDSBuffer,
                 v1,
                 256,
                 (LPVOID *)&lock_ptr1,
                 (LPDWORD)&lock_size1,
                 (LPVOID *)&lock_ptr2,
                 (LPDWORD)&lock_size2,
                 0);
      if ( result )
        break;
      qmemcpy((void *)lock_ptr1, temp_samples, lock_size1);
      v7 = (char *)lock_ptr2;
      if ( lock_ptr2 )
      {
        v8 = lock_size2;
        v9 = (unsigned int)lock_size2 >> 2;
        v10 = (char *)(2 * lock_size1 + 4602128);
        qmemcpy((void *)lock_ptr2, v10, 4 * ((unsigned int)lock_size2 >> 2));
        qmemcpy(&v7[4 * v9], &v10[4 * v9], v8 & 3);
        v7 = (char *)lock_ptr2;
      }
      result = pDSBuffer->lpVtbl->Unlock(pDSBuffer, (LPVOID)lock_ptr1, lock_size1, v7, lock_size2);
      if ( result )
        break;
      result = audio_buffer_size_bytes;
      v1 = dword_4F7598 + 256;
      dword_4F7598 += 256;
      if ( dword_4F7598 >= (unsigned int)audio_buffer_size_bytes )
      {
        v1 = 0;
        dword_4F7598 = 0;
      }
    }
  }
  return result;
}

int spucore_init_gauss_table()
{
  int v0; // ecx
  int result; // eax
  char *v2; // esi
  int v3; // ebp
  int v4; // edi
  char v5; // dl

  v0 = 0;
  result = 0;
  v2 = byte_45B900;
  v3 = 256;
  do
  {
    v4 = 128;
    do
    {
      v5 = byte_44F720[(unsigned __int8)v0++] + byte_44F720[(unsigned __int8)result--];
      *v2++ = v5;
      --v4;
    }
    while ( v4 );
    --result;
    --v3;
  }
  while ( v3 );
  return result;
}

int __cdecl spucore_voice_key_on(int a1)
{
  int result; // eax
  int v2; // edx

  result = 74 * a1;
  v2 = dword_465574[74 * a1];
  dword_4655A4[result] = 1;
  dword_4655B8[result] = 0;
  dword_4655BC[result] = v2;
  dword_4655AC[result] = 0;
  dword_465638[result] = 0;
  return result * 4;
}

int __cdecl spucore_voice_key_off(int a1)
{
  int result; // eax

  result = 296 * a1;
  if ( dword_4655A4[74 * a1] )
  {
    dword_4655A4[74 * a1] = 4;
  }
  else
  {
    dword_46559C[74 * a1] = 0;
    dword_4655B8[74 * a1] = 0;
  }
  return result;
}

char __cdecl spucore_decode_adpcm_block(int a1)
{
  unsigned __int16 v1; // cx
  int v2; // edi
  char v3; // bl
  int v4; // edx
  int v5; // eax
  unsigned __int8 v6; // cl
  int v7; // eax
  char result; // al
  __int16 v9; // di
  int v10; // eax
  int v11; // ebp
  int v12; // ebx
  int v13; // eax
  int v14; // [esp+10h] [ebp-14h]
  unsigned __int8 v15; // [esp+14h] [ebp-10h]
  int v16; // [esp+18h] [ebp-Ch]
  char v17; // [esp+1Ch] [ebp-8h]
  int v18; // [esp+20h] [ebp-4h]

  v1 = dword_463904;
  v2 = dword_4655BC[74 * a1];
  v3 = BYTE1(spu_ram[2 * v2]);
  v18 = v2;
  if ( (unsigned __int16)dword_463904 == v2 && (word_4F7550 & 0x40) != 0 && !dword_4F75A0 )
  {
    dword_4F75A0 = 1;
    irq_spu_registered_callback();
    v1 = dword_463904;
  }
  if ( v1 == dword_4655BC[74 * a1] + 1 && (word_4F7550 & 0x40) != 0 && !dword_4F75A0 )
  {
    dword_4F75A0 = 1;
    irq_spu_registered_callback();
    v1 = dword_463904;
  }
  v4 = dword_4655BC[74 * a1] + 2;
  dword_4655BC[74 * a1] = v4;
  dword_465638[74 * a1] = 1;
  if ( (v3 & 1) == 0 || (v5 = dword_4655A0[74 * a1]) == 0 || v1 != v5 )
  {
    switch ( v3 )
    {
      case 1:
      case 7:
        dword_465638[74 * a1] = 2;
        result = 0;
        goto LABEL_26;
      case 3:
        dword_4655BC[74 * a1] = dword_4655A0[74 * a1];
        goto LABEL_13;
      case 6:
        dword_4655A0[74 * a1] = v4 - 2;
        goto LABEL_13;
      default:
        goto LABEL_13;
    }
  }
  dword_4655BC[74 * a1] = v5;
LABEL_13:
  v6 = spu_ram[2 * v2];
  v7 = 2 * (v6 >> 4);
  v16 = dword_44F7A4[v7];
  v15 = 0;
  v14 = dword_44F7A8[v7];
  v17 = v6 & 0xF;
  while ( 1 )
  {
    v9 = *((unsigned __int8 *)&spu_ram[2 * v2] + v15 + 2);
    v10 = ((__int16)(v9 << 12) >> v17) + (v16 * dword_4655C0[74 * a1] + v14 * dword_4655C4[74 * a1]) / 64;
    if ( v10 > 0x7FFF )
      break;
    if ( v10 < -32768 )
      break;
    dword_4655C4[74 * a1] = dword_4655C0[74 * a1];
    dword_4655C0[74 * a1] = v10;
    v11 = 2 * (v15 + 37 * a1);
    dword_4655C8[v11] = v10;
    v12 = dword_4655C0[74 * a1];
    v13 = ((__int16)((v9 & 0xFFF0) << 8) >> v17) + (v16 * v12 + v14 * dword_4655C4[74 * a1]) / 64;
    if ( v13 > 0x7FFF || v13 < -32768 )
      break;
    dword_4655C0[74 * a1] = v13;
    dword_4655C4[74 * a1] = v12;
    dword_4655CC[v11] = v13;
    result = ++v15;
    if ( v15 >= 0xEu )
      return result;
    v2 = v18;
  }
  result = 0;
  ++word_4F75B4;
LABEL_26:
  memset(&dword_4655C8[74 * a1], 0, 0x70u);
  return result;
}

unsigned int spucore_generate_samples()
{
  int v0; // ebp
  __int16 v1; // di
  int v2; // esi
  double v3; // st7
  char *v4; // ebx
  int v5; // eax
  int v6; // edx
  int v7; // eax
  int v8; // eax
  __int16 *i; // esi
  unsigned int result; // eax
  unsigned int v11; // ecx
  unsigned int v12; // edx
  int v13; // edi
  int v14; // edi
  int v15; // eax
  int v16; // eax
  bool v17; // zf
  int v18; // eax
  int v19; // ebp
  int v20; // eax
  int v21; // eax
  int v22; // ebx
  char *v23; // edi
  unsigned int v24; // eax
  int v25; // eax
  int v26; // ecx
  int v27; // edx
  int v28; // ecx
  int v29; // eax
  int v30; // [esp+10h] [ebp-8h]
  float v31; // [esp+14h] [ebp-4h]
  int v32; // [esp+14h] [ebp-4h]

  v0 = dword_4E7114;
  v1 = HIWORD(dword_4F75B0);
  v2 = SHIWORD(dword_4F75B0);
  v31 = (double)dword_44F7A0 * 0.00002267573696145125;
  if ( dword_4E7114 | SHIWORD(dword_4F75B0) )
  {
    v3 = flt_4F75AC;
    v4 = byte_4F7154;
    if ( dword_4E7110 )
    {
      do
      {
        LOWORD(dword_4F75B0) = (__int64)v3;
        if ( (unsigned __int16)dword_4F75B0 >= v2 && v1 > 0 )
        {
          if ( !v0 )
            dword_44F7A0 -= 250;
          if ( 2 * v0 > 0 )
            qmemcpy(word_4EF140, byte_4E7128, 4 * ((unsigned int)(2 * v0) >> 1));
          v3 = 0.0;
          v1 = v0;
          v0 = 0;
          dword_4E7114 = 0;
          LOWORD(dword_4F75B0) = 0;
        }
        v2 = v1;
        if ( (unsigned __int16)dword_4F75B0 >= v1 )
        {
          *((_DWORD *)v4 - 1) = 0;
          *(_DWORD *)v4 = 0;
        }
        else
        {
          v3 = v3 + v31;
          v5 = 2 * (dword_4F75B0 & 0x3FFE);
          v6 = word_4EF140[v5];
          v7 = byte_4EF142[v5];
          *((_DWORD *)v4 - 1) = v6;
          *(_DWORD *)v4 = v7;
        }
        v4 += 8;
      }
      while ( (int)v4 < (int)dword_4F7354 );
      flt_4F75AC = v3;
      HIWORD(dword_4F75B0) = v1;
    }
    else
    {
      do
      {
        LOWORD(dword_4F75B0) = (__int64)v3;
        if ( (unsigned __int16)dword_4F75B0 >= 2 * v2 && v1 > 0 )
        {
          if ( !v0 )
            dword_44F7A0 -= 250;
          if ( 2 * v0 > 0 )
            qmemcpy(word_4EF140, byte_4E7128, 4 * ((unsigned int)(2 * v0) >> 1));
          v3 = 0.0;
          v1 = v0;
          v0 = 0;
          dword_4E7114 = 0;
          LOWORD(dword_4F75B0) = 0;
        }
        v2 = v1;
        if ( (unsigned __int16)dword_4F75B0 >= 2 * v1 )
        {
          *((_DWORD *)v4 - 1) = 0;
          *(_DWORD *)v4 = 0;
        }
        else
        {
          v3 = v3 + v31;
          v8 = word_4EF140[dword_4F75B0 & 0x3FFF];
          *((_DWORD *)v4 - 1) = v8;
          *(_DWORD *)v4 = v8;
        }
        v4 += 8;
      }
      while ( (int)v4 < (int)dword_4F7354 );
      flt_4F75AC = v3;
      HIWORD(dword_4F75B0) = v1;
    }
  }
  else
  {
    memset(&spucore_output_buffer, 0, 0x200u);
  }
  v30 = 0;
  v32 = 0;
  for ( i = (_WORD *)(dword_46559C + 2); (int)i < 4616542; i += 148 )
  {
    result = *(_DWORD *)(i + 3);
    if ( result && (((unsigned int)spucore_pitchmod_enable >> (v30 + 1)) & 1) == 0 )
    {
      v11 = ((unsigned int)(unsigned __int16)spucore_mainvol_left * *(_DWORD *)(i - 47)) >> 20;
      v12 = ((unsigned int)(unsigned __int16)spucore_mainvol_right * *(_DWORD *)(i - 45)) >> 20;
      switch ( result )
      {
        case 1u:
          v13 = (*(_DWORD *)(i + 91) << 6) + *(_DWORD *)(i - 1);
          *(_DWORD *)(i - 1) = v13;
          if ( v13 >= 0xFFFFFF )
          {
            *(_DWORD *)(i - 1) = 0xFFFFFF;
            *(_DWORD *)(i + 3) = 2;
          }
          break;
        case 2u:
          v14 = (*(_DWORD *)(i + 93) << 6) + *(_DWORD *)(i - 1);
          v15 = *(_DWORD *)(i + 95);
          *(_DWORD *)(i - 1) = v14;
          if ( v14 <= v15 )
          {
            *(_DWORD *)(i - 1) = v15;
            *(_DWORD *)(i + 3) = 3;
          }
          break;
        case 3u:
          v16 = *(_DWORD *)(i - 1) + (*(_DWORD *)(i + 97) << 6);
          v17 = *(_DWORD *)(i - 9) == 1;
          *(_DWORD *)(i - 1) = v16;
          if ( v17 )
          {
            if ( v16 <= 0 )
            {
              *(_DWORD *)(i - 1) = 0;
              *(_DWORD *)(i + 3) = 0;
            }
          }
          else if ( v16 >= 0xFFFFFF )
          {
            *(_DWORD *)(i + 3) = 5;
            goto LABEL_41;
          }
          break;
        case 4u:
          v20 = (*(_DWORD *)(i + 99) << 6) + *(_DWORD *)(i - 1);
          *(_DWORD *)(i - 1) = v20;
          if ( v20 <= 0 )
          {
            *(_DWORD *)(i - 1) = 0;
            *(_DWORD *)(i + 3) = 0;
          }
          break;
        case 5u:
LABEL_41:
          *(_DWORD *)(i - 1) = 0xFFFFFF;
          break;
        default:
          break;
      }
      v18 = *i;
      if ( *(_DWORD *)(i - 39) )
        v19 = 0xFFFF - v11 * v18;
      else
        v19 = v11 * v18;
      v21 = v12 * v18;
      if ( *(_DWORD *)(i - 37) )
        v22 = 0xFFFF - v21;
      else
        v22 = v21;
      v23 = byte_4F7154;
      do
      {
        if ( !*(_DWORD *)(i + 77) )
        {
          do
          {
            v24 = *(_DWORD *)(i + 7);
            if ( v24 > 0x1BFFFF )
            {
              do
                v24 -= 1835008;
              while ( v24 > 0x1BFFFF );
              *(_DWORD *)(i + 77) = 0;
              *(_DWORD *)(i + 7) = v24;
            }
            spucore_decode_adpcm_block(v30);
            v25 = *(_DWORD *)(i + 77);
            if ( v25 == 2 )
              *(_DWORD *)(i + 3) = 0;
          }
          while ( !v25 );
        }
        v26 = dword_4655C8[(unsigned __int16)i[8] + v32];
        v27 = ((v19 * v26) >> 16) + *((_DWORD *)v23 - 1);
        v28 = ((v22 * v26) >> 16) + *(_DWORD *)v23;
        v29 = *(_DWORD *)(i + 7);
        *((_DWORD *)v23 - 1) = v27;
        result = *(_DWORD *)(i + 11) + v29;
        *(_DWORD *)v23 = v28;
        *(_DWORD *)(i + 7) = result;
        if ( result > 0x1BFFFF )
        {
          result -= 0x1C0000;
          *(_DWORD *)(i + 77) = 0;
          *(_DWORD *)(i + 7) = result;
        }
        v23 += 8;
      }
      while ( (int)v23 < (int)dword_4F7354 );
    }
    if ( !*(_DWORD *)(i + 3) )
      *(_DWORD *)(i - 1) = 0;
    ++v30;
    v32 += 74;
  }
  return result;
}

int __cdecl spucore_set_voiceon(unsigned int a1)
{
  int i; // esi
  int result; // eax

  for ( i = 0; i < 24; ++i )
  {
    if ( (a1 & 1) != 0 )
      result = spucore_voice_key_on(i);
    a1 >>= 1;
  }
  return result;
}

int __cdecl spucore_set_pitchmod(unsigned int a1)
{
  int i; // esi
  int result; // eax

  for ( i = 0; i < 24; ++i )
  {
    if ( (a1 & 1) != 0 )
      result = spucore_voice_key_off(i);
    a1 >>= 1;
  }
  return result;
}

__int16 __cdecl spucore_write_cnt(__int16 a1)
{
  word_4F7550 = a1;
  return a1;
}

__int16 __cdecl spucore_write_dma_ctrl(__int16 a1)
{
  word_46553C = a1;
  return a1;
}

int __cdecl spucore_write_status_hi(__int16 a1)
{
  HIWORD(dword_463904) = a1 & 0xF800;
  return a1 & 0xF800;
}

int __cdecl spucore_set_dma_address(unsigned __int16 a1)
{
  int result; // eax

  result = 8 * a1;
  dword_4F7554 = result;
  return result;
}

int __cdecl spucore_dma_write_fifo(__int16 a1)
{
  int v1; // eax
  int result; // eax

  v1 = dword_4F7554;
  *(_WORD *)((char *)spu_ram + dword_4F7554) = a1;
  result = (v1 + 2) & 0x7FFFF;
  dword_4F7554 = result;
  return result;
}

__int16 spucore_dma_read_fifo()
{
  __int16 result; // ax

  result = *(_WORD *)((char *)spu_ram + dword_4F7554);
  dword_4F7554 = (dword_4F7554 + 2) & 0x7FFFF;
  return result;
}

__int16 spucore_read_cnt()
{
  return word_4F7550;
}

__int16 spucore_read_dma_ctrl()
{
  return word_46553C;
}

__int16 spucore_read_status_hi()
{
  return HIWORD(dword_463904);
}

int __cdecl spucore_write_voice_reg(int a1, int a2, unsigned __int16 a3)
{
  __int64 v3; // rax
  int v4; // ecx
  int v5; // ecx
  int v6; // esi
  double v7; // st7
  int v8; // esi
  int v9; // ecx
  int v10; // ecx
  int v11; // esi
  int v12; // ecx
  bool v13; // zf
  int v14; // ecx
  __int64 v16; // [esp+4h] [ebp-8h]

  LODWORD(v3) = a2;
  switch ( a2 )
  {
    case 0:
      v4 = 74 * a1;
      dword_465540[v4] = a3 & 0x3FFF;
      HIDWORD(v3) = (a3 >> 14) & 1;
      dword_465550[v4] = HIDWORD(v3);
      dword_465558[v4] = HIDWORD(v3);
      dword_465560[v4] = (a3 >> 13) & 1;
      LODWORD(v3) = a3 & 0x7F;
      dword_465568[v4] = a3 >> 15;
      dword_465548[v4] = v3;
      break;
    case 2:
      v5 = 74 * a1;
      dword_465544[v5] = a3 & 0x3FFF;
      HIDWORD(v3) = (a3 >> 14) & 1;
      dword_465554[v5] = HIDWORD(v3);
      dword_46555C[v5] = HIDWORD(v3);
      dword_465564[v5] = (a3 >> 13) & 1;
      LODWORD(v3) = a3 & 0x7F;
      dword_46556C[v5] = a3 >> 15;
      dword_46554C[v5] = v3;
      break;
    case 4:
      v6 = 74 * a1;
      v16 = a3 & 0x3FFF;
      dword_465570[v6] = v16;
      v7 = (double)v16 * 0.000244140625;
      *(float *)(v6 * 4 + 4609456) = v7;
      v3 = (__int64)(v7 * 65536.0);
      dword_4655B4[v6] = v3;
      break;
    case 6:
      dword_465574[74 * a1] = a3;
      LODWORD(v3) = a3;
      break;
    case 8:
      LODWORD(v3) = 296 * a1;
      *(int *)((char *)&dword_465578 + v3) = a3 >> 15;
      HIDWORD(v3) = HIBYTE(a3) & 0x7F;
      *(int *)((char *)&dword_46557C + v3) = HIDWORD(v3);
      v8 = (unsigned __int8)a3 >> 4;
      v9 = a3 & 0xF;
      *(int *)((char *)&dword_465654 + v3) = dword_44F208[HIDWORD(v3)];
      HIDWORD(v3) = dword_44F408[v8];
      *(int *)((char *)&dword_465584 + v3) = v9;
      v10 = dword_44F648[v9];
      *(int *)((char *)&dword_465580 + v3) = v8;
      *(int *)((char *)&dword_465658 + v3) = -HIDWORD(v3);
      *(int *)((char *)&dword_46565C + v3) = v10;
      break;
    case 10:
      LODWORD(v3) = 296 * a1;
      *(int *)((char *)&dword_465588 + v3) = a3 >> 15;
      HIDWORD(v3) = (a3 >> 14) & 1;
      v11 = (a3 >> 6) & 0x7F;
      v12 = a3 & 0x1F;
      *(int *)((char *)&dword_46558C + v3) = HIDWORD(v3);
      *(int *)((char *)&dword_465594 + v3) = (a3 >> 5) & 1;
      v13 = HIDWORD(v3) == 0;
      HIDWORD(v3) = dword_44F448[v11];
      *(int *)((char *)&dword_465590 + v3) = v11;
      *(int *)((char *)&dword_465598 + v3) = v12;
      if ( !v13 )
        HIDWORD(v3) = -HIDWORD(v3);
      v14 = -dword_44F688[v12];
      dword_465660[74 * a1] = HIDWORD(v3);
      dword_465664[74 * a1] = v14;
      break;
    case 12:
      dword_46559C[74 * a1] = a3 << 9;
      LODWORD(v3) = 296 * a1;
      break;
    case 14:
      dword_4655A0[74 * a1] = a3;
      break;
    default:
      return v3;
  }
  return v3;
}

__int16 __cdecl spucore_read_voice_reg(int a1, int a2)
{
  int v2; // eax
  int v3; // ecx
  int *v4; // eax

  switch ( a2 )
  {
    case 4:
      LOWORD(v2) = (__int64)(*(float *)&dword_4655B0[74 * a1] * 4096.0) & 0x3FFF;
      break;
    case 6:
      LOWORD(v2) = dword_465574[74 * a1];
      break;
    case 12:
      if ( unknown_cd_setting )
      {
        LOWORD(v2) = rand() & 1;
      }
      else
      {
        v3 = dword_46559C[74 * a1];
        v4 = &dword_46559C[74 * a1];
        if ( v3 <= 0xFFFFFF )
        {
          if ( v3 < 0 )
            *v4 = 0;
          return *v4 >> 9;
        }
        else
        {
          *v4 = 0xFFFFFF;
          return *v4 >> 9;
        }
      }
      break;
    default:
      LOWORD(v2) = 0;
      break;
  }
  return v2;
}

int spucore_init()
{
  int inited; // eax
  int result; // eax

  dbg_print(" * Init core spu ... ");
  spu_ram_ptr = (int)spu_ram;
  spucore_init_gauss_table();
  inited = spucore_init_dsound();
  if ( forcespu == 1 )
    forcespu = 0;
  dword_4E7114 = 0;
  if ( !inited )
  {
    dbg_print("Error: can't open sound handler.\n");
    fatal_error_with_message_box(" * Error can't open sound handler. (try -nosound)\n");
  }
  result = dbg_print(" ok \n");
  spucore_init_flag = 1;
  return result;
}

int spucore_destroy()
{
  int result; // eax

  result = spucore_init_flag;
  if ( spucore_init_flag )
  {
    pDSBuffer->lpVtbl->Stop(pDSBuffer);
    while ( pDSBuffer->lpVtbl->Release(pDSBuffer) )
      ;
    while ( ppDS->lpVtbl->Release(ppDS) )
      ;
    return dbg_print(" * Closing core spu...\n");
  }
  return result;
}

void spucore_dma()
{
  unsigned int v0; // esi
  int v1; // ebx
  int v2; // edi
  int *v3; // eax
  int v4; // edi
  int v5; // edx
  unsigned int v6; // ebx
  int v7; // edi
  int v8; // ebx
  unsigned __int16 fifo; // ax

  v0 = dword_516510;
  v1 = HIWORD(dword_516514);
  v2 = (unsigned __int16)dword_516514;
  if ( sound_enabled )
  {
    dword_4F75A0 = 0;
    if ( *(_DWORD *)dword_516518 == 0x1000200 )
    {
      v7 = HIWORD(dword_516514) * (unsigned __int16)dword_516514;
      if ( 2 * v7 )
      {
        v8 = 2 * v7;
        do
        {
          fifo = spucore_dma_read_fifo();
          mem_hw_reg_write_half(v0, fifo);
          v0 += 2;
          --v8;
        }
        while ( v8 );
      }
      if ( dynarec_enabled == 1 && v7 )
        dynarec_invalidate_range(dword_516510, v7);
    }
    else if ( *(_DWORD *)dword_516518 == 0x1000201 )
    {
      v3 = (int *)mem_dma_read(dword_516510);
      v4 = v1 * v2;
      v5 = dword_4F7554;
      v6 = 4 * v4 + dword_4F7554;
      if ( v6 >= 0x80000 )
      {
        for ( ; v4; dword_4F7554 = v5 )
        {
          *(int *)((char *)spu_ram + v5) = *v3;
          v5 = (v5 + 4) & 0x7FFFF;
          ++v3;
          --v4;
        }
      }
      else
      {
        qmemcpy((char *)spu_ram + dword_4F7554, v3, 4 * ((unsigned int)(4 * v4) >> 2));
        dword_4F7554 = v6;
      }
    }
    else if ( (*(_DWORD *)dword_516518 & 0x1000000) != 0 )
    {
      fatal_error_with_message_box(
        "DMA[4] mode NOT implemented (%08x)\n addr (%08x) num (%04x) size (%04x)\n",
        *(_DWORD *)dword_516518,
        dword_516510,
        HIWORD(dword_516514),
        (unsigned __int16)dword_516514);
    }
  }
}

__int16 __cdecl spucore_write_register(__int16 a1, unsigned __int16 a2)
{
  unsigned int v2; // eax
  __int16 result; // ax

  v2 = (a1 & 0xFFF) - 3072;
  dword_4F75A0 = 0;
  if ( v2 < 0x180 )
    return spucore_write_voice_reg(v2 >> 4, a1 & 0xF, a2);
  result = (a1 & 0xFFF) - 3456;
  switch ( a1 & 0xFFF )
  {
    case 0xD80:
      spucore_mainvol_left = a2 & 0x3FFF;
      break;
    case 0xD82:
      LOWORD(spucore_mainvol_right) = a2 & 0x3FFF;
      result = a2 & 0x3FFF;
      break;
    case 0xD84:
      spucore_reverb_vol_left = a2;
      break;
    case 0xD86:
      spucore_reverb_vol_right = a2;
      break;
    case 0xD88:
      result = spucore_set_voiceon(a2);
      break;
    case 0xD8A:
      result = spucore_set_voiceon(a2 << 16);
      break;
    case 0xD8C:
      result = spucore_set_pitchmod(a2);
      break;
    case 0xD8E:
      result = spucore_set_pitchmod(a2 << 16);
      break;
    case 0xD90:
      spucore_pitchmod_enable = a2 + (spucore_pitchmod_enable & 0xFF0000);
      break;
    case 0xD92:
      result = spucore_pitchmod_enable;
      spucore_pitchmod_enable = (unsigned __int16)spucore_pitchmod_enable + (a2 << 16);
      break;
    case 0xD94:
      spucore_noise_mode = a2 + (spucore_noise_mode & 0xFF0000);
      result = a2;
      break;
    case 0xD96:
      spucore_noise_mode = (unsigned __int16)spucore_noise_mode + (a2 << 16);
      break;
    case 0xD98:
      dword_4E7100 = a2 + (dword_4E7100 & 0xFF0000);
      result = a2;
      break;
    case 0xD9A:
      result = dword_4E7100;
      dword_4E7100 = (unsigned __int16)dword_4E7100 + (a2 << 16);
      break;
    case 0xD9C:
      dword_4EF138 = a2 + (dword_4EF138 & 0xFF0000);
      break;
    case 0xD9E:
      result = dword_4EF138;
      dword_4EF138 = (unsigned __int16)dword_4EF138 + (a2 << 16);
      break;
    case 0xDA2:
      byte_4EF142[0x3FFF] = a2;
      break;
    case 0xDA4:
      LOWORD(dword_463904) = a2;
      result = a2;
      break;
    case 0xDA6:
      result = spucore_set_dma_address(a2);
      break;
    case 0xDA8:
      result = spucore_dma_write_fifo(a2);
      break;
    case 0xDAA:
      result = spucore_write_cnt(a2);
      break;
    case 0xDAC:
      result = spucore_write_dma_ctrl(a2);
      break;
    case 0xDAE:
      result = spucore_write_status_hi(a2);
      break;
    case 0xDB0:
      word_4E7104 = a2;
      result = a2;
      break;
    case 0xDB2:
      word_4E7106 = a2;
      break;
    case 0xDB4:
      word_4F755C = a2;
      break;
    case 0xDB6:
      word_4F7584 = a2;
      result = a2;
      break;
    default:
      return result;
  }
  return result;
}

__int16 __cdecl spucore_read_register(__int16 a1)
{
  unsigned int v1; // eax
  unsigned int v2; // eax

  v1 = (a1 & 0xFFF) - 3072;
  dword_4F75A0 = 0;
  if ( v1 >= 0x180 )
  {
    switch ( a1 & 0xFFF )
    {
      case 0xD80:
        LOWORD(v2) = spucore_mainvol_left;
        break;
      case 0xD82:
        LOWORD(v2) = spucore_mainvol_right;
        break;
      case 0xD84:
        LOWORD(v2) = spucore_reverb_vol_left;
        break;
      case 0xD86:
        LOWORD(v2) = spucore_reverb_vol_right;
        break;
      case 0xD90:
        LOWORD(v2) = spucore_pitchmod_enable;
        break;
      case 0xD92:
        LOWORD(v2) = HIWORD(spucore_pitchmod_enable);
        break;
      case 0xD94:
        LOWORD(v2) = spucore_noise_mode;
        break;
      case 0xD96:
        LOWORD(v2) = HIWORD(spucore_noise_mode);
        break;
      case 0xD98:
        LOWORD(v2) = dword_4E7100;
        break;
      case 0xD9A:
        LOWORD(v2) = HIWORD(dword_4E7100);
        break;
      case 0xD9C:
        LOWORD(v2) = dword_4EF138;
        break;
      case 0xD9E:
        LOWORD(v2) = HIWORD(dword_4EF138);
        break;
      case 0xDA2:
        LOWORD(v2) = byte_4EF142[0x3FFF];
        break;
      case 0xDA4:
        LOWORD(v2) = dword_463904;
        break;
      case 0xDA6:
        v2 = (unsigned int)dword_4F7554 >> 3;
        break;
      case 0xDA8:
        LOWORD(v2) = spucore_dma_read_fifo();
        break;
      case 0xDAA:
        LOWORD(v2) = spucore_read_cnt();
        break;
      case 0xDAC:
        LOWORD(v2) = spucore_read_dma_ctrl();
        break;
      case 0xDAE:
        LOWORD(v2) = spucore_read_status_hi();
        break;
      case 0xDB0:
        LOWORD(v2) = word_4E7104;
        break;
      case 0xDB2:
        LOWORD(v2) = word_4E7106;
        break;
      case 0xDB4:
        LOWORD(v2) = word_4F755C;
        break;
      case 0xDB6:
        LOWORD(v2) = word_4F7584;
        break;
      default:
        LOWORD(v2) = 0;
        break;
    }
  }
  else
  {
    LOWORD(v2) = spucore_read_voice_reg(v1 >> 4, a1 & 0xF);
  }
  return v2;
}

char __cdecl spucore_play_adpcm(int a1)
{
  char result; // al
  int v2; // edx

  result = sound_enabled;
  if ( sound_enabled )
  {
    result = sound_use_xa;
    if ( sound_use_xa )
    {
      if ( xa_decode_wrapper(dword_4E7108, a1, spu_adpcm_flag) )
      {
        v2 = dword_4E7114;
      }
      else
      {
        v2 = 2016;
        dword_4E7114 = 2016;
      }
      result = dword_4E7108[0];
      if ( spu_adpcm_flag == 1 )
        dword_44F7A0 = *(_DWORD *)dword_4E7108;
      spu_adpcm_flag = 0;
      if ( HIWORD(dword_4F75B0) )
      {
        if ( dword_44F7A0 < *(int *)dword_4E7108 )
        {
          result = dword_44F7A0 - 6;
          dword_44F7A0 += 250;
        }
      }
      else
      {
        if ( 2 * v2 > 0 )
          qmemcpy(word_4EF140, byte_4E7128, 4 * ((unsigned int)(2 * v2) >> 1));
        HIWORD(dword_4F75B0) = v2;
        dword_4E7114 = 0;
      }
    }
  }
  return result;
}

// attributes: thunk
int spucore_update_thunk()
{
  return spucore_update_dsound();
}

int __cdecl spucore_freeze(const char *a1, int a2)
{
  int v2; // edx
  char *v3; // esi
  int *v4; // eax
  int v5; // ecx
  int v6; // edi
  int v7; // ebp
  int v8; // kr08_4
  int v9; // edx
  int v10; // edx
  int v11; // edx
  __int16 v12; // bx
  __int16 v13; // di
  __int16 v14; // bp
  unsigned __int8 v15; // bl
  __int16 *v16; // ecx
  int v17; // edx
  int v18; // esi
  int *v19; // kr10_4
  char Buffer[384]; // [esp+10h] [ebp-200h] BYREF
  char v22; // [esp+190h] [ebp-80h] BYREF

  sprintf(Buffer, "%s", a1);
  *(_DWORD *)&Buffer[3] = 564744;
  gzwrite(a2, (unsigned __int8 *)Buffer, 7u);
  sprintf(Buffer, "ISPU");
  gzwrite(a2, (unsigned __int8 *)Buffer, 8u);
  *(_QWORD *)Buffer = 0x89DF800000002LL;
  gzwrite(a2, (unsigned __int8 *)Buffer, 8u);
  v3 = &Buffer[2];
  v4 = dword_465550;
  v5 = 24;
  do
  {
    v6 = 0;
    v7 = 8;
    do
    {
      v8 = v2;
      v2 = 0;
      switch ( v6 )
      {
        case 0:
          v9 = 2 * (unsigned __int16)(*(_WORD *)v4 | (2 * *((_WORD *)v4 + 12)));
          LOWORD(v9) = *((_WORD *)v4 + 8) | v9;
          v2 = v9 << 13;
          LOWORD(v2) = *((_WORD *)v4 - 8) | v2;
          *((_WORD *)v3 - 1) = v2;
          break;
        case 2:
          v10 = 2 * (unsigned __int16)(*((_WORD *)v4 + 2) | (2 * *((_WORD *)v4 + 14)));
          LOWORD(v10) = *((_WORD *)v4 + 10) | v10;
          v2 = v10 << 13;
          LOWORD(v2) = *((_WORD *)v4 - 6) | v2;
          *(_WORD *)v3 = v2;
          break;
        case 4:
          LOWORD(v2) = *((_WORD *)v4 + 16);
          *((_WORD *)v3 + 1) = v2;
          break;
        case 6:
          LOWORD(v2) = *((_WORD *)v4 + 18);
          *((_WORD *)v3 + 2) = v2;
          break;
        case 8:
          v11 = 16 * (unsigned __int16)(*((_WORD *)v4 + 22) | (*((_WORD *)v4 + 20) << 7));
          LOWORD(v11) = *((_WORD *)v4 + 24) | v11;
          v2 = 16 * v11;
          LOWORD(v2) = *((_WORD *)v4 + 26) | v2;
          *((_WORD *)v3 + 3) = v2;
          break;
        case 10:
          LOBYTE(v2) = *((_BYTE *)v4 + 60) | (2 * *((_BYTE *)v4 + 56));
          LOBYTE(v12) = 0;
          HIBYTE(v12) = v2;
          *((_WORD *)v3 + 4) = *((_WORD *)v4 + 36) | (32 * (*((_WORD *)v4 + 34) | (2 * (*((_WORD *)v4 + 32) | v12))));
          break;
        case 12:
          v2 = v4[19] >> 9;
          *((_WORD *)v3 + 5) = v2;
          break;
        case 14:
          LOWORD(v2) = *((_WORD *)v4 + 40);
          *((_WORD *)v3 + 6) = v2;
          break;
        default:
          v2 = v8;
          break;
      }
      v6 += 2;
      --v7;
    }
    while ( v7 );
    v4 += 74;
    v3 += 16;
    --v5;
  }
  while ( v5 );
  v13 = spucore_mainvol_left;
  v14 = spucore_mainvol_right;
  v15 = BYTE2(spucore_pitchmod_enable);
  v16 = (__int16 *)&v22;
  v17 = 0;
  v18 = 64;
  do
  {
    v19 = v4;
    v4 = nullptr;
    switch ( v17 )
    {
      case 0:
        *v16 = v13;
        break;
      case 2:
        *v16 = v14;
        break;
      case 4:
        LOWORD(v4) = spucore_reverb_vol_left;
        goto LABEL_37;
      case 6:
        LOWORD(v4) = spucore_reverb_vol_right;
        goto LABEL_37;
      case 16:
        LOWORD(v4) = spucore_pitchmod_enable;
        goto LABEL_37;
      case 18:
        v4 = (int *)v15;
        goto LABEL_37;
      case 20:
        LOWORD(v4) = spucore_noise_mode;
        goto LABEL_37;
      case 22:
        v4 = (int *)BYTE2(spucore_noise_mode);
        goto LABEL_37;
      case 24:
        LOWORD(v4) = dword_4E7100;
        goto LABEL_37;
      case 26:
        v4 = (int *)BYTE2(dword_4E7100);
        goto LABEL_37;
      case 28:
        LOWORD(v4) = dword_4EF138;
        goto LABEL_37;
      case 30:
        v4 = (int *)BYTE2(dword_4EF138);
        goto LABEL_37;
      case 34:
        LOWORD(v4) = byte_4EF142[0x3FFF];
        goto LABEL_37;
      case 36:
        LOWORD(v4) = dword_463904;
        goto LABEL_37;
      case 42:
        LOWORD(v4) = spucore_read_cnt();
        goto LABEL_37;
      case 44:
        LOWORD(v4) = spucore_read_dma_ctrl();
        goto LABEL_37;
      case 46:
        LOWORD(v4) = spucore_read_status_hi();
        goto LABEL_37;
      case 48:
        LOWORD(v4) = word_4E7104;
        goto LABEL_37;
      case 50:
        LOWORD(v4) = word_4E7106;
        goto LABEL_37;
      case 52:
        LOWORD(v4) = word_4F755C;
        goto LABEL_37;
      case 54:
        LOWORD(v4) = word_4F7584;
LABEL_37:
        *v16 = (__int16)v4;
        break;
      default:
        v4 = v19;
        break;
    }
    v17 += 2;
    ++v16;
    --v18;
  }
  while ( v18 );
  gzwrite(a2, (unsigned __int8 *)Buffer, 0x200u);
  gzwrite(a2, (unsigned __int8 *)spu_ram, 0x80000u);
  gzwrite(a2, (unsigned __int8 *)dword_4E7108, 0x8020u);
  return gzwrite(a2, (unsigned __int8 *)dword_465540, 0x1BC0u);
}

int __cdecl spucore_unfreeze(int a1, _DWORD *a2)
{
  char *v2; // edi
  int *v3; // esi
  unsigned int v4; // ebp
  unsigned __int16 v5; // ax
  int v6; // ecx
  int v7; // edx
  unsigned __int16 v8; // ax
  int v9; // ecx
  double v10; // st7
  double v11; // st7
  unsigned __int16 v12; // ax
  char v13; // dl
  int v14; // edx
  int v15; // ecx
  int v16; // edx
  int v17; // ecx
  int v18; // eax
  int v19; // edx
  unsigned __int16 v20; // ax
  int v21; // ecx
  int v22; // edx
  int v23; // ebx
  int v24; // eax
  int v25; // edx
  int v26; // ecx
  int v27; // ebp
  int v28; // edi
  int v29; // esi
  int v30; // edx
  __int16 *v31; // ecx
  int v32; // ebx
  int result; // eax
  int v34; // [esp+10h] [ebp-220h]
  int v35; // [esp+10h] [ebp-220h]
  int v36; // [esp+14h] [ebp-21Ch]
  int v37; // [esp+18h] [ebp-218h]
  char Str1[12]; // [esp+24h] [ebp-20Ch] BYREF
  char v39[384]; // [esp+30h] [ebp-200h] BYREF
  char v40; // [esp+1B0h] [ebp-80h] BYREF

  gzread(a2, v39, 7);
  gzread(a2, Str1, 8);
  gzread(a2, v39, 8);
  gzread(a2, v39, 512);
  v2 = v39;
  v3 = dword_465550;
  v34 = 24;
  do
  {
    v4 = 0;
    v36 = 8;
    do
    {
      if ( v4 <= 0xE )
      {
        switch ( v4 )
        {
          case 0u:
            v5 = *(_WORD *)v2;
            v6 = (*(unsigned __int16 *)v2 >> 14) & 1;
            v7 = *(_WORD *)v2 & 0x3FFF;
            *v3 = v6;
            v3[2] = v6;
            *(v3 - 4) = v7;
            v3[4] = (v5 >> 13) & 1;
            v3[6] = v5 >> 15;
            *(v3 - 2) = v5 & 0x7F;
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
            v8 = *((_WORD *)v2 + 1);
            *(v3 - 3) = v8 & 0x3FFF;
            v9 = (v8 >> 14) & 1;
            v3[1] = v9;
            v3[3] = v9;
            v3[5] = (v8 >> 13) & 1;
            v3[7] = v8 >> 15;
            *(v3 - 1) = v8 & 0x7F;
            break;
          case 4u:
            v10 = (double)(*((_WORD *)v2 + 2) & 0x3FFF);
            v3[8] = *((_WORD *)v2 + 2) & 0x3FFF;
            v11 = v10 * 0.000244140625;
            *((float *)v3 + 24) = v11;
            v3[25] = (__int64)(v11 * 65536.0);
            break;
          case 6u:
            v3[9] = *((unsigned __int16 *)v2 + 3);
            break;
          case 8u:
            v12 = *((_WORD *)v2 + 4);
            v13 = v2[9];
            v3[10] = v12 >> 15;
            v14 = v13 & 0x7F;
            v15 = (unsigned __int8)v12 >> 4;
            v3[11] = v14;
            v16 = dword_44F208[v14];
            v3[12] = v15;
            v17 = dword_44F408[v15];
            v18 = v12 & 0xF;
            v3[65] = v16;
            v19 = dword_44F648[v18];
            v3[13] = v18;
            v3[66] = -v17;
            v3[67] = v19;
            break;
          case 0xAu:
            v20 = *((_WORD *)v2 + 5);
            v3[14] = v20 >> 15;
            v21 = (v20 >> 14) & 1;
            v22 = (v20 >> 6) & 0x7F;
            v23 = (v20 >> 5) & 1;
            v24 = v20 & 0x1F;
            v3[15] = v21;
            v3[16] = v22;
            v3[17] = v23;
            v3[18] = v24;
            if ( v21 )
            {
              v26 = -dword_44F448[v22];
              v25 = -dword_44F688[v24];
              v3[68] = v26;
            }
            else
            {
              v3[68] = dword_44F448[v22];
              v25 = -dword_44F688[v24];
            }
            v3[69] = v25;
            break;
          case 0xCu:
            v37 = *((unsigned __int16 *)v2 + 6) << 9;
            v3[19] = v37;
            *((float *)v3 + 26) = (double)v37 * 0.000030517578125;
            break;
          case 0xEu:
            v3[20] = *((unsigned __int16 *)v2 + 7);
            break;
        }
      }
      v4 += 2;
      --v36;
    }
    while ( v36 );
    v2 += 16;
    v3 += 74;
    --v34;
  }
  while ( v34 );
  v27 = spucore_pitchmod_enable;
  v28 = spucore_noise_mode;
  v29 = dword_4E7100;
  v30 = dword_4EF138;
  v31 = (__int16 *)&v40;
  v32 = 0;
  v35 = 64;
  do
  {
    switch ( v32 )
    {
      case 0:
        spucore_mainvol_left = *v31;
        break;
      case 2:
        LOWORD(spucore_mainvol_right) = *v31;
        break;
      case 4:
        spucore_reverb_vol_left = *v31;
        break;
      case 6:
        spucore_reverb_vol_right = *v31;
        break;
      case 16:
        v27 = (unsigned __int16)*v31;
        break;
      case 18:
        v27 = ((unsigned __int16)*v31 << 16) + (unsigned __int16)v27;
        break;
      case 20:
        v28 = (unsigned __int16)*v31;
        break;
      case 22:
        v28 = ((unsigned __int16)*v31 << 16) + (unsigned __int16)v28;
        break;
      case 24:
        v29 = (unsigned __int16)*v31;
        break;
      case 26:
        v29 = ((unsigned __int16)*v31 << 16) + (unsigned __int16)v29;
        break;
      case 28:
        v30 = (unsigned __int16)*v31;
        break;
      case 30:
        v30 = ((unsigned __int16)*v31 << 16) + (unsigned __int16)v30;
        break;
      case 34:
        byte_4EF142[0x3FFF] = *v31;
        break;
      case 36:
        LOWORD(dword_463904) = *v31;
        break;
      case 42:
        spucore_write_cnt(*v31);
        break;
      case 44:
        spucore_write_dma_ctrl(*v31);
        break;
      case 46:
        spucore_write_status_hi(*v31);
        break;
      case 48:
        word_4E7104 = *v31;
        break;
      case 50:
        word_4E7106 = *v31;
        break;
      case 52:
        word_4F755C = *v31;
        break;
      case 54:
        word_4F7584 = *v31;
        break;
      default:
        break;
    }
    v32 += 2;
    ++v31;
    --v35;
  }
  while ( v35 );
  dword_4E7100 = v29;
  dword_4EF138 = v30;
  spucore_noise_mode = v28;
  spucore_pitchmod_enable = v27;
  gzread(a2, (char *)spu_ram, 0x80000);
  gzread(a2, dword_4E7108, 32800);
  dword_44F7A0 = *(_DWORD *)dword_4E7108;
  if ( dword_4E7114 > 4096 )
    dword_4E7114 = 0;
  result = strncmp(Str1, "ISPU", 4u);
  if ( !result )
    return gzread(a2, (char *)dword_465540, 7104);
  return result;
}

