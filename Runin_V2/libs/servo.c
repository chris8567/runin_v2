//
//  servo.c
//  Runin_V2
//
//  Created by Kristian Xu on 9/22/14.
//  Copyright (c) 2014 Weiming. All rights reserved.
//

#include <avr/io.h>
#include "global.h"
#include "servo.h"
#include <util/delay.h>
#include <avr/eeprom.h>
#include "timer0.h"


void SERVO_init(void){
	//timer0 initlization for auto scan.
	timer0_comp_init();
	timer2_init();
	SERVO_DDR |= (_BV(SERVO_ENA)|_BV(SERVO_DIR)|_BV(SERVO_PUL));
	SERVO_PORT |= (_BV(SERVO_ENA));
	SERVO_enable();
	
	servo_position_buffer = ucHoldingBuf[P_SERVO_POSITION_REG];

	timer2_enable();
}

void SERVO_enable(void){
	SERVO_PORT &= ~(_BV(SERVO_ENA));
	
	
}

void SERVO_disable(void){
	SERVO_PORT |= _BV(SERVO_ENA);
	
}

U16 SERVO_get_position(void){
	return servo_position_buffer;
	
}

void SERVO_calib(U16 position){
	servo_position_buffer = position;
	ucHoldingBuf[P_SERVO_POSITION_REG]=position;
	
}

void SERVO_set_position(U16 new_position){
	if (new_position> SERVO_POSITION_UPPER_LIMIT) {
		return;
	}
	
	if (new_position != servo_position_buffer){
		
		_delay_ms(2);
		
		if(new_position > servo_position_buffer)
			SERVO_send_pulse(new_position-servo_position_buffer, true);
		else
			SERVO_send_pulse(servo_position_buffer-new_position, false);
		_delay_ms(2);
		
		
		
	
	}
	
	
}

void SERVO_send_pulse(U16 count, bool dir){
	U16 i;
	
	if(dir) SERVO_PORT |= _BV(SERVO_DIR);
	else SERVO_PORT &= ~(_BV(SERVO_DIR));
	
	for (i=0; i<count; i++) {
		SERVO_PORT |= _BV(SERVO_PUL);
		_delay_us(SERVO_PUL_WIDTH);
		SERVO_PORT &= ~(_BV(SERVO_PUL));
		_delay_us(SERVO_PUL_WIDTH);
		if(dir) servo_position_buffer++;
		else servo_position_buffer--;
		}
	}
	
	



void SERVO_poll(U8 *coil, U16 *holding){
	if(*coil&_BV(P_SERVO_AUTO_SWITCH)){
	if (servo_auto_flag == false && holding[P_SERVO_POSITION_REG]!=0) {
		servo_scan_limit = holding[P_SERVO_POSITION_REG];
	
		timer0_enable(ucHoldingBuf[P_SERVO_SCANSPEED_REG]+3);
		servo_auto_flag = true;
	}
	
	}
	else{
		if (servo_auto_flag == true){
			servo_auto_flag = false;
			timer0_disable();
			ucHoldingBuf[P_SERVO_POSITION_REG]=servo_scan_limit;
		
		}
	 SERVO_set_position(holding[P_SERVO_POSITION_REG]);
		
	}
	

}

void timer0_isr(void){

	static bool directions = 0;
	static bool pulse = true;
	if(pulse){
		SERVO_PORT |= _BV(SERVO_PUL);
		pulse = false;
	}
	else
	{
		SERVO_PORT &= ~(_BV(SERVO_PUL));
		pulse = true;
	}
	if (pulse) {
		
		if (directions){
			SERVO_PORT |= (_BV(SERVO_DIR));
			if(servo_position_buffer < servo_scan_limit)
				servo_position_buffer++;
			
			else
				directions = 0;
		}
		else{
			SERVO_PORT &= ~(_BV(SERVO_DIR));
			if (servo_position_buffer > 0) {
				servo_position_buffer --;
			}
			else
				directions = 1;
		}
		ucHoldingBuf[P_SERVO_POSITION_REG]=servo_position_buffer;
	}
	

	

	
}


void timer2_isr(void){
	static U16 count_a =0, count_v=0;
	
	
	if (ucRegCoilsBuf[0] & _BV(P_AUTO_DROP_A)){
		
		count_a++;
		
		if (count_a <= 150*ucHoldingBuf[P_AUTO_DROP_A_T_C])
			
			ucRegCoilsBuf[0] |= _BV(P_RELAY_NO1_SWITCH);
		
		else{
			
			
			if(count_a <= 150*(ucHoldingBuf[P_AUTO_DROP_A_T_C]+ucHoldingBuf[P_AUTO_DROP_A_T_O]))
				
				ucRegCoilsBuf[0] &= ~(_BV(P_RELAY_NO1_SWITCH));
			
			else
				
				count_a = 0;
			
		}
		
		
	}
	
	else count_a = 0;
	
	
	if (ucRegCoilsBuf[0] & _BV(P_AUTO_DROP_V)){
		
		count_v++;
		
		
		if (count_v <= 75*ucHoldingBuf[P_AUTO_DROP_V_T_C])
			
			ucRegCoilsBuf[0] |= _BV(P_RELAY_NO2_SWITCH);
		
		else{
			
			if(count_v <= 75*(ucHoldingBuf[P_AUTO_DROP_V_T_C]+ucHoldingBuf[P_AUTO_DROP_V_T_O]))
				
				ucRegCoilsBuf[0] &= ~(_BV(P_RELAY_NO2_SWITCH));
			
			else
				
				count_v = 0;
			
		}
		
	}
	
	else count_v =0 ;
	
	

	
	
	
}




