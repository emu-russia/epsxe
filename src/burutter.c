#include "pch.h"

static LPSTR lpFileName = "\\\\.\\2855";
static HANDLE hDevice;
static DWORD BytesReturned;
static uint32_t vibration_cmd_buffer[5];
static int burutter_initialized;

int JOY_init()
{
    if (!burutter_initialized)
    {
        OutputDebugStringA(">>>BURUTTER epsxe Vibration Driver ver 1.0 \n\r");
        hDevice = CreateFileA(lpFileName, 0xC0000000, 3u, nullptr, 3u, 0x40000004u, nullptr);
        burutter_initialized = 1;
    }
    return 0;
}

int JOY_Close()
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

BOOL __cdecl Big_Motor(unsigned int a1, int a2)
{
    int v2; // eax

    v2 = a1;
    if (a1 < 2)
        v2 = 0;
    vibration_cmd_buffer[0] = 2;
    vibration_cmd_buffer[4] = 2;
    vibration_cmd_buffer[2] = v2;
    vibration_cmd_buffer[1] = 1;
    vibration_cmd_buffer[3] = a2;
    return DeviceIoControl(hDevice, 4u, vibration_cmd_buffer, 0x14u, nullptr, 0, &BytesReturned, nullptr);
}

BOOL __cdecl Small_Motor(unsigned int a1, int a2)
{
    int v2; // eax

    v2 = a1;
    if (a1 > 1)
        v2 = 1;
    vibration_cmd_buffer[0] = 2;
    vibration_cmd_buffer[4] = 2;
    vibration_cmd_buffer[2] = v2;
    vibration_cmd_buffer[1] = 1;
    vibration_cmd_buffer[3] = a2;
    return DeviceIoControl(hDevice, 4u, vibration_cmd_buffer, 0x14u, nullptr, 0, &BytesReturned, nullptr);
}

int joy_init(void)
{
    return JOY_init();
}

int joy_issue_big_motor()
{
    int result; // eax

    if (vibration_enabled)
        return Big_Motor(0xFFFF, 1);
    joy_init();
    result = vibration_enabled;
    if (vibration_enabled)
        return Big_Motor(0xFFFF, 1);
    return result;
}

int joy_issue_small_motor()
{
    int result; // eax

    if (vibration_enabled)
        return Small_Motor(1, 1);
    joy_init();
    result = vibration_enabled;
    if (vibration_enabled)
        return Small_Motor(1, 1);
    return result;
}

/* Decompiled globals (previously generated in src/_gen) */
unsigned int vibration_enabled;
