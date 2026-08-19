#include "pch.h"

/* Decompiled globals (previously generated in src/_gen) */
static unsigned int vibration_enabled;


static LPSTR lpFileName = "\\\\.\\2855";
static HANDLE hDevice;
static DWORD BytesReturned;
static uint32_t vibration_cmd_buffer[5];
static int burutter_initialized;

static int JOY_init()
{
    if (!burutter_initialized)
    {
        OutputDebugStringA(">>>BURUTTER epsxe Vibration Driver ver 1.0 \n\r");
        hDevice = CreateFileA(lpFileName, 0xC0000000, 3u, nullptr, 3u, 0x40000004u, nullptr);
        burutter_initialized = 1;
    }
    return 0;
}

static int JOY_Close()
{
    vibration_cmd_buffer[0] = 2;
    vibration_cmd_buffer[4] = 0;
    vibration_cmd_buffer[2] = 0;
    vibration_cmd_buffer[1] = 0;
    vibration_cmd_buffer[3] = 0;
    DeviceIoControl(hDevice, 4u, vibration_cmd_buffer, 0x14u, nullptr, 0, &BytesReturned, nullptr);
    CloseHandle(hDevice);
    return 0;
}

static BOOL Big_Motor(unsigned int strength, int duration)
{
    int clamped_strength;

    clamped_strength = strength;
    if (strength < 2)
        clamped_strength = 0;
    vibration_cmd_buffer[0] = 2;
    vibration_cmd_buffer[4] = 2;
    vibration_cmd_buffer[2] = clamped_strength;
    vibration_cmd_buffer[1] = 1;
    vibration_cmd_buffer[3] = duration;
    return DeviceIoControl(hDevice, 4u, vibration_cmd_buffer, 0x14u, nullptr, 0, &BytesReturned, nullptr);
}

static BOOL Small_Motor(unsigned int strength, int duration)
{
    int clamped_strength;

    clamped_strength = strength;
    if (strength > 1)
        clamped_strength = 1;
    vibration_cmd_buffer[0] = 2;
    vibration_cmd_buffer[4] = 2;
    vibration_cmd_buffer[2] = clamped_strength;
    vibration_cmd_buffer[1] = 1;
    vibration_cmd_buffer[3] = duration;
    return DeviceIoControl(hDevice, 4u, vibration_cmd_buffer, 0x14u, nullptr, 0, &BytesReturned, nullptr);
}

static int joy_init(void)
{
    return JOY_init();
}

int joy_issue_big_motor()
{
    if (vibration_enabled)
        return Big_Motor(0xFFFF, 1);
    joy_init();
    if (vibration_enabled)
        return Big_Motor(0xFFFF, 1);
    return 0;
}

int joy_issue_small_motor()
{
    if (vibration_enabled)
        return Small_Motor(1, 1);
    joy_init();
    if (vibration_enabled)
        return Small_Motor(1, 1);
    return 0;
}
