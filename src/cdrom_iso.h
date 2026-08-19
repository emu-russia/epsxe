#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned char subchannel_buffer[0xd];
extern unsigned char subchannel_q_rel_frame;
extern unsigned char subchannel_q_abs_frame[0x4b];
extern unsigned char iso_sector_buffer[0x1160];
extern unsigned char subchannel_msf_minute;
extern unsigned char subchannel_msf_second;
extern unsigned char subchannel_msf_frame;
extern unsigned int iso_cache_start_lba;
extern unsigned int iso_sector_size;
extern unsigned int iso_file_size;
extern unsigned int iso_data_start_offset;
extern unsigned int subchannel_file_handle;
extern unsigned int subchannel_q_track_rel;
extern unsigned int iso_file_handle;
extern unsigned char use_subchannel;
extern unsigned short subchannel_q_abs_ms;

/* Function prototypes (previously generated in src/_gen) */
int iso_close();
char __cdecl iso_load(char *FileName);
char __cdecl iso_read_data(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3, int a4);
char __cdecl iso_verify_sub(unsigned __int8 a1, unsigned __int8 a2, char a3, int a4);
