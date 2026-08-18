#pragma once

/* Function prototypes (previously generated in src/_gen) */
DWORD GetASPI32SupportInfo(void);
void irq_cdrom_assert_int();
int __cdecl irq_freeze(const char *a1, int a2);
char __cdecl irq_rcnt_write_reg(unsigned __int16 a1, int a2);
void irq_sio_assert_int();
int mem_clear_memory();
void memset32(void *dst, unsigned int value, unsigned int count);
