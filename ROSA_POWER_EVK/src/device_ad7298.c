//--------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//--------------------------------------------------------------------------
//
// file name  :       ad7298.c
//
// description:       ad7298 driver
//
// Target     :       ad7298
//
// version    :       V100.001
//					  2019/08/30 wm
//
//--------------------------------------------------------------------------

#include "include.h"
SI_SEGMENT_VARIABLE( ad7298_data[4], uint16_t, SI_SEG_XDATA );
SI_SEGMENT_VARIABLE( ad7298_value[4], uint32_t, SI_SEG_XDATA );
//uint16_t ad7298_data[4];
//uint32_t idata ad7298_value[4];

//-----------------------------------------------------------------------------
// ad7298 init
//-----------------------------------------------------------------------------
//
// Return Value:
// Parameters:
//
// Configures
//
//-----------------------------------------------------------------------------
 uint8_t ad7298_init(void)
 {
	spi_init();
	ad7298_read(0);
	ad7298_read(1);

	ad7298_value[0] = 0x00;
	ad7298_value[1] = 0x00;
	ad7298_value[2] = 0x00;
	ad7298_value[3] = 0x00;

	return 0;
 }

//-----------------------------------------------------------------------------
// ad7298 read
//-----------------------------------------------------------------------------
//
// Return Value:
// Parameters:
//
// Configures
//
//-----------------------------------------------------------------------------
uint16_t ad7298_read(uint16_t channel)
{
	uint16_t temp[3];
	uint16_t value;
	uint8_t i;
	channel &= 0x07;
	switch(channel){
	case 0x00: channel = 0x80;break;
	case 0x01: channel = 0x40;break;
	case 0x02: channel = 0x20;break;
	case 0x03: channel = 0x10;break;
	case 0x04: channel = 0x08;break;
	case 0x05: channel = 0x04;break;
	case 0x06: channel = 0x02;break;
	case 0x07: channel = 0x01;break;
	}
	temp[0] = 0x8018 | (channel << 6);
	temp[1] = 0x0000;
	temp[2] = 0x0000;
	for(i = 0;i < 3;i++){
		Port_SPI_CS0 = 0;
		delay_us_timer1(2);
		value = spi_send(temp[i]);
		delay_us_timer1(2);
		Port_SPI_CS0 = 1;
		delay_us_timer1(2);
	}
	return value;
}
//-----------------------------------------------------------------------------
