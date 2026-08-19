#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned char gpu_dma2_delay_counter;
extern unsigned char gpu_dma2_state;
extern unsigned char gpu_dma6_delay_counter;
extern unsigned int gpu_dma_channel_status[1];
extern unsigned int hInst_For_DInput;
extern unsigned int hOutputWnd;
extern unsigned char use_performance_counters;

/* Function prototypes (previously generated in src/_gen) */
int gpu_close();
BOOL gpu_close_output_window();
HWND gpu_create_output_window();
int (__stdcall * gpu_cursor(int x, int y, int flag))(uint32_t, uint32_t, uint32_t);
HMODULE gpu_destroy();
int (__stdcall * gpu_display_flags(int flags))(uint32_t);
char gpu_dma();
char gpu_dma2_interrupt();
char gpu_dma6_interrupt();
int (__stdcall * gpu_do_freeze(int slot))(uint32_t, uint32_t);
int gpu_frame_update();
void gpu_freeze(const char *id, int ArgList, const char *picname);
int (__stdcall *gpu_hide_screen_pic())(uint32_t);
char gpu_init_performance_counter();
HWND gpu_load_plugin();
int (*gpu_make_snapshot())(void);
int gpu_open();
int (__stdcall *gpu_open_with_input())(uint32_t, uint32_t);
int gpu_readData();
int gpu_readStatus();
void gpu_show_screen_pic(uint8_t slot);
void gpu_unfreeze(int unused, uint32_t *ArgList);
int gpu_writeData(int data);
int gpu_writeStatus(int data);
