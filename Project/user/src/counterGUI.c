#include "counterGUI.h"

//Private defines
//Extern global variables
//Static global variables
static uint8_t indicatorRawDataBuffer[IND_RAW_DATA];
//Static functions prototypes
//Global varibales
//-----------------------------------------------------------------------------

uint8_t getCurrentTime(timeCount_t* data, uint8_t currentTime){
  if (currentTime == IND_SEC)
    return data->seconds;
  else if(currentTime == IND_MIN)
    return data->minutes;
  else
    return data->hours;
}

uint8_t getCurrentTimeSign(uint8_t currentTime){
  if (currentTime == IND_SEC)
    return 'c';
  else if(currentTime == IND_MIN)
    return 'n';
  else
    return 'h';
}

uint8_t getTheHighestTime(timeCount_t* data){
  if (data->hours)
    return data->hours;
  else if(data->minutes)
    return data->minutes;
  else
    return data->seconds;
}

uint8_t getTheHighestTimeSign(timeCount_t* data){
  if (data->hours)
    return 'h';
  else if(data->minutes)
    return 'n';
  else
    return 'c';
}

void printTimeData(uint8_t time, uint8_t timeSign, bool isDot, bool isFlash){
  if (isFlash){
    indicatorRawDataBuffer[0] = ' ';
    indicatorRawDataBuffer[1] = ' ';
  }else{
    indicatorRawDataBuffer[0] = time/10 + '0';
    indicatorRawDataBuffer[1] = time%10 + '0';
  }
  
  indicatorRawDataBuffer[2] = timeSign;
    
  if (isDot){
    indicatorRawDataBuffer[3] = '.';
    indicatorRawDataBuffer[4] = '\0'; 
  }else
    indicatorRawDataBuffer[3] = '\0'; 
  
  updateIndicatorData(indicatorRawDataBuffer);
}
