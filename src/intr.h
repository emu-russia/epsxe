#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned int dword_4FD870;
extern unsigned int dword_4FD874;
extern unsigned int dword_50BFD8[1];
extern unsigned int dword_50BFDC[1];
extern unsigned int dword_50C010[1];
extern unsigned int dword_50C014[1];
extern unsigned int dword_50C018[1];
extern unsigned int dword_50C01C[0x4d];
extern unsigned int dword_50C150[1];
extern unsigned int dword_50C154[1];
extern unsigned int dword_50C158[0x2e];
extern unsigned int dword_50C218;
extern unsigned int dword_50C21C;
extern unsigned int dword_50C220[0x10];

/* Function prototypes (previously generated in src/_gen) */
void cdrom_assert_int();
char irq_clear_hw_regs();
unsigned int irq_cpu_interrupt();
int __cdecl irq_dma_assert_int(unsigned __int8 a1);
int irq_sio_update();
void irq_spu_registered_callback();
int __cdecl irq_unfreeze(int a1, _DWORD *a2);
char __cdecl rcnt_write_reg(unsigned __int16 a1, int a2);
void sio_assert_int();
int __cdecl sub_42B080(const char *a1, int a2);
