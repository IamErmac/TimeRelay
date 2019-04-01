#include "indicator.h"

uint8_t indicatorBuffer[IND_COUNT];
uint8_t indicatorRawDataBuffer[IND_RAW_DATA];
bool isGUIUpdated = true;

void writeDataToIndicator(uint8_t data, uint8_t segment){
  GPIO_WriteHigh(IND_DIGIT_1_PORT, IND_DIGIT_1_PIN);
  GPIO_WriteHigh(IND_DIGIT_2_PORT, IND_DIGIT_2_PIN);
  GPIO_WriteHigh(IND_DIGIT_3_PORT, IND_DIGIT_3_PIN);
  
  if(data & 0x01)
    GPIO_WriteHigh(IND_A_PORT, (GPIO_Pin_TypeDef)IND_A_PIN);
  else
    GPIO_WriteLow(IND_A_PORT, (GPIO_Pin_TypeDef)IND_A_PIN);
  
  if(data & 0x02)
    GPIO_WriteHigh(IND_B_PORT, (GPIO_Pin_TypeDef)IND_B_PIN);
  else
    GPIO_WriteLow(IND_B_PORT, (GPIO_Pin_TypeDef)IND_B_PIN);
    
  if(data & 0x04)
    GPIO_WriteHigh(IND_C_PORT, (GPIO_Pin_TypeDef)IND_C_PIN);
  else
    GPIO_WriteLow(IND_C_PORT, (GPIO_Pin_TypeDef)IND_C_PIN);
    
  if(data & 0x08)
    GPIO_WriteHigh(IND_D_PORT, (GPIO_Pin_TypeDef)IND_D_PIN);
  else
    GPIO_WriteLow(IND_D_PORT, (GPIO_Pin_TypeDef)IND_D_PIN);
    
  if(data & 0x10)
    GPIO_WriteHigh(IND_E_PORT, (GPIO_Pin_TypeDef)IND_E_PIN);
  else
    GPIO_WriteLow(IND_E_PORT, (GPIO_Pin_TypeDef)IND_E_PIN);
    
  if(data & 0x20)
    GPIO_WriteHigh(IND_F_PORT, (GPIO_Pin_TypeDef)IND_F_PIN);
  else
    GPIO_WriteLow(IND_F_PORT, (GPIO_Pin_TypeDef)IND_F_PIN);
    
  if(data & 0x40)
    GPIO_WriteHigh(IND_G_PORT, (GPIO_Pin_TypeDef)IND_G_PIN);
  else
    GPIO_WriteLow(IND_G_PORT, (GPIO_Pin_TypeDef)IND_G_PIN);
    
  if(data & 0x80)
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
  
  writeDataToIndicator(indicatorBuffer[curDigit], curDigit + 1);
  
  if (++curDigit > 3)
    curDigit = 0;
}

static uint8_t convertASCIIToIndicatorNumber(uint8_t rawDigit){
  switch(rawDigit)
  {
    default: return SYM_BLANK;
    case '0': return SYM_0;
    case '1': return SYM_1;
    case '2': return SYM_2;
    case '3': return SYM_3;
    case '4': return SYM_4;
    case '5': return SYM_5;
    case '6': return SYM_6;
    case '7': return SYM_7;
    case '8': return SYM_8;
    case '9': return SYM_9;
    case '.': return SYM_DOT;
    case '-': return SYM_MINUS;
    case 'a':
    case 'A': return SYM_A;
    case 'B':
    case 'b': return SYM_b;
    case 'c': return SYM_c;
    case 'C': return SYM_C;
    case 'D':
    case 'd': return SYM_d;
    case 'e':
    case 'E': return SYM_E;
    case 'f':
    case 'F': return SYM_F;
    case 'H': return SYM_H;
    case 'h': return SYM_h;
    case 'n': return SYM_n;
    case 't': return SYM_t;
    case 'p':
    case 'P': return SYM_P;
    case 'L': return SYM_L;
  }
}

void updateIndicatorData(uint8_t* str){
  uint8_t digitCounter = 0;
  uint8_t currentDigit = convertASCIIToIndicatorNumber('0');

  for(uint8_t i = 0; i < IND_RAW_DATA; i++){
    if (digitCounter == IND_COUNT)
      break;
    
    if (str[i] == '.'){
      currentDigit += SYM_DOT;
      indicatorBuffer[digitCounter] = currentDigit;
      digitCounter++;
      continue;
    }else{
      currentDigit = convertASCIIToIndicatorNumber(str[i]);
      if (str[i + 1] != '.'){
        //update
        indicatorBuffer[digitCounter] = currentDigit;
        digitCounter++;
      }else{
        continue;
      }
    }
  }
}

