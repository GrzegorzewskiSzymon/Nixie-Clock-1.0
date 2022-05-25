#include <avr/io.h>
#include <util/delay.h>
#include "ProgI2C.h"
#include "ProgI2CSetup.h"

void I2C_START(void) {
	I2C_SDA_LOW;
	QDEL;
	I2C_SCL_LOW;
}

void I2C_REP_START(void) {
	HDEL;
	I2C_SCL_HIG;
	I2C_SDA_LOW;
	QDEL;
	I2C_SCL_LOW;
}

void I2C_STOP(void) {
	I2C_SDA_LOW;
	HDEL
	;
	I2C_SCL_HIG;
	QDEL
	;
	I2C_SDA_HIG;
	HDEL
	;
}

//inicjalizacja komunikacji
void I2C_INIT(void) {
	DDR(SDAPORT) |= (1<<SDA);
	DDR(SCLPORT) |= (1<<SCL);
	I2C_SDA_HIG;
	I2C_SCL_HIG;

}

uint8_t I2CPutByte(uint8_t b) {
	uint8_t i = 0x80;

	do {
		if (b & i)
			I2C_SDA_HIG;
		else
			I2C_SDA_LOW;

		I2C_SCL_TOOGLE
		;
	} while (i >>= 1); //wysy³anie bajtu

	I2C_SDA_HIG;

	DDR(SDAPORT) &= ~(1 << SDA);
	HDEL
	;
	I2C_SCL_HIG;
	b = PIN(SDAPORT) & (1 << SDA); //sprawdzanie bitu ACK

	HDEL
	;
	I2C_SCL_LOW;
	DDR(SDAPORT) |= (1 << SDA);
	HDEL
	;
	return (b == 0);
}

uint8_t I2CGetByte(uint8_t ack) {
	uint8_t i;
	uint8_t c, b = 0;

	I2C_SDA_HIG;
	DDR(SDAPORT) &= ~(1 << SDA);

	for (i = 8; i > 0; i--) {
		HDEL
		;
		I2C_SCL_HIG;
		c = PIN(SDAPORT) & (1 << SDA);
		b <<= 1;
		if (c)
			b |= 1;
		HDEL
		;
		I2C_SCL_LOW;
	}

	DDR(SDAPORT) |= (1 << SDA);

	if (ack)
		I2C_SDA_LOW;	//wyœlij ACK
	else
		I2C_SDA_HIG;	//wyœlij NAK

	I2C_SCL_TOOGLE;
	I2C_SDA_HIG;
	return b;
}

void I2C_Write_Buf(uint8_t device, uint8_t adr, uint8_t len, uint8_t *buf) {
	I2C_START();
	I2CPutByte(device); //wys³anie adresu urzadzenia
	I2CPutByte(adr); //wys³anie adresu pamiêci do zapisu
	while (len--) I2CPutByte(*buf++);
	I2C_STOP();
}

void I2C_Read_Buf(uint8_t device, uint8_t adr, uint8_t len, uint8_t *buf) {
	I2C_START();
	I2CPutByte(device); //wys³anie adresu urzadzenia
	I2CPutByte(adr); //wys³anie adresu pamiêci do odczytu
	I2C_REP_START();
	I2CPutByte(device | 1); // adres urz¹dzenia z bitem odczytu
	while(len--) *buf++ = I2CGetByte(len ? 1 : 0);
	I2C_STOP();

}

void EepI2C_Read_Buf(uint8_t device, uint16_t adr, uint16_t len, uint8_t *buf) {

	while (len--) {
		I2C_START();
		I2CPutByte(device | ((adr >> 8) << 1));
		I2CPutByte(adr);
		I2C_REP_START();
		I2CPutByte(device | 1); // adres urz¹dzenia z bitem odczytu
		*buf++ = I2CGetByte(0);
		I2C_STOP();
		adr++;
	}

}


void EepI2C_Write_Buf(uint8_t device, uint16_t adr, uint16_t len, uint8_t *buf) {

	while (len--) {
		I2C_START();
		I2CPutByte(device | ((adr >> 8) << 1));
		I2CPutByte(adr);

		I2CPutByte(*buf++);

		I2C_STOP();
		_delay_ms(5);
		adr++;
	}

}



