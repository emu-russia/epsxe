#pragma once

#include <stdint.h>
#include <stdio.h>
#include <Windows.h>
#include <intrin.h>

#define __noreturn

#define nullptr NULL

typedef BYTE _BYTE;
typedef DWORD _DWORD;
typedef uint64_t _QWORD;
typedef uint16_t _WORD;
typedef BOOLEAN bool;

#define BYTE2(n) (((n)>>16)&0xff)

// Pointer-based variants that can be used on both sides of an assignment (=)
#define LOWORD(x) (*((uint16_t*)&(x)))
#define HIWORD(x) (*((uint16_t*)&(x) + 1))
#define LODWORD(x) (*((uint32_t*)&(x)))
#define HIDWORD(x) (*((uint32_t*)&(x) + 1))

#include "../zlib-1.1.3/zlib.h"
#include "../psxdefs.h"
#include "../gte.h"
