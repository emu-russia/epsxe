#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern int (__stdcall *GPUabout_0)();
extern int (__stdcall *GPUinit_0)();
extern int (__stdcall *GPUshutdown_0)();
extern int (__stdcall *GPUtest_0)();
extern int ( *PSEconfigure)();
extern int ( *PSEgetLibName)();
extern int ( *PSEgetLibType)();
extern int ( *PSEgetLibVersion)();
extern unsigned char plugin_name_list_shift[0x380];
extern unsigned char plugin_name_list[0x4];
extern unsigned char plugin_name_list_tail[0x7ffc];
extern unsigned int controller_port_modes[8];
extern unsigned int found_plugin_count;
extern unsigned int pad2_small_motor_type;
extern unsigned int pad4_small_motor_type[1];
extern unsigned int g_EffectType2[1];
extern unsigned int g_PlayerDeviceMap4[1];
extern unsigned char multitap_1;
extern unsigned char pad_number_menu_selection;
extern unsigned char temp_path[0x400];
extern unsigned short pad_key_assignments[4];

/* Function prototypes (previously generated in src/_gen) */
int __stdcall about_callback(HWND hDlg, int uMsg, int16_t wParam, int lParam);
INT_PTR __stdcall bios_dialog_callback(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
int calc_bios_checksum(uint8_t *ptr, int size);
LRESULT __stdcall cheat_dialog_callback(HWND hDlg, int uMsg, int16_t wParam, int lParam);
INT_PTR __stdcall controller_setup_callback(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR __stdcall memcard_settings(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL open_file_dialog(const CHAR *title, const CHAR *filter, CHAR *file_path, const CHAR *initial_dir, const CHAR *def_ext);
INT_PTR __stdcall search_cdrom_plugin(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR __stdcall search_net_plugin(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR __stdcall search_spu_plugin(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR __stdcall search_video_plugin(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR __stdcall spucore_configure_dialog_callback(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR __stdcall w9x_cdrom_settings(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
