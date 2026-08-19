#pragma once
/**
 * \file cont.h
 * \brief PSX controller (pad) emulation: input state and response builders.
 *
 * Owns the global pad/joystick/mouse input state and builds the
 * controller responses (digital, analog, mouse, GunCon) that the
 * SIO/controller emulation sends back to the guest. Also processes
 * per-frame input, hotkeys (save/load state, screenshots, pad mode
 * toggles) and netplay input requests.
 */
/* Decompiled globals (previously generated in src/_gen) */
/** \brief Flag requesting that the dynamic recompiler cache be cleared; set by input/state handling and consumed by dynarec.c. */
extern unsigned char dynarec_clear_needed;
/** \brief Snapshot of the previous keyboard state used to detect key presses for pad button mapping. */
extern unsigned char g_KeyboardStatePrev[1];
/** \brief Current DirectInput mouse button state, copied into mouse_buttons_state each frame. */
extern unsigned int g_MouseButtons;
/** \brief Keyboard state shared with the GPU plugin (set/cleared on key messages in gpu_plugin.c). */
extern unsigned char gpu_keyboard_state[0x1b];
/** \brief Per-port joystick button state 1, filled from DirectInput by diGetJoystickButtonState1. */
extern unsigned char joystick_button_state1[4];
/** \brief Per-port joystick button state 2, filled from DirectInput by diGetJoystickButtonState2. */
extern unsigned char joystick_button_state2[4];
/** \brief Per-port joystick button state 3, filled from DirectInput by diGetJoystickButtonState3. */
extern unsigned char joystick_button_state3[4];
/** \brief Per-port joystick button state 4, filled from DirectInput by diGetJoystickButtonState4. */
extern unsigned char joystick_button_state4[4];
/** \brief Flag that disables MDEC decoding for a pad; set by mdec.c and the pad configuration dialog. */
extern unsigned int mdec_disable_flag[1];
/** \brief Current mouse button state used for mouse/GunCon pad emulation. */
extern unsigned int mouse_buttons_state;
/** \brief Current mouse X movement delta for mouse/GunCon pad emulation. */
extern int mouse_delta_x;
/** \brief Current mouse Y movement delta for mouse/GunCon pad emulation. */
extern int mouse_delta_y;
/** \brief Netplay reset request: set when ESC is pressed during netplay so the network layer resets the session. */
extern int netplay_reset_request;
/** \brief Low 16 bits of pad 1 button state, built from the keyboard/joystick mappings. */
extern unsigned short pad1_buttons_low;
/** \brief Low 16 bits of pad 2 button state, built from the keyboard/joystick mappings. */
extern unsigned short pad2_buttons_low;
/** \brief Xenogears trick toggle (initialized to 1); toggled at runtime and checked by the dynarec. */
extern unsigned char xenogears_trick_enabled;

/* Function prototypes (previously generated in src/_gen) */
/**
 * \brief Builds the 9-byte analog pad response for the given port.
 *
 * Writes the analog pad header plus button bytes, then fills the
 * analog stick axes either from the per-port analog stick state or,
 * depending on the controller mode (mouse, joystick), from mouse or
 * joystick input.
 *
 * \param port      Controller port (0-3).
 * \param response  Buffer receiving the 9-byte response.
 * \return The final response byte (or a value derived from it).
 */
char cont_build_controller_response_analog(char port, uint8_t *response);
/**
 * \brief Builds the 5-byte digital pad response for the given port.
 *
 * Fills the response buffer with the pad type header (0x41 0x5A)
 * and the high/low button bytes for the requested port; unknown
 * ports receive all-ones (no controller) data.
 *
 * \param port      Controller port (0-3).
 * \param response  Buffer receiving the 5-byte response.
 * \return The response buffer.
 */
uint8_t * cont_build_controller_response_digital(char port, uint8_t *response);
/**
 * \brief Builds the GunCon (lightgun) response for the given port.
 *
 * Tracks the gun position from accumulated mouse deltas (clamped to
 * the 512x256 lightgun range), reports the trigger buttons, and moves
 * the on-screen crosshair through gpu_cursor().
 *
 * \param port      Controller port (0-3).
 * \param response  Buffer receiving the response bytes.
 * \return The response buffer, or the gpu_cursor() result when drawing the crosshair.
 */
uint8_t * cont_build_guncon_response(char port, uint8_t *response);
/**
 * \brief Builds the PSX mouse response for the given port.
 *
 * Writes the mouse header, button byte derived from mouse_buttons_state,
 * and the current mouse delta bytes.
 *
 * \param port      Controller port (0-1).
 * \param response  Buffer receiving the response bytes.
 * \return The response buffer.
 */
uint8_t * cont_build_mouse_response(char port, uint8_t *response);
/**
 * \brief Stores a calibrated axis value into the GamepadAxis table.
 *
 * \param axis   Axis index into the GamepadAxis calibration table.
 * \param value  Axis value to store (ignored when zero).
 * \return The value that was passed in.
 */
int16_t cont_map_axis_state(uint16_t axis, int16_t value);
/**
 * \brief Stores a button mapping value into the Keys1 table.
 *
 * \param key    Key index into the Keys1 binding table.
 * \param value  Binding value to store (ignored when 1).
 * \return The value that was passed in.
 */
int16_t cont_map_button_state(uint16_t key, int16_t value);
/**
 * \brief Processes all controller input for one frame.
 *
 * Updates DirectInput device states and mouse/joystick state, handles
 * runtime hotkeys (ESC, save/load state, slot switching, screenshots,
 * pad mode toggles, Xenogears trick), rebuilds the four pad button
 * states from the keyboard mapping, and fills netplay input when
 * netplay is active.
 *
 * \return The netplay fill result (0 when no netplay), 0 after handling certain requests.
 */
int cont_process_input();
/**
 * \brief Clears the pad key assignments and stored pad state for a port.
 *
 * \param port  Controller port whose state is reset.
 * \return Always 0.
 */
int cont_reset_pad_state(uint8_t port);
/**
 * \brief Restores the default keyboard bindings for a pad.
 *
 * For port 1 (pad 2) writes the classic default key layout into
 * Keys1; ports 2-3 have their pad key assignments cleared.
 *
 * \param port  Controller port (0-3).
 * \return 0 after clearing pad key assignments; otherwise the prior result value.
 */
int cont_set_default(uint8_t port);
/**
 * \brief Updates the GPU pad LED/mode display and returns the controller mode handler.
 *
 * Pushes the pad number, analog mode and controller-type flags to the
 * GPU display for analog/mouse/neGcon-style modes, and returns the
 * controller mode as a callback function pointer. The port argument
 * selects the controller port (0-3) whose mode is reported.
 *
 * \return The controller mode callback, or the gpu_display_flags() result for digital pads.
 */
int (__stdcall * cont_update_led_and_mode(uint8_t port))(uint32_t);
