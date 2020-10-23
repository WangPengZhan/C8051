//-----------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//-----------------------------------------------------------------------------
//
// file name  :       mcu_residter.c
//
// description:       mcu register read and set function
//
// Target     :       C8051F34x / C8051F38x
//
// version    :       V100.001
//					  2017/11/16 by roy zhou
//
//-----------------------------------------------------------------------------
#include "include.h"


//-----------------------------------------------------------------------------
// MCU_Register_Write
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    regadr, val
//
// Configures     MCU register write
//
//-----------------------------------------------------------------------------
uint16_t MCU_Register_Write( uint16_t regadr, uint16_t val )
{
   switch(regadr)
   {
   	   case 0x80 : return (P0      = val);
   	   case 0xF1 : return (P0MDIN  = val);
   	   case 0xA4 : return (P0MDOUT = val);
   	   case 0xD4 : return (P0SKIP  = val);
   	   case 0x90 : return (P1      = val);
   	   case 0xF2 : return (P1MDIN  = val);
   	   case 0xA5 : return (P1MDOUT = val);
   	   case 0xD5 : return (P1SKIP  = val);
   	   case 0xA0 : return (P2      = val);
   	   case 0xF3 : return (P2MDIN  = val);
   	   case 0xA6 : return (P2MDOUT = val);
   	   case 0xD6 : return (P2SKIP  = val);
   	   case 0xB0 : return (P3      = val);
   	   case 0xF4 : return (P3MDIN  = val);
   	   case 0xA7 : return (P3MDOUT = val);
   	   case 0xDF : return (P3SKIP  = val);
   	   case 0xC7 : return (P4      = val);
   	   case 0xF5 : return (P4MDIN  = val);
   	   case 0xAE : return (P4MDOUT = val);

       default   : break;
   }

   return 0xFFFF;
}




//-----------------------------------------------------------------------------
// MCU_Register_Read
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    regadr
//
// Configures     MCU register read
//
//-----------------------------------------------------------------------------
uint16_t MCU_Register_Read( uint16_t regadr )
{
   switch(regadr)
   {
   	   case 0x80 : return P0;
   	   case 0xF1 : return P0MDIN;
   	   case 0xA4 : return P0MDOUT;
   	   case 0xD4 : return P0SKIP;
   	   case 0x90 : return P1;
   	   case 0xF2 : return P1MDIN;
   	   case 0xA5 : return P1MDOUT;
   	   case 0xD5 : return P1SKIP;
   	   case 0xA0 : return P2;
   	   case 0xF3 : return P2MDIN;
   	   case 0xA6 : return P2MDOUT;
   	   case 0xD6 : return P2SKIP;
   	   case 0xB0 : return P3;
   	   case 0xF4 : return P3MDIN;
   	   case 0xA7 : return P3MDOUT;
   	   case 0xDF : return P3SKIP;
   	   case 0xC7 : return P4;
   	   case 0xF5 : return P4MDIN;
   	   case 0xAE : return P4MDOUT;

   	   default   : break;
   }

   return 0xFFFF;
}

