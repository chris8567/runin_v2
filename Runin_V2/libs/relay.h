//
//  relay.h
//  Runin_V2
//
//  Created by Kristian Xu on 10/2/14.
//  Copyright (c) 2014 Weiming. All rights reserved.
//

#ifndef Runin_V2_relay_h
#define Runin_V2_relay_h
#include "global.h"

#define RELAY_NO1 PB6
#define RELAY_NO2 PB7
#define RELAY_PORT PORTB
#define RELAY_DDR DDRB

volatile static U8 relay1, relay2;

void RELAY_init(void);
void RELAY_poll(U8 *ucbuff);



#endif
