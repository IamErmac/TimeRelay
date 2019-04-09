#include "counter.h"

//Private defines
#define SECONDS_MAX     59
#define MINUTES_MAX     59
#define HOURS_MAX       99
//Extern global variables
//Static global variables
//Static functions prototypes
static void incrementData(uint8_t *data, uint8_t edge);
static void decrementData(uint8_t *data, uint8_t edge);
//Global varibales
timeCount_t lowStateTime = {.seconds = 0, .minutes = 0, .hours = 0};
timeCount_t highStateTime = {.seconds = 0, .minutes = 0, .hours = 0};
//-----------------------------------------------------------------------------

static void incrementData(uint8_t *data, uint8_t edge){
  if (*data < edge)
    (*data)++;
  else
    (*data) = 0;
}

static void decrementData(uint8_t *data, uint8_t edge){
  if (*data)
    (*data)--;
  else
    *data = edge;
}

void incrementTime(timeCount_t *time, uint8_t currentTime)
{
  if (currentTime == IND_SEC)
    incrementData(&time->seconds, SECONDS_MAX);
  else if (currentTime == IND_MIN)
    incrementData(&time->minutes, MINUTES_MAX);
  else
    incrementData(&time->hours, HOURS_MAX);
}

void decrementTime(timeCount_t *time, uint8_t currentTime){
  if (currentTime == IND_SEC)
    decrementData(&time->seconds, SECONDS_MAX);
  else if (currentTime == IND_MIN)
    decrementData(&time->minutes, MINUTES_MAX);
  else
    decrementData(&time->hours, HOURS_MAX);
}

void decrementTimer(timeCount_t *time){
  if (time->seconds){  
    time->seconds--;
  }else{
    if (time->minutes){
      time->minutes--;
      time->seconds = SECONDS_MAX;
    }else{
      if (time->hours){
        time->hours--;
        time->minutes = MINUTES_MAX;
        time->seconds = SECONDS_MAX;
      }
    }
  }
}

bool isTimerSetToZero(timeCount_t *time){
  if (time->seconds || time->minutes || time->hours)
    return false;
  else
    return true;
}
