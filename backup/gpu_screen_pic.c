/*
.data:004560D0 byte_4560D0     db 6 dup(0AAh), 80h, 5 dup(0), 80h, 5 dup(0), 80h, 5 dup(0)
.data:004560D0                                         ; DATA XREF: gpu_sub_42EB00+22↑o
.data:004560D0                                         ; gpu_sub_42EBF0+22↑o
.data:004560E8                 db 80h, 5 dup(0), 80h, 2 dup(0), 50h, 2 dup(0), 80h, 0
.data:004560F6                 db 5, 50h, 2 dup(0), 80h, 2 dup(0), 50h, 2 dup(0), 80h
.data:00456101                 db 2 dup(0), 50h, 2 dup(0), 80h, 2 dup(0), 50h, 2 dup(0)
.data:0045610C                 db 80h, 2 dup(0), 50h, 2 dup(0), 80h, 2 dup(0), 50h, 2 dup(0)
.data:00456118                 db 80h, 2 dup(0), 50h, 2 dup(0), 80h, 2 dup(0), 50h, 2 dup(0)
.data:00456124                 db 80h, 0, 5, 55h, 2 dup(0), 80h, 5 dup(0), 80h, 5 dup(0)
.data:00456136                 db 80h, 5 dup(0), 80h, 5 dup(0), 0Ch dup(0AAh), 80h, 5 dup(0)
.data:00456154                 db 80h, 5 dup(0), 80h, 5 dup(0), 80h, 5 dup(0), 80h, 0
.data:00456168                 db 5, 54h, 2 dup(0), 80h, 0, 14h, 5, 2 dup(0), 80h, 2 dup(0)
.data:00456175                 db 5, 2 dup(0), 80h, 2 dup(0), 5, 2 dup(0), 80h, 2 dup(0)
.data:00456181                 db 14h, 2 dup(0), 80h, 2 dup(0), 50h, 2 dup(0), 80h, 0
.data:0045618C                 db 1, 40h, 2 dup(0), 80h, 0, 5, 3 dup(0), 80h, 0, 14h
.data:00456199                 db 3 dup(0), 80h, 0, 15h, 55h, 2 dup(0), 80h, 5 dup(0)
.data:004561A8                 db 80h, 5 dup(0), 80h, 5 dup(0), 80h, 5 dup(0), 0Ch dup(0AAh)
.data:004561C6                 db 80h, 5 dup(0), 80h, 5 dup(0), 80h, 5 dup(0), 80h, 5 dup(0)
.data:004561DE                 db 80h, 0, 5, 54h, 2 dup(0), 80h, 0, 14h, 5, 2 dup(0)
.data:004561EA                 db 80h, 2 dup(0), 5, 2 dup(0), 80h, 2 dup(0), 5, 2 dup(0)
.data:004561F6                 db 80h, 0, 1, 54h, 2 dup(0), 80h, 2 dup(0), 5, 2 dup(0)
.data:00456202                 db 80h, 2 dup(0), 5, 2 dup(0), 80h, 2 dup(0), 5, 2 dup(0)
.data:0045620E                 db 80h, 0, 14h, 5, 2 dup(0), 80h, 0, 5, 54h, 2 dup(0)
.data:0045621A                 db 80h, 5 dup(0), 80h, 5 dup(0), 80h, 5 dup(0), 80h, 5 dup(0)
.data:00456232                 db 0Ch dup(0AAh), 80h, 5 dup(0), 80h, 5 dup(0), 80h, 5 dup(0)
.data:00456250                 db 80h, 5 dup(0), 80h, 2 dup(0), 14h, 2 dup(0), 80h, 2 dup(0)
.data:0045625F                 db 54h, 2 dup(0), 80h, 0, 1, 54h, 2 dup(0), 80h, 0, 1
.data:0045626B                 db 54h, 2 dup(0), 80h, 0, 5, 14h, 2 dup(0), 80h, 0, 2 dup(14h)
.data:00456278                 db 2 dup(0), 80h, 0, 15h, 55h, 2 dup(0), 80h, 2 dup(0)
.data:00456283                 db 14h, 2 dup(0), 80h, 2 dup(0), 14h, 2 dup(0), 80h, 2 dup(0)
.data:0045628F                 db 55h, 2 dup(0), 80h, 5 dup(0), 80h, 5 dup(0), 80h, 5 dup(0)
.data:004562A4                 db 80h, 5 dup(0), 0Ch dup(0AAh), 80h, 5 dup(0), 80h, 5 dup(0)
.data:004562C2                 db 80h, 5 dup(0), 80h, 5 dup(0), 80h, 0, 15h, 55h, 2 dup(0)
.data:004562D4                 db 80h, 0, 14h, 3 dup(0), 80h, 0, 14h, 3 dup(0), 80h, 0
.data:004562E2                 db 14h, 3 dup(0), 80h, 0, 15h, 54h, 2 dup(0), 80h, 2 dup(0)
.data:004562EF                 db 5, 2 dup(0), 80h, 2 dup(0), 5, 2 dup(0), 80h, 2 dup(0)
.data:004562FB                 db 5, 2 dup(0), 80h, 0, 14h, 5, 2 dup(0), 80h, 0, 5, 54h
.data:00456308                 db 2 dup(0), 80h, 5 dup(0), 80h, 5 dup(0), 80h, 5 dup(0)
.data:0045631C                 db 80h, 5 dup(0), 0Ch dup(0AAh), 80h, 5 dup(0), 80h, 5 dup(0)
.data:0045633A                 db 80h, 5 dup(0), 80h, 5 dup(0), 80h, 0, 1, 54h, 2 dup(0)
.data:0045634C                 db 80h, 0, 5, 3 dup(0), 80h, 0, 14h, 3 dup(0), 80h, 0
.data:0045635A                 db 14h, 3 dup(0), 80h, 0, 15h, 54h, 2 dup(0), 80h, 0, 15h
.data:00456367                 db 5, 2 dup(0), 80h, 0, 14h, 5, 2 dup(0), 80h, 0, 14h
.data:00456373                 db 5, 2 dup(0), 80h, 0, 14h, 5, 2 dup(0), 80h, 0, 5, 54h
.data:00456380                 db 2 dup(0), 80h, 5 dup(0), 80h, 5 dup(0), 80h, 5 dup(0)
.data:00456394                 db 80h, 5 dup(0), 0Ch dup(0AAh), 80h, 5 dup(0), 80h, 5 dup(0)
.data:004563B2                 db 80h, 5 dup(0), 80h, 5 dup(0), 80h, 0, 15h, 55h, 2 dup(0)
.data:004563C4                 db 80h, 0, 14h, 5, 2 dup(0), 80h, 2 dup(0), 14h, 2 dup(0)
.data:004563D0                 db 80h, 2 dup(0), 14h, 2 dup(0), 80h, 2 dup(0), 50h, 2 dup(0)
.data:004563DC                 db 80h, 2 dup(0), 50h, 2 dup(0), 80h, 0, 1, 40h, 2 dup(0)
.data:004563E8                 db 80h, 0, 1, 40h, 2 dup(0), 80h, 0, 5, 3 dup(0), 80h
.data:004563F5                 db 0, 5, 3 dup(0), 80h, 5 dup(0), 80h, 5 dup(0), 80h, 5 dup(0)
.data:0045640C                 db 80h, 5 dup(0), 0Ch dup(0AAh), 80h, 5 dup(0), 80h, 5 dup(0)
.data:0045642A                 db 80h, 5 dup(0), 80h, 5 dup(0), 80h, 0, 5, 54h, 2 dup(0)
.data:0045643C                 db 80h, 0, 14h, 5, 2 dup(0), 80h, 0, 14h, 5, 2 dup(0)
.data:00456448                 db 80h, 0, 14h, 5, 2 dup(0), 80h, 0, 5, 54h, 2 dup(0)
.data:00456454                 db 80h, 0, 14h, 5, 2 dup(0), 80h, 0, 14h, 5, 2 dup(0)
.data:00456460                 db 80h, 0, 14h, 5, 2 dup(0), 80h, 0, 14h, 5, 2 dup(0)
.data:0045646C                 db 80h, 0, 5, 54h, 2 dup(0), 80h, 5 dup(0), 80h, 5 dup(0)
.data:0045647E                 db 80h, 5 dup(0), 80h, 5 dup(0), 0Ch dup(0AAh), 80h, 5 dup(0)
.data:0045649C                 db 80h, 5 dup(0), 80h, 5 dup(0), 80h, 5 dup(0), 80h, 0
.data:004564B0                 db 5, 54h, 2 dup(0), 80h, 0, 14h, 5, 2 dup(0), 80h, 0
.data:004564BC                 db 14h, 5, 2 dup(0), 80h, 0, 14h, 5, 2 dup(0), 80h, 0
.data:004564C8                 db 14h, 15h, 2 dup(0), 80h, 0, 5, 55h, 2 dup(0), 80h, 2 dup(0)
.data:004564D5                 db 5, 2 dup(0), 80h, 2 dup(0), 5, 2 dup(0), 80h, 2 dup(0)
.data:004564E1                 db 14h, 2 dup(0), 80h, 0, 5, 50h, 2 dup(0), 80h, 5 dup(0)
.data:004564F0                 db 80h, 5 dup(0), 80h, 5 dup(0), 80h, 5 dup(0), 6 dup(0AAh)

*/

char __cdecl gpu_sub_42E940(_BYTE *a1, char a2)
{
  char result; // al

  result = a2;
  if ( a2 )
  {
    if ( a2 == 1 )
    {
      *a1 = -1;
      a1[1] = -1;
      a1[2] = -1;
      return (_BYTE)a1 + 1;
    }
    else if ( a2 == 2 )
    {
      *a1 = 0;
      a1[1] = 0;
      a1[2] = -1;
      return (_BYTE)a1 + 1;
    }
  }
  else
  {
    *a1 = 0;
    a1[1] = 0;
    a1[2] = 0;
    return (_BYTE)a1 + 1;
  }
  return result;
}

BOOL __cdecl gpu_draw_text_on_screen(LPCSTR lpchText, void *a2)
{
  HDC DC; // edi
  HDC CompatibleDC; // ebx
  HBRUSH SolidBrush; // edi
  HPEN Pen; // esi
  HGDIOBJ v7; // [esp-4h] [ebp-6Ch]
  void *ppvBits; // [esp+10h] [ebp-58h] BYREF
  HGDIOBJ h; // [esp+14h] [ebp-54h]
  HGDIOBJ v10; // [esp+18h] [ebp-50h]
  HGDIOBJ v11; // [esp+1Ch] [ebp-4Ch]
  HGDIOBJ ho; // [esp+20h] [ebp-48h]
  HGDIOBJ v13; // [esp+24h] [ebp-44h]
  HGDIOBJ v14; // [esp+28h] [ebp-40h]
  struct tagRECT left; // [esp+2Ch] [ebp-3Ch] BYREF
  BITMAPINFO pbmi; // [esp+3Ch] [ebp-2Ch] BYREF

  left.left = 0;
  left.top = 0;
  left.right = 128;
  left.bottom = 96;
  DC = GetDC(nullptr);
  CompatibleDC = CreateCompatibleDC(DC);
  ReleaseDC(nullptr, DC);
  memset(&pbmi, 0, sizeof(pbmi));
  pbmi.bmiHeader.biSize = 40;
  pbmi.bmiHeader.biWidth = 128;
  pbmi.bmiHeader.biHeight = -96;
  pbmi.bmiHeader.biPlanes = 1;
  pbmi.bmiHeader.biBitCount = 24;
  pbmi.bmiHeader.biCompression = 0;
  ho = CreateDIBSection(CompatibleDC, &pbmi, 0, &ppvBits, nullptr, 0);
  h = SelectObject(CompatibleDC, ho);
  SolidBrush = CreateSolidBrush(0);
  v13 = SolidBrush;
  Pen = CreatePen(0, 0, 0xFF0000u);
  v14 = Pen;
  v10 = SelectObject(CompatibleDC, SolidBrush);
  v11 = SelectObject(CompatibleDC, Pen);
  SetTextColor(CompatibleDC, 0xFFu);
  SetBkColor(CompatibleDC, 0);
  Rectangle(CompatibleDC, left.left, left.top, left.right, left.bottom);
  InflateRect(&left, -3, -2);
  DrawTextA(CompatibleDC, lpchText, strlen(lpchText), &left, 0x25u);
  v7 = h;
  qmemcpy(a2, ppvBits, 0x9000u);
  SelectObject(CompatibleDC, v7);
  SelectObject(CompatibleDC, v10);
  SelectObject(CompatibleDC, v11);
  DeleteDC(CompatibleDC);
  DeleteObject(ho);
  DeleteObject(v13);
  return DeleteObject(v14);
}

_BYTE *__cdecl gpu_sub_42EB00(char *a1, int a2)
{
  char *v2; // esi
  char *v3; // edx
  int v4; // ebp
  int v5; // edi
  unsigned __int8 v6; // cl
  _BYTE *v7; // esi
  unsigned __int8 v8; // cl
  char v9; // cl
  int v10; // edx
  char *v11; // eax
  int v12; // edx
  _BYTE *v13; // eax
  _BYTE *result; // eax
  int v15; // edx
  _BYTE *v16; // eax

  v2 = a1 + 309;
  gpu_draw_text_on_screen("NO SAVE PIC", a1);
  v3 = &byte_4560D0[120 * a2];
  v4 = 20;
  do
  {
    v5 = 6;
    do
    {
      gpu_sub_42E940(v2, (unsigned __int8)*v3 >> 6);
      v7 = v2 + 3;
      gpu_sub_42E940(v7, (v6 >> 4) & 3);
      v7 += 3;
      gpu_sub_42E940(v7, (v8 >> 2) & 3);
      v7 += 3;
      gpu_sub_42E940(v7, v9 & 3);
      v2 = v7 + 3;
      v3 = (char *)(v10 + 1);
      --v5;
    }
    while ( v5 );
    v2 += 312;
    --v4;
  }
  while ( v4 );
  v11 = a1;
  v12 = 128;
  do
  {
    v11[36480] = 0;
    *v11 = 0;
    v13 = v11 + 1;
    v13[36480] = 0;
    *v13++ = 0;
    v13[36480] = -1;
    *v13 = -1;
    v11 = v13 + 1;
    --v12;
  }
  while ( v12 );
  result = a1;
  v15 = 96;
  do
  {
    result[381] = 0;
    *result = 0;
    v16 = result + 1;
    v16[381] = 0;
    *v16++ = 0;
    v16[381] = -1;
    *v16 = -1;
    result = v16 + 382;
    --v15;
  }
  while ( v15 );
  return result;
}

_BYTE *__cdecl gpu_sub_42EBF0(char *a1, int a2)
{
  char *v2; // esi
  char *v3; // edx
  int v4; // ebp
  int v5; // edi
  unsigned __int8 v6; // cl
  _BYTE *v7; // esi
  unsigned __int8 v8; // cl
  char v9; // cl
  int v10; // edx
  char *v11; // eax
  int v12; // edx
  _BYTE *v13; // eax
  _BYTE *result; // eax
  int v15; // edx
  _BYTE *v16; // eax

  v2 = a1 + 309;
  gpu_draw_text_on_screen("FREE SLOT", a1);
  v3 = &byte_4560D0[120 * a2];
  v4 = 20;
  do
  {
    v5 = 6;
    do
    {
      gpu_sub_42E940(v2, (unsigned __int8)*v3 >> 6);
      v7 = v2 + 3;
      gpu_sub_42E940(v7, (v6 >> 4) & 3);
      v7 += 3;
      gpu_sub_42E940(v7, (v8 >> 2) & 3);
      v7 += 3;
      gpu_sub_42E940(v7, v9 & 3);
      v2 = v7 + 3;
      v3 = (char *)(v10 + 1);
      --v5;
    }
    while ( v5 );
    v2 += 312;
    --v4;
  }
  while ( v4 );
  v11 = a1;
  v12 = 128;
  do
  {
    v11[36480] = 0;
    *v11 = 0;
    v13 = v11 + 1;
    v13[36480] = 0;
    *v13++ = 0;
    v13[36480] = -1;
    *v13 = -1;
    v11 = v13 + 1;
    --v12;
  }
  while ( v12 );
  result = a1;
  v15 = 96;
  do
  {
    result[381] = 0;
    *result = 0;
    v16 = result + 1;
    v16[381] = 0;
    *v16++ = 0;
    v16[381] = -1;
    *v16 = -1;
    result = v16 + 382;
    --v15;
  }
  while ( v15 );
  return result;
}

void __cdecl gpu_show_screen_pic(unsigned __int8 a1)
{
  void *v1; // ebx
  FILE *v2; // eax
  FILE *v3; // edi
  FILE *v4; // eax
  char Buffer[1024]; // [esp+0h] [ebp-400h] BYREF

  if ( GPUshowScreenPic )
  {
    v1 = malloc(0x9000u);
    sprintf(Buffer, "%s%s.%03d.pic", "sstates\\", ppf_default_filename, a1);
    v2 = fopen(Buffer, "rb");
    v3 = v2;
    if ( v2 )
    {
      fread(v1, 1u, 0x9000u, v2);
      fclose(v3);
    }
    else
    {
      sprintf(Buffer, "%s%s.%03d", "sstates\\", ppf_default_filename, a1);
      v4 = fopen(Buffer, "rb");
      if ( v4 )
      {
        fclose(v4);
        gpu_sub_42EB00((char *)v1, a1);
      }
      else
      {
        gpu_sub_42EBF0((char *)v1, a1);
      }
    }
    GPUshowScreenPic(v1);
    free(v1);
  }
}