#include "pch.h"
void __cdecl sub_436F60(int a1, int a2)
{
  unsigned __int8 *v2; // eax
  unsigned __int8 *i; // eax

  if ( auto_ppf_load == 1 )
  {
    v2 = *((unsigned __int8 **)dword_4FFC24 + a1);
    if ( v2 )
    {
      qmemcpy((void *)(a2 + *((unsigned __int16 *)v2 + 1)), &dword_4FFC28[*((_DWORD *)v2 + 1)], *v2);
      for ( i = *((unsigned __int8 **)v2 + 2); i; i = *((unsigned __int8 **)i + 2) )
        qmemcpy((void *)(a2 + *((unsigned __int16 *)i + 1)), &dword_4FFC28[*((_DWORD *)i + 1)], *i);
    }
  }
}
