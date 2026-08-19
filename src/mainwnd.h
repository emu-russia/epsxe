#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned char bin_iso_file[0x100];
extern unsigned char shift_key_pressed;
extern unsigned int save_load_state_slot[1];
extern unsigned int main_window_bitmap;
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
