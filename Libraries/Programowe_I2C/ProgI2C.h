
#ifndef PROGRAMOWE_I2C_PROGI2C_H_
#define PROGRAMOWE_I2C_PROGI2C_H_

#include "ProgI2CSetup.h"


#define PORT(x) XPORT(x)
#define XPORT(x) (PORT##x)


#define PIN(x) XPIN(x)
#define XPIN(x) (PIN##x)

#define DDR(x) XDDR(x)
#define XDDR(x) (DDR##x)

//typedef unsigned char u08;
//typedef unsigned short u16;


//opóŸnienie cwierc bitu
#define QDEL _delay_loop_1(1);

//opóŸnienie pó³ bitu
#define HDEL _delay_loop_1(2);

#define I2C_SDA_LOW PORT(SDAPORT) &= ~(1<<SDA)
#define I2C_SDA_HIG PORT(SDAPORT) |=  (1<<SDA)

#define I2C_SCL_LOW PORT(SCLPORT) &= ~(1<<SCL)
#define I2C_SCL_HIG PORT(SCLPORT) |=  (1<<SCL)

#define I2C_SCL_TOOGLE HDEL; I2C_SCL_HIG; HDEL; I2C_SCL_LOW

void I2C_START (void);
void I2C_REP_START (void);
void I2C_STOP (void);
void I2C_INIT (void);
uint8_t I2CPutByte(uint8_t b);
uint8_t I2CGetByte(uint8_t ack);
void I2C_Write_Buf(uint8_t device, uint8_t adr, uint8_t len, uint8_t *buf);
void I2C_Read_Buf(uint8_t device, uint8_t adr, uint8_t len, uint8_t *buf);
void EepI2C_Read_Buf(uint8_t device, uint16_t adr, uint16_t len, uint8_t *buf);
void EepI2C_Write_Buf(uint8_t device, uint16_t adr, uint16_t len, uint8_t *buf);
#endif /* PROGRAMOWE_I2C_PROGI2C_H_ */
