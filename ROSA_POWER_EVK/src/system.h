//-----------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//-----------------------------------------------------------------------------
//
// file name  :       system.h
//
// description:       system set file
//
// Target     :       C8051F34x / C8051F38x
//
// version    :       V100.001
//					  2017/11/16 by roy zhou
//
//-----------------------------------------------------------------------------

#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#define WITE_VDD_STABILIZE		do{ volatile uint16_t x = 0; for( x = 0; x < 500; x ){x++;} }while(0)

extern void Sysclk_Init (void);
extern void VDDMon_Init (void);
extern void SystemReset (void);

#endif




