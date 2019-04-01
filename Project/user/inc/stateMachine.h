#ifndef STATEMACHINE_H
#define STATEMACHINE_H

#include "stm8s.h"
#include <stdbool.h>

enum{
    RC_NOT_COMPLETE = 0,
    RC_COMPLETE,
    RC_ERROR
};

#endif //STATEMACHINE_H