#include "pch.h"
// attributes: thunk
HRESULT __stdcall DirectSoundCreate(LPCGUID pcGuidDevice, LPDIRECTSOUND *ppDS, LPUNKNOWN pUnkOuter)
{
  return __imp_DirectSoundCreate(pcGuidDevice, ppDS, pUnkOuter);
}
