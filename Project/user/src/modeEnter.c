#include "modeEnter.h"

//Private defines
//Extern global variables
extern volatile button_t plusButton, minusButton, setButton;
extern timeCount_t lowStateTime, highStateTime;
//Static global variables
static bool isFlash = false;
static bool isHighStateTime = false;
static bool isGUIUpdated = false;
static uint8_t currentTime = IND_SEC;
//Static functions prototypes
static void updateGUIEnterMode(void);
static void incrementCurrentTime(void);
static void decrementCurrentTime(void);
//Global varibales
//-----------------------------------------------------------------------------

void initEnterMode(void){
  currentTime = IND_SEC;
  isHighStateTime = true;
  isGUIUpdated = true;
}

static void incrementCurrentTime(void){
  if (isHighStateTime)
    incrementTime(&highStateTime, currentTime);
  else
    incrementTime(&lowStateTime, currentTime);
}

static void decrementCurrentTime(void){
  if (isHighStateTime)
    decrementTime(&highStateTime, currentTime);
  else
    decrementTime(&lowStateTime, currentTime);
}

uint8_t handleEnterMode(void)
{
  uint8_t rc = RC_NOT_COMPLETE;
  
  if (isTimeToFlash()){
    isGUIUpdated = true;
    isFlash = !isFlash;
  }
  
  if (plusButton.wasPressed && plusButton.isShort && !minusButton.wasPressed && !minusButton.isBeingPressed){
    clearButtonEvent(&plusButton);
    incrementCurrentTime();
    isGUIUpdated = true;
  }
  
  if (plusButton.isBeingPressed && plusButton.isLong && !minusButton.wasPressed && !minusButton.isBeingPressed){
    if (isFastCountTime()){
      incrementCurrentTime();
      isGUIUpdated = true;
    }
    isFlash = false;
  }
  
  if(plusButton.wasPressed && plusButton.isLong && !minusButton.wasPressed && !minusButton.isBeingPressed){
    clearButtonEvent(&plusButton);
  }
  
  if (minusButton.wasPressed && minusButton.isShort && !plusButton.wasPressed && !plusButton.isBeingPressed){
    clearButtonEvent(&minusButton);
    decrementCurrentTime();
    isGUIUpdated = true;
  }
  
  if (minusButton.isBeingPressed && minusButton.isLong && !plusButton.wasPressed && !plusButton.isBeingPressed){
    if (isFastCountTime()){
      decrementCurrentTime();
      isGUIUpdated = true;
    }
    isFlash = false;
  }
  
  if(minusButton.wasPressed && minusButton.isLong && !plusButton.wasPressed && !plusButton.isBeingPressed){
    clearButtonEvent(&minusButton);
  }
  
  if (plusButton.isBeingPressed && minusButton.isBeingPressed && 
      plusButton.isLong && minusButton.isLong && 
      !plusButton.wasHandled && !minusButton.wasHandled){
      minusButton.wasHandled = true;
      plusButton.wasHandled = true;
        
      if ((lowStateTime.seconds || lowStateTime.minutes || lowStateTime.hours)&&(highStateTime.seconds || highStateTime.minutes || highStateTime.hours)){
      initEnterMode();
      saveSettings();
      rc = RC_COMPLETE;
    }
  }
  
  if (plusButton.wasPressed && plusButton.wasHandled && minusButton.wasPressed && minusButton.wasHandled){
    clearButtonEvent(&plusButton);
    clearButtonEvent(&minusButton);
  }
  
  if (plusButton.wasPressed && minusButton.wasPressed){
    clearButtonEvent(&minusButton);
    clearButtonEvent(&plusButton);
  }
  
  if (setButton.wasPressed && setButton.isShort){
    clearButtonEvent(&setButton);
    
    if (currentTime < IND_HOUR)
      currentTime++;
    else
      currentTime = IND_SEC;
    
    if (currentTime == IND_SEC)
      isHighStateTime = !isHighStateTime;
    
    isGUIUpdated = true;
  }
  
  if (setButton.isBeingPressed && setButton.isLong && !setButton.wasHandled){
    
    setButton.wasHandled = true;
    if ((lowStateTime.seconds || lowStateTime.minutes || lowStateTime.hours)&&(highStateTime.seconds || highStateTime.minutes || highStateTime.hours)){
      rc = RC_COMPLETE;
      initEnterMode();
    }
  }
  
  if (setButton.wasHandled && setButton.wasPressed){
    clearButtonEvent(&setButton);
  }

  updateGUIEnterMode();
   
  return rc;
}

static void updateGUIEnterMode(void){
  if (isGUIUpdated)
    isGUIUpdated = false;
  else
    return;
  
  uint8_t timeTmp;
  
  if (isHighStateTime)
    timeTmp = getCurrentTime(&highStateTime, currentTime);
  else
    timeTmp = getCurrentTime(&lowStateTime, currentTime);
  
  printTimeData(timeTmp, getCurrentTimeSign(currentTime), isHighStateTime, isFlash);
}
