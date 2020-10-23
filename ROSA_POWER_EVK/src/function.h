//-----------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//-----------------------------------------------------------------------------
//
// file name  :       function.c
//
// description:       Contains Normal function
//
// Target     :       C8051F34x / C8051F38x
//
// version    :       V100.001
//					  2017/11/16 by roy zhou
//
//-----------------------------------------------------------------------------

#ifndef __FUNCTION_H_H_
#define __FUNCTION_H_H_

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------
#ifndef FLASH_ID_SIZE
#define FLASH_ID_SIZE    0x04
#endif
typedef struct rssi_meas{
	float Meas[12];
}RSSI_MEAS;
typedef struct rssi_real{
	float Real[12];
}RSSI_REAL;
typedef struct MCU_Config_Parameters_struct
{
	float    fDC_VCC;   // 0x00-0x03
	float    fADC_Vref; // 0x04-0x07

	float    fRSSI_SR[4];     // 0x08-0x17 Kohm
	float    fRSSI_Offset[4]; // 0x18-0x27 uA

	float    fVAPD_RH[4];     // 0x28-0x37 Kohm
	float    fVAPD_RL[4];     // 0x38-0x47 Kohm
	float    fVAPD_Offset[4]; // 0x48-0x57 uA

	float    fICCI_R; // 0x58-0x5B ohm
	float    fICCO_R; // 0x5C-0x5F ohm

	uint8_t  ADC_Bits;  // 0x60
	uint8_t  ADC_Mode;  // 0x61  1: VCC for ADC VREF 0: internal 2.44v for ADC VREF

	uint8_t  gID[FLASH_ID_SIZE]; // 0x62 - 0x65
	RSSI_MEAS Rssi_Meas[4];
	RSSI_REAL Rssi_Real[4];

}MCU_Values_st;

#ifndef FLASH_USE_ADDRESS
#define FLASH_USE_ADDRESS 0xF600L
#endif

#ifndef FLASH_USE_SIZE
#define FLASH_USE_SIZE    sizeof(struct MCU_Config_Parameters_struct)
#endif


extern void(*funccallback)(void);

extern void	Port_Init(void);
extern void	LoadFlash_File(void);
extern void	WriteFlash_File(void);
extern void	Global_Value_Init(void);
extern void Port_Monitor_Ctrl (void);

#endif
