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

int gte_rtpt()
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

int __cdecl gte_clamp(int a1, int a2)
{
  int result; // eax

  result = a2;
  if ( a2 >= -32768 )
  {
    if ( a2 > 0x7FFF )
    {
      gte_regs.ctrl[31].u32 |= a1;
      return 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= a1;
    return -32768;
  }
  return result;
}

char __cdecl gte_convert_to_5bit(int a1)
{
  int v1; // eax

  if ( (a1 & 0x8000u) == 0 )
  {
    if ( (__int16)a1 <= 3968 )
      return a1 >> 7;
    else
      LOBYTE(v1) = 31;
  }
  else
  {
    LOBYTE(v1) = 0;
  }
  return v1;
}

char gte_dcpl()
{
  int v0; // esi
  int v1; // edi
  int v2; // eax
  int v3; // edx
  GTE_REG v4; // eax
  int32_t v5; // edx
  int v6; // eax

  v0 = (HIBYTE(gte_regs.data[6].u16.hi) * gte_regs.data[10].s16.hi) >> 8;
  v1 = (LOBYTE(gte_regs.data[6].s16.lo) * gte_regs.data[11].s16.hi) >> 8;
  v2 = gte_clamp(-2130706432, gte_regs.ctrl[21].u32 - ((LOBYTE(gte_regs.data[6].u32) * gte_regs.data[9].s16.hi) >> 8));
  gte_regs.data[25].u32 = v3 + ((gte_regs.data[8].s16.hi * v2) >> 12);
  gte_regs.data[26].u32 = v0 + ((gte_regs.data[8].s16.hi * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - v0)) >> 12);
  v4.u32 = v1 + ((gte_regs.data[8].s16.hi * gte_clamp(0x400000, gte_regs.ctrl[23].u32 - v1)) >> 12);
  gte_regs.data[27] = v4;
  if ( gte_regs.data[25].s32 >= -32768 )
  {
    if ( gte_regs.data[25].s32 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = gte_regs.data[25].u32;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = -32768;
  }
  if ( gte_regs.data[26].s32 >= -32768 )
  {
    if ( gte_regs.data[26].s32 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = gte_regs.data[26].u32;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = -32768;
  }
  if ( v4.s32 >= -32768 )
  {
    if ( v4.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v4;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = -32768;
  }
  gte_regs.data[20].u32 = gte_regs.data[21].u32;
  v5 = gte_regs.data[26].s32 >> 4;
  v6 = v4.s32 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  dword_8A8004 = gte_regs.data[25].s32 >> 4;
  dword_8A8008 = gte_regs.data[26].s32 >> 4;
  dword_8A800C = v6;
  if ( gte_regs.data[25].s32 >> 4 >= 0 )
  {
    if ( gte_regs.data[25].s32 >> 4 <= 255 )
    {
      LOBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[25].s32 >> 4;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x200000u;
      LOBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x200000u;
    LOBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v5 >= 0 )
  {
    if ( v5 <= 255 )
    {
      HIBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[26].s32 >> 4;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x100000u;
      HIBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x100000u;
    HIBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v6 >= 0 )
  {
    if ( v6 <= 255 )
    {
      LOBYTE(gte_regs.data[22].s16.lo) = v6;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80000u;
      LOBYTE(v6) = HIBYTE(gte_regs.data[6].u32);
      LOBYTE(gte_regs.data[22].s16.lo) = -1;
    }
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  else
  {
    LOBYTE(v6) = gte_regs.ctrl[31].u16.hi;
    LOBYTE(gte_regs.data[22].s16.lo) = 0;
    gte_regs.ctrl[31].u32 |= 0x80000u;
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  return v6;
}

char gte_dpcs()
{
  int v0; // esi
  int v1; // edi
  int v2; // eax
  int v3; // edx
  GTE_REG v4; // eax
  int32_t v5; // edx
  int v6; // eax

  v0 = 16 * HIBYTE(gte_regs.data[6].u16.hi);
  v1 = 16 * LOBYTE(gte_regs.data[6].s16.lo);
  v2 = gte_clamp(-2130706432, gte_regs.ctrl[21].u32 - 16 * LOBYTE(gte_regs.data[6].u32));
  gte_regs.data[25].u32 = v3 + ((gte_regs.data[8].s16.hi * v2) >> 12);
  gte_regs.data[26].u32 = v0 + ((gte_regs.data[8].s16.hi * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - v0)) >> 12);
  v4.u32 = v1 + ((gte_regs.data[8].s16.hi * gte_clamp(0x400000, gte_regs.ctrl[23].u32 - v1)) >> 12);
  gte_regs.data[27] = v4;
  if ( gte_regs.data[25].s32 >= -32768 )
  {
    if ( gte_regs.data[25].s32 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = gte_regs.data[25].u32;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = -32768;
  }
  if ( gte_regs.data[26].s32 >= -32768 )
  {
    if ( gte_regs.data[26].s32 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = gte_regs.data[26].u32;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = -32768;
  }
  if ( v4.s32 >= -32768 )
  {
    if ( v4.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v4;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = -32768;
  }
  gte_regs.data[20].u32 = gte_regs.data[21].u32;
  v5 = gte_regs.data[26].s32 >> 4;
  v6 = v4.s32 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  dword_8A8004 = gte_regs.data[25].s32 >> 4;
  dword_8A8008 = gte_regs.data[26].s32 >> 4;
  dword_8A800C = v6;
  if ( gte_regs.data[25].s32 >> 4 >= 0 )
  {
    if ( gte_regs.data[25].s32 >> 4 <= 255 )
    {
      LOBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[25].s32 >> 4;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x200000u;
      LOBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x200000u;
    LOBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v5 >= 0 )
  {
    if ( v5 <= 255 )
    {
      HIBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[26].s32 >> 4;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x100000u;
      HIBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x100000u;
    HIBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v6 >= 0 )
  {
    if ( v6 <= 255 )
    {
      LOBYTE(gte_regs.data[22].s16.lo) = v6;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80000u;
      LOBYTE(v6) = HIBYTE(gte_regs.data[6].u32);
      LOBYTE(gte_regs.data[22].s16.lo) = -1;
    }
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  else
  {
    LOBYTE(v6) = gte_regs.ctrl[31].u16.hi;
    LOBYTE(gte_regs.data[22].s16.lo) = 0;
    gte_regs.ctrl[31].u32 |= 0x80000u;
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  return v6;
}

char gte_ncs()
{
  int v0; // edi
  int v1; // eax
  int v2; // ecx
  int v3; // edx
  GTE_REG v4; // eax
  GTE_REG v5; // ecx
  GTE_REG v6; // edx
  int v7; // eax
  int v8; // ecx
  int v9; // edx

  v0 = gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi;
  v1 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
  v2 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
  v3 = (v0 + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo + gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
  if ( v1 >= 0 )
  {
    if ( v1 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                            + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                            + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v2 >= 0 )
  {
    if ( v2 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                             + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                             + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v3 >= 0 )
  {
    if ( v3 <= 0x7FFF )
    {
      gte_regs.data[11].u32 = (v0
                             + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo
                             + gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v4.u32 = gte_regs.ctrl[13].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  v5.u32 = gte_regs.ctrl[14].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  v6.u32 = gte_regs.ctrl[15].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  gte_regs.data[25] = v4;
  gte_regs.data[26] = v5;
  gte_regs.data[27] = v6;
  if ( v4.s32 >= 0 )
  {
    if ( v4.s32 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = gte_regs.ctrl[13].u32
                           + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                             + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                             + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v5.s32 >= 0 )
  {
    if ( v5.s32 <= 0x7FFF )
    {
      gte_regs.data[10] = v5;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v6.s32 >= 0 )
  {
    if ( v6.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v6;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v7 = v4.s32 >> 4;
  gte_regs.data[20].u32 = gte_regs.data[21].u32;
  v8 = v5.s32 >> 4;
  v9 = v6.s32 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  dword_8A8004 = v7;
  dword_8A8008 = v8;
  dword_8A800C = v9;
  if ( v7 >= 0 )
  {
    if ( v7 <= 255 )
    {
      LOBYTE(gte_regs.data[22].u16.hi) = v7;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x200000u;
      LOBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x200000u;
    LOBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v8 >= 0 )
  {
    if ( v8 <= 255 )
    {
      HIBYTE(gte_regs.data[22].u16.hi) = v8;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x100000u;
      HIBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x100000u;
    HIBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v9 >= 0 )
  {
    if ( v9 <= 255 )
    {
      LOBYTE(gte_regs.data[22].s16.lo) = v9;
    }
    else
    {
      LOBYTE(v7) = gte_regs.ctrl[31].u16.hi;
      LOBYTE(gte_regs.data[22].s16.lo) = -1;
      gte_regs.ctrl[31].u32 |= 0x80000u;
    }
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80000u;
    LOBYTE(gte_regs.data[22].s16.lo) = 0;
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
    LOBYTE(v7) = HIBYTE(gte_regs.data[6].u32);
  }
  return v7;
}

char gte_nct()
{
  int v0; // ebp
  int v1; // eax
  int v2; // ecx
  int v3; // edx
  signed int v4; // eax
  signed int v5; // ecx
  signed int v6; // edx
  int v7; // eax
  int v8; // ecx
  int v9; // edx
  int v10; // ebp
  int v11; // ecx
  int v12; // edx
  int v13; // eax
  signed int v14; // eax
  signed int v15; // ecx
  signed int v16; // edx
  int v17; // eax
  int v18; // ecx
  int v19; // edx
  int v20; // ebp
  int v21; // ecx
  int v22; // edx
  int v23; // eax
  GTE_REG v24; // eax
  GTE_REG v25; // ecx
  GTE_REG v26; // edx
  int v27; // eax
  int v28; // ecx
  int v29; // edx
  char result; // al

  v0 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
  v1 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
  v2 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
  v3 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi + v0 + gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
  if ( v1 >= 0 )
  {
    if ( v1 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                            + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                            + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v2 >= 0 )
  {
    if ( v2 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                             + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                             + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v3 >= 0 )
  {
    if ( v3 <= 0x7FFF )
    {
      gte_regs.data[11].u32 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi
                             + v0
                             + gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v4 = gte_regs.ctrl[13].u32
     + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
       + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
       + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  v5 = gte_regs.ctrl[14].u32
     + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
       + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
       + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  v6 = gte_regs.ctrl[15].u32
     + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
       + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
       + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  if ( (unsigned int)v4 >= 0x8000 )
    gte_regs.ctrl[31].u32 |= 0x81000000;
  if ( (unsigned int)v5 >= 0x8000 )
    gte_regs.ctrl[31].u32 |= 0x80800000;
  if ( (unsigned int)v6 >= 0x8000 )
    gte_regs.ctrl[31].u32 |= 0x400000u;
  v7 = v4 >> 4;
  v8 = v5 >> 4;
  v9 = v6 >> 4;
  if ( v7 >= 0 )
  {
    if ( v7 <= 255 )
    {
      LOBYTE(gte_regs.data[22].u16.hi) = v7;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x200000u;
      LOBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x200000u;
    LOBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v8 >= 0 )
  {
    if ( v8 <= 255 )
    {
      HIBYTE(gte_regs.data[22].u16.hi) = v8;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x100000u;
      HIBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x100000u;
    HIBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v9 >= 0 )
  {
    if ( v9 <= 255 )
    {
      LOBYTE(gte_regs.data[22].s16.lo) = v9;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80000u;
      LOBYTE(gte_regs.data[22].s16.lo) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80000u;
    LOBYTE(gte_regs.data[22].s16.lo) = 0;
  }
  HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  v10 = gte_regs.ctrl[10].s16.lo * gte_regs.data[3].s16.hi;
  v11 = (gte_regs.ctrl[9].s16.hi * gte_regs.data[3].s16.hi
       + gte_regs.ctrl[8].s16.lo * gte_regs.data[2].s16.lo
       + gte_regs.ctrl[8].s16.hi * gte_regs.data[2].s16.hi) >> 12;
  v12 = (v10 + gte_regs.ctrl[10].s16.hi * gte_regs.data[2].s16.lo + gte_regs.ctrl[9].s16.lo * gte_regs.data[2].s16.hi) >> 12;
  v13 = (gte_regs.ctrl[12].s16.hi * gte_regs.data[3].s16.hi
       + gte_regs.ctrl[11].s16.lo * gte_regs.data[2].s16.lo
       + gte_regs.ctrl[11].s16.hi * gte_regs.data[2].s16.hi) >> 12;
  if ( v11 >= 0 )
  {
    if ( v11 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = (gte_regs.ctrl[9].s16.hi * gte_regs.data[3].s16.hi
                            + gte_regs.ctrl[8].s16.lo * gte_regs.data[2].s16.lo
                            + gte_regs.ctrl[8].s16.hi * gte_regs.data[2].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v12 >= 0 )
  {
    if ( v12 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = (v10
                             + gte_regs.ctrl[10].s16.hi * gte_regs.data[2].s16.lo
                             + gte_regs.ctrl[9].s16.lo * gte_regs.data[2].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v13 >= 0 )
  {
    if ( v13 <= 0x7FFF )
    {
      gte_regs.data[11].u32 = (gte_regs.ctrl[12].s16.hi * gte_regs.data[3].s16.hi
                             + gte_regs.ctrl[11].s16.lo * gte_regs.data[2].s16.lo
                             + gte_regs.ctrl[11].s16.hi * gte_regs.data[2].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v14 = gte_regs.ctrl[13].u32
      + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
        + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
        + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  v15 = gte_regs.ctrl[14].u32
      + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
        + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
        + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  v16 = gte_regs.ctrl[15].u32
      + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
        + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
        + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  if ( (unsigned int)v14 >= 0x8000 )
    gte_regs.ctrl[31].u32 |= 0x81000000;
  if ( (unsigned int)v15 >= 0x8000 )
    gte_regs.ctrl[31].u32 |= 0x80800000;
  if ( (unsigned int)v16 >= 0x8000 )
    gte_regs.ctrl[31].u32 |= 0x400000u;
  v17 = v14 >> 4;
  v18 = v15 >> 4;
  v19 = v16 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  if ( v17 >= 0 )
  {
    if ( v17 <= 255 )
    {
      LOBYTE(gte_regs.data[22].u16.hi) = v17;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x200000u;
      LOBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x200000u;
    LOBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v18 >= 0 )
  {
    if ( v18 <= 255 )
    {
      HIBYTE(gte_regs.data[22].u16.hi) = v18;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x100000u;
      HIBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x100000u;
    HIBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v19 >= 0 )
  {
    if ( v19 <= 255 )
    {
      LOBYTE(gte_regs.data[22].s16.lo) = v19;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80000u;
      LOBYTE(gte_regs.data[22].s16.lo) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80000u;
    LOBYTE(gte_regs.data[22].s16.lo) = 0;
  }
  HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  v20 = gte_regs.ctrl[10].s16.lo * gte_regs.data[5].s16.hi;
  v21 = (gte_regs.ctrl[9].s16.hi * gte_regs.data[5].s16.hi
       + gte_regs.ctrl[8].s16.lo * gte_regs.data[4].s16.lo
       + gte_regs.ctrl[8].s16.hi * gte_regs.data[4].s16.hi) >> 12;
  v22 = (v20 + gte_regs.ctrl[10].s16.hi * gte_regs.data[4].s16.lo + gte_regs.ctrl[9].s16.lo * gte_regs.data[4].s16.hi) >> 12;
  v23 = (gte_regs.ctrl[12].s16.hi * gte_regs.data[5].s16.hi
       + gte_regs.ctrl[11].s16.lo * gte_regs.data[4].s16.lo
       + gte_regs.ctrl[11].s16.hi * gte_regs.data[4].s16.hi) >> 12;
  if ( v21 >= 0 )
  {
    if ( v21 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = (gte_regs.ctrl[9].s16.hi * gte_regs.data[5].s16.hi
                            + gte_regs.ctrl[8].s16.lo * gte_regs.data[4].s16.lo
                            + gte_regs.ctrl[8].s16.hi * gte_regs.data[4].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v22 >= 0 )
  {
    if ( v22 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = (v20
                             + gte_regs.ctrl[10].s16.hi * gte_regs.data[4].s16.lo
                             + gte_regs.ctrl[9].s16.lo * gte_regs.data[4].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v23 >= 0 )
  {
    if ( v23 <= 0x7FFF )
    {
      gte_regs.data[11].u32 = (gte_regs.ctrl[12].s16.hi * gte_regs.data[5].s16.hi
                             + gte_regs.ctrl[11].s16.lo * gte_regs.data[4].s16.lo
                             + gte_regs.ctrl[11].s16.hi * gte_regs.data[4].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v24.u32 = gte_regs.ctrl[13].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  v25.u32 = gte_regs.ctrl[14].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  v26.u32 = gte_regs.ctrl[15].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  gte_regs.data[25] = v24;
  gte_regs.data[26] = v25;
  gte_regs.data[27] = v26;
  if ( v24.s32 >= 0 )
  {
    if ( v24.s32 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = gte_regs.ctrl[13].u32
                           + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                             + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                             + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v25.s32 >= 0 )
  {
    if ( v25.s32 <= 0x7FFF )
    {
      gte_regs.data[10] = v25;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v26.s32 >= 0 )
  {
    if ( v26.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v26;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v27 = v24.s32 >> 4;
  gte_regs.data[20].u32 = gte_regs.data[21].u32;
  v28 = v25.s32 >> 4;
  v29 = v26.s32 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  dword_8A8004 = v27;
  dword_8A8008 = v28;
  dword_8A800C = v29;
  if ( v27 >= 0 )
  {
    if ( v27 <= 255 )
    {
      LOBYTE(gte_regs.data[22].u16.hi) = v27;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x200000u;
      LOBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x200000u;
    LOBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v28 >= 0 )
  {
    if ( v28 <= 255 )
    {
      HIBYTE(gte_regs.data[22].u16.hi) = v28;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x100000u;
      HIBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x100000u;
    HIBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v29 >= 0 )
  {
    if ( v29 <= 255 )
    {
      result = HIBYTE(gte_regs.data[6].u32);
      LOBYTE(gte_regs.data[22].s16.lo) = v29;
    }
    else
    {
      result = gte_regs.ctrl[31].s32;
      LOBYTE(gte_regs.data[22].s16.lo) = -1;
      gte_regs.ctrl[31].u32 |= 0x80000u;
    }
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  else
  {
    result = gte_regs.ctrl[31].s32;
    gte_regs.ctrl[31].u32 |= 0x80000u;
    LOBYTE(gte_regs.data[22].s16.lo) = 0;
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  return result;
}

char gte_ncds()
{
  int v0; // edi
  int v1; // eax
  int v2; // ecx
  int v3; // edx
  GTE_REG v4; // eax
  GTE_REG v5; // ecx
  GTE_REG v6; // edx
  int v7; // esi
  int v8; // edi
  int v9; // eax
  int v10; // edx
  GTE_REG v11; // eax
  int32_t v12; // edx
  int v13; // eax

  v0 = gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi;
  v1 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
  v2 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
  v3 = (v0 + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo + gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
  if ( v1 >= 0 )
  {
    if ( v1 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                            + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                            + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v2 >= 0 )
  {
    if ( v2 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                             + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                             + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v3 >= 0 )
  {
    if ( v3 <= 0x7FFF )
    {
      gte_regs.data[11].u32 = (v0
                             + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo
                             + gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v4.u32 = gte_regs.ctrl[13].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  v5.u32 = gte_regs.ctrl[14].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  v6.u32 = gte_regs.ctrl[15].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  gte_regs.data[25] = v4;
  gte_regs.data[26] = v5;
  gte_regs.data[27] = v6;
  if ( v4.s32 >= 0 )
  {
    if ( v4.s32 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = gte_regs.ctrl[13].u32
                           + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                             + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                             + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v5.s32 >= 0 )
  {
    if ( v5.s32 <= 0x7FFF )
    {
      gte_regs.data[10] = v5;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v6.s32 >= 0 )
  {
    if ( v6.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v6;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v7 = (gte_regs.data[10].s16.hi * HIBYTE(gte_regs.data[6].u16.hi)) >> 8;
  v8 = (gte_regs.data[11].s16.hi * LOBYTE(gte_regs.data[6].s16.lo)) >> 8;
  v9 = gte_clamp(-2130706432, gte_regs.ctrl[21].u32 - ((gte_regs.data[9].s16.hi * LOBYTE(gte_regs.data[6].u32)) >> 8));
  gte_regs.data[25].u32 = v10 + ((gte_regs.data[8].s16.hi * v9) >> 12);
  gte_regs.data[26].u32 = v7 + ((gte_regs.data[8].s16.hi * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - v7)) >> 12);
  v11.u32 = v8 + ((gte_regs.data[8].s16.hi * gte_clamp(0x400000, gte_regs.ctrl[23].u32 - v8)) >> 12);
  gte_regs.data[27] = v11;
  if ( gte_regs.data[25].s32 >= 0 )
  {
    if ( gte_regs.data[25].s32 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = gte_regs.data[25].u32;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( gte_regs.data[26].s32 >= 0 )
  {
    if ( gte_regs.data[26].s32 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = gte_regs.data[26].u32;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v11.s32 >= 0 )
  {
    if ( v11.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v11;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  gte_regs.data[20].u32 = gte_regs.data[21].u32;
  v12 = gte_regs.data[26].s32 >> 4;
  v13 = v11.s32 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  dword_8A8004 = gte_regs.data[25].s32 >> 4;
  dword_8A8008 = gte_regs.data[26].s32 >> 4;
  dword_8A800C = v13;
  if ( gte_regs.data[25].s32 >> 4 >= 0 )
  {
    if ( gte_regs.data[25].s32 >> 4 <= 255 )
    {
      LOBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[25].s32 >> 4;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x200000u;
      LOBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x200000u;
    LOBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v12 >= 0 )
  {
    if ( v12 <= 255 )
    {
      HIBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[26].s32 >> 4;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x100000u;
      HIBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x100000u;
    HIBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v13 >= 0 )
  {
    if ( v13 <= 255 )
    {
      LOBYTE(gte_regs.data[22].s16.lo) = v13;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80000u;
      LOBYTE(v13) = HIBYTE(gte_regs.data[6].u32);
      LOBYTE(gte_regs.data[22].s16.lo) = -1;
    }
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  else
  {
    LOBYTE(v13) = gte_regs.ctrl[31].u16.hi;
    LOBYTE(gte_regs.data[22].s16.lo) = 0;
    gte_regs.ctrl[31].u32 |= 0x80000u;
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  return v13;
}

char gte_ncdt()
{
  int v0; // eax
  int v1; // ecx
  int v2; // edx
  GTE_REG v3; // eax
  GTE_REG v4; // ecx
  GTE_REG v5; // edx
  int v6; // esi
  int v7; // edi
  int v8; // eax
  int v9; // edx
  int v10; // eax
  GTE_REG v11; // edx
  int32_t v12; // edx
  int v13; // eax
  int v14; // ebp
  int v15; // edi
  int v16; // eax
  int v17; // ecx
  int v18; // edx
  GTE_REG v19; // eax
  GTE_REG v20; // ecx
  GTE_REG v21; // edx
  int v22; // esi
  int v23; // edi
  int v24; // eax
  int v25; // edx
  int v26; // eax
  GTE_REG v27; // edx
  int32_t v28; // edx
  int v29; // eax
  int v30; // ebp
  int v31; // edi
  int v32; // eax
  int v33; // ecx
  int v34; // edx
  GTE_REG v35; // eax
  GTE_REG v36; // ecx
  GTE_REG v37; // edx
  int v38; // esi
  int v39; // edi
  int v40; // eax
  int v41; // edx
  GTE_REG v42; // eax
  int32_t v43; // edx
  int v44; // eax

  v0 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
  v1 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
  v2 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
  if ( v0 >= 0 )
  {
    if ( v0 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                            + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                            + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v1 >= 0 )
  {
    if ( v1 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                             + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                             + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v2 >= 0 )
  {
    if ( v2 <= 0x7FFF )
    {
      gte_regs.data[11].u32 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi
                             + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo
                             + gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v3.u32 = gte_regs.ctrl[13].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  v4.u32 = gte_regs.ctrl[14].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  v5.u32 = gte_regs.ctrl[15].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  gte_regs.data[25] = v3;
  gte_regs.data[26] = v4;
  gte_regs.data[27] = v5;
  if ( v3.s32 >= 0 )
  {
    if ( v3.s32 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = gte_regs.ctrl[13].u32
                           + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                             + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                             + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v4.s32 >= 0 )
  {
    if ( v4.s32 <= 0x7FFF )
    {
      gte_regs.data[10] = v4;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v5.s32 >= 0 )
  {
    if ( v5.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v5;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v6 = (gte_regs.data[10].s16.hi * HIBYTE(gte_regs.data[6].u16.hi)) >> 8;
  v7 = (gte_regs.data[11].s16.hi * LOBYTE(gte_regs.data[6].s16.lo)) >> 8;
  v8 = gte_clamp(-2130706432, gte_regs.ctrl[21].u32 - ((gte_regs.data[9].s16.hi * LOBYTE(gte_regs.data[6].u32)) >> 8));
  gte_regs.data[25].u32 = v9 + ((gte_regs.data[8].s16.hi * v8) >> 12);
  gte_regs.data[26].u32 = v6 + ((gte_regs.data[8].s16.hi * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - v6)) >> 12);
  v10 = gte_clamp(0x400000, gte_regs.ctrl[23].u32 - v7);
  v11 = gte_regs.data[21];
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  gte_regs.data[20] = v11;
  v12 = gte_regs.data[26].s32 >> 4;
  v13 = (v7 + ((gte_regs.data[8].s16.hi * v10) >> 12)) >> 4;
  if ( gte_regs.data[25].s32 >> 4 >= 0 )
  {
    if ( gte_regs.data[25].s32 >> 4 <= 255 )
    {
      LOBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[25].s32 >> 4;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x200000u;
      LOBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x200000u;
    LOBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v12 >= 0 )
  {
    if ( v12 <= 255 )
    {
      HIBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[26].s32 >> 4;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x100000u;
      HIBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x100000u;
    HIBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v13 >= 0 )
  {
    if ( v13 <= 255 )
    {
      LOBYTE(gte_regs.data[22].s16.lo) = v13;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80000u;
      LOBYTE(gte_regs.data[22].s16.lo) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80000u;
    LOBYTE(gte_regs.data[22].s16.lo) = 0;
  }
  HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  v14 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
  v15 = gte_regs.data[3].s16.hi * gte_regs.ctrl[12].s16.hi;
  v16 = (gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
       + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
       + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
  v17 = (gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
       + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
       + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
  v18 = (v15 + v14 + gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
  if ( v16 >= 0 )
  {
    if ( v16 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = (gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                            + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                            + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v17 >= 0 )
  {
    if ( v17 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = (gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                             + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                             + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v18 >= 0 )
  {
    if ( v18 <= 0x7FFF )
    {
      gte_regs.data[11].u32 = (v15 + v14 + gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v19.u32 = gte_regs.ctrl[13].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  v20.u32 = gte_regs.ctrl[14].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  v21.u32 = gte_regs.ctrl[15].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  gte_regs.data[25] = v19;
  gte_regs.data[26] = v20;
  gte_regs.data[27] = v21;
  if ( v19.s32 >= 0 )
  {
    if ( v19.s32 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = gte_regs.ctrl[13].u32
                           + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                             + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                             + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v20.s32 >= 0 )
  {
    if ( v20.s32 <= 0x7FFF )
    {
      gte_regs.data[10] = v20;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v21.s32 >= 0 )
  {
    if ( v21.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v21;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v22 = (gte_regs.data[10].s16.hi * HIBYTE(gte_regs.data[6].u16.hi)) >> 8;
  v23 = (gte_regs.data[11].s16.hi * LOBYTE(gte_regs.data[6].s16.lo)) >> 8;
  v24 = gte_clamp(-2130706432, gte_regs.ctrl[21].u32 - ((gte_regs.data[9].s16.hi * LOBYTE(gte_regs.data[6].u32)) >> 8));
  gte_regs.data[25].u32 = v25 + ((gte_regs.data[8].s16.hi * v24) >> 12);
  gte_regs.data[26].u32 = v22 + ((gte_regs.data[8].s16.hi * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - v22)) >> 12);
  v26 = gte_clamp(0x400000, gte_regs.ctrl[23].u32 - v23);
  v27 = gte_regs.data[21];
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  gte_regs.data[20] = v27;
  v28 = gte_regs.data[26].s32 >> 4;
  v29 = (v23 + ((gte_regs.data[8].s16.hi * v26) >> 12)) >> 4;
  if ( gte_regs.data[25].s32 >> 4 >= 0 )
  {
    if ( gte_regs.data[25].s32 >> 4 <= 255 )
    {
      LOBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[25].s32 >> 4;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x200000u;
      LOBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x200000u;
    LOBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v28 >= 0 )
  {
    if ( v28 <= 255 )
    {
      HIBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[26].s32 >> 4;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x100000u;
      HIBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x100000u;
    HIBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v29 >= 0 )
  {
    if ( v29 <= 255 )
    {
      LOBYTE(gte_regs.data[22].s16.lo) = v29;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80000u;
      LOBYTE(gte_regs.data[22].s16.lo) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80000u;
    LOBYTE(gte_regs.data[22].s16.lo) = 0;
  }
  HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  v30 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
  v31 = gte_regs.data[5].s16.hi * gte_regs.ctrl[12].s16.hi;
  v32 = (gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
       + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
       + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
  v33 = (gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
       + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
       + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
  v34 = (v31 + v30 + gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
  if ( v32 >= 0 )
  {
    if ( v32 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = (gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                            + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v33 >= 0 )
  {
    if ( v33 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = (gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                             + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                             + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v34 >= 0 )
  {
    if ( v34 <= 0x7FFF )
    {
      gte_regs.data[11].u32 = (v31 + v30 + gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v35.u32 = gte_regs.ctrl[13].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  v36.u32 = gte_regs.ctrl[14].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  v37.u32 = gte_regs.ctrl[15].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  gte_regs.data[25] = v35;
  gte_regs.data[26] = v36;
  gte_regs.data[27] = v37;
  if ( v35.s32 >= 0 )
  {
    if ( v35.s32 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = gte_regs.ctrl[13].u32
                           + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                             + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                             + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v36.s32 >= 0 )
  {
    if ( v36.s32 <= 0x7FFF )
    {
      gte_regs.data[10] = v36;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v37.s32 >= 0 )
  {
    if ( v37.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v37;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v38 = (gte_regs.data[10].s16.hi * HIBYTE(gte_regs.data[6].u16.hi)) >> 8;
  v39 = (gte_regs.data[11].s16.hi * LOBYTE(gte_regs.data[6].s16.lo)) >> 8;
  v40 = gte_clamp(-2130706432, gte_regs.ctrl[21].u32 - ((gte_regs.data[9].s16.hi * LOBYTE(gte_regs.data[6].u32)) >> 8));
  gte_regs.data[25].u32 = v41 + ((gte_regs.data[8].s16.hi * v40) >> 12);
  gte_regs.data[26].u32 = v38 + ((gte_regs.data[8].s16.hi * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - v38)) >> 12);
  v42.u32 = v39 + ((gte_regs.data[8].s16.hi * gte_clamp(0x400000, gte_regs.ctrl[23].u32 - v39)) >> 12);
  gte_regs.data[27] = v42;
  if ( gte_regs.data[25].s32 >= 0 )
  {
    if ( gte_regs.data[25].s32 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = gte_regs.data[25].u32;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( gte_regs.data[26].s32 >= 0 )
  {
    if ( gte_regs.data[26].s32 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = gte_regs.data[26].u32;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v42.s32 >= 0 )
  {
    if ( v42.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v42;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  gte_regs.data[20].u32 = gte_regs.data[21].u32;
  v43 = gte_regs.data[26].s32 >> 4;
  v44 = v42.s32 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  dword_8A8004 = gte_regs.data[25].s32 >> 4;
  dword_8A8008 = gte_regs.data[26].s32 >> 4;
  dword_8A800C = v44;
  if ( gte_regs.data[25].s32 >> 4 >= 0 )
  {
    if ( gte_regs.data[25].s32 >> 4 <= 255 )
    {
      LOBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[25].s32 >> 4;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x200000u;
      LOBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x200000u;
    LOBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v43 >= 0 )
  {
    if ( v43 <= 255 )
    {
      HIBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[26].s32 >> 4;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x100000u;
      HIBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x100000u;
    HIBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v44 >= 0 )
  {
    if ( v44 <= 255 )
    {
      LOBYTE(gte_regs.data[22].s16.lo) = v44;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80000u;
      LOBYTE(v44) = HIBYTE(gte_regs.data[6].u32);
      LOBYTE(gte_regs.data[22].s16.lo) = -1;
    }
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  else
  {
    LOBYTE(v44) = gte_regs.ctrl[31].u16.hi;
    LOBYTE(gte_regs.data[22].s16.lo) = 0;
    gte_regs.ctrl[31].u32 |= 0x80000u;
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  return v44;
}

GTE_REG gte_dpct()
{
  GTE_REG v0; // esi
  int v1; // esi
  int v2; // edi
  int v3; // eax
  int v4; // edx
  int v5; // eax
  GTE_REG result; // eax
  int32_t v7; // edx
  int32_t v8; // ebx
  int v9; // [esp-4h] [ebp-18h]
  int v10; // [esp+10h] [ebp-4h]

  LOBYTE(v0.u16.hi) = gte_regs.data[20].u16.hi;
  v10 = 3;
  do
  {
    v9 = gte_regs.ctrl[21].u32 - 16 * LOBYTE(v0.u32);
    v1 = 16 * HIBYTE(gte_regs.data[20].u16.hi);
    v2 = 16 * LOBYTE(gte_regs.data[20].s16.lo);
    v3 = gte_clamp(-2130706432, v9);
    gte_regs.data[25].u32 = v4 + ((gte_regs.data[8].s16.hi * v3) >> 12);
    gte_regs.data[26].u32 = v1 + ((gte_regs.data[8].s16.hi * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - v1)) >> 12);
    v5 = gte_clamp(0x400000, gte_regs.ctrl[23].u32 - v2);
    v0 = gte_regs.data[21];
    result.u32 = v2 + ((gte_regs.data[8].s16.hi * v5) >> 12);
    gte_regs.data[21].u32 = gte_regs.data[22].u32;
    v7 = gte_regs.data[26].s32 >> 4;
    v8 = result.s32 >> 4;
    gte_regs.data[27] = result;
    gte_regs.data[20] = v0;
    dword_8A8004 = gte_regs.data[25].s32 >> 4;
    dword_8A8008 = gte_regs.data[26].s32 >> 4;
    dword_8A800C = result.s32 >> 4;
    if ( gte_regs.data[25].s32 >> 4 >= 0 )
    {
      if ( gte_regs.data[25].s32 >> 4 <= 255 )
      {
        LOBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[25].s32 >> 4;
      }
      else
      {
        gte_regs.ctrl[31].u32 |= 0x200000u;
        LOBYTE(gte_regs.data[22].u16.hi) = -1;
      }
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x200000u;
      LOBYTE(gte_regs.data[22].u16.hi) = 0;
    }
    if ( v7 >= 0 )
    {
      if ( v7 <= 255 )
      {
        HIBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[26].s32 >> 4;
      }
      else
      {
        gte_regs.ctrl[31].u32 |= 0x100000u;
        HIBYTE(gte_regs.data[22].u16.hi) = -1;
      }
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x100000u;
      HIBYTE(gte_regs.data[22].u16.hi) = 0;
    }
    if ( v8 >= 0 )
    {
      if ( v8 <= 255 )
      {
        LOBYTE(gte_regs.data[22].s16.lo) = result.s32 >> 4;
      }
      else
      {
        gte_regs.ctrl[31].u32 |= 0x80000u;
        LOBYTE(gte_regs.data[22].s16.lo) = -1;
      }
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80000u;
      LOBYTE(gte_regs.data[22].s16.lo) = 0;
    }
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
    --v10;
  }
  while ( v10 );
  if ( gte_regs.data[25].s32 >= -32768 )
  {
    if ( gte_regs.data[25].s32 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = gte_regs.data[25].u32;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = -32768;
  }
  if ( gte_regs.data[26].s32 >= -32768 )
  {
    if ( gte_regs.data[26].s32 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = gte_regs.data[26].u32;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = -32768;
  }
  if ( result.s32 >= -32768 )
  {
    if ( result.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = result;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = -32768;
  }
  return result;
}

char gte_nccs()
{
  int v0; // edi
  int v1; // eax
  int v2; // ecx
  int v3; // edx
  signed int v4; // eax
  GTE_REG v5; // ecx
  GTE_REG v6; // edx
  int v7; // eax
  int v8; // ecx
  int v9; // edx
  int v10; // eax
  int v11; // ecx
  int v12; // edx

  v0 = gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi;
  v1 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
  v2 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
  v3 = (v0 + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo + gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
  if ( v1 >= 0 )
  {
    if ( v1 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                            + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                            + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v2 >= 0 )
  {
    if ( v2 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                             + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                             + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v3 >= 0 )
  {
    if ( v3 <= 0x7FFF )
    {
      gte_regs.data[11].u32 = (v0
                             + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo
                             + gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v4 = gte_regs.ctrl[13].u32
     + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
       + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
       + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  v5.u32 = gte_regs.ctrl[14].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  v6.u32 = gte_regs.ctrl[15].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  if ( v4 >= 0 )
  {
    if ( v4 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = gte_regs.ctrl[13].u32
                           + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                             + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                             + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v5.s32 >= 0 )
  {
    if ( v5.s32 <= 0x7FFF )
    {
      gte_regs.data[10] = v5;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v6.s32 >= 0 )
  {
    if ( v6.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v6;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v7 = (gte_regs.data[9].s16.hi * LOBYTE(gte_regs.data[6].u32)) >> 8;
  gte_regs.data[25].u32 = v7;
  v8 = (gte_regs.data[10].s16.hi * HIBYTE(gte_regs.data[6].u16.hi)) >> 8;
  gte_regs.data[26].u32 = v8;
  v9 = (gte_regs.data[11].s16.hi * LOBYTE(gte_regs.data[6].s16.lo)) >> 8;
  gte_regs.data[27].u32 = v9;
  if ( v7 >= 0 )
  {
    if ( v7 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = (gte_regs.data[9].s16.hi * LOBYTE(gte_regs.data[6].u32)) >> 8;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v8 >= 0 )
  {
    if ( v8 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = (gte_regs.data[10].s16.hi * HIBYTE(gte_regs.data[6].u16.hi)) >> 8;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v9 >= 0 )
  {
    if ( v9 <= 0x7FFF )
    {
      gte_regs.data[11].u32 = (gte_regs.data[11].s16.hi * LOBYTE(gte_regs.data[6].s16.lo)) >> 8;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v10 = v7 >> 4;
  gte_regs.data[20].u32 = gte_regs.data[21].u32;
  v11 = v8 >> 4;
  v12 = v9 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  dword_8A8004 = v10;
  dword_8A8008 = v11;
  dword_8A800C = v12;
  if ( v10 >= 0 )
  {
    if ( v10 <= 255 )
    {
      LOBYTE(gte_regs.data[22].u16.hi) = v10;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x200000u;
      LOBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x200000u;
    LOBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v11 >= 0 )
  {
    if ( v11 <= 255 )
    {
      HIBYTE(gte_regs.data[22].u16.hi) = v11;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x100000u;
      HIBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x100000u;
    HIBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v12 >= 0 )
  {
    if ( v12 <= 255 )
    {
      LOBYTE(gte_regs.data[22].s16.lo) = v12;
    }
    else
    {
      LOBYTE(v10) = gte_regs.ctrl[31].u16.hi;
      gte_regs.ctrl[31].u32 |= 0x80000u;
      LOBYTE(gte_regs.data[22].s16.lo) = -1;
    }
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80000u;
    LOBYTE(gte_regs.data[22].s16.lo) = 0;
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
    LOBYTE(v10) = HIBYTE(gte_regs.data[6].u32);
  }
  return v10;
}

char gte_ncct()
{
  int v0; // ebp
  int v1; // eax
  int v2; // ecx
  int v3; // edx
  signed int v4; // eax
  GTE_REG v5; // ecx
  GTE_REG v6; // edx
  int v7; // eax
  int v8; // ecx
  int v9; // edx
  int v10; // ebp
  int v11; // ecx
  int v12; // edx
  int v13; // eax
  signed int v14; // eax
  GTE_REG v15; // ecx
  GTE_REG v16; // edx
  int v17; // eax
  int v18; // ecx
  int v19; // edx
  int v20; // ebp
  int v21; // ecx
  int v22; // edx
  int v23; // eax
  signed int v24; // eax
  GTE_REG v25; // ecx
  GTE_REG v26; // edx
  int v27; // eax
  int v28; // ecx
  int v29; // edx
  int v30; // eax
  int v31; // ecx
  int v32; // edx
  char result; // al

  v0 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
  v1 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
  v2 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
  v3 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi + v0 + gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
  if ( v1 >= 0 )
  {
    if ( v1 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                            + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                            + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v2 >= 0 )
  {
    if ( v2 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                             + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                             + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v3 >= 0 )
  {
    if ( v3 <= 0x7FFF )
    {
      gte_regs.data[11].u32 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi
                             + v0
                             + gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v4 = gte_regs.ctrl[13].u32
     + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
       + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
       + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  v5.u32 = gte_regs.ctrl[14].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  v6.u32 = gte_regs.ctrl[15].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  if ( v4 >= 0 )
  {
    if ( v4 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = gte_regs.ctrl[13].u32
                           + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                             + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                             + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v5.s32 >= 0 )
  {
    if ( v5.s32 <= 0x7FFF )
    {
      gte_regs.data[10] = v5;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v6.s32 >= 0 )
  {
    if ( v6.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v6;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v7 = (LOBYTE(gte_regs.data[6].u32) * gte_regs.data[9].s16.hi) >> 12;
  v8 = (HIBYTE(gte_regs.data[6].u16.hi) * gte_regs.data[10].s16.hi) >> 12;
  v9 = (LOBYTE(gte_regs.data[6].s16.lo) * gte_regs.data[11].s16.hi) >> 12;
  if ( v7 >= 0 )
  {
    if ( v7 <= 255 )
    {
      LOBYTE(gte_regs.data[22].u16.hi) = (LOBYTE(gte_regs.data[6].u32) * gte_regs.data[9].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x200000u;
      LOBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x200000u;
    LOBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v8 >= 0 )
  {
    if ( v8 <= 255 )
    {
      HIBYTE(gte_regs.data[22].u16.hi) = (HIBYTE(gte_regs.data[6].u16.hi) * gte_regs.data[10].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x100000u;
      HIBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x100000u;
    HIBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v9 >= 0 )
  {
    if ( v9 <= 255 )
    {
      LOBYTE(gte_regs.data[22].s16.lo) = (LOBYTE(gte_regs.data[6].s16.lo) * gte_regs.data[11].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80000u;
      LOBYTE(gte_regs.data[22].s16.lo) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80000u;
    LOBYTE(gte_regs.data[22].s16.lo) = 0;
  }
  HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  v10 = gte_regs.ctrl[10].s16.lo * gte_regs.data[3].s16.hi;
  v11 = (gte_regs.ctrl[9].s16.hi * gte_regs.data[3].s16.hi
       + gte_regs.ctrl[8].s16.lo * gte_regs.data[2].s16.lo
       + gte_regs.ctrl[8].s16.hi * gte_regs.data[2].s16.hi) >> 12;
  v12 = (v10 + gte_regs.ctrl[10].s16.hi * gte_regs.data[2].s16.lo + gte_regs.ctrl[9].s16.lo * gte_regs.data[2].s16.hi) >> 12;
  v13 = (gte_regs.ctrl[12].s16.hi * gte_regs.data[3].s16.hi
       + gte_regs.ctrl[11].s16.lo * gte_regs.data[2].s16.lo
       + gte_regs.ctrl[11].s16.hi * gte_regs.data[2].s16.hi) >> 12;
  if ( v11 >= 0 )
  {
    if ( v11 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = (gte_regs.ctrl[9].s16.hi * gte_regs.data[3].s16.hi
                            + gte_regs.ctrl[8].s16.lo * gte_regs.data[2].s16.lo
                            + gte_regs.ctrl[8].s16.hi * gte_regs.data[2].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v12 >= 0 )
  {
    if ( v12 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = (v10
                             + gte_regs.ctrl[10].s16.hi * gte_regs.data[2].s16.lo
                             + gte_regs.ctrl[9].s16.lo * gte_regs.data[2].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v13 >= 0 )
  {
    if ( v13 <= 0x7FFF )
    {
      gte_regs.data[11].u32 = (gte_regs.ctrl[12].s16.hi * gte_regs.data[3].s16.hi
                             + gte_regs.ctrl[11].s16.lo * gte_regs.data[2].s16.lo
                             + gte_regs.ctrl[11].s16.hi * gte_regs.data[2].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v14 = gte_regs.ctrl[13].u32
      + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
        + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
        + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  v15.u32 = gte_regs.ctrl[14].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  v16.u32 = gte_regs.ctrl[15].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  if ( v14 >= 0 )
  {
    if ( v14 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = gte_regs.ctrl[13].u32
                           + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                             + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                             + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v15.s32 >= 0 )
  {
    if ( v15.s32 <= 0x7FFF )
    {
      gte_regs.data[10] = v15;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v16.s32 >= 0 )
  {
    if ( v16.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v16;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v17 = (LOBYTE(gte_regs.data[6].u32) * gte_regs.data[9].s16.hi) >> 12;
  v18 = (HIBYTE(gte_regs.data[6].u16.hi) * gte_regs.data[10].s16.hi) >> 12;
  v19 = (LOBYTE(gte_regs.data[6].s16.lo) * gte_regs.data[11].s16.hi) >> 12;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  if ( v17 >= 0 )
  {
    if ( v17 <= 255 )
    {
      LOBYTE(gte_regs.data[22].u16.hi) = (LOBYTE(gte_regs.data[6].u32) * gte_regs.data[9].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x200000u;
      LOBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x200000u;
    LOBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v18 >= 0 )
  {
    if ( v18 <= 255 )
    {
      HIBYTE(gte_regs.data[22].u16.hi) = (HIBYTE(gte_regs.data[6].u16.hi) * gte_regs.data[10].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x100000u;
      HIBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x100000u;
    HIBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v19 >= 0 )
  {
    if ( v19 <= 255 )
    {
      LOBYTE(gte_regs.data[22].s16.lo) = (LOBYTE(gte_regs.data[6].s16.lo) * gte_regs.data[11].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80000u;
      LOBYTE(gte_regs.data[22].s16.lo) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80000u;
    LOBYTE(gte_regs.data[22].s16.lo) = 0;
  }
  HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  v20 = gte_regs.ctrl[10].s16.lo * gte_regs.data[5].s16.hi;
  v21 = (gte_regs.ctrl[9].s16.hi * gte_regs.data[5].s16.hi
       + gte_regs.ctrl[8].s16.lo * gte_regs.data[4].s16.lo
       + gte_regs.ctrl[8].s16.hi * gte_regs.data[4].s16.hi) >> 12;
  v22 = (v20 + gte_regs.ctrl[10].s16.hi * gte_regs.data[4].s16.lo + gte_regs.ctrl[9].s16.lo * gte_regs.data[4].s16.hi) >> 12;
  v23 = (gte_regs.ctrl[12].s16.hi * gte_regs.data[5].s16.hi
       + gte_regs.ctrl[11].s16.lo * gte_regs.data[4].s16.lo
       + gte_regs.ctrl[11].s16.hi * gte_regs.data[4].s16.hi) >> 12;
  if ( v21 >= 0 )
  {
    if ( v21 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = (gte_regs.ctrl[9].s16.hi * gte_regs.data[5].s16.hi
                            + gte_regs.ctrl[8].s16.lo * gte_regs.data[4].s16.lo
                            + gte_regs.ctrl[8].s16.hi * gte_regs.data[4].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v22 >= 0 )
  {
    if ( v22 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = (v20
                             + gte_regs.ctrl[10].s16.hi * gte_regs.data[4].s16.lo
                             + gte_regs.ctrl[9].s16.lo * gte_regs.data[4].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v23 >= 0 )
  {
    if ( v23 <= 0x7FFF )
    {
      gte_regs.data[11].u32 = (gte_regs.ctrl[12].s16.hi * gte_regs.data[5].s16.hi
                             + gte_regs.ctrl[11].s16.lo * gte_regs.data[4].s16.lo
                             + gte_regs.ctrl[11].s16.hi * gte_regs.data[4].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v24 = gte_regs.ctrl[13].u32
      + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
        + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
        + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  v25.u32 = gte_regs.ctrl[14].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  v26.u32 = gte_regs.ctrl[15].u32
          + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
            + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
            + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  if ( v24 >= 0 )
  {
    if ( v24 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = gte_regs.ctrl[13].u32
                           + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                             + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                             + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v25.s32 >= 0 )
  {
    if ( v25.s32 <= 0x7FFF )
    {
      gte_regs.data[10] = v25;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v26.s32 >= 0 )
  {
    if ( v26.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v26;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v27 = (LOBYTE(gte_regs.data[6].u32) * gte_regs.data[9].s16.hi) >> 8;
  v28 = (HIBYTE(gte_regs.data[6].u16.hi) * gte_regs.data[10].s16.hi) >> 8;
  v29 = (LOBYTE(gte_regs.data[6].s16.lo) * gte_regs.data[11].s16.hi) >> 8;
  gte_regs.data[25].u32 = v27;
  gte_regs.data[26].u32 = v28;
  gte_regs.data[27].u32 = v29;
  if ( v27 >= 0 )
  {
    if ( v27 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = (LOBYTE(gte_regs.data[6].u32) * gte_regs.data[9].s16.hi) >> 8;
    }
    else
    {
      HIBYTE(gte_regs.ctrl[31].u32) |= 0x81u;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    HIBYTE(gte_regs.ctrl[31].u32) |= 0x81u;
    gte_regs.data[9].u32 = 0;
  }
  if ( v28 >= 0 )
  {
    if ( v28 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = (HIBYTE(gte_regs.data[6].u16.hi) * gte_regs.data[10].s16.hi) >> 8;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v29 >= 0 )
  {
    if ( v29 <= 0x7FFF )
    {
      gte_regs.data[11].u32 = (LOBYTE(gte_regs.data[6].s16.lo) * gte_regs.data[11].s16.hi) >> 8;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v30 = v27 >> 4;
  gte_regs.data[20].u32 = gte_regs.data[21].u32;
  v31 = v28 >> 4;
  v32 = v29 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  dword_8A8004 = v30;
  dword_8A8008 = v31;
  dword_8A800C = v32;
  if ( v30 >= 0 )
  {
    if ( v30 <= 255 )
    {
      LOBYTE(gte_regs.data[22].u16.hi) = v30;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x200000u;
      LOBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x200000u;
    LOBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v31 >= 0 )
  {
    if ( v31 <= 255 )
    {
      HIBYTE(gte_regs.data[22].u16.hi) = v31;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x100000u;
      HIBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x100000u;
    HIBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v32 >= 0 )
  {
    if ( v32 <= 255 )
    {
      result = HIBYTE(gte_regs.data[6].u32);
      LOBYTE(gte_regs.data[22].s16.lo) = v32;
    }
    else
    {
      result = gte_regs.ctrl[31].s32;
      LOBYTE(gte_regs.data[22].s16.lo) = -1;
      gte_regs.ctrl[31].u32 |= 0x80000u;
    }
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  else
  {
    result = gte_regs.ctrl[31].s32;
    gte_regs.ctrl[31].u32 |= 0x80000u;
    LOBYTE(gte_regs.data[22].s16.lo) = 0;
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  return result;
}

char gte_cdp()
{
  GTE_REG v0; // eax
  GTE_REG v1; // ecx
  GTE_REG v2; // edx
  int v3; // esi
  int v4; // edi
  int v5; // eax
  int v6; // edx
  GTE_REG v7; // eax
  int32_t v8; // edx
  int v9; // eax

  v0.u32 = gte_regs.ctrl[13].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  v1.u32 = gte_regs.ctrl[14].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  v2.u32 = gte_regs.ctrl[15].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  gte_regs.data[25] = v0;
  gte_regs.data[26] = v1;
  gte_regs.data[27] = v2;
  if ( v0.s32 >= 0 )
  {
    if ( v0.s32 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = gte_regs.ctrl[13].u32
                           + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                             + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                             + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v1.s32 >= 0 )
  {
    if ( v1.s32 <= 0x7FFF )
    {
      gte_regs.data[10] = v1;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v2.s32 >= 0 )
  {
    if ( v2.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v2;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v3 = (gte_regs.data[10].s16.hi * HIBYTE(gte_regs.data[6].u16.hi)) >> 8;
  v4 = (gte_regs.data[11].s16.hi * LOBYTE(gte_regs.data[6].s16.lo)) >> 8;
  v5 = gte_clamp(-2130706432, gte_regs.ctrl[21].u32 - ((gte_regs.data[9].s16.hi * LOBYTE(gte_regs.data[6].u32)) >> 8));
  gte_regs.data[25].u32 = v6 + ((gte_regs.data[8].s16.hi * v5) >> 12);
  gte_regs.data[26].u32 = v3 + ((gte_regs.data[8].s16.hi * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - v3)) >> 12);
  v7.u32 = v4 + ((gte_regs.data[8].s16.hi * gte_clamp(0x400000, gte_regs.ctrl[23].u32 - v4)) >> 12);
  gte_regs.data[27] = v7;
  if ( gte_regs.data[25].s32 >= 0 )
  {
    if ( gte_regs.data[25].s32 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = gte_regs.data[25].u32;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( gte_regs.data[26].s32 >= 0 )
  {
    if ( gte_regs.data[26].s32 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = gte_regs.data[26].u32;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v7.s32 >= 0 )
  {
    if ( v7.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v7;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  gte_regs.data[20].u32 = gte_regs.data[21].u32;
  v8 = gte_regs.data[26].s32 >> 4;
  v9 = v7.s32 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  dword_8A8004 = gte_regs.data[25].s32 >> 4;
  dword_8A8008 = gte_regs.data[26].s32 >> 4;
  dword_8A800C = v9;
  if ( gte_regs.data[25].s32 >> 4 >= 0 )
  {
    if ( gte_regs.data[25].s32 >> 4 <= 255 )
    {
      LOBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[25].s32 >> 4;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x200000u;
      LOBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x200000u;
    LOBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v8 >= 0 )
  {
    if ( v8 <= 255 )
    {
      HIBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[26].s32 >> 4;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x100000u;
      HIBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x100000u;
    HIBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v9 >= 0 )
  {
    if ( v9 <= 255 )
    {
      LOBYTE(gte_regs.data[22].s16.lo) = v9;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80000u;
      LOBYTE(v9) = HIBYTE(gte_regs.data[6].u32);
      LOBYTE(gte_regs.data[22].s16.lo) = -1;
    }
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  else
  {
    LOBYTE(v9) = gte_regs.ctrl[31].u16.hi;
    LOBYTE(gte_regs.data[22].s16.lo) = 0;
    gte_regs.ctrl[31].u32 |= 0x80000u;
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  return v9;
}

char gte_cc()
{
  signed int v0; // eax
  GTE_REG v1; // ecx
  GTE_REG v2; // edx
  int v3; // eax
  int v4; // ecx
  int v5; // edx
  int v6; // eax
  int v7; // ecx
  int v8; // edx

  v0 = gte_regs.ctrl[13].u32
     + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
       + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
       + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
  v1.u32 = gte_regs.ctrl[14].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo) >> 12);
  v2.u32 = gte_regs.ctrl[15].u32
         + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
           + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
           + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
  if ( v0 >= 0 )
  {
    if ( v0 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = gte_regs.ctrl[13].u32
                           + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                             + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                             + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v1.s32 >= 0 )
  {
    if ( v1.s32 <= 0x7FFF )
    {
      gte_regs.data[10] = v1;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v2.s32 >= 0 )
  {
    if ( v2.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v2;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v3 = (gte_regs.data[9].s16.hi * LOBYTE(gte_regs.data[6].u32)) >> 8;
  gte_regs.data[25].u32 = v3;
  v4 = (gte_regs.data[10].s16.hi * HIBYTE(gte_regs.data[6].u16.hi)) >> 8;
  gte_regs.data[26].u32 = v4;
  v5 = (gte_regs.data[11].s16.hi * LOBYTE(gte_regs.data[6].s16.lo)) >> 8;
  gte_regs.data[27].u32 = v5;
  if ( v3 >= 0 )
  {
    if ( v3 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = (gte_regs.data[9].s16.hi * LOBYTE(gte_regs.data[6].u32)) >> 8;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = 0;
  }
  if ( v4 >= 0 )
  {
    if ( v4 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = (gte_regs.data[10].s16.hi * HIBYTE(gte_regs.data[6].u16.hi)) >> 8;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = 0;
  }
  if ( v5 >= 0 )
  {
    if ( v5 <= 0x7FFF )
    {
      gte_regs.data[11].u32 = (gte_regs.data[11].s16.hi * LOBYTE(gte_regs.data[6].s16.lo)) >> 8;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x400000u;
      gte_regs.data[11].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x400000u;
    gte_regs.data[11].u32 = 0;
  }
  v6 = v3 >> 4;
  gte_regs.data[20].u32 = gte_regs.data[21].u32;
  v7 = v4 >> 4;
  v8 = v5 >> 4;
  gte_regs.data[21].u32 = gte_regs.data[22].u32;
  dword_8A8004 = v6;
  dword_8A8008 = v7;
  dword_8A800C = v8;
  if ( v6 >= 0 )
  {
    if ( v6 <= 255 )
    {
      LOBYTE(gte_regs.data[22].u16.hi) = v6;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x200000u;
      LOBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x200000u;
    LOBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v7 >= 0 )
  {
    if ( v7 <= 255 )
    {
      HIBYTE(gte_regs.data[22].u16.hi) = v7;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x100000u;
      HIBYTE(gte_regs.data[22].u16.hi) = -1;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x100000u;
    HIBYTE(gte_regs.data[22].u16.hi) = 0;
  }
  if ( v8 >= 0 )
  {
    if ( v8 <= 255 )
    {
      LOBYTE(gte_regs.data[22].s16.lo) = v8;
    }
    else
    {
      LOBYTE(v6) = gte_regs.ctrl[31].u16.hi;
      gte_regs.ctrl[31].u32 |= 0x80000u;
      LOBYTE(gte_regs.data[22].s16.lo) = -1;
    }
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80000u;
    LOBYTE(gte_regs.data[22].s16.lo) = 0;
    HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
    LOBYTE(v6) = HIBYTE(gte_regs.data[6].u32);
  }
  return v6;
}

int gte_op()
{
  int result; // eax
  GTE_REG v1; // ecx
  GTE_REG v2; // edx

  result = gte_regs.data[11].s16.hi * gte_regs.ctrl[2].s16.hi - gte_regs.data[10].s16.hi * gte_regs.ctrl[4].s16.hi;
  v1.u32 = gte_regs.data[10].s16.hi * gte_regs.ctrl[0].s16.hi - gte_regs.ctrl[2].s16.hi * gte_regs.data[9].s16.hi;
  v2.u32 = gte_regs.ctrl[4].s16.hi * gte_regs.data[9].s16.hi - gte_regs.data[11].s16.hi * gte_regs.ctrl[0].s16.hi;
  gte_regs.data[25].u32 = result;
  gte_regs.data[26] = v2;
  gte_regs.data[27] = v1;
  if ( result >= (int)-0x8000u )
  {
    if ( result <= 0x7FFF )
    {
      gte_regs.data[9].u32 = gte_regs.data[11].s16.hi * gte_regs.ctrl[2].s16.hi
                           - gte_regs.data[10].s16.hi * gte_regs.ctrl[4].s16.hi;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = -0x8000u;
  }
  if ( v2.s32 >= (int)-0x8000u )
  {
    if ( v2.s32 <= 0x7FFF )
    {
      gte_regs.data[10] = v2;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = -0x8000u;
  }
  if ( v1.s32 >= (int)-0x8000u )
  {
    if ( v1.s32 <= 0x7FFF )
    {
      gte_regs.data[11] = v1;
    }
    else
    {
      gte_regs.data[11].u32 = 0x7FFF;
      result = gte_regs.ctrl[31].u32 | 0x400000;
      gte_regs.ctrl[31].u32 |= 0x400000u;
    }
  }
  else
  {
    gte_regs.data[11].u32 = -0x8000u;
    result = gte_regs.ctrl[31].u32 | 0x400000;
    gte_regs.ctrl[31].u32 |= 0x400000u;
  }
  return result;
}

GTE_REG gte_op_shifted()
{
  GTE_REG result; // eax
  int v1; // edx
  int v2; // ecx

  result.u32 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[2].s16.hi - gte_regs.data[10].s16.hi * gte_regs.ctrl[4].s16.hi) >> 12;
  v1 = (gte_regs.ctrl[4].s16.hi * gte_regs.data[9].s16.hi - gte_regs.data[11].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12;
  v2 = (gte_regs.data[10].s16.hi * gte_regs.ctrl[0].s16.hi - gte_regs.ctrl[2].s16.hi * gte_regs.data[9].s16.hi) >> 12;
  gte_regs.data[25] = result;
  gte_regs.data[26].u32 = v1;
  gte_regs.data[27].u32 = v2;
  if ( result.s32 >= -32768 )
  {
    if ( result.s32 <= 0x7FFF )
    {
      gte_regs.data[9].u32 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[2].s16.hi
                            - gte_regs.data[10].s16.hi * gte_regs.ctrl[4].s16.hi) >> 12;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x81000000;
      gte_regs.data[9].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x81000000;
    gte_regs.data[9].u32 = -32768;
  }
  if ( v1 >= -32768 )
  {
    if ( v1 <= 0x7FFF )
    {
      gte_regs.data[10].u32 = v1;
    }
    else
    {
      gte_regs.ctrl[31].u32 |= 0x80800000;
      gte_regs.data[10].u32 = 0x7FFF;
    }
  }
  else
  {
    gte_regs.ctrl[31].u32 |= 0x80800000;
    gte_regs.data[10].u32 = -32768;
  }
  if ( v2 >= -32768 )
  {
    if ( v2 <= 0x7FFF )
    {
      gte_regs.data[11].u32 = v2;
    }
    else
    {
      gte_regs.data[11].u32 = 0x7FFF;
      result.u32 = gte_regs.ctrl[31].u32 | 0x400000;
      gte_regs.ctrl[31].u32 |= 0x400000u;
    }
  }
  else
  {
    gte_regs.data[11].u32 = -32768;
    result.u32 = gte_regs.ctrl[31].u32 | 0x400000;
    gte_regs.ctrl[31].u32 |= 0x400000u;
  }
  return result;
}

int __cdecl gte_count_leading_bits(int a1)
{
  int v1; // eax
  int v2; // ecx

  v1 = a1;
  if ( a1 < 0 )
    v1 = ~a1;
  v2 = 31;
  if ( !v1 )
    return 32;
  if ( v1 >= 0 )
  {
    do
      --v2;
    while ( ((1 << v2) & v1) == 0 );
  }
  return 31 - v2;
}

char gte_exec_opcode()
{
  int v0; // eax
  int v1; // edx
  GTE_REG v2; // eax
  int32_t v3; // edx
  GTE_REG v4; // ecx
  GTE_REG v5; // edx
  int v6; // ecx
  int v7; // edx
  GTE_REG v8; // eax
  GTE_REG v9; // ecx
  GTE_REG v10; // edx
  int v11; // ecx
  int v12; // edx
  int v13; // eax
  int v14; // ecx
  int v15; // edx
  int v16; // ecx
  int v17; // edx
  GTE_REG v18; // ecx
  GTE_REG v19; // edx
  int v20; // ecx
  int v21; // edx
  GTE_REG v22; // ecx
  GTE_REG v23; // edx
  int v24; // ecx
  int v25; // edx
  unsigned int v26; // eax
  unsigned __int8 v27; // bl
  unsigned __int8 v28; // cl
  unsigned __int8 v29; // al
  int v30; // edx
  GTE_REG v31; // ecx
  GTE_REG v32; // edx
  int v33; // esi
  int v34; // edx
  int v35; // edi
  uint32_t v36; // ebp
  int v37; // ebx
  int v38; // ecx
  int v39; // ecx
  GTE_REG v40; // ebp
  int v41; // edx
  GTE_REG v42; // esi
  int v43; // esi
  int v44; // edx
  int v45; // edi
  uint32_t v46; // ebp
  int v47; // ebx
  int v48; // ecx
  GTE_REG v49; // ebp
  int v50; // ebx
  int v51; // edi
  int v52; // edx
  int v53; // esi
  int v54; // edi
  int v55; // ebp
  int v56; // ecx
  int v57; // edx
  int v58; // esi
  int v59; // edi
  int v60; // ebx
  int v61; // ecx
  int v62; // edx
  int v63; // ecx
  int v64; // edx
  int v65; // ebp
  int v66; // edi
  int v67; // edx
  GTE_REG v68; // edi
  int v69; // edi
  int v70; // ebx
  int v71; // esi
  int v72; // edx
  int v73; // edi
  int v74; // esi
  GTE_REG v75; // ebp
  int v76; // edx
  int v77; // edi
  uint32_t v78; // ebp
  int v79; // ebx
  int v80; // ecx
  int v81; // edx
  int v82; // edi
  int v83; // esi
  uint32_t v84; // ebp
  int v85; // ebx
  int v86; // ecx
  uint32_t v87; // ebp
  int v88; // ebx
  int v89; // ecx
  int v90; // edi
  int v91; // ebp
  int v92; // ecx
  int v93; // edx
  int v94; // edi
  int v95; // ebx
  int v96; // esi
  int v97; // ecx
  int v98; // edx
  int v99; // edi
  int v100; // ebx
  int v101; // esi
  int v102; // eax
  int v103; // ecx
  int v104; // edx
  int v105; // edx
  int v106; // ebx
  int v107; // edi
  GTE_REG v108; // ebp
  int v109; // esi
  int v110; // edi
  int v111; // ebp
  int v112; // ecx
  int v113; // edx
  int v114; // edx
  int v115; // ebp
  int v116; // edi
  int v117; // edx
  int v118; // esi
  int lo; // edi
  int hi; // ebp
  int v121; // ecx
  int v122; // edx
  int v123; // edx
  int v124; // ebp
  int v125; // edi
  int v126; // edx
  int v127; // esi
  int v128; // edi
  int v129; // ebp
  int v130; // ecx
  int v131; // edx
  int v132; // esi
  int v133; // edi
  int v134; // ebx
  int v135; // ecx
  int v136; // edx
  int v137; // ecx
  int v138; // edx
  int v139; // ebx
  int v140; // edi
  int v141; // esi
  int v142; // edi
  int v143; // ebp
  int v144; // ecx
  int v145; // edx
  int v146; // edx
  int v147; // ebp
  int v148; // edi
  int v149; // edx
  int v150; // edi
  int v151; // ebx
  int v152; // ecx
  int v153; // edx
  int v154; // edi
  int v155; // ebp
  int v156; // ecx
  int v157; // edx
  int v158; // edi
  int v159; // ebp
  int v160; // ecx
  int v161; // edx
  int v162; // edi
  int v163; // ebx
  int v164; // ecx
  int v165; // edx
  int v166; // edi
  int v167; // ebx
  int v168; // ecx
  int v169; // edx
  int v170; // edi
  int v171; // ebp
  int v172; // esi
  int v173; // ecx
  int v174; // edx
  int v175; // edi
  int v176; // ebx
  int v177; // ecx
  int v178; // edx
  int v179; // edi
  int v180; // ebp
  int v181; // ecx
  int v182; // edx
  int v183; // ecx
  int v184; // ecx

  LOBYTE(v26) = cpu_opcode;
  switch ( ((unsigned int)cpu_opcode >> 21) & 0x1F )
  {
    case 0u:
      v27 = BYTE2(cpu_opcode) & 0x1F;
      v28 = ((unsigned int)cpu_opcode >> 11) & 0x1F;
      byte_8A7EE0 = BYTE2(cpu_opcode) & 0x1F;
      byte_8A8001 = v28;
      if ( (cpu_opcode & 0x1F0000) != 0 )
      {
        if ( v28 == 31 )
        {
          v26 = (unsigned __int8)gte_count_leading_bits(gte_regs.data[30].s32);
          cpu_gpr[v27] = v26;
        }
        else
        {
          if ( v28 == 29 )
          {
            gte_convert_to_5bit(gte_regs.data[11].u16.hi);
            gte_convert_to_5bit(gte_regs.data[10].u16.hi);
            v29 = gte_convert_to_5bit(gte_regs.data[9].u16.hi);
            v27 = byte_8A7EE0;
            gte_regs.data[29].u32 = v29 | v30;
          }
          LOBYTE(v26) = v27;
          cpu_gpr[v27] = gte_regs.data[v28].s32;
        }
      }
      return v26;
    case 2u:
      LOBYTE(v26) = ((unsigned int)cpu_opcode >> 11) & 0x1F;
      byte_8A7EE0 = BYTE2(cpu_opcode) & 0x1F;
      byte_8A8000 = v26;
      if ( (cpu_opcode & 0x1F0000) != 0 )
      {
        v26 = BYTE2(cpu_opcode) & 0x1F;
        cpu_gpr[v26] = gte_regs.ctrl[(unsigned __int16)cpu_opcode >> 11].s32;
      }
      return v26;
    case 4u:
      LOBYTE(v26) = ((unsigned int)cpu_opcode >> 11) & 0x1F;
      byte_8A7EE0 = BYTE2(cpu_opcode) & 0x1F;
      byte_8A8001 = v26;
      v31.u32 = cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
      gte_regs.data[(unsigned __int8)v26] = v31;
      if ( (unsigned __int8)v26 >= 0x10u && (unsigned __int8)v26 <= 0x13u )
        gte_regs.data[(unsigned __int8)v26].u32 = v31.u16.hi;
      switch ( (_BYTE)v26 )
      {
        case 0xE:
          gte_regs.data[15] = v31;
          break;
        case 0xF:
          LOBYTE(v26) = gte_regs.data[13].u16.hi;
          gte_regs.data[12].u32 = gte_regs.data[13].u32;
          gte_regs.data[13].u32 = gte_regs.data[14].u32;
          gte_regs.data[14] = v31;
          break;
        case 0x1C:
          v26 = (gte_regs.data[28].u16.hi >> 3) & 0xF80;
          gte_regs.data[9].u32 = (gte_regs.data[28].u16.hi & 0x1F) << 7;
          gte_regs.data[10].u32 = 4 * (gte_regs.data[28].u16.hi & 0x3E0);
          gte_regs.data[11].u32 = v26;
          break;
      }
      return v26;
    case 6u:
      LOBYTE(v26) = ((unsigned int)cpu_opcode >> 11) & 0x1F;
      byte_8A7EE0 = BYTE2(cpu_opcode) & 0x1F;
      v32.u32 = cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
      byte_8A8000 = v26;
      gte_regs.ctrl[(unsigned __int8)v26] = v32;
      return v26;
    default:
      v26 = cpu_opcode & 0x1FFFFFF;
      gte_regs.ctrl[31].u32 = 0;
      if ( (cpu_opcode & 0x1FFFFFFu) <= 0x48A412 )
      {
        if ( v26 == 4760594 )
        {
          lo = gte_regs.data[2].s16.lo;
          hi = gte_regs.data[2].s16.hi;
          v118 = gte_regs.data[3].s16.hi;
          v26 = gte_regs.ctrl[13].u32
              + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
          v121 = gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
          v122 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
          goto LABEL_314;
        }
        if ( v26 <= 0x432012 )
        {
          if ( v26 == 4399122 )
          {
            v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi
                + gte_regs.ctrl[13].u32
                + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                + gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi;
            v39 = gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo
                + gte_regs.ctrl[14].u32
                + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                + gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo;
            v41 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi
                + gte_regs.ctrl[15].u32
                + gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo
                + gte_regs.data[5].s16.hi * gte_regs.ctrl[12].s16.hi;
            v42.u32 = -32768;
            goto LABEL_56;
          }
          if ( v26 <= 0x416012 )
          {
            if ( v26 == 4284434 )
            {
              v59 = gte_regs.data[4].s16.lo;
              v60 = gte_regs.data[4].s16.hi;
              v58 = gte_regs.data[5].s16.hi;
              v26 = gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                  + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi;
              v61 = gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                  + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
              v62 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
              goto LABEL_80;
            }
            if ( v26 <= 0x408012 )
            {
              if ( v26 == 4227090 )
              {
                v34 = gte_regs.data[2].s16.lo;
                v35 = gte_regs.data[2].s16.hi;
                v33 = gte_regs.data[3].s16.hi;
                v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi
                    + gte_regs.ctrl[5].u32
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi;
                v36 = gte_regs.ctrl[6].u32 + gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi;
                v37 = gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
                v38 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
                goto LABEL_43;
              }
              if ( v26 <= 0x400412 )
              {
                if ( v26 != 0x400412 )
                {
                  if ( v26 <= 0x198001 )
                  {
                    if ( v26 == 0x198001 )
                      goto LABEL_37;
                    if ( v26 != 0x140006 )
                    {
                      if ( v26 != 0x180001 )
                      {
                        if ( v26 != 0x18041B )
                          goto LABEL_630;
LABEL_602:
                        LOBYTE(v26) = gte_nccs();
                        return v26;
                      }
LABEL_37:
                      LOBYTE(v26) = gte_rtps();
                      return v26;
                    }
LABEL_612:
                    v26 = gte_regs.data[14].s16.hi * (gte_regs.data[12].s16.lo - gte_regs.data[13].s16.lo);
                    gte_regs.data[24].u32 = v26
                                          + gte_regs.data[13].s16.hi
                                          * (gte_regs.data[14].s16.lo - gte_regs.data[12].s16.lo)
                                          + gte_regs.data[12].s16.hi
                                          * (gte_regs.data[13].s16.lo - gte_regs.data[14].s16.lo);
                    return v26;
                  }
                  if ( v26 == 0x280030 )
                  {
                    LOBYTE(v26) = gte_rtpt();
                    return v26;
                  }
                  if ( v26 == 0x400006 )
                    goto LABEL_612;
                  if ( v26 != 0x400012 )
                    goto LABEL_630;
                  v33 = gte_regs.data[1].s16.hi;
                  v34 = gte_regs.data[0].s16.lo;
                  v35 = gte_regs.data[0].s16.hi;
                  goto LABEL_42;
                }
                v43 = gte_regs.data[1].s16.hi;
                v44 = gte_regs.data[0].s16.lo;
                v45 = gte_regs.data[0].s16.hi;
LABEL_52:
                v26 = v45 * gte_regs.ctrl[0].s16.hi
                    + gte_regs.ctrl[5].u32
                    + v44 * gte_regs.ctrl[0].s16.lo
                    + v43 * gte_regs.ctrl[1].s16.hi;
                v46 = gte_regs.ctrl[6].u32 + v45 * gte_regs.ctrl[1].s16.lo;
                v47 = v43 * gte_regs.ctrl[2].s16.lo;
                v48 = v44 * gte_regs.ctrl[2].s16.hi;
LABEL_53:
                v39 = v47 + v46 + v48;
                v49 = gte_regs.ctrl[7];
LABEL_54:
                v50 = v45 * gte_regs.ctrl[3].s16.hi;
                v51 = v44 * gte_regs.ctrl[3].s16.lo;
                v52 = gte_regs.ctrl[4].s16.hi;
LABEL_55:
                v41 = v50 + v49.u32 + v51 + v43 * v52;
                v42.u32 = 0;
                goto LABEL_56;
              }
              if ( v26 <= 0x404412 )
              {
                if ( v26 != 0x404412 )
                {
                  if ( v26 == 0x402012 )
                  {
                    v34 = gte_regs.data[0].s16.lo;
                    v35 = gte_regs.data[0].s16.hi;
                    v33 = gte_regs.data[1].s16.hi;
                    v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[0].s16.hi
                        + gte_regs.ctrl[13].u32
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[1].s16.hi * gte_regs.ctrl[1].s16.hi;
                    v39 = gte_regs.data[1].s16.hi * gte_regs.ctrl[2].s16.lo
                        + gte_regs.ctrl[14].u32
                        + gte_regs.data[0].s16.hi * gte_regs.ctrl[1].s16.lo
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[2].s16.hi;
                    v40 = gte_regs.ctrl[15];
                    goto LABEL_44;
                  }
                  if ( v26 != 4203538 )
                  {
                    if ( v26 != 4210706 )
                      goto LABEL_630;
                    v34 = gte_regs.data[0].s16.lo;
                    v35 = gte_regs.data[0].s16.hi;
                    v33 = gte_regs.data[1].s16.hi;
                    v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[0].s16.hi
                        + gte_regs.ctrl[21].u32
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[1].s16.hi * gte_regs.ctrl[1].s16.hi;
                    v39 = gte_regs.data[1].s16.hi * gte_regs.ctrl[2].s16.lo
                        + gte_regs.ctrl[22].u32
                        + gte_regs.data[0].s16.hi * gte_regs.ctrl[1].s16.lo
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[2].s16.hi;
                    v40 = gte_regs.ctrl[23];
                    goto LABEL_44;
                  }
                  v44 = gte_regs.data[0].s16.lo;
                  v45 = gte_regs.data[0].s16.hi;
                  v43 = gte_regs.data[1].s16.hi;
                  v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[0].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[1].s16.hi * gte_regs.ctrl[1].s16.hi;
                  v39 = gte_regs.data[1].s16.hi * gte_regs.ctrl[2].s16.lo
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[1].s16.lo
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[2].s16.hi;
                  v49 = gte_regs.ctrl[15];
                  goto LABEL_54;
                }
                v43 = gte_regs.data[1].s16.hi;
                v44 = gte_regs.data[0].s16.lo;
                v45 = gte_regs.data[0].s16.hi;
                goto LABEL_138;
              }
              if ( v26 != 4218898 )
              {
                if ( v26 != 4219922 )
                  goto LABEL_630;
                v53 = gte_regs.data[1].s16.hi;
                v54 = gte_regs.data[0].s16.lo;
                v55 = gte_regs.data[0].s16.hi;
                goto LABEL_72;
              }
              v58 = gte_regs.data[1].s16.hi;
              v59 = gte_regs.data[0].s16.lo;
              v60 = gte_regs.data[0].s16.hi;
              goto LABEL_79;
            }
            if ( v26 > 0x40E412 )
            {
              if ( v26 > 0x412412 )
              {
                if ( v26 == 4276242 )
                {
                  v34 = gte_regs.data[4].s16.lo;
                  v35 = gte_regs.data[4].s16.hi;
                  v33 = gte_regs.data[5].s16.hi;
                  v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi
                      + gte_regs.ctrl[21].u32
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi;
                  v39 = gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo
                      + gte_regs.ctrl[22].u32
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                  v40 = gte_regs.ctrl[23];
                  goto LABEL_44;
                }
                if ( v26 != 4277266 )
                  goto LABEL_630;
                v44 = gte_regs.data[4].s16.lo;
                v45 = gte_regs.data[4].s16.hi;
                v43 = gte_regs.data[5].s16.hi;
                v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi
                    + gte_regs.ctrl[21].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi;
                v39 = gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo
                    + gte_regs.ctrl[22].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                v49 = gte_regs.ctrl[23];
                goto LABEL_54;
              }
              if ( v26 == 4269074 )
              {
                v44 = gte_regs.data[4].s16.lo;
                v45 = gte_regs.data[4].s16.hi;
                v43 = gte_regs.data[5].s16.hi;
                v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi
                    + gte_regs.ctrl[13].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi;
                v39 = gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo
                    + gte_regs.ctrl[14].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                v49 = gte_regs.ctrl[15];
                goto LABEL_54;
              }
              if ( v26 == 4259858 )
              {
                v34 = gte_regs.data[4].s16.lo;
                v35 = gte_regs.data[4].s16.hi;
                v33 = gte_regs.data[5].s16.hi;
                v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi
                    + gte_regs.ctrl[5].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi;
                v36 = gte_regs.ctrl[6].u32 + gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi;
                v37 = gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
                v38 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                goto LABEL_43;
              }
              if ( v26 != 4260882 )
              {
                if ( v26 != 4268050 )
                  goto LABEL_630;
                v34 = gte_regs.data[4].s16.lo;
                v35 = gte_regs.data[4].s16.hi;
                v33 = gte_regs.data[5].s16.hi;
                v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi
                    + gte_regs.ctrl[13].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi;
                v39 = gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo
                    + gte_regs.ctrl[14].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                v40 = gte_regs.ctrl[15];
                goto LABEL_44;
              }
              v44 = gte_regs.data[4].s16.lo;
              v45 = gte_regs.data[4].s16.hi;
              v43 = gte_regs.data[5].s16.hi;
              v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi
                  + gte_regs.ctrl[5].u32
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi;
              v46 = gte_regs.ctrl[6].u32 + gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi;
              v47 = gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
              v48 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
              goto LABEL_53;
            }
            if ( v26 != 4252690 )
            {
              if ( v26 <= 0x40C012 )
              {
                if ( v26 == 4243474 )
                {
                  v34 = gte_regs.data[2].s16.lo;
                  v35 = gte_regs.data[2].s16.hi;
                  v33 = gte_regs.data[3].s16.hi;
                  v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi
                      + gte_regs.ctrl[21].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi;
                  v39 = gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo
                      + gte_regs.ctrl[22].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
                  v40 = gte_regs.ctrl[23];
                  goto LABEL_44;
                }
                if ( v26 != 4228114 )
                {
                  if ( v26 == 4235282 )
                  {
                    v34 = gte_regs.data[2].s16.lo;
                    v35 = gte_regs.data[2].s16.hi;
                    v33 = gte_regs.data[3].s16.hi;
                    v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi
                        + gte_regs.ctrl[13].u32
                        + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi;
                    v39 = gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo
                        + gte_regs.ctrl[14].u32
                        + gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                        + gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
                    v40 = gte_regs.ctrl[15];
                    goto LABEL_44;
                  }
                  if ( v26 != 4236306 )
                    goto LABEL_630;
                  v44 = gte_regs.data[2].s16.lo;
                  v45 = gte_regs.data[2].s16.hi;
                  v43 = gte_regs.data[3].s16.hi;
                  v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi;
                  v39 = gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
                  v49 = gte_regs.ctrl[15];
                  goto LABEL_54;
                }
                v44 = gte_regs.data[2].s16.lo;
                v45 = gte_regs.data[2].s16.hi;
                v43 = gte_regs.data[3].s16.hi;
                v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi
                    + gte_regs.ctrl[5].u32
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi;
                v46 = gte_regs.ctrl[6].u32 + gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi;
                v47 = gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
                v48 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
                goto LABEL_53;
              }
              if ( v26 == 4244498 )
              {
                v44 = gte_regs.data[2].s16.lo;
                v45 = gte_regs.data[2].s16.hi;
                v43 = gte_regs.data[3].s16.hi;
                v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi
                    + gte_regs.ctrl[21].u32
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi;
                v39 = gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo
                    + gte_regs.ctrl[22].u32
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
                v49 = gte_regs.ctrl[23];
                goto LABEL_54;
              }
              if ( v26 != 4251666 )
                goto LABEL_630;
              v59 = gte_regs.data[2].s16.lo;
              v60 = gte_regs.data[2].s16.hi;
              v58 = gte_regs.data[3].s16.hi;
              v26 = gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                  + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                  + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi;
              v61 = gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                  + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
              v62 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
              goto LABEL_80;
            }
            v53 = gte_regs.data[3].s16.hi;
            v54 = gte_regs.data[2].s16.lo;
            v55 = gte_regs.data[2].s16.hi;
LABEL_98:
            v26 = v53 * gte_regs.ctrl[1].s16.hi + v54 * gte_regs.ctrl[0].s16.lo + v55 * gte_regs.ctrl[0].s16.hi;
            v56 = v54 * gte_regs.ctrl[2].s16.hi + v55 * gte_regs.ctrl[1].s16.lo;
            v57 = v53 * gte_regs.ctrl[2].s16.lo;
            goto LABEL_99;
          }
          if ( v26 <= 0x424012 )
          {
            if ( v26 == 4341778 )
            {
              v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi
                  + gte_regs.ctrl[21].u32
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                  + gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi;
              v39 = gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo
                  + gte_regs.ctrl[22].u32
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                  + gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo;
              v41 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi
                  + gte_regs.ctrl[23].u32
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo
                  + gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi;
              v42.u32 = -32768;
            }
            else
            {
              if ( v26 <= 0x41C412 )
              {
                if ( v26 == 4310034 )
                {
                  v43 = gte_regs.data[11].s16.hi;
                  v44 = gte_regs.data[10].s16.hi;
                  v45 = gte_regs.data[9].s16.hi;
LABEL_138:
                  v26 = v45 * gte_regs.ctrl[0].s16.hi
                      + gte_regs.ctrl[21].u32
                      + v44 * gte_regs.ctrl[0].s16.lo
                      + v43 * gte_regs.ctrl[1].s16.hi;
                  v39 = v43 * gte_regs.ctrl[2].s16.lo
                      + gte_regs.ctrl[22].u32
                      + v45 * gte_regs.ctrl[1].s16.lo
                      + v44 * gte_regs.ctrl[2].s16.hi;
                  v49 = gte_regs.ctrl[23];
                  goto LABEL_54;
                }
                if ( v26 > 0x41A012 )
                {
                  if ( v26 != 4301842 )
                  {
                    if ( v26 != 4309010 )
                      goto LABEL_630;
                    v34 = gte_regs.data[10].s16.hi;
                    v35 = gte_regs.data[9].s16.hi;
                    v33 = gte_regs.data[11].s16.hi;
                    v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[0].s16.hi
                        + gte_regs.ctrl[21].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[1].s16.hi;
                    v39 = gte_regs.data[11].s16.hi * gte_regs.ctrl[2].s16.lo
                        + gte_regs.ctrl[22].u32
                        + gte_regs.data[9].s16.hi * gte_regs.ctrl[1].s16.lo
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[2].s16.hi;
                    v40 = gte_regs.ctrl[23];
                    goto LABEL_44;
                  }
                  v44 = gte_regs.data[10].s16.hi;
                  v45 = gte_regs.data[9].s16.hi;
                  v43 = gte_regs.data[11].s16.hi;
                  v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[0].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[11].s16.hi * gte_regs.ctrl[1].s16.hi;
                  v39 = gte_regs.data[11].s16.hi * gte_regs.ctrl[2].s16.lo
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[1].s16.lo
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[2].s16.hi;
                  v49 = gte_regs.ctrl[15];
                  goto LABEL_54;
                }
                if ( v26 == 4300818 )
                {
                  v34 = gte_regs.data[10].s16.hi;
                  v35 = gte_regs.data[9].s16.hi;
                  v33 = gte_regs.data[11].s16.hi;
                  v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[0].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[11].s16.hi * gte_regs.ctrl[1].s16.hi;
                  v39 = gte_regs.data[11].s16.hi * gte_regs.ctrl[2].s16.lo
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[1].s16.lo
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[2].s16.hi;
                  v40 = gte_regs.ctrl[15];
                  goto LABEL_44;
                }
                if ( v26 != 4285458 )
                {
                  if ( v26 == 4292626 )
                  {
                    v33 = gte_regs.data[11].s16.hi;
                    v34 = gte_regs.data[10].s16.hi;
                    v35 = gte_regs.data[9].s16.hi;
LABEL_42:
                    v26 = v35 * gte_regs.ctrl[0].s16.hi
                        + gte_regs.ctrl[5].u32
                        + v34 * gte_regs.ctrl[0].s16.lo
                        + v33 * gte_regs.ctrl[1].s16.hi;
                    v36 = gte_regs.ctrl[6].u32 + v35 * gte_regs.ctrl[1].s16.lo;
                    v37 = v33 * gte_regs.ctrl[2].s16.lo;
                    v38 = v34 * gte_regs.ctrl[2].s16.hi;
LABEL_43:
                    v39 = v37 + v36 + v38;
                    v40 = gte_regs.ctrl[7];
LABEL_44:
                    v41 = v35 * gte_regs.ctrl[3].s16.hi
                        + v40.u32
                        + v34 * gte_regs.ctrl[3].s16.lo
                        + v33 * gte_regs.ctrl[4].s16.hi;
                    v42.u32 = -32768;
                    goto LABEL_56;
                  }
                  if ( v26 != 4293650 )
                    goto LABEL_630;
                  v43 = gte_regs.data[11].s16.hi;
                  v44 = gte_regs.data[10].s16.hi;
                  v45 = gte_regs.data[9].s16.hi;
                  goto LABEL_52;
                }
                v53 = gte_regs.data[5].s16.hi;
                v54 = gte_regs.data[4].s16.lo;
                v55 = gte_regs.data[4].s16.hi;
                goto LABEL_98;
              }
              if ( v26 > 0x420412 )
              {
                if ( v26 != 4333586 )
                {
                  if ( v26 != 4334610 )
                    goto LABEL_630;
                  v43 = gte_regs.data[1].s16.hi;
                  v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi;
                  v50 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
                  v39 = gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo;
                  v51 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
                  v49 = gte_regs.ctrl[15];
                  v52 = gte_regs.ctrl[12].s16.hi;
                  goto LABEL_55;
                }
                v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi
                    + gte_regs.ctrl[13].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi;
                v39 = gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo
                    + gte_regs.ctrl[14].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo;
                v41 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi
                    + gte_regs.ctrl[15].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi;
                v42.u32 = -32768;
              }
              else
              {
                switch ( v26 )
                {
                  case 0x420412u:
                    v43 = gte_regs.data[1].s16.hi;
                    v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi
                        + gte_regs.ctrl[5].u32
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                        + gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi;
                    v50 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
                    v39 = gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo
                        + gte_regs.ctrl[6].u32
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                        + gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo;
                    v51 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
                    v49 = gte_regs.ctrl[7];
                    v52 = gte_regs.ctrl[12].s16.hi;
                    goto LABEL_55;
                  case 0x41E012u:
                    v58 = gte_regs.data[11].s16.hi;
                    v59 = gte_regs.data[10].s16.hi;
                    v60 = gte_regs.data[9].s16.hi;
LABEL_79:
                    v26 = v58 * gte_regs.ctrl[1].s16.hi + v59 * gte_regs.ctrl[0].s16.lo + v60 * gte_regs.ctrl[0].s16.hi;
                    v61 = v60 * gte_regs.ctrl[1].s16.lo + v58 * gte_regs.ctrl[2].s16.lo;
                    v62 = v59 * gte_regs.ctrl[2].s16.hi;
LABEL_80:
                    v39 = v62 + v61;
                    v41 = v58 * gte_regs.ctrl[4].s16.hi + v59 * gte_regs.ctrl[3].s16.lo + v60 * gte_regs.ctrl[3].s16.hi;
                    v42.u32 = -32768;
                    goto LABEL_56;
                  case 0x41E412u:
                    v53 = gte_regs.data[11].s16.hi;
                    v54 = gte_regs.data[10].s16.hi;
                    v55 = gte_regs.data[9].s16.hi;
LABEL_72:
                    v26 = v53 * gte_regs.ctrl[1].s16.hi + v54 * gte_regs.ctrl[0].s16.lo + v55 * gte_regs.ctrl[0].s16.hi;
                    v56 = v55 * gte_regs.ctrl[1].s16.lo + v53 * gte_regs.ctrl[2].s16.lo;
                    v57 = v54 * gte_regs.ctrl[2].s16.hi;
LABEL_99:
                    v63 = v57 + v56;
                    v64 = v55 * gte_regs.ctrl[3].s16.hi;
                    v65 = v54 * gte_regs.ctrl[3].s16.lo;
                    v66 = gte_regs.ctrl[4].s16.hi;
LABEL_100:
                    v67 = v65 + v64;
                    v68.u32 = v53 * v66;
LABEL_101:
                    v41 = v68.u32 + v67;
                    goto LABEL_102;
                }
                if ( v26 != 4325394 )
                  goto LABEL_630;
                v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi
                    + gte_regs.ctrl[5].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi;
                v39 = gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo
                    + gte_regs.ctrl[6].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo;
                v41 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi
                    + gte_regs.ctrl[7].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi;
                v42.u32 = -32768;
              }
            }
LABEL_56:
            gte_regs.data[25].u32 = v26;
            gte_regs.data[26].u32 = v39;
            gte_regs.data[27].u32 = v41;
            if ( (int)v26 >= v42.s32 )
            {
              if ( (int)v26 <= 0x7FFF )
              {
                gte_regs.data[9].u32 = v26;
              }
              else
              {
                gte_regs.ctrl[31].u32 = -2130706432;
                gte_regs.data[9].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 = -2130706432;
              gte_regs.data[9] = v42;
            }
            if ( v39 >= v42.s32 )
            {
              if ( v39 <= 0x7FFF )
              {
                gte_regs.data[10].u32 = v39;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80800000;
                gte_regs.data[10].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x80800000;
              gte_regs.data[10] = v42;
            }
            if ( v41 >= v42.s32 )
            {
LABEL_541:
              if ( v41 <= 0x7FFF )
              {
                gte_regs.data[11].u32 = v41;
              }
              else
              {
                gte_regs.data[11].u32 = 0x7FFF;
                LOBYTE(v26) = gte_regs.ctrl[31].u16.hi;
                gte_regs.ctrl[31].u32 |= 0x400000u;
              }
              return v26;
            }
LABEL_558:
            gte_regs.data[11] = v42;
            LOBYTE(v26) = gte_regs.ctrl[31].u16.hi;
            gte_regs.ctrl[31].u32 |= 0x400000u;
            return v26;
          }
          if ( v26 > 0x42A412 )
          {
            if ( v26 > 0x42E412 )
            {
              if ( v26 != 4390930 )
              {
                if ( v26 != 4391954 )
                  goto LABEL_630;
                v43 = gte_regs.data[5].s16.hi;
                v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi
                    + gte_regs.ctrl[5].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi;
                v50 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
                v39 = gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo
                    + gte_regs.ctrl[6].u32
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo;
                v51 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
                v49 = gte_regs.ctrl[7];
                v52 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_55;
              }
              v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi
                  + gte_regs.ctrl[5].u32
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi;
              v39 = gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo
                  + gte_regs.ctrl[6].u32
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo;
              v41 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi
                  + gte_regs.ctrl[7].u32
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[12].s16.hi;
              v42.u32 = -32768;
            }
            else
            {
              switch ( v26 )
              {
                case 0x42E412u:
                  v53 = gte_regs.data[3].s16.hi;
                  v26 = gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi;
                  v63 = gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo;
                  v64 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
                  v65 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
                  v66 = gte_regs.ctrl[12].s16.hi;
                  goto LABEL_100;
                case 0x42C012u:
                  v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi
                      + gte_regs.ctrl[21].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi;
                  v39 = gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo
                      + gte_regs.ctrl[22].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo;
                  v41 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi
                      + gte_regs.ctrl[23].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[12].s16.hi;
                  v42.u32 = -32768;
                  break;
                case 0x42C412u:
                  v43 = gte_regs.data[3].s16.hi;
                  v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi
                      + gte_regs.ctrl[21].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi;
                  v50 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
                  v39 = gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo
                      + gte_regs.ctrl[22].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo;
                  v51 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
                  v49 = gte_regs.ctrl[23];
                  v52 = gte_regs.ctrl[12].s16.hi;
                  goto LABEL_55;
                case 0x42E012u:
                  v26 = gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi;
                  v39 = gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo;
                  v41 = gte_regs.data[3].s16.hi * gte_regs.ctrl[12].s16.hi
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
                  v42.u32 = -32768;
                  break;
                default:
                  goto LABEL_630;
              }
            }
            goto LABEL_56;
          }
          if ( v26 == 4367378 )
          {
            v43 = gte_regs.data[3].s16.hi;
            v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi
                + gte_regs.ctrl[13].u32
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                + gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi;
            v50 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
            v39 = gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo
                + gte_regs.ctrl[14].u32
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                + gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo;
            v51 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
            v49 = gte_regs.ctrl[15];
            v52 = gte_regs.ctrl[12].s16.hi;
            goto LABEL_55;
          }
          if ( v26 > 0x428012 )
          {
            if ( v26 == 4359186 )
            {
              v43 = gte_regs.data[3].s16.hi;
              v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi
                  + gte_regs.ctrl[5].u32
                  + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                  + gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi;
              v50 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
              v39 = gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo
                  + gte_regs.ctrl[6].u32
                  + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                  + gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo;
              v51 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
              v49 = gte_regs.ctrl[7];
              v52 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_55;
            }
            if ( v26 != 4366354 )
              goto LABEL_630;
            v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi
                + gte_regs.ctrl[13].u32
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                + gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi;
            v39 = gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo
                + gte_regs.ctrl[14].u32
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                + gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo;
            v41 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi
                + gte_regs.ctrl[15].u32
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo
                + gte_regs.data[3].s16.hi * gte_regs.ctrl[12].s16.hi;
            v42.u32 = -32768;
            goto LABEL_56;
          }
          if ( v26 == 4358162 )
          {
            v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi
                + gte_regs.ctrl[5].u32
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                + gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi;
            v39 = gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo
                + gte_regs.ctrl[6].u32
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                + gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo;
            v41 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi
                + gte_regs.ctrl[7].u32
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo
                + gte_regs.data[3].s16.hi * gte_regs.ctrl[12].s16.hi;
            v42.u32 = -32768;
            goto LABEL_56;
          }
          if ( v26 == 4342802 )
          {
            v43 = gte_regs.data[1].s16.hi;
            v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi
                + gte_regs.ctrl[21].u32
                + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                + gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi;
            v50 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
            v39 = gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo
                + gte_regs.ctrl[22].u32
                + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                + gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo;
            v51 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
            v49 = gte_regs.ctrl[23];
            v52 = gte_regs.ctrl[12].s16.hi;
            goto LABEL_55;
          }
          if ( v26 != 4349970 )
          {
            if ( v26 != 4350994 )
              goto LABEL_630;
            v53 = gte_regs.data[1].s16.hi;
            v26 = gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi;
            v63 = gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo;
            v64 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
            v65 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
            v66 = gte_regs.ctrl[12].s16.hi;
            goto LABEL_100;
          }
          v69 = gte_regs.data[0].s16.lo;
          v70 = gte_regs.data[0].s16.hi;
          v71 = gte_regs.data[1].s16.hi;
          v26 = gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
              + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
              + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi;
LABEL_214:
          v39 = v71 * gte_regs.ctrl[10].s16.lo + v69 * gte_regs.ctrl[10].s16.hi + v70 * gte_regs.ctrl[9].s16.lo;
          v41 = v71 * gte_regs.ctrl[12].s16.hi + v69 * gte_regs.ctrl[11].s16.lo + v70 * gte_regs.ctrl[11].s16.hi;
          v42.u32 = -32768;
          goto LABEL_56;
        }
        if ( v26 <= 0x44E412 )
        {
          if ( v26 != 4514834 )
          {
            if ( v26 <= 0x440412 )
            {
              if ( v26 != 4457490 )
              {
                if ( v26 <= 0x43A012 )
                {
                  if ( v26 == 4431890 )
                  {
                    v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi
                        + gte_regs.ctrl[13].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi;
                    v39 = gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo
                        + gte_regs.ctrl[14].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo;
                    v41 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi
                        + gte_regs.ctrl[15].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[12].s16.hi;
                    v42.u32 = -32768;
                  }
                  else if ( v26 > 0x436012 )
                  {
                    if ( v26 == 4416530 )
                    {
                      v53 = gte_regs.data[5].s16.hi;
                      v26 = gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                          + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                          + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi;
                      v63 = gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                          + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                          + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo;
                      v64 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
                      v65 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
                      v66 = gte_regs.ctrl[12].s16.hi;
                      goto LABEL_100;
                    }
                    if ( v26 != 4423698 )
                    {
                      if ( v26 != 4424722 )
                        goto LABEL_630;
                      v43 = gte_regs.data[11].s16.hi;
                      v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi
                          + gte_regs.ctrl[5].u32
                          + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                          + gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi;
                      v50 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
                      v39 = gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo
                          + gte_regs.ctrl[6].u32
                          + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                          + gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo;
                      v51 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
                      v49 = gte_regs.ctrl[7];
                      v52 = gte_regs.ctrl[12].s16.hi;
                      goto LABEL_55;
                    }
                    v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi
                        + gte_regs.ctrl[5].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi;
                    v39 = gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo
                        + gte_regs.ctrl[6].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo;
                    v41 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi
                        + gte_regs.ctrl[7].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[12].s16.hi;
                    v42.u32 = -32768;
                  }
                  else
                  {
                    switch ( v26 )
                    {
                      case 0x436012u:
                        v26 = gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                            + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi;
                        v39 = gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                            + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo;
                        v41 = gte_regs.data[5].s16.hi * gte_regs.ctrl[12].s16.hi
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo
                            + gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
                        v42.u32 = -32768;
                        break;
                      case 0x432412u:
                        v43 = gte_regs.data[5].s16.hi;
                        v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi
                            + gte_regs.ctrl[13].u32
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                            + gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi;
                        v50 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
                        v39 = gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo
                            + gte_regs.ctrl[14].u32
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                            + gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo;
                        v51 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
                        v49 = gte_regs.ctrl[15];
                        v52 = gte_regs.ctrl[12].s16.hi;
                        goto LABEL_55;
                      case 0x434012u:
                        v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi
                            + gte_regs.ctrl[21].u32
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                            + gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi;
                        v39 = gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo
                            + gte_regs.ctrl[22].u32
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                            + gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo;
                        v41 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi
                            + gte_regs.ctrl[23].u32
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo
                            + gte_regs.data[5].s16.hi * gte_regs.ctrl[12].s16.hi;
                        v42.u32 = -32768;
                        break;
                      case 0x434412u:
                        v43 = gte_regs.data[5].s16.hi;
                        v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi
                            + gte_regs.ctrl[21].u32
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                            + gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi;
                        v50 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
                        v39 = gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo
                            + gte_regs.ctrl[22].u32
                            + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                            + gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo;
                        v51 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
                        v49 = gte_regs.ctrl[23];
                        v52 = gte_regs.ctrl[12].s16.hi;
                        goto LABEL_55;
                      default:
                        goto LABEL_630;
                    }
                  }
                  goto LABEL_56;
                }
                if ( v26 <= 0x43E012 )
                {
                  if ( v26 != 4448274 )
                  {
                    if ( v26 == 4432914 )
                    {
                      v43 = gte_regs.data[11].s16.hi;
                      v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi
                          + gte_regs.ctrl[13].u32
                          + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                          + gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi;
                      v50 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
                      v39 = gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo
                          + gte_regs.ctrl[14].u32
                          + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                          + gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo;
                      v51 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
                      v49 = gte_regs.ctrl[15];
                      v52 = gte_regs.ctrl[12].s16.hi;
                      goto LABEL_55;
                    }
                    if ( v26 != 4440082 )
                    {
                      if ( v26 != 4441106 )
                        goto LABEL_630;
                      v43 = gte_regs.data[11].s16.hi;
                      v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi
                          + gte_regs.ctrl[21].u32
                          + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                          + gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi;
                      v50 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
                      v39 = gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo
                          + gte_regs.ctrl[22].u32
                          + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                          + gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo;
                      v51 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
                      v49 = gte_regs.ctrl[23];
                      v52 = gte_regs.ctrl[12].s16.hi;
                      goto LABEL_55;
                    }
                    v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi
                        + gte_regs.ctrl[21].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi;
                    v39 = gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo
                        + gte_regs.ctrl[22].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo;
                    v41 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi
                        + gte_regs.ctrl[23].u32
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[12].s16.hi;
                    v42.u32 = -32768;
                    goto LABEL_56;
                  }
                  v69 = gte_regs.data[10].s16.hi;
                  v70 = gte_regs.data[9].s16.hi;
                  v71 = gte_regs.data[11].s16.hi;
                  v26 = gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi;
                  goto LABEL_214;
                }
                if ( v26 == 4449298 )
                {
                  v53 = gte_regs.data[11].s16.hi;
                  v26 = gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi;
                  v63 = gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo;
                  v64 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
                  v65 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
                  v66 = gte_regs.ctrl[12].s16.hi;
                  goto LABEL_100;
                }
                if ( v26 != 4456466 )
                  goto LABEL_630;
                v72 = gte_regs.data[0].s16.lo;
                v73 = gte_regs.data[0].s16.hi;
                v74 = gte_regs.data[1].s16.hi;
                v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi
                    + gte_regs.ctrl[5].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi;
                v39 = gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.ctrl[6].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
                v75 = gte_regs.ctrl[7];
LABEL_282:
                v41 = v73 * gte_regs.ctrl[19].s16.hi
                    + v75.u32
                    + v72 * gte_regs.ctrl[19].s16.lo
                    + v74 * gte_regs.ctrl[20].s16.hi;
                v42.u32 = -32768;
                goto LABEL_56;
              }
              v76 = gte_regs.data[0].s16.lo;
              v77 = gte_regs.data[0].s16.hi;
              v43 = gte_regs.data[1].s16.hi;
              v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi
                  + gte_regs.ctrl[5].u32
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi;
              v39 = gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo
                  + gte_regs.ctrl[6].u32
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                  + gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
              v49 = gte_regs.ctrl[7];
LABEL_287:
              v50 = v77 * gte_regs.ctrl[19].s16.hi;
              v51 = v76 * gte_regs.ctrl[19].s16.lo;
              v52 = gte_regs.ctrl[20].s16.hi;
              goto LABEL_55;
            }
            if ( v26 <= 0x448012 )
            {
              if ( v26 == 4489234 )
              {
                v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi
                    + gte_regs.ctrl[5].u32
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi;
                v39 = gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi
                    + gte_regs.ctrl[6].u32
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo;
                v41 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi
                    + gte_regs.ctrl[7].u32
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[20].s16.hi;
                v42.u32 = -32768;
                goto LABEL_56;
              }
              if ( v26 <= 0x444412 )
              {
                if ( v26 != 4473874 )
                {
                  if ( v26 != 4464658 )
                  {
                    if ( v26 == 4465682 )
                    {
                      v76 = gte_regs.data[0].s16.lo;
                      v77 = gte_regs.data[0].s16.hi;
                      v43 = gte_regs.data[1].s16.hi;
                      v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi
                          + gte_regs.ctrl[13].u32
                          + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                          + gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi;
                      v39 = gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo
                          + gte_regs.ctrl[14].u32
                          + gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                          + gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
                      v49 = gte_regs.ctrl[15];
                      goto LABEL_287;
                    }
                    if ( v26 != 4472850 )
                      goto LABEL_630;
                    v72 = gte_regs.data[0].s16.lo;
                    v73 = gte_regs.data[0].s16.hi;
                    v74 = gte_regs.data[1].s16.hi;
                    v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi
                        + gte_regs.ctrl[21].u32
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                        + gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi;
                    v78 = gte_regs.ctrl[22].u32 + gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi;
                    v79 = gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
                    v80 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_281:
                    v39 = v79 + v78 + v80;
                    v75 = gte_regs.ctrl[23];
                    goto LABEL_282;
                  }
                  v81 = gte_regs.data[0].s16.lo;
                  v82 = gte_regs.data[0].s16.hi;
                  v83 = gte_regs.data[1].s16.hi;
                  v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi;
                  v84 = gte_regs.ctrl[14].u32 + gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi;
                  v85 = gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
                  v86 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_277:
                  v39 = v85 + v84 + v86;
                  v41 = v82 * gte_regs.ctrl[19].s16.hi
                      + gte_regs.ctrl[15].u32
                      + v81 * gte_regs.ctrl[19].s16.lo
                      + v83 * gte_regs.ctrl[20].s16.hi;
                  v42.u32 = -32768;
                  goto LABEL_56;
                }
                v76 = gte_regs.data[0].s16.lo;
                v77 = gte_regs.data[0].s16.hi;
                v43 = gte_regs.data[1].s16.hi;
                v26 = gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi
                    + gte_regs.ctrl[21].u32
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi;
                v87 = gte_regs.ctrl[22].u32 + gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi;
                v88 = gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
                v89 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_286:
                v39 = v88 + v87 + v89;
                v49 = gte_regs.ctrl[23];
                goto LABEL_287;
              }
              if ( v26 != 4481042 )
              {
                if ( v26 != 4482066 )
                  goto LABEL_630;
                v90 = gte_regs.data[0].s16.lo;
                v91 = gte_regs.data[0].s16.hi;
                v53 = gte_regs.data[1].s16.hi;
                v26 = gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi;
                v92 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                    + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
                v93 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
                goto LABEL_302;
              }
              v94 = gte_regs.data[0].s16.lo;
              v95 = gte_regs.data[0].s16.hi;
              v96 = gte_regs.data[1].s16.hi;
              v26 = gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi;
              v97 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
              v98 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_305:
              v39 = v98 + v97;
              v41 = v96 * gte_regs.ctrl[20].s16.hi + v94 * gte_regs.ctrl[19].s16.lo + v95 * gte_regs.ctrl[19].s16.hi;
              v42.u32 = -32768;
              goto LABEL_56;
            }
            if ( v26 <= 0x44C012 )
            {
              switch ( v26 )
              {
                case 0x44C012u:
                  v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[21].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi;
                  v39 = gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi
                      + gte_regs.ctrl[22].u32
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo;
                  v41 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi
                      + gte_regs.ctrl[23].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[20].s16.hi;
                  v42.u32 = -32768;
                  goto LABEL_56;
                case 0x448412u:
                  v76 = gte_regs.data[2].s16.lo;
                  v77 = gte_regs.data[2].s16.hi;
                  v43 = gte_regs.data[3].s16.hi;
                  v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[5].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi;
                  v39 = gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi
                      + gte_regs.ctrl[6].u32
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo;
                  v49 = gte_regs.ctrl[7];
                  break;
                case 0x44A012u:
                  v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi;
                  v39 = gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo;
                  v41 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi
                      + gte_regs.ctrl[15].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[20].s16.hi;
                  v42.u32 = -32768;
                  goto LABEL_56;
                case 0x44A412u:
                  v76 = gte_regs.data[2].s16.lo;
                  v77 = gte_regs.data[2].s16.hi;
                  v43 = gte_regs.data[3].s16.hi;
                  v26 = gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi;
                  v39 = gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo;
                  v49 = gte_regs.ctrl[15];
                  break;
                default:
                  goto LABEL_630;
              }
              goto LABEL_287;
            }
            if ( v26 != 4506642 )
            {
              if ( v26 != 4513810 )
                goto LABEL_630;
              v94 = gte_regs.data[2].s16.lo;
              v95 = gte_regs.data[2].s16.hi;
              v96 = gte_regs.data[3].s16.hi;
              v26 = gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi;
              goto LABEL_304;
            }
            v43 = gte_regs.data[3].s16.hi;
            v76 = gte_regs.data[2].s16.lo;
            v77 = gte_regs.data[2].s16.hi;
LABEL_285:
            v26 = v77 * gte_regs.ctrl[16].s16.hi
                + gte_regs.ctrl[21].u32
                + v76 * gte_regs.ctrl[16].s16.lo
                + v43 * gte_regs.ctrl[17].s16.hi;
            v87 = gte_regs.ctrl[22].u32 + v43 * gte_regs.ctrl[18].s16.lo;
            v88 = v76 * gte_regs.ctrl[18].s16.hi;
            v89 = v77 * gte_regs.ctrl[17].s16.lo;
            goto LABEL_286;
          }
          v90 = gte_regs.data[2].s16.lo;
          v91 = gte_regs.data[2].s16.hi;
          v53 = gte_regs.data[3].s16.hi;
          v26 = gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi
              + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
              + gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi;
LABEL_301:
          v92 = v53 * gte_regs.ctrl[18].s16.lo + v90 * gte_regs.ctrl[18].s16.hi;
          v93 = v91 * gte_regs.ctrl[17].s16.lo;
LABEL_302:
          v63 = v93 + v92;
          v64 = v91 * gte_regs.ctrl[19].s16.hi;
          v65 = v90 * gte_regs.ctrl[19].s16.lo;
          v66 = gte_regs.ctrl[20].s16.hi;
          goto LABEL_100;
        }
        if ( v26 <= 0x45C412 )
        {
          if ( v26 == 4572178 )
          {
            v43 = gte_regs.data[11].s16.hi;
            v76 = gte_regs.data[10].s16.hi;
            v77 = gte_regs.data[9].s16.hi;
            goto LABEL_285;
          }
          if ( v26 > 0x456012 )
          {
            if ( v26 > 0x45A012 )
            {
              if ( v26 == 4563986 )
              {
                v76 = gte_regs.data[10].s16.hi;
                v77 = gte_regs.data[9].s16.hi;
                v43 = gte_regs.data[11].s16.hi;
                v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi
                    + gte_regs.ctrl[13].u32
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi;
                v39 = gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
                    + gte_regs.ctrl[14].u32
                    + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
                v49 = gte_regs.ctrl[15];
                goto LABEL_287;
              }
              if ( v26 != 4571154 )
                goto LABEL_630;
              v72 = gte_regs.data[10].s16.hi;
              v73 = gte_regs.data[9].s16.hi;
              v74 = gte_regs.data[11].s16.hi;
              v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi
                  + gte_regs.ctrl[21].u32
                  + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi;
              v78 = gte_regs.ctrl[22].u32 + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo;
              v79 = gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi;
              v80 = gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
              goto LABEL_281;
            }
            if ( v26 == 4562962 )
            {
              v81 = gte_regs.data[10].s16.hi;
              v82 = gte_regs.data[9].s16.hi;
              v83 = gte_regs.data[11].s16.hi;
              v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi
                  + gte_regs.ctrl[13].u32
                  + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi;
              v84 = gte_regs.ctrl[14].u32 + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo;
              v85 = gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi;
              v86 = gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
              goto LABEL_277;
            }
            if ( v26 != 4547602 )
            {
              if ( v26 == 4554770 )
              {
                v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi
                    + gte_regs.ctrl[5].u32
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi;
                v39 = gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
                    + gte_regs.ctrl[6].u32
                    + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
                v41 = gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi
                    + gte_regs.ctrl[7].u32
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
                    + gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi;
                v42.u32 = -32768;
                goto LABEL_56;
              }
              if ( v26 != 4555794 )
                goto LABEL_630;
              v76 = gte_regs.data[10].s16.hi;
              v77 = gte_regs.data[9].s16.hi;
              v43 = gte_regs.data[11].s16.hi;
              v26 = gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi
                  + gte_regs.ctrl[5].u32
                  + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi;
              v39 = gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi
                  + gte_regs.ctrl[6].u32
                  + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                  + gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
              v49 = gte_regs.ctrl[7];
              goto LABEL_287;
            }
            v90 = gte_regs.data[4].s16.lo;
            v91 = gte_regs.data[4].s16.hi;
            v53 = gte_regs.data[5].s16.hi;
            v26 = gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi
                + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                + gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi;
            goto LABEL_301;
          }
          if ( v26 != 4546578 )
          {
            if ( v26 <= 0x452412 )
            {
              switch ( v26 )
              {
                case 0x452412u:
                  v76 = gte_regs.data[4].s16.lo;
                  v77 = gte_regs.data[4].s16.hi;
                  v43 = gte_regs.data[5].s16.hi;
                  v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi;
                  v39 = gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo;
                  v49 = gte_regs.ctrl[15];
                  break;
                case 0x450012u:
                  v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[5].u32
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi;
                  v39 = gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi
                      + gte_regs.ctrl[6].u32
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo;
                  v41 = gte_regs.data[4].s16.hi * gte_regs.ctrl[19].s16.hi
                      + gte_regs.ctrl[7].u32
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[19].s16.lo
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[20].s16.hi;
                  v42.u32 = -32768;
                  goto LABEL_56;
                case 0x450412u:
                  v76 = gte_regs.data[4].s16.lo;
                  v77 = gte_regs.data[4].s16.hi;
                  v43 = gte_regs.data[5].s16.hi;
                  v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[5].u32
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi;
                  v39 = gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi
                      + gte_regs.ctrl[6].u32
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo;
                  v49 = gte_regs.ctrl[7];
                  break;
                case 0x452012u:
                  v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi
                      + gte_regs.ctrl[13].u32
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi;
                  v39 = gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi
                      + gte_regs.ctrl[14].u32
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo;
                  v41 = gte_regs.data[4].s16.hi * gte_regs.ctrl[19].s16.hi
                      + gte_regs.ctrl[15].u32
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[19].s16.lo
                      + gte_regs.data[5].s16.hi * gte_regs.ctrl[20].s16.hi;
                  v42.u32 = -32768;
                  goto LABEL_56;
                default:
                  goto LABEL_630;
              }
              goto LABEL_287;
            }
            if ( v26 == 4538386 )
            {
              v26 = gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi
                  + gte_regs.ctrl[21].u32
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi;
              v39 = gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi
                  + gte_regs.ctrl[22].u32
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                  + gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo;
              v41 = gte_regs.data[4].s16.hi * gte_regs.ctrl[19].s16.hi
                  + gte_regs.ctrl[23].u32
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[19].s16.lo
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[20].s16.hi;
              v42.u32 = -32768;
              goto LABEL_56;
            }
            if ( v26 != 4539410 )
              goto LABEL_630;
            v43 = gte_regs.data[5].s16.hi;
            v76 = gte_regs.data[4].s16.lo;
            v77 = gte_regs.data[4].s16.hi;
            goto LABEL_285;
          }
          v94 = gte_regs.data[4].s16.lo;
          v95 = gte_regs.data[4].s16.hi;
          v96 = gte_regs.data[5].s16.hi;
          v26 = gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi
              + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
              + gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi;
LABEL_304:
          v97 = v96 * gte_regs.ctrl[18].s16.lo + v94 * gte_regs.ctrl[18].s16.hi;
          v98 = v95 * gte_regs.ctrl[17].s16.lo;
          goto LABEL_305;
        }
        if ( v26 <= 0x484012 )
        {
          if ( v26 == 4734994 )
          {
            v26 = gte_regs.ctrl[21].u32
                + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[1].s16.hi
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[0].s16.lo
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
            v39 = gte_regs.ctrl[22].u32
                + ((gte_regs.data[0].s16.lo * gte_regs.ctrl[2].s16.hi
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[1].s16.lo
                  + gte_regs.data[1].s16.hi * gte_regs.ctrl[2].s16.lo) >> 12);
            v41 = gte_regs.ctrl[23].u32
                + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[4].s16.hi
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[3].s16.lo
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[3].s16.hi) >> 12);
            v42.u32 = -32768;
            goto LABEL_56;
          }
          if ( v26 <= 0x480412 )
          {
            if ( v26 != 4719634 )
            {
              if ( v26 == 4579346 )
              {
                v94 = gte_regs.data[10].s16.hi;
                v95 = gte_regs.data[9].s16.hi;
                v96 = gte_regs.data[11].s16.hi;
                v26 = gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi;
                goto LABEL_304;
              }
              if ( v26 == 4580370 )
              {
                v90 = gte_regs.data[10].s16.hi;
                v91 = gte_regs.data[9].s16.hi;
                v53 = gte_regs.data[11].s16.hi;
                v26 = gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi;
                goto LABEL_301;
              }
              if ( v26 != 4718610 )
                goto LABEL_630;
              v99 = gte_regs.data[0].s16.lo;
              v100 = gte_regs.data[0].s16.hi;
              v101 = gte_regs.data[1].s16.hi;
              v102 = gte_regs.data[1].s16.hi * gte_regs.ctrl[1].s16.hi
                   + gte_regs.data[0].s16.lo * gte_regs.ctrl[0].s16.lo
                   + gte_regs.data[0].s16.hi * gte_regs.ctrl[0].s16.hi;
              goto LABEL_296;
            }
            v109 = gte_regs.data[1].s16.hi;
            v110 = gte_regs.data[0].s16.lo;
            v111 = gte_regs.data[0].s16.hi;
LABEL_307:
            v26 = gte_regs.ctrl[5].u32
                + ((v109 * gte_regs.ctrl[1].s16.hi + v110 * gte_regs.ctrl[0].s16.lo + v111 * gte_regs.ctrl[0].s16.hi) >> 12);
            v112 = v111 * gte_regs.ctrl[1].s16.lo + v109 * gte_regs.ctrl[2].s16.lo;
            v113 = v110 * gte_regs.ctrl[2].s16.hi;
LABEL_308:
            v63 = gte_regs.ctrl[6].u32 + ((v113 + v112) >> 12);
            v114 = v111 * gte_regs.ctrl[3].s16.hi;
            v115 = v110 * gte_regs.ctrl[3].s16.lo;
            v116 = gte_regs.ctrl[4].s16.hi;
            goto LABEL_309;
          }
          if ( v26 == 4726802 )
          {
            v26 = gte_regs.ctrl[13].u32
                + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[1].s16.hi
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[0].s16.lo
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
            v39 = gte_regs.ctrl[14].u32
                + ((gte_regs.data[0].s16.lo * gte_regs.ctrl[2].s16.hi
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[1].s16.lo
                  + gte_regs.data[1].s16.hi * gte_regs.ctrl[2].s16.lo) >> 12);
            v41 = gte_regs.ctrl[15].u32
                + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[4].s16.hi
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[3].s16.lo
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[3].s16.hi) >> 12);
            v42.u32 = -32768;
            goto LABEL_56;
          }
          if ( v26 != 4727826 )
            goto LABEL_630;
          v118 = gte_regs.data[1].s16.hi;
          lo = gte_regs.data[0].s16.lo;
          hi = gte_regs.data[0].s16.hi;
          goto LABEL_313;
        }
        if ( v26 > 0x488012 )
        {
          if ( v26 != 4752402 )
          {
            if ( v26 != 4759570 )
              goto LABEL_630;
            v101 = gte_regs.data[3].s16.hi;
            v26 = gte_regs.ctrl[13].u32
                + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                  + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                  + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
            v108 = gte_regs.ctrl[15];
            v39 = gte_regs.ctrl[14].u32
                + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo
                  + gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                  + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo) >> 12);
            v105 = gte_regs.data[2].s16.hi * gte_regs.ctrl[3].s16.hi;
            v106 = gte_regs.data[2].s16.lo * gte_regs.ctrl[3].s16.lo;
            v107 = gte_regs.ctrl[4].s16.hi;
            goto LABEL_299;
          }
          v110 = gte_regs.data[2].s16.lo;
          v111 = gte_regs.data[2].s16.hi;
          v109 = gte_regs.data[3].s16.hi;
          v26 = gte_regs.ctrl[5].u32
              + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
          v112 = gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
          v113 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
          goto LABEL_308;
        }
        if ( v26 == 4751378 )
        {
          v99 = gte_regs.data[2].s16.lo;
          v100 = gte_regs.data[2].s16.hi;
          v101 = gte_regs.data[3].s16.hi;
          v26 = gte_regs.ctrl[5].u32
              + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
          v103 = gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
          v104 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
          goto LABEL_297;
        }
        if ( v26 != 4736018 )
        {
          if ( v26 != 4743186 )
          {
            if ( v26 != 4744210 )
              goto LABEL_630;
            v127 = gte_regs.data[1].s16.hi;
            v128 = gte_regs.data[0].s16.lo;
            v129 = gte_regs.data[0].s16.hi;
LABEL_324:
            v130 = v129 * gte_regs.ctrl[1].s16.lo + v127 * gte_regs.ctrl[2].s16.lo;
            v26 = (v127 * gte_regs.ctrl[1].s16.hi + v128 * gte_regs.ctrl[0].s16.lo + v129 * gte_regs.ctrl[0].s16.hi) >> 12;
            v131 = v128 * gte_regs.ctrl[2].s16.hi;
LABEL_325:
            v63 = (v131 + v130) >> 12;
            v41 = (v127 * gte_regs.ctrl[4].s16.hi + v128 * gte_regs.ctrl[3].s16.lo + v129 * gte_regs.ctrl[3].s16.hi) >> 12;
            goto LABEL_102;
          }
          v132 = gte_regs.data[1].s16.hi;
          v133 = gte_regs.data[0].s16.lo;
          v134 = gte_regs.data[0].s16.hi;
          goto LABEL_327;
        }
        v141 = gte_regs.data[1].s16.hi;
        v142 = gte_regs.data[0].s16.lo;
        v143 = gte_regs.data[0].s16.hi;
LABEL_331:
        v26 = gte_regs.ctrl[21].u32
            + ((v141 * gte_regs.ctrl[1].s16.hi + v142 * gte_regs.ctrl[0].s16.lo + v143 * gte_regs.ctrl[0].s16.hi) >> 12);
        v144 = v143 * gte_regs.ctrl[1].s16.lo + v141 * gte_regs.ctrl[2].s16.lo;
        v145 = v142 * gte_regs.ctrl[2].s16.hi;
LABEL_332:
        v63 = gte_regs.ctrl[22].u32 + ((v145 + v144) >> 12);
        v146 = v143 * gte_regs.ctrl[3].s16.hi;
        v147 = v142 * gte_regs.ctrl[3].s16.lo;
        v148 = gte_regs.ctrl[4].s16.hi;
        goto LABEL_333;
      }
      if ( v26 <= 0x4C4012 )
      {
        if ( v26 != 4997138 )
        {
          if ( v26 <= 0x4A8012 )
          {
            if ( v26 == 4882450 )
            {
              v101 = gte_regs.data[3].s16.hi;
              v26 = gte_regs.ctrl[5].u32
                  + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              v39 = gte_regs.ctrl[6].u32
                  + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              v105 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
              v106 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
              v107 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_298;
            }
            if ( v26 <= 0x49A012 )
            {
              if ( v26 == 4825106 )
              {
                v101 = gte_regs.data[11].s16.hi;
                v26 = gte_regs.ctrl[13].u32
                    + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[1].s16.hi
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                v108 = gte_regs.ctrl[15];
                v39 = gte_regs.ctrl[14].u32
                    + ((gte_regs.data[10].s16.hi * gte_regs.ctrl[2].s16.hi
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[1].s16.lo
                      + gte_regs.data[11].s16.hi * gte_regs.ctrl[2].s16.lo) >> 12);
                v105 = gte_regs.data[9].s16.hi * gte_regs.ctrl[3].s16.hi;
                v106 = gte_regs.data[10].s16.hi * gte_regs.ctrl[3].s16.lo;
                v107 = gte_regs.ctrl[4].s16.hi;
                goto LABEL_299;
              }
              if ( v26 > 0x492412 )
              {
                if ( v26 > 0x496412 )
                {
                  if ( v26 == 4816914 )
                  {
                    v99 = gte_regs.data[10].s16.hi;
                    v100 = gte_regs.data[9].s16.hi;
                    v101 = gte_regs.data[11].s16.hi;
                    v102 = gte_regs.data[11].s16.hi * gte_regs.ctrl[1].s16.hi
                         + gte_regs.data[10].s16.hi * gte_regs.ctrl[0].s16.lo
                         + gte_regs.data[9].s16.hi * gte_regs.ctrl[0].s16.hi;
LABEL_296:
                    v26 = gte_regs.ctrl[5].u32 + (v102 >> 12);
                    v103 = v100 * gte_regs.ctrl[1].s16.lo + v101 * gte_regs.ctrl[2].s16.lo;
                    v104 = v99 * gte_regs.ctrl[2].s16.hi;
LABEL_297:
                    v39 = gte_regs.ctrl[6].u32 + ((v104 + v103) >> 12);
                    v105 = v100 * gte_regs.ctrl[3].s16.hi;
                    v106 = v99 * gte_regs.ctrl[3].s16.lo;
                    v107 = gte_regs.ctrl[4].s16.hi;
LABEL_298:
                    v108 = gte_regs.ctrl[7];
LABEL_299:
                    v41 = v108.u32 + ((v101 * v107 + v106 + v105) >> 12);
                    v42.u32 = -32768;
                    goto LABEL_56;
                  }
                  if ( v26 != 4817938 )
                    goto LABEL_630;
                  v109 = gte_regs.data[11].s16.hi;
                  v110 = gte_regs.data[10].s16.hi;
                  v111 = gte_regs.data[9].s16.hi;
                  goto LABEL_307;
                }
                if ( v26 == 4809746 )
                {
                  v128 = gte_regs.data[4].s16.lo;
                  v129 = gte_regs.data[4].s16.hi;
                  v127 = gte_regs.data[5].s16.hi;
                  v130 = gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                       + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
                  v26 = (gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                       + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                       + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12;
                  v131 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                  goto LABEL_325;
                }
                if ( v26 == 4800530 )
                {
                  v101 = gte_regs.data[5].s16.hi;
                  v26 = gte_regs.ctrl[21].u32
                      + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                        + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                  v108 = gte_regs.ctrl[23];
                  v39 = gte_regs.ctrl[22].u32
                      + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo
                        + gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                        + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo) >> 12);
                  v105 = gte_regs.data[4].s16.hi * gte_regs.ctrl[3].s16.hi;
                  v106 = gte_regs.data[4].s16.lo * gte_regs.ctrl[3].s16.lo;
                  v107 = gte_regs.ctrl[4].s16.hi;
                  goto LABEL_299;
                }
                if ( v26 != 4801554 )
                {
                  if ( v26 != 4808722 )
                    goto LABEL_630;
                  v133 = gte_regs.data[4].s16.lo;
                  v134 = gte_regs.data[4].s16.hi;
                  v132 = gte_regs.data[5].s16.hi;
                  v135 = gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                       + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
                  v26 = (gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                       + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                       + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12;
                  v136 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                  goto LABEL_328;
                }
                v142 = gte_regs.data[4].s16.lo;
                v143 = gte_regs.data[4].s16.hi;
                v141 = gte_regs.data[5].s16.hi;
                v26 = gte_regs.ctrl[21].u32
                    + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                v144 = gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                     + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
                v145 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
              }
              else
              {
                if ( v26 == 4793362 )
                {
                  lo = gte_regs.data[4].s16.lo;
                  hi = gte_regs.data[4].s16.hi;
                  v118 = gte_regs.data[5].s16.hi;
                  v26 = gte_regs.ctrl[13].u32
                      + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                        + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                  v121 = gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                       + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
                  v122 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                  goto LABEL_314;
                }
                if ( v26 > 0x48E412 )
                {
                  if ( v26 == 4784146 )
                  {
                    v99 = gte_regs.data[4].s16.lo;
                    v100 = gte_regs.data[4].s16.hi;
                    v101 = gte_regs.data[5].s16.hi;
                    v26 = gte_regs.ctrl[5].u32
                        + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                          + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                          + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                    v103 = gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                         + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
                    v104 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                    goto LABEL_297;
                  }
                  if ( v26 != 4785170 )
                  {
                    if ( v26 != 4792338 )
                      goto LABEL_630;
                    v101 = gte_regs.data[5].s16.hi;
                    v26 = gte_regs.ctrl[13].u32
                        + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                          + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                          + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                    v108 = gte_regs.ctrl[15];
                    v39 = gte_regs.ctrl[14].u32
                        + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo
                          + gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                          + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo) >> 12);
                    v105 = gte_regs.data[4].s16.hi * gte_regs.ctrl[3].s16.hi;
                    v106 = gte_regs.data[4].s16.lo * gte_regs.ctrl[3].s16.lo;
                    v107 = gte_regs.ctrl[4].s16.hi;
                    goto LABEL_299;
                  }
                  v110 = gte_regs.data[4].s16.lo;
                  v111 = gte_regs.data[4].s16.hi;
                  v109 = gte_regs.data[5].s16.hi;
                  v26 = gte_regs.ctrl[5].u32
                      + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[1].s16.hi
                        + gte_regs.data[4].s16.lo * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[4].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                  v112 = gte_regs.data[4].s16.lo * gte_regs.ctrl[2].s16.hi
                       + gte_regs.data[4].s16.hi * gte_regs.ctrl[1].s16.lo;
                  v113 = gte_regs.data[5].s16.hi * gte_regs.ctrl[2].s16.lo;
                  goto LABEL_308;
                }
                if ( v26 == 4776978 )
                {
                  v128 = gte_regs.data[2].s16.lo;
                  v129 = gte_regs.data[2].s16.hi;
                  v127 = gte_regs.data[3].s16.hi;
                  v130 = gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                       + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
                  v26 = (gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                       + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                       + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12;
                  v131 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
                  goto LABEL_325;
                }
                if ( v26 == 4767762 )
                {
                  v101 = gte_regs.data[3].s16.hi;
                  v26 = gte_regs.ctrl[21].u32
                      + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                        + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                  v108 = gte_regs.ctrl[23];
                  v39 = gte_regs.ctrl[22].u32
                      + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo
                        + gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                        + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo) >> 12);
                  v105 = gte_regs.data[2].s16.hi * gte_regs.ctrl[3].s16.hi;
                  v106 = gte_regs.data[2].s16.lo * gte_regs.ctrl[3].s16.lo;
                  v107 = gte_regs.ctrl[4].s16.hi;
                  goto LABEL_299;
                }
                if ( v26 != 4768786 )
                {
                  if ( v26 != 4775954 )
                    goto LABEL_630;
                  v133 = gte_regs.data[2].s16.lo;
                  v134 = gte_regs.data[2].s16.hi;
                  v132 = gte_regs.data[3].s16.hi;
                  v135 = gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                       + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
                  v26 = (gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                       + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                       + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12;
                  v136 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
                  goto LABEL_328;
                }
                v142 = gte_regs.data[2].s16.lo;
                v143 = gte_regs.data[2].s16.hi;
                v141 = gte_regs.data[3].s16.hi;
                v26 = gte_regs.ctrl[21].u32
                    + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[1].s16.hi
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[0].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                v144 = gte_regs.data[2].s16.lo * gte_regs.ctrl[2].s16.hi
                     + gte_regs.data[2].s16.hi * gte_regs.ctrl[1].s16.lo;
                v145 = gte_regs.data[3].s16.hi * gte_regs.ctrl[2].s16.lo;
              }
              goto LABEL_332;
            }
            if ( v26 <= 0x4A0412 )
            {
              if ( v26 == 4850706 )
              {
                v109 = gte_regs.data[1].s16.hi;
                v26 = gte_regs.ctrl[5].u32
                    + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                v63 = gte_regs.ctrl[6].u32
                    + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                v114 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
                v115 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
                v116 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_309;
              }
              if ( v26 > 0x49E012 )
              {
                if ( v26 != 4842514 )
                {
                  if ( v26 != 4849682 )
                    goto LABEL_630;
                  v101 = gte_regs.data[1].s16.hi;
                  v26 = gte_regs.ctrl[5].u32
                      + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                        + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                  v39 = gte_regs.ctrl[6].u32
                      + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                        + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                        + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                  v105 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
                  v106 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
                  v107 = gte_regs.ctrl[12].s16.hi;
                  goto LABEL_298;
                }
                v127 = gte_regs.data[11].s16.hi;
                v128 = gte_regs.data[10].s16.hi;
                v129 = gte_regs.data[9].s16.hi;
                goto LABEL_324;
              }
              switch ( v26 )
              {
                case 0x49E012u:
                  v132 = gte_regs.data[11].s16.hi;
                  v133 = gte_regs.data[10].s16.hi;
                  v134 = gte_regs.data[9].s16.hi;
LABEL_327:
                  v135 = v134 * gte_regs.ctrl[1].s16.lo + v132 * gte_regs.ctrl[2].s16.lo;
                  v26 = (v132 * gte_regs.ctrl[1].s16.hi + v133 * gte_regs.ctrl[0].s16.lo
                                                        + v134 * gte_regs.ctrl[0].s16.hi) >> 12;
                  v136 = v133 * gte_regs.ctrl[2].s16.hi;
LABEL_328:
                  v137 = v136 + v135;
                  v138 = v134 * gte_regs.ctrl[3].s16.hi;
                  v139 = v133 * gte_regs.ctrl[3].s16.lo;
                  v140 = gte_regs.ctrl[4].s16.hi;
LABEL_329:
                  v39 = v137 >> 12;
                  v41 = (v132 * v140 + v139 + v138) >> 12;
                  v42.u32 = -32768;
                  goto LABEL_56;
                case 0x49A412u:
                  v118 = gte_regs.data[11].s16.hi;
                  lo = gte_regs.data[10].s16.hi;
                  hi = gte_regs.data[9].s16.hi;
LABEL_313:
                  v26 = gte_regs.ctrl[13].u32
                      + ((v118 * gte_regs.ctrl[1].s16.hi + lo * gte_regs.ctrl[0].s16.lo + hi * gte_regs.ctrl[0].s16.hi) >> 12);
                  v121 = hi * gte_regs.ctrl[1].s16.lo + v118 * gte_regs.ctrl[2].s16.lo;
                  v122 = lo * gte_regs.ctrl[2].s16.hi;
LABEL_314:
                  v63 = gte_regs.ctrl[14].u32 + ((v122 + v121) >> 12);
                  v123 = hi * gte_regs.ctrl[3].s16.hi;
                  v124 = lo * gte_regs.ctrl[3].s16.lo;
                  v125 = gte_regs.ctrl[4].s16.hi;
                  goto LABEL_315;
                case 0x49C012u:
                  v101 = gte_regs.data[11].s16.hi;
                  v26 = gte_regs.ctrl[21].u32
                      + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[1].s16.hi
                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[0].s16.lo
                        + gte_regs.data[9].s16.hi * gte_regs.ctrl[0].s16.hi) >> 12);
                  v108 = gte_regs.ctrl[23];
                  v39 = gte_regs.ctrl[22].u32
                      + ((gte_regs.data[10].s16.hi * gte_regs.ctrl[2].s16.hi
                        + gte_regs.data[9].s16.hi * gte_regs.ctrl[1].s16.lo
                        + gte_regs.data[11].s16.hi * gte_regs.ctrl[2].s16.lo) >> 12);
                  v105 = gte_regs.data[9].s16.hi * gte_regs.ctrl[3].s16.hi;
                  v106 = gte_regs.data[10].s16.hi * gte_regs.ctrl[3].s16.lo;
                  v107 = gte_regs.ctrl[4].s16.hi;
                  goto LABEL_299;
              }
              if ( v26 != 4834322 )
                goto LABEL_630;
              v141 = gte_regs.data[11].s16.hi;
              v142 = gte_regs.data[10].s16.hi;
              v143 = gte_regs.data[9].s16.hi;
              goto LABEL_331;
            }
            if ( v26 <= 0x4A4412 )
            {
              if ( v26 == 4867090 )
              {
                v141 = gte_regs.data[1].s16.hi;
                v26 = gte_regs.ctrl[21].u32
                    + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                v63 = gte_regs.ctrl[22].u32
                    + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                v146 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
                v147 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
                v148 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_333;
              }
              if ( v26 == 4857874 )
              {
                v101 = gte_regs.data[1].s16.hi;
                v26 = gte_regs.ctrl[13].u32
                    + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                v108 = gte_regs.ctrl[15];
                v39 = gte_regs.ctrl[14].u32
                    + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                v105 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
                v106 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
                v107 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_299;
              }
              if ( v26 != 4858898 )
              {
                if ( v26 != 4866066 )
                  goto LABEL_630;
                v101 = gte_regs.data[1].s16.hi;
                v26 = gte_regs.ctrl[21].u32
                    + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                v108 = gte_regs.ctrl[23];
                v39 = gte_regs.ctrl[22].u32
                    + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                v105 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
                v106 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
                v107 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_299;
              }
              v118 = gte_regs.data[1].s16.hi;
              v26 = gte_regs.ctrl[13].u32
                  + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              v63 = gte_regs.ctrl[14].u32
                  + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              v123 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
              v124 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
              v125 = gte_regs.ctrl[12].s16.hi;
LABEL_315:
              v126 = v118 * v125 + v124 + v123;
              v68 = gte_regs.ctrl[15];
              v67 = v126 >> 12;
              goto LABEL_101;
            }
            if ( v26 == 4874258 )
            {
              v132 = gte_regs.data[1].s16.hi;
              v137 = gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                   + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                   + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo;
              v138 = gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi;
              v26 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                   + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                   + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
              v139 = gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo;
              v140 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_329;
            }
            if ( v26 != 4875282 )
              goto LABEL_630;
            v26 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[9].s16.hi
                 + gte_regs.data[0].s16.lo * gte_regs.ctrl[8].s16.lo
                 + gte_regs.data[0].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
            v63 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[10].s16.lo
                 + gte_regs.data[0].s16.lo * gte_regs.ctrl[10].s16.hi
                 + gte_regs.data[0].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
            v41 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[12].s16.hi
                 + gte_regs.data[0].s16.lo * gte_regs.ctrl[11].s16.lo
                 + gte_regs.data[0].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
LABEL_102:
            gte_regs.data[25].u32 = v26;
            gte_regs.data[26].u32 = v63;
            gte_regs.data[27].u32 = v41;
            if ( (v26 & 0x80000000) == 0 )
            {
              if ( (int)v26 <= 0x7FFF )
              {
                gte_regs.data[9].u32 = v26;
              }
              else
              {
                gte_regs.ctrl[31].u32 = -2130706432;
                gte_regs.data[9].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 = -2130706432;
              gte_regs.data[9].u32 = 0;
            }
            if ( v63 >= 0 )
            {
              if ( v63 <= 0x7FFF )
              {
                gte_regs.data[10].u32 = v63;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80800000;
                gte_regs.data[10].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x80800000;
              gte_regs.data[10].u32 = 0;
            }
            if ( v41 >= 0 )
              goto LABEL_541;
LABEL_573:
            LOBYTE(v26) = gte_regs.ctrl[31].u16.hi;
            gte_regs.data[11].u32 = 0;
            gte_regs.ctrl[31].u32 |= 0x400000u;
            return v26;
          }
          if ( v26 <= 0x4B6012 )
          {
            if ( v26 == 4939794 )
            {
              v132 = gte_regs.data[5].s16.hi;
              v137 = gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                   + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                   + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo;
              v138 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
              v26 = (gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                   + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                   + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
              v139 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
              v140 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_329;
            }
            if ( v26 <= 0x4AE412 )
            {
              if ( v26 == 4908050 )
              {
                v26 = (gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                     + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                     + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
                v63 = (gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                     + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                     + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
                v41 = (gte_regs.data[3].s16.hi * gte_regs.ctrl[12].s16.hi
                     + gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo
                     + gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
                goto LABEL_102;
              }
              if ( v26 <= 0x4AC012 )
              {
                switch ( v26 )
                {
                  case 0x4AC012u:
                    v101 = gte_regs.data[3].s16.hi;
                    v26 = gte_regs.ctrl[21].u32
                        + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                          + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                          + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                    v108 = gte_regs.ctrl[23];
                    v39 = gte_regs.ctrl[22].u32
                        + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                          + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                          + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                    v105 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
                    v106 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
                    v107 = gte_regs.ctrl[12].s16.hi;
                    goto LABEL_299;
                  case 0x4A8412u:
                    v109 = gte_regs.data[3].s16.hi;
                    v26 = gte_regs.ctrl[5].u32
                        + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                          + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                          + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                    v63 = gte_regs.ctrl[6].u32
                        + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                          + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                          + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                    v114 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
                    v115 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
                    v116 = gte_regs.ctrl[12].s16.hi;
                    goto LABEL_309;
                  case 0x4AA012u:
                    v101 = gte_regs.data[3].s16.hi;
                    v26 = gte_regs.ctrl[13].u32
                        + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                          + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                          + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                    v108 = gte_regs.ctrl[15];
                    v39 = gte_regs.ctrl[14].u32
                        + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                          + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                          + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                    v105 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
                    v106 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
                    v107 = gte_regs.ctrl[12].s16.hi;
                    goto LABEL_299;
                }
                if ( v26 != 4891666 )
                  goto LABEL_630;
                v118 = gte_regs.data[3].s16.hi;
                v26 = gte_regs.ctrl[13].u32
                    + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                v63 = gte_regs.ctrl[14].u32
                    + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                v123 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
                v124 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
                v125 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_315;
              }
              if ( v26 != 4899858 )
              {
                if ( v26 != 4907026 )
                  goto LABEL_630;
                v132 = gte_regs.data[3].s16.hi;
                v137 = gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                     + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                     + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo;
                v138 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
                v26 = (gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                     + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                     + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
                v139 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
                v140 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_329;
              }
              v141 = gte_regs.data[3].s16.hi;
              v26 = gte_regs.ctrl[21].u32
                  + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[2].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              v63 = gte_regs.ctrl[22].u32
                  + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[2].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              v146 = gte_regs.data[2].s16.hi * gte_regs.ctrl[11].s16.hi;
              v147 = gte_regs.data[2].s16.lo * gte_regs.ctrl[11].s16.lo;
              v148 = gte_regs.ctrl[12].s16.hi;
LABEL_333:
              v149 = v141 * v148 + v147 + v146;
              v68 = gte_regs.ctrl[23];
              v67 = v149 >> 12;
              goto LABEL_101;
            }
            if ( v26 > 0x4B2412 )
            {
              if ( v26 == 4931602 )
              {
                v101 = gte_regs.data[5].s16.hi;
                v26 = gte_regs.ctrl[21].u32
                    + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                v108 = gte_regs.ctrl[23];
                v39 = gte_regs.ctrl[22].u32
                    + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                v105 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
                v106 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
                v107 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_299;
              }
              if ( v26 != 4932626 )
                goto LABEL_630;
              v141 = gte_regs.data[5].s16.hi;
              v26 = gte_regs.ctrl[21].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              v63 = gte_regs.ctrl[22].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              v146 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
              v147 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
              v148 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_333;
            }
            if ( v26 == 4924434 )
            {
              v118 = gte_regs.data[5].s16.hi;
              v26 = gte_regs.ctrl[13].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              v63 = gte_regs.ctrl[14].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              v123 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
              v124 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
              v125 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_315;
            }
            if ( v26 == 4915218 )
            {
              v101 = gte_regs.data[5].s16.hi;
              v26 = gte_regs.ctrl[5].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              v39 = gte_regs.ctrl[6].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              v105 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
              v106 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
              v107 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_298;
            }
            if ( v26 != 4916242 )
            {
              if ( v26 != 4923410 )
                goto LABEL_630;
              v101 = gte_regs.data[5].s16.hi;
              v26 = gte_regs.ctrl[13].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              v108 = gte_regs.ctrl[15];
              v39 = gte_regs.ctrl[14].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              v105 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
              v106 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
              v107 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_299;
            }
            v109 = gte_regs.data[5].s16.hi;
            v26 = gte_regs.ctrl[5].u32
                + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                  + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
            v63 = gte_regs.ctrl[6].u32
                + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                  + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
            v114 = gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi;
            v115 = gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo;
            v116 = gte_regs.ctrl[12].s16.hi;
LABEL_309:
            v117 = v109 * v116 + v115 + v114;
            v68 = gte_regs.ctrl[7];
            v67 = v117 >> 12;
            goto LABEL_101;
          }
          if ( v26 <= 0x4BC412 )
          {
            if ( v26 == 4965394 )
            {
              v141 = gte_regs.data[11].s16.hi;
              v26 = gte_regs.ctrl[21].u32
                  + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              v63 = gte_regs.ctrl[22].u32
                  + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              v146 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
              v147 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
              v148 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_333;
            }
            if ( v26 > 0x4BA012 )
            {
              if ( v26 != 4957202 )
              {
                if ( v26 != 4964370 )
                  goto LABEL_630;
                v101 = gte_regs.data[11].s16.hi;
                v26 = gte_regs.ctrl[21].u32
                    + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                v108 = gte_regs.ctrl[23];
                v39 = gte_regs.ctrl[22].u32
                    + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                v105 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
                v106 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
                v107 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_299;
              }
              v118 = gte_regs.data[11].s16.hi;
              v26 = gte_regs.ctrl[13].u32
                  + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
              v63 = gte_regs.ctrl[14].u32
                  + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
              v123 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
              v124 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
              v125 = gte_regs.ctrl[12].s16.hi;
              goto LABEL_315;
            }
            switch ( v26 )
            {
              case 0x4BA012u:
                v101 = gte_regs.data[11].s16.hi;
                v26 = gte_regs.ctrl[13].u32
                    + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                v108 = gte_regs.ctrl[15];
                v39 = gte_regs.ctrl[14].u32
                    + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                v105 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
                v106 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
                v107 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_299;
              case 0x4B6412u:
                v26 = (gte_regs.data[5].s16.hi * gte_regs.ctrl[9].s16.hi
                     + gte_regs.data[4].s16.lo * gte_regs.ctrl[8].s16.lo
                     + gte_regs.data[4].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
                v63 = (gte_regs.data[5].s16.hi * gte_regs.ctrl[10].s16.lo
                     + gte_regs.data[4].s16.lo * gte_regs.ctrl[10].s16.hi
                     + gte_regs.data[4].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
                v41 = (gte_regs.data[5].s16.hi * gte_regs.ctrl[12].s16.hi
                     + gte_regs.data[4].s16.lo * gte_regs.ctrl[11].s16.lo
                     + gte_regs.data[4].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
                goto LABEL_102;
              case 0x4B8012u:
                v101 = gte_regs.data[11].s16.hi;
                v26 = gte_regs.ctrl[5].u32
                    + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
                v39 = gte_regs.ctrl[6].u32
                    + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                      + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                      + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
                v105 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
                v106 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
                v107 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_298;
            }
            if ( v26 != 4949010 )
              goto LABEL_630;
            v109 = gte_regs.data[11].s16.hi;
            v26 = gte_regs.ctrl[5].u32
                + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                  + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                  + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12);
            v63 = gte_regs.ctrl[6].u32
                + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                  + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                  + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12);
            v114 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
            v115 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
            v116 = gte_regs.ctrl[12].s16.hi;
            goto LABEL_309;
          }
          if ( v26 <= 0x4C0412 )
          {
            if ( v26 != 4981778 )
            {
              if ( v26 == 4972562 )
              {
                v132 = gte_regs.data[11].s16.hi;
                v137 = gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                     + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                     + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo;
                v138 = gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi;
                v26 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                     + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                     + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
                v139 = gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo;
                v140 = gte_regs.ctrl[12].s16.hi;
                goto LABEL_329;
              }
              if ( v26 == 4973586 )
              {
                v26 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[9].s16.hi
                     + gte_regs.data[10].s16.hi * gte_regs.ctrl[8].s16.lo
                     + gte_regs.data[9].s16.hi * gte_regs.ctrl[8].s16.hi) >> 12;
                v63 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[10].s16.lo
                     + gte_regs.data[10].s16.hi * gte_regs.ctrl[10].s16.hi
                     + gte_regs.data[9].s16.hi * gte_regs.ctrl[9].s16.lo) >> 12;
                v41 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[12].s16.hi
                     + gte_regs.data[10].s16.hi * gte_regs.ctrl[11].s16.lo
                     + gte_regs.data[9].s16.hi * gte_regs.ctrl[11].s16.hi) >> 12;
                goto LABEL_102;
              }
              if ( v26 != 4980754 )
                goto LABEL_630;
              v150 = gte_regs.data[0].s16.lo;
              v151 = gte_regs.data[0].s16.hi;
              v101 = gte_regs.data[1].s16.hi;
              v26 = gte_regs.ctrl[5].u32
                  + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              v152 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                   + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
              v153 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_528:
              v39 = gte_regs.ctrl[6].u32 + ((v153 + v152) >> 12);
              v105 = v151 * gte_regs.ctrl[19].s16.hi;
              v106 = v150 * gte_regs.ctrl[19].s16.lo;
              v107 = gte_regs.ctrl[20].s16.hi;
              goto LABEL_298;
            }
            v154 = gte_regs.data[0].s16.lo;
            v155 = gte_regs.data[0].s16.hi;
            v109 = gte_regs.data[1].s16.hi;
            v26 = gte_regs.ctrl[5].u32
                + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            v156 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                 + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
            v157 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
            goto LABEL_526;
          }
          if ( (int *)v26 != (int *)((char *)&spu_ram[93124] + 2) )
          {
            if ( (int *)v26 != (int *)((char *)&spu_ram[93380] + 2) )
              goto LABEL_630;
            v158 = gte_regs.data[0].s16.lo;
            v159 = gte_regs.data[0].s16.hi;
            v118 = gte_regs.data[1].s16.hi;
            v26 = gte_regs.ctrl[13].u32
                + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            v160 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                 + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
            v161 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
            goto LABEL_506;
          }
          v162 = gte_regs.data[0].s16.lo;
          v163 = gte_regs.data[0].s16.hi;
          v101 = gte_regs.data[1].s16.hi;
          v26 = gte_regs.ctrl[13].u32
              + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
          v164 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
          v165 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_530:
          v108 = gte_regs.ctrl[15];
          v39 = gte_regs.ctrl[14].u32 + ((v165 + v164) >> 12);
          v105 = v163 * gte_regs.ctrl[19].s16.hi;
          v106 = v162 * gte_regs.ctrl[19].s16.lo;
          v107 = gte_regs.ctrl[20].s16.hi;
          goto LABEL_299;
        }
        v166 = gte_regs.data[0].s16.lo;
        v167 = gte_regs.data[0].s16.hi;
        v101 = gte_regs.data[1].s16.hi;
        v26 = gte_regs.ctrl[21].u32
            + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
              + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
              + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
        v168 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
        v169 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_519:
        v108 = gte_regs.ctrl[23];
        v39 = gte_regs.ctrl[22].u32 + ((v169 + v168) >> 12);
        v105 = v167 * gte_regs.ctrl[19].s16.hi;
        v106 = v166 * gte_regs.ctrl[19].s16.lo;
        v107 = gte_regs.ctrl[20].s16.hi;
        goto LABEL_299;
      }
      if ( v26 <= 0x680029 )
      {
        if ( v26 == 6815785 )
        {
          LOBYTE(v26) = gte_dcpl();
          return v26;
        }
        if ( v26 <= 0x4D2412 )
        {
          if ( v26 == 5055506 )
          {
            v158 = gte_regs.data[4].s16.lo;
            v159 = gte_regs.data[4].s16.hi;
            v118 = gte_regs.data[5].s16.hi;
            v26 = gte_regs.ctrl[13].u32
                + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            v160 = gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                 + gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi;
            v161 = gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo;
LABEL_506:
            v63 = gte_regs.ctrl[14].u32 + ((v161 + v160) >> 12);
            v123 = v159 * gte_regs.ctrl[19].s16.hi;
            v124 = v158 * gte_regs.ctrl[19].s16.lo;
            v125 = gte_regs.ctrl[20].s16.hi;
            goto LABEL_315;
          }
          if ( v26 <= 0x4CC012 )
          {
            if ( v26 == 5029906 )
            {
              v101 = gte_regs.data[3].s16.hi;
              v26 = gte_regs.ctrl[21].u32
                  + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              v108 = gte_regs.ctrl[23];
              v39 = gte_regs.ctrl[22].u32
                  + ((gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
              v105 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi;
              v106 = gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo;
              v107 = gte_regs.ctrl[20].s16.hi;
              goto LABEL_299;
            }
            if ( v26 > 0x4C8012 )
            {
              if ( v26 == 5014546 )
              {
                v109 = gte_regs.data[3].s16.hi;
                v26 = gte_regs.ctrl[5].u32
                    + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
                v63 = gte_regs.ctrl[6].u32
                    + ((gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
                v114 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi;
                v115 = gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo;
                v116 = gte_regs.ctrl[20].s16.hi;
                goto LABEL_309;
              }
              if ( v26 == 5021714 )
              {
                v101 = gte_regs.data[3].s16.hi;
                v26 = gte_regs.ctrl[13].u32
                    + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                      + gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
                v108 = gte_regs.ctrl[15];
                v39 = gte_regs.ctrl[14].u32
                    + ((gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo
                      + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                      + gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
                v105 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi;
                v106 = gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo;
                v107 = gte_regs.ctrl[20].s16.hi;
                goto LABEL_299;
              }
              if ( v26 != 5022738 )
                goto LABEL_630;
              v118 = gte_regs.data[3].s16.hi;
              v26 = gte_regs.ctrl[13].u32
                  + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              v63 = gte_regs.ctrl[14].u32
                  + ((gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
              v123 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi;
              v124 = gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo;
              v125 = gte_regs.ctrl[20].s16.hi;
              goto LABEL_315;
            }
            if ( v26 == 5013522 )
            {
              v101 = gte_regs.data[3].s16.hi;
              v26 = gte_regs.ctrl[5].u32
                  + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              v39 = gte_regs.ctrl[6].u32
                  + ((gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
              v105 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi;
              v106 = gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo;
              v107 = gte_regs.ctrl[20].s16.hi;
              goto LABEL_298;
            }
            if ( v26 != 4998162 )
            {
              if ( v26 != 5005330 )
              {
                if ( v26 != 5006354 )
                  goto LABEL_630;
                v170 = gte_regs.data[0].s16.lo;
                v171 = gte_regs.data[0].s16.hi;
                v172 = gte_regs.data[1].s16.hi;
                v173 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                     + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
                v26 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                     + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                     + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12;
                v174 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
                goto LABEL_522;
              }
              v175 = gte_regs.data[0].s16.lo;
              v176 = gte_regs.data[0].s16.hi;
              v132 = gte_regs.data[1].s16.hi;
              v177 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                   + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
              v26 = (gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                   + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                   + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12;
              v178 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_516:
              v137 = v178 + v177;
              v138 = v176 * gte_regs.ctrl[19].s16.hi;
              v139 = v175 * gte_regs.ctrl[19].s16.lo;
              v140 = gte_regs.ctrl[20].s16.hi;
              goto LABEL_329;
            }
            v179 = gte_regs.data[0].s16.lo;
            v180 = gte_regs.data[0].s16.hi;
            v141 = gte_regs.data[1].s16.hi;
            v26 = gte_regs.ctrl[21].u32
                + ((gte_regs.data[1].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[0].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[0].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            v181 = gte_regs.data[0].s16.lo * gte_regs.ctrl[18].s16.hi
                 + gte_regs.data[0].s16.hi * gte_regs.ctrl[17].s16.lo;
            v182 = gte_regs.data[1].s16.hi * gte_regs.ctrl[18].s16.lo;
LABEL_537:
            v63 = gte_regs.ctrl[22].u32 + ((v182 + v181) >> 12);
            v146 = v180 * gte_regs.ctrl[19].s16.hi;
            v147 = v179 * gte_regs.ctrl[19].s16.lo;
            v148 = gte_regs.ctrl[20].s16.hi;
            goto LABEL_333;
          }
          if ( v26 > 0x4D0012 )
          {
            if ( v26 != 5047314 )
            {
              if ( v26 != 5054482 )
                goto LABEL_630;
              v101 = gte_regs.data[5].s16.hi;
              v26 = gte_regs.ctrl[13].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              v108 = gte_regs.ctrl[15];
              v39 = gte_regs.ctrl[14].u32
                  + ((gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
              v105 = gte_regs.data[4].s16.hi * gte_regs.ctrl[19].s16.hi;
              v106 = gte_regs.data[4].s16.lo * gte_regs.ctrl[19].s16.lo;
              v107 = gte_regs.ctrl[20].s16.hi;
              goto LABEL_299;
            }
            v109 = gte_regs.data[5].s16.hi;
            v26 = gte_regs.ctrl[5].u32
                + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            v63 = gte_regs.ctrl[6].u32
                + ((gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
            v114 = gte_regs.data[4].s16.hi * gte_regs.ctrl[19].s16.hi;
            v115 = gte_regs.data[4].s16.lo * gte_regs.ctrl[19].s16.lo;
            v116 = gte_regs.ctrl[20].s16.hi;
            goto LABEL_309;
          }
          if ( v26 == 5046290 )
          {
            v101 = gte_regs.data[5].s16.hi;
            v26 = gte_regs.ctrl[5].u32
                + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            v39 = gte_regs.ctrl[6].u32
                + ((gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo
                  + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                  + gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
            v105 = gte_regs.data[4].s16.hi * gte_regs.ctrl[19].s16.hi;
            v106 = gte_regs.data[4].s16.lo * gte_regs.ctrl[19].s16.lo;
            v107 = gte_regs.ctrl[20].s16.hi;
            goto LABEL_298;
          }
          if ( v26 == 5030930 )
          {
            v141 = gte_regs.data[3].s16.hi;
            v26 = gte_regs.ctrl[21].u32
                + ((gte_regs.data[3].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[2].s16.lo * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[2].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            v63 = gte_regs.ctrl[22].u32
                + ((gte_regs.data[2].s16.hi * gte_regs.ctrl[17].s16.lo
                  + gte_regs.data[3].s16.hi * gte_regs.ctrl[18].s16.lo
                  + gte_regs.data[2].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
            v146 = gte_regs.data[2].s16.hi * gte_regs.ctrl[19].s16.hi;
            v147 = gte_regs.data[2].s16.lo * gte_regs.ctrl[19].s16.lo;
            v148 = gte_regs.ctrl[20].s16.hi;
            goto LABEL_333;
          }
          if ( v26 != 5038098 )
          {
            if ( v26 != 5039122 )
              goto LABEL_630;
            v172 = gte_regs.data[3].s16.hi;
            v170 = gte_regs.data[2].s16.lo;
            v171 = gte_regs.data[2].s16.hi;
            goto LABEL_521;
          }
          v132 = gte_regs.data[3].s16.hi;
          v175 = gte_regs.data[2].s16.lo;
          v176 = gte_regs.data[2].s16.hi;
          goto LABEL_515;
        }
        if ( v26 <= 0x4DA012 )
        {
          if ( v26 == 5087250 )
          {
            v162 = gte_regs.data[10].s16.hi;
            v163 = gte_regs.data[9].s16.hi;
            v101 = gte_regs.data[11].s16.hi;
            v26 = gte_regs.ctrl[13].u32
                + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            v164 = gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                 + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi;
            v165 = gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
            goto LABEL_530;
          }
          if ( v26 > 0x4D6412 )
          {
            if ( v26 == 5079058 )
            {
              v150 = gte_regs.data[10].s16.hi;
              v151 = gte_regs.data[9].s16.hi;
              v101 = gte_regs.data[11].s16.hi;
              v26 = gte_regs.ctrl[5].u32
                  + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              v152 = gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                   + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi;
              v153 = gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
              goto LABEL_528;
            }
            if ( v26 != 5080082 )
              goto LABEL_630;
            v154 = gte_regs.data[10].s16.hi;
            v155 = gte_regs.data[9].s16.hi;
            v109 = gte_regs.data[11].s16.hi;
            v26 = gte_regs.ctrl[5].u32
                + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                  + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                  + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
            v156 = gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                 + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi;
            v157 = gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
LABEL_526:
            v63 = gte_regs.ctrl[6].u32 + ((v157 + v156) >> 12);
            v114 = v155 * gte_regs.ctrl[19].s16.hi;
            v115 = v154 * gte_regs.ctrl[19].s16.lo;
            v116 = gte_regs.ctrl[20].s16.hi;
            goto LABEL_309;
          }
          switch ( v26 )
          {
            case 0x4D6412u:
              v172 = gte_regs.data[5].s16.hi;
              v170 = gte_regs.data[4].s16.lo;
              v171 = gte_regs.data[4].s16.hi;
LABEL_521:
              v173 = v172 * gte_regs.ctrl[18].s16.lo + v170 * gte_regs.ctrl[18].s16.hi;
              v26 = (v172 * gte_regs.ctrl[17].s16.hi + v170 * gte_regs.ctrl[16].s16.lo + v171 * gte_regs.ctrl[16].s16.hi) >> 12;
              v174 = v171 * gte_regs.ctrl[17].s16.lo;
LABEL_522:
              v63 = (v174 + v173) >> 12;
              v41 = (v172 * gte_regs.ctrl[20].s16.hi + v170 * gte_regs.ctrl[19].s16.lo + v171 * gte_regs.ctrl[19].s16.hi) >> 12;
              goto LABEL_102;
            case 0x4D4012u:
              v166 = gte_regs.data[4].s16.lo;
              v167 = gte_regs.data[4].s16.hi;
              v101 = gte_regs.data[5].s16.hi;
              v26 = gte_regs.ctrl[21].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              v168 = gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                   + gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi;
              v169 = gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo;
              goto LABEL_519;
            case 0x4D4412u:
              v141 = gte_regs.data[5].s16.hi;
              v26 = gte_regs.ctrl[21].u32
                  + ((gte_regs.data[5].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[4].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              v63 = gte_regs.ctrl[22].u32
                  + ((gte_regs.data[4].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.data[5].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[4].s16.lo * gte_regs.ctrl[18].s16.hi) >> 12);
              v146 = gte_regs.data[4].s16.hi * gte_regs.ctrl[19].s16.hi;
              v147 = gte_regs.data[4].s16.lo * gte_regs.ctrl[19].s16.lo;
              v148 = gte_regs.ctrl[20].s16.hi;
              goto LABEL_333;
          }
          if ( v26 != 5070866 )
            goto LABEL_630;
          v132 = gte_regs.data[5].s16.hi;
          v175 = gte_regs.data[4].s16.lo;
          v176 = gte_regs.data[4].s16.hi;
LABEL_515:
          v177 = v132 * gte_regs.ctrl[18].s16.lo + v175 * gte_regs.ctrl[18].s16.hi;
          v26 = (v132 * gte_regs.ctrl[17].s16.hi + v175 * gte_regs.ctrl[16].s16.lo + v176 * gte_regs.ctrl[16].s16.hi) >> 12;
          v178 = v176 * gte_regs.ctrl[17].s16.lo;
          goto LABEL_516;
        }
        if ( v26 <= 0x4DE012 )
        {
          switch ( v26 )
          {
            case 0x4DE012u:
              v26 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                   + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                   + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12;
              v183 = (gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi) >> 12;
              v41 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
                   + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
                   + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12;
              v42.u32 = -32768;
              gte_regs.data[25].u32 = v26;
              gte_regs.data[26].u32 = v183;
              gte_regs.data[27].u32 = v41;
              if ( (int)v26 >= -32768 )
              {
                if ( (int)v26 <= 0x7FFF )
                {
                  gte_regs.data[9].u32 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                                        + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                                        + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12;
                }
                else
                {
                  gte_regs.ctrl[31].u32 = -2130706432;
                  gte_regs.data[9].u32 = 0x7FFF;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 = -2130706432;
                gte_regs.data[9].u32 = -32768;
              }
              if ( v183 >= -32768 )
              {
                if ( v183 <= 0x7FFF )
                {
                  gte_regs.data[10].u32 = v183;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x80800000;
                  gte_regs.data[10].u32 = 0x7FFF;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80800000;
                gte_regs.data[10].u32 = -32768;
              }
              if ( v41 >= -32768 )
                goto LABEL_541;
              goto LABEL_558;
            case 0x4DA412u:
              v26 = gte_regs.ctrl[13].u32
                  + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              v63 = gte_regs.ctrl[14].u32
                  + ((gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi) >> 12);
              v68 = gte_regs.ctrl[15];
              v67 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
                   + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
                   + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12;
              goto LABEL_101;
            case 0x4DC012u:
              v26 = gte_regs.ctrl[21].u32
                  + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
              v39 = gte_regs.ctrl[22].u32
                  + ((gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo
                    + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi) >> 12);
              v41 = gte_regs.ctrl[23].u32
                  + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12);
              v42.u32 = -32768;
              goto LABEL_56;
          }
          if ( v26 != 5096466 )
            goto LABEL_630;
          v179 = gte_regs.data[10].s16.hi;
          v180 = gte_regs.data[9].s16.hi;
          v141 = gte_regs.data[11].s16.hi;
          v26 = gte_regs.ctrl[21].u32
              + ((gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12);
          v181 = gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
               + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi;
          v182 = gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo;
          goto LABEL_537;
        }
        if ( v26 == 5104658 )
        {
          v26 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
               + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
               + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12;
          v184 = (gte_regs.data[9].s16.hi * gte_regs.ctrl[17].s16.lo
                + gte_regs.data[11].s16.hi * gte_regs.ctrl[18].s16.lo
                + gte_regs.data[10].s16.hi * gte_regs.ctrl[18].s16.hi) >> 12;
          v41 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[20].s16.hi
               + gte_regs.data[10].s16.hi * gte_regs.ctrl[19].s16.lo
               + gte_regs.data[9].s16.hi * gte_regs.ctrl[19].s16.hi) >> 12;
          gte_regs.data[25].u32 = v26;
          gte_regs.data[26].u32 = v184;
          gte_regs.data[27].u32 = v41;
          if ( (v26 & 0x80000000) == 0 )
          {
            if ( (int)v26 <= 0x7FFF )
            {
              gte_regs.data[9].u32 = (gte_regs.data[11].s16.hi * gte_regs.ctrl[17].s16.hi
                                    + gte_regs.data[10].s16.hi * gte_regs.ctrl[16].s16.lo
                                    + gte_regs.data[9].s16.hi * gte_regs.ctrl[16].s16.hi) >> 12;
            }
            else
            {
              gte_regs.ctrl[31].u32 = -2130706432;
              gte_regs.data[9].u32 = 0x7FFF;
            }
          }
          else
          {
            gte_regs.ctrl[31].u32 = -2130706432;
            gte_regs.data[9].u32 = 0;
          }
          if ( v184 >= 0 )
          {
            if ( v184 <= 0x7FFF )
            {
              gte_regs.data[10].u32 = v184;
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x80800000;
              gte_regs.data[10].u32 = 0x7FFF;
            }
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x80800000;
            gte_regs.data[10].u32 = 0;
          }
          if ( v41 >= 0 )
            goto LABEL_541;
          goto LABEL_573;
        }
        if ( v26 != 5767213 )
          goto LABEL_630;
LABEL_694:
        gte_regs.data[24].u32 = gte_regs.ctrl[29].s16.hi
                              * (gte_regs.data[17].u16.hi + gte_regs.data[18].u16.hi + gte_regs.data[19].u16.hi);
        v26 = gte_regs.data[24].s32 >> 12;
        if ( gte_regs.data[24].s32 >> 12 >= 0 )
        {
          if ( (int)v26 <= 0xFFFF )
          {
            gte_regs.data[7].u16.hi = gte_regs.data[24].s32 >> 12;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x80040000;
            gte_regs.data[7].u16.hi = -1;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x80040000;
          gte_regs.data[7].u16.hi = 0;
        }
        return v26;
      }
      if ( v26 > 0x118043F )
      {
        if ( v26 <= 0x178000C )
        {
          if ( v26 == 24641548 )
          {
            LOBYTE(v26) = gte_op_shifted().u32;
            return v26;
          }
          if ( v26 <= 0x158002D )
          {
            if ( v26 != 22544429 )
            {
              if ( v26 == 19399700 )
              {
                LOBYTE(v26) = gte_cdp();
                return v26;
              }
              if ( v26 == 20448284 )
              {
                LOBYTE(v26) = gte_cc();
                return v26;
              }
              if ( v26 != 20971526 )
                goto LABEL_630;
              goto LABEL_612;
            }
            goto LABEL_694;
          }
          if ( v26 != 23593006 )
          {
            if ( v26 == 24117260 )
            {
              LOBYTE(v26) = gte_op();
              return v26;
            }
            goto LABEL_630;
          }
          goto LABEL_699;
        }
        if ( v26 > 0x198003D )
        {
          if ( v26 != 0x1A0003E )
          {
            if ( v26 == 0x1A8003E )
            {
              v22.u32 = ((gte_regs.data[8].s16.hi * gte_regs.data[10].s16.hi) >> 12) + gte_regs.data[26].u32;
              v23.u32 = ((gte_regs.data[8].s16.hi * gte_regs.data[11].s16.hi) >> 12) + gte_regs.data[27].u32;
              gte_regs.data[25].u32 += (gte_regs.data[8].s16.hi * gte_regs.data[9].s16.hi) >> 12;
              gte_regs.data[26] = v22;
              gte_regs.data[27] = v23;
              if ( gte_regs.data[25].s32 >= -32768 )
              {
                if ( gte_regs.data[25].s32 <= 0x7FFF )
                {
                  gte_regs.data[9].u32 = gte_regs.data[25].u32;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x81000000;
                  gte_regs.data[9].u32 = 0x7FFF;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x81000000;
                gte_regs.data[9].u32 = -32768;
              }
              if ( v22.s32 >= -32768 )
              {
                if ( v22.s32 <= 0x7FFF )
                {
                  gte_regs.data[10] = v22;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x80800000;
                  gte_regs.data[10].u32 = 0x7FFF;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80800000;
                gte_regs.data[10].u32 = -32768;
              }
              if ( v23.s32 >= -32768 )
              {
                if ( v23.s32 <= 0x7FFF )
                {
                  gte_regs.data[11] = v23;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x400000u;
                  gte_regs.data[11].u32 = 0x7FFF;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x400000u;
                gte_regs.data[11].u32 = -32768;
              }
              gte_regs.data[20].u32 = gte_regs.data[21].u32;
              v26 = gte_regs.data[25].s32 >> 4;
              gte_regs.data[21].u32 = gte_regs.data[22].u32;
              v24 = v22.s32 >> 4;
              v25 = v23.s32 >> 4;
              dword_8A8004 = gte_regs.data[25].s32 >> 4;
              dword_8A8008 = v24;
              dword_8A800C = v25;
              if ( gte_regs.data[25].s32 >> 4 >= 0 )
              {
                if ( (int)v26 <= 255 )
                {
                  LOBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[25].s32 >> 4;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x200000u;
                  LOBYTE(gte_regs.data[22].u16.hi) = -1;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x200000u;
                LOBYTE(gte_regs.data[22].u16.hi) = 0;
              }
              if ( v24 >= 0 )
              {
                if ( v24 <= 255 )
                {
                  HIBYTE(gte_regs.data[22].u16.hi) = v24;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x100000u;
                  HIBYTE(gte_regs.data[22].u16.hi) = -1;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x100000u;
                HIBYTE(gte_regs.data[22].u16.hi) = 0;
              }
              if ( v25 >= 0 )
              {
                if ( v25 <= 255 )
                {
                  LOBYTE(gte_regs.data[22].s16.lo) = v25;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x80000u;
                  LOBYTE(v26) = HIBYTE(gte_regs.data[6].u32);
                  LOBYTE(gte_regs.data[22].s16.lo) = -1;
                }
                HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
              }
              else
              {
                LOBYTE(v26) = gte_regs.ctrl[31].u16.hi;
                gte_regs.ctrl[31].u32 |= 0x80000u;
                LOBYTE(gte_regs.data[22].s16.lo) = 0;
                HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
              }
              return v26;
            }
            goto LABEL_630;
          }
        }
        else
        {
          switch ( v26 )
          {
            case 0x198003Du:
              goto LABEL_735;
            case 0x1780010u:
              goto LABEL_626;
            case 0x190003Du:
              goto LABEL_704;
          }
          if ( v26 != 26214462 )
            goto LABEL_630;
        }
        v18.u32 = gte_regs.data[8].s16.hi * gte_regs.data[10].s16.hi + gte_regs.data[26].u32;
        v19.u32 = gte_regs.data[8].s16.hi * gte_regs.data[11].s16.hi + gte_regs.data[27].u32;
        gte_regs.data[25].u32 += gte_regs.data[8].s16.hi * gte_regs.data[9].s16.hi;
        gte_regs.data[26] = v18;
        gte_regs.data[27] = v19;
        if ( gte_regs.data[25].s32 >= -32768 )
        {
          if ( gte_regs.data[25].s32 <= 0x7FFF )
          {
            gte_regs.data[9].u32 = gte_regs.data[25].u32;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x81000000;
            gte_regs.data[9].u32 = 0x7FFF;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x81000000;
          gte_regs.data[9].u32 = -32768;
        }
        if ( v18.s32 >= -32768 )
        {
          if ( v18.s32 <= 0x7FFF )
          {
            gte_regs.data[10] = v18;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x80800000;
            gte_regs.data[10].u32 = 0x7FFF;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x80800000;
          gte_regs.data[10].u32 = -32768;
        }
        if ( v19.s32 >= -32768 )
        {
          if ( v19.s32 <= 0x7FFF )
          {
            gte_regs.data[11] = v19;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x400000u;
            gte_regs.data[11].u32 = 0x7FFF;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x400000u;
          gte_regs.data[11].u32 = -32768;
        }
        gte_regs.data[20].u32 = gte_regs.data[21].u32;
        v26 = gte_regs.data[25].s32 >> 4;
        gte_regs.data[21].u32 = gte_regs.data[22].u32;
        v20 = v18.s32 >> 4;
        v21 = v19.s32 >> 4;
        dword_8A8004 = gte_regs.data[25].s32 >> 4;
        dword_8A8008 = v20;
        dword_8A800C = v21;
        if ( gte_regs.data[25].s32 >> 4 >= 0 )
        {
          if ( (int)v26 <= 255 )
          {
            LOBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[25].s32 >> 4;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x200000u;
            LOBYTE(gte_regs.data[22].u16.hi) = -1;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x200000u;
          LOBYTE(gte_regs.data[22].u16.hi) = 0;
        }
        if ( v20 >= 0 )
        {
          if ( v20 <= 255 )
          {
            HIBYTE(gte_regs.data[22].u16.hi) = v20;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x100000u;
            HIBYTE(gte_regs.data[22].u16.hi) = -1;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x100000u;
          HIBYTE(gte_regs.data[22].u16.hi) = 0;
        }
        if ( v21 >= 0 )
        {
          if ( v21 <= 255 )
          {
            LOBYTE(gte_regs.data[22].s16.lo) = v21;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x80000u;
            LOBYTE(v26) = HIBYTE(gte_regs.data[6].u32);
            LOBYTE(gte_regs.data[22].s16.lo) = -1;
          }
          HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
        }
        else
        {
          LOBYTE(v26) = gte_regs.ctrl[31].u16.hi;
          gte_regs.ctrl[31].u32 |= 0x80000u;
          LOBYTE(gte_regs.data[22].s16.lo) = 0;
          HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
        }
        return v26;
      }
      if ( v26 == 18351167 )
      {
        LOBYTE(v26) = gte_ncct();
        return v26;
      }
      if ( v26 <= 0xA80428 )
      {
        if ( v26 == 11011112 )
        {
          v26 = (gte_regs.data[9].s16.hi * gte_regs.data[9].s16.hi) >> 12;
          v6 = (gte_regs.data[10].s16.hi * gte_regs.data[10].s16.hi) >> 12;
          v7 = (gte_regs.data[11].s16.hi * gte_regs.data[11].s16.hi) >> 12;
          gte_regs.data[25].u32 = v26;
          gte_regs.data[26].u32 = v6;
          gte_regs.data[27].u32 = v7;
          if ( (v26 & 0x80000000) == 0 )
          {
            if ( (int)v26 <= 0x7FFF )
            {
              gte_regs.data[9].u32 = (gte_regs.data[9].s16.hi * gte_regs.data[9].s16.hi) >> 12;
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x81000000;
              gte_regs.data[9].u32 = 0x7FFF;
            }
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x81000000;
            gte_regs.data[9].u32 = 0;
          }
          if ( v6 >= 0 )
          {
            if ( v6 <= 0x7FFF )
            {
              gte_regs.data[10].u32 = (gte_regs.data[10].s16.hi * gte_regs.data[10].s16.hi) >> 12;
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x80800000;
              gte_regs.data[10].u32 = 0x7FFF;
            }
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x80800000;
            gte_regs.data[10].u32 = 0;
          }
          if ( v7 >= 0 )
          {
            if ( v7 <= 0x7FFF )
            {
              gte_regs.data[11].u32 = (gte_regs.data[11].s16.hi * gte_regs.data[11].s16.hi) >> 12;
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x400000u;
              gte_regs.data[11].u32 = 0x7FFF;
            }
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x400000u;
            gte_regs.data[11].u32 = 0;
          }
          return v26;
        }
        if ( v26 <= 0x980011 )
        {
          if ( v26 == 9961489 )
          {
            gte_regs.data[25].u32 = gte_regs.data[9].s16.hi
                                  + ((gte_regs.data[8].s16.hi
                                    * gte_clamp(-2130706432, gte_regs.ctrl[21].u32 - gte_regs.data[9].s16.hi)) >> 12);
            gte_regs.data[26].u32 = gte_regs.data[10].s16.hi
                                  + ((gte_regs.data[8].s16.hi
                                    * gte_clamp(-2139095040, gte_regs.ctrl[22].u32 - gte_regs.data[10].s16.hi)) >> 12);
            v0 = gte_clamp(0x400000, gte_regs.ctrl[23].u32 - gte_regs.data[11].s16.hi);
            v2.u32 = gte_regs.data[11].s16.hi + ((gte_regs.data[8].s16.hi * v0) >> 12);
            gte_regs.data[27] = v2;
            if ( gte_regs.data[25].s32 >= -32768 )
            {
              if ( gte_regs.data[25].s32 <= 0x7FFF )
              {
                gte_regs.data[9].u32 = gte_regs.data[25].u32;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= v1;
                gte_regs.data[9].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= v1;
              gte_regs.data[9].u32 = -32768;
            }
            if ( gte_regs.data[26].s32 >= -32768 )
            {
              if ( gte_regs.data[26].s32 <= 0x7FFF )
              {
                gte_regs.data[10].u32 = gte_regs.data[26].u32;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80800000;
                gte_regs.data[10].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x80800000;
              gte_regs.data[10].u32 = -32768;
            }
            if ( v2.s32 >= -32768 )
            {
              if ( v2.s32 <= 0x7FFF )
              {
                gte_regs.data[11] = v2;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x400000u;
                gte_regs.data[11].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x400000u;
              gte_regs.data[11].u32 = -32768;
            }
            gte_regs.data[20].u32 = gte_regs.data[21].u32;
            v3 = gte_regs.data[26].s32 >> 4;
            v26 = v2.s32 >> 4;
            gte_regs.data[21].u32 = gte_regs.data[22].u32;
            dword_8A8004 = gte_regs.data[25].s32 >> 4;
            dword_8A8008 = gte_regs.data[26].s32 >> 4;
            dword_8A800C = v26;
            if ( gte_regs.data[25].s32 >> 4 >= 0 )
            {
              if ( gte_regs.data[25].s32 >> 4 <= 255 )
              {
                LOBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[25].s32 >> 4;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x200000u;
                LOBYTE(gte_regs.data[22].u16.hi) = -1;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x200000u;
              LOBYTE(gte_regs.data[22].u16.hi) = 0;
            }
            if ( v3 >= 0 )
            {
              if ( v3 <= 255 )
              {
                HIBYTE(gte_regs.data[22].u16.hi) = gte_regs.data[26].s32 >> 4;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x100000u;
                HIBYTE(gte_regs.data[22].u16.hi) = -1;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x100000u;
              HIBYTE(gte_regs.data[22].u16.hi) = 0;
            }
            if ( (v26 & 0x80000000) == 0 )
            {
              if ( (int)v26 <= 255 )
              {
                LOBYTE(gte_regs.data[22].s16.lo) = v26;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80000u;
                LOBYTE(v26) = HIBYTE(gte_regs.data[6].u32);
                LOBYTE(gte_regs.data[22].s16.lo) = -1;
              }
              HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
            }
            else
            {
              LOBYTE(v26) = gte_regs.ctrl[31].u16.hi;
              gte_regs.ctrl[31].u32 |= 0x80000u;
              LOBYTE(gte_regs.data[22].s16.lo) = 0;
              HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
            }
            return v26;
          }
          if ( (int *)v26 != (int *)((char *)&ram[205947] + 2) )
          {
            if ( (int *)v26 != &ram[468084] )
            {
              if ( v26 != 9437245 )
                goto LABEL_630;
LABEL_704:
              v8.u32 = gte_regs.data[8].s16.hi * gte_regs.data[9].s16.hi;
              v9.u32 = gte_regs.data[8].s16.hi * gte_regs.data[10].s16.hi;
              v10.u32 = gte_regs.data[8].s16.hi * gte_regs.data[11].s16.hi;
              gte_regs.data[25] = v8;
              gte_regs.data[26] = v9;
              gte_regs.data[27] = v10;
              if ( v8.s32 >= -32768 )
              {
                if ( v8.s32 <= 0x7FFF )
                {
                  gte_regs.data[9].u32 = gte_regs.data[8].s16.hi * gte_regs.data[9].s16.hi;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x81000000;
                  gte_regs.data[9].u32 = 0x7FFF;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x81000000;
                gte_regs.data[9].u32 = -32768;
              }
              if ( v9.s32 >= -32768 )
              {
                if ( v9.s32 <= 0x7FFF )
                {
                  gte_regs.data[10].u32 = gte_regs.data[8].s16.hi * gte_regs.data[10].s16.hi;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x80800000;
                  gte_regs.data[10].u32 = 0x7FFF;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80800000;
                gte_regs.data[10].u32 = -32768;
              }
              if ( v10.s32 >= -32768 )
              {
                if ( v10.s32 <= 0x7FFF )
                {
                  gte_regs.data[11].u32 = gte_regs.data[8].s16.hi * gte_regs.data[11].s16.hi;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x400000u;
                  gte_regs.data[11].u32 = 0x7FFF;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x400000u;
                gte_regs.data[11].u32 = -32768;
              }
              gte_regs.data[20].u32 = gte_regs.data[21].u32;
              v26 = v8.s32 >> 4;
              gte_regs.data[21].u32 = gte_regs.data[22].u32;
              v11 = v9.s32 >> 4;
              v12 = v10.s32 >> 4;
              dword_8A8004 = v26;
              dword_8A8008 = v11;
              dword_8A800C = v12;
              if ( (v26 & 0x80000000) == 0 )
              {
                if ( (int)v26 <= 255 )
                {
                  LOBYTE(gte_regs.data[22].u16.hi) = v26;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x200000u;
                  LOBYTE(gte_regs.data[22].u16.hi) = -1;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x200000u;
                LOBYTE(gte_regs.data[22].u16.hi) = 0;
              }
              if ( v11 >= 0 )
              {
                if ( v11 <= 255 )
                {
                  HIBYTE(gte_regs.data[22].u16.hi) = v11;
                }
                else
                {
                  gte_regs.ctrl[31].u32 |= 0x100000u;
                  HIBYTE(gte_regs.data[22].u16.hi) = -1;
                }
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x100000u;
                HIBYTE(gte_regs.data[22].u16.hi) = 0;
              }
              if ( v12 >= 0 )
              {
                if ( v12 <= 255 )
                {
                  LOBYTE(gte_regs.data[22].s16.lo) = v12;
                }
                else
                {
                  LOBYTE(v26) = gte_regs.ctrl[31].u16.hi;
                  gte_regs.ctrl[31].u32 |= 0x80000u;
                  LOBYTE(gte_regs.data[22].s16.lo) = -1;
                }
                HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80000u;
                LOBYTE(gte_regs.data[22].s16.lo) = 0;
                HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
                LOBYTE(v26) = HIBYTE(gte_regs.data[6].u32);
              }
              return v26;
            }
LABEL_626:
            LOBYTE(v26) = gte_dpcs();
            return v26;
          }
LABEL_699:
          gte_regs.data[24].u32 = gte_regs.ctrl[30].s16.hi
                                * (gte_regs.data[16].u16.hi
                                 + gte_regs.data[17].u16.hi
                                 + gte_regs.data[18].u16.hi
                                 + gte_regs.data[19].u16.hi);
          v26 = gte_regs.data[24].s32 >> 12;
          if ( gte_regs.data[24].s32 >> 12 >= 0 )
          {
            if ( (int)v26 <= 0xFFFF )
            {
              gte_regs.data[7].u16.hi = gte_regs.data[24].s32 >> 12;
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x80040000;
              gte_regs.data[7].u16.hi = -1;
            }
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x80040000;
            gte_regs.data[7].u16.hi = 0;
          }
          return v26;
        }
        if ( v26 != 9961533 )
        {
          if ( v26 == 10486824 )
          {
            v26 = gte_regs.data[9].s16.hi * gte_regs.data[9].s16.hi;
            v4.u32 = gte_regs.data[10].s16.hi * gte_regs.data[10].s16.hi;
            v5.u32 = gte_regs.data[11].s16.hi * gte_regs.data[11].s16.hi;
            gte_regs.data[25].u32 = v26;
            gte_regs.data[26] = v4;
            gte_regs.data[27] = v5;
            if ( (v26 & 0x80000000) == 0 )
            {
              if ( (int)v26 <= 0x7FFF )
              {
                gte_regs.data[9].u32 = gte_regs.data[9].s16.hi * gte_regs.data[9].s16.hi;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x81000000;
                gte_regs.data[9].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x81000000;
              gte_regs.data[9].u32 = 0;
            }
            if ( v4.s32 >= 0 )
            {
              if ( v4.s32 <= 0x7FFF )
              {
                gte_regs.data[10].u32 = gte_regs.data[10].s16.hi * gte_regs.data[10].s16.hi;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x80800000;
                gte_regs.data[10].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x80800000;
              gte_regs.data[10].u32 = 0;
            }
            if ( v5.s32 >= 0 )
            {
              if ( v5.s32 <= 0x7FFF )
              {
                gte_regs.data[11].u32 = gte_regs.data[11].s16.hi * gte_regs.data[11].s16.hi;
              }
              else
              {
                gte_regs.ctrl[31].u32 |= 0x400000u;
                gte_regs.data[11].u32 = 0x7FFF;
              }
            }
            else
            {
              gte_regs.ctrl[31].u32 |= 0x400000u;
              gte_regs.data[11].u32 = 0;
            }
            return v26;
          }
          goto LABEL_630;
        }
LABEL_735:
        v13 = (gte_regs.data[8].s16.hi * gte_regs.data[9].s16.hi) >> 12;
        v14 = (gte_regs.data[8].s16.hi * gte_regs.data[10].s16.hi) >> 12;
        v15 = (gte_regs.data[8].s16.hi * gte_regs.data[11].s16.hi) >> 12;
        gte_regs.data[25].u32 = v13;
        gte_regs.data[26].u32 = v14;
        gte_regs.data[27].u32 = v15;
        if ( v13 >= -32768 )
        {
          if ( v13 <= 0x7FFF )
          {
            gte_regs.data[9].u32 = (gte_regs.data[8].s16.hi * gte_regs.data[9].s16.hi) >> 12;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x81000000;
            gte_regs.data[9].u32 = 0x7FFF;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x81000000;
          gte_regs.data[9].u32 = -32768;
        }
        if ( v14 >= -32768 )
        {
          if ( v14 <= 0x7FFF )
          {
            gte_regs.data[10].u32 = (gte_regs.data[8].s16.hi * gte_regs.data[10].s16.hi) >> 12;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x80800000;
            gte_regs.data[10].u32 = 0x7FFF;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x80800000;
          gte_regs.data[10].u32 = -32768;
        }
        if ( v15 >= -32768 )
        {
          if ( v15 <= 0x7FFF )
          {
            gte_regs.data[11].u32 = (gte_regs.data[8].s16.hi * gte_regs.data[11].s16.hi) >> 12;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x400000u;
            gte_regs.data[11].u32 = 0x7FFF;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x400000u;
          gte_regs.data[11].u32 = -32768;
        }
        gte_regs.data[20].u32 = gte_regs.data[21].u32;
        v26 = v13 >> 4;
        gte_regs.data[21].u32 = gte_regs.data[22].u32;
        v16 = v14 >> 4;
        v17 = v15 >> 4;
        dword_8A8004 = v26;
        dword_8A8008 = v16;
        dword_8A800C = v17;
        if ( (v26 & 0x80000000) == 0 )
        {
          if ( (int)v26 <= 255 )
          {
            LOBYTE(gte_regs.data[22].u16.hi) = v26;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x200000u;
            LOBYTE(gte_regs.data[22].u16.hi) = -1;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x200000u;
          LOBYTE(gte_regs.data[22].u16.hi) = 0;
        }
        if ( v16 >= 0 )
        {
          if ( v16 <= 255 )
          {
            HIBYTE(gte_regs.data[22].u16.hi) = v16;
          }
          else
          {
            gte_regs.ctrl[31].u32 |= 0x100000u;
            HIBYTE(gte_regs.data[22].u16.hi) = -1;
          }
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x100000u;
          HIBYTE(gte_regs.data[22].u16.hi) = 0;
        }
        if ( v17 >= 0 )
        {
          if ( v17 <= 255 )
          {
            LOBYTE(gte_regs.data[22].s16.lo) = v17;
          }
          else
          {
            LOBYTE(v26) = gte_regs.ctrl[31].u16.hi;
            gte_regs.ctrl[31].u32 |= 0x80000u;
            LOBYTE(gte_regs.data[22].s16.lo) = -1;
          }
          HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
        }
        else
        {
          gte_regs.ctrl[31].u32 |= 0x80000u;
          LOBYTE(gte_regs.data[22].s16.lo) = 0;
          HIBYTE(gte_regs.data[22].u32) = HIBYTE(gte_regs.data[6].u32);
          LOBYTE(v26) = HIBYTE(gte_regs.data[6].u32);
        }
        return v26;
      }
      if ( v26 <= 0xF8002A )
      {
        switch ( v26 )
        {
          case 0xF8002Au:
            LOBYTE(v26) = gte_dpct().u32;
            return v26;
          case 0xC8041Eu:
            LOBYTE(v26) = gte_ncs();
            return v26;
          case 0xD80420u:
            LOBYTE(v26) = gte_nct();
            return v26;
          case 0xE80413u:
            LOBYTE(v26) = gte_ncds();
            return v26;
        }
        goto LABEL_630;
      }
      if ( v26 == 0xF80416 )
      {
        LOBYTE(v26) = gte_ncdt();
        return v26;
      }
      if ( v26 == 0x108041B )
        goto LABEL_602;
LABEL_630:
      if ( gtrace )
        LOBYTE(v26) = dbg_print("CODE [%07x]\n", v26);
      return v26;
  }
}

int __cdecl gte_read_data_register(unsigned __int8 a1)
{
  unsigned __int8 v2; // al
  int v3; // edx

  if ( a1 == 31 )
    return (unsigned __int8)gte_count_leading_bits(gte_regs.data[30].s32);
  if ( a1 != 29 )
    return gte_regs.data[a1].s32;
  gte_convert_to_5bit(gte_regs.data[11].u16.hi);
  gte_convert_to_5bit(gte_regs.data[10].u16.hi);
  v2 = gte_convert_to_5bit(gte_regs.data[9].u16.hi);
  return v3 | v2;
}

GTE_REG __cdecl gte_write_data_register(unsigned __int8 a1, GTE_REG a2)
{
  GTE_REG result; // eax

  result = a2;
  gte_regs.data[a1] = a2;
  if ( a1 >= 0x10u && a1 <= 0x13u )
    gte_regs.data[a1].u32 = a2.u16.hi;
  switch ( a1 )
  {
    case 0xEu:
      gte_regs.data[15] = a2;
      break;
    case 0xFu:
      gte_regs.data[12].u32 = gte_regs.data[13].u32;
      gte_regs.data[13].u32 = gte_regs.data[14].u32;
      gte_regs.data[14] = a2;
      break;
    case 0x1Cu:
      result.u32 = ((a2.u32 >> 10) & 0x1F) << 7;
      gte_regs.data[9].u32 = (a2.u16.hi & 0x1F) << 7;
      gte_regs.data[10].u32 = ((a2.u32 >> 5) & 0x1F) << 7;
      gte_regs.data[11] = result;
      break;
  }
  return result;
}

int gte_clear_regs()
{
  memset(&gte_regs, 0, sizeof(gte_regs));
  return 0;
}

int __cdecl gte_freeze(const char *a1, int a2)
{
  char Buffer[3]; // [esp+4h] [ebp-10h] BYREF
  int v4; // [esp+7h] [ebp-Dh]

  sprintf(Buffer, "%s", a1);
  v4 = 256;
  gzwrite(a2, (unsigned __int8 *)Buffer, 7u);
  return gzwrite(a2, (unsigned __int8 *)&gte_regs, 0x100u);
}

int __cdecl gte_unfreeze(int a1, _DWORD *a2)
{
  char v3[16]; // [esp+4h] [ebp-10h] BYREF

  gzread(a2, v3, 7);
  return gzread(a2, (char *)&gte_regs, 256);
}

