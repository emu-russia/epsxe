#include "pch.h"
int gte_rtps()
{
  int v0; // edi
  __int64 v1; // mm1
  int v2; // eax
  __m64 v3; // mm0
  __m64 v4; // mm2
  __m64 v5; // mm3
  __m64 v6; // mm4
  __m64 v7; // mm3
  __m64 v8; // mm1
  __m64 v9; // mm6
  __m64 v10; // mm0
  __m64 v11; // mm1
  __m64 v12; // mm0
  __m64 v13; // mm6
  int v14; // eax
  int v15; // ecx
  int v16; // ebx
  int v17; // esi
  int v18; // ebx
  int v19; // eax
  int v20; // edx
  int v21; // ecx
  int v22; // ebx
  unsigned __int64 v23; // rt0
  int v24; // ebx
  int v25; // eax
  int v26; // eax
  int result; // eax
  bool v28; // sf

  v0 = dword_44F950;
  *(_DWORD *)(dword_44F950 + 252) = 0;
  v1 = *(_QWORD *)(v0 + 68);
  v2 = *(_DWORD *)(v0 + 76);
  *(_QWORD *)(v0 + 48) = *(_QWORD *)(v0 + 52);
  *(_QWORD *)(v0 + 64) = v1;
  *(_DWORD *)(v0 + 72) = v2;
  v3 = _m_psrlqi(_m_psllqi(*(__m64 *)v0, 0x10u), 0x10u);
  v4 = _m_psradi(_m_pmaddwd(*(__m64 *)(v0 + 134), v3), 1u);
  v5 = _m_psradi(_m_pmaddwd(*(__m64 *)(v0 + 140), v3), 1u);
  v6 = _m_psradi(_m_pmaddwd(*(__m64 *)(v0 + 128), v3), 1u);
  v7 = _m_paddd(_m_psradi(_m_paddd(v5, _m_psrlqi(v5, 0x20u)), 0xBu), *(__m64 *)(v0 + 156));
  v8 = _m_paddd(_m_psradi(_m_paddd(_m_punpckldq(v6, v4), _m_punpckhdq(v6, v4)), 0xBu), *(__m64 *)(v0 + 148));
  *(_DWORD *)(v0 + 108) = _mm_cvtsi64_si32(v7);
  *(__m64 *)(v0 + 100) = v8;
  v9 = v8;
  v10 = _m_packssdw(v8, v7);
  v11 = _m_psradi(_m_psrlqi(v10, 0x10u), 0x10u);
  v12 = _m_psradi(_m_punpcklwd(v10, v10), 0x10u);
  v13 = _m_pandn(_m_pcmpeqd(v9, v12), (__m64)qword_44F958);
  v14 = _mm_cvtsi64_si32(_m_por(_m_pandn(_m_pcmpeqd(v7, v11), (__m64)qword_44F960), _m_por(v13, _m_psrlqi(v13, 0x20u))));
  *(_DWORD *)(v0 + 252) |= v14;
  v15 = _mm_cvtsi64_si32(v7);
  *(__m64 *)(v0 + 36) = v12;
  *(_DWORD *)(v0 + 44) = _mm_cvtsi64_si32(v11);
  if ( (unsigned int)v15 > 0xFFFF )
  {
    *(_DWORD *)(v0 + 252) |= 0x80040000;
    v28 = v15 < 0;
    v15 = 0xFFFF;
    if ( v28 )
    {
      v15 = 0;
      v14 = 0x20000;
      *(_DWORD *)(v0 + 76) = 0;
      goto LABEL_5;
    }
  }
  else
  {
    v14 = 0x20000;
    if ( !v15 )
    {
LABEL_5:
      *(_DWORD *)(v0 + 76) = v15;
      *(_DWORD *)(v0 + 252) |= 0x80020000;
      goto LABEL_6;
    }
  }
  *(_DWORD *)(v0 + 76) = v15;
  v16 = *(_DWORD *)(v0 + 232);
  if ( 2 * v15 < v16 )
    goto LABEL_5;
  v14 = (v16 << 16) / (unsigned int)v15;
LABEL_6:
  v17 = v14;
  v18 = ((unsigned __int64)(_mm_cvtsi64_si32(v12) * (__int64)v14) >> 16) + (*(int *)(v0 + 224) >> 16);
  v19 = (*(int *)(v0 + 228) >> 16) + ((unsigned __int64)(v14 * (__int64)_mm_cvtsi64_si32(_m_psrlqi(v12, 0x20u))) >> 16);
  v20 = v18 + 1024;
  v21 = v19 + 1024;
  if ( (unsigned int)(v18 + 1024) > 0x7FF )
  {
    *(_DWORD *)(v0 + 252) |= 0x80004000;
    v18 = 1023;
    if ( v20 < 0 )
      v18 = -1024;
  }
  if ( (unsigned int)v21 > 0x7FF )
  {
    *(_DWORD *)(v0 + 252) |= 0x80002000;
    v19 = 1023;
    if ( v21 < 0 )
      v19 = -1024;
  }
  LODWORD(v23) = v18 << 16;
  HIDWORD(v23) = v19;
  v22 = v23 >> 16;
  *(_DWORD *)(v0 + 56) = v22;
  *(_DWORD *)(v0 + 60) = v22;
  v24 = *(_DWORD *)(v0 + 240);
  v25 = (unsigned __int64)(v17 * (__int64)*(int *)(v0 + 236)) >> 12;
  *(_DWORD *)(v0 + 96) = v17 * *(_DWORD *)(v0 + 236) + v24;
  v26 = (v24 >> 12) + v25;
  if ( (unsigned int)v26 > 0x1000 )
  {
    *(_DWORD *)(v0 + 252) |= 0x1000u;
    v28 = v26 < 0;
    v26 = 4096;
    if ( v28 )
      v26 = 0;
  }
  *(_DWORD *)(v0 + 32) = v26;
  result = (*(_DWORD *)(v0 + 252) & 0x20000) << 14;
  *(_DWORD *)(v0 + 252) |= result;
  _m_empty();
  return result;
}
