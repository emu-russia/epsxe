#include "pch.h"
char patch_game()
{
  FILE *v0; // eax
  FILE *v1; // esi
  size_t v2; // edi

  LOBYTE(v0) = auto_ppf_load;
  if ( auto_ppf_load )
  {
    if ( !strcmp(ppf_filename, "NULL") )
      sprintf(ppf_filename, "%s%s", "patches\\", byte_8B3D80);
    v0 = fopen(ppf_filename, "rb");
    v1 = v0;
    if ( v0 )
    {
      dbg_print(" * Patching game ... ");
      auto_ppf_load = 1;
      fseek(v1, 0, 2);
      v2 = ftell(v1);
      fseek(v1, 0, 0);
      dword_4FFC28 = (char *)malloc(v2);
      fread(dword_4FFC28, v2, 1u, v1);
      if ( !strncmp("PPF", dword_4FFC28, 3u) )
      {
        if ( dword_4FFC28[5] )
        {
          if ( dword_4FFC28[5] == 1 )
          {
            dbg_print("ppf file v.2.0 ");
            if ( !strncmp(".DIZ", &dword_4FFC28[v2 - 8], 4u) )
              sub_436B50(v2 - *(_DWORD *)&dword_4FFC28[v2 - 4] - 1122, (int)dword_4FFC28, 0x43Cu);
            else
              sub_436B50(v2 - 1084, (int)dword_4FFC28, 0x43Cu);
            LOBYTE(v0) = fclose(v1);
          }
          else
          {
            auto_ppf_load = 0;
            free(dword_4FFC28);
            fclose(v1);
            LOBYTE(v0) = dbg_print("unk ppf format.\n");
          }
        }
        else
        {
          dbg_print("ppf file v.1.0 ");
          sub_436B50(v2 - 56, (int)dword_4FFC28, 0x38u);
          LOBYTE(v0) = fclose(v1);
        }
      }
      else
      {
        auto_ppf_load = 0;
        free(dword_4FFC28);
        fclose(v1);
        LOBYTE(v0) = dbg_print("no ppf file.\n");
      }
    }
    else
    {
      auto_ppf_load = 0;
    }
  }
  return (char)v0;
}
