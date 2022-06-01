#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Libraries/RTC/i2c.h"
#include "Libraries/RTC/pcf8583.h"
#include "Libraries/NixieDrivers/SN74141.h"
#include "Libraries/NixieDrivers/AnodesMultiplexer.h"
#include "Libraries/Utils/utils.h"



int main(void)
{
	//visual confirmation of start
	Led_Init();
	BlinkLed();
	Timer0_Init();//for milis

	Anodes_Init();
	BCD_Init();

	SwitchInit(&Switch_0, &Switch_1);//Numerate switches

	//Put actual hour to rtc
	RtcInit();


	uint8_t seconds, minutes, hours;
	while (1)
	{
		RtcReadData(&seconds, &minutes, &hours);
		DisplayTime(hours, minutes);

	}
}


