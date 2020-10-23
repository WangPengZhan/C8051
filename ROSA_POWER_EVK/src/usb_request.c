//-----------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//-----------------------------------------------------------------------------
//
// file name  :       usb_request.c
//
// description:       usb ISR request process
//
// Target     :       C8051F34x / C8051F38x
//
// version    :       V100.001
//					  2017/11/16 by roy zhou
//
//-----------------------------------------------------------------------------
#include "include.h"

#define USB_BUFFER_SIZE     (COMMAND_BUFFER_SIZE+6)       /// Size of USB buffer

SI_SEGMENT_VARIABLE( usb_msg, extern udi_command_msg_s, SI_SEG_XDATA);

SI_SEGMENT_VARIABLE(readLen,  uint16_t, SI_SEG_IDATA);
SI_SEGMENT_VARIABLE(writeLen, uint16_t, SI_SEG_IDATA);
/**************************************************************************//**
 * @brief USBXpress call-back
 *
 * This function is called by USBXpress. In this example any received data
 * sent back up to the host.
 *
 *****************************************************************************/

//-----------------------------------------------------------------------------
// my_usbxp_callback
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     usb ISR request process
//
//-----------------------------------------------------------------------------
void my_usbxp_callback(void)
{
	uint32_t intval = USBX_getCallbackSource();

	// Suspend
	if (intval & USBX_DEV_SUSPEND) // init
	{
		// Enter suspend mode to save power
		USBX_suspend();
	}

	// Device opened
	if (intval & USBX_DEV_OPEN) // open
	{
		// Prime first read
		USBX_blockRead((uint8_t*)(&usb_msg), USB_BUFFER_SIZE, &readLen);
	}

	// USB read complete
	if (intval & USBX_RX_COMPLETE) // host send data to device 1
	{
		USBX_blockRead((uint8_t*)(&usb_msg), USB_BUFFER_SIZE, &readLen);

		USB_Command_Decode();

		USBX_blockWrite((uint8_t*)(&usb_msg), USB_BUFFER_SIZE, &writeLen);
	}

	// USB write complete
	if (intval & USBX_TX_COMPLETE) // host send data to device 2
	{
		// The data was sent to the host, so start a new read
		USBX_blockRead((uint8_t*)(&usb_msg), USB_BUFFER_SIZE, &readLen);
	}
}

