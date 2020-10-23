//--------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//--------------------------------------------------------------------------
//
// file name  :       pac1932.c
//
// description:       pac1932 driver
//
// Target     :       pac1932
//
// version    :       V100.001
//					  2018/09/29 by ysung
//
//--------------------------------------------------------------------------

#include "include.h"

//-----------------------------------------------------------------------------
// pac1932 init
//-----------------------------------------------------------------------------
//
// Return Value:
// Parameters:
//
// Configures
//
//-----------------------------------------------------------------------------
 uint8_t pac1932_init(void)
 {
	uint8_t temp;
	//enable chip
	Port_PWRDN = 1;

	temp = 0x70;
	pac1932_write(CHANNEL_DIS,1,&temp);
	pac1932_write(REFRESH_V_CMD,0,&temp);
	delay_us_timer1(1000);
	return 0;
 }

//-----------------------------------------------------------------------------
// pac1932 read
//-----------------------------------------------------------------------------
//
// Return Value:
// Parameters:
//
// Configures
//
//-----------------------------------------------------------------------------
uint8_t	pac1932_read(uint8_t address,uint8_t len,uint8_t *buffer)
{
	I2C_Master_readBytes(PAC1932_SLAVE_ADDR,address,len,buffer);
	return 0;
}

//-----------------------------------------------------------------------------
// pac1932 write
//-----------------------------------------------------------------------------
//
// Return Value:
// Parameters:
//
// Configures
//
//-----------------------------------------------------------------------------
uint8_t	pac1932_write(uint8_t address,uint8_t len,uint8_t *buffer)
{
	I2C_Master_writeBytes(PAC1932_SLAVE_ADDR,address,len,buffer);
	return 0;
}
//-----------------------------------------------------------------------------
// pac1932 read ch1
//-----------------------------------------------------------------------------
//
// Return Value:
// Parameters:
//
// Configures
//
//-----------------------------------------------------------------------------
uint16_t pac1932_read_vsense_1(void)
{
	uint8_t buffer[2];
	uint16_t temp = 0x0000;

	IE_EA = 0;
	pac1932_write(REFRESH_V_CMD,0,buffer);
	IE_EA = 1;
	delay_us_timer1(1000);

	IE_EA = 0;
	pac1932_read(VSENSE1_AVG_REG,2,buffer);
	IE_EA = 1;

	temp = ((buffer[0] << 8) & 0xff00);
	temp |= (buffer[1] & 0x00ff);

	return temp;
}
//-----------------------------------------------------------------------------
// pac1932 read ch1
//-----------------------------------------------------------------------------
//
// Return Value:
// Parameters:
//
// Configures
//
//-----------------------------------------------------------------------------
uint16_t pac1932_read_vbus_1(void)
{
	uint8_t buffer[2];
	uint16_t temp = 0x0000;

	IE_EA = 0;
	pac1932_write(REFRESH_V_CMD,0,buffer);
	IE_EA = 1;
	delay_us_timer1(1000);

	IE_EA = 0;
	pac1932_read(VBUS1_REG,2,buffer);
	IE_EA = 1;

	temp = ((buffer[0] << 8) & 0xff00);
	temp |= (buffer[1] & 0x00ff);

	return temp;
}

//-----------------------------------------------------------------------------
// pac1932 read ch1
//-----------------------------------------------------------------------------
//
// Return Value:
// Parameters:
//
// Configures
//
//-----------------------------------------------------------------------------
uint8_t pac1932_read_pid(void)
{
	uint8_t temp = 0x00;

	pac1932_read(VERSION,1,&temp);

	return temp;
}
