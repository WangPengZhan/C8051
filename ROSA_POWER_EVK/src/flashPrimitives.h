//-----------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//-----------------------------------------------------------------------------
//
// file name  :       flashPrimitives.h
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
// Open Header #define
//-----------------------------------------------------------------------------
#ifndef _FLASHPRIMITIVES_H_
#define _FLASHPRIMITIVES_H_

//-----------------------------------------------------------------------------
// Structures, Unions, Enumerations, and Type Definitions
//-----------------------------------------------------------------------------
typedef uint16_t FLADDR;

//-----------------------------------------------------------------------------
// Global Constants
//-----------------------------------------------------------------------------

#ifndef FLASH_PAGESIZE
#define FLASH_PAGESIZE 512
#endif

#ifndef FLASH_TEMP
#define FLASH_TEMP 0xF800L             // For 64K Flash devices
//#define FLASH_TEMP 0x7C00L           // For 32K Flash devices
//#define FLASH_TEMP 0x3C00L           // For 16K Flash devices
#endif


#ifndef FLASH_LAST
#define FLASH_LAST 0xFA00L             // For 64K Flash devices
//#define FLASH_LAST 0x7E00L           // For 32K Flash devices
//#define FLASH_LAST 0x3E00L           // For 16K Flash devices
#endif

//-----------------------------------------------------------------------------
// Exported Function Prototypes
//-----------------------------------------------------------------------------

extern void    FLASH_ByteWrite (FLADDR addr, char byte);
extern uint8_t FLASH_ByteRead  (FLADDR addr);
extern void    FLASH_PageErase (FLADDR addr);

//-----------------------------------------------------------------------------
// Close Header #define
//-----------------------------------------------------------------------------

#endif // _FLASHPRIMITIVES_H_

//-----------------------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------------------
