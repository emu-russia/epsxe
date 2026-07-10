#include "pch.h"
BOOL __cdecl draw_text_on_screen(LPCSTR lpchText, void *a2)
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
