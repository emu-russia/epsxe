#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned int mdec_status;
extern unsigned int mdec_timer_count;

/* Function prototypes (previously generated in src/_gen) */
int mdec_decode();
void mdec_dma_in_handler();
int mdec_freeze(const char *filename, int file);
int mdec_freeze2(const char *filename, int file);
int mdec_handle_special_command(int command);
int mdec_init();
char mdec_timer_handler();
int mdec_unfreeze(int unused, uint32_t *file);
int mdec_unfreeze2(int unused, uint32_t *file);
int16_t mdec_write_command(unsigned int command);
