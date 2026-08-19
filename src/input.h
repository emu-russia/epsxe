#pragma once

/**
 * \file input.h
 * \brief DirectInput keyboard, mouse and joystick handling.
 *
 * Declares the DirectInput device-state accessors used to poll the
 * keyboard, mouse and up to four joysticks, plus the global input
 * state shared with the pad emulation (cont.c) and the input
 * configuration dialog.
 */

/** \brief Name of a keyboard entry, stored as a fixed 13-character text field. */
typedef struct _KBD_NAME {
	char text[13];
} KBD_NAME;

/** \brief Name of a joystick entry, stored as a fixed 14-character text field. */
typedef struct _JOY_NAME {
	char text[14];
} JOY_NAME;
/* Decompiled globals (previously generated in src/_gen) */
/** \brief Keyboard state buffer used for pad button mapping; written by diUpdateDeviceStates(). */
extern unsigned short g_KeyboardState[1];
/** \brief Joystick device number assigned to pad 1 (player 1's device map). */
extern unsigned int g_PlayerDeviceMap1[1];
/** \brief Window handle used as the DirectInput cooperative-level window (input dialog or main output window). */
extern unsigned int hDlgInput;
/** \brief Whether the mouse (pointing device) input is enabled. */
extern unsigned int point_device_enabled;

/* Function prototypes (previously generated in src/_gen) */
/**
 * \brief Acquires all DirectInput devices (joysticks, mouse, keyboard).
 *
 * \return Always 1.
 */
int diAcquireAllDevices();
/**
 * \brief Acquires the DirectInput mouse device.
 *
 * \return Always 1.
 */
int diAcquireMouseDevice();
/**
 * \brief Returns the current mouse X position, clamped to the configured range.
 *
 * \return Clamped mouse X coordinate.
 */
int diGetClampedMouseX();
/**
 * \brief Returns the current mouse Y position, clamped to the configured range.
 *
 * \return Clamped mouse Y coordinate.
 */
int diGetClampedMouseY();
/**
 * \brief Returns joystick button state 1 for a port.
 *
 * \param port  Joystick port (0-3).
 * \return The mapped keyboard-state value for the bound axis.
 */
int diGetJoystickButtonState1(int port);
/**
 * \brief Returns joystick button state 2 for a port.
 *
 * \param port  Joystick port (0-3).
 * \return The mapped keyboard-state value for the bound axis.
 */
int diGetJoystickButtonState2(int port);
/**
 * \brief Returns joystick button state 3 for a port.
 *
 * \param port  Joystick port (0-3).
 * \return The mapped keyboard-state value for the bound axis.
 */
int diGetJoystickButtonState3(int port);
/**
 * \brief Returns joystick button state 4 for a port.
 *
 * \param port  Joystick port (0-3).
 * \return The mapped keyboard-state value for the bound axis.
 */
int diGetJoystickButtonState4(int port);
/**
 * \brief Initializes DirectInput: keyboard, mouse and joystick devices.
 *
 * Creates the DirectInput object, opens the keyboard and (if enabled)
 * mouse devices, enumerates joysticks (and force-feedback effects when
 * a player device map references them), then acquires all devices.
 *
 * \return 1 on success, 0 on failure.
 */
int diInitDirectInput();
/**
 * \brief Sets the force-feedback effect magnitude for a pad.
 *
 * \param effectSet  Which effect set to use (0 or non-zero).
 * \param magnitude  Effect magnitude (0-255 scale).
 * \param unused     Unused parameter.
 * \param port       Pad port whose effect is updated.
 * \return The effect type when no matching effect handler exists, otherwise the handler's result.
 */
int diSetEffectMagnitude(int effectSet, int magnitude, int unused, int port);
/**
 * \brief Shuts down DirectInput and releases all devices.
 *
 * \return The final Release() result of the DirectInput object.
 */
int diShutdownDirectInput();
/**
 * \brief Unacquires all DirectInput devices.
 *
 * \return Always 1.
 */
int diUnacquireAllDevices();
/**
 * \brief Updates keyboard, mouse and joystick device states.
 *
 * Reads the keyboard state into g_KeyboardState, refreshes the
 * per-port joystick axis/button/pov state and computes the axis and
 * button pressed flags used by pad emulation.
 *
 * \return The last device read result.
 */
int diUpdateDeviceStates();
/**
 * \brief Polls the joystick devices and records axis/button state transitions.
 *
 * \return The last device read result.
 */
int diUpdateJoystickStates();
