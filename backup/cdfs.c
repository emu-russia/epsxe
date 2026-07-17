//.data:004FD9E8 byte_4FD9E8     db ?                    ; DATA XREF: sub_436A00+B↑o
//.data:004FD9E8                                         ; sub_436A00+33↑o ...
//.data:004FD9E9                 align 10h
//.data:004FD9F0 ; char byte_4FD9F0[4088]
//.data:004FD9F0 byte_4FD9F0     db 0FF8h dup(?)         ; DATA XREF: sub_436A00+4E↑r
//.data:004FE9E8 byte_4FE9E8     db 800h dup(?)          ; DATA XREF: sub_436910+1↑o
//.data:004FE9E8                                         ; sub_436910+1E↑o ...
//.data:004FF1E8 byte_4FF1E8     db 800h dup(?)          ; DATA XREF: sub_436910+32↑o

int __cdecl cdfs_read_le32(unsigned __int8 *a1)
{
  return *a1 | ((a1[1] | ((a1[2] | ((char)a1[3] << 8)) << 8)) << 8);
}

unsigned int __cdecl cdfs_read_data(int a1, int a2, unsigned int a3, void *a4)
{
  unsigned __int8 v5; // [esp+8h] [ebp-126Ch]
  unsigned __int8 v6; // [esp+Ch] [ebp-1268h]
  unsigned __int8 v7; // [esp+10h] [ebp-1264h]
  _BYTE v8[4704]; // [esp+14h] [ebp-1260h] BYREF

  v7 = (a1 + 150) % 0x4Bu;
  v6 = (a1 + 150) / 0x4Bu / 0x3C;
  v5 = (a1 + 150) / 0x4Bu % 0x3C;
  if ( loaded_file_type == 3 )
  {
    iso_read_data(v6, v5, v7, (int)v8);
  }
  else if ( loaded_file_type == 1 )
  {
    cdrom_read_data_cb(v6, v5, v7, v8);
  }
  qmemcpy(a4, &v8[a2], a3);
  return a3;
}

char *sub_436910()
{
  int le32; // esi

  cdfs_read_data(16, 24, 0x800u, byte_4FE9E8);
  le32 = cdfs_read_le32((unsigned __int8 *)&byte_4FE9E8[158]);
  cdfs_read_data(le32, 24, 0x800u, byte_4FE9E8);
  cdfs_read_data(le32 + 1, 24, 0x800u, byte_4FF1E8);
  return byte_4FE9E8;
}

int *__cdecl sub_436960(const char *a1, int *a2, int **a3)
{
  int v3; // ebp
  char *v4; // edi
  int *result; // eax

  v3 = 0;
  while ( 1 )
  {
    v4 = &byte_4FE9E8[v3];
    if ( !byte_4FE9E8[v3] )
    {
LABEL_8:
      *a2 = 0;
      return a2;
    }
    v3 += (unsigned __int8)byte_4FE9E8[v3];
    if ( (unsigned __int8)v4[33] >= 2u && (!strncmp(a1, v4 + 33, 0xCu) || v4[44] == 59 && !strncmp(a1, v4 + 33, 0xBu)) )
      break;
    if ( v3 >= 4096 )
      goto LABEL_8;
  }
  *a2 = cdfs_read_le32((unsigned __int8 *)v4 + 2);
  result = (int *)cdfs_read_le32((unsigned __int8 *)v4 + 10);
  *a3 = result;
  return result;
}

unsigned __int8 __cdecl sub_436A00(int a1, int a2, char *Buffer, int *a4, int **a5)
{
  int v5; // esi
  unsigned __int8 result; // al
  int v7; // edx
  int v8; // ecx
  _DWORD v9[3]; // [esp+4h] [ebp-100h] BYREF
  char v10; // [esp+10h] [ebp-F4h]
  char v11; // [esp+11h] [ebp-F3h]

  v5 = 0;
  result = cdfs_read_data(a1, 24, 0x800u, byte_4FD9E8);
  if ( a2 > 8 )
  {
    do
    {
      result = byte_4FD9E8[v5];
      if ( result == 83 )
        break;
      if ( result == 115 )
        break;
      if ( byte_4FD9F0[v5] == 46 )
        break;
      result = ++v5 + 8;
    }
    while ( v5 + 8 < a2 );
  }
  if ( v5 + 8 == a2 )
  {
    *a4 = 0;
  }
  else
  {
    v7 = *(_DWORD *)&byte_4FD9E8[v5 + 4];
    v9[0] = *(_DWORD *)&byte_4FD9E8[v5];
    v8 = *(_DWORD *)&byte_4FD9E8[v5 + 8];
    v9[1] = v7;
    LOBYTE(v7) = byte_4FD9E8[v5 + 12];
    v9[2] = v8;
    v10 = v7;
    v11 = 0;
    sprintf(Buffer, "%s", (const char *)v9);
    return (unsigned __int8)sub_436960((const char *)v9, a4, a5);
  }
  return result;
}

unsigned __int8 __cdecl sub_436AF0(char *Buffer)
{
  int v2; // [esp+0h] [ebp-8h] BYREF
  int v3; // [esp+4h] [ebp-4h] BYREF

  sub_436910();
  sub_436960("SYSTEM.CNF;1", &v2, (int **)&v3);
  if ( v2 )
    return sub_436A00(v2, v3, Buffer, &v3, (int **)&Buffer);
  else
    return sprintf(Buffer, "SLUS_999.99");
}