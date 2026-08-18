#pragma once

#pragma pack(push, 1)
typedef struct _BIOS_DESCR
{
	uint32_t crc;
	char descr[32];
} BIOS_DESCR;
typedef struct _BIOS_DESCR _BIOS_DESCR;
#pragma pack(pop)
