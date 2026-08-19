#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned char Memcard1[0x400];
extern unsigned char Memcard2[0x400];
extern unsigned char memcard2_data[0x2000];
extern unsigned char pad_analog_mode_flags[8];
extern unsigned int sio0_mode_reg;
extern unsigned char sio_memcard_loaded;
extern unsigned int sio_transfer_pending;
extern unsigned int sio_transfer_timeout;
extern unsigned char sio_tx_fifo[0x104];

/* Function prototypes (previously generated in src/_gen) */
int save_temp_memcard1();
int save_temp_memcard2();
bool sio_controller_init(int16_t control);
char * sio_for_netplay(uint8_t slot);
int sio_freeze(const char *tag, int gz_file);
char sio_memcard_auto_save();
char sio_memcard_both_save();
char sio_memcard_load();
void sio_read_data_byte();
int sio_read_register(int address, char size);
int (__stdcall *sio_reset_all())(uint32_t);
void sio_trigger_rx_ready_irq();
void sio_unfreeze(int unused, uint32_t *gz_file);
void sio_write_data_byte(int unused, char data);
