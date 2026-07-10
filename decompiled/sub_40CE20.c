#include "pch.h"
int __cdecl sub_40CE20(int a1, int a2, unsigned __int16 a3)
{
  __int64 v3; // rax
  int v4; // ecx
  int v5; // ecx
  int v6; // esi
  double v7; // st7
  int v8; // esi
  int v9; // ecx
  int v10; // ecx
  int v11; // esi
  int v12; // ecx
  bool v13; // zf
  int v14; // ecx
  __int64 v16; // [esp+4h] [ebp-8h]

  LODWORD(v3) = a2;
  switch ( a2 )
  {
    case 0:
      v4 = 74 * a1;
      dword_465540[v4] = a3 & 0x3FFF;
      HIDWORD(v3) = (a3 >> 14) & 1;
      dword_465550[v4] = HIDWORD(v3);
      dword_465558[v4] = HIDWORD(v3);
      dword_465560[v4] = (a3 >> 13) & 1;
      LODWORD(v3) = a3 & 0x7F;
      dword_465568[v4] = a3 >> 15;
      dword_465548[v4] = v3;
      break;
    case 2:
      v5 = 74 * a1;
      dword_465544[v5] = a3 & 0x3FFF;
      HIDWORD(v3) = (a3 >> 14) & 1;
      dword_465554[v5] = HIDWORD(v3);
      dword_46555C[v5] = HIDWORD(v3);
      dword_465564[v5] = (a3 >> 13) & 1;
      LODWORD(v3) = a3 & 0x7F;
      dword_46556C[v5] = a3 >> 15;
      dword_46554C[v5] = v3;
      break;
    case 4:
      v6 = 74 * a1;
      v16 = a3 & 0x3FFF;
      dword_465570[v6] = v16;
      v7 = (double)v16 * 0.000244140625;
      *(float *)(v6 * 4 + 4609456) = v7;
      v3 = (__int64)(v7 * 65536.0);
      dword_4655B4[v6] = v3;
      break;
    case 6:
      dword_465574[74 * a1] = a3;
      LODWORD(v3) = a3;
      break;
    case 8:
      LODWORD(v3) = 296 * a1;
      *(int *)((char *)&dword_465578 + v3) = a3 >> 15;
      HIDWORD(v3) = HIBYTE(a3) & 0x7F;
      *(int *)((char *)&dword_46557C + v3) = HIDWORD(v3);
      v8 = (unsigned __int8)a3 >> 4;
      v9 = a3 & 0xF;
      *(int *)((char *)&dword_465654 + v3) = dword_44F208[HIDWORD(v3)];
      HIDWORD(v3) = dword_44F408[v8];
      *(int *)((char *)&dword_465584 + v3) = v9;
      v10 = dword_44F648[v9];
      *(int *)((char *)&dword_465580 + v3) = v8;
      *(int *)((char *)&dword_465658 + v3) = -HIDWORD(v3);
      *(int *)((char *)&dword_46565C + v3) = v10;
      break;
    case 10:
      LODWORD(v3) = 296 * a1;
      *(int *)((char *)&dword_465588 + v3) = a3 >> 15;
      HIDWORD(v3) = (a3 >> 14) & 1;
      v11 = (a3 >> 6) & 0x7F;
      v12 = a3 & 0x1F;
      *(int *)((char *)&dword_46558C + v3) = HIDWORD(v3);
      *(int *)((char *)&dword_465594 + v3) = (a3 >> 5) & 1;
      v13 = HIDWORD(v3) == 0;
      HIDWORD(v3) = *(&dword_44F448 + v11);
      *(int *)((char *)&dword_465590 + v3) = v11;
      *(int *)((char *)&dword_465598 + v3) = v12;
      if ( !v13 )
        HIDWORD(v3) = -HIDWORD(v3);
      v14 = -dword_44F688[v12];
      dword_465660[74 * a1] = HIDWORD(v3);
      dword_465664[74 * a1] = v14;
      break;
    case 12:
      dword_46559C[74 * a1] = a3 << 9;
      LODWORD(v3) = 296 * a1;
      break;
    case 14:
      dword_4655A0[74 * a1] = a3;
      break;
    default:
      return v3;
  }
  return v3;
}
