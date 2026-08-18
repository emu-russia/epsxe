#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned char byte_505680[0xd];
extern unsigned char byte_505691;
extern unsigned char byte_505695[0x4b];
extern unsigned char byte_505700[0x1160];
extern unsigned char byte_50A1A4;
extern unsigned char byte_50A1A5;
extern unsigned char byte_50A1A6;
extern unsigned int dword_456D74;
extern unsigned int dword_456D78;
extern unsigned int dword_4FD9A8;
extern unsigned int dword_4FD9AC;
extern unsigned int dword_505400;
extern unsigned int dword_50568D;
extern unsigned int dword_50A098;
extern unsigned char use_subchannel;
extern unsigned short word_505693;

/* Function prototypes (previously generated in src/_gen) */
int iso_close();
char __cdecl iso_load(char *FileName);
char __cdecl iso_read_data(unsigned __int8 a1, unsigned __int8 a2, unsigned __int8 a3, int a4);
char __cdecl iso_verify_sub(unsigned __int8 a1, unsigned __int8 a2, char a3, int a4);
