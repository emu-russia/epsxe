#pragma once

/**
 * \file pch.h
 * \brief Precompiled header and global include aggregation point.
 *
 * Includes the standard library, Windows, plugin API and per-module
 * headers used across the emulator, and defines the compatibility
 * macros and pragmas the decompiled code relies on (byte/word accessors,
 * IDA decompiler helpers, warning suppressions, plugin API renames, etc.).
 */

#include <stdint.h>
#include <stdio.h>
#include <Windows.h>
#include <intrin.h>
#include <mmintrin.h>
#include <emmintrin.h>
#include <windef.h>
#include <ntddscsi.h>
#include <dsound.h>
#include <dinput.h>
#include "mmx_compat.h"
#include "../resources/Resource.h"

#define __noreturn

#define nullptr NULL

/* Decompiled code relies on several deprecated/risky constructs */
#pragma warning(disable : 4996) /* deprecated functions (GetVersionExA etc.) */
#pragma warning(disable : 4700) /* uninitialized local (decompiler artifacts) */
#pragma warning(disable : 4701) /* potentially uninitialized local */
#pragma warning(disable : 4047) /* pointer/int conversions */
#pragma warning(disable : 4022) /* pointer type mismatch in call */
#pragma warning(disable : 4311) /* pointer truncation casts */
#pragma warning(disable : 4312) /* pointer widening casts */
#pragma warning(disable : 4133) /* incompatible function pointer types */
#pragma warning(disable : 4244) /* int conversion loss */
#pragma warning(disable : 4013) /* implicit function declaration */

typedef BOOLEAN bool;

#define BYTEn(x, n) (*((unsigned char*)&(x) + n))
#define BYTE0(x) BYTEn(x, 0)
#define BYTE1(x) BYTEn(x, 1)
#define BYTE2(x) BYTEn(x, 2)
#define BYTE3(x) BYTEn(x, 3)
#define BYTE4(x) BYTEn(x, 4)
#define BYTE5(x) BYTEn(x, 5)
#define BYTE6(x) BYTEn(x, 6)
#define BYTE7(x) BYTEn(x, 7)
#define BYTE8(x) BYTEn(x, 8)
#define SBYTEn(x, n) (*((signed char*)&(x) + n))
#define SBYTE1(x) SBYTEn(x, 1)
#define SBYTE2(x) SBYTEn(x, 2)
#define SBYTE3(x) SBYTEn(x, 3)
#define SBYTE4(x) SBYTEn(x, 4)
#define SLOBYTE(x) SBYTEn(x, 0)
#define SHIBYTE(x) SBYTEn(x, 3)
#define SLOWORD(x) (*((short*)&(x)))
#define SHIWORD(x) (*((short*)&(x) + 1))

/* IDA-style lvalue byte/word accessors (winnt.h versions are rvalues) */
#undef LOBYTE
#undef HIBYTE
#undef LOWORD
#undef HIWORD
#undef LODWORD
#undef HIDWORD
#define LOBYTE(w)   (*((BYTE *)&(w)))
#define HIBYTE(w)   (*((BYTE *)&(w) + 1))
#define LOWORD(w)   (*((WORD *)&(w)))
#define HIWORD(w)   (*((WORD *)&(w) + 1))
#define LODWORD(w)  (*((DWORD *)&(w)))
#define HIDWORD(w)  (*((DWORD *)&(w) + 1))

/** \brief IDA decompiler helper aliases: qmemcpy/qmemmove/qmemcmp map to the CRT memcpy/memmove/memcmp. */
#define qmemcpy memcpy
#define qmemmove memmove
#define qmemcmp memcmp

/* GetProcAddress returns FARPROC (__stdcall on x86); the decompiled code
 * assigns it to function pointers, which is an error on x86.
 * Casting to void* lets C convert implicitly to any function pointer type. */
#define GetProcAddress(h, n) ((void *)(GetProcAddress)(h, n))

/* DirectInput error codes */
#ifndef DIERR_INPUTLOST
#define DIERR_INPUTLOST 0x8007001EL
#endif

#include "../zlib-1.1.3/zlib.h"
/* Plugin API typedefs are renamed so decompiled global function-pointer
   variables can share the same names (C forbids same-scope shadowing). */
#define CDRclose CDRclose_t
#define CDRconfigure CDRconfigure_t
#define CDRgetBuffer CDRgetBuffer_t
#define CDRgetBufferSub CDRgetBufferSub_t
#define CDRgetTD CDRgetTD_t
#define CDRgetTN CDRgetTN_t
#define CDRinit CDRinit_t
#define CDRopen CDRopen_t
#define CDRplay CDRplay_t
#define CDRreadTrack CDRreadTrack_t
#define CDRshutdown CDRshutdown_t
#define CDRstop CDRstop_t
#define CDRtest CDRtest_t
#define GPUabout GPUabout_t
#define GPUclearDynarec GPUclearDynarec_t
#define GPUclose GPUclose_t
#define GPUconfigure GPUconfigure_t
#define GPUcursor GPUcursor_t
#define GPUdmaChain GPUdmaChain_t
#define GPUfreeze GPUfreeze_t
#define GPUgetScreenPic GPUgetScreenPic_t
#define GPUinit GPUinit_t
#define GPUmakeSnapshot GPUmakeSnapshot_t
#define GPUopen GPUopen_t
#define GPUreadData GPUreadData_t
#define GPUreadDataMem GPUreadDataMem_t
#define GPUreadStatus GPUreadStatus_t
#define GPUshowScreenPic GPUshowScreenPic_t
#define GPUshutdown GPUshutdown_t
#define GPUtest GPUtest_t
#define GPUupdateLace GPUupdateLace_t
#define GPUwriteData GPUwriteData_t
#define GPUwriteDataMem GPUwriteDataMem_t
#define GPUwriteStatus GPUwriteStatus_t
#define NETclose NETclose_t
#define NETinit NETinit_t
#define NETopen NETopen_t
#define NETpause NETpause_t
#define NETqueryPlayer NETqueryPlayer_t
#define NETresume NETresume_t
#define NETshutdown NETshutdown_t
#define PSEgetLibName PSEgetLibName_t
#define PSEgetLibType PSEgetLibType_t
#define PSEgetLibVersion PSEgetLibVersion_t
#define SPUabout SPUabout_t
#define SPUasync SPUasync_t
#define SPUclose SPUclose_t
#define SPUconfigure SPUconfigure_t
#define SPUfreeze SPUfreeze_t
#define SPUinit SPUinit_t
#define SPUopen SPUopen_t
#define SPUplayADPCMchannel SPUplayADPCMchannel_t
#define SPUplaySample SPUplaySample_t
#define SPUreadDMA SPUreadDMA_t
#define SPUreadDMAMem SPUreadDMAMem_t
#define SPUreadRegister SPUreadRegister_t
#define SPUregisterCallback SPUregisterCallback_t
#define SPUshutdown SPUshutdown_t
#define SPUtest SPUtest_t
#define SPUwriteDMA SPUwriteDMA_t
#define SPUwriteDMAMem SPUwriteDMAMem_t
#define SPUwriteRegister SPUwriteRegister_t
#include "psemu.h"
#undef CDRclose
#undef CDRconfigure
#undef CDRgetBuffer
#undef CDRgetBufferSub
#undef CDRgetTD
#undef CDRgetTN
#undef CDRinit
#undef CDRopen
#undef CDRplay
#undef CDRreadTrack
#undef CDRshutdown
#undef CDRstop
#undef CDRtest
#undef GPUabout
#undef GPUclearDynarec
#undef GPUclose
#undef GPUconfigure
#undef GPUcursor
#undef GPUdmaChain
#undef GPUfreeze
#undef GPUgetScreenPic
#undef GPUinit
#undef GPUmakeSnapshot
#undef GPUopen
#undef GPUreadData
#undef GPUreadDataMem
#undef GPUreadStatus
#undef GPUshowScreenPic
#undef GPUshutdown
#undef GPUtest
#undef GPUupdateLace
#undef GPUwriteData
#undef GPUwriteDataMem
#undef GPUwriteStatus
#undef NETclose
#undef NETinit
#undef NETopen
#undef NETpause
#undef NETqueryPlayer
#undef NETresume
#undef NETshutdown
#undef PSEgetLibName
#undef PSEgetLibType
#undef PSEgetLibVersion
#undef SPUabout
#undef SPUasync
#undef SPUclose
#undef SPUconfigure
#undef SPUfreeze
#undef SPUinit
#undef SPUopen
#undef SPUplayADPCMchannel
#undef SPUplaySample
#undef SPUreadDMA
#undef SPUreadDMAMem
#undef SPUreadRegister
#undef SPUregisterCallback
#undef SPUshutdown
#undef SPUtest
#undef SPUwriteDMA
#undef SPUwriteDMAMem
#undef SPUwriteRegister
#include "psxdefs.h"
#include "bios_descr.h"
#include "gte.h"
#include "zip.h"
#include "ppf.h"
#include "main.h"
#include "cfg.h"
#include "op_tabs.h"
#include "ops.h"
#include "cpu.h"
#include "cheat.h"
#include "spucore.h"
#include "input.h"
#include "wnaspi32.h"

/* Per-module declarations (globals + prototypes formerly generated in src/_gen) */
#include "burutter.h"
#include "cdfs.h"
#include "cdr.h"
#include "cdr_plugin.h"
#include "cdrom_fake.h"
#include "cdrom_iso.h"
#include "cdrom_w2k.h"
#include "cdrom_w9x.h"
#include "cont.h"
#include "debug.h"
#include "dinput_shim.h"
#include "dlg_callbacks.h"
#include "dynarec.h"
#include "gpu_plugin.h"
#include "hw.h"
#include "intr.h"
#include "loader.h"
#include "mainwnd.h"
#include "mdec.h"
#include "mem.h"
#include "net.h"
#include "plugin.h"
#include "setup_wizard.h"
#include "sio.h"
#include "spu_plugin.h"
#include "sstates.h"
#include "xa.h"
