/*
 * utils.c
 *
 *  Created on: 26 maj 2022
 *      Author: Grzegorzewski Szymon
 */
#include <avr/io.h>
#include <util/delay.h>
#include "utils.h"

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

