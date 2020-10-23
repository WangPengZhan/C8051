//-----------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//-----------------------------------------------------------------------------
//
// file name  :       timer.h
//
// description:       timer set file
//
// Target     :       C8051F34x / C8051F38x
//
// version    :       V100.001
//					  2017/11/16 by roy zhou
//
//-----------------------------------------------------------------------------
#ifndef _TIMER_H__
#define _TIMER_H__
 
// -----------------------------------------------------------------------------
// Global Constants
#define BLINK_RATE         500          // ms per blink
#define SYSCLK             48000000     // SYSCLK frequency in Hz
#define PRESCALE           48           // Timer prescaler
#define TIMER_RELOAD 	   -(SYSCLK / PRESCALE / 1000)
#define F_SCK_MAX          2000000      // SPI0 Clock Rate

#define TIMER_RELOAD_HIGH ((TIMER_RELOAD & 0xFF00)>>8)
#define TIMER_RELOAD_LOW   (TIMER_RELOAD & 0x00FF)

// 1us - 10ms
extern void delay_us_timer1( uint32_t delay_us );

#endif


