#include "init_periph.h"

//Private defines
//Extern global variables
//Static global variables
//Static functions prototypes
//Global varibales
//-----------------------------------------------------------------------------

void initPeriph(void){
  initClock();
  initGPIO();
  initMemory();
  initTimer1();
  //Enable interrupts
  enableInterrupts();
}