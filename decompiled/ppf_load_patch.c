#include "pch.h"
char ppf_load_patch()
{
  FILE *v0; // eax
  FILE *v1; // esi
  size_t v2; // edi

  LOBYTE(v0) = ppf_enabled;
  if ( ppf_enabled )
  {
    if ( !strcmp(ppf_filename, "NULL") )
      sprintf(ppf_filename, "%s%s", "patches\\", ppf_default_filename);
    v0 = fopen(ppf_filename, "rb");
    v1 = v0;
    if ( v0 )
    {
      dbg_print(" * Patching game ... ");
      ppf_enabled = 1;
      fseek(v1, 0, 2);
      v2 = ftell(v1);
      fseek(v1, 0, 0);
      ppf_file_data = (char *)malloc(v2);
      fread(ppf_file_data, v2, 1u, v1);
      if ( !strncmp("PPF", ppf_file_data, 3u) )
      {
        if ( ppf_file_data[5] )
        {
          if ( ppf_file_data[5] == 1 )
          {
            dbg_print("ppf file v.2.0 ");
            if ( !strncmp(".DIZ", &ppf_file_data[v2 - 8], 4u) )
              ppf_parse_and_build(v2 - *(_DWORD *)&ppf_file_data[v2 - 4] - 1122, (int)ppf_file_data, 0x43Cu);
            else
              ppf_parse_and_build(v2 - 1084, (int)ppf_file_data, 0x43Cu);
            LOBYTE(v0) = fclose(v1);
          }
          else
          {
            ppf_enabled = 0;
            free(ppf_file_data);
            fclose(v1);
            LOBYTE(v0) = dbg_print("unk ppf format.\n");
          }
        }
        else
        {
          dbg_print("ppf file v.1.0 ");
          ppf_parse_and_build(v2 - 56, (int)ppf_file_data, 0x38u);
          LOBYTE(v0) = fclose(v1);
        }
      }
      else
      {
        ppf_enabled = 0;
        free(ppf_file_data);
        fclose(v1);
        LOBYTE(v0) = dbg_print("no ppf file.\n");
      }
    }
    else
    {
      ppf_enabled = 0;
    }
  }
  return (char)v0;
}
