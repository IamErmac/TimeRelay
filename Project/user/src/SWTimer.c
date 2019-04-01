#include "SWTimer.h"

#define FLASH_TIME      500
#define SECOND_TIME     1000

static volatile uint16_t flashTimer = 0;
static volatile uint16_t secondTimer = 0;

//Need to rename to SWTimer

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