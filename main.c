#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Libraries/RTC/i2c.h"
#include "Libraries/RTC/pcf8583.h"
#include "Libraries/Utils/utils.h"

int main(void)
{
	//visual confirmation of start
	Led_Init();
	BlinkLed();

	//Put actual hour to rtc
	RtcInit();


	uint8_t seconds, minutes, hours;
	while (1) {

		RtcReadData(&seconds, &minutes, &hours);


//		if(seconds >= 1)
//			LED0_ON;
//		else
//			LED0_OFF;
//
//		if(seconds >= 5)
//			LED1_ON;
//		else
//			LED1_OFF;
//		_delay_ms(100);

	}
}


