#include "pch.h"
int sub_40FE00()
{
  int v0; // edi
  __m64 v1; // mm0
  __m64 v2; // mm2
  __m64 v3; // mm3
  __m64 v4; // mm4
  __m64 v5; // mm3
  __m64 v6; // mm6
  __m64 v7; // mm0
  __m64 v8; // mm1
  __m64 v9; // mm0
  __m64 v10; // mm6
  int v11; // eax
  int v12; // ecx
  int v13; // ebx
  int v14; // ebx
  int v15; // eax
  int v16; // edx
  int v17; // ecx
  unsigned __int64 v18; // rt0
  __m64 v19; // mm0
  __m64 v20; // mm2
  __m64 v21; // mm3
  __m64 v22; // mm4
  __m64 v23; // mm3
  __m64 v24; // mm6
  __m64 v25; // mm0
  __m64 v26; // mm1
  __m64 v27; // mm0
  __m64 v28; // mm6
  int v29; // eax
  int v30; // ecx
  int v31; // ebx
  int v32; // ebx
  int v33; // eax
  int v34; // edx
  int v35; // ecx
  unsigned __int64 v36; // rt0
  __m64 v37; // mm0
  __m64 v38; // mm2
  __m64 v39; // mm3
  __m64 v40; // mm4
  __m64 v41; // mm3
  __m64 v42; // mm1
  __m64 v43; // mm6
  __m64 v44; // mm0
  __m64 v45; // mm1
  __m64 v46; // mm0
  __m64 v47; // mm6
  int v48; // eax
  int v49; // ecx
  int v50; // ebx
  int v51; // esi
  int v52; // ebx
  int v53; // eax
  int v54; // edx
  int v55; // ecx
  int v56; // ebx
  unsigned __int64 v57; // rt0
  int v58; // ebx
  int v59; // eax
  int v60; // eax
  int result; // eax
  bool v62; // sf

  v0 = dword_44F950;
  *(_DWORD *)(dword_44F950 + 252) = 0;
  *(_DWORD *)(v0 + 64) = *(_DWORD *)(v0 + 76);
  v1 = _m_psrlqi(_m_psllqi(*(__m64 *)v0, 0x10u), 0x10u);
  v2 = _m_psradi(_m_pmaddwd(*(__m64 *)(v0 + 134), v1), 1u);
  v3 = _m_psradi(_m_pmaddwd(*(__m64 *)(v0 + 140), v1), 1u);
  v4 = _m_psradi(_m_pmaddwd(*(__m64 *)(v0 + 128), v1), 1u);
  v5 = _m_paddd(_m_psradi(_m_paddd(v3, _m_psrlqi(v3, 0x20u)), 0xBu), *(__m64 *)(v0 + 156));
  v6 = _m_paddd(_m_psradi(_m_paddd(_m_punpckldq(v4, v2), _m_punpckhdq(v4, v2)), 0xBu), *(__m64 *)(v0 + 148));
  v7 = _m_packssdw(v6, v5);
  v8 = _m_psrlqi(v7, 0x10u);
  v9 = _m_psradi(_m_punpcklwd(v7, v7), 0x10u);
  v10 = _m_pandn(_m_pcmpeqd(v6, v9), (__m64)qword_44F958);
  v11 = _mm_cvtsi64_si32(
          _m_por(
            _m_pandn(_m_pcmpeqd(v5, _m_psradi(v8, 0x10u)), (__m64)qword_44F960),
            _m_por(v10, _m_psrlqi(v10, 0x20u))));
  *(_DWORD *)(v0 + 252) |= v11;
  v12 = _mm_cvtsi64_si32(v5);
  if ( (unsigned int)v12 > 0xFFFF )
  {
    *(_DWORD *)(v0 + 252) |= 0x80040000;
    v62 = v12 < 0;
    v12 = 0xFFFF;
    if ( v62 )
    {
      v12 = 0;
      v11 = 0x20000;
      *(_DWORD *)(v0 + 68) = 0;
      goto LABEL_5;
    }
  }
  else
  {
    v11 = 0x20000;
    if ( !v12 )
    {
LABEL_5:
      *(_DWORD *)(v0 + 68) = v12;
      *(_DWORD *)(v0 + 252) |= 0x80020000;
      goto LABEL_6;
    }
  }
  *(_DWORD *)(v0 + 68) = v12;
  v13 = *(_DWORD *)(v0 + 232);
  if ( 2 * v12 < v13 )
    goto LABEL_5;
  v11 = (v13 << 16) / (unsigned int)v12;
LABEL_6:
  v14 = ((unsigned __int64)(_mm_cvtsi64_si32(v9) * (__int64)v11) >> 16) + (*(int *)(v0 + 224) >> 16);
  v15 = (*(int *)(v0 + 228) >> 16) + ((unsigned __int64)(v11 * (__int64)_mm_cvtsi64_si32(_m_psrlqi(v9, 0x20u))) >> 16);
  v16 = v14 + 1024;
  v17 = v15 + 1024;
  if ( (unsigned int)(v14 + 1024) > 0x7FF )
  {
    *(_DWORD *)(v0 + 252) |= 0x80004000;
    v14 = 1023;
    if ( v16 < 0 )
      v14 = -1024;
  }
  if ( (unsigned int)v17 > 0x7FF )
  {
    *(_DWORD *)(v0 + 252) |= 0x80002000;
    v15 = 1023;
    if ( v17 < 0 )
      v15 = -1024;
  }
  LODWORD(v18) = v14 << 16;
  HIDWORD(v18) = v15;
  *(_DWORD *)(v0 + 48) = v18 >> 16;
  v19 = _m_psrlqi(*(__m64 *)(v0 + 6), 0x10u);
  v20 = _m_psradi(_m_pmaddwd(*(__m64 *)(v0 + 134), v19), 1u);
  v21 = _m_psradi(_m_pmaddwd(*(__m64 *)(v0 + 140), v19), 1u);
  v22 = _m_psradi(_m_pmaddwd(*(__m64 *)(v0 + 128), v19), 1u);
  v23 = _m_paddd(_m_psradi(_m_paddd(v21, _m_psrlqi(v21, 0x20u)), 0xBu), *(__m64 *)(v0 + 156));
  v24 = _m_paddd(_m_psradi(_m_paddd(_m_punpckldq(v22, v20), _m_punpckhdq(v22, v20)), 0xBu), *(__m64 *)(v0 + 148));
  v25 = _m_packssdw(v24, v23);
  v26 = _m_psrlqi(v25, 0x10u);
  v27 = _m_psradi(_m_punpcklwd(v25, v25), 0x10u);
  v28 = _m_pandn(_m_pcmpeqd(v24, v27), (__m64)qword_44F958);
  v29 = _mm_cvtsi64_si32(
          _m_por(
            _m_pandn(_m_pcmpeqd(v23, _m_psradi(v26, 0x10u)), (__m64)qword_44F960),
            _m_por(v28, _m_psrlqi(v28, 0x20u))));
  *(_DWORD *)(v0 + 252) |= v29;
  v30 = _mm_cvtsi64_si32(v23);
  if ( (unsigned int)v30 > 0xFFFF )
  {
    *(_DWORD *)(v0 + 252) |= 0x80040000;
    v62 = v30 < 0;
    v30 = 0xFFFF;
    if ( v62 )
    {
      v30 = 0;
      v29 = 0x20000;
      *(_DWORD *)(v0 + 72) = 0;
      goto LABEL_12;
    }
  }
  else
  {
    v29 = 0x20000;
    if ( !v30 )
    {
LABEL_12:
      *(_DWORD *)(v0 + 72) = v30;
      *(_DWORD *)(v0 + 252) |= 0x80020000;
      goto LABEL_13;
    }
  }
  *(_DWORD *)(v0 + 72) = v30;
  v31 = *(_DWORD *)(v0 + 232);
  if ( 2 * v30 < v31 )
    goto LABEL_12;
  v29 = (v31 << 16) / (unsigned int)v30;
LABEL_13:
  v32 = ((unsigned __int64)(_mm_cvtsi64_si32(v27) * (__int64)v29) >> 16) + (*(int *)(v0 + 224) >> 16);
  v33 = (*(int *)(v0 + 228) >> 16) + ((unsigned __int64)(v29 * (__int64)_mm_cvtsi64_si32(_m_psrlqi(v27, 0x20u))) >> 16);
  v34 = v32 + 1024;
  v35 = v33 + 1024;
  if ( (unsigned int)(v32 + 1024) > 0x7FF )
  {
    *(_DWORD *)(v0 + 252) |= 0x80004000;
    v32 = 1023;
    if ( v34 < 0 )
      v32 = -1024;
  }
  if ( (unsigned int)v35 > 0x7FF )
  {
    *(_DWORD *)(v0 + 252) |= 0x80002000;
    v33 = 1023;
    if ( v35 < 0 )
      v33 = -1024;
  }
  LODWORD(v36) = v32 << 16;
  HIDWORD(v36) = v33;
  *(_DWORD *)(v0 + 52) = v36 >> 16;
  v37 = _m_psrlqi(*(__m64 *)(v0 + 14), 0x10u);
  v38 = _m_psradi(_m_pmaddwd(*(__m64 *)(v0 + 134), v37), 1u);
  v39 = _m_psradi(_m_pmaddwd(*(__m64 *)(v0 + 140), v37), 1u);
  v40 = _m_psradi(_m_pmaddwd(*(__m64 *)(v0 + 128), v37), 1u);
  v41 = _m_paddd(_m_psradi(_m_paddd(v39, _m_psrlqi(v39, 0x20u)), 0xBu), *(__m64 *)(v0 + 156));
  v42 = _m_paddd(_m_psradi(_m_paddd(_m_punpckldq(v40, v38), _m_punpckhdq(v40, v38)), 0xBu), *(__m64 *)(v0 + 148));
  *(_DWORD *)(v0 + 108) = _mm_cvtsi64_si32(v41);
  *(__m64 *)(v0 + 100) = v42;
  v43 = v42;
  v44 = _m_packssdw(v42, v41);
  v45 = _m_psradi(_m_psrlqi(v44, 0x10u), 0x10u);
  v46 = _m_psradi(_m_punpcklwd(v44, v44), 0x10u);
  v47 = _m_pandn(_m_pcmpeqd(v43, v46), (__m64)qword_44F958);
  v48 = _mm_cvtsi64_si32(_m_por(_m_pandn(_m_pcmpeqd(v41, v45), (__m64)qword_44F960), _m_por(v47, _m_psrlqi(v47, 0x20u))));
  *(_DWORD *)(v0 + 252) |= v48;
  v49 = _mm_cvtsi64_si32(v41);
  *(__m64 *)(v0 + 36) = v46;
  *(_DWORD *)(v0 + 44) = _mm_cvtsi64_si32(v45);
  if ( (unsigned int)v49 > 0xFFFF )
  {
    *(_DWORD *)(v0 + 252) |= 0x80040000;
    v62 = v49 < 0;
    v49 = 0xFFFF;
    if ( v62 )
    {
      v49 = 0;
      v48 = 0x20000;
      *(_DWORD *)(v0 + 76) = 0;
      goto LABEL_19;
    }
  }
  else
  {
    v48 = 0x20000;
    if ( !v49 )
    {
LABEL_19:
      *(_DWORD *)(v0 + 76) = v49;
      *(_DWORD *)(v0 + 252) |= 0x80020000;
      goto LABEL_20;
    }
  }
  *(_DWORD *)(v0 + 76) = v49;
  v50 = *(_DWORD *)(v0 + 232);
  if ( 2 * v49 < v50 )
    goto LABEL_19;
  v48 = (v50 << 16) / (unsigned int)v49;
LABEL_20:
  v51 = v48;
  v52 = ((unsigned __int64)(_mm_cvtsi64_si32(v46) * (__int64)v48) >> 16) + (*(int *)(v0 + 224) >> 16);
  v53 = (*(int *)(v0 + 228) >> 16) + ((unsigned __int64)(v48 * (__int64)_mm_cvtsi64_si32(_m_psrlqi(v46, 0x20u))) >> 16);
  v54 = v52 + 1024;
  v55 = v53 + 1024;
  if ( (unsigned int)(v52 + 1024) > 0x7FF )
  {
    *(_DWORD *)(v0 + 252) |= 0x80004000;
    v52 = 1023;
    if ( v54 < 0 )
      v52 = -1024;
  }
  if ( (unsigned int)v55 > 0x7FF )
  {
    *(_DWORD *)(v0 + 252) |= 0x80002000;
    v53 = 1023;
    if ( v55 < 0 )
      v53 = -1024;
  }
  LODWORD(v57) = v52 << 16;
  HIDWORD(v57) = v53;
  v56 = v57 >> 16;
  *(_DWORD *)(v0 + 56) = v56;
  *(_DWORD *)(v0 + 60) = v56;
  v58 = *(_DWORD *)(v0 + 240);
  v59 = (unsigned __int64)(v51 * (__int64)*(int *)(v0 + 236)) >> 12;
  *(_DWORD *)(v0 + 96) = v51 * *(_DWORD *)(v0 + 236) + v58;
  v60 = (v58 >> 12) + v59;
  if ( (unsigned int)v60 > 0x1000 )
  {
    *(_DWORD *)(v0 + 252) |= 0x1000u;
    v62 = v60 < 0;
    v60 = 4096;
    if ( v62 )
      v60 = 0;
  }
  *(_DWORD *)(v0 + 32) = v60;
  result = (*(_DWORD *)(v0 + 252) & 0x20000) << 14;
  *(_DWORD *)(v0 + 252) |= result;
  _m_empty();
  return result;
}
