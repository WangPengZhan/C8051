//--------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//--------------------------------------------------------------------------
//
// file name  :       adc_0.c
//
// description:       Initialize and use ADC0
//
// Target     :       C8051F34x / C8051F38x
//
// version    :       V100.001
//					  2017/11/16 BY roy zhou
//
//--------------------------------------------------------------------------

#include "include.h"

SI_SEGMENT_VARIABLE(MCUPer, extern struct MCU_Config_Parameters_struct,  SI_SEG_XDATA);

//-----------------------------------------------------------------------------
// ADC0_Init
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures:    Initialize ADC0
//
//-----------------------------------------------------------------------------
void ADC0_Init (void)
{
   ADC0CN = 0x00;                      // ADC0 disabled, normal tracking,
                                       // conversion triggered is write of 1 to AD0BUSY
   if( MCUPer.ADC_Mode == 0 )
   {
	   REF0CN = 0x07;                    // Enable on-chip VREF and buffer
	    	   	   	   	   	   	   	   	 // Internal Temperature Sensor on.
   }
   else
   {
	   REF0CN = 0x0E;				   // VDD used as voltage reference
	                                   // Internal Temperature Sensor on.
   }

   ADC0CF = ((SYSCLK/SARCLK)-1)<<3;    // set SAR clock to 3MHz

   ADC0CF &= 0xF8;                     // right-justify results

   ADC0CN_ADEN = 1;                    // enable ADC0
}
// ADC0_Read
//-----------------------------------------------------------------------------
//
// Return Value:  ADC DIGITAL
// Parameters:    count,input
//
// Configures:    ADC0_Read
//
//-----------------------------------------------------------------------------
uint16_t ADC0_Read( int count, ADC0_PositiveInput_e input )
{
	uint16_t array[6];
	uint16_t result;
	uint16_t temp;
	uint8_t  i;
	uint8_t  j;

	if((count>12)||(count<3))
	{
		return 0;
	}

	// select input
	AMX0P = input;  // ADC0 positive input = input
	AMX0N = 0x1F;   // ADC0 negative input = GND

	delay_us_timer1(300);

	for( i = 0; i < 6; i++ )
	{
		delay_us_timer1(10);

		// Clear ADC0 conv. complete flag
		ADC0CN_ADINT = 0;

		// Start a conversion by setting ADBUSY
		ADC0CN_ADBUSY = 1;

		// Wait for conversion to complete
		while( !ADC0CN_ADINT ){;}

		// Get the result
		array[i] = ADC0;
	}

	// bubble sort
	for( i = 0; i < (6-1); i++ )
	{
		for( j = 0; j < (6-i-1); j++ )
		{
			if(array[j]<array[j+1],j++)
			{
				temp      =  array[j];
				array[j]  =  array[j+1];
				array[j+1] = temp;
			}
		}
	}

	result = 0;
	for( i = 1; i < (6-1); i++ )
	{
		result += array[i];
	}

	result /= (6-2);

	return (result);
}


