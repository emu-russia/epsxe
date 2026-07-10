#include "pch.h"
int __cdecl sub_43C450(unsigned int a1, unsigned __int8 *a2, unsigned int a3)
{
  unsigned __int8 *v3; // esi
  unsigned int v4; // ecx
  unsigned int v5; // edi
  unsigned int i; // ebx
  int v8; // eax
  unsigned int v9; // ebp
  int v10; // edx
  int v11; // ecx
  int v12; // edi
  int v13; // ecx
  int v14; // edi
  int v15; // ecx
  int v16; // edi
  int v17; // ecx
  int v18; // edi
  int v19; // ecx
  int v20; // edi
  int v21; // ecx
  int v22; // edi
  int v23; // ecx
  int v24; // edi
  int v25; // ecx
  int v26; // edi
  int v27; // ecx
  int v28; // edi
  int v29; // ecx
  int v30; // edi
  int v31; // ecx
  int v32; // edi
  int v33; // ecx
  int v34; // edi
  int v35; // ecx
  int v36; // edi
  int v37; // ecx
  int v38; // edi
  int v39; // ecx
  int v40; // edi

  v3 = a2;
  v4 = (unsigned __int16)a1;
  v5 = HIWORD(a1);
  if ( !a2 )
    return 1;
  for ( i = a3; i; v5 %= 0xFFF1u )
  {
    v8 = i;
    if ( i >= 0x15B0 )
      v8 = 5552;
    i -= v8;
    if ( v8 >= 16 )
    {
      v9 = (unsigned int)v8 >> 4;
      v8 += -16 * ((unsigned int)v8 >> 4);
      do
      {
        v10 = *v3;
        v3 += 16;
        v11 = v10 + v4;
        v12 = v11 + v5;
        v13 = *(v3 - 15) + v11;
        v14 = v13 + v12;
        v15 = *(v3 - 14) + v13;
        v16 = v15 + v14;
        v17 = *(v3 - 13) + v15;
        v18 = v17 + v16;
        v19 = *(v3 - 12) + v17;
        v20 = v19 + v18;
        v21 = *(v3 - 11) + v19;
        v22 = v21 + v20;
        v23 = *(v3 - 10) + v21;
        v24 = v23 + v22;
        v25 = *(v3 - 9) + v23;
        v26 = v25 + v24;
        v27 = *(v3 - 8) + v25;
        v28 = v27 + v26;
        v29 = *(v3 - 7) + v27;
        v30 = v29 + v28;
        v31 = *(v3 - 6) + v29;
        v32 = v31 + v30;
        v33 = *(v3 - 5) + v31;
        v34 = v33 + v32;
        v35 = *(v3 - 4) + v33;
        v36 = v35 + v34;
        v37 = *(v3 - 3) + v35;
        v38 = v37 + v36;
        v39 = *(v3 - 2) + v37;
        v40 = v39 + v38;
        v4 = *(v3 - 1) + v39;
        v5 = v4 + v40;
        --v9;
      }
      while ( v9 );
    }
    for ( ; v8; --v8 )
    {
      v4 += *v3++;
      v5 += v4;
    }
    v4 %= 0xFFF1u;
  }
  return v4 | (v5 << 16);
}
