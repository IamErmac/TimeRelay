#ifndef COUNTER_H
#define COUNTER_H

#include "stm8s.h"
#include <stdbool.h>

typedef struct{
  uint8_t seconds;
  uint8_t minutes;
  uint8_t hours;
}timeCount_t;

#endif //COUNTER_H