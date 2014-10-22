//
//  pcint.h
//  Runin_V2
//
//  Created by Kristian Xu on 9/22/14.
//  Copyright (c) 2014 Weiming. All rights reserved.
//

#ifndef Runin_V2_pcint_h
#define Runin_V2_pcint_h
#include <avr/io.h>

#define INT_VECT PCINT0_vect
#define INT_PIN PB0
#define INT_PORT PORTB
#define INT_PORT_DDR DDRB
#define	PCINT_BUTTON PB1
#define PCINT_DROP PB0
#define PCINT_DDR DDRB
#define PCINT_PORT PORTB

#define EEPROM_DATA_START 0x10

void PCINT_init(void);




#endif
