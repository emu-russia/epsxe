#include "pch.h"
char __cdecl spu_write_register(unsigned int a1, unsigned __int16 a2)
{
  char result; // al

  if ( spu_use_external_plugin == 1 )
    return SPUwriteRegister(a1, a2);
  result = a1;
  if ( a1 > 0x1F801CC6 )
  {
    switch ( a1 )
    {
      case 0x1F801CD0u:
      case 0x1F801CE0u:
      case 0x1F801CF0u:
      case 0x1F801D00u:
      case 0x1F801D10u:
      case 0x1F801D20u:
      case 0x1F801D30u:
      case 0x1F801D40u:
      case 0x1F801D50u:
      case 0x1F801D60u:
      case 0x1F801D70u:
LABEL_7:
        if ( sound_enabled )
          result = SPUsetVolumeL((a1 >> 4) & 0x1F, a2);
        break;
      case 0x1F801CD2u:
      case 0x1F801CE2u:
      case 0x1F801CF2u:
      case 0x1F801D02u:
      case 0x1F801D12u:
      case 0x1F801D22u:
      case 0x1F801D32u:
      case 0x1F801D42u:
      case 0x1F801D52u:
      case 0x1F801D62u:
      case 0x1F801D72u:
LABEL_9:
        if ( sound_enabled )
          result = SPUsetVolumeR((a1 >> 4) & 0x1F, a2);
        break;
      case 0x1F801CD4u:
      case 0x1F801CE4u:
      case 0x1F801CF4u:
      case 0x1F801D04u:
      case 0x1F801D14u:
      case 0x1F801D24u:
      case 0x1F801D34u:
      case 0x1F801D44u:
      case 0x1F801D54u:
      case 0x1F801D64u:
      case 0x1F801D74u:
LABEL_11:
        if ( sound_enabled )
          result = SPUsetPitch((a1 >> 4) & 0x1F, a2);
        break;
      case 0x1F801CD6u:
      case 0x1F801CE6u:
      case 0x1F801CF6u:
      case 0x1F801D06u:
      case 0x1F801D16u:
      case 0x1F801D26u:
      case 0x1F801D36u:
      case 0x1F801D46u:
      case 0x1F801D56u:
      case 0x1F801D66u:
      case 0x1F801D76u:
        goto LABEL_13;
      case 0x1F801D88u:
        result = sound_enabled;
        if ( sound_enabled )
          result = SPUstartChannels1(a2);
        break;
      case 0x1F801D8Au:
        result = sound_enabled;
        if ( sound_enabled )
          result = SPUstartChannels2(a2);
        break;
      case 0x1F801D8Cu:
        result = sound_enabled;
        if ( sound_enabled )
          result = SPUstopChannels1(a2);
        break;
      case 0x1F801D8Eu:
        result = sound_enabled;
        if ( sound_enabled )
          result = SPUstopChannels2(a2);
        break;
      case 0x1F801DA6u:
        dword_8A8080 = 8 * a2;
        break;
      case 0x1F801DA8u:
        result = sound_enabled;
        if ( sound_enabled )
        {
          result = SPUputOne(dword_8A8080, a2);
          dword_8A8080 += 2;
        }
        break;
      default:
LABEL_26:
        *(__int16 *)((char *)word_8A8084 + (a1 & 0x1FF)) = a2;
        result = a1;
        break;
    }
  }
  else
  {
    if ( a1 != 528489670 )
    {
      switch ( a1 )
      {
        case 0x1F801C00u:
        case 0x1F801C10u:
        case 0x1F801C20u:
        case 0x1F801C30u:
        case 0x1F801C40u:
        case 0x1F801C50u:
        case 0x1F801C60u:
        case 0x1F801C70u:
        case 0x1F801C80u:
        case 0x1F801C90u:
        case 0x1F801CA0u:
        case 0x1F801CB0u:
        case 0x1F801CC0u:
          goto LABEL_7;
        case 0x1F801C02u:
        case 0x1F801C12u:
        case 0x1F801C22u:
        case 0x1F801C32u:
        case 0x1F801C42u:
        case 0x1F801C52u:
        case 0x1F801C62u:
        case 0x1F801C72u:
        case 0x1F801C82u:
        case 0x1F801C92u:
        case 0x1F801CA2u:
        case 0x1F801CB2u:
        case 0x1F801CC2u:
          goto LABEL_9;
        case 0x1F801C04u:
        case 0x1F801C14u:
        case 0x1F801C24u:
        case 0x1F801C34u:
        case 0x1F801C44u:
        case 0x1F801C54u:
        case 0x1F801C64u:
        case 0x1F801C74u:
        case 0x1F801C84u:
        case 0x1F801C94u:
        case 0x1F801CA4u:
        case 0x1F801CB4u:
        case 0x1F801CC4u:
          goto LABEL_11;
        case 0x1F801C06u:
        case 0x1F801C16u:
        case 0x1F801C26u:
        case 0x1F801C36u:
        case 0x1F801C46u:
        case 0x1F801C56u:
        case 0x1F801C66u:
        case 0x1F801C76u:
        case 0x1F801C86u:
        case 0x1F801C96u:
        case 0x1F801CA6u:
        case 0x1F801CB6u:
          break;
        default:
          goto LABEL_26;
      }
    }
LABEL_13:
    if ( sound_enabled )
      return SPUsetAddr((a1 >> 4) & 0x1F, a2);
  }
  return result;
}
