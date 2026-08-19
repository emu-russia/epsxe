#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned char use_subchannel;

/* Function prototypes (previously generated in src/_gen) */
int iso_close();
char iso_load(char *FileName);
char iso_read_data(uint8_t minute, uint8_t second, uint8_t frame, int buffer);
char iso_verify_sub(uint8_t minute, uint8_t second, char frame, int buffer);
