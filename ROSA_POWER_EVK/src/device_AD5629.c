//--------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//--------------------------------------------------------------------------
//
// file name  :       adc_0.c
//
// description:       AD5629R Driver
//
// Target     :       AD5629R
//
// version    :       V100.001
//					  2017/11/16 by roy zhou
//
//--------------------------------------------------------------------------

#include "include.h"

uint8_t  slave;

SI_SEGMENT_VARIABLE( DAC_array[8], uint16_t, SI_SEG_XDATA );
//-----------------------------------------------------------------------------
// AD5629_Init
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    channel,data
//
// Configures     set AD5629 DAC value
//
//-----------------------------------------------------------------------------
 uint8_t	AD5629_Init ( void )
 {
	uint8_t error;
	uint8_t i;

	slave = (AD5629R_SLAVE_ADDR(0x02)<<1);

	for( i = 0; i < 8; i++ )
	{
		DAC_array[i] = 0x1480;
	}

	// reset
	error = AD5629_Write( AD5629R_CMD_RESET, AD5629R_ADDR_DAC_ALL, 0xFFFF );

	delay_us_timer1( 1000 );

	// Power-down mode
	error = AD5629_Write( AD5629R_CMD_POWERDOWN, AD5629R_ADDR_DAC_ALL, 0x00FF );

	delay_us_timer1( 1000 );

	// Load clear code register.
	error = AD5629_Write( AD5629R_CMD_LOAD_CLEAR_CODE, AD5629R_ADDR_DAC_ALL, 0x0002 );

	delay_us_timer1( 1000 );

	// Set up internal REF register.
	error = AD5629_Write( AD5629R_CMD_SET_INT_REF, AD5629R_ADDR_DAC_ALL, 0x0001 );
	delay_us_timer1( 1000 );
	// Write to Input Register n, update all.
	error = AD5629_Write( AD5629R_CMD_WRITE_INPUT_N_UPDATE_ALL, AD5629R_ADDR_DAC_ALL, DAC_array[0] );

	return error;
 }

//-----------------------------------------------------------------------------
// AD5629_Write
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    channel,data
//
// Configures     set AD5629 DAC value
//
//-----------------------------------------------------------------------------
uint8_t	AD5629_Write( uint8_t COMMAND, uint8_t ADDR, uint16_t DAC )
{
	uint8_t address;
	uint8_t array[2];
	uint8_t error;

	address  = ((COMMAND<<4)&0xF0) | ((ADDR<<0)&0x0F);
	array[0] = (uint8_t)(DAC>>8);
	array[1] = (uint8_t)(DAC>>0);

	error = I2C_Master_writeBytes( slave, address, 2, array );

	return error;
}
