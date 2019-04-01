#include "modeMain.h"

static modes_e currentMode = MODE_BOOT;
static modes_e nextMode = MODE_SAME;

void switchMode(void)
{
  switch(currentMode){
    default:
      currentMode = MODE_SHUTDOWN;
      nextMode = MODE_SAME;
      break;
      
    case MODE_BOOT:
      nextMode = MODE_ENTER;
      initEnterMode();
      break;
      
    case MODE_ENTER:
      if (handleEnterMode() == RC_COMPLETE){
        nextMode = MODE_WORK;
        initWorkMode();
      }
      break;
      
    case MODE_WORK:
      if (handleWorkMode() == RC_COMPLETE)
        nextMode = MODE_ENTER;
      break;
  }
  
  if (currentMode != MODE_SAME)
    currentMode = nextMode;

  switchIndicatorDigit();
}
