#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern char FileName[256];
extern unsigned char video_plugin_search_path[0x400];
extern unsigned char spu_plugin_search_path[0x400];
extern unsigned char cdrom_plugin_search_path[0x400];
extern unsigned char bios_search_path[0x80];
extern unsigned char cdrom_plugin_configured_flag;
extern BIOS_DESCR debug_bios;
extern BIOS_DESCR retail_bioses;
extern unsigned int setup_wizard_step;

/* Function prototypes (previously generated in src/_gen) */
int setup_wizard_callback(HWND hWndParent);
