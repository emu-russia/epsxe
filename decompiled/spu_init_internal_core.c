#include "pch.h"
int spu_init_internal_core()
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

  dword_4F7148 = dword_44F710;
  dword_465530 = dword_44F714;
  if ( DirectSoundCreate(nullptr, &ppDS, nullptr) )
    return 0;
  ppDS->lpVtbl->SetCooperativeLevel(ppDS, hSaveLoadWnd, 1);
  v3 = 1;
  switch ( dword_44F710 )
  {
    case 0:
      v0 = 2048;
      v1 = 8000;
      dword_44F708 = 2048;
      break;
    case 1:
      v0 = 2048;
      dword_44F708 = 2048;
      goto LABEL_11;
    case 2:
      v0 = 4096;
      v1 = 22050;
      dword_44F708 = 4096;
      break;
    case 3:
      v0 = 0x2000;
      v1 = 44100;
      dword_44F708 = 0x2000;
      break;
    case 4:
      v0 = 4096;
      v1 = 16000;
      dword_44F708 = 4096;
      break;
    case 5:
      v0 = 0x2000;
      v1 = 32000;
      dword_44F708 = 0x2000;
      break;
    case 6:
      v0 = 0x2000;
      v1 = 48000;
      dword_44F708 = 0x2000;
      break;
    default:
      v0 = dword_44F708;
LABEL_11:
      v1 = 11025;
      break;
  }
  v5 = v1;
  if ( dword_44F714 == 1 )
  {
    v0 *= 2;
    v4 = 2;
    v7 = 4;
    dword_44F708 = v0;
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
  byte_4F7570 = (int)&v3;
  if ( ppDS->lpVtbl->CreateSoundBuffer(
         ppDS,
         (LPCDSBUFFERDESC)&dword_4F7560,
         (LPDIRECTSOUNDBUFFER *)&dword_45B8FC,
         nullptr)
    || (*(int (__stdcall **)(int, _DWORD, _DWORD, int))(*(_DWORD *)dword_45B8FC + 48))(dword_45B8FC, 0, 0, 1) )
  {
    return 0;
  }
  dword_44F70C = 0;
  return 1;
}
