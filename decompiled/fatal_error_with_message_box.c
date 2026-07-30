#include "pch.h"
void fatal_error_with_message_box(const char *Format, ...)
{
    char *buf;
    va_list arg_list;

    va_start(arg_list, Format);
    sio_memcard_both_save();
    net_close();
    nullsub_1();
    if (spu_destroy_cb)
        spu_destroy_cb(0);
    if (dynarec_active == 1)
        dynarec_deinit();
    buf = (char *)malloc(0x8000u);
    vsprintf(buf, Format, arg_list);
    fprintf(stdout, "%s", buf);
    MessageBoxA(nullptr, buf, "Error running ePSXe", 0x10u);
    free(buf);
    gpu_destroy();
    if (cdrom_deinit_cb)
        cdrom_deinit_cb(0);
    ppf_free();
    check_and_clear_console_log_flush_pending();
    if (error_log_file)
        fclose(error_log_file);
    free_console();
    exit(1);
}