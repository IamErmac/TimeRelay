#ifndef EEPROMSETTINGS_H
#define EEPROMSETTINGS_H

#include "stm8s.h"
#include <stdbool.h>
#include "stateMachine.h"
#include "counter.h"

void loadSettings(void);
void saveSettings(void);

#endif //EEPROMSETTINGS_H