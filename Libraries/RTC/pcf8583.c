/*
 * pcf8583.c
 *
 *  Created on: 28 maj 2022
 *      Author: Grzegorzewski Szymon
 */
#include <avr/io.h>
#include "pcf8583.h"
#include "i2c.h"
//#include "../Utils/utils.h"

uint8_t DecToBCD(uint8_t dec) {
	return ((dec / 10) << 4) | (dec % 10);
}
uint8_t BCDToDec(uint8_t bcd){
	return ((((bcd)>>4) & 0x0F) *10 ) + ((bcd) & 0x0F);
}

void RtcInit()
{
	uint8_t buffer[4];
	buffer[0] = 0;
	buffer[1] = DecToBCD(0);
	buffer[2] = DecToBCD(30);
	buffer[3] = DecToBCD(8);
	TWI_Write_Buf(0xA0, 0x01, 4, buffer);
}

void RtcReadData(uint8_t *seconds, uint8_t *minutes, uint8_t *hours )
{
	uint8_t buffer2[3];
	TWI_Read_Buf(0xA0, 0x02, 3, buffer2);
	*seconds = BCDToDec(buffer2[0]);
	*minutes = BCDToDec(buffer2[1]);
	*hours   = BCDToDec(buffer2[2]);

}
