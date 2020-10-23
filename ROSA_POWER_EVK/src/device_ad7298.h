//--------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//--------------------------------------------------------------------------
//
// file name  :       device_ad7298.c
//
// description:       ad7298 driver
//
// Target     :       ad7298
//
// version    :       V100.001
//					  2019/08/30 by wm
//
//--------------------------------------------------------------------------

#ifndef __DEVICE_AD7298_H_H
#define __DEVICE_AD7298_H_H

extern uint8_t ad7298_init(void);
extern uint16_t ad7298_read(uint16_t channel);
//extern uint16_t ad7298_data[4];
//extern uint32_t  ad7298_value[4];

#endif
