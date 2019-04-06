#include "init_timer1.h"

//Private defines
#define TMR_1_MS_DIV            ((MCU_FREQ/1000)-1)
//Extern global variables
//Static global variables
//Static functions prototypes
//Global varibales
//-----------------------------------------------------------------------------

void initTimer1(void){
  TIM1_TimeBaseInit(0, TIM1_COUNTERMODE_UP, TMR_1_MS_DIV, 0);
  TIM1_ClearFlag(TIM1_FLAG_UPDATE);
  TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);
  TIM1_Cmd(ENABLE);
}