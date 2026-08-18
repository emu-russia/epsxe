#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned char bin_iso_file[0x100];
extern unsigned char byte_45B8E8;
extern unsigned int dword_44DF24[1];
extern unsigned int dword_45B8D8;
extern unsigned char g_bDisableMouse;
extern unsigned int g_hInstance;
extern unsigned int g_hWnd;
extern unsigned int h;
extern MSG stru_8A94E0;

/* Function prototypes (previously generated in src/_gen) */
BOOL create_main_window();
LRESULT __stdcall main_window_callback(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
BOOL register_win_class();
void save_load_state();
