#ifndef INITPERIPH_H
#define INITPERIPH_H

#include "stm8s.h"

#define RELAY_GPIO_PORT         (GPIOA)
#define RELAY_GPIO_PIN          (GPIO_PIN_3)

#define BUTTONS_GPIO_PORT       (GPIOC)
#define BUTTON_SET_GPIO_PIN     (GPIO_PIN_3)
#define BUTTON_PLUS_GPIO_PIN    (GPIO_PIN_4)
#define BUTTON_MINUS_GPIO_PIN   (GPIO_PIN_5)

#define IND_DIGIT_1_PORT        (GPIOD)
#define IND_DIGIT_1_PIN         (GPIO_PIN_4)
#define IND_DIGIT_2_PORT        (GPIOB)
#define IND_DIGIT_2_PIN         (GPIO_PIN_5)
#define IND_DIGIT_3_PORT        (GPIOB)
#define IND_DIGIT_3_PIN         (GPIO_PIN_4)

#define IND_A_PORT              (GPIOD)
#define IND_A_PIN               (GPIO_PIN_5)
#define IND_B_PORT              (GPIOA)
#define IND_B_PIN               (GPIO_PIN_2)
#define IND_C_PORT              (GPIOC)
#define IND_C_PIN               (GPIO_PIN_7)
#define IND_D_PORT              (GPIOD)
#define IND_D_PIN               (GPIO_PIN_3)
#define IND_E_PORT              (GPIOD)
#define IND_E_PIN               (GPIO_PIN_1)
#define IND_F_PORT              (GPIOA)
#define IND_F_PIN               (GPIO_PIN_1)
#define IND_G_PORT              (GPIOC)
#define IND_G_PIN               (GPIO_PIN_6)
#define IND_POINT_PORT          (GPIOD)
#define IND_POINT_PIN           (GPIO_PIN_2)

void initPeriph(void);

#endif //INITPERIPH_H