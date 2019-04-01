#include "button.h"

//Private defines
#define SHORT_PRESS	10
#define LONG_PRESS	1000
//Extern global variables
//Static global variables
//Static functions prototypes
//Global varibales
volatile button_t plusButton, minusButton, setButton;
//-----------------------------------------------------------------------------

void buttonHandler(volatile button_t *button, bool buttonState){
  if (button->isBeingProcessed)
    return;

  if (buttonState){
    if (button->counter < LONG_PRESS)
      button->counter++;
    
    button->isBeingPressed = true;
    button->wasPressed = false;
    
    if (button->counter >= LONG_PRESS){
      button->isLong = true;
      button->isShort = false;
    }else if (button->counter >= SHORT_PRESS){
      button->isLong = false;
      button->isShort = true;
    }else{
      button->isLong = false;
      button->isShort = false;
    }
  }
  else if (buttonState != button->lastState){
    button->isBeingPressed = false;
    button->wasPressed = true;
    button->counter = 0;
  }
  button->lastState = buttonState;
}

void clearButtonEvent(volatile button_t *button){
  button->isBeingProcessed = true;
  
  button->isLong = false;
  button->wasHandled = false;
  button->isShort = false;
  button->isBeingPressed = false;
  button->wasPressed = false;
  button->counter = 0;
  button->lastState = false;

  button->isBeingProcessed = false;
}