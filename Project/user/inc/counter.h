#ifndef COUNTER_H
#define COUNTER_H

#include "stm8s.h"
#include <stdbool.h>

enum{
  IND_SEC = 0,
  IND_MIN,
  IND_HOUR
};

typedef struct{
  uint8_t seconds;
  uint8_t minutes;
  uint8_t hours;
}timeCount_t;

void incrementTime(timeCount_t *time, uint8_t currentTime);
void decrementTime(timeCount_t *time, uint8_t currentTime);
void decrementTimer(timeCount_t *time);
bool isTimerSetToZero(timeCount_t *time);

#endif //COUNTER_H