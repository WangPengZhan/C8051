//--------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//--------------------------------------------------------------------------
//
// file name  :       adc_0.h
//
// description:       Initialize and use ADC0
//
// Target     :       C8051F34x / C8051F38x
//
// version    :       V100.001
//					  2017/11/16 BY roy zhou
//
//--------------------------------------------------------------------------

#ifndef __ADC_0_H__
#define __ADC_0_H__
 
#include "include.h"

#define 	SARCLK		3000000

/// Positive input selection enums.
typedef enum {

	ADC0_POSITIVE_INPUT_P20=0x00,
	ADC0_POSITIVE_INPUT_P21=0x01,
	ADC0_POSITIVE_INPUT_P22=0x02,
	ADC0_POSITIVE_INPUT_P23=0x03,
	ADC0_POSITIVE_INPUT_P25=0x04,
	ADC0_POSITIVE_INPUT_P26=0x05,
	ADC0_POSITIVE_INPUT_P30=0x06,
	ADC0_POSITIVE_INPUT_P31=0x07,
	ADC0_POSITIVE_INPUT_P34=0x08,
	ADC0_POSITIVE_INPUT_P35=0x09,
	ADC0_POSITIVE_INPUT_P37=0x0A,
	ADC0_POSITIVE_INPUT_P40=0x0B,
	ADC0_POSITIVE_INPUT_P43=0x0C,
	ADC0_POSITIVE_INPUT_P44=0x0D,
	ADC0_POSITIVE_INPUT_P45=0x0E,
	ADC0_POSITIVE_INPUT_P46=0x0F,
	// 0x10 is reserved
	ADC0_POSITIVE_INPUT_P03=0x11,
	ADC0_POSITIVE_INPUT_P04=0x12,
	ADC0_POSITIVE_INPUT_P11=0x13,
	ADC0_POSITIVE_INPUT_P12=0x14,
	// 0x15~0x1D is reserved
	ADC0_POSITIVE_INPUT_Temp_Sensor=0x1E,
	ADC0_POSITIVE_INPUT_VDD=0x1F,
	ADC0_POSITIVE_INPUT_P41=0x20,
	ADC0_POSITIVE_INPUT_P42=0x21,
	ADC0_POSITIVE_INPUT_P47=0x22,
	// 0x22~0xFF is reserved

}ADC0_PositiveInput_e;

#define ADC_HV_RSSI				0x09 //ADC0_POSITIVE_INPUT_P35
#define ADC_VCC3V3M_MON  	0x12 //ADC0_POSITIVE_INPUT_P04

#define APD_RSSI0	0x01
#define APD_RSSI1	0x02
#define APD_RSSI2	0x03
#define APD_RSSI3	0x04
#define TIA_CURRENT 0x05

extern void     ADC0_Init(void);
extern uint16_t ADC0_Read( int count, ADC0_PositiveInput_e input );

#endif

