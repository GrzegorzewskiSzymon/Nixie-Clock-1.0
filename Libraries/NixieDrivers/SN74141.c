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

uint32_t millis_DisplayTime = 0;
void DisplayTime(uint8_t hours, uint8_t minutes)
{
	if(millis-millis_DisplayTime > 12)//Its time to display units of minutes
	{
		PORTD = minutes%10;

		NIXIE_4_OFF;
		NIXIE_3_OFF;
		NIXIE_2_OFF;
		NIXIE_1_ON;

		millis_DisplayTime = millis;//set actual time after full cicle
		return;
	}

	if(millis-millis_DisplayTime > 9)//Its time to display tens of minutes
	{
		PORTD = minutes/10;

		NIXIE_4_OFF;
		NIXIE_3_OFF;
		NIXIE_2_ON;
		NIXIE_1_OFF;

		return;
	}

	if(millis-millis_DisplayTime > 6)//Its time to display units of hours
	{
		PORTD = hours%10;
		NIXIE_4_OFF;
		NIXIE_3_ON;
		NIXIE_2_OFF;
		NIXIE_1_OFF;

		return;
	}

	if(millis-millis_DisplayTime > 3 &&hours > 9)//Its time to display tens of hours
	{
		PORTD = hours/10;
		NIXIE_4_ON;
		NIXIE_3_OFF;
		NIXIE_2_OFF;
		NIXIE_1_OFF;

		return;
	}

}
