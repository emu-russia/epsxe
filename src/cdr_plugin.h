#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern int (__cdecl *CDRclose)();
extern int (__cdecl *CDRgetBuffer)();
extern int (__cdecl *CDRgetBufferSub)();
extern int (__cdecl *CDRgetTD)();
extern unsigned int CDRgetTN;
extern int (__cdecl *CDRinit)();
extern int (__cdecl *CDRopen)();
extern unsigned int CDRplay;
extern int (__cdecl *CDRreadTrack)();
extern int (__cdecl *CDRshutdown)();
extern int (__cdecl *CDRstop)();
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
char __cdecl ext_CDR_get_first_last_track(_BYTE *a1, _BYTE *a2);
unsigned __int8 __cdecl ext_CDR_lba_to_msf( unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3, unsigned __int8 *a4, unsigned __int8 *a5, unsigned __int8 *a6);
int __cdecl ext_CDR_read(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3, char *Buffer);
void ext_CDR_reset_state();
char __cdecl ext_CDR_track_to_msf(__int16 a1, _BYTE *a2, _BYTE *a3, _BYTE *a4);
char __cdecl ext_CDR_verify_subchannel_data(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3, int a4);
char __cdecl ext_CDRplay(int a1, char a2);
char ext_CDRstop();
int (*ext_cdrom_deinit())(void);
char ext_cdrom_load_plugin();
