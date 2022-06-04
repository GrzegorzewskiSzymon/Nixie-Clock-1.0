/*
 * SN74141.c
 *
 *  Created on: 28 maj 2022
 *      Author: Grzegorzewski Szymon
 */
#include <avr/io.h>
#include <util/delay.h>
#include "SN74141.h"
#include "AnodesMultiplexer.h"
#include "../Utils/utils.h"


void BCD_Init()
{
	BCD_INIT;
}

uint64_t millis_DisplayTime = 0;
uint64_t millis_SlowMultiplexing = 0;
void DisplayTime(int8_t hours, int8_t minutes)
{
	uint16_t slower = 1;
	if(millis-millis_SlowMultiplexing > (1000ULL*60ULL*TIME_BETWEEN_SLOW_MULTIPLEXING))//when it's  time to "repair" balance in nixie tubes
	{
		LED1_ON;
		slower = 400;
	}
	if(millis-millis_SlowMultiplexing > ((1000ULL*60ULL*TIME_BETWEEN_SLOW_MULTIPLEXING)+(1000ULL*60ULL*TIME_OF_SLOW_MULTIPLEXING)) )
	{
		LED1_OFF;
		slower = 1;
		millis_SlowMultiplexing = millis;

	}


	if(millis-millis_DisplayTime > 12*slower)//Its time to display units of minutes
	{
		PORTD = minutes%10;

		NIXIE_4_OFF;
		NIXIE_3_OFF;
		NIXIE_2_OFF;
		NIXIE_1_ON;

		millis_DisplayTime = millis;//set actual time after full cicle
		return;
	}

	if(millis-millis_DisplayTime > 9*slower)//Its time to display tens of minutes
	{
		PORTD = minutes/10;

		NIXIE_4_OFF;
		NIXIE_3_OFF;
		NIXIE_2_ON;
		NIXIE_1_OFF;

		return;
	}

	if(millis-millis_DisplayTime > 6*slower)//Its time to display units of hours
	{
		PORTD = hours%10;
		NIXIE_4_OFF;
		NIXIE_3_ON;
		NIXIE_2_OFF;
		NIXIE_1_OFF;

		return;
	}

	if(millis-millis_DisplayTime > 3*slower &&hours > 9)//Its time to display tens of hours
	{
		PORTD = hours/10;
		NIXIE_4_ON;
		NIXIE_3_OFF;
		NIXIE_2_OFF;
		NIXIE_1_OFF;

		return;
	}

}
