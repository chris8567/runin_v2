//
//  global.h
//  Runin_V2
//
//  Created by Kristian Xu on 9/22/14.
//  Copyright (c) 2014 Weiming. All rights reserved.
//

#ifndef Runin_V2_global_h
#define Runin_V2_global_h

typedef unsigned char U8;
typedef unsigned int U16;



#ifndef bool
typedef unsigned char bool;
#endif

#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif

#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#define REG_COILS_START 1000
#define REG_COILS_SIZE      128
#define REG_HOLDING_START 1000
#define REG_HOLDING_SIZE	32



#define P_RELAY_NO1_SWITCH 1  // direction
#define P_RELAY_NO2_SWITCH 2	//drop down
#define P_SERVO_AUTO_SWITCH 3
#define P_AUTO_DROP_V 4
#define P_AUTO_DROP_A 5

#define P_AUTO_DROP_V_T_C 3
#define P_AUTO_DROP_V_T_O 4
#define P_AUTO_DROP_A_T_C 5
#define P_AUTO_DROP_A_T_O 6

#define P_SERVO_SCANSPEED_REG 2
#define P_SERVO_POSITION_REG 1

extern U8 ucRegCoilsBuf[REG_COILS_SIZE/8];
extern U16 ucHoldingBuf[REG_HOLDING_SIZE];







#endif
