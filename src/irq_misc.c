/*
 * irq_misc.c — small interrupt/memory helpers that were decompiled as
 * separate procedures and never assembled into a module.
 */
#include "pch.h"

void irq_cdrom_assert_int()
{
    *(_DWORD *)int_reg |= 4u;
}

void irq_sio_assert_int()
{
    *(_DWORD *)int_reg |= 0x80u;
}

char __cdecl irq_rcnt_write_reg(unsigned __int16 a1, int a2)
{
    int v2; // eax
    bool v3; // zf

    LOBYTE(v2) = a1;
    switch (a1)
    {
    case 0x1100u:
    case 0x1110u:
    case 0x1120u:
    case 0x1130u:
        if (!a2)
        {
            v2 = 16 * ((a1 >> 4) & 3);
            *(int *)((char *)rcnt_counter + v2) = 0;
        }
        break;
    case 0x1104u:
    case 0x1114u:
    case 0x1124u:
    case 0x1134u:
        v2 = 16 * ((a1 >> 4) & 3);
        *(int *)((char *)rcnt_counter + v2) = 0;
        *(int *)((char *)rcnt_mode + v2) = a2 & 0x3FF | 0x1000;
        if ((a2 & 8) != 0 && *(int *)((char *)rcnt_target + v2))
        {
            *(int *)((char *)rcnt_compare + v2) = (unsigned __int16)*(int *)((char *)rcnt_target + v2);
            v3 = a1 == 4388;
        }
        else
        {
            *(int *)((char *)rcnt_compare + v2) = 0xFFFF;
            v3 = a1 == 4388;
        }
        goto LABEL_13;
    case 0x1108u:
    case 0x1118u:
    case 0x1128u:
    case 0x1138u:
        v2 = 16 * ((a1 >> 4) & 3);
        *(int *)((char *)rcnt_target + v2) = a2;
        if ((*((_BYTE *)rcnt_mode + v2) & 8) != 0 && a2)
            *(int *)((char *)rcnt_compare + v2) = (unsigned __int16)a2;
        else
            *(int *)((char *)rcnt_compare + v2) = 0xFFFF;
        v3 = a1 == 4392;
    LABEL_13:
        if (v3)
        {
            LOBYTE(v2) = parasite_eve_cheat;
            if (parasite_eve_cheat)
                rcnt2_compare = (unsigned int)rcnt2_compare >> 2;
        }
        break;
    default:
        return v2;
    }
    return v2;
}

int __cdecl irq_freeze(const char *a1, int a2)
{
    char Buffer[3]; // [esp+4h] [ebp-40h] BYREF
    int v4; // [esp+7h] [ebp-3Dh]

    sprintf(Buffer, "%s", a1);
    v4 = 668;
    gzwrite(a2, (unsigned __int8 *)Buffer, 7u);
    gzwrite(a2, (unsigned __int8 *)sio_irq_timeout, 4u);
    gzwrite(a2, (unsigned __int8 *)sio_irq_delay_time, 4u);
    gzwrite(a2, (unsigned __int8 *)sio_irq_pending, 4u);
    sio_transfer_timeout_saved = sio_transfer_timeout;
    sio_pending_time_saved = sio_scheduled_transfer_timeout;
    sio_transfer_pending_saved[0] = sio_transfer_pending;
    return gzwrite(a2, (unsigned __int8 *)int_reg, 0x290u);
}

int mem_clear_memory()
{
    memset(ram, 0, 0x200000u);
    memset(pio_mem, 0xFFu, 0x20000u);
    memset(dcache, 0, sizeof(dcache));
    return 0;
}

void memset32(void *dst, unsigned int value, unsigned int count)
{
    unsigned int *p = (unsigned int *)dst;
    while (count--)
        *p++ = value;
}

/* ASPI support: wnaspi32.lib is not shipped with modern SDKs, so load the
 * function from the system DLL at runtime. */
DWORD GetASPI32SupportInfo(void)
{
    static DWORD(WINAPI *real)(void) = NULL;
    if (!real)
    {
        HMODULE m = LoadLibraryA("WNASPI32.DLL");
        if (m)
            real = (DWORD(WINAPI *)(void))GetProcAddress(m, "GetASPI32SupportInfo");
    }
    if (!real)
        return 0;
    return real();
}
