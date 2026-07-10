#include "pch.h"
int __cdecl sub_439770(unsigned __int8 **a1, int a2)
{
  int v2; // edi
  unsigned int v3; // ebx
  unsigned __int8 *v4; // eax
  unsigned __int8 *v5; // ecx
  unsigned __int8 *v6; // eax
  int v7; // ecx
  unsigned __int8 *v8; // edx
  unsigned __int8 *v9; // edx
  unsigned __int8 *v10; // eax
  unsigned __int8 *v11; // ebx
  int v12; // ecx
  unsigned __int8 *v13; // eax
  int v14; // eax
  unsigned __int8 *v15; // eax
  unsigned __int8 *v16; // eax
  unsigned __int8 *v17; // edx
  unsigned __int8 *v18; // eax
  unsigned __int8 *v19; // ecx
  unsigned __int8 *v20; // eax
  unsigned __int8 *v21; // ecx
  unsigned __int8 *v22; // eax
  unsigned __int8 *v23; // ecx
  unsigned __int8 *v24; // edx
  unsigned __int8 *v25; // eax
  unsigned __int8 *v26; // eax
  unsigned __int8 *v27; // edx
  unsigned __int8 *v28; // eax
  unsigned __int8 *v30; // ecx
  unsigned __int8 *v31; // ecx
  unsigned __int8 *v32; // eax
  unsigned __int8 *v33; // edx
  unsigned __int8 *v34; // edx
  unsigned __int8 *v35; // eax
  unsigned __int8 *v36; // ecx
  unsigned __int8 *v37; // eax
  unsigned __int8 *v38; // ecx
  unsigned __int8 *v39; // edx
  unsigned __int8 *v40; // eax
  unsigned __int8 *v41; // eax
  unsigned __int8 *v42; // eax
  unsigned int v43; // [esp+18h] [ebp+8h]

  if ( !a1 || !a1[7] || !*a1 )
    return -2;
  v2 = -5;
  v3 = a2 != 4 ? 0 : 0xFFFFFFFB;
  v43 = v3;
  while ( 2 )
  {
    v4 = a1[7];
    switch ( *(_DWORD *)v4 )
    {
      case 0:
        v5 = a1[1];
        if ( !v5 )
          return v2;
        a1[1] = v5 - 1;
        v2 = v3;
        ++a1[2];
        *((_DWORD *)v4 + 1) = **a1;
        v6 = a1[7];
        v7 = *((_DWORD *)v6 + 1) & 0xF;
        ++*a1;
        if ( (_BYTE)v7 != 8 )
        {
          *(_DWORD *)v6 = 13;
          v8 = a1[7];
          a1[6] = (unsigned __int8 *)aUnknownCompres;
          *((_DWORD *)v8 + 1) = 5;
          continue;
        }
        if ( (unsigned int)((*((_DWORD *)v6 + 1) >> 4) + 8) > *((_DWORD *)v6 + 4) )
        {
          *(_DWORD *)v6 = 13;
          v9 = a1[7];
          a1[6] = (unsigned __int8 *)aInvalidWindowS;
          *((_DWORD *)v9 + 1) = 5;
          continue;
        }
        *(_DWORD *)v6 = 1;
LABEL_12:
        v10 = a1[1];
        if ( !v10 )
          return v2;
        a1[1] = v10 - 1;
        v2 = v3;
        v11 = a1[7];
        ++a1[2];
        v12 = *(*a1)++;
        if ( (v12 + (*((_DWORD *)v11 + 1) << 8)) % 0x1Fu )
        {
          *(_DWORD *)v11 = 13;
          v13 = a1[7];
          v3 = v43;
          a1[6] = (unsigned __int8 *)aIncorrectHeade;
          *((_DWORD *)v13 + 1) = 5;
          continue;
        }
        if ( (v12 & 0x20) == 0 )
        {
          *(_DWORD *)v11 = 7;
          v3 = v43;
          continue;
        }
        v3 = v43;
        *(_DWORD *)a1[7] = 2;
LABEL_35:
        v28 = a1[1];
        if ( !v28 )
          return v2;
        v30 = *a1;
        ++a1[2];
        a1[1] = v28 - 1;
        v2 = v3;
        *((_DWORD *)a1[7] + 2) = *v30 << 24;
        v31 = a1[7];
        ++*a1;
        *(_DWORD *)v31 = 3;
LABEL_38:
        v32 = a1[1];
        if ( !v32 )
          return v2;
        v33 = *a1;
        a1[1] = v32 - 1;
        ++a1[2];
        v2 = v3;
        *((_DWORD *)a1[7] + 2) += *v33 << 16;
        v34 = a1[7];
        ++*a1;
        *(_DWORD *)v34 = 4;
LABEL_41:
        v35 = a1[1];
        if ( !v35 )
          return v2;
        v36 = *a1;
        a1[1] = v35 - 1;
        ++a1[2];
        v2 = v3;
        *((_DWORD *)a1[7] + 2) += *v36 << 8;
        ++*a1;
        *(_DWORD *)a1[7] = 5;
LABEL_44:
        v37 = a1[1];
        if ( !v37 )
          return v2;
        v38 = *a1;
        v39 = a1[2] + 1;
        a1[1] = v37 - 1;
        v40 = a1[7];
        a1[2] = v39;
        *((_DWORD *)v40 + 2) += *v38;
        ++*a1;
        v41 = a1[7];
        a1[12] = *((unsigned __int8 **)v41 + 2);
        *(_DWORD *)v41 = 6;
        return 2;
      case 1:
        goto LABEL_12;
      case 2:
        goto LABEL_35;
      case 3:
        goto LABEL_38;
      case 4:
        goto LABEL_41;
      case 5:
        goto LABEL_44;
      case 6:
        *(_DWORD *)a1[7] = 13;
        v42 = a1[7];
        a1[6] = (unsigned __int8 *)aNeedDictionary;
        *((_DWORD *)v42 + 1) = 0;
        return -2;
      case 7:
        v14 = sub_43B6C0(*((_DWORD **)v4 + 5), a1, v2);
        v2 = v14;
        if ( v14 == -3 )
        {
          *(_DWORD *)a1[7] = 13;
          *((_DWORD *)a1[7] + 1) = 0;
        }
        else
        {
          if ( !v14 )
            v2 = v3;
          if ( v2 != 1 )
            return v2;
          v2 = v3;
          sub_43B5A0(*((_DWORD *)a1[7] + 5), a1, a1[7] + 4);
          v15 = a1[7];
          if ( *((_DWORD *)v15 + 3) )
          {
            *(_DWORD *)v15 = 12;
          }
          else
          {
            *(_DWORD *)v15 = 8;
LABEL_25:
            v16 = a1[1];
            if ( !v16 )
              return v2;
            v17 = a1[7];
            a1[1] = v16 - 1;
            ++a1[2];
            v2 = v3;
            *((_DWORD *)v17 + 2) = *(*a1)++ << 24;
            *(_DWORD *)a1[7] = 9;
LABEL_27:
            v18 = a1[1];
            if ( !v18 )
              return v2;
            v19 = *a1;
            ++a1[2];
            a1[1] = v18 - 1;
            v2 = v3;
            *((_DWORD *)a1[7] + 2) += *v19 << 16;
            ++*a1;
            *(_DWORD *)a1[7] = 10;
LABEL_29:
            v20 = a1[1];
            if ( !v20 )
              return v2;
            v21 = *a1;
            ++a1[2];
            a1[1] = v20 - 1;
            v2 = v3;
            *((_DWORD *)a1[7] + 2) += *v21 << 8;
            ++*a1;
            *(_DWORD *)a1[7] = 11;
LABEL_31:
            v22 = a1[1];
            if ( !v22 )
              return v2;
            v23 = *a1;
            v24 = a1[2] + 1;
            a1[1] = v22 - 1;
            v25 = a1[7];
            a1[2] = v24;
            v2 = v3;
            *((_DWORD *)v25 + 2) += *v23;
            ++*a1;
            v26 = a1[7];
            if ( *((_DWORD *)v26 + 1) == *((_DWORD *)v26 + 2) )
            {
              *(_DWORD *)a1[7] = 12;
              return 1;
            }
            *(_DWORD *)v26 = 13;
            v27 = a1[7];
            a1[6] = (unsigned __int8 *)aIncorrectDataC;
            *((_DWORD *)v27 + 1) = 5;
          }
        }
        continue;
      case 8:
        goto LABEL_25;
      case 9:
        goto LABEL_27;
      case 0xA:
        goto LABEL_29;
      case 0xB:
        goto LABEL_31;
      case 0xC:
        return 1;
      case 0xD:
        return -3;
      default:
        return -2;
    }
  }
}
