#include "sevenDigit.h"

//Private defines
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
//Extern global variables
//Static global variables
//Static functions prototypes
//Global varibales
//-----------------------------------------------------------------------------

uint8_t convertASCIIToSevenDigit(uint8_t dataASCII){
  switch(dataASCII){
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
