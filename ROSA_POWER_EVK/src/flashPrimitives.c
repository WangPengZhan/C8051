//-----------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//-----------------------------------------------------------------------------
//
// file name  :       flashPrimitives.c
//
// description:       Contains several useful utilities for writing and updating
//
// Target     :       C8051F34x / C8051F38x
//
// version    :       V100.001
//					  2017/11/16 by roy zhou
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "include.h"

//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// FLASH_ByteWrite
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   :
//   1) FLADDR addr - address of the byte to write to
//                    valid range is from 0x0000 to 0x7DFE for 32K devices
//                    valid range is from 0x0000 to 0x3FFE for 16K devices
//   2) char byte - byte to write to Flash.
//
// This routine writes <byte> to the linear FLASH address <addr>.
//-----------------------------------------------------------------------------
void FLASH_ByteWrite (FLADDR addr, char byte)
{
   bit EA_SAVE = IE_EA;                // Preserve EA
   char xdata * data pwrite;           // FLASH write pointer

   IE_EA = 0;                          // Disable interrupts

   VDM0CN = 0xA0;                      // Enable VDD monitor and high threshold

   RSTSRC = 0x02;                      // Enable VDD monitor as a reset source

   pwrite = (char xdata *) addr;

   FLKEY  = 0xA5;                      // Key Sequence 1
   FLKEY  = 0xF1;                      // Key Sequence 2
   PSCTL |= 0x01;                      // PSWE = 1 which enables writes

   VDM0CN = 0xA0;                      // Enable VDD monitor and high threshold

   RSTSRC = 0x02;                      // Enable VDD monitor as a reset source

   *pwrite = byte;                     // Write the byte

   PSCTL &= ~0x01;                     // PSWE = 0 which disable writes

   IE_EA = EA_SAVE;                    // Restore interrupts
}


//-----------------------------------------------------------------------------
// FLASH_ByteRead
//-----------------------------------------------------------------------------
//
// Return Value :
//      unsigned char - byte read from Flash
// Parameters   :
//   1) FLADDR addr - address of the byte to read to
//                    valid range is from 0x0000 to 0x7DFE for 32K devices
//                    valid range is from 0x0000 to 0x3FFE for 16K devices
//
// This routine reads a <byte> from the linear FLASH address <addr>.
//-----------------------------------------------------------------------------
uint8_t FLASH_ByteRead (FLADDR addr)
{
   bit EA_SAVE = IE_EA;                // Preserve EA
   char code * data pread;             // FLASH read pointer
   uint8_t     byte;

   IE_EA = 0;                          // Disable interrupts

   pread = (char code *) addr;

   byte = *pread;                      // Read the byte

   IE_EA = EA_SAVE;                    // Restore interrupts

   return byte;
}


//-----------------------------------------------------------------------------
// FLASH_PageErase
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   :
//   1) FLADDR addr - address of any byte in the page to erase
//                    valid range is from 0x0000 to 0x7BFF for 32K devices
//                    valid range is from 0x0000 to 0x3DFF for 16K devices
//
// This routine erases the FLASH page containing the linear FLASH address
// <addr>.  Note that the page of Flash containing the Lock Byte cannot be
// erased if the Lock Byte is set.
//
//-----------------------------------------------------------------------------
void FLASH_PageErase (FLADDR addr)
{
   bit EA_SAVE = IE_EA;                // Preserve EA
   char xdata * data pwrite;           // FLASH write pointer

   IE_EA = 0;                          // Disable interrupts

   VDM0CN = 0x80;                      // Enable VDD monitor

   RSTSRC = 0x02;                      // Enable VDD monitor as a reset source

   pwrite = (char xdata *) addr;

   FLKEY  = 0xA5;                      // Key Sequence 1
   FLKEY  = 0xF1;                      // Key Sequence 2
   PSCTL |= 0x03;                      // PSWE = 1; PSEE = 1


   VDM0CN = 0x80;                      // Enable VDD monitor

   RSTSRC = 0x02;                      // Enable VDD monitor as a reset source
   *pwrite = 0;                        // Initiate page erase

   PSCTL &= ~0x03;                     // PSWE = 0; PSEE = 0

   IE_EA = EA_SAVE;                    // Restore interrupts
}

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
