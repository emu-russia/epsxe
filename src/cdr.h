#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern int adjust_timing;
extern unsigned char cdr_randomize_response_flag;
extern unsigned int g_cdr_data_bytes_transferred;
extern unsigned char g_cdr_irq_pending;
extern unsigned char g_cdr_response_index;
extern unsigned char g_cdr_response_size;
extern unsigned char report_mode_enabled;

/* Function prototypes (previously generated in src/_gen) */
unsigned int cdr_dma();
int cdr_freeze(const char *tag, int gz_file);
int cdr_get_response_status();
int cdr_get_status(int status);
int cdr_msf_to_lba(uint8_t minute, uint8_t second, uint8_t frame);
void cdr_play_tick();
char cdr_process_delays();
char cdr_reg0_write(char command);
void cdr_reg1_write(uint8_t command);
char cdr_reg2_write(char command);
void cdr_reg3_write(char command);
char cdr_reset_controller();
void cdr_spinup_motor();
int cdr_unfreeze(int unused, uint32_t *gz_file);
int cdr_unfreeze_new(int unused, uint32_t *gz_file);
char cdr_update_motor_status();
