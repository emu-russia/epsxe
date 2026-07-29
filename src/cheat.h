#pragma once

#pragma pack(push,1)

typedef struct _CHEAT_DB_ENTRY {

	char gameid[14];
	char text[56];
	uint8_t mdectiming;
	uint8_t dword_50C374;
	uint8_t forcespu;
	uint8_t forcepad;
	uint8_t byte_455946;
	uint8_t parasite_eve_cheat;
	uint8_t byte_455FA4;
	uint8_t byte_4F75AA;
	uint8_t nocdstatus;
	uint8_t unk;
	uint8_t byte_4FC4E6;
	
} CHEAT_DB_ENTRY;

typedef struct _MINI_CHEAR_ENTRY {
	
	char id[16]; 			// "SLUS_008.45"
	uint32_t attr; 		// 0x10023458
	uint32_t unk;

} MINI_CHEAR_ENTRY;

#pragma pack(pop)

//cheat_entries_count dd 39

//00450C78
//00454CC0  = 200 + 1