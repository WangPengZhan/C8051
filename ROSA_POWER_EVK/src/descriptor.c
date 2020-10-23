//-----------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//-----------------------------------------------------------------------------
//
// file name  :       descriptor.c
//
// description:       Descriptor information to pass to USB
//
// Target     :       C8051F34x / C8051F38x
//
// version    :       V100.001
//					  2017/11/16 by roy zhou
//
//-----------------------------------------------------------------------------

#include "include.h"


//--- [BEGIN] USB Descriptor Information [BEGIN] ---/

#define MFR_STRING          "Silicon Labs"        /// Manufacturer String
#define PROD_STRING         "ROSA_EVK_WITH_CDR"   /// Product String
#define SERIAL_STRING       "0009"                /// Serial String

USBX_STRING_DESC(USB_MfrStr[], MFR_STRING);
USBX_STRING_DESC(USB_ProductStr[], PROD_STRING);
USBX_STRING_DESC(USB_SerialStr[], SERIAL_STRING);


const USBX_Init_t initStruct =
{
   0x0145, //0x10C4,       // Vendor ID
   0x3009, //0xEA61,       // Product ID
   USB_MfrStr,             // Pointer to Manufacturer String
   USB_ProductStr,         // Pointer to Product String
   USB_SerialStr,          // Pointer to Serial String
   0x32,                     // Max Power / 2
   0x80,                   // Power Attribute
   0x0100,                 // Device Release # (BCD format)
   false                   // Use USB FIFO space true
};
