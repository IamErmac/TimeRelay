#ifndef MODEWORK_H
#define MODEWORK_H

#include "stm8s.h"
#include <stdbool.h>
#include "stateMachine.h"
#include "button.h"
#include "indicator.h"
#include "SWTimer.h"
#include "counter.h"
#include "initPeriph.h"

void initWorkMode(void);
uint8_t handleWorkMode(void);

#endif //MODEWORK_H