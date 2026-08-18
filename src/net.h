#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern int (__stdcall *NETclose)();
extern int (__stdcall *NETcompareData)();
extern int (__stdcall *NETinit)();
extern int (__stdcall *NETopen)();
extern int (__stdcall *NETpadState)();
extern int (__stdcall *NETpause)();
extern int (__stdcall *NETqueryPlayer)();
extern int (__stdcall *NETresume)();
extern int (__stdcall *NETshutdown)();
extern int (__stdcall *NETtransferData)();
extern unsigned char byte_45696C;
extern unsigned char byte_50A1C4;
extern unsigned char byte_50A1C5;
extern unsigned char byte_50A1C6;
extern unsigned char byte_50A1C7;
extern unsigned char byte_50A1C8;
extern unsigned char byte_50A1C9;
extern unsigned char byte_50A1CA;
extern unsigned char byte_50A1D4;
extern unsigned char byte_50A1D5;
extern unsigned char byte_50A1D6;
extern unsigned char byte_50A1D7;
extern unsigned char byte_50A200;
extern unsigned char byte_50A201[0x41f];
extern unsigned char byte_50A628;
extern unsigned char byte_50A629;
extern unsigned char byte_50A62A;
extern unsigned char byte_50A62B[0x405];
extern unsigned int dword_50A1C0;
extern unsigned int dword_50A1D0;
extern unsigned int dword_50A1D8;
extern unsigned int dword_50A1E0;
extern unsigned int dword_50A620;
extern unsigned int dword_50A624;
extern unsigned int hNetModule;
extern unsigned int network_enabled;
extern unsigned int unknown_timing_value;

/* Function prototypes (previously generated in src/_gen) */
HMODULE net_close();
int net_fill_input();
int net_load_plugin();
char net_netplay_handler();
int net_open();
HMODULE net_pause();
HMODULE net_resume();
