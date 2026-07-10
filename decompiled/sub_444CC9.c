#include "pch.h"
int *__cdecl sub_444CC9(DWORD NumberOfBytesWritten)
{
  int v1; // ecx
  int *result; // eax
  int v3; // esi
  char *v4; // edi
  const char **v5; // esi
  HANDLE StdHandle; // eax
  const char *v7; // [esp-14h] [ebp-1B8h]
  DWORD v8; // [esp-10h] [ebp-1B4h]
  DWORD *p_NumberOfBytesWritten; // [esp-Ch] [ebp-1B0h]
  int v10; // [esp-8h] [ebp-1ACh]
  CHAR Filename[260]; // [esp+0h] [ebp-1A4h] BYREF
  char Destination[160]; // [esp+104h] [ebp-A0h] BYREF
  int savedregs; // [esp+1A4h] [ebp+0h] BYREF

  v1 = 0;
  result = dword_45AF90;
  do
  {
    if ( NumberOfBytesWritten == *result )
      break;
    result += 2;
    ++v1;
  }
  while ( result < dword_45B020 );
  v3 = 2 * v1;
  if ( NumberOfBytesWritten == dword_45AF90[2 * v1] )
  {
    result = (int *)dword_4FFA6C;
    if ( dword_4FFA6C == 1 || !dword_4FFA6C && dword_458C64 == 1 )
    {
      v5 = (const char **)&(&off_45AF94)[v3];
      v10 = 0;
      p_NumberOfBytesWritten = &NumberOfBytesWritten;
      v8 = strlen(*v5);
      v7 = *v5;
      StdHandle = GetStdHandle(0xFFFFFFF4);
      return (int *)WriteFile(StdHandle, v7, v8, &NumberOfBytesWritten, nullptr);
    }
    else if ( NumberOfBytesWritten != 252 )
    {
      if ( !GetModuleFileNameA(nullptr, Filename, 0x104u) )
        strcpy(Filename, "<program name unknown>");
      v4 = Filename;
      if ( strlen(Filename) + 1 > 0x3C )
      {
        v4 = (char *)&savedregs + strlen(Filename) - 479;
        strncpy(v4, "...", 3u);
      }
      strcpy(Destination, "Runtime Error!\n\nProgram: ");
      strcat(Destination, v4);
      strcat(Destination, "\n\n");
      strcat(Destination, (&off_45AF94)[v3]);
      return (int *)__crtMessageBoxA(Destination, "Microsoft Visual C++ Runtime Library", 73744);
    }
  }
  return result;
}
