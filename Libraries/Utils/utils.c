/*
 * utils.c
 *
 *  Created on: 26 maj 2022
 *      Author: Grzegorzewski Szymon
 */
#include <avr/io.h>
#include <avr/interrupt.h>
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

uint64_t millis;
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

SWITCH Switch_0;
SWITCH Switch_1;
void SwitchInit(SWITCH *Switch_0, SWITCH *Switch_1)
{
	Switch_0->switchNumber = 0;
	Switch_1->switchNumber = 1;
}


static void Idle(SWITCH *switch_)
{

	if(switch_->switchNumber == 0)
	{
		if(SW_0_IS_PUSHED)//possibility of being pressed
		{
			switch_->timerDebounce = millis;
			switch_->switchState = DEBOUNCE;
		}
	}
	else
	{
		if(SW_1_IS_PUSHED)//possibility of being pressed
		{
			switch_->timerDebounce = millis;
			switch_->switchState = DEBOUNCE;
		}
	}
}

static void Debounce(SWITCH *switch_)
{
	if(millis-switch_->timerDebounce > DEBOUNCE_TIME)
	{
		if(switch_->switchNumber == 0)
		{
			if(SW_0_IS_PUSHED)//if pressed
			{
				switch_->counterData++;
				switch_->timerPress = millis;
				switch_->switchState = PRESSED;
			}
		}
		else
		{
			if(SW_1_IS_PUSHED)//if pressed
			{
				switch_->counterData++;
				switch_->timerPress = millis;
				switch_->switchState = PRESSED;
			}
		}
	}
}


static void Pressed(SWITCH *switch_)
{
	if(switch_->switchNumber == 0)
	{
		if(SW_0_IS_PUSHED)//if still pressed
		{
			if(millis-switch_->timerPress > LONG_PRESS_TIME)
			{
				switch_->timerLongPress = millis;
				switch_->switchState = LONG_PRESS;
			}
		}
		else
		{
			switch_->switchState = RELEASED;
		}
	}
	else
	{
		if(SW_1_IS_PUSHED)//if still pressed
		{
			if(millis-switch_->timerPress > LONG_PRESS_TIME)
			{
				switch_->timerLongPress = millis;
				switch_->switchState = LONG_PRESS;
			}
		}
		else
		{
			switch_->switchState = RELEASED;
		}
	}

}


static void LongPress(SWITCH *switch_)
{
	if(millis-switch_->timerLongPress > LONG_PRESS_TIME_CYCLE)
	{
		if(switch_->switchNumber == 0)
		{
			if(SW_0_IS_PUSHED)//if pressed
			{
				switch_->counterData++;
				switch_->timerLongPress = millis;
			}
			else
			{
				switch_->switchState = RELEASED;
			}
		}
		else
		{
			if(SW_1_IS_PUSHED)//if pressed
			{
				switch_->counterData++;
				switch_->timerLongPress = millis;
			}
			else
			{
				switch_->switchState = RELEASED;
			}
		}

	}
}


void StateMachine(SWITCH *switch_)
{
	switch(switch_->switchState)
	{
		case IDLE:
			Idle(switch_);
			break;

		case DEBOUNCE:
			Debounce(switch_);
			break;

		case PRESSED:
			Pressed(switch_);
			break;

		case LONG_PRESS:
			LongPress(switch_);
			break;

		case RELEASED:
			switch_->switchState = IDLE;
			break;
	}
}



