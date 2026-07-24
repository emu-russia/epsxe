#pragma once

#include <stdint.h>
#include <stdio.h>
#include <Windows.h>
#include <intrin.h>
#include <mmintrin.h>
#include <windef.h>

#define __noreturn

#define nullptr NULL

typedef BYTE _BYTE;
typedef DWORD _DWORD;
typedef uint64_t _QWORD;
typedef uint16_t _WORD;
typedef BOOLEAN bool;

#define BYTEn(x, n) (*((unsigned char*)&(x) + n))
#define BYTE0(x) BYTEn(x, 0)
#define BYTE1(x) BYTEn(x, 1)
#define BYTE2(x) BYTEn(x, 2)

#include "../zlib-1.1.3/zlib.h"
#include "psemu.h"
#include "psxdefs.h"
#include "gte.h"
#include "zip.h"
#include "ppf.h"