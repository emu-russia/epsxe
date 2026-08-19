#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned int console_log_handle;
extern unsigned char dcache[0x1000];
extern unsigned int mem_read_hooks[0x10000];
extern unsigned int mem_write_hooks[0x10000];
extern unsigned char ram[0x200000];
extern unsigned int sio0_control_reg;

/* Function prototypes (previously generated in src/_gen) */
int mem_clear_memory();
int mem_dma_read(unsigned int addr);
int mem_freeze(const char *name, int gzf);
unsigned int mem_gpu_dma_read(unsigned int addr);
void mem_gpu_dma_write(unsigned int addr, unsigned int value);
void mem_hw_reg_read_byte(unsigned int addr);
void mem_hw_reg_write_byte(unsigned int addr, char value);
void mem_hw_reg_write_half(unsigned int addr, uint16_t value);
void mem_init_memory_handlers();
int16_t mem_read_half(unsigned int addr);
int mem_read_word(unsigned int addr);
int mem_unfreeze(int unused, uint32_t *gzf);
void mem_write_half(unsigned int addr, uint16_t value);
void mem_write_word(unsigned int addr, unsigned int value);
