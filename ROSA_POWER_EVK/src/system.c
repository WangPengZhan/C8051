//-----------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//-----------------------------------------------------------------------------
//
// file name  :       system.c
//
// description:       system set file
//
// Target     :       C8051F34x / C8051F38x
//
// version    :       V100.001
//					  2017/11/16 by roy zhou
//
//-----------------------------------------------------------------------------
#include "include.h"


//-----------------------------------------------------------------------------
// SiLabs_Startup() Routine
// ----------------------------------------------------------------------------
// This function is called immediately after reset, before the initialization
// code is run in SILABS_STARTUP.A51 (which runs before main() ). This is a
// useful place to disable the watchdog timer, which is enable by default
// and may trigger before main() in some instances.
//-----------------------------------------------------------------------------
void SiLabs_Startup (void)
{
	PCA0MD &= ~PCA0MD_WDTE__BMASK;   // Disable watchdog timer
}


//-----------------------------------------------------------------------------
// VDDMon_Init
//-----------------------------------------------------------------------------
//
// Return Value : None
// Parameters   : None
//
// This function initializes the VDD Monitor and enables it as a reset source.
// The VDD Monitor is enabled following a power-on reset, but this routine
// explicitly enables the VDD Monitor.
//
// Note: If the VDD Monitor is not enabled or not enabled as a reset source,
// any attempt to write or erase Flash will cause a Flash Error Device Reset.
//-----------------------------------------------------------------------------
void VDDMon_Init(void)
{
   // VDM0CN and RSTSRC are accessible from all SFR pages

   // Step 1. Enable the VDD Monitor ( VDMEN bit in VDM0CN = ??.
   VDM0CN = VDM0CN_VDMEN__ENABLED;  // Enable the VDD Monitor

   // Step 2. Wait for the VDD Monitor to stabilize (approximately 5 ).
   // Note: This delay should be omitted if software contains routines which
   // erase or write Flash memory.
   // Omitted in this code
   WITE_VDD_STABILIZE;

   // Step 3. Select the VDD Monitor as a reset source (PORSF bit in
   // RSTSRC = ??.
   RSTSRC = RSTSRC_PORSF__SET;
}


// -------------------------------
// Initialization Functions
/**************************************************************************//**
 * @brief clock initialization
 *
 * Set fastest system clock (48Mhz)
 *****************************************************************************/
void Sysclk_Init (void)
{
	/*
	OSCICN  = OSCICN_IOSCEN__ENABLED;          // Enable intosc (48Mhz)
	FLSCL  |= FLSCL_FLRT__SYSCLK_BELOW_48_MHZ; // Set flash scale
	PFE0CN |= PFE0CN_PFEN__ENABLED;            // Enable prefetch
	CLKSEL  = CLKSEL_CLKSL__CLKMUL;            // select full speed sysclk
	*/
	FLSCL  |= FLSCL_FLRT__SYSCLK_BELOW_48_MHZ;
	PFE0CN |= PFE0CN_PFEN__ENABLED;

	OSCICN |= OSCICN_IOSCEN__ENABLED
	       |  OSCICN_IFCN__HFOSC_DIV_1;        // Select full speed HFOSC

	CLKMUL  = 0x00;                            // clear multiplier
	CLKMUL |= CLKMUL_MULEN__ENABLED;           // enable multiplier
	WITE_VDD_STABILIZE;
	CLKMUL |= CLKMUL_MULINIT__SET;             // Initialize multiplier
	WITE_VDD_STABILIZE;

	while(!(CLKMUL & CLKMUL_MULRDY__BMASK));   // Wati for multiplier to lock

	CLKSEL = CLKSEL_CLKSL__CLKMUL;             // select full speed sysclk
}


//-----------------------------------------------------------------------------
// SystemReset
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     SystemReset
//
//-----------------------------------------------------------------------------
void SystemReset(void)
{
	/*
	* Bit4 -- SWRSF: Software Reset Force and Flag.
	* 0: Read: Source of last reset was not a write to the SWRSF bit; Write: No Effect.
	* 1: Read: Source of last was a write to the SWRSF bit; Write: Forces a system reset.
	*/
	RSTSRC |= 0x10;
}


































