#pragma once

/**
 * \file dinput_shim.h
 * \brief Shim for the legacy DirectInput 7 API (DirectInputCreateA).
 *
 * Declares the DirectInputCreateA shim that loads dinput.dll at runtime and
 * forwards to the real export, so the emulator links without dinput.lib.
 */

/* Function prototypes (previously generated in src/_gen) */

/**
 * \brief Loads dinput.dll and forwards to the real DirectInputCreateA.
 *
 * Lazily resolves the DirectInputCreateA export from dinput.dll on first call
 * (the legacy DirectInput 7 API is not provided as an import library by the
 * modern Windows SDK) and forwards the call unchanged.
 *
 * \param hinst     Instance handle of the calling application.
 * \param dwVersion DirectInput interface version requested (e.g. 0x0700).
 * \param ppDI      Receives the created IDirectInputA interface pointer.
 * \param punkOuter COM outer unknown (must be NULL for DirectInput).
 * \return S_OK on success, E_FAIL when dinput.dll cannot be loaded, otherwise the real function's HRESULT.
 */
HRESULT WINAPI DirectInputCreateA(HINSTANCE hinst, DWORD dwVersion, LPDIRECTINPUTA *ppDI, LPUNKNOWN punkOuter);
