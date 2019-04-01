#include "modeWork.h"

//Private defines
#define HIGH_STATE_START (true)
//Extern global variables
extern timeCount_t lowStateTime, highStateTime;
extern bool isGUIUpdated;
extern uint8_t indicatorRawDataBuffer[IND_RAW_DATA];
extern volatile button_t setButton;
//Static global variables
static bool isHighStateTime = true;
static bool isTimerDirectionChanged = false;
static bool isDot = false;
static timeCount_t tmpTimer = {0,0,0};
//Static functions prototypes
static void loadNewTimerData(void);
static void decrementTimer(timeCount_t *time);
static void sprintfCustom(uint8_t *buf, timeCount_t *data);
static void updateGUIWorkMode(void);
//Global varibales
//-----------------------------------------------------------------------------

static void loadNewTimerData(void){
  if (isHighStateTime){
    tmpTimer.seconds = highStateTime.seconds;
    tmpTimer.minutes = highStateTime.minutes;
    tmpTimer.hours = highStateTime.hours;
    sprintfCustom(indicatorRawDataBuffer, &tmpTimer);
    GPIO_WriteHigh(RELAY_GPIO_PORT, RELAY_GPIO_PIN);
  }else{
    tmpTimer.seconds = lowStateTime.seconds;
    tmpTimer.minutes = lowStateTime.minutes;
    tmpTimer.hours = lowStateTime.hours;
    sprintfCustom(indicatorRawDataBuffer, &tmpTimer);
    GPIO_WriteLow(RELAY_GPIO_PORT, RELAY_GPIO_PIN);
  }
}

void initWorkMode(void){
  
#ifdef HIGH_STATE_START
  isHighStateTime = true;
#else
  isHighStateTime = false;
#endif
  
  loadNewTimerData();
  
  isGUIUpdated = true;
  setSecondTimerToZero();
}

static void decrementTimer(timeCount_t *time){
  if (time->seconds){  
    time->seconds--;
  }else{
    if (time->minutes){
      time->minutes--;
      time->seconds = 59;
    }else{
      if (time->hours){
        time->hours--;
        time->minutes = 59;
        time->seconds = 59;
      }//else{
        //isTimerDirectionChanged = true;
      //}
    }
  }
  if (!(time->seconds || time->minutes || time->hours))
    isTimerDirectionChanged = true;
}

static void sprintfCustom(uint8_t *buf, timeCount_t *data){
  if (data->hours){
    buf[0] = data->hours/10;
    buf[1] = data->hours%10;
    buf[2] = 'h';
  }else if(data->minutes){
    buf[0] = data->minutes/10;
    buf[1] = data->minutes%10;
    buf[2] = 'n';
  }else{
    buf[0] = data->seconds/10;
    buf[1] = data->seconds%10;
    buf[2] = 'c';
  }
  buf[0] += '0';
  buf[1] += '0';
  
  if (isDot)
    buf[3] = '\0';
  else
    buf[3] = '.';
  
  buf[4] = '\0';
}

static void updateGUIWorkMode(void){
  if (!isGUIUpdated)
    return;
  
  isGUIUpdated = false;
  
  updateIndicatorData(indicatorRawDataBuffer);
}

uint8_t handleWorkMode(void){
  
  uint8_t rc = RC_NOT_COMPLETE;

  if(isSecondPast()){
    isDot = !isDot;
    isGUIUpdated = true;
   
    decrementTimer(&tmpTimer);
    
    sprintfCustom(indicatorRawDataBuffer, &tmpTimer);
    
    if (isTimerDirectionChanged){
      isTimerDirectionChanged = false;
      isHighStateTime = !isHighStateTime;
      loadNewTimerData();
      sprintfCustom(indicatorRawDataBuffer, &tmpTimer);
    }
  }
  
  if (setButton.wasPressed && setButton.isLong){
    clearButtonEvent(&setButton);
    rc = RC_COMPLETE;
    GPIO_WriteLow(RELAY_GPIO_PORT, RELAY_GPIO_PIN);
  }
  
  updateGUIWorkMode();
  
  return rc;
}