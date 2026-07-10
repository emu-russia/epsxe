#include "pch.h"
int sub_40FBA0()
{
  int *v0; // edi
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

  v0 = off_44F950;
  off_44F950[63] = 0;
  v1 = *(_QWORD *)(v0 + 17);
  v2 = v0[19];
  *((_QWORD *)v0 + 6) = *(_QWORD *)(v0 + 13);
  *((_QWORD *)v0 + 8) = v1;
  v0[18] = v2;
  v3 = _m_psrlqi(_m_psllqi(*(__m64 *)v0, 0x10u), 0x10u);
  v4 = _m_psradi(_m_pmaddwd(*(__m64 *)((char *)v0 + 134), v3), 1u);
  v5 = _m_psradi(_m_pmaddwd(*(__m64 *)(v0 + 35), v3), 1u);
  v6 = _m_psradi(_m_pmaddwd(*((__m64 *)v0 + 16), v3), 1u);
  v7 = _m_paddd(_m_psradi(_m_paddd(v5, _m_psrlqi(v5, 0x20u)), 0xBu), *(__m64 *)(v0 + 39));
  v8 = _m_paddd(_m_psradi(_m_paddd(_m_punpckldq(v6, v4), _m_punpckhdq(v6, v4)), 0xBu), *(__m64 *)(v0 + 37));
  v0[27] = _mm_cvtsi64_si32(v7);
  *(__m64 *)(v0 + 25) = v8;
  v9 = v8;
  v10 = _m_packssdw(v8, v7);
  v11 = _m_psradi(_m_psrlqi(v10, 0x10u), 0x10u);
  v12 = _m_psradi(_m_punpcklwd(v10, v10), 0x10u);
  v13 = _m_pandn(_m_pcmpeqd(v9, v12), (__m64)qword_44F958);
  v14 = _mm_cvtsi64_si32(_m_por(_m_pandn(_m_pcmpeqd(v7, v11), (__m64)qword_44F960), _m_por(v13, _m_psrlqi(v13, 0x20u))));
  v0[63] |= v14;
  v15 = _mm_cvtsi64_si32(v7);
  *(__m64 *)(v0 + 9) = v12;
  v0[11] = _mm_cvtsi64_si32(v11);
  if ( (unsigned int)v15 > 0xFFFF )
  {
    v0[63] |= 0x80040000;
    v28 = v15 < 0;
    v15 = 0xFFFF;
    if ( v28 )
    {
      v15 = 0;
      v14 = 0x20000;
      v0[19] = 0;
      goto LABEL_5;
    }
  }
  else
  {
    v14 = 0x20000;
    if ( !v15 )
    {
LABEL_5:
      v0[19] = v15;
      v0[63] |= 0x80020000;
      goto LABEL_6;
    }
  }
  v0[19] = v15;
  v16 = v0[58];
  if ( 2 * v15 < v16 )
    goto LABEL_5;
  v14 = (v16 << 16) / (unsigned int)v15;
LABEL_6:
  v17 = v14;
  v18 = ((unsigned __int64)(_mm_cvtsi64_si32(v12) * (__int64)v14) >> 16) + (v0[56] >> 16);
  v19 = (v0[57] >> 16) + ((unsigned __int64)(v14 * (__int64)_mm_cvtsi64_si32(_m_psrlqi(v12, 0x20u))) >> 16);
  v20 = v18 + 1024;
  v21 = v19 + 1024;
  if ( (unsigned int)(v18 + 1024) > 0x7FF )
  {
    v0[63] |= 0x80004000;
    v18 = 1023;
    if ( v20 < 0 )
      v18 = -1024;
  }
  if ( (unsigned int)v21 > 0x7FF )
  {
    v0[63] |= 0x80002000;
    v19 = 1023;
    if ( v21 < 0 )
      v19 = -1024;
  }
  LODWORD(v23) = v18 << 16;
  HIDWORD(v23) = v19;
  v22 = v23 >> 16;
  v0[14] = v22;
  v0[15] = v22;
  v24 = v0[60];
  v25 = (unsigned __int64)(v17 * (__int64)v0[59]) >> 12;
  v0[24] = v17 * v0[59] + v24;
  v26 = (v24 >> 12) + v25;
  if ( (unsigned int)v26 > 0x1000 )
  {
    v0[63] |= 0x1000u;
    v28 = v26 < 0;
    v26 = 4096;
    if ( v28 )
      v26 = 0;
  }
  v0[8] = v26;
  result = (v0[63] & 0x20000) << 14;
  v0[63] |= result;
  _m_empty();
  return result;
}
