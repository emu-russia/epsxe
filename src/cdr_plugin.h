#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned char cdrom_fake_filename[0x100];
extern unsigned int hCdrModule;

/* Function prototypes (previously generated in src/_gen) */
char ext_CDR_get_first_last_track(uint8_t *first_track, uint8_t *last_track);
uint8_t ext_CDR_lba_to_msf( uint8_t min, uint8_t sec, uint8_t frame, uint8_t *out_min, uint8_t *out_sec, uint8_t *out_frame);
int ext_CDR_read(uint8_t min, uint8_t sec, uint8_t frame, char *Buffer);
void ext_CDR_reset_state();
char ext_CDR_track_to_msf(int16_t track, uint8_t *min, uint8_t *sec, uint8_t *frame);
char ext_CDR_verify_subchannel_data(uint8_t min, uint8_t sec, uint8_t frame, int buffer);
char ext_CDRplay(int track_msf, char sec);
char ext_CDRstop();
int (*ext_cdrom_deinit())(void);
char ext_cdrom_load_plugin();
