#pragma once

/**
 * \file bios_descr.h
 * \brief Declarations for the BIOS descriptor table.
 *
 * Defines the BIOS_DESCR structure used by the setup wizard to identify
 * known PSX BIOS images by their CRC32 checksum and display a friendly
 * description (region/version) in the BIOS selection dialog.
 */

#pragma pack(push, 1)
/**
 * \brief Describes a known PSX BIOS image: its CRC32 checksum and a short description string.
 */
typedef struct _BIOS_DESCR
{
	uint32_t crc;
	char descr[32];
} BIOS_DESCR;
typedef struct _BIOS_DESCR _BIOS_DESCR;
#pragma pack(pop)
