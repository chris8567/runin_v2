//
//  servo.h
//  Runin_V2
//
//  Created by Kristian Xu on 9/22/14.
//  Copyright (c) 2014 Weiming. All rights reserved.
//

#ifndef Runin_V2_servo_h
#define Runin_V2_servo_h
#include "global.h"
#include <avr/io.h>

#define SERVO_ENA PD3
#define SERVO_DIR PD4
#define SERVO_PUL PD5
#define SERVO_DDR DDRD
#define SERVO_PORT PORTD
#define SERVO_POSITION_UPPER_LIMIT 2860
#define SERVO_PUL_WIDTH 600



volatile static U16 servo_position_buffer;
volatile static U16 servo_scan_limit;
volatile static bool servo_auto_flag=false;



void SERVO_init(void);
U16 SERVO_get_position(void);
void SERVO_set_position(U16 new_position);
void SERVO_send_pulse(U16 count, bool dir);
void SERVO_calib(U16 position);
void SERVO_enable(void);
void SERVO_disable(void);
void SERVO_poll(U8 *coil, U16 *holding);


#endif
