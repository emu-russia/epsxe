#include "pch.h"

static uint32_t op_jump_addr;
static uint32_t op_imm;
static uint32_t op_ofs;
static uint8_t op_rs;
static uint8_t op_rs_0;
static uint8_t op_rt;
static uint8_t op_rd;
static uint8_t op_sa;

void op_UNKNOWN()
{
  ui_error(
    "\nePSXe: Opcode [%02x-%08x] in PC [%08x] UNKNOWN [%08x:%03d:%d]\n",
    (unsigned int)cpu_opcode >> 26,
    cpu_opcode,
    *(uint32_t *)reg_pc - 4,
    frame_counter,
    scanline_counter,
    hw_update_counter);
}

void op_LB()
{
  unsigned int offset;
  int rt;
  int value;

  offset = (uint16_t)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_ofs = (uint16_t)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    offset = cpu_opcode | 0xFFFF0000;
    op_ofs = offset;
  }
  mem_hw_reg_read_byte(offset + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]);
  rt = (uint8_t)op_rt;
  value = (uint8_t)value;
  cpu_gpr[(uint8_t)op_rt] = (uint8_t)value;
  if ( (value & 0x80u) != 0 )
  {
    value |= 0xFFFFFF00;
    cpu_gpr[rt] = value;
  }
}

void op_LBU()
{
  unsigned int offset;
  uint8_t value;

  offset = (uint16_t)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_ofs = (uint16_t)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    offset = cpu_opcode | 0xFFFF0000;
    op_ofs = offset;
  }
  if ( (cpu_opcode & 0x1F0000) != 0 )
  {
    mem_hw_reg_read_byte(offset + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]);
    cpu_gpr[(uint8_t)op_rt] = value;
  }
  else
  {
    mem_hw_reg_read_byte(offset + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]);
  }
}

void op_LH()
{
  unsigned int offset;
  int rt;
  int value;

  offset = (uint16_t)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_ofs = (uint16_t)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    offset = cpu_opcode | 0xFFFF0000;
    op_ofs = offset;
  }
  LOWORD(value) = mem_read_half(offset + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]);
  rt = (uint8_t)op_rt;
  value = (uint16_t)value;
  cpu_gpr[(uint8_t)op_rt] = (uint16_t)value;
  if ( (value & 0x8000) != 0 )
  {
    value |= 0xFFFF0000;
    cpu_gpr[rt] = value;
  }
}

void op_LHU()
{
  unsigned int offset;
  int value;

  offset = (uint16_t)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_ofs = (uint16_t)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    offset = cpu_opcode | 0xFFFF0000;
    op_ofs = offset;
  }
  value = (uint16_t)mem_read_half(offset + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]);
  cpu_gpr[(uint8_t)op_rt] = value;
}

void op_LW()
{
  unsigned int offset;
  int value;

  offset = (uint16_t)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_ofs = (uint16_t)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    offset = cpu_opcode | 0xFFFF0000;
    op_ofs = offset;
  }
  if ((cpu_opcode & 0x1F0000) == 0) {
      mem_read_word(offset + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]);
  }
  else {
      value = mem_read_word(offset + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]);
      cpu_gpr[(uint8_t)op_rt] = value;
  }
}

void op_LWL()
{
  unsigned int offset;
  unsigned int addr;
  int value;

  offset = (uint16_t)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_ofs = (uint16_t)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    offset = cpu_opcode | 0xFFFF0000;
    op_ofs = offset;
  }
  addr = offset + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  value = mem_read_word(addr & 0xFFFFFFFC);
  if ( op_rt )
  {
    switch ( addr & 3 )
    {
      case 0u:
        value <<= 24;
        cpu_gpr[(uint8_t)op_rt] = value | cpu_gpr[(uint8_t)op_rt] & 0xFFFFFF;
        break;
      case 1u:
        value <<= 16;
        cpu_gpr[(uint8_t)op_rt] = value | (uint16_t)cpu_gpr[(uint8_t)op_rt];
        break;
      case 2u:
        value <<= 8;
        cpu_gpr[(uint8_t)op_rt] = value | (uint8_t)cpu_gpr[(uint8_t)op_rt];
        break;
      case 3u:
        cpu_gpr[(uint8_t)op_rt] = value;
        break;
    }
  }
}

void op_LWR()
{
  unsigned int offset;
  unsigned int addr;
  unsigned int value;

  offset = (uint16_t)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_ofs = (uint16_t)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    offset = cpu_opcode | 0xFFFF0000;
    op_ofs = offset;
  }
  addr = offset + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  value = mem_read_word(addr & 0xFFFFFFFC);
  if ( op_rt )
  {
    switch ( addr & 3 )
    {
      case 0u:
        cpu_gpr[(uint8_t)op_rt] = value;
        break;
      case 1u:
        value >>= 8;
        cpu_gpr[(uint8_t)op_rt] = value | cpu_gpr[(uint8_t)op_rt] & 0xFF000000;
        break;
      case 2u:
        value >>= 16;
        cpu_gpr[(uint8_t)op_rt] = value | cpu_gpr[(uint8_t)op_rt] & 0xFFFF0000;
        break;
      case 3u:
        value >>= 24;
        cpu_gpr[(uint8_t)op_rt] = value | cpu_gpr[(uint8_t)op_rt] & 0xFFFFFF00;
        break;
    }
  }
}

void op_LUI()
{
  int value;

  op_imm = (uint16_t)cpu_opcode;
  value = (uint16_t)cpu_opcode << 16;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  cpu_gpr[BYTE2(cpu_opcode) & 0x1F] = value;
}

void op_SB()
{
  unsigned int offset;

  offset = (uint16_t)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_ofs = (uint16_t)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    offset = cpu_opcode | 0xFFFF0000;
    op_ofs = offset;
  }
  mem_hw_reg_write_byte(offset + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F], cpu_gpr[BYTE2(cpu_opcode) & 0x1F]);
}

void op_SH()
{
  unsigned int offset;

  offset = (uint16_t)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_ofs = (uint16_t)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    offset = cpu_opcode | 0xFFFF0000;
    op_ofs = offset;
  }
  mem_write_half(offset + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F], cpu_gpr[BYTE2(cpu_opcode) & 0x1F]);
}

void op_SW()
{
  unsigned int offset;

  offset = (uint16_t)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_ofs = (uint16_t)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    offset = cpu_opcode | 0xFFFF0000;
    op_ofs = offset;
  }
  mem_write_word(offset + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F], cpu_gpr[BYTE2(cpu_opcode) & 0x1F]);
}

void op_SWL()
{
  unsigned int offset;
  unsigned int addr;
  unsigned int alignedAddr;
  int word;

  offset = (uint16_t)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_ofs = (uint16_t)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    offset = cpu_opcode | 0xFFFF0000;
    op_ofs = offset;
  }
  addr = offset + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  alignedAddr = addr & 0xFFFFFFFC;
  word = mem_read_word(addr & 0xFFFFFFFC);
  switch ( addr & 3 )
  {
    case 0u:
      mem_write_word(alignedAddr, HIBYTE(cpu_gpr[(uint8_t)op_rt]) | word & 0xFFFFFF00);
      break;
    case 1u:
      mem_write_word(alignedAddr, HIWORD(cpu_gpr[(uint8_t)op_rt]) | word & 0xFFFF0000);
      break;
    case 2u:
      mem_write_word(alignedAddr, ((unsigned int)cpu_gpr[(uint8_t)op_rt] >> 8) | word & 0xFF000000);
      break;
    case 3u:
      mem_write_word(alignedAddr, cpu_gpr[(uint8_t)op_rt]);
      break;
  }
}

void op_SWR()
{
  unsigned int offset;
  unsigned int addr;
  unsigned int alignedAddr;
  int word;

  offset = (uint16_t)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_ofs = (uint16_t)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    offset = cpu_opcode | 0xFFFF0000;
    op_ofs = offset;
  }
  addr = offset + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  alignedAddr = addr & 0xFFFFFFFC;
  word = mem_read_word(addr & 0xFFFFFFFC);
  switch ( addr & 3 )
  {
    case 0u:
      mem_write_word(alignedAddr, cpu_gpr[(uint8_t)op_rt]);
      break;
    case 1u:
      mem_write_word(alignedAddr, (cpu_gpr[(uint8_t)op_rt] << 8) | (uint8_t)word);
      break;
    case 2u:
      mem_write_word(alignedAddr, (cpu_gpr[(uint8_t)op_rt] << 16) | (uint16_t)word);
      break;
    case 3u:
      mem_write_word(alignedAddr, (cpu_gpr[(uint8_t)op_rt] << 24) | word & 0xFFFFFF);
      break;
  }
}

void op_ADDI()
{
  unsigned int offset;
  unsigned int value;

  offset = (uint16_t)cpu_opcode;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_imm = (uint16_t)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    offset = cpu_opcode | 0xFFFF0000;
    op_imm = offset;
  }
  value = offset + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  cpu_gpr[BYTE2(cpu_opcode) & 0x1F] = value;
}

void op_ADD()
{
  int rtValue;
  int value;

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  rtValue = cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  op_rd = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  value = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] + rtValue;
  cpu_gpr[(uint16_t)cpu_opcode >> 11] = value;
}

void op_SUB()
{
  int value;

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rd = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  value = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] - cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  cpu_gpr[(uint16_t)cpu_opcode >> 11] = value;
}

void op_ANDI()
{
  int value;

  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_imm = (uint16_t)cpu_opcode;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  value = (uint16_t)cpu_opcode & cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  cpu_gpr[BYTE2(cpu_opcode) & 0x1F] = value;
}

void op_AND()
{
  int rtValue;
  int value;

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  rtValue = cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  op_rd = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  value = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] & rtValue;
  cpu_gpr[(uint16_t)cpu_opcode >> 11] = value;
}

void op_NOR()
{
  int rtValue;
  int value;

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  rtValue = cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  op_rd = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  value = ~(cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] | rtValue);
  cpu_gpr[(uint16_t)cpu_opcode >> 11] = value;
}

void op_ORI()
{
  int value;

  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_imm = (uint16_t)cpu_opcode;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  value = (uint16_t)cpu_opcode | cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  cpu_gpr[BYTE2(cpu_opcode) & 0x1F] = value;
}

void op_OR()
{
  int rtValue;
  int value;

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  rtValue = cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  op_rd = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  value = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] | rtValue;
  cpu_gpr[(uint16_t)cpu_opcode >> 11] = value;
}

void op_XORI()
{
  int value;

  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_imm = (uint16_t)cpu_opcode;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  value = (uint16_t)cpu_opcode ^ cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  cpu_gpr[BYTE2(cpu_opcode) & 0x1F] = value;
}

void op_XOR()
{
  int rtValue;
  int value;

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  rtValue = cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  op_rd = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  value = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] ^ rtValue;
  cpu_gpr[(uint16_t)cpu_opcode >> 11] = value;
}

void op_SLTI()
{
  signed int imm;
  BOOL value;

  imm = (uint16_t)cpu_opcode;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_imm = (uint16_t)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    imm = cpu_opcode | 0xFFFF0000;
    op_imm = imm;
  }
  value = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] < imm;
  cpu_gpr[BYTE2(cpu_opcode) & 0x1F] = value;
}

void op_SLTIU()
{
  BOOL value;

  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_imm = (uint16_t)cpu_opcode;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  value = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] < (unsigned int)(uint16_t)cpu_opcode;
  cpu_gpr[BYTE2(cpu_opcode) & 0x1F] = value;
}

void op_SLT()
{
  int rtValue;
  int rd;

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  rtValue = cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  op_rd = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  rd = (uint16_t)cpu_opcode >> 11;
  cpu_gpr[rd] = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] < rtValue;
}

void op_SLTU()
{
  int64_t tmp;

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rd = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  LODWORD(tmp) = (uint16_t)cpu_opcode >> 11;
  HIDWORD(tmp) = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] < (unsigned int)cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  cpu_gpr[(uint32_t)tmp] = HIDWORD(tmp);
}

void op_SLL()
{
  char rd;

  rd = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rd = rd;
  op_sa = ((unsigned int)cpu_opcode >> 6) & 0x1F;
  if ( rd )
    cpu_gpr[(uint16_t)cpu_opcode >> 11] = cpu_gpr[BYTE2(cpu_opcode) & 0x1F] << (((unsigned int)cpu_opcode >> 6)
                                                                                      & 0x1F);
}

void op_SLLV()
{
  char shift;
  int value;

  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  shift = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rd = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  value = cpu_gpr[BYTE2(cpu_opcode) & 0x1F] << shift;
  cpu_gpr[(uint16_t)cpu_opcode >> 11] = value;
}

void op_SRL()
{
  unsigned int value;
  char rd;

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_sa = ((unsigned int)cpu_opcode >> 6) & 0x1F;
  value = (unsigned int)cpu_gpr[BYTE2(cpu_opcode) & 0x1F] >> op_sa;
  rd = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  op_rd = rd;
  cpu_gpr[(uint16_t)cpu_opcode >> 11] = value;
}

void op_SRLV()
{
  char shift;
  unsigned int value;

  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  shift = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rd = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  value = (unsigned int)cpu_gpr[BYTE2(cpu_opcode) & 0x1F] >> shift;
  cpu_gpr[(uint16_t)cpu_opcode >> 11] = value;
}

void op_SRA()
{
  int value;
  char rd;

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_sa = ((unsigned int)cpu_opcode >> 6) & 0x1F;
  value = cpu_gpr[BYTE2(cpu_opcode) & 0x1F] >> op_sa;
  rd = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  op_rd = rd;
  cpu_gpr[(uint16_t)cpu_opcode >> 11] = value;
}

void op_SRAV()
{
  char shift;
  int value;

  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  shift = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rd = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  value = cpu_gpr[BYTE2(cpu_opcode) & 0x1F] >> shift;
  cpu_gpr[(uint16_t)cpu_opcode >> 11] = value;
}

void op_MULT()
{
  int64_t product;

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  product = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] * (int64_t)cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  cpu_LO = (uint32_t)product;
  cpu_HI = (uint32_t)(product >> 32);
}

void op_MULTU()
{
  uint64_t product;

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  product = (unsigned int)cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]
          * (uint64_t)(unsigned int)cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  cpu_LO = (uint32_t)product;
  cpu_HI = (uint32_t)(product >> 32);
}

void op_DIV()
{
  int rt;
  int rtValue;
  int quotient;

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  rt = BYTE2(cpu_opcode) & 0x1F;
  rtValue = cpu_gpr[rt];
  if ( rtValue )
  {
    cpu_LO = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] / rtValue;
    quotient = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] / cpu_gpr[rt];
    cpu_HI = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] % cpu_gpr[rt];
  }
  else
  {
    cpu_HI = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
    cpu_LO = -1;
    dbg_print(" division sign by 0 \n");
  }
}

void op_DIVU()
{
  int rt;
  unsigned int rtValue;
  unsigned int quotient;

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  rt = BYTE2(cpu_opcode) & 0x1F;
  rtValue = cpu_gpr[rt];
  if ( rtValue )
  {
    cpu_LO = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] / rtValue;
    quotient = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] / (unsigned int)cpu_gpr[rt];
    cpu_HI = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] % (unsigned int)cpu_gpr[rt];
  }
  else
  {
    cpu_HI = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
    cpu_LO = -1;
    dbg_print(" division by 0 \n");
  }
}

void op_MFHI()
{
  char rd;

  rd = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  op_rd = rd;
  cpu_gpr[(uint16_t)cpu_opcode >> 11] = cpu_HI;
}

void op_MFLO()
{
  char rd;

  rd = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  op_rd = rd;
  cpu_gpr[(uint16_t)cpu_opcode >> 11] = cpu_LO;
}

void op_MTHI()
{
  unsigned int rs;

  rs = (unsigned int)cpu_opcode >> 21;
  LOBYTE(rs) = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rs_0 = rs;
  cpu_HI = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
}

void op_MTLO()
{
  unsigned int rs;

  rs = (unsigned int)cpu_opcode >> 21;
  LOBYTE(rs) = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rs_0 = rs;
  cpu_LO = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
}

void op_J()
{
  int target;

  op_jump_addr = cpu_opcode & 0x3FFFFFF;
  target = 4 * (cpu_opcode & 0x3FFFFFF);
  cpu_opcode = *(uint32_t *)(*(uint16_t *)reg_pc + mem_read_hooks[*(uint16_t *)&reg_pc[2]]);
  *(uint32_t *)reg_pc = target | *(uint32_t *)reg_pc & 0xF0000000;
  cpu_main_table[(unsigned int)cpu_opcode >> 26]();
  --hw_update_counter;
}

void op_JAL()
{
  int target;

  op_jump_addr = cpu_opcode & 0x3FFFFFF;
  target = 4 * (cpu_opcode & 0x3FFFFFF);
  cpu_opcode = *(uint32_t *)(*(uint16_t *)reg_pc + mem_read_hooks[*(uint16_t *)&reg_pc[2]]);
  cpu_gpr[31] = *(uint32_t *)reg_pc + 4;
  *(uint32_t *)reg_pc = target | *(uint32_t *)reg_pc & 0xF0000000;
  cpu_main_table[(unsigned int)cpu_opcode >> 26]();
  --hw_update_counter;
}

void op_JR()
{
  unsigned int rs;

  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  cpu_opcode = *(uint32_t *)(*(uint16_t *)reg_pc + mem_read_hooks[*(uint16_t *)&reg_pc[2]]);
  *(uint32_t *)reg_pc = cpu_gpr[rs];
  cpu_main_table[(unsigned int)cpu_opcode >> 26]();
  --hw_update_counter;
}

void op_JALR()
{
  int hook;
  int rd;
  unsigned int rs;

  hook = mem_read_hooks[*(uint16_t *)&reg_pc[2]];
  op_rd = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  rd = (uint16_t)cpu_opcode >> 11;
  rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  cpu_opcode = *(uint32_t *)(*(uint16_t *)reg_pc + hook);
  cpu_gpr[rd] = *(uint32_t *)reg_pc + 4;
  *(uint32_t *)reg_pc = cpu_gpr[rs];
  cpu_main_table[(unsigned int)cpu_opcode >> 26]();
  --hw_update_counter;
}

void op_BEQ()
{
  unsigned int offset;
  int rsValue;

  offset = (uint16_t)cpu_opcode;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_ofs = (uint16_t)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    offset = cpu_opcode | 0xFFFF0000;
    op_ofs = offset;
  }
  rsValue = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  if ( rsValue == cpu_gpr[BYTE2(cpu_opcode) & 0x1F] )
  {
    cpu_opcode = *(uint32_t *)(*(uint16_t *)reg_pc + mem_read_hooks[*(uint16_t *)&reg_pc[2]]);
    *(uint32_t *)reg_pc += 4 * offset;
    cpu_main_table[(unsigned int)cpu_opcode >> 26]();
    --hw_update_counter;
  }
}

void op_BNE()
{
  unsigned int offset;
  int rsValue;

  offset = (uint16_t)cpu_opcode;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_ofs = (uint16_t)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    offset = cpu_opcode | 0xFFFF0000;
    op_ofs = offset;
  }
  rsValue = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  if ( rsValue != cpu_gpr[BYTE2(cpu_opcode) & 0x1F] )
  {
    cpu_opcode = *(uint32_t *)(*(uint16_t *)reg_pc + mem_read_hooks[*(uint16_t *)&reg_pc[2]]);
    *(uint32_t *)reg_pc += 4 * offset;
    cpu_main_table[(unsigned int)cpu_opcode >> 26]();
    --hw_update_counter;
  }
}

void op_BGTZ()
{
  unsigned int offset;
  int rsValue;

  offset = (uint16_t)cpu_opcode;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_ofs = (uint16_t)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    offset = cpu_opcode | 0xFFFF0000;
    op_ofs = offset;
  }
  rsValue = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  if ( rsValue > 0 )
  {
    cpu_opcode = *(uint32_t *)(*(uint16_t *)reg_pc + mem_read_hooks[*(uint16_t *)&reg_pc[2]]);
    *(uint32_t *)reg_pc += 4 * offset;
    cpu_main_table[(unsigned int)cpu_opcode >> 26]();
    --hw_update_counter;
  }
}

void op_BLTZ()
{
  unsigned int offset;
  int rsValue;

  offset = (uint16_t)cpu_opcode;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_ofs = (uint16_t)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    offset = cpu_opcode | 0xFFFF0000;
    op_ofs = offset;
  }
  rsValue = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  if ( rsValue < 0 )
  {
    cpu_opcode = *(uint32_t *)(*(uint16_t *)reg_pc + mem_read_hooks[*(uint16_t *)&reg_pc[2]]);
    *(uint32_t *)reg_pc += 4 * offset;
    cpu_main_table[(unsigned int)cpu_opcode >> 26]();
    --hw_update_counter;
  }
}

void op_BLEZ()
{
  unsigned int offset;
  int rsValue;

  offset = (uint16_t)cpu_opcode;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_ofs = (uint16_t)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    offset = cpu_opcode | 0xFFFF0000;
    op_ofs = offset;
  }
  rsValue = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  if ( rsValue <= 0 )
  {
    cpu_opcode = *(uint32_t *)(*(uint16_t *)reg_pc + mem_read_hooks[*(uint16_t *)&reg_pc[2]]);
    *(uint32_t *)reg_pc += 4 * offset;
    cpu_main_table[(unsigned int)cpu_opcode >> 26]();
    --hw_update_counter;
  }
}

void op_BGEZ()
{
  unsigned int offset;
  int rsValue;

  offset = (uint16_t)cpu_opcode;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_ofs = (uint16_t)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    offset = cpu_opcode | 0xFFFF0000;
    op_ofs = offset;
  }
  rsValue = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  if ( rsValue >= 0 )
  {
    cpu_opcode = *(uint32_t *)(*(uint16_t *)reg_pc + mem_read_hooks[*(uint16_t *)&reg_pc[2]]);
    *(uint32_t *)reg_pc += 4 * offset;
    cpu_main_table[(unsigned int)cpu_opcode >> 26]();
    --hw_update_counter;
  }
}

void op_BLTZAL()
{
  unsigned int offset;
  int rsValue;

  offset = (uint16_t)cpu_opcode;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_ofs = (uint16_t)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    offset = cpu_opcode | 0xFFFF0000;
    op_ofs = offset;
  }
  rsValue = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  if ( rsValue < 0 )
  {
    cpu_opcode = *(uint32_t *)(*(uint16_t *)reg_pc + mem_read_hooks[*(uint16_t *)&reg_pc[2]]);
    cpu_gpr[31] = *(uint32_t *)reg_pc + 4;
    *(uint32_t *)reg_pc += 4 * offset;
    cpu_main_table[(unsigned int)cpu_opcode >> 26]();
    --hw_update_counter;
  }
}

void op_BGEZAL()
{
  unsigned int offset;
  int rsValue;

  offset = (uint16_t)cpu_opcode;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_ofs = (uint16_t)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    offset = cpu_opcode | 0xFFFF0000;
    op_ofs = offset;
  }
  rsValue = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  if ( rsValue >= 0 )
  {
    cpu_opcode = *(uint32_t *)(*(uint16_t *)reg_pc + mem_read_hooks[*(uint16_t *)&reg_pc[2]]);
    cpu_gpr[31] = *(uint32_t *)reg_pc + 4;
    *(uint32_t *)reg_pc += 4 * offset;
    cpu_main_table[(unsigned int)cpu_opcode >> 26]();
    --hw_update_counter;
  }
}

void op_MTC0()
{
  uint8_t rd;
  uint8_t rt;
  unsigned int value;
  int gprValue;
  int newValue;

  rd = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  rt = BYTE2(cpu_opcode) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rd = rd;
  if (rd == 14 || rd == 15 || rd == 8) {
      dbg_print("[%d] only read!!!\n", (uint16_t)cpu_opcode >> 11);
      return;
  }
  if ( rd == 13 )
  {
    value = cpu_gpr[rt];
    cop0_cause = value;
    if ( (value & 0x100) != 0 && (cop0_sr & 0x101) == 0x101 )
    {
LABEL_21:
      value = cop0_sr;
      if ( (cop0_sr & 0x101) == 0x101 )
      {
        value = cop0_sr & 0xFFFFFFC0;
        cop0_epc = *(uint32_t *)reg_pc;
        cop0_cause = 256;
        *(uint32_t *)reg_pc = 0x80000080;
        cop0_sr = cop0_sr & 0xFFFFFFC0 | (4 * (cop0_sr & 0xF));
      }
    }
  }
  else if ( rd == 12 )
  {
    value = cpu_gpr[rt];
    cop0_sr = value;
    if ( (cop0_cause & 0x100) != 0 )
    {
      value &= 0x101u;
      if ( value == 257 )
        goto LABEL_21;
    }
  }
  else
  {
    if ( rd == 3 )
    {
      if ( xenogears_cd_detected )
      {
        xenogears_cd_detected = 0;
        cpu_gpr[rt] |= 1u;
      }
      else
      {
        gprValue = cpu_gpr[rt];
        if ( cop0_bpc_value[0] != gprValue )
        {
          newValue = gprValue | 1;
          if ( cop0_bpc_value[0] == newValue )
            cpu_gpr[rt] = newValue;
        }
      }
    }
    cop0_regs[rd] = cpu_gpr[rt];
  }
}

void op_MFC0()
{
  int rt;

  op_rd = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  rt = BYTE2(cpu_opcode) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  cpu_gpr[rt] = cop0_regs[(uint16_t)cpu_opcode >> 11];
}

static void op_RFE()
{
  unsigned int sr;
  int newSr;

  sr = cop0_sr;
  if ( (cop0_sr & 1) != 0 )
    sr = cop0_sr | 4;
  newSr = ((uint8_t)sr ^ (uint8_t)(sr >> 2)) & 0xF ^ sr;
  cop0_sr = newSr;
}

void op_SWC2()
{
  unsigned int data_register;

  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_ofs = (uint16_t)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
    op_ofs = cpu_opcode | 0xFFFF0000;
  data_register = gte_read_data_register(BYTE2(cpu_opcode) & 0x1F);
  mem_write_word(op_ofs + cpu_gpr[(uint8_t)op_rs], data_register);
}

void op_LWC2()
{
  unsigned int offset;
  int word;

  offset = (uint16_t)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_ofs = (uint16_t)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    offset = cpu_opcode | 0xFFFF0000;
    op_ofs = offset;
  }
  word = mem_read_word(offset + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]);
  {
    GTE_REG data_reg;
    data_reg.u32 = (uint32_t)word;
    gte_write_data_register(op_rt, data_reg);
  }
}

void op_SYSCALL()
{
  unsigned int srMask;

  cop0_epc = *(uint32_t *)reg_pc - 4;
  srMask = cop0_sr & 0xFFFFFFC0;
  cop0_cause = 32;
  cop0_sr = cop0_sr & 0xFFFFFFC0 | (4 * (cop0_sr & 0xF));
  *(uint32_t *)reg_pc = 0x80000080;
}

void op_BREAK()
{
}

/* Decompiled globals (previously generated in src/_gen) */
unsigned char xenogears_cd_detected;
unsigned int cop0_regs[1];
unsigned int cop0_sr;
unsigned int cop0_cause;
unsigned int cop0_epc;
