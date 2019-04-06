#include "indicator.h"

//Private defines
enum{
  IND_A_POS = ((uint8_t)(1 << 0)),
  IND_B_POS = ((uint8_t)(1 << 1)),
  IND_C_POS = ((uint8_t)(1 << 2)),
  IND_D_POS = ((uint8_t)(1 << 3)),
  IND_E_POS = ((uint8_t)(1 << 4)),
  IND_F_POS = ((uint8_t)(1 << 5)),
  IND_G_POS = ((uint8_t)(1 << 6)),
  IND_DP_POS = ((uint8_t)(1 << 7))
};
//Extern global variables
//Static global variables
static uint8_t indicatorBuffer[SEG_ALL];
//Static functions prototypes
static void writeDataToIndicator(uint8_t data, uint8_t segment);
//Global varibales
//-----------------------------------------------------------------------------

static void writeDataToIndicator(uint8_t data, uint8_t segment){
  GPIO_WriteHigh(IND_DIGIT_1_PORT, IND_DIGIT_1_PIN);
  GPIO_WriteHigh(IND_DIGIT_2_PORT, IND_DIGIT_2_PIN);
  GPIO_WriteHigh(IND_DIGIT_3_PORT, IND_DIGIT_3_PIN);
  
  if(data & IND_A_POS)
    GPIO_WriteHigh(IND_A_PORT, (GPIO_Pin_TypeDef)IND_A_PIN);
  else
    GPIO_WriteLow(IND_A_PORT, (GPIO_Pin_TypeDef)IND_A_PIN);
  
  if(data & IND_B_POS)
    GPIO_WriteHigh(IND_B_PORT, (GPIO_Pin_TypeDef)IND_B_PIN);
  else
    GPIO_WriteLow(IND_B_PORT, (GPIO_Pin_TypeDef)IND_B_PIN);
    
  if(data & IND_C_POS)
    GPIO_WriteHigh(IND_C_PORT, (GPIO_Pin_TypeDef)IND_C_PIN);
  else
    GPIO_WriteLow(IND_C_PORT, (GPIO_Pin_TypeDef)IND_C_PIN);
    
  if(data & IND_D_POS)
    GPIO_WriteHigh(IND_D_PORT, (GPIO_Pin_TypeDef)IND_D_PIN);
  else
    GPIO_WriteLow(IND_D_PORT, (GPIO_Pin_TypeDef)IND_D_PIN);
    
  if(data & IND_E_POS)
    GPIO_WriteHigh(IND_E_PORT, (GPIO_Pin_TypeDef)IND_E_PIN);
  else
    GPIO_WriteLow(IND_E_PORT, (GPIO_Pin_TypeDef)IND_E_PIN);
    
  if(data & IND_F_POS)
    GPIO_WriteHigh(IND_F_PORT, (GPIO_Pin_TypeDef)IND_F_PIN);
  else
    GPIO_WriteLow(IND_F_PORT, (GPIO_Pin_TypeDef)IND_F_PIN);
    
  if(data & IND_G_POS)
    GPIO_WriteHigh(IND_G_PORT, (GPIO_Pin_TypeDef)IND_G_PIN);
  else
    GPIO_WriteLow(IND_G_PORT, (GPIO_Pin_TypeDef)IND_G_PIN);
    
  if(data & IND_DP_POS)
    GPIO_WriteHigh(IND_POINT_PORT, (GPIO_Pin_TypeDef)IND_POINT_PIN);
  else
    GPIO_WriteLow(IND_POINT_PORT, (GPIO_Pin_TypeDef)IND_POINT_PIN);
  
  if (segment == SEG_1){
    GPIO_WriteLow(IND_DIGIT_1_PORT, IND_DIGIT_1_PIN);
    GPIO_WriteHigh(IND_DIGIT_2_PORT, IND_DIGIT_2_PIN);
    GPIO_WriteHigh(IND_DIGIT_3_PORT, IND_DIGIT_3_PIN);
  }else if (segment == SEG_2){
    GPIO_WriteHigh(IND_DIGIT_1_PORT, IND_DIGIT_1_PIN);
    GPIO_WriteLow(IND_DIGIT_2_PORT, IND_DIGIT_2_PIN);
    GPIO_WriteHigh(IND_DIGIT_3_PORT, IND_DIGIT_3_PIN);
  }else if (segment == SEG_3){
    GPIO_WriteHigh(IND_DIGIT_1_PORT, IND_DIGIT_1_PIN);
    GPIO_WriteHigh(IND_DIGIT_2_PORT, IND_DIGIT_2_PIN);
    GPIO_WriteLow(IND_DIGIT_3_PORT, IND_DIGIT_3_PIN);
  }else{
    return;
  }
}

void switchIndicatorDigit(void){
  static uint8_t curDigit = 0;
  writeDataToIndicator(indicatorBuffer[curDigit], curDigit);
  if (++curDigit > SEG_ALL)
    curDigit = 0;
}

void updateIndicatorData(uint8_t* str){
  uint8_t digitCounter = 0;
  uint8_t currentDigit = convertASCIIToSevenDigit(' ');

  for(uint8_t i = 0; i < IND_RAW_DATA; i++){
    if ((digitCounter == SEG_ALL) || !str[i])
      break;
    
    if (str[i] == '.'){
      currentDigit += convertASCIIToSevenDigit('.');
      indicatorBuffer[digitCounter] = currentDigit;
      digitCounter++;
      continue;
    }else{
      currentDigit = convertASCIIToSevenDigit(str[i]);
      if ((i + 1 < IND_RAW_DATA)&&(str[i + 1] != '.')){
        //update
        indicatorBuffer[digitCounter] = currentDigit;
        digitCounter++;
      }else{
        continue;
      }
    }
  }
}
