//-----------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//-----------------------------------------------------------------------------
//
// file name  :       ROSA_EVK.c
//
// description:       main file
//
// Target     :       C8051F34x
//
// version    :       V100.001
//					  2017/11/16 by roy zhou
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "include.h"

SI_SEGMENT_VARIABLE(ad5629IsCuted, uint8_t, SI_SEG_XDATA);

//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
// Note: the software watchdog timer is not disabled by default in this
// example, so a long-running program will reset periodically unless
// the timer is disabled or your program periodically writes to it.
//
// Review the "Watchdog Timer" section under the part family's datasheet
// for details. To find the datasheet, select your part in the
// Simplicity Launcher and click on "Data Sheet".
//-----------------------------------------------------------------------------
int main (void)
{
	VDDMon_Init();						   // Enable VDD Monitor and as a reset source

	Sysclk_Init();                         // Initialize system clock

	LoadFlash_File();					   // load flash file

	Port_Init();                           // Initialize crossbar and GPIO

	Global_Value_Init();				   // Initialize Global Value

	ADC0_Init();						   // Initialize ADC0

	I2C_Master_Init();					   // Initialize I2C Master
	spi_init();

	USB_Command_Init();					   // Initialize USB Command tree

	AD5629_Init();						   // Initialize AD5629

	ad7298_init();							//initialize ad7298

	pac1932_init();							//initialize pac1932

	// USBXpress Initialization
	USBX_init(&initStruct);

	// Enable USBXpress API interrupts
	USBX_apiCallbackEnable(my_usbxp_callback);

	IE_EA = 1; // Enable global interrupts

	ad5629IsCuted = 0x00;

	while (1)  // Spin forever
	{
		if(ad5629IsCuted)
		{
			Port_Init();
			AD5629_Init();
			ad5629IsCuted = 0x00;
		}

		if( funccallback != NULL )
		{
			funccallback();
			funccallback = NULL;
		}
		WriteFlash_File();
		Port_Monitor_Ctrl();

	}
}
