//
//  relay.c
//  Runin_V2
//
//  Created by Kristian Xu on 10/2/14.
//  Copyright (c) 2014 Weiming. All rights reserved.
//

#include "global.h"
#include "relay.h"
#include <avr/io.h>

void RELAY_init(){
	RELAY_DDR |= (_BV(RELAY_NO1)|_BV(RELAY_NO2));
	RELAY_PORT &= ~(_BV(RELAY_NO1)&_BV(RELAY_NO2));
	
}


void RELAY_poll(U8 *ucbuff){
	
	relay1 = *ucbuff & _BV(P_RELAY_NO1_SWITCH);
	relay2 = *ucbuff & _BV(P_RELAY_NO2_SWITCH);
	
	if (relay1) {
		RELAY_PORT |= _BV(RELAY_NO1);
	}
	else{
		RELAY_PORT &= ~(_BV(RELAY_NO1));
	}
	
	if (relay2) {
		RELAY_PORT |= _BV(RELAY_NO2);
	}
	else{
		RELAY_PORT &= ~(_BV(RELAY_NO2));
	}
	
	
}

