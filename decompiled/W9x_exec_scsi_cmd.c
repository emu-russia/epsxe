#include "pch.h"
char __cdecl W9x_exec_scsi_cmd(const void *a1, unsigned int a2, BYTE *a3, DWORD a4)
{
  HANDLE EventA; // ebx
  SRB_ExecSCSICmd v6; // [esp+Ch] [ebp-50h] BYREF

  EventA = CreateEventA(nullptr, 1, 0, nullptr);
  memset(&v6, 0, sizeof(v6));
  v6.SRB_Target = cdrom_target;
  v6.SRB_BufPointer = a3;
  v6.SRB_CDBLen = a2;
  v6.SRB_Lun = cdrom_lun;
  v6.SRB_HaId = cdrom_haid;
  v6.SRB_Cmd = 2;
  v6.SRB_Flags = 72;
  v6.SRB_BufLen = a4;
  v6.SRB_SenseLen = 14;
  v6.SRB_PostProc = EventA;
  qmemcpy(v6.CDBByte, a1, a2);
  ResetEvent(EventA);
  if ( !SendASPI32Command_cb(&v6) )
    WaitForSingleObject(EventA, 0xFFFFFFFF);
  if ( v6.SRB_Status != 1 )
    return 1;
  CloseHandle(EventA);
  return 0;
}
