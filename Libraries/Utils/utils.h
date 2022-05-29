/*
 * utils.h
 *
 *  Created on: 26 maj 2022
 *      Author: Grzegorzewski Szymon
 */

#ifndef LIBRARIES_UTILS_UTILS_H_
#define LIBRARIES_UTILS_UTILS_H_

#define LED0_INIT DDRB |=  (1<<PB1)
#define LED0_ON  PORTB |=  (1<<PB1)
#define LED0_OFF PORTB &=~ (1<<PB1)
#define LED0_TOG PORTB ^=  (1<<PB1)

#define LED1_INIT DDRB |=  (1<<PB2)
#define LED1_ON  PORTB |=  (1<<PB2)
#define LED1_OFF PORTB &=~ (1<<PB2)
#define LED1_TOG PORTB ^=  (1<<PB2)

void Led_Init();
void BlinkLed();

void Timer0_Init();//millis

#endif /* LIBRARIES_UTILS_UTILS_H_ */
