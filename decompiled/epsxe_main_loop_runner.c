#include "pch.h"
void __noreturn epsxe_main_loop_runner()
{
  if ( create_window_flag )
    create_main_window();
  alloc_console();
  dbg_print(" * Running %s emulator version %1.1f.%d. %s\n", "ePSXe", 1.6, 0, &byte_45B8CC);
  old_auto_ppf_load = ppf_enabled;
  while ( 1 )
  {
    ppf_enabled = 0;
    mem_init_memory_handlers();
    mem_clear_memory();
    loader_load_cheats();
    loader_load_bios();
    cpu_clear_regs();
    select_plugins_backend();
    clear_hw_regs();
    if ( !reset_flag )
    {
      if ( loaded_file_type == 3 || loaded_file_type == 1 )
        cdrom_init_cb();
      loader_cdrom_detect_region();
      if ( loaded_file_type == 1 )
        cdrom_subchannel_read_cb();
      gpu_load_plugin();
      gpu_sub_42E3A0();
      spu_init_cb();
      nullsub_1();
    }
    cdr_reset_controller();
    gte_clear_regs();
    sio_reset_all();
    reopen_console_log();
    nullsub_1();
    gpu_init_performance_counter();
    mdec_init();
    if ( dword_50C36C == 1 )
      dynarec_init();
    reset_flag = 0;
    ppf_enabled = old_auto_ppf_load;
    ppf_load_patch();
    cpu_load_bios_shell();
    if ( loaded_file_type == 1 || loaded_file_type == 3 )
    {
      if ( fastboot )
        *(_DWORD *)reg_pc = cpu_gpr[31];
    }
    else if ( loaded_file_type == 4 )
    {
      if ( BYTE1(active_mini_cheat_count) )
        loader_load_demo("libps.exe");
      if ( loader_touch_demo_file() )
        loader_load_zip();
    }
    get_tick_count();
    if ( dword_50C36C )
    {
      if ( dword_50C36C == 1 )
        dynarec_execute();
      else
        nullsub_1();
    }
    else
    {
      cpu_execute();
    }
  }
}
