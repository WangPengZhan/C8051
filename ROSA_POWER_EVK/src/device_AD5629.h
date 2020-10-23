//--------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//--------------------------------------------------------------------------
//
// file name  :       adc_0.c
//
// description:       AD5629R Driver
//
// Target     :       AD5629R
//
// version    :       V100.001
//					  2017/11/16 by roy zhou
//
//--------------------------------------------------------------------------

#ifndef _DEVICE_AD5629_H_H
#define _DEVICE_AD5629_H_H

//------------------ AD5629R ID ------------------------//
#define AD5629R_SLAVE_ADDR(x)       (0x54 | ((x) & 0x03)) // Device slave address.


//------------- AD5629R Input Register --------------------------/
#define AD5629R_CMD(x)              ((0x00F & (uint32_t)(x)) << 20)
#define AD5629R_ADDR(x)             ((0x00F & (uint32_t)(x)) << 16)
#define AD5629R_DATA_BITS(x)        ((0xFFF & (uint32_t)(x)) <<  4)


//---------- Command Definitions (AD5629R_COMMAND(x) options) ----------------------//
#define AD5629R_CMD_WRITE_INPUT_N             0 // Write to Input Register n.
#define AD5629R_CMD_UPDATE_DAC_N              1 // Update DAC Register n.
#define AD5629R_CMD_WRITE_INPUT_N_UPDATE_ALL  2 // Write to Input Register n, update all.
#define AD5629R_CMD_WRITE_INPUT_N_UPDATE_N    3 // Write to and update DAC Channel n.
#define AD5629R_CMD_POWERDOWN                 4 // Power down/power up DAC.
#define AD5629R_CMD_LOAD_CLEAR_CODE           5 // Load clear code register.
#define AD5629R_CMD_LOAD_LDAC_REG             6 // Load LDAC register.
#define AD5629R_CMD_RESET                     7 // Reset (power-on reset)
#define AD5629R_CMD_SET_INT_REF               8 // Set up internal REF register.
#define AD5629R_CMD_ENABLE_MULTIPLE_BYTE      9 // Enable multiple byte mode.


//------ Address Commands (AD5629R_ADDRESS(x) options) -----------------------------//
#define AD5629R_ADDR_DAC_A      0x00 //DAC A
#define AD5629R_ADDR_DAC_B      0x01 //DAC B
#define AD5629R_ADDR_DAC_C      0x02 //DAC C
#define AD5629R_ADDR_DAC_D      0x03 //DAC D
#define AD5629R_ADDR_DAC_E      0x04 //DAC E
#define AD5629R_ADDR_DAC_F      0x05 //DAC F
#define AD5629R_ADDR_DAC_G      0x06 //DAC G
#define AD5629R_ADDR_DAC_H      0x07 //DAC H
#define AD5629R_ADDR_DAC_ALL    0x0F //All DACs


//------ Internal Reference Register ----------------//
#define AD5629R_INT_REF_OFF     0
#define AD5629R_INT_REF_ON      1

//-------------- Power-Down Modes of Operation -------------------------//
#define AD5629R_POWER_MODE(x)         ((0x03 & (unsigned short) (x)) << 8 )

#define AD5629R_PWRDN_NONE         0 // Normal operation
#define AD5629R_PWRDN_1K           1 // 1 kOhm to GND    (Power-down mode)
#define AD5629R_PWRDN_100K         2 // 100 kOhm to GND  (Power-down mode)
#define AD5629R_PWRDN_3STATE       3 // Three-state      (Power-down mode)

//------------------------ Clear Code Function -------------------------//
#define AD5629R_CODE_0X0000        0
#define AD5629R_CODE_0X8000        1
#define AD5629R_CODE_0XFFFF        2
#define AD5629R_CODE_NOP           3

extern  uint8_t	 AD5629_Init  ( void );
extern  uint8_t	 AD5629_Write ( uint8_t COMMAND, uint8_t ADDR, uint16_t DAC );

#endif


