#include "pch.h"

//.data:00455C80 cpu_special_opcode_table dd offset op_SLL, offset op_UNKNOWN, offset op_SRL, offset op_SRA
//.data : 00455C90                 dd offset op_SLLV, offset op_UNKNOWN, offset op_SRLV, offset op_SRAV
//.data : 00455CA0                 dd offset op_JR, offset op_JALR, offset op_UNKNOWN, offset op_UNKNOWN
//.data : 00455CB0                 dd offset op_SYSCALL, offset nullsub_1, offset op_UNKNOWN
//.data : 00455CBC                 dd offset op_UNKNOWN, offset op_MFHI, offset op_MTHI, offset op_MFLO
//.data : 00455CCC                 dd offset op_MTLO, offset op_UNKNOWN, offset op_UNKNOWN
//.data : 00455CD8                 dd offset op_UNKNOWN, offset op_UNKNOWN, offset op_MULT
//.data : 00455CE4                 dd offset op_MULTU, offset op_DIV, offset op_DIVU, offset op_UNKNOWN
//.data : 00455CF4                 dd offset op_UNKNOWN, offset op_UNKNOWN, offset op_UNKNOWN
//.data : 00455D00                 dd offset op_ADD, offset op_ADD, offset op_SUB, offset op_SUB
//.data : 00455D10                 dd offset op_AND, offset op_OR, offset op_XOR, offset op_NOR
//.data : 00455D20                 dd offset op_UNKNOWN, offset op_UNKNOWN, offset op_SLT
//.data : 00455D2C                 dd offset op_SLTU, offset op_UNKNOWN, offset op_UNKNOWN
//.data : 00455D38                 dd offset op_UNKNOWN, offset op_UNKNOWN, offset op_UNKNOWN
//.data : 00455D44                 dd offset op_UNKNOWN, offset op_UNKNOWN, offset op_UNKNOWN
//.data : 00455D50                 dd offset op_UNKNOWN, offset op_UNKNOWN, offset op_UNKNOWN
//.data : 00455D5C                 dd offset op_UNKNOWN, offset op_UNKNOWN, offset op_UNKNOWN
//.data : 00455D68                 dd offset op_UNKNOWN, offset op_UNKNOWN, offset op_UNKNOWN
//.data : 00455D74                 dd offset op_UNKNOWN, offset op_UNKNOWN, offset op_UNKNOWN
//.data : 00455D80 cpu_cop0_table  dd offset op_MFC0
//.data : 00455D84                 dd offset op_UNKNOWN
//.data : 00455D88                 dd offset op_UNKNOWN
//.data : 00455D8C                 dd offset op_UNKNOWN
//.data : 00455D90                 dd offset op_MTC0
//.data : 00455D94                 dd offset op_UNKNOWN
//.data : 00455D98                 dd offset op_UNKNOWN
//.data : 00455D9C                 dd offset op_UNKNOWN
//.data : 00455DA0                 dd offset op_UNKNOWN
//.data : 00455DA4                 dd offset op_UNKNOWN
//.data : 00455DA8                 dd offset op_UNKNOWN
//.data : 00455DAC                 dd offset op_UNKNOWN
//.data : 00455DB0                 dd offset op_UNKNOWN
//.data : 00455DB4                 dd offset op_UNKNOWN
//.data : 00455DB8                 dd offset op_UNKNOWN
//.data : 00455DBC                 dd offset op_UNKNOWN
//.data : 00455DC0                 dd offset op_RFE
//.data : 00455DC4                 dd offset op_UNKNOWN
//.data : 00455DC8                 dd offset op_UNKNOWN
//.data : 00455DCC                 dd offset op_UNKNOWN
//.data : 00455DD0                 dd offset op_UNKNOWN
//.data : 00455DD4                 dd offset op_UNKNOWN
//.data : 00455DD8                 dd offset op_UNKNOWN
//.data : 00455DDC                 dd offset op_UNKNOWN
//.data : 00455DE0                 dd offset op_UNKNOWN
//.data : 00455DE4                 dd offset op_UNKNOWN
//.data : 00455DE8                 dd offset op_UNKNOWN
//.data : 00455DEC                 dd offset op_UNKNOWN
//.data : 00455DF0                 dd offset op_UNKNOWN
//.data : 00455DF4                 dd offset op_UNKNOWN
//.data : 00455DF8                 dd offset op_UNKNOWN
//.data : 00455DFC                 dd offset op_UNKNOWN
//.data : 00455E00 cpu_bcond_opcode_table dd offset op_BLTZ
//.data : 00455E04                 dd offset op_BGEZ
//.data : 00455E08                 dd offset op_UNKNOWN
//.data : 00455E0C                 dd offset op_UNKNOWN
//.data : 00455E10                 dd offset op_UNKNOWN
//.data : 00455E14                 dd offset op_UNKNOWN
//.data : 00455E18                 dd offset op_UNKNOWN
//.data : 00455E1C                 dd offset op_UNKNOWN
//.data : 00455E20                 dd offset op_UNKNOWN
//.data : 00455E24                 dd offset op_UNKNOWN
//.data : 00455E28                 dd offset op_UNKNOWN
//.data : 00455E2C                 dd offset op_UNKNOWN
//.data : 00455E30                 dd offset op_UNKNOWN
//.data : 00455E34                 dd offset op_UNKNOWN
//.data : 00455E38                 dd offset op_UNKNOWN
//.data : 00455E3C                 dd offset op_UNKNOWN
//.data : 00455E40                 dd offset op_BLTZAL
//.data : 00455E44                 dd offset op_BGEZAL
//.data : 00455E48                 dd offset op_UNKNOWN
//.data : 00455E4C                 dd offset op_UNKNOWN
//.data : 00455E50                 dd offset op_UNKNOWN
//.data : 00455E54                 dd offset op_UNKNOWN
//.data : 00455E58                 dd offset op_UNKNOWN
//.data : 00455E5C                 dd offset op_UNKNOWN
//.data : 00455E60                 dd offset op_UNKNOWN
//.data : 00455E64                 dd offset op_UNKNOWN
//.data : 00455E68                 dd offset op_UNKNOWN
//.data : 00455E6C                 dd offset op_UNKNOWN
//.data : 00455E70                 dd offset op_UNKNOWN
//.data : 00455E74                 dd offset op_UNKNOWN
//.data : 00455E78                 dd offset op_UNKNOWN
//.data : 00455E7C                 dd offset op_UNKNOWN
//.data : 00455E80 cpu_main_table  dd offset op_SPECIAL, offset op_BCONDZ, offset op_J, offset op_JAL
//.data:00455E90                 dd offset op_BEQ, offset op_BNE, offset op_BLEZ, offset op_BGTZ
//.data : 00455EA0                 dd offset op_ADDI, offset op_ADDI, offset op_SLTI, offset op_SLTIU
//.data : 00455EB0                 dd offset op_ANDI, offset op_ORI, offset op_XORI, offset op_LUI
//.data : 00455EC0                 dd offset op_COP0, offset op_UNKNOWN, offset gte_exec_opcode
//.data : 00455ECC                 dd offset op_UNKNOWN, offset op_UNKNOWN, offset op_UNKNOWN
//.data : 00455ED8                 dd offset op_UNKNOWN, offset op_UNKNOWN, offset op_UNKNOWN
//.data : 00455EE4                 dd offset op_UNKNOWN, offset op_UNKNOWN, offset op_UNKNOWN
//.data : 00455EF0                 dd offset op_UNKNOWN, offset op_UNKNOWN, offset op_UNKNOWN
//.data : 00455EFC                 dd offset op_UNKNOWN, offset op_LB, offset op_LH, offset op_LWL
//.data : 00455F0C                 dd offset op_LW, offset op_LBU, offset op_LHU, offset op_LWR
//.data : 00455F1C                 dd offset op_UNKNOWN, offset op_SB, offset op_SH, offset op_SWL
//.data : 00455F2C                 dd offset op_SW, offset op_UNKNOWN, offset op_UNKNOWN
//.data : 00455F38                 dd offset op_SWR, offset op_UNKNOWN, offset op_UNKNOWN
//.data : 00455F44                 dd offset op_UNKNOWN, offset op_LWC2, offset op_UNKNOWN
//.data : 00455F50                 dd offset op_UNKNOWN, offset op_UNKNOWN, offset op_UNKNOWN
//.data : 00455F5C                 dd offset op_UNKNOWN, offset op_UNKNOWN, offset op_UNKNOWN
//.data : 00455F68                 dd offset op_SWC2, offset op_UNKNOWN, offset op_UNKNOWN
//.data : 00455F74                 dd offset op_UNKNOWN, offset op_UNKNOWN, offset op_UNKNOWN

void __noreturn op_SPECIAL()
{
  cpu_special_opcode_table[cpu_opcode & 0x3F]();
}

void __noreturn op_BCONDZ()
{
  cpu_bcond_opcode_table[BYTE2(cpu_opcode) & 0x1F]();
}

void __noreturn op_COP0()
{
  cpu_cop0_table[((unsigned int)cpu_opcode >> 21) & 0x1F]();
}