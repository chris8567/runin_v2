//
//  timer0.c
//  Runin_controller
//
//  Created by Kristian Xu on 9/16/14.
//  Copyright (c) 2014 Kristian Xu. All rights reserved.
//

#include <avr/io.h>
#include "timer0.h"
#include <avr/interrupt.h>



void timer0_comp_init()
{
	TIMSK0|= (1 << OCIE0A);
	TCCR0A |= (1<<WGM01);
	TCCR0B |= (1<<CS02)|(1<<CS00);
	OCR0A = 20;
	//TCNT0 = 0;
	timer0_disable();
	
}

void timer2_init(void){
	TIMSK2 |= _BV(OCIE2A);
	TCCR2A |= _BV(WGM01);
	TCCR2B |= _BV(CS02) | _BV(CS00);
	OCR2A = 0xFF;
	OCR2B = 0;
	
}

void timer2_enable(void){
	TIMSK2 |= _BV(OCIE2A);
}

void  timer2_disable(void){
	TIMSK2 &=~(_BV(OCIE2A));
	
}


void timer0_enable(U8 speed)

{
	if (speed < 3) speed = 3;
	if (speed > 15) speed = 15;

	OCR0A = speed;
	TIMSK0|= (1 << OCIE0A);
	
}

void timer0_disable(void)
{
	TIMSK0 &= ~(1 << OCIE0A);
}


ISR(TIMER0_COMPA_vect){
		timer0_isr();
}


ISR(TIMER2_COMPA_vect){
	timer2_isr();
	
}
