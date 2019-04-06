#include "init_memory.h"

//Private defines
#define ROP_OPTION_BYTE_ADDR    0x4800
#define ROP_OPTION_BYTE_DATA    0xAA
//Extern global variables
//Static global variables
//Static functions prototypes
//Global varibales
//-----------------------------------------------------------------------------

void initMemory(void){
  //EEPROM init
  FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
  FLASH_Unlock(FLASH_MEMTYPE_DATA);
  //Enable Readout Protection (ROP)
#ifndef MEM_PROT_DIS
  if (FLASH_ReadOptionByte(ROP_OPTION_BYTE_ADDR) != ROP_OPTION_BYTE_DATA)
    FLASH_ProgramOptionByte(ROP_OPTION_BYTE_ADDR, ROP_OPTION_BYTE_DATA);
#endif
}