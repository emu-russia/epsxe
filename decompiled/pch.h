#pragma once

#include <stdio.h>
#include <Windows.h>

#define __noreturn

#define nullptr NULL

typedef BYTE _BYTE;
typedef DWORD _DWORD;

#define BYTE2(n) (((n)>>16)&0xff)

#include "../zlib-1.1.3/zlib.h"