//--------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//--------------------------------------------------------------------------
//
// file name  :       device_pac1932.c
//
// description:       PAC1932 Driver
//
// Target     :       PAC1932
//
// version    :       V100.001
//					  2018/09/29 by ysung
//
//--------------------------------------------------------------------------

#ifndef _DEVICE_PAC1932_H_H
#define _DEVICE_PAC1932_H_H

#define PAC1932_SLAVE_ADDR	0x20// Device slave address

//reg
#define REFRESH_CMD 0x00
#define REFRESH_V_CMD 0x1f
#define CTRL_REG 0x01
#define CHANNEL_DIS 0x1c

#define VERSION 0xff
#define VID 0xfe
#define PID 0xfd

#define VBUS1_REG 0x07
#define VBUS2_REG 0x08
#define VBUS3_REG 0x09
#define VBUS4_REG 0x0a

#define VSENSE1_REG 0x0b
#define VSENSE2_REG 0x0c
#define VSENSE3_REG 0x0d
#define VSENSE4_REG 0x0e

#define VBUS1_AVG_REG 0x0F
#define VBUS2_AVG_REG 0x10
#define VBUS3_AVG_REG 0x11
#define VBUS4_AVG_REG 0x12

#define VSENSE1_AVG_REG 0x13
#define VSENSE2_AVG_REG 0x14
#define VSENSE3_AVG_REG 0x15
#define VSENSE4_AVG_REG 0x16

extern uint8_t pac1932_init(void);
extern uint8_t pac1932_read(uint8_t address,uint8_t len,uint8_t *buffer);
extern uint8_t pac1932_write(uint8_t address,uint8_t len,uint8_t *buffer);
extern uint16_t pac1932_read_vsense_1(void);
extern uint16_t pac1932_read_vbus_1(void);
extern uint8_t pac1932_read_pid(void);

#endif
