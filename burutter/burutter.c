//.data:10005030 ; LPCSTR lpFileName
//.data:10005030 lpFileName      dd offset a2855         ; DATA XREF: JOY_init+14↑r
//.data:10005030                                         ; "\\\\.\\2855"
//.data:10005034 ; const char a2855[9]
//.data:10005034 a2855           db '\\.\2855',0         ; DATA XREF: .data:lpFileName↑o

//.data:100053A0 dword_100053A0  dd 5 dup(0)             ; DATA XREF: JOY_Close+2↑w
//.data:100053A0                                         ; JOY_Close+2F↑o ...
//.data:100053B4 ; HANDLE hDevice
//.data:100053B4 hDevice         dd 0                    ; DATA XREF: JOY_init+32↑w
//.data:100053B4                                         ; JOY_Close+28↑r ...
//.data:100053B8 ; DWORD BytesReturned
//.data:100053B8 BytesReturned   dd 0                    ; DATA XREF: JOY_Close+D↑o
//.data:100053B8                                         ; Big_Motor+11↑o ...
//.data:100053BC dword_100053BC  dd 0                    ; DATA XREF: JOY_init↑r
//.data:100053BC                                         ; JOY_init+37↑w


BOOL __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
  return 1;
}

int JOY_init()
{
  if ( !dword_100053BC )
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
  if ( a1 < 2 )
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
  if ( a1 > 1 )
    v2 = 1;
  dword_100053A0[0] = 2;
  dword_100053A0[4] = 2;
  dword_100053A0[2] = v2;
  dword_100053A0[1] = 1;
  dword_100053A0[3] = a2;
  return DeviceIoControl(hDevice, 4u, dword_100053A0, 0x14u, nullptr, 0, &BytesReturned, nullptr);
}