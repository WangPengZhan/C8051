#ifndef _INCLUDE_H
#define _INCLUDE_H

#include <SI_C8051F340_Register_Enums.h> // SFR declarations
#include <string.h>
#include <LIMITS.h>
#include <math.h>

#include <stdint.h>
#include <stdbool.h>
#include <si_toolchain.h>
#include "efm8_usbxpress.h"
#include "descriptor.h"

// lib
//#include <sfr_page.h>
//#include <dac.h>
//#include <wdt_0.h>
//#include <flash_utils.h>
//#include <i2c_status.h>
//#include <timer.h>
//#include <system.h>

// user include file
#include "version.h"
#include "mcu_register.h"
#include "pins.h"
#include "system.h"
#include "timer.h"
#include "adc_0.h"
#include "function.h"
#include "i2c_master.h"
#include "usb_request.h"
#include "command_item.h"
#include "device_AD5629.h"
#include "flashPrimitives.h"
#include "flashUtils.h"

#include "spi_simulate.h"
#include "device_ad7298.h"
#include "device_pac1932.h"
#include "common.h"
#endif

