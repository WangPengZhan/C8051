//-----------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//-----------------------------------------------------------------------------
//
// file name  :       spi_simulate.h
//
// description:       spi driver
//
// Target     :       C8051F34x / C8051F38x
//
// version    :       V100.001
//					  2018/09/29 by ysung
//
//-----------------------------------------------------------------------------
#ifndef __SPI_H
#define __SPI_H

#define   SPI_SCK_ON()		Port_SPI_SCK = 1	//设置sck高电平
#define   SPI_SCK_OFF()		Port_SPI_SCK = 0	//设置sck为低

#define   SPI_CS0_ON()		Port_SPI_CS0 = 1	//设置cnv高电平
#define   SPI_CS0_OFF()		Port_SPI_CS0 = 0	//设置cnv为低

#define   SPI_MOSI_ON()		Port_SPI_MOSI = 1	//设置mosi高电平
#define   SPI_MOSI_OFF()	Port_SPI_MOSI = 0	//设置mosi为低

#define   GET_MISO()		Port_SPI_MISO		//读取miso电平

//------------------------- Internal Function ------------------------/
extern uint8_t spi_init(void);
extern uint16_t spi_send(uint16_t buffer);
extern uint8_t spi_write(uint8_t num,uint16_t *buf);

#endif
