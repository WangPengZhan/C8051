//-----------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//-----------------------------------------------------------------------------
//
// file name  :       flashUtils.h
//
// description:       Contains several useful utilities for writing and updating
//
// Target     :       C8051F34x / C8051F38x
//
// version    :       V100.001
//					  2017/11/16 by roy zhou
//
//-----------------------------------------------------------------------------

// Open Header #define
//-----------------------------------------------------------------------------
#ifndef _FLASHUTILS_H_
#define _FLASHUTILS_H_

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Exported Function Prototypes
//-----------------------------------------------------------------------------

// FLASH read/write/erase routines
void FLASH_Write  (FLADDR dest, char *src, uint16_t numbytes);
char * FLASH_Read (char *dest, FLADDR src, uint16_t numbytes);
void FLASH_Clear  (FLADDR addr, uint16_t numbytes);

// FLASH update/copy routines
void FLASH_Update (FLADDR dest, char *src, uint16_t numbytes);
void FLASH_Copy   (FLADDR dest, FLADDR src, uint16_t numbytes);

// FLASH test routines
void FLASH_Fill (FLADDR addr, uint32_t length, uint8_t fill);

//-----------------------------------------------------------------------------
// Close Header #define
//-----------------------------------------------------------------------------

#endif // _FLASHUTILS_H_

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
