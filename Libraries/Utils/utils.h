/*
 * utils.h
 *
 *  Created on: 26 maj 2022
 *      Author: Grzegorzewski Szymon
 */

#ifndef LIBRARIES_UTILS_UTILS_H_
#define LIBRARIES_UTILS_UTILS_H_

/////////////////////////////////////////////////////////
//                   LEDs
/////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////
//                   SWITCHES
/////////////////////////////////////////////////////////

#define SW_0_IS_PUSHED !(PIND & (1<<PD5))
#define SW_1_IS_PUSHED !(PIND & (1<<PD6))

#define DEBOUNCE_TIME 20 //ms;
#define LONG_PRESS_TIME 2000 //ms;  time to press turns to long press
#define LONG_PRESS_TIME_CYCLE 60 //ms;

typedef enum
{
	IDLE = 0,
	DEBOUNCE,
	PRESSED,
	LONG_PRESS,
	RELEASED

}SWITCH_STATE;

typedef struct
{
	SWITCH_STATE switchState;
	uint8_t switchNumber;

	uint16_t counterData;

	uint32_t timerDebounce;
	uint32_t timerPress;
	uint32_t timerLongPress;

}SWITCH;

extern SWITCH Switch_0;
extern SWITCH Switch_1;
void SwitchInit(SWITCH *switch_0, SWITCH *switch_1);
void StateMachine(SWITCH *switch_);
/////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////
//                   TIMERS
/////////////////////////////////////////////////////////
void Timer0_Init();//start counting millis
extern uint64_t millis;
/////////////////////////////////////////////////////////

#endif /* LIBRARIES_UTILS_UTILS_H_ */
