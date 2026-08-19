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
extern unsigned char net_closed_flag;
extern unsigned char netplay_pad2_reserved_1;
extern unsigned char netplay_pad2_reserved_2;
extern unsigned char netplay_pad2_reserved_3;
extern unsigned char netplay_pad2_reserved_4;
extern unsigned char netplay_pad2_reserved_5;
extern unsigned char netplay_pad2_reserved_6;
extern unsigned char netplay_pad2_reserved_7;
extern unsigned char netplay_joy1_state;
extern unsigned char netplay_joy2_state;
extern unsigned char netplay_joy3_state;
extern unsigned char netplay_joy4_state;
extern unsigned char netplay_sound_enabled;
extern unsigned char netplay_start_options[0x41f];
extern unsigned char netplay_config_mdectiming;
extern unsigned char netplay_config_mdec_disable;
extern unsigned char netplay_config_xa_read_enable;
extern unsigned char netplay_config_padding[0x405];
extern unsigned int netplay_pad2_state;
extern unsigned int netplay_pad1_state;
extern unsigned int netplay_mouse_state;
extern unsigned int netplay_player_count;
extern unsigned int netplay_config_packet;
extern unsigned int netplay_config_options;
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
