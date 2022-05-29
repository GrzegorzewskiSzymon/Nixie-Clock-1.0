/*
 * AnodesMultiplexer.h
 *
 *  Created on: 28 maj 2022
 *      Author: Grzegorzewski Szymon
 */

#ifndef LIBRARIES_NIXIEDRIVERS_ANODESMULTIPLEXER_H_
#define LIBRARIES_NIXIEDRIVERS_ANODESMULTIPLEXER_H_

#define ANODES_INIT DDRC |= 0b00000111; DDRD |= (1<<PD4)

#define NIXIE_4_ON  PORTC &=~ (1<<PC1)
#define NIXIE_4_OFF PORTC |=  (1<<PC1)

#define NIXIE_3_ON  PORTC &=~ (1<<PC2)
#define NIXIE_3_OFF PORTC |=  (1<<PC2)

#define NIXIE_2_ON  PORTD &=~ (1<<PD4)
#define NIXIE_2_OFF PORTD |=  (1<<PD4)

#define NIXIE_1_ON  PORTC &=~ (1<<PC0)
#define NIXIE_1_OFF PORTC |=  (1<<PC0)

void Anodes_Init();

#endif /* LIBRARIES_NIXIEDRIVERS_ANODESMULTIPLEXER_H_ */
