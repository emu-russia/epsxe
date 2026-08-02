#include "pch.h"

static LPSTR lpFileName = "\\\\.\\2855";
static HANDLE hDevice;
static DWORD BytesReturned;
static uint32_t dword_100053A0[5];
static int dword_100053BC;

int JOY_init()
{
    if (!dword_100053BC)
    {
        OutputDebugStringA(">>>BURUTTER epsxe Vibration Driver ver 1.0 \n\r");
        hDevice = CreateFileA(lpFileName, 0xC0000000, 3u, nullptr, 3u, 0x40000004u, nullptr);
        dword_100053BC = 1;
    }
    return 0;
}

int JOY_Close()
{
    dword_100053A0[0] = 2;
    dword_100053A0[4] = 0;
    dword_100053A0[2] = 0;
    dword_100053A0[1] = 0;
    dword_100053A0[3] = 0;
    DeviceIoControl(hDevice, 4u, dword_100053A0, 0x14u, nullptr, 0, &BytesReturned, nullptr);
    CloseHandle(hDevice);
    return 0;
}

BOOL __cdecl Big_Motor(unsigned int a1, int a2)
{
    int v2; // eax

    v2 = a1;
    if (a1 < 2)
        v2 = 0;
    dword_100053A0[0] = 2;
    dword_100053A0[4] = 2;
    dword_100053A0[2] = v2;
    dword_100053A0[1] = 1;
    dword_100053A0[3] = a2;
    return DeviceIoControl(hDevice, 4u, dword_100053A0, 0x14u, nullptr, 0, &BytesReturned, nullptr);
}

BOOL __cdecl Small_Motor(unsigned int a1, int a2)
{
    int v2; // eax

    v2 = a1;
    if (a1 > 1)
        v2 = 1;
    dword_100053A0[0] = 2;
    dword_100053A0[4] = 2;
    dword_100053A0[2] = v2;
    dword_100053A0[1] = 1;
    dword_100053A0[3] = a2;
    return DeviceIoControl(hDevice, 4u, dword_100053A0, 0x14u, nullptr, 0, &BytesReturned, nullptr);
}

int joy_init(void)
{
    return JOY_init();
}

int joy_issue_big_motor()
{
    int result; // eax

    if (dword_4FC45C)
        return Big_Motor();
    joy_init();
    result = dword_4FC45C;
    if (dword_4FC45C)
        return Big_Motor();
    return result;
}

int joy_issue_small_motor()
{
    int result; // eax

    if (dword_4FC45C)
        return Small_Motor();
    joy_init();
    result = dword_4FC45C;
    if (dword_4FC45C)
        return Small_Motor();
    return result;
}