#ifndef INDICATETIME_H
#define INDICATETIME_H

#include "indicator.h"
#include "counter.h"

uint8_t getCurrentTime(timeCount_t* data, uint8_t currentTime);
uint8_t getCurrentTimeSign(uint8_t currentTime);
uint8_t getTheHighestTime(timeCount_t* data);
uint8_t getTheHighestTimeSign(timeCount_t* data);
void printTimeData(uint8_t time, uint8_t timeSign, bool isDot, bool isFlash);

#endif //INDICATETIME_H