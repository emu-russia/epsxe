#pragma once

typedef struct _KBD_NAME {
	char text[13];
} KBD_NAME;

typedef struct _JOY_NAME {
	char text[14];
} JOY_NAME;
/* Decompiled globals (previously generated in src/_gen) */
extern unsigned short g_KeyboardState[1];
extern unsigned int g_PlayerDeviceMap1[1];
extern unsigned int hDlgInput;
extern unsigned int point_device_enabled;

/* Function prototypes (previously generated in src/_gen) */
int diAcquireAllDevices();
int diAcquireMouseDevice();
int diGetClampedMouseX();
int diGetClampedMouseY();
int diGetJoystickButtonState1(int port);
int diGetJoystickButtonState2(int port);
int diGetJoystickButtonState3(int port);
int diGetJoystickButtonState4(int port);
int diInitDirectInput();
int diSetEffectMagnitude(int effectSet, int magnitude, int unused, int port);
int diShutdownDirectInput();
int diUnacquireAllDevices();
int diUpdateDeviceStates();
int diUpdateJoystickStates();
