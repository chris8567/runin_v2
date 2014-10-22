//
//  pcint.c
//  Runin_V2
//
//  Created by Kristian Xu on 9/22/14.
//  Copyright (c) 2014 Weiming. All rights reserved.
//

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "pcint.h"
#include "servo.h"
#include "global.h"

#include <avr/eeprom.h>



void PCINT_init(void){

	PCINT_DDR &= ~(_BV(PCINT_BUTTON)|_BV(PCINT_DROP));
	PCICR |= _BV(PCIE0);
	PCMSK0 |= (_BV(PCINT0)|_BV(PCINT1));
	sei();
	

}



ISR(PCINT0_vect){

	cli();
	
	
	if (!(PINB & _BV(PCINT_DROP))) {

	
	
	U8 i;
		eeprom_busy_wait();
		eeprom_write_byte((uint8_t *)EEPROM_DATA_START,0xee);
		eeprom_write_byte((uint8_t *)EEPROM_DATA_START+1,ucRegCoilsBuf[0]);
		
	for (i=0; i<8; i++)
		eeprom_write_word((uint16_t *)(EEPROM_DATA_START+2+i*2),ucHoldingBuf[i]);
		
	}
	
	else if (!(PINB & _BV(PCINT_BUTTON))) {
		SERVO_calib(0);
	}

	
	sei();
	
 


	
	
}




