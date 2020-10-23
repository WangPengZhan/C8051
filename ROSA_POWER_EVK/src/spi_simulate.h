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

#define   SPI_SCK_ON()		Port_SPI_SCK = 1	//����sck�ߵ�ƽ
#define   SPI_SCK_OFF()		Port_SPI_SCK = 0	//����sckΪ��

#define   SPI_CS0_ON()		Port_SPI_CS0 = 1	//����cnv�ߵ�ƽ
#define   SPI_CS0_OFF()		Port_SPI_CS0 = 0	//����cnvΪ��

#define   SPI_MOSI_ON()		Port_SPI_MOSI = 1	//����mosi�ߵ�ƽ
#define   SPI_MOSI_OFF()	Port_SPI_MOSI = 0	//����mosiΪ��

#define   GET_MISO()		Port_SPI_MISO		//��ȡmiso��ƽ

//------------------------- Internal Function ------------------------/
extern uint8_t spi_init(void);
extern uint16_t spi_send(uint16_t buffer);
extern uint8_t spi_write(uint8_t num,uint16_t *buf);

#endif
