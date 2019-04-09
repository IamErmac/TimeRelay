#ifndef MODEMAIN_H
#define MODEMAIN_H

#include "stm8s.h"
#include <stdbool.h>
#include "stateMachine.h"

#include "modeEnter.h"
#include "modeWork.h"

typedef enum{
	MODE_SAME = 0,
	MODE_BOOT,
	MODE_SHUTDOWN,
	MODE_MENU,
	MODE_ENTER,
	MODE_WORK,
	MODE_MAX
}modes_e;

void switchMode(void);

#endif //MODEMAIN_H