//
//  timer0.h
//  Runin_controller
//
//  Created by Kristian Xu on 9/16/14.
//  Copyright (c) 2014 Kristian Xu. All rights reserved.
//

#ifndef Runin_controller_timer0_h
#define Runin_controller_timer0_h
#include "global.h"


extern void timer0_isr(void);
extern void timer2_isr(void);

void timer0_comp_init(void);
void timer0_enable(U8 speed);
void timer0_disable(void);

void timer2_init(void);
void timer2_enable(void);
void timer2_disable(void);



#endif
