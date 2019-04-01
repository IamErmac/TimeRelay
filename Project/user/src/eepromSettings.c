#include "eepromSettings.h"

#define PROT_BYTE_1 0x12
#define PROT_BYTE_2 0x34

#define START_ADDRESS 0x4000

extern timeCount_t timeUp;
extern timeCount_t timeDown;

void saveSettings(void){
  FLASH_ProgramByte(START_ADDRESS, PROT_BYTE_1);
  FLASH_ProgramByte(START_ADDRESS + 1, PROT_BYTE_2);
  
  FLASH_ProgramByte(START_ADDRESS + 2, timeUp.seconds);
  FLASH_ProgramByte(START_ADDRESS + 3, timeUp.minutes);
  FLASH_ProgramByte(START_ADDRESS + 4, timeUp.hours);
 
  FLASH_ProgramByte(START_ADDRESS + 5, timeDown.seconds);
  FLASH_ProgramByte(START_ADDRESS + 6, timeDown.minutes);
  FLASH_ProgramByte(START_ADDRESS + 7, timeDown.hours);
}

static bool checkSettings(void){
  if ((FLASH_ReadByte(START_ADDRESS) == PROT_BYTE_1)&&(FLASH_ReadByte(START_ADDRESS + 1) == PROT_BYTE_2))
    return true;
  else
    return false;
}

void loadSettings(void){
  if (!checkSettings())
    return;
  
  timeUp.seconds = FLASH_ReadByte(START_ADDRESS + 2);
  timeUp.minutes = FLASH_ReadByte(START_ADDRESS + 3);
  timeUp.hours = FLASH_ReadByte(START_ADDRESS + 4);
  
  timeDown.seconds = FLASH_ReadByte(START_ADDRESS + 5);
  timeDown.minutes = FLASH_ReadByte(START_ADDRESS + 6);
  timeDown.hours = FLASH_ReadByte(START_ADDRESS + 7);
}
