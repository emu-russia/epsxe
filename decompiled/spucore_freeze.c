#include "pch.h"
int __cdecl sub_40D8F0(const char *a1, int a2)
{
  int v2; // edx
  char *v3; // esi
  int v4; // eax
  int v5; // ecx
  int v6; // edi
  int v7; // ebp
  int v8; // kr08_4
  int v9; // edx
  int v10; // edx
  int v11; // edx
  __int16 v12; // bx
  __int16 v13; // di
  __int16 v14; // bp
  unsigned __int8 v15; // bl
  __int16 *v16; // ecx
  int v17; // edx
  int v18; // esi
  int v19; // kr10_4
  char Buffer[384]; // [esp+10h] [ebp-200h] BYREF
  char v22; // [esp+190h] [ebp-80h] BYREF

  sprintf(Buffer, "%s", a1);
  *(_DWORD *)&Buffer[3] = 564744;
  sub_438F70(a2, Buffer, 7);
  sprintf(Buffer, aIspu);
  sub_438F70(a2, Buffer, 8);
  *(_QWORD *)Buffer = 0x89DF800000002LL;
  sub_438F70(a2, Buffer, 8);
  v3 = &Buffer[2];
  v4 = (int)dword_465550;
  v5 = 24;
  do
  {
    v6 = 0;
    v7 = 8;
    do
    {
      v8 = v2;
      v2 = 0;
      switch ( v6 )
      {
        case 0:
          v9 = 2 * (unsigned __int16)(*(_WORD *)v4 | (2 * *(_WORD *)(v4 + 24)));
          LOWORD(v9) = *(_WORD *)(v4 + 16) | v9;
          v2 = v9 << 13;
          LOWORD(v2) = *(_WORD *)(v4 - 16) | v2;
          *((_WORD *)v3 - 1) = v2;
          break;
        case 2:
          v10 = 2 * (unsigned __int16)(*(_WORD *)(v4 + 4) | (2 * *(_WORD *)(v4 + 28)));
          LOWORD(v10) = *(_WORD *)(v4 + 20) | v10;
          v2 = v10 << 13;
          LOWORD(v2) = *(_WORD *)(v4 - 12) | v2;
          *(_WORD *)v3 = v2;
          break;
        case 4:
          LOWORD(v2) = *(_WORD *)(v4 + 32);
          *((_WORD *)v3 + 1) = v2;
          break;
        case 6:
          LOWORD(v2) = *(_WORD *)(v4 + 36);
          *((_WORD *)v3 + 2) = v2;
          break;
        case 8:
          v11 = 16 * (unsigned __int16)(*(_WORD *)(v4 + 44) | (*(_WORD *)(v4 + 40) << 7));
          LOWORD(v11) = *(_WORD *)(v4 + 48) | v11;
          v2 = 16 * v11;
          LOWORD(v2) = *(_WORD *)(v4 + 52) | v2;
          *((_WORD *)v3 + 3) = v2;
          break;
        case 10:
          LOBYTE(v2) = *(_BYTE *)(v4 + 60) | (2 * *(_BYTE *)(v4 + 56));
          LOBYTE(v12) = 0;
          HIBYTE(v12) = v2;
          *((_WORD *)v3 + 4) = *(_WORD *)(v4 + 72) | (32 * (*(_WORD *)(v4 + 68) | (2 * (*(_WORD *)(v4 + 64) | v12))));
          break;
        case 12:
          v2 = *(int *)(v4 + 76) >> 9;
          *((_WORD *)v3 + 5) = v2;
          break;
        case 14:
          LOWORD(v2) = *(_WORD *)(v4 + 80);
          *((_WORD *)v3 + 6) = v2;
          break;
        default:
          v2 = v8;
          break;
      }
      v6 += 2;
      --v7;
    }
    while ( v7 );
    v4 += 296;
    v3 += 16;
    --v5;
  }
  while ( v5 );
  v13 = word_4F7586;
  v14 = dword_4F7588;
  v15 = BYTE2(dword_4F7558);
  v16 = (__int16 *)&v22;
  v17 = 0;
  v18 = 64;
  do
  {
    v19 = v4;
    v4 = 0;
    switch ( v17 )
    {
      case 0:
        *v16 = v13;
        break;
      case 2:
        *v16 = v14;
        break;
      case 4:
        LOWORD(v4) = word_4EF130;
        goto LABEL_37;
      case 6:
        LOWORD(v4) = word_4EF132;
        goto LABEL_37;
      case 16:
        LOWORD(v4) = dword_4F7558;
        goto LABEL_37;
      case 18:
        v4 = v15;
        goto LABEL_37;
      case 20:
        LOWORD(v4) = dword_463900;
        goto LABEL_37;
      case 22:
        v4 = BYTE2(dword_463900);
        goto LABEL_37;
      case 24:
        LOWORD(v4) = dword_4E7100;
        goto LABEL_37;
      case 26:
        v4 = BYTE2(dword_4E7100);
        goto LABEL_37;
      case 28:
        LOWORD(v4) = dword_4EF138;
        goto LABEL_37;
      case 30:
        v4 = BYTE2(dword_4EF138);
        goto LABEL_37;
      case 34:
        LOWORD(v4) = MEMORY[0x4F7140];
        goto LABEL_37;
      case 36:
        LOWORD(v4) = dword_463904;
        goto LABEL_37;
      case 42:
        v4 = sub_40CDF0(v16);
        goto LABEL_37;
      case 44:
        v4 = sub_40CE00(v16);
        goto LABEL_37;
      case 46:
        LOWORD(v4) = sub_40CE10();
        goto LABEL_37;
      case 48:
        LOWORD(v4) = word_4E7104;
        goto LABEL_37;
      case 50:
        LOWORD(v4) = word_4E7106;
        goto LABEL_37;
      case 52:
        LOWORD(v4) = word_4F755C;
        goto LABEL_37;
      case 54:
        LOWORD(v4) = word_4F7584;
LABEL_37:
        *v16 = v4;
        break;
      default:
        v4 = v19;
        break;
    }
    v17 += 2;
    ++v16;
    --v18;
  }
  while ( v18 );
  sub_438F70(a2, Buffer, 512);
  sub_438F70(a2, spu_ram, 0x80000);
  sub_438F70(a2, &dword_4E7108, 32800);
  return sub_438F70(a2, dword_465540, 7104);
}
