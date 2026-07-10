#include "pch.h"
void __noreturn epsxe_main_loop_runner()
{
  if ( create_window_flag )
    create_main_window();
  alloc_console();
  dbg_print(" * Running %s emulator version %1.1f.%d. %s\n", "ePSXe", 1.6, 0, &byte_45B8CC);
  old_auto_ppf_load = auto_ppf_load;
  while ( 1 )
  {
    auto_ppf_load = 0;
    init_memory_handlers();
    clear_memory();
    load_cheats();
    load_bios();
    clear_regs();
    select_plugins_backend();
    sub_42ACC0();
    if ( !dword_50C380 )
    {
      if ( dword_50C37C == 3 || dword_50C37C == 1 )
        cdrom_init_cb();
      cdrom_detect_region();
      if ( dword_50C37C == 1 )
        cdrom_subchannel_read_cb();
      gpu_load_plugin();
      sub_42E3A0();
      spu_init_cb();
      nullsub_1();
    }
    sub_42C830();
    sub_41BB90();
    sio_reset();
    reopen_console_log();
    nullsub_1();
    sub_42DCF0();
    sub_429240();
    if ( dword_50C36C == 1 )
      sub_428270();
    dword_50C380 = 0;
    auto_ppf_load = old_auto_ppf_load;
    patch_game();
    sub_42B1E0();
    if ( dword_50C37C == 1 || dword_50C37C == 3 )
    {
      if ( fastboot )
        reg_pc = dword_50C35C;
    }
    else if ( dword_50C37C == 4 )
    {
      if ( BYTE1(dword_4F831C) )
        epsxe_load_demo("libps.exe");
      if ( touch_demo_file() )
        epsxe_load_zip();
    }
    get_tick_count();
    if ( dword_50C36C )
    {
      if ( dword_50C36C == 1 )
        sub_429140();
      else
        nullsub_1();
    }
    else
    {
      sub_42B2A0();
    }
  }
}
