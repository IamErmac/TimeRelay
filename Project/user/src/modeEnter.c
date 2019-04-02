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
//Global varibales
//-----------------------------------------------------------------------------

void initEnterMode(void){
  currentTime = IND_SEC;
  isHighStateTime = false;
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
    buf[3] = '\0';
  else
    buf[3] = '.';
  
  buf[4] = '\0';
}

void incrementCurrentTime(void){
  if (isHighStateTime)
    incrementTime(&highStateTime);
  else
    incrementTime(&lowStateTime);
}

void decrementCurrentTime(void){
  if (isHighStateTime)
    decrementTime(&highStateTime);
  else
    decrementTime(&lowStateTime);
}

uint8_t handleEnterMode(void)
{
  uint8_t rc = RC_NOT_COMPLETE;
  
  if (plusButton.wasPressed && plusButton.isShort){
    clearButtonEvent(&plusButton);
    incrementCurrentTime();
    isGUIUpdated = true;
  }
  
  if (plusButton.isBeingPressed && plusButton.isLong){
    if (isFastCountTime()){
      incrementCurrentTime();
      isGUIUpdated = true;
    }
  }
  
  if(plusButton.wasPressed && plusButton.isLong){
    clearButtonEvent(&plusButton);
  }
  
  if (minusButton.wasPressed && minusButton.isShort){
    clearButtonEvent(&plusButton);
    decrementCurrentTime();
    isGUIUpdated = true;
  }
  
  if (minusButton.isBeingPressed && minusButton.isLong){
    if (isFastCountTime()){
      decrementCurrentTime();
      isGUIUpdated = true;
    }
  }
  
  if(minusButton.wasPressed && minusButton.isLong){
    clearButtonEvent(&minusButton);
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
      saveSettings();
    }
  }
  
  if (setButton.wasHandled && setButton.wasPressed){
    clearButtonEvent(&setButton);
  }

  if (isTimeToFlash()){
    isGUIUpdated = true;
    isFlash = !isFlash;
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
