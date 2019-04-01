#ifndef MODEENTER_H
#define MODEENTER_H

#include "stm8s.h"
#include <stdbool.h>
#include "stateMachine.h"
#include "button.h"
#include "indicator.h"
#include "eepromSettings.h"
#include "SWTimer.h"
#include "counter.h"

void initEnterMode(void);
uint8_t handleEnterMode(void);

enum{
  IND_SEC = 0,
  IND_MIN,
  IND_HOUR
};

#endif //MODEENTER_H