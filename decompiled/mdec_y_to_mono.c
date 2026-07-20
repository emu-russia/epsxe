#include "pch.h"
void __cdecl mdec_y_to_mono(unsigned int *a1, __m64 *a2, int a3)
{
  unsigned int *v3; // esi
  unsigned int *v4; // eax
  unsigned int *v5; // ebx
  unsigned int *v6; // ecx
  __m64 *v7; // edi
  __m64 *v8; // edx
  __m64 v9; // mm0
  __m64 v10; // mm0
  __m64 v11; // mm4
  __m64 v12; // mm1
  __m64 v13; // mm1
  __m64 v14; // mm5
  __m64 v15; // mm6
  __m64 v16; // mm0
  __m64 v17; // mm1
  __m64 v18; // mm7
  __m64 v19; // mm1
  __m64 v20; // mm4
  __m64 v21; // mm2
  __m64 v22; // mm6
  __m64 v23; // mm5
  __m64 v24; // mm3
  __m64 v25; // mm5
  __m64 v26; // mm0
  __m64 v27; // mm1
  __m64 v28; // mm0
  __m64 v29; // mm5
  __m64 v30; // mm4
  __m64 v31; // mm3
  __m64 v32; // mm3
  __m64 v33; // mm7
  __m64 v34; // mm0
  __m64 v35; // mm6
  __m64 v36; // mm2
  __m64 v37; // mm4
  __m64 v38; // mm3
  __m64 v39; // mm7
  __m64 v40; // mm2
  __m64 v41; // mm7
  __m64 v42; // mm3
  __m64 v43; // mm0
  __m64 v44; // mm3
  __m64 v45; // mm1
  __m64 v46; // mm5
  __m64 v47; // mm5
  int v48; // [esp+Ch] [ebp-1Ch]
  int v49; // [esp+10h] [ebp-18h]
  int v50; // [esp+14h] [ebp-14h]

  v3 = a1 + 32;
  v4 = a1 + 34;
  v5 = a1;
  v6 = a1 + 16;
  v7 = a2;
  v8 = a2 + 6;
  do
  {
    v48 = 2;
    do
    {
      v49 = 2;
      do
      {
        v50 = 4;
        do
        {
          v9 = _mm_cvtsi32_si64(*v5);
          v10 = _m_punpcklbw(v9, v9);
          v11 = _m_punpcklwd(v10, v10);
          v12 = _mm_cvtsi32_si64(*v6);
          v13 = _m_punpcklbw(v12, v12);
          v14 = _m_punpcklwd(v13, v13);
          v15 = _m_paddb(_mm_cvtsi32_si64(*v3), (__m64)qword_455C70);
          v16 = _m_paddsw(
                  _m_pmulhw(_m_psrawi(_m_punpckldq(v11, v11), 6u), (__m64)qword_455C50),
                  _m_pmulhw(_m_psrawi(_m_punpckldq(v14, v14), 6u), (__m64)qword_455C58));
          v17 = _m_punpcklbw(v15, v15);
          v18 = _m_punpcklwd(v17, v15);
          v19 = _m_psrlqi(v17, 0x10u);
          v20 = _m_paddsw(
                  _m_pmulhw(_m_psrawi(_m_punpckhdq(v11, v11), 6u), (__m64)qword_455C60),
                  _m_pmulhw(_m_psrawi(_m_punpckhdq(v14, v14), 6u), (__m64)qword_455C68));
          v21 = _m_por(
                  _m_psrlqi(_m_pand(v16, (__m64)qword_455C78), 0x10u),
                  _m_psllqi(_m_pand(v20, (__m64)qword_455C78), 0x10u));
          v22 = _m_paddb(_mm_cvtsi32_si64(*v4), (__m64)qword_455C70);
          v7->m64_u64 = (unsigned __int64)_m_packuswb(
                                            _m_paddsw(_m_punpcklbw(v18, (__m64)(unsigned int)dword_4FD858), v16),
                                            _m_paddsw(_m_punpcklbw(v19, (__m64)(unsigned int)dword_4FD858), v21));
          v23 = _m_punpcklbw(v22, v22);
          v24 = _m_punpcklbw(_m_punpcklwd(v23, v22), (__m64)(unsigned int)dword_4FD858);
          v25 = _m_psrlqi(v23, 0x10u);
          v8->m64_u64 = (unsigned __int64)_m_packuswb(
                                            _m_paddsw(v24, v16),
                                            _m_paddsw(
                                              _m_punpcklbw(_m_punpckldq(v25, v25), (__m64)(unsigned int)dword_4FD858),
                                              v21));
          v26 = _m_psrlqi(_mm_cvtsi32_si64(*v5), 0x10u);
          v27 = _m_paddsw(
                  _m_punpcklbw(
                    _m_punpcklwd(_m_psrlqi(v19, 0x18u), _m_psrlqi(v19, 0x20u)),
                    (__m64)(unsigned int)dword_4FD858),
                  v20);
          v28 = _m_punpcklbw(v26, v26);
          v29 = _m_paddsw(
                  _m_punpcklbw(
                    _m_punpcklwd(_m_psrlqi(v25, 0x18u), _m_psrlqi(v25, 0x20u)),
                    (__m64)(unsigned int)dword_4FD858),
                  v20);
          v30 = _m_punpcklwd(v28, v28);
          v31 = _m_psrlqi(_mm_cvtsi32_si64(*v6), 0x10u);
          v32 = _m_punpcklbw(v31, v31);
          v33 = _m_punpcklwd(v32, v32);
          v34 = _m_paddsw(
                  _m_pmulhw(_m_psrawi(_m_punpckldq(v30, v30), 6u), (__m64)qword_455C50),
                  _m_pmulhw(_m_psrawi(_m_punpckldq(v33, v33), 6u), (__m64)qword_455C58));
          v35 = _m_paddb(_mm_cvtsi32_si64(v3[1]), (__m64)qword_455C70);
          v36 = _m_psrlqi(_m_pand(v34, (__m64)qword_455C78), 0x10u);
          v37 = _m_paddsw(
                  _m_pmulhw(_m_psrawi(_m_punpckhdq(v30, v30), 6u), (__m64)qword_455C60),
                  _m_pmulhw(_m_psrawi(_m_punpckhdq(v33, v33), 6u), (__m64)qword_455C68));
          v38 = _m_paddb(_mm_cvtsi32_si64(v4[1]), (__m64)qword_455C70);
          v39 = _m_psllqi(_m_pand(v37, (__m64)qword_455C78), 0x10u);
          v7[1].m64_u64 = (unsigned __int64)_m_packuswb(
                                              v27,
                                              _m_paddsw(
                                                _m_punpcklbw(
                                                  _m_punpcklwd(_m_punpcklbw(v35, v35), v35),
                                                  (__m64)(unsigned int)dword_4FD858),
                                                v34));
          v40 = _m_por(v36, v39);
          v41 = v38;
          v42 = _m_paddsw(_m_punpcklbw(_m_punpcklwd(_m_punpcklbw(v38, v38), v38), 0), v34);
          v43 = _m_psrlqi(v41, 8u);
          v8[1].m64_u64 = (unsigned __int64)_m_packuswb(v29, v42);
          v44 = _m_psrlqi(v35, 8u);
          v45 = _m_psrlqi(v44, 8u);
          v3 += 4;
          v4 += 4;
          v46 = _m_psrlqi(v43, 8u);
          v7 += 12;
          v8 += 12;
          v5 += 2;
          v47 = _m_paddsw(
                  _m_punpcklbw(
                    _m_punpcklwd(v46, _m_psrlqi(_m_punpcklbw(v46, v46), 0x10u)),
                    (__m64)(unsigned int)dword_4FD858),
                  v37);
          v7[-10].m64_u64 = (unsigned __int64)_m_packuswb(
                                                _m_paddsw(_m_punpcklbw(_m_punpcklbw(v44, v44), 0), v40),
                                                _m_paddsw(
                                                  _m_punpcklbw(
                                                    _m_punpcklwd(v45, _m_psrlqi(_m_punpcklbw(v45, v45), 0x10u)),
                                                    (__m64)(unsigned int)dword_4FD858),
                                                  v37));
          v6 += 2;
          v8[-10].m64_u64 = (unsigned __int64)_m_packuswb(_m_paddsw(_m_punpcklbw(_m_punpcklbw(v43, v43), 0), v40), v47);
          --v50;
        }
        while ( v50 );
        v5 -= 7;
        v6 -= 7;
        v7 -= 45;
        v8 -= 45;
        --v49;
      }
      while ( v49 );
      v5 += 6;
      v6 += 6;
      v7 += 42;
      v8 += 42;
      --v48;
    }
    while ( v48 );
    v5 += 80;
    v6 += 80;
    v3 += 32;
    v4 += 32;
    --a3;
  }
  while ( a3 );
  mdec_sse_m_empty();
}
