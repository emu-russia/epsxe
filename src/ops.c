#include "pch.h"
void __noreturn op_UNKNOWN()
{
  ui_error(
    "\nePSXe: Opcode [%02x-%08x] in PC [%08x] UNKNOWN [%08x:%03d:%d]\n",
    (unsigned int)cpu_opcode >> 26,
    cpu_opcode,
    *(_DWORD *)reg_pc - 4,
    dword_50C360,
    dword_50C364,
    hw_update_counter);
}

int op_LB()
{
  unsigned int v0; // ecx
  int v1; // ecx
  int result; // eax

  v0 = (unsigned __int16)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  mem_hw_reg_read_byte(v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]);
  v1 = (unsigned __int8)op_rt;
  result = (unsigned __int8)result;
  cpu_gpr[(unsigned __int8)op_rt] = (unsigned __int8)result;
  if ( (result & 0x80u) != 0 )
  {
    result |= 0xFFFFFF00;
    cpu_gpr[v1] = result;
  }
  return result;
}

void op_LBU()
{
  unsigned int v0; // ecx
  unsigned __int8 v1; // al

  v0 = (unsigned __int16)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  if ( (cpu_opcode & 0x1F0000) != 0 )
  {
    mem_hw_reg_read_byte(v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]);
    cpu_gpr[(unsigned __int8)op_rt] = v1;
  }
  else
  {
    mem_hw_reg_read_byte(v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]);
  }
}

int op_LH()
{
  unsigned int v0; // ecx
  int v1; // ecx
  int result; // eax

  v0 = (unsigned __int16)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  LOWORD(result) = mem_read_half(v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]);
  v1 = (unsigned __int8)op_rt;
  result = (unsigned __int16)result;
  cpu_gpr[(unsigned __int8)op_rt] = (unsigned __int16)result;
  if ( (result & 0x8000) != 0 )
  {
    result |= 0xFFFF0000;
    cpu_gpr[v1] = result;
  }
  return result;
}

int op_LHU()
{
  unsigned int v0; // ecx
  int result; // eax

  v0 = (unsigned __int16)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  result = (unsigned __int16)mem_read_half(v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]);
  cpu_gpr[(unsigned __int8)op_rt] = result;
  return result;
}

int op_LW()
{
  unsigned int v0; // ecx
  int result; // eax

  v0 = (unsigned __int16)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  if ( (cpu_opcode & 0x1F0000) == 0 )
    return mem_read_word(v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]);
  result = mem_read_word(v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]);
  cpu_gpr[(unsigned __int8)op_rt] = result;
  return result;
}

int op_LWL()
{
  unsigned int v0; // ecx
  unsigned int v1; // esi
  int result; // eax

  v0 = (unsigned __int16)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  v1 = v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  result = mem_read_word(v1 & 0xFFFFFFFC);
  if ( op_rt )
  {
    switch ( v1 & 3 )
    {
      case 0u:
        result <<= 24;
        cpu_gpr[(unsigned __int8)op_rt] = result | cpu_gpr[(unsigned __int8)op_rt] & 0xFFFFFF;
        break;
      case 1u:
        result <<= 16;
        cpu_gpr[(unsigned __int8)op_rt] = result | (unsigned __int16)cpu_gpr[(unsigned __int8)op_rt];
        break;
      case 2u:
        result <<= 8;
        cpu_gpr[(unsigned __int8)op_rt] = result | (unsigned __int8)cpu_gpr[(unsigned __int8)op_rt];
        break;
      case 3u:
        cpu_gpr[(unsigned __int8)op_rt] = result;
        break;
    }
  }
  return result;
}

unsigned int op_LWR()
{
  unsigned int v0; // ecx
  unsigned int v1; // esi
  unsigned int result; // eax

  v0 = (unsigned __int16)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  v1 = v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  result = mem_read_word(v1 & 0xFFFFFFFC);
  if ( op_rt )
  {
    switch ( v1 & 3 )
    {
      case 0u:
        cpu_gpr[(unsigned __int8)op_rt] = result;
        break;
      case 1u:
        result >>= 8;
        cpu_gpr[(unsigned __int8)op_rt] = result | cpu_gpr[(unsigned __int8)op_rt] & 0xFF000000;
        break;
      case 2u:
        result >>= 16;
        cpu_gpr[(unsigned __int8)op_rt] = result | cpu_gpr[(unsigned __int8)op_rt] & 0xFFFF0000;
        break;
      case 3u:
        result >>= 24;
        cpu_gpr[(unsigned __int8)op_rt] = result | cpu_gpr[(unsigned __int8)op_rt] & 0xFFFFFF00;
        break;
    }
  }
  return result;
}

int op_LUI()
{
  int result; // eax

  dword_576DA4 = (unsigned __int16)cpu_opcode;
  result = (unsigned __int16)cpu_opcode << 16;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  cpu_gpr[BYTE2(cpu_opcode) & 0x1F] = result;
  return result;
}

void op_SB()
{
  unsigned int v0; // esi

  v0 = (unsigned __int16)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  mem_hw_reg_write_byte(v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F], cpu_gpr[BYTE2(cpu_opcode) & 0x1F]);
}

void op_SH()
{
  unsigned int v0; // esi

  v0 = (unsigned __int16)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  mem_write_half(v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F], cpu_gpr[BYTE2(cpu_opcode) & 0x1F]);
}

void op_SW()
{
  unsigned int v0; // esi

  v0 = (unsigned __int16)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  mem_write_word(v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F], cpu_gpr[BYTE2(cpu_opcode) & 0x1F]);
}

void op_SWL()
{
  unsigned int v0; // ecx
  unsigned int v1; // esi
  unsigned int v2; // edi
  int word; // eax

  v0 = (unsigned __int16)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  v1 = v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  v2 = v1 & 0xFFFFFFFC;
  word = mem_read_word(v1 & 0xFFFFFFFC);
  switch ( v1 & 3 )
  {
    case 0u:
      mem_write_word(v2, HIBYTE(cpu_gpr[(unsigned __int8)op_rt]) | word & 0xFFFFFF00);
      break;
    case 1u:
      mem_write_word(v2, HIWORD(cpu_gpr[(unsigned __int8)op_rt]) | word & 0xFFFF0000);
      break;
    case 2u:
      mem_write_word(v2, ((unsigned int)cpu_gpr[(unsigned __int8)op_rt] >> 8) | word & 0xFF000000);
      break;
    case 3u:
      mem_write_word(v2, cpu_gpr[(unsigned __int8)op_rt]);
      break;
  }
}

void op_SWR()
{
  unsigned int v0; // ecx
  unsigned int v1; // esi
  unsigned int v2; // edi
  int word; // eax

  v0 = (unsigned __int16)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  v1 = v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  v2 = v1 & 0xFFFFFFFC;
  word = mem_read_word(v1 & 0xFFFFFFFC);
  switch ( v1 & 3 )
  {
    case 0u:
      mem_write_word(v2, cpu_gpr[(unsigned __int8)op_rt]);
      break;
    case 1u:
      mem_write_word(v2, (cpu_gpr[(unsigned __int8)op_rt] << 8) | (unsigned __int8)word);
      break;
    case 2u:
      mem_write_word(v2, (cpu_gpr[(unsigned __int8)op_rt] << 16) | (unsigned __int16)word);
      break;
    case 3u:
      mem_write_word(v2, (cpu_gpr[(unsigned __int8)op_rt] << 24) | word & 0xFFFFFF);
      break;
  }
}

int op_ADDI()
{
  unsigned int v0; // esi
  int result; // eax

  v0 = (unsigned __int16)cpu_opcode;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA4 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA4 = v0;
  }
  result = v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  cpu_gpr[BYTE2(cpu_opcode) & 0x1F] = result;
  return result;
}

int op_ADD()
{
  int v0; // eax
  int result; // eax

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  v0 = cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  byte_576DAD = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  result = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] + v0;
  cpu_gpr[(unsigned __int16)cpu_opcode >> 11] = result;
  return result;
}

int op_SUB()
{
  int result; // eax

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  byte_576DAD = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  result = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] - cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  cpu_gpr[(unsigned __int16)cpu_opcode >> 11] = result;
  return result;
}

int op_ANDI()
{
  int result; // eax

  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  dword_576DA4 = (unsigned __int16)cpu_opcode;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  result = (unsigned __int16)cpu_opcode & cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  cpu_gpr[BYTE2(cpu_opcode) & 0x1F] = result;
  return result;
}

int op_AND()
{
  int v0; // eax
  int result; // eax

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  v0 = cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  byte_576DAD = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  result = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] & v0;
  cpu_gpr[(unsigned __int16)cpu_opcode >> 11] = result;
  return result;
}

int op_NOR()
{
  int v0; // eax
  int result; // eax

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  v0 = cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  byte_576DAD = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  result = ~(cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] | v0);
  cpu_gpr[(unsigned __int16)cpu_opcode >> 11] = result;
  return result;
}

int op_ORI()
{
  int result; // eax

  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  dword_576DA4 = (unsigned __int16)cpu_opcode;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  result = (unsigned __int16)cpu_opcode | cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  cpu_gpr[BYTE2(cpu_opcode) & 0x1F] = result;
  return result;
}

int op_OR()
{
  int v0; // eax
  int result; // eax

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  v0 = cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  byte_576DAD = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  result = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] | v0;
  cpu_gpr[(unsigned __int16)cpu_opcode >> 11] = result;
  return result;
}

int op_XORI()
{
  int result; // eax

  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  dword_576DA4 = (unsigned __int16)cpu_opcode;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  result = (unsigned __int16)cpu_opcode ^ cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  cpu_gpr[BYTE2(cpu_opcode) & 0x1F] = result;
  return result;
}

int op_XOR()
{
  int v0; // eax
  int result; // eax

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  v0 = cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  byte_576DAD = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  result = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] ^ v0;
  cpu_gpr[(unsigned __int16)cpu_opcode >> 11] = result;
  return result;
}

BOOL op_SLTI()
{
  signed int v0; // esi
  BOOL result; // eax

  v0 = (unsigned __int16)cpu_opcode;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA4 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA4 = v0;
  }
  result = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] < v0;
  cpu_gpr[BYTE2(cpu_opcode) & 0x1F] = result;
  return result;
}

BOOL op_SLTIU()
{
  BOOL result; // eax

  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  dword_576DA4 = (unsigned __int16)cpu_opcode;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  result = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] < (unsigned int)(unsigned __int16)cpu_opcode;
  cpu_gpr[BYTE2(cpu_opcode) & 0x1F] = result;
  return result;
}

int op_SLT()
{
  int v0; // esi
  int result; // eax

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  v0 = cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  byte_576DAD = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  result = (unsigned __int16)cpu_opcode >> 11;
  cpu_gpr[result] = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] < v0;
  return result;
}

__int64 op_SLTU()
{
  __int64 result; // rax

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  byte_576DAD = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  LODWORD(result) = (unsigned __int16)cpu_opcode >> 11;
  HIDWORD(result) = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] < (unsigned int)cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  cpu_gpr[(_DWORD)result] = HIDWORD(result);
  return result;
}

char op_SLL()
{
  char result; // al

  result = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  byte_576DAD = result;
  byte_576DAE = ((unsigned int)cpu_opcode >> 6) & 0x1F;
  if ( result )
    cpu_gpr[(unsigned __int16)cpu_opcode >> 11] = cpu_gpr[BYTE2(cpu_opcode) & 0x1F] << (((unsigned int)cpu_opcode >> 6)
                                                                                      & 0x1F);
  return result;
}

int op_SLLV()
{
  char v0; // cl
  int result; // eax

  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  v0 = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  byte_576DAD = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  result = cpu_gpr[BYTE2(cpu_opcode) & 0x1F] << v0;
  cpu_gpr[(unsigned __int16)cpu_opcode >> 11] = result;
  return result;
}

char op_SRL()
{
  unsigned int v0; // edx
  char result; // al

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  byte_576DAE = ((unsigned int)cpu_opcode >> 6) & 0x1F;
  v0 = (unsigned int)cpu_gpr[BYTE2(cpu_opcode) & 0x1F] >> byte_576DAE;
  result = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  byte_576DAD = result;
  cpu_gpr[(unsigned __int16)cpu_opcode >> 11] = v0;
  return result;
}

unsigned int op_SRLV()
{
  char v0; // cl
  unsigned int result; // eax

  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  v0 = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  byte_576DAD = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  result = (unsigned int)cpu_gpr[BYTE2(cpu_opcode) & 0x1F] >> v0;
  cpu_gpr[(unsigned __int16)cpu_opcode >> 11] = result;
  return result;
}

char op_SRA()
{
  int v0; // edx
  char result; // al

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  byte_576DAE = ((unsigned int)cpu_opcode >> 6) & 0x1F;
  v0 = cpu_gpr[BYTE2(cpu_opcode) & 0x1F] >> byte_576DAE;
  result = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  byte_576DAD = result;
  cpu_gpr[(unsigned __int16)cpu_opcode >> 11] = v0;
  return result;
}

int op_SRAV()
{
  char v0; // cl
  int result; // eax

  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  v0 = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  byte_576DAD = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  result = cpu_gpr[BYTE2(cpu_opcode) & 0x1F] >> v0;
  cpu_gpr[(unsigned __int16)cpu_opcode >> 11] = result;
  return result;
}

__int64 op_MULT()
{
  __int64 result; // rax

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  result = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] * (__int64)cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  __SET_PAIR__(cpu_HI, cpu_LO, result);
  return result;
}

unsigned __int64 op_MULTU()
{
  unsigned __int64 result; // rax

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  result = (unsigned int)cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]
         * (unsigned __int64)(unsigned int)cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  __SET_PAIR__(cpu_HI, cpu_LO, result);
  return result;
}

int op_DIV()
{
  int v0; // ecx
  int v1; // esi
  int result; // eax

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  v0 = BYTE2(cpu_opcode) & 0x1F;
  v1 = cpu_gpr[v0];
  if ( v1 )
  {
    cpu_LO = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] / v1;
    result = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] / cpu_gpr[v0];
    cpu_HI = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] % cpu_gpr[v0];
  }
  else
  {
    cpu_HI = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
    cpu_LO = -1;
    return dbg_print(" division sign by 0 \n");
  }
  return result;
}

unsigned int op_DIVU()
{
  int v0; // ecx
  unsigned int v1; // esi
  unsigned int result; // eax

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  v0 = BYTE2(cpu_opcode) & 0x1F;
  v1 = cpu_gpr[v0];
  if ( v1 )
  {
    cpu_LO = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] / v1;
    result = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] / (unsigned int)cpu_gpr[v0];
    cpu_HI = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] % (unsigned int)cpu_gpr[v0];
  }
  else
  {
    cpu_HI = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
    cpu_LO = -1;
    return dbg_print(" division by 0 \n");
  }
  return result;
}

char op_MFHI()
{
  char result; // al

  result = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  byte_576DAD = result;
  cpu_gpr[(unsigned __int16)cpu_opcode >> 11] = cpu_HI;
  return result;
}

char op_MFLO()
{
  char result; // al

  result = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  byte_576DAD = result;
  cpu_gpr[(unsigned __int16)cpu_opcode >> 11] = cpu_LO;
  return result;
}

unsigned int op_MTHI()
{
  unsigned int result; // eax

  result = (unsigned int)cpu_opcode >> 21;
  LOBYTE(result) = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rs_0 = result;
  cpu_HI = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  return result;
}

unsigned int op_MTLO()
{
  unsigned int result; // eax

  result = (unsigned int)cpu_opcode >> 21;
  LOBYTE(result) = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rs_0 = result;
  cpu_LO = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  return result;
}

char op_J()
{
  int v0; // ecx
  char result; // al

  dword_576DA0 = cpu_opcode & 0x3FFFFFF;
  v0 = 4 * (cpu_opcode & 0x3FFFFFF);
  cpu_opcode = *(_DWORD *)(*(unsigned __int16 *)reg_pc + mem_read_hooks[*(unsigned __int16 *)&reg_pc[2]]);
  *(_DWORD *)reg_pc = v0 | *(_DWORD *)reg_pc & 0xF0000000;
  result = cpu_main_table[(unsigned int)cpu_opcode >> 26]();
  --hw_update_counter;
  return result;
}

char op_JAL()
{
  int v0; // ecx
  char result; // al

  dword_576DA0 = cpu_opcode & 0x3FFFFFF;
  v0 = 4 * (cpu_opcode & 0x3FFFFFF);
  cpu_opcode = *(_DWORD *)(*(unsigned __int16 *)reg_pc + mem_read_hooks[*(unsigned __int16 *)&reg_pc[2]]);
  MEMORY[0x50C35C] = *(_DWORD *)reg_pc + 4;
  *(_DWORD *)reg_pc = v0 | *(_DWORD *)reg_pc & 0xF0000000;
  result = cpu_main_table[(unsigned int)cpu_opcode >> 26]();
  --hw_update_counter;
  return result;
}

char op_JR()
{
  unsigned int v0; // edx
  char result; // al

  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  v0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  cpu_opcode = *(_DWORD *)(*(unsigned __int16 *)reg_pc + mem_read_hooks[*(unsigned __int16 *)&reg_pc[2]]);
  *(_DWORD *)reg_pc = cpu_gpr[v0];
  result = cpu_main_table[(unsigned int)cpu_opcode >> 26]();
  --hw_update_counter;
  return result;
}

int op_JALR()
{
  int v0; // esi
  int v1; // ebx
  unsigned int v2; // ecx

  v0 = mem_read_hooks[*(unsigned __int16 *)&reg_pc[2]];
  byte_576DAD = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  v1 = (unsigned __int16)cpu_opcode >> 11;
  v2 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  cpu_opcode = *(_DWORD *)(*(unsigned __int16 *)reg_pc + v0);
  cpu_gpr[v1] = *(_DWORD *)reg_pc + 4;
  *(_DWORD *)reg_pc = cpu_gpr[v2];
  cpu_main_table[(unsigned int)cpu_opcode >> 26]();
  return --hw_update_counter;
}

char op_BEQ()
{
  unsigned int v0; // esi
  int v1; // eax

  v0 = (unsigned __int16)cpu_opcode;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  v1 = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  if ( v1 == cpu_gpr[BYTE2(cpu_opcode) & 0x1F] )
  {
    cpu_opcode = *(_DWORD *)(*(unsigned __int16 *)reg_pc + mem_read_hooks[*(unsigned __int16 *)&reg_pc[2]]);
    *(_DWORD *)reg_pc += 4 * v0;
    LOBYTE(v1) = cpu_main_table[(unsigned int)cpu_opcode >> 26]();
    --hw_update_counter;
  }
  return v1;
}

char op_BNE()
{
  unsigned int v0; // esi
  int v1; // eax

  v0 = (unsigned __int16)cpu_opcode;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  v1 = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  if ( v1 != cpu_gpr[BYTE2(cpu_opcode) & 0x1F] )
  {
    cpu_opcode = *(_DWORD *)(*(unsigned __int16 *)reg_pc + mem_read_hooks[*(unsigned __int16 *)&reg_pc[2]]);
    *(_DWORD *)reg_pc += 4 * v0;
    LOBYTE(v1) = cpu_main_table[(unsigned int)cpu_opcode >> 26]();
    --hw_update_counter;
  }
  return v1;
}

char op_BGTZ()
{
  unsigned int v0; // ecx
  int v1; // eax

  v0 = (unsigned __int16)cpu_opcode;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  v1 = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  if ( v1 > 0 )
  {
    cpu_opcode = *(_DWORD *)(*(unsigned __int16 *)reg_pc + mem_read_hooks[*(unsigned __int16 *)&reg_pc[2]]);
    *(_DWORD *)reg_pc += 4 * v0;
    LOBYTE(v1) = cpu_main_table[(unsigned int)cpu_opcode >> 26]();
    --hw_update_counter;
  }
  return v1;
}

char op_BLTZ()
{
  unsigned int v0; // ecx
  int v1; // eax

  v0 = (unsigned __int16)cpu_opcode;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  v1 = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  if ( v1 < 0 )
  {
    cpu_opcode = *(_DWORD *)(*(unsigned __int16 *)reg_pc + mem_read_hooks[*(unsigned __int16 *)&reg_pc[2]]);
    *(_DWORD *)reg_pc += 4 * v0;
    LOBYTE(v1) = cpu_main_table[(unsigned int)cpu_opcode >> 26]();
    --hw_update_counter;
  }
  return v1;
}

char op_BLEZ()
{
  unsigned int v0; // ecx
  int v1; // eax

  v0 = (unsigned __int16)cpu_opcode;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  v1 = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  if ( v1 <= 0 )
  {
    cpu_opcode = *(_DWORD *)((unsigned __int16)reg_pc + mem_read_hooks[HIWORD(reg_pc)]);
    reg_pc += 4 * v0;
    LOBYTE(v1) = cpu_main_table[(unsigned int)cpu_opcode >> 26]();
    --hw_update_counter;
  }
  return v1;
}

char sub_41EA00()
{
  unsigned int v0; // ecx
  int v1; // eax

  v0 = (unsigned __int16)cpu_opcode;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  v1 = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  if ( v1 >= 0 )
  {
    cpu_opcode = *(_DWORD *)((unsigned __int16)reg_pc + mem_read_hooks[HIWORD(reg_pc)]);
    reg_pc += 4 * v0;
    LOBYTE(v1) = cpu_main_table[(unsigned int)cpu_opcode >> 26]();
    --hw_update_counter;
  }
  return v1;
}

char sub_41EA80()
{
  unsigned int v0; // ecx
  int v1; // eax

  v0 = (unsigned __int16)cpu_opcode;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  v1 = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  if ( v1 < 0 )
  {
    cpu_opcode = *(_DWORD *)(*(unsigned __int16 *)reg_pc + mem_read_hooks[*(unsigned __int16 *)&reg_pc[2]]);
    MEMORY[0x50C35C] = *(_DWORD *)reg_pc + 4;
    *(_DWORD *)reg_pc += 4 * v0;
    LOBYTE(v1) = cpu_main_table[(unsigned int)cpu_opcode >> 26]();
    --hw_update_counter;
  }
  return v1;
}

char sub_41EB10()
{
  unsigned int v0; // ecx
  int v1; // eax

  v0 = (unsigned __int16)cpu_opcode;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  v1 = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  if ( v1 >= 0 )
  {
    cpu_opcode = *(_DWORD *)(*(unsigned __int16 *)reg_pc + mem_read_hooks[*(unsigned __int16 *)&reg_pc[2]]);
    MEMORY[0x50C35C] = *(_DWORD *)reg_pc + 4;
    *(_DWORD *)reg_pc += 4 * v0;
    LOBYTE(v1) = cpu_main_table[(unsigned int)cpu_opcode >> 26]();
    --hw_update_counter;
  }
  return v1;
}

unsigned int op_MTC0()
{
  unsigned __int8 v0; // cl
  unsigned __int8 v1; // al
  unsigned int result; // eax
  int v3; // edx
  int v4; // edx

  v0 = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  v1 = BYTE2(cpu_opcode) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  byte_576DAD = v0;
  if ( v0 == 14 || v0 == 15 || v0 == 8 )
    return dbg_print("[%d] only read!!!\n", (unsigned __int16)cpu_opcode >> 11);
  if ( v0 == 13 )
  {
    result = cpu_gpr[v1];
    dword_50C2A8 = result;
    if ( (result & 0x100) != 0 && (dword_50C2A4 & 0x101) == 0x101 )
    {
LABEL_21:
      result = dword_50C2A4;
      if ( (dword_50C2A4 & 0x101) == 0x101 )
      {
        result = dword_50C2A4 & 0xFFFFFFC0;
        dword_50C2AC = *(_DWORD *)reg_pc;
        dword_50C2A8 = 256;
        *(_DWORD *)reg_pc = 0x80000080;
        dword_50C2A4 = dword_50C2A4 & 0xFFFFFFC0 | (4 * (dword_50C2A4 & 0xF));
      }
    }
  }
  else if ( v0 == 12 )
  {
    result = cpu_gpr[v1];
    dword_50C2A4 = result;
    if ( (dword_50C2A8 & 0x100) != 0 )
    {
      result &= 0x101u;
      if ( result == 257 )
        goto LABEL_21;
    }
  }
  else
  {
    if ( v0 == 3 )
    {
      if ( byte_4F8320 )
      {
        byte_4F8320 = 0;
        cpu_gpr[v1] |= 1u;
      }
      else
      {
        v3 = cpu_gpr[v1];
        if ( dword_50C280 != v3 )
        {
          v4 = v3 | 1;
          if ( dword_50C280 == v4 )
            cpu_gpr[v1] = v4;
        }
      }
    }
    cop0_regs[v0] = cpu_gpr[v1];
    return v0;
  }
  return result;
}

int op_MFC0()
{
  int result; // eax

  byte_576DAD = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  result = BYTE2(cpu_opcode) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  cpu_gpr[result] = cop0_regs[(unsigned __int16)cpu_opcode >> 11];
  return result;
}

unsigned int sub_41ED00()
{
  unsigned int v0; // eax
  unsigned int result; // eax

  v0 = dword_50C2A4;
  if ( (dword_50C2A4 & 1) != 0 )
    v0 = dword_50C2A4 | 4;
  result = ((unsigned __int8)v0 ^ (unsigned __int8)(v0 >> 2)) & 0xF ^ v0;
  dword_50C2A4 = result;
  return result;
}

void op_SWC2()
{
  unsigned int data_register; // eax

  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
    dword_576DA8 = cpu_opcode | 0xFFFF0000;
  data_register = gte_read_data_register(BYTE2(cpu_opcode) & 0x1F);
  mem_write_word(dword_576DA8 + cpu_gpr[(unsigned __int8)op_rs], data_register);
}

GTE_REG op_LWC2()
{
  unsigned int v0; // ecx
  int word; // eax

  v0 = (unsigned __int16)cpu_opcode;
  op_rs = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  dword_576DA8 = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    dword_576DA8 = v0;
  }
  word = mem_read_word(v0 + cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F]);
  return gte_write_data_register(op_rt, (GTE_REG)word);
}

unsigned int op_SYSCALL()
{
  unsigned int result; // eax

  dword_50C2AC = *(_DWORD *)reg_pc - 4;
  result = dword_50C2A4 & 0xFFFFFFC0;
  dword_50C2A8 = 32;
  dword_50C2A4 = dword_50C2A4 & 0xFFFFFFC0 | (4 * (dword_50C2A4 & 0xF));
  *(_DWORD *)reg_pc = 0x80000080;
  return result;
}

