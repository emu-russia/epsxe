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
INT_PTR __stdcall setup_wizard_begin(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4);
int __cdecl setup_wizard_callback(HWND hWndParent);
INT_PTR __stdcall setup_wizard_controllers(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4);
INT_PTR __stdcall setup_wizard_end(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4);
HANDLE setup_wizard_init();
INT_PTR __stdcall setup_wizard_search_bios(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4);
INT_PTR __stdcall setup_wizard_search_cdrom_plugin(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4);
INT_PTR __stdcall setup_wizard_search_spu_plugin(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4);
INT_PTR __stdcall setup_wizard_search_video_plugin(HWND hDlg, UINT a2, WPARAM a3, LPARAM a4);
