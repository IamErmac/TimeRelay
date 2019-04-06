#include "init_gpio.h"

//Private defines
//Extern global variables
//Static global variables
//Static functions prototypes
static void initRelay(void);
static void initButtons(void);
static void initIndicatorDigits(void);
static void initIndicatorSegments(void);
//Global varibales
//-----------------------------------------------------------------------------

static void initRelay(void){
  GPIO_Init(RELAY_GPIO_PORT, RELAY_GPIO_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
}

static void initButtons(void){
  GPIO_Init(BUTTONS_GPIO_PORT, (GPIO_Pin_TypeDef)(BUTTON_SET_GPIO_PIN | BUTTON_PLUS_GPIO_PIN | BUTTON_MINUS_GPIO_PIN), GPIO_MODE_IN_PU_NO_IT);
}

static void initIndicatorDigits(void){
  GPIO_Init(IND_DIGIT_1_PORT, IND_DIGIT_1_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(IND_DIGIT_2_PORT, IND_DIGIT_2_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(IND_DIGIT_3_PORT, IND_DIGIT_3_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
}

static void initIndicatorSegments(void){
  GPIO_Init(IND_A_PORT, IND_A_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(IND_B_PORT, IND_B_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(IND_C_PORT, IND_C_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(IND_D_PORT, IND_D_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(IND_E_PORT, IND_E_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(IND_F_PORT, IND_F_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(IND_G_PORT, IND_G_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
  GPIO_Init(IND_POINT_PORT, IND_POINT_PIN, GPIO_MODE_OUT_PP_LOW_FAST);
}

void initGPIO(void){
  initRelay();
  initButtons();
  initIndicatorDigits();
  initIndicatorSegments();
}