#ifndef MODEENTER_H
#define MODEENTER_H

#include "stm8s.h"
#include <stdbool.h>
#include "stateMachine.h"
#include "button.h"
#include "eepromSettings.h"
#include "SWTimer.h"
#include "counter.h"
#include "counterGUI.h"

void initEnterMode(void);
uint8_t handleEnterMode(void);

#endif //MODEENTER_H