//-----------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//-----------------------------------------------------------------------------
//
// file name  :       mcu_residter.c
//
// description:       mcu register read and set function
//
// Target     :       C8051F34x / C8051F38x
//
// version    :       V100.001
//					  2017/11/16 by roy zhou
//
//-----------------------------------------------------------------------------
#ifndef MUC_REGISTER_H_H
#define MCU_REGISTER_H_H

extern uint16_t MCU_Register_Write( uint16_t regadr, uint16_t val );
extern uint16_t MCU_Register_Read( uint16_t regadr );


#endif

