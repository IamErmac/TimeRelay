#include "initPeriph.h"

//Private defines
#define MCU_FREQ                16000000ul
#define TMR_1_MS_DIV            ((MCU_FREQ/1000)-1)
//Extern global variables
//Static global variables
//Static functions prototypes
//Global varibales
//-----------------------------------------------------------------------------

void initPeriph(void){
  //Relay init
  GPIO_Init(RELAY_GPIO_PORT, RELAY_GPIO_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  //Buttons init
  GPIO_Init(BUTTONS_GPIO_PORT, (GPIO_Pin_TypeDef)(BUTTON_SET_GPIO_PIN | BUTTON_PLUS_GPIO_PIN | BUTTON_MINUS_GPIO_PIN), GPIO_MODE_IN_PU_NO_IT);
  //Indicator digits init
  GPIO_Init(IND_DIGIT_1_PORT, IND_DIGIT_1_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(IND_DIGIT_2_PORT, IND_DIGIT_2_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(IND_DIGIT_3_PORT, IND_DIGIT_3_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
  //Indicator segments init
  GPIO_Init(IND_A_PORT, IND_A_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(IND_B_PORT, IND_B_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(IND_C_PORT, IND_C_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(IND_D_PORT, IND_D_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(IND_E_PORT, IND_E_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(IND_F_PORT, IND_F_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(IND_G_PORT, IND_G_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(IND_POINT_PORT, IND_POINT_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  //Clock init at 16MHz from internal HSI
  CLK_DeInit();
  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);
  CLK_SYSCLKConfig(CLK_PRESCALER_HSIDIV1);
  CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
  //EEPROM init
  FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
  FLASH_Unlock(FLASH_MEMTYPE_DATA);
  //Timer 1 init
  TIM1_TimeBaseInit(0, TIM1_COUNTERMODE_UP, TMR_1_MS_DIV, 0);
  TIM1_ClearFlag(TIM1_FLAG_UPDATE);
  TIM1_ITConfig(TIM1_IT_UPDATE, ENABLE);
  TIM1_Cmd(ENABLE);
  //Enable interrupts
  enableInterrupts();
}