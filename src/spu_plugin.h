#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned int Size[0x100];
extern unsigned int spu_dma_chcr_ptr;
extern unsigned char sound_enabled;
extern unsigned int spu_adpcm_flag;

/* Function prototypes (previously generated in src/_gen) */
int (* spu_async_update(int cycles))(void);
char spu_close();
char spu_destroy();
void spu_dma();
void spu_freeze(const char *id, int gzfile);
char spu_load_plugin();
char spu_open();
char spu_play_adpcm(int hdr);
int16_t spu_read_register(unsigned int reg);
void spu_set_adpcm_flag();
void spu_unfreeze(int unused, uint32_t *gzfile);
int (*spu_update())(void);
char spu_write_register(unsigned int reg, int16_t value);
