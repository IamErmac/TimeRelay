#include "eepromSettings.h"

//Private defines
#define PROT_BYTE_1 0x12
#define PROT_BYTE_2 0x34
#define START_ADDRESS 0x4000
//Extern global variables
extern timeCount_t lowStateTime;
extern timeCount_t highStateTime;
//Static global variables
//Static functions prototypes
static bool checkSettings(void);
//Global varibales
//-----------------------------------------------------------------------------

void saveSettings(void){
  FLASH_ProgramByte(START_ADDRESS, PROT_BYTE_1);
  FLASH_ProgramByte(START_ADDRESS + 1, PROT_BYTE_2);
  
  FLASH_ProgramByte(START_ADDRESS + 2, lowStateTime.seconds);
  FLASH_ProgramByte(START_ADDRESS + 3, lowStateTime.minutes);
  FLASH_ProgramByte(START_ADDRESS + 4, lowStateTime.hours);
 
  FLASH_ProgramByte(START_ADDRESS + 5, highStateTime.seconds);
  FLASH_ProgramByte(START_ADDRESS + 6, highStateTime.minutes);
  FLASH_ProgramByte(START_ADDRESS + 7, highStateTime.hours);
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
  
  lowStateTime.seconds = FLASH_ReadByte(START_ADDRESS + 2);
  lowStateTime.minutes = FLASH_ReadByte(START_ADDRESS + 3);
  lowStateTime.hours = FLASH_ReadByte(START_ADDRESS + 4);
  
  highStateTime.seconds = FLASH_ReadByte(START_ADDRESS + 5);
  highStateTime.minutes = FLASH_ReadByte(START_ADDRESS + 6);
  highStateTime.hours = FLASH_ReadByte(START_ADDRESS + 7);
}
