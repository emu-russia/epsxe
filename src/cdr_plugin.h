#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern int ( *CDRclose)();
extern int ( *CDRgetBuffer)();
extern int ( *CDRgetBufferSub)();
extern int ( *CDRgetTD)();
extern unsigned int CDRgetTN;
extern int ( *CDRinit)();
extern int ( *CDRopen)();
extern unsigned int CDRplay;
extern int ( *CDRreadTrack)();
extern int ( *CDRshutdown)();
extern int ( *CDRstop)();
extern unsigned int CDRtest;
extern unsigned char cdrom_fake_filename[0x100];
extern unsigned short current_position_low;
extern unsigned int current_position_msf;
extern unsigned short first_last_tracks;
extern unsigned int hCdrModule;
extern unsigned int track_info_buffer;
extern unsigned char track_minutes_table[1];
extern unsigned char track_msf_minutes[1];
extern unsigned char track_msf_seconds[1];
extern unsigned char track_msf_sectors[1];
extern unsigned char track_msf_table[1];
extern unsigned char track_seconds_table[1];
extern unsigned char track_sectors_table[0x139];

/* Function prototypes (previously generated in src/_gen) */
char ext_CDR_get_first_last_track(uint8_t *a1, uint8_t *a2);
uint8_t ext_CDR_lba_to_msf( uint8_t a1, uint8_t a2, uint8_t a3, uint8_t *a4, uint8_t *a5, uint8_t *a6);
int ext_CDR_read(uint8_t a1, uint8_t a2, uint8_t a3, char *Buffer);
void ext_CDR_reset_state();
char ext_CDR_track_to_msf(int16_t a1, uint8_t *a2, uint8_t *a3, uint8_t *a4);
char ext_CDR_verify_subchannel_data(uint8_t a1, uint8_t a2, uint8_t a3, int a4);
char ext_CDRplay(int a1, char a2);
char ext_CDRstop();
int (*ext_cdrom_deinit())(void);
char ext_cdrom_load_plugin();
