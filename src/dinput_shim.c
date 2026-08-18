/*
 * dinput_shim.c — DirectInputCreateA shim.
 *
 * The decompiled ePSXe uses the legacy DirectInput 7 API (DirectInputCreateA),
 * which is exported by the system DLL dinput.dll but is NOT provided as an
 * import library by the modern Windows SDK.  This shim loads dinput.dll at
 * runtime and forwards the call, so the emulator links without dinput.lib.
 */
#include "pch.h"

HRESULT WINAPI DirectInputCreateA(HINSTANCE hinst, DWORD dwVersion,
                                  LPDIRECTINPUTA *ppDI, LPUNKNOWN punkOuter)
{
    static HRESULT(WINAPI *real)(HINSTANCE, DWORD, LPDIRECTINPUTA *, LPUNKNOWN) = NULL;
    if (!real)
    {
        HMODULE m = LoadLibraryA("dinput.dll");
        if (m)
            real = (HRESULT(WINAPI *)(HINSTANCE, DWORD, LPDIRECTINPUTA *, LPUNKNOWN))
                GetProcAddress(m, "DirectInputCreateA");
    }
    if (!real)
        return E_FAIL;
    return real(hinst, dwVersion, ppDI, punkOuter);
}
