#include "pch.h"
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
