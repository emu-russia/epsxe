#include "pch.h"

/* Decompiled globals (previously generated in src/_gen) */
static GUID GUID_Keyboard;
static GUID GUID_Mouse;
static unsigned char g_directinput_initialized;
static unsigned char joystick_button_1_state[1];
static unsigned char joystick_button_2_state[1];
static unsigned char joystick_button_3_state[1];
static unsigned char joystick_button_4_state[1];
static unsigned char joystick_button_5_state[1];
static unsigned char joystick_button_6_state[1];
static unsigned char joystick_button_7_state[1];
static unsigned char joystick_button_8_state[1];
static unsigned char joystick_button_9_state[1];
static unsigned char joystick_button_10_state[1];
static unsigned char joystick_button_11_state[1];
static unsigned char joystick_button_12_state[1];
static unsigned char joystick_button_13_state[1];
static unsigned char joystick_button_14_state[1];
static unsigned char joystick_button_15_state[1];
static unsigned char joystick_button_16_state[0x101];
static unsigned char pad_axis_1_positive_pressed[1];
static unsigned char pad_axis_1_negative_pressed[1];
static unsigned char pad_axis_2_positive_pressed[1];
static unsigned char pad_axis_2_negative_pressed[1];
static unsigned char pad_axis_3_positive_pressed[1];
static unsigned char pad_axis_3_negative_pressed[1];
static unsigned char pad_axis_4_positive_pressed[1];
static unsigned char pad_axis_4_negative_pressed[1];
static unsigned char pad_axis_5_positive_pressed[1];
static unsigned char pad_axis_5_negative_pressed[1];
static unsigned char pad_axis_6_positive_pressed[1];
static unsigned char pad_axis_6_negative_pressed[1];
static unsigned char pad_axis_7_positive_pressed[1];
static unsigned char pad_axis_7_negative_pressed[1];
static unsigned char pad_button_1_pressed[1];
static unsigned char pad_button_2_pressed[1];
static unsigned char pad_button_3_pressed[1];
static unsigned char pad_button_4_pressed[1];
static unsigned char pad_button_5_pressed[1];
static unsigned char pad_button_6_pressed[1];
static unsigned char pad_button_7_pressed[1];
static unsigned char pad_button_8_pressed[1];
static unsigned char pad_button_9_pressed[1];
static unsigned char pad_button_10_pressed[1];
static unsigned char pad_button_11_pressed[1];
static unsigned char pad_button_12_pressed[1];
static unsigned char pad_button_13_pressed[1];
static unsigned char pad_button_14_pressed[1];
static unsigned char pad_button_15_pressed[1];
static unsigned char pad_button_16_pressed[0x61];
static unsigned char pad_pov_right_pressed[1];
static unsigned char pad_pov_down_pressed[1];
static unsigned char pad_pov_left_pressed[0x7d];
static unsigned int joystick_axis_2_state[1];
static unsigned int joystick_axis_3_state[1];
static unsigned int joystick_axis_4_state[1];
static unsigned int joystick_axis_5_state[1];
static unsigned int joystick_axis_6_state[1];
static unsigned int joystick_axis_7_state[1];
static unsigned int joystick_pov_hat_value[0x4];
static unsigned int joystick_z_axis_positive_triggered[0x10];
static unsigned int joystick_button_3_triggered[0x10];
static unsigned int joystick_button_4_triggered[0x10];
static unsigned int joystick_button_5_triggered[0x10];
static unsigned int joystick_button_6_triggered[0x10];
static unsigned int joystick_button_7_triggered[0x10];
static unsigned int joystick_button_8_triggered[0x10];
static unsigned int joystick_button_9_triggered[0x10];
static unsigned int joystick_button_10_triggered[0x10];
static unsigned int joystick_button_11_triggered[0x10];
static unsigned int joystick_button_12_triggered[0x10];
static unsigned int joystick_button_13_triggered[0x10];
static unsigned int joystick_button_14_triggered[0x10];
static unsigned int joystick_button_15_triggered[0x10];
static unsigned int joystick_button_16_triggered[0x30];
static void *force_feedback_effect_handles2[4];
static unsigned char g_EffectBuffer1[0x190];
static unsigned int g_EffectBuffer2[0x64];
static unsigned int g_EffectScaleFactor = 0x4b;
static unsigned char g_JoystickButtonState[1];
static unsigned char g_JoystickDataFormat = 0x18;
static unsigned char g_JoystickStateBuffer[1];
static unsigned int g_JoystickStateFlags[0x10];
static unsigned char g_KeyboardDataFormat = 0x18;
unsigned short g_KeyboardState[1];
static unsigned char g_MouseDataFormat = 0x18;
static unsigned int g_MouseMaxX = 0x7f;
static unsigned int g_MouseMaxY = 0x7f;
static unsigned int g_MouseMinX = 0xffffff80;
static unsigned int g_MouseMinY = 0xffffff80;
static unsigned int g_MouseX;
static unsigned int g_MouseY[1];
unsigned int g_PlayerDeviceMap1[1];
static unsigned int g_bDevicesAcquired;
static unsigned int g_pDirectInput;
static unsigned int g_pEffectStructs[0x3];
static unsigned int g_pEffectStructs2[0x4];
static unsigned int g_pJoystickDevices[0x4];
static unsigned int g_pKeyboardDevice;
static unsigned int g_pMouseDevice;
static unsigned int g_uiNumJoysticks;
unsigned int hDlgInput;
static int joystick_axis_1_negative_triggered[4];
static int joystick_axis_1_positive_triggered[4];
static int joystick_axis_2_negative_triggered[4];
static int joystick_axis_2_positive_triggered[4];
static int joystick_axis_3_negative_triggered[4];
static int joystick_axis_3_positive_triggered[4];
static int joystick_axis_4_negative_triggered[4];
static int joystick_axis_4_positive_triggered[4];
static int joystick_axis_5_negative_triggered[4];
static int joystick_axis_5_positive_triggered[4];
static int joystick_axis_6_negative_triggered[4];
static int joystick_axis_6_positive_triggered[4];
static int joystick_axis_7_negative_triggered[4];
static int joystick_axis_7_positive_triggered[4];
static int joystick_button_1_triggered[4];
static int joystick_button_2_triggered[4];
unsigned int point_device_enabled;
static unsigned short pad_axis_1_value[1];
static unsigned short pad_axis_2_value[1];
static unsigned short pad_axis_3_value[1];
static unsigned short pad_axis_4_value[1];
static unsigned short pad_axis_5_value[1];
static unsigned short pad_axis_6_value[1];
static unsigned short pad_axis_7_value[1];

int diAcquireAllDevices()
{
  if ( g_pJoystickDevices[0] )
    (*(void (__stdcall **)(int))(*(uint32_t *)g_pJoystickDevices[0] + 28))(g_pJoystickDevices[0]);
  if ( g_pJoystickDevices[1] )
    (*(void (__stdcall **)(int))(*(uint32_t *)g_pJoystickDevices[1] + 28))(g_pJoystickDevices[1]);
  if ( g_pJoystickDevices[2] )
    (*(void (__stdcall **)(int))(*(uint32_t *)g_pJoystickDevices[2] + 28))(g_pJoystickDevices[2]);
  if ( g_pJoystickDevices[3] )
    (*(void (__stdcall **)(int))(*(uint32_t *)g_pJoystickDevices[3] + 28))(g_pJoystickDevices[3]);
  if ( g_pMouseDevice )
    (*(void (__stdcall **)(int))(*(uint32_t *)g_pMouseDevice + 28))(g_pMouseDevice);
  if ( g_pKeyboardDevice )
    (*(void (__stdcall **)(int))(*(uint32_t *)g_pKeyboardDevice + 28))(g_pKeyboardDevice);
  g_bDevicesAcquired = 1;
  return 1;
}

int diUnacquireAllDevices()
{
  if ( g_pMouseDevice && point_device_enabled )
    (*(void (__stdcall **)(int))(*(uint32_t *)g_pMouseDevice + 32))(g_pMouseDevice);
  if ( g_pKeyboardDevice )
    (*(void (__stdcall **)(int))(*(uint32_t *)g_pKeyboardDevice + 32))(g_pKeyboardDevice);
  if ( g_pJoystickDevices[0] )
    (*(void (__stdcall **)(int))(*(uint32_t *)g_pJoystickDevices[0] + 32))(g_pJoystickDevices[0]);
  if ( g_pJoystickDevices[1] )
    (*(void (__stdcall **)(int))(*(uint32_t *)g_pJoystickDevices[1] + 32))(g_pJoystickDevices[1]);
  if ( g_pJoystickDevices[2] )
    (*(void (__stdcall **)(int))(*(uint32_t *)g_pJoystickDevices[2] + 32))(g_pJoystickDevices[2]);
  if ( g_pJoystickDevices[3] )
    (*(void (__stdcall **)(int))(*(uint32_t *)g_pJoystickDevices[3] + 32))(g_pJoystickDevices[3]);
  g_bDevicesAcquired = 0;
  return 1;
}

int diAcquireMouseDevice()
{
  if ( g_pMouseDevice && point_device_enabled )
    (*(void (__stdcall **)(int))(*(uint32_t *)g_pMouseDevice + 28))(g_pMouseDevice);
  return 1;
}

static int diGetMouseState()
{
  int device;
  int result;
  uint32_t state[3];
  uint8_t buttons[8];

  if ( !point_device_enabled )
    return 0;
  device = g_pMouseDevice;
  g_MouseX = 0;
  g_MouseY[0] = 0;
  if ( g_pMouseDevice && g_bDevicesAcquired == 1 )
  {
    while ( 1 )
    {
      result = (*(int (__stdcall **)(int, int, uint32_t *))(*(uint32_t *)device + 36))(device, 16, state);
      if ( result != DIERR_INPUTLOST )
        break;
      if ( (*(int (__stdcall **)(int))(*(uint32_t *)g_pMouseDevice + 28))(g_pMouseDevice) < 0 )
        return 0;
      device = g_pMouseDevice;
    }
    if ( result < 0 )
      return 0;
    g_MouseX = 3 * state[0];
    g_MouseY[0] = 3 * state[1];
    g_MouseButtons = (buttons[3] | ((buttons[2] | ((unsigned int)(buttons[1] | (buttons[0] >> 1)) >> 1)) >> 1)) >> 4;
  }
  return 1;
}

static int __stdcall diEnumEffectsCallback(uint32_t *effectInfo, uint32_t *out)
{
  if ( out )
  {
    *out = effectInfo[1];
    out[1] = effectInfo[2];
    out[2] = effectInfo[3];
    out[3] = effectInfo[4];
  }
  return 0;
}

static unsigned int diCreateEffectHelper(int device, uint32_t *effect)
{
  int flags;
  uint8_t guid[16];

  if ( *effect )
    (*(void (__stdcall **)(uint32_t))(*(uint32_t *)*effect + 8))(*effect);
  flags = effect[1];
  *effect = 0;
  if ( (*(int (__stdcall **)(int, int (__stdcall *)(uint32_t *, uint32_t *), uint8_t *, int))(*(uint32_t *)device + 76))(
         device,
         diEnumEffectsCallback,
         guid,
         flags) >= 0 )
    return (*(int (__stdcall **)(int, uint8_t *, uint32_t *, uint32_t *, uint32_t))(*(uint32_t *)device + 72))(device, guid, effect + 2, effect, 0) >= 0
         ? 0
         : 0x80004005;
  else
    return 0x80004005;
}

static unsigned int diSetupConstantForceEffect(int effect, int device)
{
  uint32_t *effectData;
  int deviceCopy;
  uint32_t envelope[2];
  uint32_t typeParams[2];

  effectData = (uint32_t *)effect;
  if ( !effect )
    return E_FAIL;
  deviceCopy = device;
  if ( !device )
    return E_FAIL;
  *(uint32_t *)(effect + 40) = envelope;
  effectData[5] = 0;
  effectData[8] = 0;
  effectData[11] = typeParams;
  envelope[0] = 0;
  typeParams[0] = 0;
  typeParams[1] = 0;
  effectData[12] = 0;
  effectData[7] = -1;
  effect = 10000;
  envelope[1] = 4;
  effectData[3] = 34;
  effectData[4] = 20000;
  effectData[9] = 2;
  effectData[13] = 4;
  effectData[14] = &effect;
  effectData[1] = 1;
  return (diCreateEffectHelper(deviceCopy, effectData) & 0x80000000) == 0 ? 0 : 0x80004005;
}

static unsigned int diSetupPeriodicForceEffect(uint32_t *effect, int device)
{
  int tmp1;
  int tmp2;
  uint32_t periodicParams[4];

  if ( !effect || !device )
    return E_FAIL;
  effect[5] = 0;
  effect[8] = 0;
  effect[17] = 0;
  effect[18] = 0;
  effect[19] = 0;
  periodicParams[1] = 0;
  periodicParams[2] = 0;
  tmp1 = 0;
  tmp2 = 0;
  effect[10] = &tmp1;
  effect[12] = effect + 16;
  effect[7] = -1;
  effect[11] = &tmp2;
  effect[20] = 1000000;
  periodicParams[0] = 10000;
  periodicParams[3] = 100000;
  effect[3] = 18;
  effect[4] = 20000;
  effect[9] = 1;
  effect[13] = 16;
  effect[14] = periodicParams;
  effect[1] = 3;
  return (diCreateEffectHelper(device, effect) & 0x80000000) == 0 ? 0 : E_FAIL;
}

static int diSetConstantForceMagnitude(int effect, int magnitude)
{
  uint32_t *effectData;
  int effectHandle;
  uint32_t params[14];

  effectData = (uint32_t *)effect;
  if ( !effect )
    return E_INVALIDARG;
  effectHandle = *(uint32_t *)effect;
  if ( !*(uint32_t *)effect )
    return E_INVALIDARG;
  memset(params, 0, sizeof(params));
  effect = 10000 * magnitude / 255;
  params[0] = 56;
  params[11] = 4;
  params[12] = &effect;
  (*(void (__stdcall **)(int, uint32_t *, int))(*(uint32_t *)effectHandle + 24))(effectHandle, params, 256);
  return (*(int (__stdcall **)(uint32_t, int, uint32_t))(*(uint32_t *)*effectData + 28))(*effectData, 1, 0);
}

static int diSetPeriodicForceMagnitude(uint32_t *effect, int magnitude)
{
  int effectHandle;
  int scaledMagnitude;
  uint32_t params[14];

  if ( !effect )
    return E_INVALIDARG;
  effectHandle = *effect;
  if ( !*effect )
    return E_INVALIDARG;
  memset(params, 0, sizeof(params));
  scaledMagnitude = 10000 * magnitude / 255;
  params[0] = 56;
  params[11] = 16;
  params[12] = &scaledMagnitude;
  (*(void (__stdcall **)(int, uint32_t *, int))(*(uint32_t *)effectHandle + 24))(effectHandle, params, 256);
  return (*(int (__stdcall **)(uint32_t, int, uint32_t))(*(uint32_t *)*effect + 28))(*effect, 1, 0);
}

static uint32_t * diInitEffectStruct(uint32_t *effect)
{
  memset(effect + 2, 0, 0x38u);
  effect[2] = 56;
  effect[6] = 7500;
  effect[16] = 0;
  effect[17] = 0;
  effect[18] = 0;
  effect[19] = 0;
  effect[20] = 0;
  effect[16] = 20;
  *effect = 0;
  return effect + 16;
}

int diSetEffectMagnitude(int effectSet, int magnitude, int unused, int port)
{
  int effectType;

  if ( effectSet )
  {
    effectType = g_EffectType1[port];
    if ( effectType == 1 )
    {
      return diSetConstantForceMagnitude(g_MouseY[g_PlayerDeviceMap1[port]], magnitude);
    }
    else if ( effectType == 2 )
    {
      return diSetPeriodicForceMagnitude((uint32_t *)g_MouseY[g_PlayerDeviceMap1[port]], magnitude);
    }
  }
  else
  {
    effectType = g_EffectType2[port];
    if ( effectType == 1 )
    {
      return diSetConstantForceMagnitude(force_feedback_effect_handles2[g_PlayerDeviceMap1[port]], magnitude);
    }
    else if ( effectType == 2 )
    {
      return diSetPeriodicForceMagnitude((uint32_t *)force_feedback_effect_handles2[g_PlayerDeviceMap1[port]], magnitude);
    }
  }
  return effectType;
}

static int diEnumDevicesCallback(int deviceInstance, uint32_t *dinput, int flags)
{
  int tmp;
  int guidTmp;
  int i;
  int *devicePtr;
  int vtable;
  int hr;
  int device;
  bool failed;
  int idx1;
  int deviceY;
  int idx2;
  int deviceZ;
  int idx3;
  int deviceRx;
  int idx4;
  int deviceRy;
  int idx5;
  int deviceRz;
  int idx6;
  int deviceS0;
  int idx7;
  int deviceS1;
  int idx8;
  int deadzoneDevice;
  int deadzoneY;
  int deadzoneZ;
  int deadzoneRx;
  int deadzoneRy;
  int deadzoneRz;
  int deadzoneS0;
  int deadzoneS1;
  int ffDevice;
  int idx;
  int *effectBuffer2;
  int effectType1;
  int effectType2;
  char *effectBuffer1;
  uint32_t deviceGuid[4];
  int propSize;
  int propHeaderSize;
  int propObj;
  int propHow;
  int propData;
  uint32_t ffLoad[5];
  int rangeSize;
  uint32_t rangeHeader[2];
  int rangeObj;
  int rangeMin;
  int rangeMax;
  int playerIndex;

  guidTmp = *(uint32_t *)(deviceInstance + 8);
  deviceGuid[0] = *(uint32_t *)(deviceInstance + 4);
  deviceGuid[2] = *(uint32_t *)(deviceInstance + 12);
  deviceGuid[1] = guidTmp;
  deviceGuid[3] = *(uint32_t *)(deviceInstance + 16);
  playerIndex = -1;
  if ( (unsigned int)g_uiNumJoysticks <= 3 )
  {
    for ( i = 0; i < 4; ++i )
    {
      if ( g_PlayerDeviceMap1[i] == g_uiNumJoysticks + 1 )
        playerIndex = i;
    }
    if ( !(*(int (__stdcall **)(uint32_t *, uint32_t *, GUID *, int, uint32_t))(*dinput + 36))(
            dinput,
            deviceGuid,
            &GUID_Joystick,
            4 * g_uiNumJoysticks + 5207916,
            0) )
    {
      if ( (*(int (__stdcall **)(int, char *))(*(uint32_t *)g_pJoystickDevices[g_uiNumJoysticks] + 44))(
             g_pJoystickDevices[g_uiNumJoysticks],
             &g_JoystickDataFormat)
        || ((devicePtr = (int *)g_pJoystickDevices[g_uiNumJoysticks], vtable = *devicePtr, playerIndex == -1)
          ? (hr = (*(int (__stdcall **)(int *, int, int))(vtable + 52))(devicePtr, hDlgInput, 6))
          : (hr = (*(int (__stdcall **)(int *, int, int))(vtable + 52))(devicePtr, hDlgInput, 5)),
            hr) )
      {
        (*(void (__stdcall **)(int))(*(uint32_t *)g_pJoystickDevices[g_uiNumJoysticks] + 8))(g_pJoystickDevices[g_uiNumJoysticks]);
        return 1;
      }
      device = g_pJoystickDevices[g_uiNumJoysticks];
      rangeSize = 24;
      rangeHeader[0] = 16;
      rangeHeader[1] = 0;
      rangeObj = 1;
      rangeMin = -128;
      rangeMax = 127;
      failed = (*(int (__stdcall **)(int, int, int *, int))(*(uint32_t *)device + 24))(device, 4, &rangeSize, tmp) < 0;
      idx1 = g_uiNumJoysticks;
      if ( failed )
      {
        g_JoystickStateFlags[g_uiNumJoysticks] = 1;
        joystick_axis_1_positive_triggered[idx1] = 1;
      }
      deviceY = g_pJoystickDevices[idx1];
      rangeObj = 4;
      failed = (*(int (__stdcall **)(int, int, uint32_t *))(*(uint32_t *)deviceY + 24))(deviceY, 4, rangeHeader) < 0;
      idx2 = g_uiNumJoysticks;
      if ( failed )
      {
        joystick_axis_1_negative_triggered[g_uiNumJoysticks] = 1;
        joystick_axis_2_positive_triggered[idx2] = 1;
      }
      deviceZ = g_pJoystickDevices[idx2];
      rangeObj = 8;
      failed = (*(int (__stdcall **)(int, int, uint32_t *))(*(uint32_t *)deviceZ + 24))(deviceZ, 4, rangeHeader) < 0;
      idx3 = g_uiNumJoysticks;
      if ( failed )
      {
        joystick_z_axis_positive_triggered[g_uiNumJoysticks] = 1;
        joystick_axis_2_negative_triggered[idx3] = 1;
      }
      deviceRx = g_pJoystickDevices[idx3];
      rangeObj = 12;
      failed = (*(int (__stdcall **)(int, int, uint32_t *))(*(uint32_t *)deviceRx + 24))(deviceRx, 4, rangeHeader) < 0;
      idx4 = g_uiNumJoysticks;
      if ( failed )
      {
        joystick_axis_3_positive_triggered[g_uiNumJoysticks] = 1;
        joystick_axis_3_negative_triggered[idx4] = 1;
      }
      deviceRy = g_pJoystickDevices[idx4];
      rangeObj = 16;
      failed = (*(int (__stdcall **)(int, int, uint32_t *))(*(uint32_t *)deviceRy + 24))(deviceRy, 4, rangeHeader) < 0;
      idx5 = g_uiNumJoysticks;
      if ( failed )
      {
        joystick_axis_4_positive_triggered[g_uiNumJoysticks] = 1;
        joystick_axis_4_negative_triggered[idx5] = 1;
      }
      deviceRz = g_pJoystickDevices[idx5];
      rangeObj = 20;
      failed = (*(int (__stdcall **)(int, int, uint32_t *))(*(uint32_t *)deviceRz + 24))(deviceRz, 4, rangeHeader) < 0;
      idx6 = g_uiNumJoysticks;
      if ( failed )
      {
        joystick_axis_5_positive_triggered[g_uiNumJoysticks] = 1;
        joystick_axis_5_negative_triggered[idx6] = 1;
      }
      deviceS0 = g_pJoystickDevices[idx6];
      rangeObj = 24;
      failed = (*(int (__stdcall **)(int, int, uint32_t *))(*(uint32_t *)deviceS0 + 24))(deviceS0, 4, rangeHeader) < 0;
      idx7 = g_uiNumJoysticks;
      if ( failed )
      {
        joystick_axis_6_positive_triggered[g_uiNumJoysticks] = 1;
        joystick_axis_6_negative_triggered[idx7] = 1;
      }
      deviceS1 = g_pJoystickDevices[idx7];
      rangeObj = 28;
      failed = (*(int (__stdcall **)(int, int, uint32_t *))(*(uint32_t *)deviceS1 + 24))(deviceS1, 4, rangeHeader) < 0;
      idx8 = g_uiNumJoysticks;
      if ( failed )
      {
        joystick_axis_7_positive_triggered[g_uiNumJoysticks] = 1;
        joystick_axis_7_negative_triggered[idx8] = 1;
      }
      deadzoneDevice = g_pJoystickDevices[idx8];
      propHeaderSize = 20;
      propObj = 16;
      propData = 1;
      ffLoad[0] = 2500;
      propHow = 0;
      (*(void (__stdcall **)(int, int))(*(uint32_t *)deadzoneDevice + 24))(deadzoneDevice, 5);
      deadzoneY = g_pJoystickDevices[g_uiNumJoysticks];
      propObj = 4;
      (*(void (__stdcall **)(int, int, int *))(*(uint32_t *)deadzoneY + 24))(deadzoneY, 5, &propSize);
      deadzoneZ = g_pJoystickDevices[g_uiNumJoysticks];
      propObj = 8;
      (*(void (__stdcall **)(int, int, int *))(*(uint32_t *)deadzoneZ + 24))(deadzoneZ, 5, &propSize);
      deadzoneRx = g_pJoystickDevices[g_uiNumJoysticks];
      propObj = 12;
      (*(void (__stdcall **)(int, int, int *))(*(uint32_t *)deadzoneRx + 24))(deadzoneRx, 5, &propSize);
      deadzoneRy = g_pJoystickDevices[g_uiNumJoysticks];
      propObj = 16;
      (*(void (__stdcall **)(int, int, int *))(*(uint32_t *)deadzoneRy + 24))(deadzoneRy, 5, &propSize);
      deadzoneRz = g_pJoystickDevices[g_uiNumJoysticks];
      propObj = 20;
      (*(void (__stdcall **)(int, int, int *))(*(uint32_t *)deadzoneRz + 24))(deadzoneRz, 5, &propSize);
      deadzoneS0 = g_pJoystickDevices[g_uiNumJoysticks];
      propObj = 24;
      (*(void (__stdcall **)(int, int, int *))(*(uint32_t *)deadzoneS0 + 24))(deadzoneS0, 5, &propSize);
      deadzoneS1 = g_pJoystickDevices[g_uiNumJoysticks];
      propObj = 28;
      (*(void (__stdcall **)(int, int, int *))(*(uint32_t *)deadzoneS1 + 24))(deadzoneS1, 5, &propSize);
      propSize = 20;
      propHeaderSize = 16;
      propHow = 0;
      propData = 0;
      propObj = 0;
      (*(void (__stdcall **)(int, int, int *))(*(uint32_t *)g_pJoystickDevices[g_uiNumJoysticks] + 24))(
        g_pJoystickDevices[g_uiNumJoysticks],
        2,
        &propSize);
      if ( playerIndex != -1 )
      {
        ffDevice = g_pJoystickDevices[g_uiNumJoysticks];
        ffLoad[0] = 20;
        ffLoad[1] = 16;
        memset(&ffLoad[2], 0, 12);
        (*(void (__stdcall **)(int, int, uint32_t *))(*(uint32_t *)ffDevice + 24))(ffDevice, 9, ffLoad);
        idx = g_uiNumJoysticks;
        effectBuffer2 = &g_EffectBuffer2[25 * g_uiNumJoysticks];
        effectBuffer1 = &g_EffectBuffer1[100 * g_uiNumJoysticks];
        g_pEffectStructs[g_uiNumJoysticks] = (int)effectBuffer1;
        g_pEffectStructs2[idx] = (int)effectBuffer2;
        diInitEffectStruct(effectBuffer1);
        diInitEffectStruct((uint32_t *)g_pEffectStructs2[g_uiNumJoysticks]);
        *(uint32_t *)(g_pEffectStructs[g_uiNumJoysticks] + 24) = 100 * g_EffectScaleFactor;
        *(uint32_t *)(g_pEffectStructs2[g_uiNumJoysticks] + 24) = 100 * g_EffectScaleFactor;
        effectType1 = g_EffectType1[playerIndex];
        if ( effectType1 == 1 )
        {
          diSetupConstantForceEffect(g_pEffectStructs[g_uiNumJoysticks], g_pJoystickDevices[g_uiNumJoysticks]);
        }
        else if ( effectType1 == 2 )
        {
          diSetupPeriodicForceEffect((uint32_t *)g_pEffectStructs[g_uiNumJoysticks], g_pJoystickDevices[g_uiNumJoysticks]);
        }
        effectType2 = g_EffectType2[playerIndex];
        if ( effectType2 == 1 )
        {
          diSetupConstantForceEffect(g_pEffectStructs2[g_uiNumJoysticks], g_pJoystickDevices[g_uiNumJoysticks]);
        }
        else if ( effectType2 == 2 )
        {
          diSetupPeriodicForceEffect(
            (uint32_t *)g_pEffectStructs2[g_uiNumJoysticks],
            g_pJoystickDevices[g_uiNumJoysticks]);
        }
      }
      ++g_uiNumJoysticks;
    }
  }
  return 1;
}

int diInitDirectInput()
{
  HRESULT hr;
  CHAR Text[256];

  hr = DirectInputCreateA(hInst_For_DInput, 0x700, (int)&g_pDirectInput, 0);
  if ( hr >= 0 )
  {
    if ( (*(int (__stdcall **)(int, GUID *, int *, uint32_t))(*(uint32_t *)g_pDirectInput + 12))(
           g_pDirectInput,
           &GUID_Keyboard,
           &g_pKeyboardDevice,
           0) < 0 )
      return 0;
    if ( (*(int (__stdcall **)(int, char *))(*(uint32_t *)g_pKeyboardDevice + 44))(
           g_pKeyboardDevice,
           &g_KeyboardDataFormat) < 0 )
      return 0;
    (*(void (__stdcall **)(int, int, int))(*(uint32_t *)g_pKeyboardDevice + 52))(g_pKeyboardDevice, hDlgInput, 6);
    if ( !point_device_enabled || g_bDisableMouse )
      goto LABEL_25;
    if ( (*(int (__stdcall **)(int, GUID *, int *, uint32_t))(*(uint32_t *)g_pDirectInput + 12))(
           g_pDirectInput,
           &GUID_Mouse,
           &g_pMouseDevice,
           0) < 0 )
      return 0;
    if ( (*(int (__stdcall **)(int, char *))(*(uint32_t *)g_pMouseDevice + 44))(g_pMouseDevice, &g_MouseDataFormat) < 0 )
      return 0;
    if ( (*(int (__stdcall **)(int, int, int))(*(uint32_t *)g_pMouseDevice + 52))(g_pMouseDevice, hDlgInput, 5) >= 0 )
    {
LABEL_25:
      g_pJoystickDevices[0] = 0;
      g_pJoystickDevices[1] = 0;
      g_pJoystickDevices[2] = 0;
      g_pJoystickDevices[3] = 0;
      (*(void (__stdcall **)(int, int, int (*)(int, uint32_t *, int), int, int))(*(uint32_t *)g_pDirectInput + 16))(
        g_pDirectInput,
        4,
        diEnumDevicesCallback,
        g_pDirectInput,
        1);
      if ( (g_PlayerDeviceMap1[0] && g_PlayerDeviceMap1[0] <= 4u
         || g_PlayerDeviceMap2 && (unsigned int)g_PlayerDeviceMap2 <= 4
         || g_PlayerDeviceMap3 && (unsigned int)g_PlayerDeviceMap3 <= 4
         || g_PlayerDeviceMap4[0] && g_PlayerDeviceMap4[0] <= 4u)
        && (*(int (__stdcall **)(int, int, int (*)(int, uint32_t *, int), int, int))(*(uint32_t *)g_pDirectInput + 16))(
             g_pDirectInput,
             4,
             diEnumDevicesCallback,
             g_pDirectInput,
             257) < 0 )
      {
        printf(" * No force-feedback joysticks available. \n");
      }
      diAcquireAllDevices();
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    sprintf(Text, "Error initializing DirectInput\n");
    MessageBoxA(nullptr, Text, "Init Error", 0x10u);
    if ( hr > DIERR_OLDDIRECTINPUTVERSION )
    {
      if ( hr != DIERR_BETADIRECTINPUTVERSION )
      {
LABEL_10:
        sprintf(Text, "UNKNOWN %X\n", hr);
        MessageBoxA(nullptr, Text, "Init", 0x10u);
        return 0;
      }
      sprintf(Text, "Beta %X\n", DIERR_BETADIRECTINPUTVERSION);
    }
    else
    {
      if ( hr == DIERR_OLDDIRECTINPUTVERSION )
      {
        sprintf(Text, "OLDDIRECTINPUTVERSION %X\n", DIERR_OLDDIRECTINPUTVERSION);
        MessageBoxA(nullptr, Text, "Init", 0x10u);
        return 0;
      }
      if ( hr != DIERR_OUTOFMEMORY )
      {
        if ( hr == DIERR_INVALIDPARAM )
        {
          sprintf(Text, "Invalid %X\n", DIERR_INVALIDPARAM);
          MessageBoxA(nullptr, Text, "Init", 0x10u);
          return 0;
        }
        goto LABEL_10;
      }
      sprintf(Text, "OUTOFMEMORY %X\n", DIERR_OUTOFMEMORY);
    }
    MessageBoxA(nullptr, Text, "Init", 0x10u);
    return 0;
  }
}

int diUpdateJoystickStates()
{
  char *buffer;
  int i;
  int result;
  int device;

  buffer = g_JoystickStateBuffer;
  for ( i = 0; ; ++i )
  {
    result = g_pJoystickDevices[i];
    if ( result )
      break;
LABEL_97:
    buffer += 80;
    if ( (int)buffer >= (int)g_EffectBuffer2 )
      return result;
  }
  (*(void (__stdcall **)(int))(*(uint32_t *)result + 100))(g_pJoystickDevices[i]);
  if ( (*(int (__stdcall **)(int, int, char *))(*(uint32_t *)g_pJoystickDevices[i] + 36))(g_pJoystickDevices[i], 80, buffer) != -2147024866 )
    goto LABEL_8;
  device = g_pJoystickDevices[i];
  if ( device )
    (*(void (__stdcall **)(int))(*(uint32_t *)device + 28))(g_pJoystickDevices[i]);
  result = (*(int (__stdcall **)(int, int, char *))(*(uint32_t *)g_pJoystickDevices[i] + 36))(
             g_pJoystickDevices[i],
             80,
             buffer);
  if ( result >= 0 )
  {
LABEL_8:
    if ( !g_JoystickStateFlags[i] && *(int *)buffer > 0 )
      g_JoystickStateFlags[i] = 1;
    if ( !joystick_axis_1_positive_triggered[i] && *(int *)buffer < 0 )
      joystick_axis_1_positive_triggered[i] = 1;
    if ( !joystick_axis_1_negative_triggered[i] && *((int *)buffer + 1) > 0 )
      joystick_axis_1_negative_triggered[i] = 1;
    if ( !joystick_axis_2_positive_triggered[i] && *((int *)buffer + 1) < 0 )
      joystick_axis_2_positive_triggered[i] = 1;
    if ( !joystick_z_axis_positive_triggered[i] && *((int *)buffer + 2) > 0 )
      joystick_z_axis_positive_triggered[i] = 1;
    if ( !joystick_axis_2_negative_triggered[i] && *((int *)buffer + 2) < 0 )
      joystick_axis_2_negative_triggered[i] = 1;
    if ( !joystick_axis_4_positive_triggered[i] && *((int *)buffer + 4) > 0 )
      joystick_axis_4_positive_triggered[i] = 1;
    if ( !joystick_axis_4_negative_triggered[i] && *((int *)buffer + 4) < 0 )
      joystick_axis_4_negative_triggered[i] = 1;
    if ( !joystick_axis_5_positive_triggered[i] && *((int *)buffer + 5) > 0 )
      joystick_axis_5_positive_triggered[i] = 1;
    if ( !joystick_axis_5_negative_triggered[i] && *((int *)buffer + 5) < 0 )
      joystick_axis_5_negative_triggered[i] = 1;
    if ( !joystick_axis_6_positive_triggered[i] && *((int *)buffer + 6) > 0 )
      joystick_axis_6_positive_triggered[i] = 1;
    if ( !joystick_axis_6_negative_triggered[i] && *((int *)buffer + 6) < 0 )
      joystick_axis_6_negative_triggered[i] = 1;
    if ( !joystick_axis_7_positive_triggered[i] && *((int *)buffer + 7) > 0 )
      joystick_axis_7_positive_triggered[i] = 1;
    if ( !joystick_axis_7_negative_triggered[i] && *((int *)buffer + 7) < 0 )
      joystick_axis_7_negative_triggered[i] = 1;
    if ( !joystick_button_1_triggered[i] && buffer[48] )
      joystick_button_1_triggered[i] = 1;
    if ( !joystick_button_2_triggered[i] && buffer[49] )
      joystick_button_2_triggered[i] = 1;
    if ( !joystick_button_3_triggered[i] && buffer[50] )
      joystick_button_3_triggered[i] = 1;
    if ( !joystick_button_4_triggered[i] && buffer[51] )
      joystick_button_4_triggered[i] = 1;
    if ( !joystick_button_5_triggered[i] && buffer[52] )
      joystick_button_5_triggered[i] = 1;
    if ( !joystick_button_6_triggered[i] && buffer[53] )
      joystick_button_6_triggered[i] = 1;
    if ( !joystick_button_7_triggered[i] && buffer[54] )
      joystick_button_7_triggered[i] = 1;
    if ( !joystick_button_8_triggered[i] && buffer[55] )
      joystick_button_8_triggered[i] = 1;
    if ( !joystick_button_9_triggered[i] && buffer[56] )
      joystick_button_9_triggered[i] = 1;
    if ( !joystick_button_10_triggered[i] && buffer[57] )
      joystick_button_10_triggered[i] = 1;
    if ( !joystick_button_11_triggered[i] && buffer[58] )
      joystick_button_11_triggered[i] = 1;
    if ( !joystick_button_12_triggered[i] && buffer[59] )
      joystick_button_12_triggered[i] = 1;
    if ( !joystick_button_13_triggered[i] && buffer[60] )
      joystick_button_13_triggered[i] = 1;
    if ( !joystick_button_14_triggered[i] && buffer[61] )
      joystick_button_14_triggered[i] = 1;
    if ( !joystick_button_15_triggered[i] && buffer[62] )
      joystick_button_15_triggered[i] = 1;
    result = joystick_button_16_triggered[i];
    if ( !result )
    {
      result = (uint8_t)buffer[63];
      if ( (uint8_t)result )
        joystick_button_16_triggered[i] = 1;
    }
    goto LABEL_97;
  }
  return result;
}

int diUpdateDeviceStates()
{
  int result;
  int i;
  int port;
  int device;
  char *buttonState;
  int *stateBuffer;
  int dev;
  unsigned int povValue;
  char *buttonState2;
  char *buttonPtr;
  uint8_t keyState[256];

  memset(g_KeyboardState, 0, 0x40u);
  memset(keyState, 0, sizeof(keyState));
  result = g_pKeyboardDevice;
  if ( g_pKeyboardDevice )
  {
    if ( g_bDevicesAcquired == 1 )
    {
      result = (*(int (__stdcall **)(int, int, uint8_t *))(*(uint32_t *)g_pKeyboardDevice + 36))(
                 g_pKeyboardDevice,
                 256,
                 keyState);
      if ( result >= 0 )
      {
        for ( i = 0; i < 256; ++i )
        {
          if ( keyState[i] )
          {
            if ( !g_KeyboardStatePrev[i] )
              g_KeyboardStatePrev[i] = 1;
          }
          else
          {
            g_KeyboardStatePrev[i] = 0;
          }
        }
        g_KeyboardStatePrev[0] = 0;
        for ( port = 0; port < 4; ++port )
        {
          device = g_pJoystickDevices[port];
          result = 0;
          if ( device )
          {
            buttonState = &g_JoystickButtonState[32 * port];
            buttonPtr = buttonState;
            do
            {
              buttonState[result - 128] = 0;
              buttonState[result++] = 0;
            }
            while ( result < 32 );
            (*(void (__stdcall **)(int))(*(uint32_t *)device + 100))(device);
            stateBuffer = (int *)&g_JoystickStateBuffer[80 * port];
            result = (*(int (__stdcall **)(int, int, int *))(*(uint32_t *)g_pJoystickDevices[port] + 36))(
                       g_pJoystickDevices[port],
                       80,
                       stateBuffer);
            if ( result == -2147024866 )
            {
              dev = g_pJoystickDevices[port];
              if ( dev )
                (*(void (__stdcall **)(int))(*(uint32_t *)dev + 28))(g_pJoystickDevices[port]);
              result = (*(int (__stdcall **)(int, int, char *))(*(uint32_t *)g_pJoystickDevices[port] + 36))(
                         g_pJoystickDevices[port],
                         80,
                         &g_JoystickStateBuffer[80 * port]);
              if ( result < 0 )
                return result;
            }
            if ( !g_JoystickStateFlags[port] )
            {
              result = *stateBuffer;
              if ( *stateBuffer > 0 )
              {
                pad_axis_1_positive_pressed[32 * port] = 1;
                result = 16 * port;
                pad_axis_1_value[8 * port] = *(uint16_t *)stateBuffer;
              }
            }
            if ( !joystick_axis_1_positive_triggered[port] )
            {
              result = *stateBuffer;
              if ( *stateBuffer < 0 )
              {
                pad_axis_1_negative_pressed[32 * port] = 1;
                result = 16 * port;
                pad_axis_1_value[8 * port] = *(uint16_t *)stateBuffer;
              }
            }
            if ( !joystick_axis_1_negative_triggered[port] )
            {
              result = joystick_axis_2_state[20 * port];
              if ( result > 0 )
              {
                pad_axis_2_positive_pressed[32 * port] = 1;
                result = 16 * port;
                pad_axis_2_value[8 * port] = joystick_axis_2_state[20 * port];
              }
            }
            if ( !joystick_axis_2_positive_triggered[port] )
            {
              result = joystick_axis_2_state[20 * port];
              if ( result < 0 )
              {
                pad_axis_2_negative_pressed[32 * port] = 1;
                result = 16 * port;
                pad_axis_2_value[8 * port] = joystick_axis_2_state[20 * port];
              }
            }
            if ( !joystick_z_axis_positive_triggered[port] )
            {
              result = joystick_axis_3_state[20 * port];
              if ( result > 0 )
              {
                pad_axis_3_positive_pressed[32 * port] = 1;
                result = 16 * port;
                pad_axis_3_value[8 * port] = joystick_axis_3_state[20 * port];
              }
            }
            if ( !joystick_axis_2_negative_triggered[port] )
            {
              result = joystick_axis_3_state[20 * port];
              if ( result < 0 )
              {
                pad_axis_3_negative_pressed[32 * port] = 1;
                result = 16 * port;
                pad_axis_3_value[8 * port] = joystick_axis_3_state[20 * port];
              }
            }
            if ( !joystick_axis_4_positive_triggered[port] )
            {
              result = joystick_axis_4_state[20 * port];
              if ( result > 0 )
              {
                pad_axis_4_positive_pressed[32 * port] = 1;
                result = 16 * port;
                pad_axis_4_value[8 * port] = joystick_axis_4_state[20 * port];
              }
            }
            if ( !joystick_axis_4_negative_triggered[port] )
            {
              result = joystick_axis_4_state[20 * port];
              if ( result < 0 )
              {
                pad_axis_4_negative_pressed[32 * port] = 1;
                result = 16 * port;
                pad_axis_4_value[8 * port] = joystick_axis_4_state[20 * port];
              }
            }
            if ( !joystick_axis_5_positive_triggered[port] )
            {
              result = joystick_axis_5_state[20 * port];
              if ( result > 0 )
              {
                pad_axis_5_positive_pressed[32 * port] = 1;
                result = 16 * port;
                pad_axis_5_value[8 * port] = joystick_axis_5_state[20 * port];
              }
            }
            if ( !joystick_axis_5_negative_triggered[port] )
            {
              result = joystick_axis_5_state[20 * port];
              if ( result < 0 )
              {
                pad_axis_5_negative_pressed[32 * port] = 1;
                result = 16 * port;
                pad_axis_5_value[8 * port] = joystick_axis_5_state[20 * port];
              }
            }
            if ( !joystick_axis_6_positive_triggered[port] )
            {
              result = joystick_axis_6_state[20 * port];
              if ( result > 0 )
              {
                pad_axis_6_positive_pressed[32 * port] = 1;
                result = 16 * port;
                pad_axis_6_value[8 * port] = joystick_axis_6_state[20 * port];
              }
            }
            if ( !joystick_axis_6_negative_triggered[port] )
            {
              result = joystick_axis_6_state[20 * port];
              if ( result < 0 )
              {
                pad_axis_6_negative_pressed[32 * port] = 1;
                result = 16 * port;
                pad_axis_6_value[8 * port] = joystick_axis_6_state[20 * port];
              }
            }
            if ( !joystick_axis_7_positive_triggered[port] )
            {
              result = joystick_axis_7_state[20 * port];
              if ( result > 0 )
              {
                pad_axis_7_positive_pressed[32 * port] = 1;
                result = 16 * port;
                pad_axis_7_value[8 * port] = joystick_axis_7_state[20 * port];
              }
            }
            if ( !joystick_axis_7_negative_triggered[port] )
            {
              result = joystick_axis_7_state[20 * port];
              if ( result < 0 )
              {
                pad_axis_7_negative_pressed[32 * port] = 1;
                result = 16 * port;
                pad_axis_7_value[8 * port] = joystick_axis_7_state[20 * port];
              }
            }
            if ( !joystick_button_1_triggered[port] && joystick_button_1_state[80 * port] )
              pad_button_1_pressed[32 * port] = 1;
            if ( !joystick_button_2_triggered[port] && joystick_button_2_state[80 * port] )
            {
              result = 32 * port;
              pad_button_2_pressed[32 * port] = 1;
            }
            if ( !joystick_button_3_triggered[port] && joystick_button_3_state[80 * port] )
              pad_button_3_pressed[32 * port] = 1;
            if ( !joystick_button_4_triggered[port] && joystick_button_4_state[80 * port] )
              pad_button_4_pressed[32 * port] = 1;
            if ( !joystick_button_5_triggered[port] && joystick_button_5_state[80 * port] )
            {
              result = 32 * port;
              pad_button_5_pressed[32 * port] = 1;
            }
            if ( !joystick_button_6_triggered[port] && joystick_button_6_state[80 * port] )
              pad_button_6_pressed[32 * port] = 1;
            if ( !joystick_button_7_triggered[port] && joystick_button_7_state[80 * port] )
              pad_button_7_pressed[32 * port] = 1;
            if ( !joystick_button_8_triggered[port] && joystick_button_8_state[80 * port] )
            {
              result = 32 * port;
              pad_button_8_pressed[32 * port] = 1;
            }
            if ( !joystick_button_9_triggered[port] && joystick_button_9_state[80 * port] )
              pad_button_9_pressed[32 * port] = 1;
            if ( !joystick_button_10_triggered[port] && joystick_button_10_state[80 * port] )
              pad_button_10_pressed[32 * port] = 1;
            if ( !joystick_button_11_triggered[port] && joystick_button_11_state[80 * port] )
            {
              result = 32 * port;
              pad_button_11_pressed[32 * port] = 1;
            }
            if ( !joystick_button_12_triggered[port] && joystick_button_12_state[80 * port] )
              pad_button_12_pressed[32 * port] = 1;
            if ( !joystick_button_13_triggered[port] && joystick_button_13_state[80 * port] )
              pad_button_13_pressed[32 * port] = 1;
            if ( !joystick_button_14_triggered[port] && joystick_button_14_state[80 * port] )
            {
              result = 32 * port;
              pad_button_14_pressed[32 * port] = 1;
            }
            if ( !joystick_button_15_triggered[port] && joystick_button_15_state[80 * port] )
              pad_button_15_pressed[32 * port] = 1;
            if ( !joystick_button_16_triggered[port] && joystick_button_16_state[80 * port] )
              pad_button_16_pressed[32 * port] = 1;
            povValue = joystick_pov_hat_value[20 * port];
            if ( povValue > 0x4650 )
            {
              switch ( povValue )
              {
                case 0x57E4u:
                  result = (int)&g_KeyboardStatePrev[32 * port];
                  *(uint8_t *)(result + 386) = 1;
                  *(uint8_t *)(result + 387) = 1;
                  break;
                case 0x6978u:
                  pad_pov_left_pressed[32 * port] = 1;
                  break;
                case 0x7B0Cu:
                  result = 32 * port;
                  pad_pov_left_pressed[32 * port] = 1;
                  *buttonPtr = 1;
                  break;
              }
            }
            else if ( povValue == 18000 )
            {
              pad_pov_down_pressed[32 * port] = 1;
            }
            else if ( povValue > 0x2328 )
            {
              if ( povValue == 13500 )
              {
                result = (int)&g_KeyboardStatePrev[32 * port];
                *(uint8_t *)(result + 385) = 1;
                *(uint8_t *)(result + 386) = 1;
              }
            }
            else if ( povValue == 9000 )
            {
              result = 32 * port;
              pad_pov_right_pressed[32 * port] = 1;
            }
            else if ( povValue )
            {
              if ( povValue == 4500 )
              {
                result = (int)&g_JoystickButtonState[32 * port];
                *buttonPtr = 1;
                pad_pov_right_pressed[32 * port] = 1;
              }
            }
            else
            {
              *buttonPtr = 1;
            }
          }
          else
          {
            buttonState2 = &g_JoystickButtonState[32 * port];
            do
            {
              buttonState2[result - 128] = 0;
              buttonState2[result++] = 0;
            }
            while ( result < 32 );
          }
        }
      }
    }
  }
  return result;
}

int diGetClampedMouseX()
{
  int value;

  if ( !point_device_enabled )
    return 0;
  diGetMouseState();
  value = g_MouseX;
  if ( g_MouseX < g_MouseMinX )
  {
    value = g_MouseMinX;
    g_MouseX = g_MouseMinX;
  }
  if ( value > g_MouseMaxX )
  {
    g_MouseX = g_MouseMaxX;
    return g_MouseMaxX;
  }
  return value;
}

int diGetClampedMouseY()
{
  int value;

  if ( !point_device_enabled )
    return 0;
  value = g_MouseY[0];
  if ( g_MouseY[0] < g_MouseMinY )
  {
    value = g_MouseMinY;
    g_MouseY[0] = g_MouseMinY;
  }
  if ( value > g_MouseMaxY )
  {
    g_MouseY[0] = g_MouseMaxY;
    return g_MouseMaxY;
  }
  return value;
}

int diShutdownDirectInput()
{
  int *device;
  int hr;

  diUnacquireAllDevices();
  if ( g_pKeyboardDevice )
    (*(void (__stdcall **)(int))(*(uint32_t *)g_pKeyboardDevice + 8))(g_pKeyboardDevice);
  g_pKeyboardDevice = 0;
  device = g_pJoystickDevices;
  do
  {
    if ( *device )
      (*(void (__stdcall **)(int))(*(uint32_t *)*device + 8))(*device);
    *device++ = 0;
  }
  while ( (int)device < (int)&g_directinput_initialized );
  hr = (*(int (__stdcall **)(int))(*(uint32_t *)g_pDirectInput + 8))(g_pDirectInput);
  g_pDirectInput = 0;
  g_uiNumJoysticks = 0;
  return hr;
}

int diGetJoystickButtonState1(int port)
{
  return g_KeyboardState[LOWORD(GamepadAxis[2 * port])];
}

int diGetJoystickButtonState2(int port)
{
  return g_KeyboardState[HIWORD(GamepadAxis[2 * port])];
}

int diGetJoystickButtonState3(int port)
{
  return g_KeyboardState[LOWORD(GamepadAxis[2 * port + 1])];
}

int diGetJoystickButtonState4(int port)
{
  return g_KeyboardState[HIWORD(GamepadAxis[2 * port + 1])];
}
