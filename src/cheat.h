#pragma once

#pragma pack(push,1)

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

typedef struct _MINI_CHEAT_ENTRY {
	
	char id[16]; 			// "SLUS_008.45"
	uint32_t attr; 		// 0x10023458
	uint32_t unk;

} MINI_CHEAT_ENTRY;

#pragma pack(pop)
/* Decompiled globals (previously generated in src/_gen) */
extern CHEAT_DB_ENTRY cheat_db[200];
extern MINI_CHEAT_ENTRY mini_cheat_db[200];
