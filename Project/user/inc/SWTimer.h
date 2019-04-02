#ifndef SWTIMER_H
#define SWTIMER_H

#include "stm8s.h"
#include <stdbool.h>
#include "indicator.h"
#include "button.h"

void handleFlashTimer(void);
void handleSecondTimer(void);
bool isTimeToFlash(void);
bool isSecondPast(void);
void setSecondTimerToZero(void);
void setFlashTimerToZero(void);
void handleFastCountTimer(void);
bool isFastCountTime(void);
void setFastCountTimerToZero(void);

#endif //SWTIMER_H