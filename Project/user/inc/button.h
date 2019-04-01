#ifndef BUTTON_H
#define BUTTON_H

#include "stm8s_it.h"
#include <stdbool.h>

typedef struct{
  bool isBeingPressed;
  bool wasPressed;
  bool isShort;
  bool isLong;
  bool isBeingProcessed;
  bool lastState;
  bool wasHandled;
  uint16_t counter;
}button_t;

void buttonHandler(volatile button_t *button, bool buttonState);
void clearButtonEvent(volatile button_t *button);

#endif //BUTTON_H