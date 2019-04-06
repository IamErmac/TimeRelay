#include "modeWork.h"

//Private defines
//Extern global variables
extern timeCount_t lowStateTime, highStateTime;
extern volatile button_t plusButton, minusButton, setButton;
//Static global variables
static bool isHighStateTime = true;
static bool isDot = false;
static bool isGUIUpdated = false;
static timeCount_t tmpTimer = {.seconds = 0, .minutes = 0, .hours = 0};
//Static functions prototypes
static void loadNewTimerData(void);
static void updateGUIWorkMode(void);
//Global varibales
//-----------------------------------------------------------------------------

static void loadNewTimerData(void){
  if (isHighStateTime){
    tmpTimer.seconds = highStateTime.seconds;
    tmpTimer.minutes = highStateTime.minutes;
    tmpTimer.hours = highStateTime.hours;
  }else{
    tmpTimer.seconds = lowStateTime.seconds;
    tmpTimer.minutes = lowStateTime.minutes;
    tmpTimer.hours = lowStateTime.hours;
  }
}

static void updateRelayState(bool isHigh){
  if (isHigh)
    GPIO_WriteHigh(RELAY_GPIO_PORT, RELAY_GPIO_PIN);
  else
    GPIO_WriteLow(RELAY_GPIO_PORT, RELAY_GPIO_PIN);
}

void initWorkMode(void){
#ifdef HIGH_STATE_START
  isHighStateTime = true;
#else
  isHighStateTime = false;
#endif
  loadNewTimerData();
  updateRelayState(isHighStateTime);
  
  isGUIUpdated = true;
  setSecondTimerToZero();
}

uint8_t handleWorkMode(void){
  uint8_t rc = RC_NOT_COMPLETE;

  if(isSecondPast()){
    isDot = !isDot;
    isGUIUpdated = true;
   
    decrementTimer(&tmpTimer);
    
    if (isTimerSetToZero(&tmpTimer)){
      isHighStateTime = !isHighStateTime;
      loadNewTimerData();
      updateRelayState(isHighStateTime);
    }
  }
  
  if (setButton.isBeingPressed && setButton.isLong && !setButton.wasHandled){
    setButton.wasHandled = true;
    updateRelayState(false);
    rc = RC_COMPLETE;
  }
  
  if (setButton.wasHandled && setButton.wasPressed){
    clearButtonEvent(&setButton);
  }
  
  if (plusButton.wasPressed && plusButton.wasHandled){
    clearButtonEvent(&plusButton);
  }
  
  if (minusButton.wasPressed && minusButton.wasHandled){
    clearButtonEvent(&minusButton);
  }
  
  updateGUIWorkMode();
  
  return rc;
}

static void updateGUIWorkMode(void){
  if (!isGUIUpdated)
    return;
  else
    isGUIUpdated = false;
  
  printTimeData(getTheHighestTime(&tmpTimer), getTheHighestTimeSign(&tmpTimer), isDot, false);
}
