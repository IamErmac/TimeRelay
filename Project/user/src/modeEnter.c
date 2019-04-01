#include "modeEnter.h"

#define HIGH_TIME_EDGE (360000ul - 1)
#define SECONDS_MAX 59
#define MINUTES_MAX 59
#define HOURS_MAX 99

extern volatile button_t plusButton, minusButton, setButton;
extern bool isGUIUpdated;
extern uint8_t indicatorRawDataBuffer[IND_RAW_DATA];

static bool isFlash = false;
static bool isTimeUp = true;
static uint8_t currentTime = IND_SEC;

extern timeCount_t timeUp;
extern timeCount_t timeDown;

static void updateGUIEnterMode(void);

void initEnterMode(void){
  currentTime = IND_SEC;
  isTimeUp = true;
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
  //  *data = tmp;
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
  
  if (isTimeUp)
    buf[3] = '\0';
  else
    buf[3] = '.';
  
  buf[4] = '\0';
}

uint8_t handleEnterMode(void)
{
  uint8_t rc = RC_NOT_COMPLETE;
  
  if (plusButton.wasPressed){
    clearButtonEvent(&plusButton);
    
    if (isTimeUp)
      incrementTime(&timeUp);
    else
      incrementTime(&timeDown);
    
    isGUIUpdated = true;
  }
  
  if (minusButton.wasPressed){
    clearButtonEvent(&minusButton);
    
     if (isTimeUp)
      decrementTime(&timeUp);
    else
      decrementTime(&timeDown);
    
    isGUIUpdated = true;
  }
  
  if (setButton.wasPressed && setButton.isShort){
    clearButtonEvent(&setButton);
    
    if (currentTime < IND_HOUR)
      currentTime++;
    else
      currentTime = IND_SEC;
    
    if (currentTime == IND_SEC)
      isTimeUp = !isTimeUp;
    
    isGUIUpdated = true;
  }
  
  if (setButton.wasPressed && setButton.isLong){
    clearButtonEvent(&setButton);

    if ((timeUp.seconds || timeUp.minutes || timeUp.hours)&&(timeDown.seconds || timeDown.minutes || timeDown.hours)){
      rc = RC_COMPLETE;
      //Set mode settings to default before exit
      initEnterMode();
      saveSettings();
    }
  }

  if (isTimeToFlash())
  {
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
  
  if (isTimeUp)
      sprintfCustom(indicatorRawDataBuffer, &timeUp);
    else
      sprintfCustom(indicatorRawDataBuffer, &timeDown);

  updateIndicatorData(indicatorRawDataBuffer);
}