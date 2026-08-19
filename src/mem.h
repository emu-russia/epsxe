#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned int console_log_handle;
extern unsigned char dcache[0x1000];
extern unsigned char dummy_page[0x10000];
extern unsigned char mem_handlers_inited;
extern unsigned int mem_read_hooks[0x10000];
extern unsigned int mem_write_hooks[0x10000];
extern unsigned char pio_mem[0x20000];
extern unsigned char ram[0x200000];
extern unsigned int sio0_control_reg;

/* Function prototypes (previously generated in src/_gen) */
int __cdecl mem_dma_read(unsigned int a1);
int __cdecl mem_freeze(const char *a1, int a2);
unsigned int __cdecl mem_gpu_dma_read(unsigned int a1);
void __cdecl mem_gpu_dma_write(unsigned int a1, unsigned int a2);
void __cdecl mem_hw_reg_read_byte(unsigned int a1);
void __cdecl mem_hw_reg_write_byte(unsigned int a1, char a2);
void __cdecl mem_hw_reg_write_half(unsigned int a1, unsigned __int16 a2);
void mem_init_memory_handlers();
__int16 __cdecl mem_read_half(unsigned int a1);
int __cdecl mem_read_word(unsigned int a1);
int __cdecl mem_unfreeze(int a1, _DWORD *a2);
void __cdecl mem_write_half(unsigned int a1, unsigned __int16 a2);
void __cdecl mem_write_word(unsigned int a1, unsigned int a2);
