/*
 * utils.c
 *
 *  Created on: 26 maj 2022
 *      Author: Grzegorzewski Szymon
 */
#include <avr/io.h>
#include <util/delay.h>
#include "utils.h"
#include <avr/interrupt.h>

void Led_Init()
{
	LED0_INIT;
	LED1_INIT;
}
void BlinkLed()
{
	LED0_ON;
	LED1_OFF;
	_delay_ms(150);
	LED0_OFF;
	LED1_OFF;
}

uint32_t millis;
void Timer0_Init()
{
	sei();// allow interrupts

	TCCR0A |= (1<<WGM01); //CTC mode
	TIMSK0 |= (1<<OCIE0A); //Compare match
	TCCR0B |= (1<<CS00) | (1<<CS01); //Prescaler = 64     8000000\64 = 125000
	OCR0A = 124;                     //                   125000\(124+1) = 1000
}

ISR(TIMER0_COMPA_vect)
{
	millis++;
}
