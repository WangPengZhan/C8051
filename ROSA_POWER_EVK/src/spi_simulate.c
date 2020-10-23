//-----------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//-----------------------------------------------------------------------------
//
// file name  :       spi_simulate.c
//
// description:       spi_simulate driver
//
// Target     :       C8051F34x / C8051F38x
//
// version    :       V100.001
//					  2018/09/29 by ysung
//
//-----------------------------------------------------------------------------
#include "include.h"

//-----------------------------------------------------------------------------
// spi_simulate init
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures
//
//-----------------------------------------------------------------------------
uint8_t spi_init(void)
{
	/*SPI0CFG   = 0x40;
	SPI0CN_NSSMD0 = 1;
	SPI0CN_NSSMD1 = 1;
	SPI0CN_SPIEN = 1;
	SPI0CKR   = (SYSCLK/(2*F_SCK_MAX)) - 1;*/
	SPI_SCK_ON();
	SPI_CS0_ON();
	SPI_MOSI_ON();

	return 0;
}

//-----------------------------------------------------------------------------
// spi_send
//-----------------------------------------------------------------------------
//
// Return Value: receive data
// Parameters: send data
//
// Configures
//
//-----------------------------------------------------------------------------
uint16_t spi_send(uint16_t buffer)
{
	uint8_t i;
	//uint8_t j;
	uint16_t temp = 0x0000;

	SPI_SCK_OFF();
	delay_us_timer1(1);

	for(i = 0;i < 16;i++){
		if(buffer & 0x8000){
			SPI_MOSI_ON();
		}else {
			SPI_MOSI_OFF();
		}

		delay_us_timer1(1);
		buffer <<= 1;

		SPI_SCK_ON();
		delay_us_timer1(2);

		temp <<= 1;
		if(GET_MISO()){
			temp |= 0x0001;
		}else {
			temp |= 0x0000;
		}
		SPI_SCK_OFF();
		delay_us_timer1(2);
	}

	return temp;
}

//-----------------------------------------------------------------------------
// spi_write
//-----------------------------------------------------------------------------
//
// Return Value: none
// Parameters: send num,send data,receive data
//
// Configures
//
//-----------------------------------------------------------------------------
uint8_t spi_write(uint8_t num,uint16_t *buf)
{
	uint8_t i;

	for(i = 0;i < num;i++){
		buf[i] = spi_send(buf[i]);
	}

	return 0;
}
