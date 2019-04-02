#include "SWTimer.h"

//Private defines
#define FLASH_TIME      500
#define SECOND_TIME     1000
#define FAST_COUNT_TIME 200
//Extern global variables
//Static global variables
static volatile uint16_t flashTimer = 0;
static volatile uint16_t secondTimer = 0;
static volatile uint16_t fastCountTimer = 0;
//Static functions prototypes
//Global varibales
//-----------------------------------------------------------------------------

void handleFlashTimer(void){
  if(flashTimer < FLASH_TIME)
    flashTimer++;
}

void handleSecondTimer(void){
  if(secondTimer < SECOND_TIME)
    secondTimer++;
}

bool isTimeToFlash(void){
  if(flashTimer >= FLASH_TIME){
    flashTimer = 0;
    return true;
  }
  return false;
}

bool isSecondPast(void){
  if(secondTimer >= SECOND_TIME){
    secondTimer = 0;
    return true;
  }
  return false;
}

void setSecondTimerToZero(void){
  secondTimer = 0;
}

void setFlashTimerToZero(void){
  flashTimer = 0;
}

void handleFastCountTimer(void){
  if(fastCountTimer < FAST_COUNT_TIME)
    fastCountTimer++;
}

bool isFastCountTime(void){
  if(fastCountTimer >= FAST_COUNT_TIME){
    fastCountTimer = 0;
    return true;
  }
  return false;
}

void setFastCountTimerToZero(void){
  fastCountTimer = 0;
}