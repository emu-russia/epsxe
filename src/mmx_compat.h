/* MMX intrinsics compatibility layer for x64 builds.
 *
 * MSVC's mmintrin.h only declares the _m_* MMX intrinsics for 32-bit
 * (x86) targets.  The decompiled mdec.c / gte.c rely on them, so on x64
 * we reimplement the ones actually used, operating directly on the
 * __m64 union type (which IS defined for x64).
 */
#pragma once
#ifndef MMX_COMPAT_H_INCLUDED
#define MMX_COMPAT_H_INCLUDED

#include <mmintrin.h>

/* _m_from_int64 is not provided by MSVC even on x86 (only _m_from_int is);
 * it is used by the decompiled IDCT code on all platforms. */
static __inline __m64 _m_from_int64(__int64 _I)
{
    __m64 r;
    r.m64_u64 = (unsigned __int64)_I;
    return r;
}

#if defined(_M_X64) && !defined(_M_IX86)

static __inline void _m_empty(void) { }

static __inline __m64 _m_from_int(int _I)
{
    __m64 r;
    r.m64_u32[0] = (unsigned int)_I;
    r.m64_u32[1] = 0;
    return r;
}

static __inline int _m_to_int(__m64 _M)
{
    return _M.m64_i32[0];
}

static __inline __m64 _m_paddb(__m64 _MM1, __m64 _MM2)
{
    __m64 r;
    int i;
    for (i = 0; i < 8; i++) r.m64_u8[i] = (unsigned char)(_MM1.m64_u8[i] + _MM2.m64_u8[i]);
    return r;
}

static __inline __m64 _m_paddw(__m64 _MM1, __m64 _MM2)
{
    __m64 r;
    int i;
    for (i = 0; i < 4; i++) r.m64_u16[i] = (unsigned short)(_MM1.m64_u16[i] + _MM2.m64_u16[i]);
    return r;
}

static __inline __m64 _m_paddd(__m64 _MM1, __m64 _MM2)
{
    __m64 r;
    int i;
    for (i = 0; i < 2; i++) r.m64_u32[i] = _MM1.m64_u32[i] + _MM2.m64_u32[i];
    return r;
}

static __inline __m64 _m_paddsw(__m64 _MM1, __m64 _MM2)
{
    __m64 r;
    int i;
    for (i = 0; i < 4; i++)
    {
        long s = (long)_MM1.m64_i16[i] + (long)_MM2.m64_i16[i];
        if (s > 32767) s = 32767;
        if (s < -32768) s = -32768;
        r.m64_i16[i] = (short)s;
    }
    return r;
}

static __inline __m64 _m_psubw(__m64 _MM1, __m64 _MM2)
{
    __m64 r;
    int i;
    for (i = 0; i < 4; i++) r.m64_u16[i] = (unsigned short)(_MM1.m64_u16[i] - _MM2.m64_u16[i]);
    return r;
}

static __inline __m64 _m_pmulhw(__m64 _MM1, __m64 _MM2)
{
    __m64 r;
    int i;
    for (i = 0; i < 4; i++)
        r.m64_u16[i] = (unsigned short)(((long)_MM1.m64_i16[i] * (long)_MM2.m64_i16[i]) >> 16);
    return r;
}

static __inline __m64 _m_psllwi(__m64 _MM1, int count)
{
    __m64 r;
    int i;
    count &= 15;
    for (i = 0; i < 4; i++) r.m64_u16[i] = (unsigned short)(_MM1.m64_u16[i] << count);
    return r;
}

static __inline __m64 _m_psllqi(__m64 _MM1, int count)
{
    __m64 r;
    count &= 63;
    r.m64_u64 = _MM1.m64_u64 << count;
    return r;
}

static __inline __m64 _m_psrlqi(__m64 _MM1, int count)
{
    __m64 r;
    count &= 63;
    r.m64_u64 = _MM1.m64_u64 >> count;
    return r;
}

static __inline __m64 _m_psradi(__m64 _MM1, int count)
{
    __m64 r;
    int i;
    count &= 15;
    for (i = 0; i < 4; i++) r.m64_i16[i] = (short)(_MM1.m64_i16[i] >> count);
    return r;
}

static __inline __m64 _m_psrawi(__m64 _MM1, int count)
{
    return _m_psradi(_MM1, count);
}

static __inline __m64 _m_pand(__m64 _MM1, __m64 _MM2)
{
    __m64 r;
    r.m64_u64 = _MM1.m64_u64 & _MM2.m64_u64;
    return r;
}

static __inline __m64 _m_pmaddwd(__m64 _MM1, __m64 _MM2)
{
    __m64 r;
    long t0 = (long)_MM1.m64_i16[0] * (long)_MM2.m64_i16[0]
            + (long)_MM1.m64_i16[1] * (long)_MM2.m64_i16[1];
    long t1 = (long)_MM1.m64_i16[2] * (long)_MM2.m64_i16[2]
            + (long)_MM1.m64_i16[3] * (long)_MM2.m64_i16[3];
    r.m64_i32[0] = (int)t0;
    r.m64_i32[1] = (int)t1;
    return r;
}

static __inline __m64 _m_packsswb(__m64 _MM1, __m64 _MM2)
{
    __m64 r;
    int i;
    for (i = 0; i < 4; i++)
    {
        long v = (long)_MM1.m64_i16[i];
        if (v > 127) v = 127;
        if (v < -128) v = -128;
        r.m64_i8[i] = (signed char)v;
        v = (long)_MM2.m64_i16[i];
        if (v > 127) v = 127;
        if (v < -128) v = -128;
        r.m64_i8[i + 4] = (signed char)v;
    }
    return r;
}

static __inline __m64 _m_packssdw(__m64 _MM1, __m64 _MM2)
{
    __m64 r;
    int i;
    for (i = 0; i < 2; i++)
    {
        long v = (long)_MM1.m64_i32[i];
        if (v > 32767) v = 32767;
        if (v < -32768) v = -32768;
        r.m64_i16[i] = (short)v;
        v = (long)_MM2.m64_i32[i];
        if (v > 32767) v = 32767;
        if (v < -32768) v = -32768;
        r.m64_i16[i + 2] = (short)v;
    }
    return r;
}

static __inline __m64 _m_packuswb(__m64 _MM1, __m64 _MM2)
{
    __m64 r;
    int i;
    for (i = 0; i < 4; i++)
    {
        long v = (long)_MM1.m64_i16[i];
        if (v > 255) v = 255;
        if (v < 0) v = 0;
        r.m64_u8[i] = (unsigned char)v;
        v = (long)_MM2.m64_i16[i];
        if (v > 255) v = 255;
        if (v < 0) v = 0;
        r.m64_u8[i + 4] = (unsigned char)v;
    }
    return r;
}

static __inline __m64 _m_punpcklbw(__m64 _MM1, __m64 _MM2)
{
    __m64 r;
    int i;
    for (i = 0; i < 4; i++)
    {
        r.m64_u8[2 * i] = _MM1.m64_u8[i];
        r.m64_u8[2 * i + 1] = _MM2.m64_u8[i];
    }
    return r;
}

static __inline __m64 _m_punpckhbw(__m64 _MM1, __m64 _MM2)
{
    __m64 r;
    int i;
    for (i = 0; i < 4; i++)
    {
        r.m64_u8[2 * i] = _MM1.m64_u8[i + 4];
        r.m64_u8[2 * i + 1] = _MM2.m64_u8[i + 4];
    }
    return r;
}

static __inline __m64 _m_punpcklwd(__m64 _MM1, __m64 _MM2)
{
    __m64 r;
    int i;
    for (i = 0; i < 2; i++)
    {
        r.m64_u16[2 * i] = _MM1.m64_u16[i];
        r.m64_u16[2 * i + 1] = _MM2.m64_u16[i];
    }
    return r;
}

static __inline __m64 _m_punpckhwd(__m64 _MM1, __m64 _MM2)
{
    __m64 r;
    int i;
    for (i = 0; i < 2; i++)
    {
        r.m64_u16[2 * i] = _MM1.m64_u16[i + 2];
        r.m64_u16[2 * i + 1] = _MM2.m64_u16[i + 2];
    }
    return r;
}

static __inline __m64 _m_punpckldq(__m64 _MM1, __m64 _MM2)
{
    __m64 r;
    r.m64_u32[0] = _MM1.m64_u32[0];
    r.m64_u32[1] = _MM2.m64_u32[0];
    return r;
}

static __inline __m64 _m_punpckhdq(__m64 _MM1, __m64 _MM2)
{
    __m64 r;
    r.m64_u32[0] = _MM1.m64_u32[1];
    r.m64_u32[1] = _MM2.m64_u32[1];
    return r;
}

static __inline __m64 _m_pcmpeqd(__m64 _MM1, __m64 _MM2)
{
    __m64 r;
    r.m64_u32[0] = (_MM1.m64_u32[0] == _MM2.m64_u32[0]) ? 0xFFFFFFFFu : 0u;
    r.m64_u32[1] = (_MM1.m64_u32[1] == _MM2.m64_u32[1]) ? 0xFFFFFFFFu : 0u;
    return r;
}

static __inline __m64 _m_pandn(__m64 _MM1, __m64 _MM2)
{
    __m64 r;
    r.m64_u64 = (~_MM1.m64_u64) & _MM2.m64_u64;
    return r;
}

static __inline __m64 _m_por(__m64 _MM1, __m64 _MM2)
{
    __m64 r;
    r.m64_u64 = _MM1.m64_u64 | _MM2.m64_u64;
    return r;
}

#endif /* _M_X64 */

#endif /* MMX_COMPAT_H_INCLUDED */
