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

	Anodes_Init();
	BCD_Init();

	//Put actual hour to rtc
	RtcInit();




	uint8_t seconds, minutes, hours;
	while (1)
	{

	}
}


