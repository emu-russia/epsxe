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
