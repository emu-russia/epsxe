#include "pch.h"
int __cdecl sub_41FEB0(char *FileName, char *a2, LPVOID *a3, size_t *a4)
{
  FILE *v4; // eax
  FILE *v5; // ebp
  int v6; // esi
  char *v8; // esi
  char v9; // al
  void *v11; // eax
  int v12; // eax
  int v13; // [esp-8h] [ebp-ACh]
  LPVOID v14; // [esp+Ch] [ebp-98h] BYREF
  LPVOID lpMem; // [esp+10h] [ebp-94h] BYREF
  int v16; // [esp+14h] [ebp-90h] BYREF
  __int16 v17; // [esp+18h] [ebp-8Ch]
  __int16 v18; // [esp+1Ah] [ebp-8Ah]
  __int16 v19; // [esp+1Ch] [ebp-88h]
  __int16 v20; // [esp+1Eh] [ebp-86h]
  int v21[2]; // [esp+2Ch] [ebp-78h] BYREF
  __int16 v22; // [esp+34h] [ebp-70h]
  size_t Size; // [esp+44h] [ebp-60h]
  char ArgList[32]; // [esp+50h] [ebp-54h] BYREF
  int v25[13]; // [esp+70h] [ebp-34h] BYREF

  lpMem = nullptr;
  v14 = nullptr;
  *(_DWORD *)::ArgList = sub_4201C0(FileName);
  v4 = fopen(FileName, Mode);
  v5 = v4;
  if ( v4 )
  {
    v6 = sub_420C70(v4, (int)&ElementCount);
    if ( v6 )
    {
      sub_420210(aErrorInZipfile, ::ArgList[0]);
    }
    else
    {
      v6 = sub_420AF0(v5, (int)&v16);
      if ( v6 )
      {
        sub_420210(aErrorReadingEn, ::ArgList[0]);
      }
      else
      {
        if ( v17 != v18 || v19 != v20 || !v20 )
        {
          v6 = -1;
          sub_420210(aUnsupportedZip, ::ArgList[0]);
          goto LABEL_13;
        }
        v8 = ArgList;
        do
        {
          v13 = *a2++;
          v9 = toupper(v13);
          *v8++ = v9;
        }
        while ( v9 );
        v6 = sub_420500(v5, (int)ArgList, (int)&v16, (int)v25);
        if ( v6 )
        {
          sub_420210(aCouldNotFindSI, (char)ArgList);
        }
        else
        {
          v6 = sub_4203E0(v5, (int)v25, (int)v21, &byte_4F8350);
          if ( !v6 )
          {
            if ( v22 )
            {
              if ( v22 == 8 )
              {
                v6 = sub_420310(v5, (int)v25, (int)v21, (int)&lpMem);
                if ( v6 )
                {
                  sub_420210(aCouldNotCreate_0, ::ArgList[0]);
                  goto LABEL_13;
                }
                dword_576980 = (int)lpMem;
                v11 = malloc(Size);
                v14 = v11;
                if ( !v11 )
                {
                  sub_420210(aCouldnTAllocat, ::ArgList[0]);
                  v6 = -1;
                  goto LABEL_13;
                }
                dword_4FC454 = (int)v11;
                dword_576984 = malloc(0x8000u);
                if ( !dword_576984 )
                {
                  sub_420210(aCouldNotCreate, ::ArgList[0]);
                  v6 = -1;
                  goto LABEL_13;
                }
                v12 = zip_inflate();
                v6 = v12;
                if ( v12 )
                {
                  sub_420210(aErrorDInflatin, v12);
                  goto LABEL_13;
                }
              }
            }
            else
            {
              v6 = sub_420310(v5, (int)v25, (int)v21, (int)&v14);
              if ( v6 )
              {
                sub_420210(aCouldnTExtract, ::ArgList[0]);
                goto LABEL_13;
              }
            }
            *a3 = v14;
            *a4 = Size;
            v14 = nullptr;
            goto LABEL_13;
          }
          sub_420210(aErrorReadingLo, ::ArgList[0]);
        }
      }
    }
LABEL_13:
    fclose(v5);
    goto LABEL_14;
  }
  sub_420210(aCouldNotOpenZi, (char)FileName);
  v6 = -1;
LABEL_14:
  if ( lpMem )
    free(lpMem);
  if ( v14 )
    free(v14);
  if ( dword_576984 )
  {
    free(dword_576984);
    dword_576984 = nullptr;
  }
  return v6;
}
