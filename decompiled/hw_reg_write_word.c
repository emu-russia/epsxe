#include "pch.h"
void __cdecl hw_reg_write_word(unsigned int a1, unsigned int a2)
{
  int v2; // eax
  unsigned int v3; // esi
  int v4; // ecx
  int v5; // edx
  int v6; // edi
  int v7; // ebx

  if ( a1 <= 0x1F801020 && a1 >= 0x1F801000 )
  {
    *(_DWORD *)&byte_516600[(unsigned __int16)a1] = a2;
    return;
  }
  if ( a1 <= 0x1F801138 && a1 >= 0x1F801100 )
  {
    rcnt_write_reg(a1, a2);
    return;
  }
  if ( a1 <= 0x1F801E0F && a1 >= 0x1F801C00 )
  {
    spu_write_register_cb(a1, (unsigned __int16)a2);
    spu_write_register_cb(a1 + 2, HIWORD(a2));
    return;
  }
  if ( a1 <= 0x1F8010B8 )
  {
    if ( a1 == 0x1F8010B8 )
    {
      dword_51650C = a2;
      if ( dword_5164D0[1] < 0 )
      {
        cdr_dma();
        dword_51650C = a2 & 0xFEFFFFFF;
        dma_assert_int(3u);
      }
    }
    else
    {
      switch ( a1 )
      {
        case 0x1F801040u:
          sio_write_data_byte(a1, a2);
          sio_write_data_byte(a1, SBYTE1(a2));
          sio_write_data_byte(a1, SBYTE2(a2));
          sio_write_data_byte(a1, SHIBYTE(a2));
          break;
        case 0x1F801060u:
          *(_DWORD *)&byte_516600[(unsigned __int16)a1] = a2;
          break;
        case 0x1F801070u:
          if ( *(_DWORD *)dword_4FD878 )
          {
            if ( (unsigned int)hw_update_counter < *(_DWORD *)dword_4FD870 )
            {
              *(_DWORD *)int_reg |= *(_DWORD *)dword_4FD878;
              *(_DWORD *)dword_4FD878 = 0;
            }
          }
          *(_DWORD *)int_reg &= a2 & int_mask;
          break;
        case 0x1F801074u:
          int_mask = a2;
          break;
        case 0x1F801080u:
        case 0x1F801090u:
        case 0x1F8010A0u:
        case 0x1F8010B0u:
          goto LABEL_32;
        case 0x1F801084u:
        case 0x1F801094u:
        case 0x1F8010A4u:
        case 0x1F8010B4u:
          goto LABEL_37;
        case 0x1F801088u:
          mdec_dma_control[0] = a2;
          if ( (dword_5164D0[0] & 8) != 0 )
          {
            mdec_dma_in_handler();
            mdec_dma_control[0] = a2 & 0xFEFFFFFF;
            dma_assert_int(0);
          }
          break;
        case 0x1F801098u:
          mdec_dma_status = a2;
          if ( dword_5164D0[0] < 0 )
          {
            mdec_decode();
            if ( !mdectiming )
            {
              mdec_dma_status = a2 & 0xFEFFFFFF;
              dma_assert_int(1u);
            }
          }
          break;
        case 0x1F8010A8u:
          *(_DWORD *)dword_516500 = a2;
          if ( (dword_5164D0[1] & 8) != 0 )
            gpu_dma();
          break;
        default:
          goto LABEL_51;
      }
    }
    return;
  }
  if ( a1 <= 0x1F8010E4 )
  {
    if ( a1 == 528486628 )
    {
LABEL_37:
      dword_5164E4[3 * ((unsigned __int8)a1 >> 4) - 24] = a2;
    }
    else
    {
      switch ( a1 )
      {
        case 0x1F8010C0u:
        case 0x1F8010D0u:
        case 0x1F8010E0u:
LABEL_32:
          mdec_dma_src[3 * ((unsigned __int8)a1 >> 4) - 24] = a2;
          break;
        case 0x1F8010C4u:
        case 0x1F8010D4u:
          goto LABEL_37;
        case 0x1F8010C8u:
          *(_DWORD *)dword_516518 = a2;
          if ( (*(_DWORD *)dword_5164D0 & 0x80000) != 0 )
          {
            spu_dma_cb();
            *(_DWORD *)dword_516518 = a2 & 0xFEFFFFFF;
            dma_assert_int(4u);
          }
          break;
        case 0x1F8010D8u:
          dword_516524 = a2;
          if ( ((unsigned int)&bios_image[37248] & *(_DWORD *)dword_5164D0) != 0 )
          {
            dword_516524 = a2 & 0xFEFFFFFF;
            dma_assert_int(5u);
          }
          break;
        default:
          goto LABEL_51;
      }
    }
    return;
  }
  if ( a1 > 0x1F801810 )
  {
    switch ( a1 )
    {
      case 0x1F801814u:
        gpu_writeStatus(a2);
        return;
      case 0x1F801820u:
        mdec_write_command(a2);
        return;
      case 0x1F801824u:
        mdec_handle_special_command(a2);
        return;
    }
LABEL_51:
    dump_log(console_log_handle, "REG %s [%08x] <- %08x sizeof(%d) (%08x)\n", "UNK", a1, a2, 4, *(_DWORD *)reg_pc);
    return;
  }
  if ( a1 == 528488464 )
  {
    gpu_writeData(a2);
    return;
  }
  if ( a1 != 528486632 )
  {
    if ( a1 == 528486640 )
    {
      *(_DWORD *)dword_5164D0 = a2;
      return;
    }
    if ( a1 == 528486644 )
    {
      dword_50BFC8 = a2 & 0xFFFFFF | dword_50BFC8 & ~(a2 | 0xFFFFFF);
      return;
    }
    goto LABEL_51;
  }
  *(_DWORD *)dword_516530 = a2;
  if ( (*(_DWORD *)dword_5164D0 & 0x8000000) != 0 )
  {
    v2 = dword_516528;
    v3 = dword_51652C;
    if ( *(_DWORD *)dword_516530 == 285212674 )
    {
      if ( dword_51652C )
      {
        v4 = dword_516528 - 4;
        v5 = dword_51652C;
        do
        {
          v6 = v4 & 0xFFFFFF;
          v7 = v2 & 0x1FFFFF;
          v2 -= 4;
          v4 -= 4;
          --v5;
          *(int *)((char *)ram + v7) = v6;
        }
        while ( v5 );
      }
      *(int *)((char *)&ram[1] + (v2 & 0x1FFFFF)) = 0xFFFFFF;
      if ( v3 <= 0x40 )
      {
        *(_DWORD *)dword_516530 = 268435458;
        dma_assert_int(6u);
      }
      else
      {
        byte_50C215 = 1;
      }
    }
    else if ( (*(_DWORD *)dword_516530 & 0x1000000) != 0 )
    {
      ui_error("DMA[6] mode NOT implemented (%08x)\n", *(_DWORD *)dword_516530);
    }
  }
}
