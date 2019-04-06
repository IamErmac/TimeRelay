#ifndef INDICATOR_H
#define INDICATOR_H

#include "stm8s_it.h"
#include <stdbool.h>
#include "init_gpio.h"
#include "sevenDigit.h"

 enum{
  SEG_1 = 0x0,
  SEG_2,
  SEG_3,
  SEG_ALL
 };

#define IND_RAW_DATA    (SEG_ALL*2 + 1)

void switchIndicatorDigit(void);
void updateIndicatorData(uint8_t* str);

#endif //INDICATOR_H