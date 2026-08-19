#pragma once

/**
 * \file cheat.h
 * \brief Declarations for the cheat database structures and globals.
 *
 * Defines the per-game cheat database entries used to apply game-specific
 * timing and configuration overrides, plus the compact built-in mini cheat
 * entries, and exposes the two global cheat database arrays.
 */

#pragma pack(push,1)

/**
 * \brief Per-game cheat database entry describing game-specific timing/config overrides.
 */
typedef struct _CHEAT_DB_ENTRY {

	char gameid[14];
	char text[56];
	uint8_t mdectiming;
	uint8_t timing_value;
	uint8_t forcespu;
	uint8_t forcepad;
	uint8_t cpu_overclock;
	uint8_t parasite_eve_cheat;
	uint8_t cd_increment;
	uint8_t cd_setting;
	uint8_t nocdstatus;
	uint8_t unk;
	uint8_t cd_extra;
	
} CHEAT_DB_ENTRY;

/**
 * \brief Compact built-in cheat entry (game ID plus attribute), used for the mini cheat database.
 */
typedef struct _MINI_CHEAT_ENTRY {
	
	char id[16]; 			// "SLUS_008.45"
	uint32_t attr; 		// 0x10023458
	uint32_t unk;

} MINI_CHEAT_ENTRY;

#pragma pack(pop)
/* Decompiled globals (previously generated in src/_gen) */
/** \brief The internal cheat database (up to 200 per-game entries), loaded from "cheats\\dataconf.dat". */
extern CHEAT_DB_ENTRY cheat_db[200];
/** \brief The built-in mini cheat database (up to 200 entries), loaded from "cheats\\database.dat". */
extern MINI_CHEAT_ENTRY mini_cheat_db[200];
