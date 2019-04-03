#include "modeEnter.h"

//Private defines
#define HIGH_TIME_EDGE  (360000ul - 1)
#define SECONDS_MAX     59
#define MINUTES_MAX     59
#define HOURS_MAX       99
//Extern global variables
extern volatile button_t plusButton, minusButton, setButton;
extern bool isGUIUpdated;
extern uint8_t indicatorRawDataBuffer[IND_RAW_DATA];
extern timeCount_t lowStateTime;
extern timeCount_t highStateTime;
//Static global variables
static bool isFlash = false;
static bool isHighStateTime = false;
static uint8_t currentTime = IND_SEC;
//Static functions prototypes
static void updateGUIEnterMode(void);
static void incrementData(uint8_t *data, uint8_t edge);
static void decrementData(uint8_t *data, uint8_t edge);
static void incrementTime(timeCount_t *time);
static void decrementTime(timeCount_t *time);
static void sprintfCustom(uint8_t *buf, timeCount_t *data);
static void incrementCurrentTime(void);
static void decrementCurrentTime(void);
//Global varibales
//-----------------------------------------------------------------------------

void initEnterMode(void){
  currentTime = IND_SEC;
  isHighStateTime = true;
}

static void incrementData(uint8_t *data, uint8_t edge){
  uint8_t tmp = *data;
  if (tmp < edge)
    tmp++;
  else
    tmp = 0;
  *data = tmp;
}

static void decrementData(uint8_t *data, uint8_t edge){
  uint8_t tmp = *data;
  if(tmp)
    tmp--;
  else
    tmp = edge;
  *data = tmp;
  //Bug occurs in production hex file. Code below doesn't work
  //if(*data)
  //  *data--;
  //else
  //  *data = edge;
}

static void incrementTime(timeCount_t *time)
{
  if (currentTime == IND_SEC)
    incrementData(&time->seconds, SECONDS_MAX);
  else if (currentTime == IND_MIN)
    incrementData(&time->minutes, MINUTES_MAX);
  else
    incrementData(&time->hours, HOURS_MAX);
}

static void decrementTime(timeCount_t *time){
  if (currentTime == IND_SEC)
    decrementData(&time->seconds, SECONDS_MAX);
  else if (currentTime == IND_MIN)
    decrementData(&time->minutes, MINUTES_MAX);
  else
    decrementData(&time->hours, HOURS_MAX);
}

static void sprintfCustom(uint8_t *buf, timeCount_t *data)
{
  if (currentTime == IND_SEC){
    buf[0] = data->seconds/10;
    buf[1] = data->seconds%10;
    buf[2] = 'c';
  }
  else if(currentTime == IND_MIN){
    buf[0] = data->minutes/10;
    buf[1] = data->minutes%10;
    buf[2] = 'n';
  }
  else{
    buf[0] = data->hours/10;
    buf[1] = data->hours%10;
    buf[2] = 'h';
  }
  buf[0] += '0';
  buf[1] += '0';
  
  if (isFlash)
  {
    buf[0] = ' ';
    buf[1] = ' ';
  }
  
  if (isHighStateTime)
    buf[3] = '.';
  else
    buf[3] = '\0';
  
  buf[4] = '\0';
}

static void incrementCurrentTime(void){
  if (isHighStateTime)
    incrementTime(&highStateTime);
  else
    incrementTime(&lowStateTime);
}

static void decrementCurrentTime(void){
  if (isHighStateTime)
    decrementTime(&highStateTime);
  else
    decrementTime(&lowStateTime);
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
      rc = RC_COMPLETE;
      initEnterMode();
      saveSettings();
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
      //Set mode settings to default before exit
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
  if (!isGUIUpdated)
    return;
  else
    isGUIUpdated = false;
  
  if (isHighStateTime)
      sprintfCustom(indicatorRawDataBuffer, &highStateTime);
    else
      sprintfCustom(indicatorRawDataBuffer, &lowStateTime);

  updateIndicatorData(indicatorRawDataBuffer);
}
