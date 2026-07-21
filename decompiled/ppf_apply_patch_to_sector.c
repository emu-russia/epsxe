#include "pch.h"
void __cdecl ppf_apply_patch_to_sector(int a1, int a2)
{
  unsigned __int8 *v2; // eax
  unsigned __int8 *i; // eax

  if ( ppf_enabled == 1 )
  {
    v2 = *((unsigned __int8 **)ppf_sector_lists + a1);
    if ( v2 )
    {
      qmemcpy((void *)(a2 + *((unsigned __int16 *)v2 + 1)), &ppf_file_data[*((_DWORD *)v2 + 1)], *v2);
      for ( i = *((unsigned __int8 **)v2 + 2); i; i = *((unsigned __int8 **)i + 2) )
        qmemcpy((void *)(a2 + *((unsigned __int16 *)i + 1)), &ppf_file_data[*((_DWORD *)i + 1)], *i);
    }
  }
}
