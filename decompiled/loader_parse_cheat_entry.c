#include "pch.h"
char __cdecl loader_parse_cheat_entry(const char *a1, char *Buffer)
{
  int v2; // edi
  CHEAT_DB_ENTRY *i; // ebp
  signed __int8 mdectiming; // cl
  signed __int8 dword_50C374; // cl
  signed __int8 forcepad; // cl
  char *text; // eax

  if ( noauto )
    return 0;
  v2 = 0;
  if ( !cheat_entries_count )
    return 0;
  for ( i = cheat_db; strcmp(a1, i->gameid); ++i )
  {
    if ( ++v2 >= (unsigned int)cheat_entries_count )
      return 0;
  }
  mdectiming = cheat_db[v2].mdectiming;
  if ( mdectiming != -1 )
    ::mdectiming = mdectiming;
  dword_50C374 = cheat_db[v2].dword_50C374;
  if ( dword_50C374 != -1 )
    ::dword_50C374 = dword_50C374;
  if ( cheat_db[v2].forcespu != 0xFF )
    forcespu = cheat_db[v2].forcespu;
  forcepad = cheat_db[v2].forcepad;
  if ( forcepad != -1 )
    ::forcepad = forcepad;
  if ( cheat_db[v2].byte_455946 != 0xFF )
    byte_455946 = cheat_db[v2].byte_455946;
  if ( cheat_db[v2].parasite_eve_cheat != 0xFF )
    parasite_eve_cheat = cheat_db[v2].parasite_eve_cheat;
  if ( cheat_db[v2].byte_455FA4 != 0xFF )
    cd_inc = cheat_db[v2].byte_455FA4;
  if ( cheat_db[v2].byte_4F75AA != 0xFF )
    byte_4F75AA = cheat_db[v2].byte_4F75AA;
  if ( cheat_db[v2].nocdstatus != 0xFF )
    nocdstatus = cheat_db[v2].nocdstatus;
  if ( cheat_db[v2].byte_4FC4E6 != 0xFF )
    byte_4FC4E6 = cheat_db[v2].byte_4FC4E6;
  text = cheat_db[v2].text;
  if ( !strcmp("NULL", text) )
    return 0;
  sprintf(Buffer, "%s", text);
  return 1;
}
