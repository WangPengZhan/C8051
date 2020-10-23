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

#include "include.h"

SI_SEGMENT_VARIABLE(gFlagWriteFlash, uint8_t, SI_SEG_XDATA);
SI_SEGMENT_VARIABLE(fADC_bits, float, SI_SEG_XDATA);
SI_SEGMENT_VARIABLE(MCUPer, struct MCU_Config_Parameters_struct, SI_SEG_XDATA);
SI_LOCATED_VARIABLE_NO_INIT(gID_Flash[FLASH_USE_SIZE], uint8_t, SI_SEG_CODE, FLASH_USE_ADDRESS );
SI_SEGMENT_VARIABLE(Port_Monitor, uint8_t, SI_SEG_XDATA);
SI_SEGMENT_VARIABLE(pin, uint16_t, SI_SEG_XDATA);
void(*funccallback)(void);
//-----------------------------------------------------------------------------
// Port_Init
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures Init Pin
//
//-----------------------------------------------------------------------------
void	Port_Init(void)
{
	// IO    -  Skip,		    Port, 	MDOUT,      	   MDIN			  USE

	// P0.0  -  Skipped,        0		Open-Drain, 	   Digital        none
	// P0.1  -  Skipped,        1		push-pull, 	       Digital        EN1V8
	// P0.2  -  Skipped,        1		push-pull,         Digital        EN5V
	// P0.3  -  Skipped,        0		push-pull,  	   Digital        EN-3V
	// P0.4  -  Skipped,        0		Open-Drain,        Analog         VCC3V3M_MON
	// P0.5  -  Skipped,        1		push-pull,         Digital        EN3V3
	// P0.6  -  Skipped,        0		Open-Drain,        Digital        none
	// P0.7  -  Skipped,        0		Open-Drain,        Digital        none
	P0      = 0x26;
	P0MDIN  = 0xEF;
	P0MDOUT = 0x2E;
	P0SKIP  = 0xFF;

	// P1.0  -  Skipped,        0		Open-Drain,        Digital        none
	// P1.1  -  Skipped,    	0		Open-Drain, 	   Digital        none
	// P1.2  -  Skipped,    	0		Open-Drain, 	   Digital        none
	// P1.3  -  Skipped,        1		Open-Drain, 	   Digital        APD_ALARM0
	// P1.4  -  Skipped,        1		Open-Drain, 	   Digital        APD_ALARM1
	// P1.5  -  Skipped,        0		Open-Drain, 	   Digital        none
	// P1.6  -  Skipped,        1		Open-Drain, 	   Digital        APD_ALARM3
	// P1.7  -  Skipped,        1		Open-Drain, 	   Digital        APD_ALARM2
	P1      = 0xD8;
    P1MDIN  = 0xFF;
	P1MDOUT = 0x00;
	P1SKIP  = 0xFF;

	// P2.0  -  Skipped,        1		Open-Drain, 	   Digital        RX_LOS
	// P2.1  -  Skipped,        0		push-pull, 	       Digital        RX_DIS
	// P2.2  -  Skipped,        1		push-pull,         Digital         PWRDN
	// P2.3  -  Skipped,        1		Open-Drain,        Digital       SLOW
	// P2.4  -  Skipped,        1		push-pull,         Digital        SPI_SCK
	// P2.5  -  Skipped,        1		push-pull,         Digital        SPI_MISO
	// P2.6  -  Skipped,        1		push-pull,         Digital        CS0
	// P2.7  -  Skipped,        1		push-pull,         Digital        MOSI
	P2      = 0xFD;
	P2MDIN  = 0xFF;
	P2MDOUT = 0xD6;
	P2SKIP  = 0xFF;

	// P3.0  -  Skipped,        1		push-pull, 	       Digital        OE
	// P3.1  -  Skipped,        0		Open-Drain, 	   Digital        none
	// P3.2  -  Skipped,        1		Open-Drain,        Digital        I2C_SDA
	// P3.3  -  Skipped,        1		Open-Drain,        Digital        I2C_SCL
	// P3.4  -  Skipped,        1		Push-pull,         Digital        HV_EN
	// P3.5  -  Skipped,        0		Open-Drain,        Digital        none
	// P3.6  -  Skipped,        0		Open-Drain,        Digital        none
	// P3.7  -  Skipped,        1		push-pull,         Digital        BWC
	P3      = 0x9D;
	P3MDIN  = 0xFF;
	P3MDOUT = 0x91;
	P3SKIP  = 0xFF;

	// P4.0  -  Skipped,        1		push-pull, 	       Digital        Vdiver
	// P4.1  -  Skipped,        1		push-pull, 	       Digital        Tsense_BUSY
	// P4.2  -  Skipped,        1		Open-Drain,        Digital        PD/EST
	// P4.3  -  none,        	0		Open-Drain,        Digital        none
	// P4.4  -  none,        	0		Open-Drain,        Digital        none
	// P4.5  -  none,        	0		Open-Drain,        Digital        none
	// P4.6  -  none,        	0		Open-Drain,        Digital        none
	// P4.7  -  none,        	0		Open-Drain,        Digital        none
	P4      = 0x07;
	P4MDIN  = 0xFF;
	P4MDOUT = 0x03;

	XBR0 = 0x02;
	XBR1 = XBR1_XBARE__ENABLED;  // Enable the crossbar
	XBR2 = 0x00;
}


//-----------------------------------------------------------------------------
// LoadFlash_File
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     None
//
//-----------------------------------------------------------------------------
void	LoadFlash_File(void)
{
	int i = 0;

	FLASH_Read( (uint8_t SI_SEG_XDATA *)&MCUPer, FLASH_USE_ADDRESS, FLASH_USE_SIZE );

	if( (MCUPer.fADC_Vref < 1.0) || (MCUPer.fADC_Vref>4.0) || (MCUPer.ADC_Bits>16) )
	{
		MCUPer.fDC_VCC   = 3.3;  // v
		MCUPer.fADC_Vref = 3.3;  // v

		for( i = 0; i < 4; i++ )
		{
			MCUPer.fRSSI_SR[i]     = 1.0; // K
			MCUPer.fRSSI_Offset[i] = 0;   // uA
			MCUPer.fVAPD_RH[i]     = 150; // K
			MCUPer.fVAPD_RL[i]     = 10;  // k
			MCUPer.fVAPD_Offset[i] = 0;   // uA
		}

		MCUPer.fICCI_R = 1.15; // ohm
		MCUPer.fICCO_R = 1.15; // ohm

		MCUPer.ADC_Bits  = 10;   // Bits
		MCUPer.ADC_Mode  = 1;    // Vref = VDD

		FLASH_Update ( FLASH_USE_ADDRESS, (uint8_t SI_SEG_XDATA*)&MCUPer, FLASH_USE_SIZE );
	}

	fADC_bits = (float)(pow( 2, MCUPer.ADC_Bits))-1;

	gFlagWriteFlash = 0;
}


//-----------------------------------------------------------------------------
// Global_Value_Init
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     Initialize Global Value
//
//-----------------------------------------------------------------------------
void	Global_Value_Init(void)
{
	Port_Monitor = 0x01; // enable auto monitor
	funccallback = NULL;
}


//-----------------------------------------------------------------------------
// WriteFlash_File
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     None
//
//-----------------------------------------------------------------------------
void	WriteFlash_File(void)
{
	if( gFlagWriteFlash == 1 )
	{
		IE_EA = 0; // Enable global interrupts
		FLASH_Update ( FLASH_USE_ADDRESS, (uint8_t SI_SEG_XDATA*)&MCUPer, FLASH_USE_SIZE );
		IE_EA = 1; // Enable global interrupts

		gFlagWriteFlash = 0;
	}
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Port_Monitor_Ctrl
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     Port monitor and control
//
//-----------------------------------------------------------------------------
void	Port_Monitor_Ctrl (void)
{
	uint16_t rada;
	rada = MCU_Register_Read(P0);
	rada = (rada >> 5) & 0x01;
	if(rada == 0x00){
		pin =0x00;
	}else if((rada == 0x01)&&(pin == 0x00)){
		// Set up internal REF register.
		AD5629_Write( AD5629R_CMD_SET_INT_REF, AD5629R_ADDR_DAC_ALL, 0x0001 );
		pin = 0x01;
	}else{
		pin = 0x01;
	}

}

