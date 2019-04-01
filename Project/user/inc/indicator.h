#ifndef INDICATOR_H
#define INDICATOR_H

#include "stm8s_it.h"
#include <stdbool.h>
#include "initPeriph.h"

#define IND_COUNT       3
#define IND_RAW_DATA    (IND_COUNT*2 + 1)

 enum{
  SYM_0 = 0x3f,
  SYM_1 = 0x06,
  SYM_2 = 0x5b,
  SYM_3 = 0x4f,
  SYM_4 = 0x66,
  SYM_5 = 0x6d,
  SYM_6 = 0x7d,
  SYM_7 = 0x07,
  SYM_8 = 0x7f,
  SYM_9 = 0x6f,
  SYM_A = 0x77,
  SYM_b = 0x7c,
  SYM_C = 0x39,
  SYM_d = 0x5e,
  SYM_E = 0x79,
  SYM_F = 0x71,
  SYM_H = 0x76,
  SYM_t = 0x78,
  SYM_P = 0x73,
  SYM_L = 0x38,
  SYM_MINUS = 0x40,
  SYM_DOT = 0x80,
  SYM_BLANK  = 0x00,
  SYM_h = 0x74,
  SYM_c = 0x58,
  SYM_n = 0x54
};

 enum{
  SEG_1 = 0x01,
  SEG_2 = 0x02,
  SEG_3 = 0x03,
 };
 
 void switchIndicatorDigit(void);
 void updateIndicatorData(uint8_t* str);

#endif //INDICATOR_H