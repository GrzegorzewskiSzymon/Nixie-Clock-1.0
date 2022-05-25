#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Libraries/Programowe_I2C/ProgI2C.h"


#define ACK 1
#define NACK 0

void TWI_Start(void);
void TWI_Stop(void);
void TWI_Write(uint8_t byte);
void TWI_Write_Buf(uint8_t sla, uint8_t adr, uint8_t len, uint8_t *buf);
uint8_t TWI_Read(uint8_t ack);
void TWI_Read_Buf(uint8_t sla, uint8_t adr, uint8_t len, uint8_t *buf);

uint8_t DecToBCD(uint8_t dec);
uint8_t BCDToDec(uint8_t bcd);


int main(void)
{
	DDRD = 0b00011111;

	DDRC = 0b00000011; //LEDs
	PORTC = 0b00000011;
	_delay_ms(150);
	PORTC = 0b00000000;

	I2C_INIT();


	uint8_t buffer[4];
	buffer[0] = 0;
	buffer[1] = DecToBCD(0);
	buffer[2] = DecToBCD(59);
	buffer[3] = DecToBCD(24);
	I2C_Write_Buf(0xA0, 0x01, 4, buffer);

	uint8_t buffer2[3];
	uint8_t seconds, minutes, hours;
	while (1) {


		I2C_Read_Buf(0xA0, 0x02, 3, buffer2);
		seconds = BCDToDec(buffer2[0]);
		minutes = BCDToDec(buffer2[1]);
		hours   = BCDToDec(buffer2[2]);

		if(seconds > 5)
			PORTC |= (1<<PC0);
		else
			PORTC &=~ (1<<PC0);

		if(seconds > 15)
			PORTC |= (1<<PC1);
		else
			PORTC &=~ (1<<PC1);
		_delay_ms(100);
	}
}

void TWI_Start(void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);
	while (!(TWCR & (1 << TWINT)))
		;
}
void TWI_Stop(void) {
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
	while ((TWCR & (1 << TWSTO)))
		;
}
void TWI_Write(uint8_t byte) {
	TWDR = byte;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)))
		;
}
uint8_t TWI_Read(uint8_t ack) {
	TWCR = (1 << TWINT) | (ack << TWEA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)))
		;
	return TWDR;
}
void TWI_Write_Buf(uint8_t sla, uint8_t adr, uint8_t len, uint8_t *buf) {
	TWI_Start();
	TWI_Write(sla); //adres uk³adu Slave
	TWI_Write(adr); //pierwszy adres bajtu do którego nast¹pi zapis
	while (len--)
		TWI_Write(*buf++);
	TWI_Stop();
}
uint8_t DecToBCD(uint8_t dec) {
	return ((dec / 10) << 4) | (dec % 10);
}
uint8_t BCDToDec(uint8_t bcd){
	return ((((bcd)>>4) & 0x0F) *10 ) + ((bcd) & 0x0F);
}

void TWI_Read_Buf(uint8_t sla, uint8_t adr, uint8_t len, uint8_t *buf) {
	TWI_Start();
	TWI_Write(sla);
	TWI_Write(adr);
	TWI_Start();
	TWI_Write(sla + 1);
	while (len--) *buf++ = TWI_Read(len ? ACK : NACK);
	TWI_Stop();


}
