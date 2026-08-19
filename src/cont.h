#pragma once
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned char dynarec_clear_needed;
extern unsigned char g_KeyboardStatePrev[1];
extern unsigned int g_MouseButtons;
extern unsigned char gpu_keyboard_state[0x1b];
extern unsigned char joystick_button_state1[4];
extern unsigned char joystick_button_state2[4];
extern unsigned char joystick_button_state3[4];
extern unsigned char joystick_button_state4[4];
extern unsigned int mdec_disable_flag[1];
extern unsigned int mouse_buttons_state;
extern int mouse_delta_x;
extern int mouse_delta_y;
extern int netplay_reset_request;
extern unsigned short pad1_buttons_low;
extern unsigned short pad2_buttons_low;
extern unsigned char xenogears_trick_enabled;

/* Function prototypes (previously generated in src/_gen) */
char cont_build_controller_response_analog(char port, uint8_t *response);
uint8_t * cont_build_controller_response_digital(char port, uint8_t *response);
uint8_t * cont_build_guncon_response(char port, uint8_t *response);
uint8_t * cont_build_mouse_response(char port, uint8_t *response);
int16_t cont_map_axis_state(uint16_t axis, int16_t value);
int16_t cont_map_button_state(uint16_t key, int16_t value);
int cont_process_input();
int cont_reset_pad_state(uint8_t port);
int cont_set_default(uint8_t port);
int (__stdcall * cont_update_led_and_mode(uint8_t port))(uint32_t);
