char __cdecl sub_420D60(char a1, char *a2)
{
  int v2; // eax

  LOBYTE(v2) = a1;
  if ( !a1 )
    LOBYTE(sio0_mode_reg) = sio0_mode_reg | 2;
  byte_52670C[(unsigned __int8)dword_526810 + 3] = *a2;
  LOBYTE(dword_526810) = dword_526810 + 1;
  if ( a1 )
  {
    LOBYTE(v2) = sio0_control_reg;
    if ( (sio0_control_reg & 0x1000) != 0 )
    {
      sub_42AFD0();
      v2 = hw_update_counter;
      if ( hw_update_counter >= 0 )
      {
        if ( (unsigned int)hw_update_counter > 0x1F9 )
        {
          dword_4FD864 = hw_update_counter - 505;
          dword_4FD86C = 128;
          LOBYTE(v2) = hw_update_counter + 7;
          return v2;
        }
      }
      else
      {
        v2 = 0;
        hw_update_counter = 0;
      }
      dword_4FD868 = dword_455940 + v2 - 505;
      dword_4FD86C = 0;
    }
  }
  return v2;
}

int __cdecl sub_420DB0(unsigned __int8 a1, int a2, char a3)
{
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // ecx
  char v7; // dl
  int v8; // ecx
  int v10; // edx
  _BYTE v11[9]; // [esp+4h] [ebp-10h] BYREF

  v3 = dword_456048[a1];
  if ( !v3 )
    goto LABEL_24;
  v4 = v3 - 1;
  if ( v4 )
  {
    if ( v4 == 3 )
    {
      byte_4FC464[(unsigned __int8)byte_516560[0]] = a3;
      if ( a3 == 66 || a3 == 67 )
      {
        if ( dword_4FD8E0[a1] )
        {
          sub_42D0E0(a1, v11);
        }
        else
        {
          sub_42D010(a1, v11);
          *(_DWORD *)&v11[5] = -2139062144;
        }
      }
      switch ( a3 )
      {
        case 'D':
          v5 = dword_4557B0;
          v6 = dword_4557B4;
          v7 = byte_4557B8;
          goto LABEL_17;
        case 'E':
          *(_DWORD *)v11 = dword_4557BC;
          *(_DWORD *)&v11[4] = dword_4557C0;
          v8 = dword_4FD8E0[a1];
          v11[8] = byte_4557C4;
          if ( v8 == 1 )
            v11[5] = 1;
          break;
        case 'F':
          v5 = dword_4557C8;
          v6 = dword_4557CC;
          v7 = byte_4557D0;
          goto LABEL_17;
        case 'G':
          v5 = dword_4557D4;
          v6 = dword_4557D8;
          v7 = byte_4557DC;
          goto LABEL_17;
        case 'L':
          v5 = dword_4557EC;
          v6 = dword_4557F0;
          v7 = byte_4557F4;
          goto LABEL_17;
        case 'M':
          v5 = dword_4557E0;
          v6 = dword_4557E4;
          v7 = byte_4557E8;
LABEL_17:
          *(_DWORD *)v11 = v5;
          *(_DWORD *)&v11[4] = v6;
          v11[8] = v7;
          break;
        default:
          break;
      }
      v10 = *(_DWORD *)&v11[5];
      *(_DWORD *)a2 = *(_DWORD *)&v11[1];
      *(_DWORD *)(a2 + 4) = v10;
      return a2;
    }
LABEL_24:
    *(_BYTE *)(a2 + 3) = -1;
    *(_BYTE *)(a2 + 2) = -1;
    *(_BYTE *)(a2 + 1) = 90;
    *(_BYTE *)a2 = 65;
    *(_DWORD *)(a2 + 4) = -2139062144;
    return a2 + 4;
  }
  sub_42D010(a1, v11);
  if ( a3 != 66 )
    v11[1] = a3;
  if ( a3 == 69 )
  {
    *(_DWORD *)v11 = dword_4557F8;
    v11[4] = byte_4557FC;
  }
  *(_DWORD *)a2 = *(_DWORD *)&v11[1];
  *(_DWORD *)(a2 + 4) = -2139062144;
  return a2 + 4;
}

unsigned int __cdecl sub_420F90(_BYTE *a1, _DWORD *a2)
{
  int *v2; // ecx
  int *v3; // esi
  int v4; // edi
  unsigned int result; // eax

  dword_516540 = 0;
  *a2 = 3;
  v2 = &dword_516540;
  v3 = dword_456048;
  v4 = 4;
  do
  {
    *(_BYTE *)v2 = *(_BYTE *)a2;
    ++v3;
    v2 = (int *)((char *)v2 + 1);
    --v4;
    *a2 += 8;
  }
  while ( v4 );
  *a1 = 1;
  a1[1] = 0x80;
  result = *a2 - 3;
  a1[2] = 90;
  if ( result < 0x20 )
  {
    result >>= 1;
    LOBYTE(result) = result | 0x80;
    a1[1] = result;
  }
  return result;
}

void __cdecl sio_command(char *a1)
{
  char v1; // bl
  int v2; // esi
  int v3; // eax
  unsigned __int8 v4; // dl
  char v6; // cl
  bool v7; // zf
  int v8; // edx
  int v9; // eax
  char v10; // cl
  int v11; // ecx
  int v12; // edx
  char v13; // al
  int v14; // eax
  int v15; // ecx
  char v16; // dl
  int v17; // edx
  int v18; // eax
  char v19; // cl
  int v20; // ecx
  int v21; // edx
  char v22; // al
  int v23; // eax
  int v24; // ecx
  char v25; // dl
  unsigned __int8 v26; // si
  int v27; // eax
  unsigned int v28; // ecx
  unsigned int v29; // ecx
  int v30; // eax
  unsigned int v31; // ecx
  unsigned int v32; // edx
  _BYTE *v33; // eax
  bool v34; // cf
  char v35; // al
  __int16 v36; // ax
  __int16 v37; // ax
  char v38; // al
  char *v39; // ecx
  int v40; // esi
  unsigned __int8 v41; // [esp-4h] [ebp-14h]
  unsigned __int8 v42; // [esp-4h] [ebp-14h]
  char v43; // [esp+14h] [ebp+4h]

  v1 = byte_516560[0];
  if ( byte_516560[0] >= 0 )
  {
    v2 = (unsigned __int8)byte_516560[0];
    v3 = 65 * (unsigned __int8)byte_516560[0];
    v4 = byte_516560[v3 + 2];
    if ( v4 )
    {
      if ( byte_516560[1] == 1 )
      {
        if ( v4 == 1 )
        {
          if ( (*a1 & 0x40) != 0x40 )
          {
            sub_420D60(1, &byte_516560[v3 + 3]);
            byte_516560[65 * (unsigned __int8)byte_516560[0] + 2] = 0;
            return;
          }
          v6 = multitap_1;
          v7 = multitap_1 == 0;
          v43 = dword_456048[(unsigned __int8)byte_516560[0]];
          byte_4FC464[(unsigned __int8)byte_516560[0]] = 0;
          LOWORD(dword_4FC480) = -256;
          if ( v7 )
            BYTE1(dword_4FC480) = v1;
          if ( v1 )
          {
            if ( v1 == 1 && v6 )
              v43 = 0;
          }
          else if ( v6 )
          {
            v43 = 10;
          }
          switch ( v43 )
          {
            case 0:
              *(_WORD *)(v3 + 5334371) = -1;
              if ( *a1 != 66 )
                byte_516564[65 * (unsigned __int8)byte_516560[0]] = *a1;
              dword_4557AC = 2;
              break;
            case 1:
              sub_42D010(v2, (_BYTE *)(v3 + 5334371));
              if ( *a1 != 66 )
                byte_516564[65 * (unsigned __int8)byte_516560[0]] = *a1;
              dword_4557AC = 5;
              if ( *a1 == 69 )
              {
                byte_516560[65 * (unsigned __int8)byte_516560[0] + 3] = 1;
                byte_516564[65 * (unsigned __int8)byte_516560[0]] = -13;
                byte_516565[65 * (unsigned __int8)byte_516560[0]] = 90;
                byte_516566[65 * (unsigned __int8)byte_516560[0]] = 0;
                byte_516567[65 * (unsigned __int8)byte_516560[0]] = 0;
              }
              break;
            case 2:
              if ( !dword_4FD8E0[v2] )
              {
                sub_42D010(v2, (_BYTE *)(v3 + 5334371));
                if ( *a1 != 66 )
                  byte_516564[65 * (unsigned __int8)byte_516560[0]] = *a1;
                goto LABEL_30;
              }
              sub_42D3C0(v2, (_BYTE *)(v3 + 5334371));
              dword_4557AC = 7;
              break;
            case 3:
              if ( dword_4FD8E0[v2] )
              {
                sub_42D440(v2, (_BYTE *)(v3 + 5334371));
                dword_4557AC = 9;
              }
              else
              {
                sub_42D010(v2, (_BYTE *)(v3 + 5334371));
                if ( *a1 == 66 )
                {
LABEL_30:
                  dword_4557AC = 5;
                }
                else
                {
                  byte_516564[65 * (unsigned __int8)byte_516560[0]] = *a1;
                  dword_4557AC = 5;
                }
              }
              break;
            case 4:
            case 5:
            case 6:
              byte_4FC464[v2] = *a1;
              if ( *a1 == 66 || *a1 == 67 )
              {
                if ( dword_4FD8E0[v2] )
                {
                  sub_42D0E0(v2, (_BYTE *)(v3 + 0x516563));
                }
                else
                {
                  sub_42D010(v2, (_BYTE *)(v3 + 5334371));
                  *(_DWORD *)&byte_516568[65 * (unsigned __int8)byte_516560[0]] = -2139062144;
                }
              }
              dword_4557AC = 9;
              byte_526820[0] = 1;
              byte_526821[0] = *a1;
              if ( *a1 == 68 )
              {
                v8 = dword_4557B4;
                v9 = 65 * (unsigned __int8)byte_516560[0] + 5334371;
                *(_DWORD *)v9 = dword_4557B0;
                v10 = byte_4557B8;
                *(_DWORD *)(v9 + 4) = v8;
                *(_BYTE *)(v9 + 8) = v10;
              }
              if ( *a1 == 69 )
              {
                v11 = dword_4557C0;
                v12 = 65 * (unsigned __int8)byte_516560[0] + 5334371;
                *(_DWORD *)v12 = dword_4557BC;
                v13 = byte_4557C4;
                *(_DWORD *)(v12 + 4) = v11;
                *(_BYTE *)(v12 + 8) = v13;
                if ( dword_4FD8E0[(unsigned __int8)byte_516560[0]] == 1 )
                  byte_516568[65 * (unsigned __int8)byte_516560[0]] = 1;
              }
              if ( *a1 == 70 )
              {
                v14 = dword_4557CC;
                v15 = 65 * (unsigned __int8)byte_516560[0] + 5334371;
                *(_DWORD *)v15 = dword_4557C8;
                v16 = byte_4557D0;
                *(_DWORD *)(v15 + 4) = v14;
                *(_BYTE *)(v15 + 8) = v16;
              }
              if ( *a1 == 71 )
              {
                v17 = dword_4557D8;
                v18 = 65 * (unsigned __int8)byte_516560[0] + 5334371;
                *(_DWORD *)v18 = dword_4557D4;
                v19 = byte_4557DC;
                *(_DWORD *)(v18 + 4) = v17;
                *(_BYTE *)(v18 + 8) = v19;
              }
              if ( *a1 == 76 )
              {
                v20 = dword_4557E4;
                v21 = 65 * (unsigned __int8)byte_516560[0] + 5334371;
                *(_DWORD *)v21 = dword_4557E0;
                v22 = byte_4557E8;
                *(_DWORD *)(v21 + 4) = v20;
                *(_BYTE *)(v21 + 8) = v22;
              }
              if ( *a1 == 77 )
              {
                v23 = dword_4557F0;
                v24 = 65 * (unsigned __int8)byte_516560[0] + 5334371;
                *(_DWORD *)v24 = dword_4557EC;
                v25 = byte_4557F4;
                *(_DWORD *)(v24 + 4) = v23;
                *(_BYTE *)(v24 + 8) = v25;
              }
              break;
            case 10:
              sub_420F90((_BYTE *)(v3 + 5334371), &dword_4557AC);
              break;
            default:
              break;
          }
        }
        else
        {
          byte_526820[(unsigned __int8)byte_516560[65 * (unsigned __int8)byte_516560[0] + 2]] = *a1;
          if ( multitap_1 )
          {
            if ( !v1 && *((_BYTE *)&dword_516540 + (unsigned __int8)(BYTE1(dword_4FC480) + 1)) == byte_516560[2] )
            {
              LOBYTE(dword_4FC480) = byte_516560[2] - 1;
              if ( (*a1 & 0x40) == 0x40 )
              {
                ++BYTE1(dword_4FC480);
                byte_4FC464[0] = 0;
                sub_420DB0(BYTE1(dword_4FC480), (unsigned __int8)byte_516560[2] + 5334371, *a1);
              }
            }
          }
          v26 = dword_4FC480;
          if ( byte_4FC464[(unsigned __int8)byte_516560[0]] == 76
            && *a1 == 1
            && (unsigned __int8)byte_516560[65 * (unsigned __int8)byte_516560[0] + 2] == (unsigned __int8)dword_4FC480
                                                                                       + 3 )
          {
            byte_516569[65 * (unsigned __int8)byte_516560[0] + (unsigned __int8)dword_4FC480] = 7;
          }
          if ( byte_4FC464[(unsigned __int8)byte_516560[0]] == 70
            && *a1 == 1
            && (unsigned __int8)byte_516560[65 * (unsigned __int8)byte_516560[0] + 2] == v26 + 3 )
          {
            byte_516568[65 * (unsigned __int8)byte_516560[0] + v26] = 4;
            byte_516569[65 * (unsigned __int8)byte_516560[0] + v26] = 3;
            byte_51656A[65 * (unsigned __int8)byte_516560[0] + v26] = 1;
            byte_51656B[65 * (unsigned __int8)byte_516560[0] + v26] = 30;
          }
          if ( byte_4FC464[(unsigned __int8)byte_516560[0]] == 68
            && *a1
            && (unsigned __int8)byte_516560[65 * (unsigned __int8)byte_516560[0] + 2] == v26 + 3
            && dword_4FD8E0[BYTE1(dword_4FC480)] != 1 )
          {
            v41 = BYTE1(dword_4FC480);
            dword_4FD8E0[BYTE1(dword_4FC480)] = 1;
            sub_42D620(v41);
            v26 = dword_4FC480;
          }
          if ( byte_4FC464[(unsigned __int8)byte_516560[0]] == 68
            && !*a1
            && (unsigned __int8)byte_516560[65 * (unsigned __int8)byte_516560[0] + 2] == v26 + 3
            && dword_4FD8E0[BYTE1(dword_4FC480)] )
          {
            v42 = BYTE1(dword_4FC480);
            dword_4FD8E0[BYTE1(dword_4FC480)] = 0;
            sub_42D620(v42);
            v26 = dword_4FC480;
          }
          v27 = (unsigned __int8)byte_516560[0];
          if ( byte_4FC464[(unsigned __int8)byte_516560[0]] == 66 )
          {
            if ( (*a1 & 1) != 0 && (unsigned __int8)byte_516560[65 * (unsigned __int8)byte_516560[0] + 2] == v26 + 3 )
            {
              if ( g_PlayerDeviceMap1[BYTE1(dword_4FC480)] == 5 )
              {
                joy_issue_small_motor();
                v26 = dword_4FC480;
              }
              v28 = g_PlayerDeviceMap1[BYTE1(dword_4FC480)];
              if ( v28 && v28 <= 4 )
              {
                diSetEffectMagnitude(0, 1, 2, BYTE1(dword_4FC480));
                v26 = dword_4FC480;
              }
              v27 = (unsigned __int8)byte_516560[0];
              byte_4FC468[2 * (unsigned __int8)byte_516560[0]] = *a1 & 1;
            }
            if ( byte_4FC464[v27] == 66 && *a1 && (unsigned __int8)byte_516560[65 * v27 + 2] == v26 + 4 )
            {
              if ( g_PlayerDeviceMap1[BYTE1(dword_4FC480)] == 5 )
                joy_issue_big_motor();
              v29 = g_PlayerDeviceMap1[BYTE1(dword_4FC480)];
              if ( v29 && v29 <= 4 )
                diSetEffectMagnitude(1, (unsigned __int8)*a1, 2, BYTE1(dword_4FC480));
              byte_4FC469[2 * (unsigned __int8)byte_516560[0]] = *a1;
            }
          }
        }
        v30 = 65 * (unsigned __int8)byte_516560[0];
        v31 = (unsigned __int8)byte_516560[v30 + 2];
        if ( v31 >= dword_4557AC - 1 )
          sub_420D60(0, (char *)(v31 + v30 + 5334371));
        else
          sub_420D60(1, (char *)(v31 + v30 + 5334371));
        v32 = dword_4557AC;
        ++byte_516560[65 * (unsigned __int8)byte_516560[0] + 2];
        v33 = (_BYTE *)(65 * (unsigned __int8)byte_516560[0] + 5334370);
        v34 = (unsigned __int8)byte_516560[65 * (unsigned __int8)byte_516560[0] + 2] < v32;
      }
      else
      {
        if ( byte_516560[1] != 2 )
          return;
        if ( v4 == 1 )
        {
          if ( *a1 == 87 )
          {
            v35 = 87;
            byte_547060[129024] = 87;
            byte_547060[129025] = -118;
            byte_547060[129026] = 0;
            byte_547060[129027] = 90;
            byte_547060[129028] = 93;
            byte_547060[129029] = 0;
            byte_547060[129160] = 92;
            byte_547060[129161] = 93;
            byte_547060[129162] = 71;
          }
          else
          {
            if ( *a1 != 82 )
            {
              byte_516560[65 * (unsigned __int8)byte_516560[0] + 2] = 0;
              return;
            }
            v1 = byte_516560[0];
            v35 = 82;
            byte_547060[129024] = 82;
            byte_547060[129025] = -116;
            byte_547060[129026] = 0;
            byte_547060[129027] = 90;
            byte_547060[129028] = 93;
            byte_547060[129029] = 0;
            byte_547060[129030] = 0;
            byte_547060[129031] = 92;
            byte_547060[129032] = 93;
            byte_547060[129164] = 71;
          }
        }
        else
        {
          v35 = byte_547060[129024];
        }
        if ( v35 == 82 )
        {
          if ( v4 == 4 )
          {
            LOBYTE(v37) = 0;
            HIBYTE(v37) = *a1;
            word_566962 = v37;
            byte_547060[129033] = *a1;
          }
          if ( v4 == 5 )
          {
            word_566962 |= (unsigned __int8)*a1;
            byte_547060[129034] = *a1;
          }
          if ( v4 == 6 )
          {
            qmemcpy(
              &byte_547060[129035],
              &byte_526860[128 * ((unsigned __int16)word_566962 + ((unsigned __int8)byte_516560[0] << 10))],
              0x80u);
            v38 = 0;
            byte_547060[129163] = 0;
            v39 = &byte_547060[129033];
            v40 = 130;
            do
            {
              v38 ^= *v39++;
              --v40;
              byte_547060[129163] = v38;
            }
            while ( v40 );
          }
        }
        else if ( v35 == 87 )
        {
          if ( v1 )
            dword_4FC47C = 1;
          else
            dword_4FC478 = 1;
          if ( v4 > 3u && v4 < 0x86u )
            byte_547060[v4 + 129026] = *a1;
          if ( v4 == 0x89 )
          {
            LOBYTE(v36) = 0;
            HIBYTE(v36) = byte_547060[129030];
            word_566962 = (unsigned __int8)byte_547060[129031] | v36;
            qmemcpy(&byte_526860[128 * ((unsigned __int16)word_566962 + (v2 << 10))], &byte_547060[129032], 0x80u);
          }
        }
        if ( v4 >= (unsigned int)byte_547060[129025] )
          sub_420D60(0, &byte_547060[v4 + 129025]);
        else
          sub_420D60(1, &byte_547060[v4 + 129025]);
        ++byte_516560[65 * (unsigned __int8)byte_516560[0] + 2];
        v33 = (_BYTE *)(65 * (unsigned __int8)byte_516560[0] + 5334370);
        v34 = (unsigned __int8)byte_516560[65 * (unsigned __int8)byte_516560[0] + 2] < (unsigned int)byte_547060[129025];
      }
      if ( !v34 )
        *v33 = 0;
    }
    else
    {
      if ( *a1 == 1 )
      {
        byte_516560[1] = 1;
        ++byte_516560[65 * (unsigned __int8)byte_516560[0] + 2];
LABEL_9:
        sub_420D60(1, (char *)(65 * (unsigned __int8)byte_516560[0] + 5334371));
        return;
      }
      if ( *a1 == -127 )
      {
        if ( byte_4557A8 )
        {
          byte_516560[1] = 2;
          ++byte_516560[65 * (unsigned __int8)byte_516560[0] + 2];
        }
        else
        {
          byte_516560[65 * (unsigned __int8)byte_516560[0] + 2] = 0;
        }
        goto LABEL_9;
      }
      sub_420D60(0, (char *)(v3 + 5334371));
    }
  }
}

bool __cdecl sub_421B10(__int16 a1)
{
  bool result; // al

  if ( (a1 & 2) != 0 )
  {
    result = (a1 & 0x2000) != 0;
    byte_516560[0] = result;
  }
  else
  {
    byte_5165A3 = 0;
    byte_516560[2] = 0;
    byte_516560[0] = 0x80;
    return 0;
  }
  return result;
}

char sub_421B40()
{
  unsigned int i; // eax

  byte_516560[0] = 0;
  byte_5165A3 = 0;
  byte_516560[2] = 0;
  byte_516560[1] = 0;
  for ( i = 3; i < 6; ++i )
  {
    byte_516560[i + 3] = -1;
    byte_5165A4[i] = -1;
  }
  byte_516560[3] = 0;
  byte_516564[0] = 65;
  byte_516565[0] = 90;
  byte_5165A4[0] = 0;
  byte_5165A5 = 65;
  byte_5165A6 = 90;
  return 90;
}

char memcard_load()
{
  FILE *v0; // eax
  unsigned int i; // eax
  unsigned int j; // eax
  unsigned int k; // eax
  FILE *v4; // eax
  FILE *v5; // esi
  FILE *v6; // esi

  LOBYTE(v0) = byte_4FC460;
  if ( !byte_4FC460 )
  {
    if ( !strcmp((const char *)Memcard1, "NULL") )
      sprintf((char *const)Memcard1, "%s", "memcards\\epsxe000.mcr");
    if ( !strcmp((const char *)Memcard2, "NULL") )
      sprintf((char *const)Memcard2, "%s", "memcards\\epsxe001.mcr");
    for ( i = 0; i < 0x20000; ++i )
    {
      byte_546860[i] = 0;
      byte_526860[i] = 0;
    }
    byte_546860[0] = 77;
    byte_526860[0] = 77;
    byte_546861[0] = 67;
    byte_526861 = 67;
    byte_5468DF = 14;
    byte_5268DF = 14;
    for ( j = 0; j < 0x780; j += 128 )
    {
      byte_5468E0[j] = -96;
      byte_5268E0[j] = -96;
      byte_5468E8[j] = -1;
      byte_5268E8[j] = -1;
      byte_5468E9[j] = -1;
      byte_5268E9[j] = -1;
      byte_54695F[j] = -96;
      byte_52695F[j] = -96;
    }
    for ( k = 0; k < 0xA00; k += 128 )
    {
      byte_547060[k] = -1;
      byte_527060[k] = -1;
      byte_547060[k + 1] = -1;
      byte_527061[k] = -1;
      byte_547060[k + 2] = -1;
      byte_527062[k] = -1;
      byte_547060[k + 3] = -1;
      byte_527063[k] = -1;
      byte_547060[k + 8] = -1;
      byte_527068[k] = -1;
      byte_547060[k + 9] = -1;
      byte_527069[k] = -1;
    }
    v4 = fopen((const char *)Memcard1, "rb");
    v5 = v4;
    if ( v4 )
    {
      fseek(v4, 0, 2);
      Offset = ftell(v5) - 0x20000;
      fseek(v5, Offset, 0);
      fread(byte_526860, 1u, 0x20000u, v5);
      fclose(v5);
    }
    else
    {
      Offset = 0;
    }
    v0 = fopen((const char *)Memcard2, "rb");
    v6 = v0;
    if ( v0 )
    {
      fseek(v0, 0, 2);
      dword_4FC474 = ftell(v6) - 0x20000;
      fseek(v6, dword_4FC474, 0);
      fread(byte_546860, 1u, 0x20000u, v6);
      LOBYTE(v0) = fclose(v6);
    }
    else
    {
      dword_4FC474 = 0;
    }
    byte_4FC460 = 1;
  }
  return (char)v0;
}

char memcard1_save()
{
  char result; // al
  FILE *v1; // esi

  result = byte_4FC460;
  if ( byte_4FC460 )
  {
    v1 = fopen((const char *)Memcard1, "wb");
    if ( v1 )
    {
      fseek(v1, Offset, 0);
      fwrite(byte_526860, 1u, 0x20000u, v1);
      return fclose(v1);
    }
    else
    {
      return dbg_print(" * Warning: The memcard [%s] has NOT been saved to disk\n", (const char *)Memcard1);
    }
  }
  return result;
}

char memcard2_save()
{
  char result; // al
  FILE *v1; // esi

  result = byte_4FC460;
  if ( byte_4FC460 )
  {
    v1 = fopen((const char *)Memcard2, "wb");
    if ( v1 )
    {
      fseek(v1, dword_4FC474, 0);
      fwrite(byte_546860, 1u, 0x20000u, v1);
      return fclose(v1);
    }
    else
    {
      return dbg_print(" * Warning: The memcard [%s] has NOT been saved to disk\n", (const char *)Memcard2);
    }
  }
  return result;
}

// Microsoft VisualC 2-14/net runtime
char memcard12_save()
{
  memcard1_save();
  return memcard2_save();
}

char memcard_all_save()
{
  int v0; // eax

  v0 = dword_4FC478;
  if ( dword_4FC478 )
    v0 = ++dword_4FC478;
  if ( dword_4FC47C )
    ++dword_4FC47C;
  if ( v0 == 120 )
  {
    dword_4FC478 = 0;
    LOBYTE(v0) = memcard1_save();
  }
  if ( dword_4FC47C == 120 )
  {
    dword_4FC47C = 0;
    LOBYTE(v0) = memcard2_save();
  }
  return v0;
}

int (__stdcall *sio_reset())(_DWORD)
{
  sio0_mode_reg = 5;
  sio0_control_reg = 0;
  byte_52670C[0] = 0;
  byte_52670C[1] = 0;
  byte_52670C[2] = 1;
  byte_52670C[259] = 0;
  LOBYTE(dword_526810) = 0;
  sub_421B40();
  memcard_load();
  return sub_42D620(0);
}

void __cdecl sio_data_write(int a1, char a2)
{
  LOBYTE(sio0_mode_reg) = sio0_mode_reg & 0xFB;
  byte_52660C[(unsigned __int8)--byte_52670C[0]] = a2;
  if ( !byte_52670C[0] )
  {
    LOBYTE(sio0_mode_reg) = sio0_mode_reg & 0xFE;
    if ( (sio0_control_reg & 1) != 0 )
    {
      sio_command(byte_52660C);
      LOBYTE(sio0_mode_reg) = sio0_mode_reg | 5;
      byte_52670C[0] = byte_52670C[2];
      if ( (sio0_control_reg & 0x400) != 0 )
      {
        BYTE1(sio0_mode_reg) |= 2u;
        sio_assert_int();
      }
    }
  }
}

void sub_421FD0()
{
  LOWORD(sio0_mode_reg) = sio0_mode_reg | 0x202;
}

void sio_data_read()
{
  if ( dword_4FD86C && hw_update_counter < (unsigned int)dword_4FD864 )
  {
    dword_4FD86C = 0;
    sub_421FD0();
  }
  if ( byte_52670C[259] != (_BYTE)dword_526810 && ++byte_52670C[259] == (_BYTE)dword_526810 )
    LOBYTE(sio0_mode_reg) = sio0_mode_reg & 0xFD;
}

__int16 __cdecl sio_read_half(int a1)
{
  char v1; // al
  __int16 v2; // bx
  char v3; // al
  __int16 result; // ax

  switch ( a1 )
  {
    case 0x1F801040:
      sio_data_read();
      HIBYTE(v2) = v1;
      sio_data_read();
      LOBYTE(v2) = v3;
      result = v2;
      break;
    case 0x1F801044:
      if ( dword_4FD86C )
      {
        if ( hw_update_counter < (unsigned int)dword_4FD864 )
        {
          dword_4FD86C = 0;
          sub_421FD0();
        }
      }
      result = sio0_mode_reg;
      break;
    case 0x1F801048:
      result = HIWORD(sio0_mode_reg);
      break;
    case 0x1F80104A:
      result = sio0_control_reg;
      break;
    case 0x1F80104E:
      result = HIWORD(sio0_control_reg);
      break;
    default:
      result = 0;
      break;
  }
  return result;
}

int __cdecl sio_read_word(int a1)
{
  char v2; // al
  unsigned __int16 v3; // bx
  char v4; // al
  unsigned __int8 v5; // al
  int v6; // ebx
  unsigned __int8 v7; // al

  if ( a1 == 0x1F801040 )
  {
    sio_data_read();
    HIBYTE(v3) = v2;
    sio_data_read();
    LOBYTE(v3) = v4;
    sio_data_read();
    v6 = (v5 | (v3 << 8)) << 8;
    sio_data_read();
    return v6 | v7;
  }
  else if ( a1 == 0x1F801044 )
  {
    if ( dword_4FD86C )
    {
      if ( hw_update_counter < (unsigned int)dword_4FD864 )
      {
        dword_4FD86C = 0;
        sub_421FD0();
      }
    }
    return (unsigned __int16)sio0_mode_reg;
  }
  else
  {
    return 0;
  }
}

int __cdecl sio_read(int a1, char a2)
{
  int result; // eax

  result = 0xFFFF;
  switch ( a2 )
  {
    case 1:
      sio_data_read();
      return (unsigned __int8)result;
    case 2:
      return (unsigned __int16)sio_read_half(a1);
    case 4:
      return sio_read_word(a1);
  }
  return result;
}

int __cdecl sio_freeze(const char *a1, int a2)
{
  char Buffer[64]; // [esp+8h] [ebp-40h] BYREF

  sprintf(Buffer, "%s", a1);
  *(_DWORD *)&Buffer[3] = 263532;
  gzwrite(a2, (unsigned __int8 *)Buffer, 7u);
  gzwrite(a2, (unsigned __int8 *)byte_526600, 0x214u);
  gzwrite(a2, (unsigned __int8 *)byte_516560, 0x84u);
  gzwrite(a2, (unsigned __int8 *)byte_526860, 0x40104u);
  memset(Buffer, 0, sizeof(Buffer));
  *(_DWORD *)&Buffer[4] = dword_516540;
  *(_WORD *)&Buffer[8] = dword_4FC480;
  *(_DWORD *)Buffer = dword_4557AC;
  Buffer[10] = multitap_1 & 1;
  return gzwrite(a2, (unsigned __int8 *)Buffer, 0x40u);
}

void __cdecl sio_unfreeze(int a1, _DWORD *a2)
{
  char *v2; // edi
  char v3[4]; // [esp+8h] [ebp-40h] BYREF
  int v4; // [esp+Ch] [ebp-3Ch]
  __int16 v5; // [esp+10h] [ebp-38h]
  char v6; // [esp+12h] [ebp-36h]

  v2 = (char *)malloc(0x40104u);
  gzread(a2, v3, 7);
  gzread(a2, byte_526600, 532);
  gzread(a2, byte_516560, 132);
  memcard12_save();
  gzread(a2, v2, 262404);
  gzread(a2, v3, 64);
  dword_516540 = v4;
  dword_4557AC = *(_DWORD *)v3;
  LOWORD(dword_4FC480) = v5;
  multitap_1 = v6 & 1;
  free(v2);
}