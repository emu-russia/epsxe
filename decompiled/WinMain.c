#include "pch.h"
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    unsigned int v4; // kr04_4
    unsigned int v5; // edi
    int v6; // ebp
    int v7; // eax
    unsigned int v8; // eax
    CHAR v9; // cl
    CHAR v10; // cl
    CHAR v11; // bl
    CHAR v12; // [esp+Fh] [ebp-405h]
    int v13; // [esp+10h] [ebp-404h]
    DWORD v14[256]; // [esp+14h] [ebp-400h] BYREF

    v4 = strlen(lpCmdLine) + 1;
    v13 = 1;
    v5 = v4 - 1;
    v6 = 0;
    v12 = 0;
    v7 = 256;
    do
    {
        --v7;
        v14[0] = 0;
    } while (v7);
    v8 = 0;
    if (v4 == 1)
        goto LABEL_16;
    if (*lpCmdLine == 32)
    {
        while (v8 < v5)
        {
            v9 = lpCmdLine[++v8];
            if (v9 != 32)
                goto LABEL_7;
        }
    LABEL_16:
        sprintf(unk_8B4580, aNull);
        sprintf((char* const)byte_8B3180, aNull);
        sprintf((char* const)byte_8B3580, aNull);
        sprintf(byte_8B2580, aInternal);
        sprintf(unk_8B5180, aNull);
        sprintf((char* const)byte_8B4180, aDisabled);
        version_setting = 0;
        dword_50C36C = 1;
        dword_50C370 = 0;
        forcepad = 0;
        country_setting = 255;
        dword_50C37C = 1;
        dword_50C380 = 0;
        dword_45593C = 312;
        dword_455940 = 2171;
        unk_8B55A0 = 0;
        load_settings();
        parse_command_line_options(v13, (int)v14);
        sub_437030();
        select_cdrom_core();
        dbg_print(" * Running %s emulator version %1.1f.%d. %s\n", aEpsxe, 1.6, 0, &byte_45B8CC);
        if (strlen(&unk_8B55A0))
            load_cheat_file(&unk_8B55A0);
        epsxe_main_loop_runner();
    }
LABEL_7:
    if (v8 >= v5)
        goto LABEL_16;
    if (lpCmdLine[v8] == 34)
    {
        ++v8;
        v6 = 1;
    }
    v14[1] = &lpCmdLine[v8];
    v13 = 2;
    if (v8 >= v5)
        goto LABEL_16;
    while (1)
    {
        v10 = lpCmdLine[v8];
        if (v6 == 1)
        {
            if (v10 == 34 && v12 != 92)
                goto LABEL_21;
        }
        else if (v10 == 32 && v12 != 92)
        {
        LABEL_21:
            v6 = 0;
            lpCmdLine[v8] = 0;
            if (++v8 < v5)
            {
                if (lpCmdLine[v8] == 32)
                {
                    while (v8 < v5)
                    {
                        v11 = lpCmdLine[++v8];
                        if (v11 != 32)
                            goto LABEL_25;
                    }
                }
                else
                {
                LABEL_25:
                    if (v8 < v5)
                    {
                        if (lpCmdLine[v8] == 34)
                        {
                            ++v8;
                            v6 = 1;
                        }
                        v14[v13] = &lpCmdLine[v8];
                        v10 = lpCmdLine[v8];
                        if (v8 < v5)
                            ++v13;
                    }
                }
            }
            goto LABEL_15;
        }
        ++v8;
    LABEL_15:
        v12 = v10;
        if (v8 >= v5)
            goto LABEL_16;
    }
}