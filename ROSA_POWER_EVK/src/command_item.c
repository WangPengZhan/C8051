//-----------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//-----------------------------------------------------------------------------
//
// file name  :       command_item.c
//
// description:       USB command process
//
// Target     :       C8051F34x / C8051F38x
//
// version    :       V100.001
//					  2017/11/16 by roy zhou
//
//-----------------------------------------------------------------------------

#include "include.h"

// 命令执行函数数组
SI_SEGMENT_VARIABLE(Command_Array[COMMANDTYPE_COUNT_MAX], CommandItem_s, SI_SEG_XDATA);
SI_SEGMENT_VARIABLE(usb_msg, udi_command_msg_s, SI_SEG_XDATA);
SI_SEGMENT_VARIABLE(MCUPer,  extern struct MCU_Config_Parameters_struct,  SI_SEG_XDATA);
SI_SEGMENT_VARIABLE(Port_Monitor,  extern uint8_t,  SI_SEG_XDATA);
SI_SEGMENT_VARIABLE(DAC_array[8],  extern uint16_t, SI_SEG_XDATA );
SI_SEGMENT_VARIABLE(gFlagWriteFlash, extern uint8_t, SI_SEG_XDATA);
SI_SEGMENT_VARIABLE(rdata_array[30],  uint16_t, SI_SEG_XDATA );
SI_SEGMENT_VARIABLE(ad5629IsCuted, extern uint8_t, SI_SEG_XDATA);
//-----------------------------------------------------------------------------
// USB_Command_Init
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     Initialize USB Command tree
//
//-----------------------------------------------------------------------------
void USB_Command_Init (void)
{
	// General Command
	Command_Array[0].count = 4;
	Command_Array[0].item[0].pfun = Func_CMD_General_QueryVersion;
	Command_Array[0].item[1].pfun = Func_CMD_General_GetEVK_ID;
	Command_Array[0].item[2].pfun = Func_CMD_General_SetEVK_ID;
	Command_Array[0].item[3].pfun = Func_CMD_General_Reboot;

	// MCU Register Command
	Command_Array[1].count = 4;
	Command_Array[1].item[0].pfun = Func_CMD_MCU_ReadRegister;
	Command_Array[1].item[1].pfun = Func_CMD_MCU_WriteRegister;
	Command_Array[1].item[2].pfun = Func_CMD_MCU_SetRegister;
	Command_Array[1].item[3].pfun = Func_CMD_MCU_ClearRegister;

	// MCU Register Command
	Command_Array[2].count = 2;
	Command_Array[2].item[0].pfun = Func_CMD_I2C_ReadArray;
	Command_Array[2].item[1].pfun = Func_CMD_I2C_WriteArray;

	// MCU adc read
	Command_Array[3].count = 2;
	Command_Array[3].item[0].pfun = Func_CMD_ADC_GetFeature;
	Command_Array[3].item[1].pfun = Func_CMD_ADC_SetFeature;

	// AD7298 Command
	Command_Array[4].count = 1;
	Command_Array[4].item[0].pfun = Func_CMD_AD7298_Read;

	// SI544 Command
	//Command_Array[5].count = 2;
	//Command_Array[5].item[0].pfun = Func_CMD_SI544_Set;
	//Command_Array[5].item[1].pfun = Func_CMD_SI544_Read;

	// Control monitor
	Command_Array[6].count = 2;
	Command_Array[6].item[0].pfun = Func_CMD_Ctrl_GetPortMonitor;
	Command_Array[6].item[1].pfun = Func_CMD_Ctrl_SetPortMonitor;

	//PAC1932 Command
	Command_Array[7].count = 2;
	Command_Array[7].item[0].pfun = Func_CMD_PAC1932_Read;
	Command_Array[7].item[1].pfun = Func_CMD_PAC1932_Read_BUS;

	//Coeff Command
	Command_Array[8].count = 2;
	Command_Array[8].item[0].pfun = Func_CMD_Get_AD7298_Coeff;
	Command_Array[8].item[1].pfun = Func_CMD_Set_AD7298_Coeff;

	//Power Command
	Command_Array[9].count = 2;
	Command_Array[9].item[0].pfun = Func_CMD_Get_Power;
	Command_Array[9].item[1].pfun = Func_CMD_Set_Power;
}


//-----------------------------------------------------------------------------
// USB_Command_Decode
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     Decode USB Command
//
//-----------------------------------------------------------------------------
bool USB_Command_Decode()
{
	uint8_t status;

	// 判断命令类型是否超过范围
	if( usb_msg.write.cmd_type >= COMMANDTYPE_COUNT_MAX )
	{
		usb_msg.read.cmd_status = sCMDUnknownType;
		return false;
	}

	// 判断此命令类型下得命令ID是否超过范围
	if( usb_msg.write.cmd_id >= Command_Array[usb_msg.write.cmd_type].count )
	{
		usb_msg.read.cmd_status = sCMDUnknownId;
		return false;
	}

	// 执行命令处理函数，返回执行状态代码
	if( Command_Array[usb_msg.write.cmd_type].item[usb_msg.write.cmd_id].pfun != NULL )
	{
		status = Command_Array[usb_msg.write.cmd_type].item[usb_msg.write.cmd_id].pfun();

		if ( status != sCMDDoing )
	    {
			usb_msg.read.cmd_status = status;
	    }
	}
	else
	{
		usb_msg.read.cmd_status = sCMDSuccess;
	}

	return true;
}


//-----------------------------------------------------------------------------
// Func_CMD_General_QueryVersion
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     Get Firmware version
//
//-----------------------------------------------------------------------------
uint8_t Func_CMD_General_QueryVersion( void )
{
	usb_msg.read.databuf[0x00] = FIRMWARE_NAME1;
	usb_msg.read.databuf[0x01] = FIRMWARE_NAME2;
	usb_msg.read.databuf[0x02] = FIRMWARE_NAME3;
	usb_msg.read.databuf[0x03] = VEISION;
	usb_msg.read.databuf[0x04] = BUILD;

	usb_msg.read.datalength = 5;
	return sCMDSuccess;
}



//-----------------------------------------------------------------------------
// Func_CMD_General_GetEVK_ID
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Get EVK ID
//
//-----------------------------------------------------------------------------
uint8_t Func_CMD_General_GetEVK_ID (void)
{
	int i;


	for( i = 0; i < 4; i++ )
	{
		usb_msg.read.databuf[i] = MCUPer.gID[i];
	}

	usb_msg.read.datalength = 4;
	return sCMDSuccess;
}


//-----------------------------------------------------------------------------
// Func_CMD_General_SetEVK_ID
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// set EVK ID
//
//-----------------------------------------------------------------------------
uint8_t Func_CMD_General_SetEVK_ID (void)
{
	int i;
	//uint16_t length;

	//length = usb_msg.write.datalength;
	for( i = 0; i < 4; i++ )
	{
		MCUPer.gID[i] = usb_msg.write.databuf[i];
	}

	gFlagWriteFlash = 1;
	return sCMDSuccess;
}


//-----------------------------------------------------------------------------
// Func_CMD_General_Reboot
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     Reboot MCU system
//
//-----------------------------------------------------------------------------
uint8_t Func_CMD_General_Reboot( void )
{
	funccallback = SystemReset;
	usb_msg.read.datalength = 0;
	return sCMDSuccess;
}


//-----------------------------------------------------------------------------
// Func_CMD_MCU_ReadRegister
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     Read MCU register
//
//-----------------------------------------------------------------------------
uint8_t Func_CMD_MCU_ReadRegister( void )
{
   uint16_t adr;
   uint16_t rdata;

	adr = ((uint16_t)usb_msg.write.databuf[0x00]<<8) |
	      ((uint16_t)usb_msg.write.databuf[0x01]<<0);

   rdata = MCU_Register_Read(adr);

   usb_msg.read.databuf[0x02] = (uint8_t)(rdata>>8);
   usb_msg.read.databuf[0x03] = (uint8_t)(rdata>>0);
   usb_msg.read.datalength    = 4;

   return sCMDSuccess;
}


//-----------------------------------------------------------------------------
// Func_CMD_MCU_WriteRegister
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     Write MCU register
//
//-----------------------------------------------------------------------------
uint8_t Func_CMD_MCU_WriteRegister( void )
{
	uint16_t adr;
	uint16_t wdata, rdata;

	adr = ((uint16_t)usb_msg.write.databuf[0x00]<<8) |
	      ((uint16_t)usb_msg.write.databuf[0x01]<<0);

	wdata = (uint16_t)(usb_msg.write.databuf[0x02]<<8) |
			(uint16_t)(usb_msg.write.databuf[0x03]<<0);

	rdata = MCU_Register_Write(adr,wdata);

	usb_msg.read.databuf[0x02] = (uint8_t)(rdata>>8);
	usb_msg.read.databuf[0x03] = (uint8_t)(rdata>>0);
	usb_msg.read.datalength    = 4;

   return sCMDSuccess;
}


//-----------------------------------------------------------------------------
// Func_CMD_MCU_SetRegister
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     Set MCU register
//
//-----------------------------------------------------------------------------
uint8_t Func_CMD_MCU_SetRegister( void )
{
	uint16_t adr;
	uint16_t wdata, rdata;

	adr = ((uint16_t)usb_msg.write.databuf[0x00]<<8) |
	      ((uint16_t)usb_msg.write.databuf[0x01]<<0);

	wdata = (uint16_t)(usb_msg.write.databuf[0x02]<<8) |
			(uint16_t)(usb_msg.write.databuf[0x03]<<0);

	if(adr == (uint16_t)(0x80))
	{
		if(wdata == (uint16_t)(0x01 << 2) )
		{
			SCL_HIZ();
			SDA_HIZ();
			ad5629IsCuted = 0x01;
		}
	}

	rdata = MCU_Register_Read(adr);
	wdata = wdata|rdata;
	rdata = MCU_Register_Write(adr,wdata);

	usb_msg.read.databuf[0x02] = (uint8_t)(rdata>>8);
	usb_msg.read.databuf[0x03] = (uint8_t)(rdata>>0);
	usb_msg.read.datalength    = 4;

	return sCMDSuccess;
}


//-----------------------------------------------------------------------------
// Func_CMD_MCU_ClearRegister
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     Clear MCU register
//
//-----------------------------------------------------------------------------
uint8_t Func_CMD_MCU_ClearRegister( void )
{
   uint16_t adr;
   uint16_t wdata, rdata;

   adr = ((uint16_t)usb_msg.write.databuf[0x00]<<8) |
         ((uint16_t)usb_msg.write.databuf[0x01]<<0);

   wdata = ~( (uint16_t)(usb_msg.write.databuf[0x02]<<8) |
		      (uint16_t)(usb_msg.write.databuf[0x03]<<0) );

	if(adr == (uint16_t)(0x80))
	{
		if(wdata == (uint16_t)~(0x01 << 2) )
		{
			P0      = 0x00;
		    P0MDIN  = 0xFF;
			P0MDOUT = 0x00;

			P1      = 0x00;
		    P1MDIN  = 0xFF;
			P1MDOUT = 0x00;

			P2      = 0x00;
		    P2MDIN  = 0xFF;
			P2MDOUT = 0x00;

			P3      = 0x00;
		    P3MDIN  = 0xFF;
			P3MDOUT = 0x00;
		}
	}

   rdata = MCU_Register_Read(adr);
   wdata = wdata&rdata;
   rdata = MCU_Register_Write(adr,wdata);

   usb_msg.read.databuf[0x02] = (uint8_t)(rdata>>8);
   usb_msg.read.databuf[0x03] = (uint8_t)(rdata>>0);
   usb_msg.read.datalength    = 4;

   return sCMDSuccess;
}


//-----------------------------------------------------------------------------
// Func_CMD_I2C_ReadArray
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     I2C read array
//
//-----------------------------------------------------------------------------
uint8_t Func_CMD_I2C_ReadArray( void )
{
   uint8_t  sleaddr;
   uint8_t  regaddr;
   uint16_t length;

   sleaddr = usb_msg.write.databuf[0x00];
   regaddr = usb_msg.write.databuf[0x01];
   length  = ( (uint16_t)usb_msg.write.databuf[0x02]<<8) |
		     ( (uint16_t)usb_msg.write.databuf[0x03]<<0);

  if( (sleaddr & 0xFE) == 0xAC )
   {
	   usb_msg.read.databuf[0x04] = (uint8_t)(DAC_array[regaddr&0x07]>>8);
	   usb_msg.read.databuf[0x05] = (uint8_t)(DAC_array[regaddr&0x07]>>0);
   }else{
	   if ( I2C_Master_readBytes( sleaddr, regaddr, length,
	                             (uint8_t*)&(usb_msg.read.databuf[0x04])) )
	   {
		  usb_msg.read.datalength  = 0;
	      return sCMDFailed;
	   }
   }

   usb_msg.read.datalength  = length;
   return sCMDSuccess;
}


//-----------------------------------------------------------------------------
// Func_CMD_I2C_WriteArray
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     I2C write array
//
//-----------------------------------------------------------------------------
uint8_t Func_CMD_I2C_WriteArray( void )
{
    uint8_t  sleaddr;
    uint8_t  regaddr;
    uint16_t length;

    sleaddr = usb_msg.write.databuf[0x00];
    regaddr = usb_msg.write.databuf[0x01];
    length  = ( (uint16_t)usb_msg.write.databuf[0x02]<<8) |
		      ( (uint16_t)usb_msg.write.databuf[0x03]<<0);

    if( (sleaddr & 0xFE) == 0xAC )
    {
	    DAC_array[regaddr&0x07]  = ( (uint16_t)usb_msg.write.databuf[0x04]<<8) |
			      	  	  	       ( (uint16_t)usb_msg.write.databuf[0x05]<<0);
    }

    if ( I2C_Master_writeBytes( sleaddr, regaddr, length,
                                (uint8_t *)&(usb_msg.write.databuf[0x04])) )
    {
    	usb_msg.read.datalength = 0;
        return sCMDFailed;
    }

    usb_msg.read.datalength = length;
    return sCMDSuccess;
}

//-----------------------------------------------------------------------------
// Func_CMD_ADC_GetFeature
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     Get MCU ADC feature
//
//-----------------------------------------------------------------------------
uint8_t  Func_CMD_ADC_GetFeature(void)
{
	int i;

	uint8_t *pData = (uint8_t SI_SEG_XDATA*)(&MCUPer);

	for( i = 0; i < FLASH_USE_SIZE; i++ )
	{
		usb_msg.read.databuf[i] = pData[i];
	}

	usb_msg.read.datalength = FLASH_USE_SIZE;
	return sCMDSuccess;
}

//-----------------------------------------------------------------------------
// Func_CMD_ADC_SetFeature
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     Set MCU ADC feature
//
//-----------------------------------------------------------------------------
uint8_t  Func_CMD_ADC_SetFeature(void)
{
	int i;

	uint8_t *pData = (uint8_t SI_SEG_XDATA*)(&MCUPer);

	for( i = 0; i < FLASH_USE_SIZE; i++ )
	{
		pData[i] = usb_msg.write.databuf[i];
	}

	//fADC_bits = (float)(pow( 2, MCUPer.ADC_Bits ))-1;

	gFlagWriteFlash = 1;

	usb_msg.read.datalength = 0;
	return sCMDSuccess;
}

//-----------------------------------------------------------------------------
// Func_CMD_AD7298_Read
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     AD7298 Read
//
//-----------------------------------------------------------------------------
uint8_t Func_CMD_AD7298_Read( void )
{
	   uint16_t adr;
	   uint16_t rdata;
	   uint8_t i;
	   uint32_t rdata_sum = 0;
		adr = ((uint16_t)usb_msg.write.databuf[0x00]<<8) |
		      ((uint16_t)usb_msg.write.databuf[0x01]<<0);
	   for(i = 0; i < 30; i++){
		   rdata_array[i] = ad7298_read(adr);
	   }
	   sort(rdata_array,30);
	   for(i = 0; i < 10 ; i++){
		   rdata_sum += rdata_array[10 + i];
	   }
	   rdata = rdata_sum / 10;

	   usb_msg.read.databuf[0x02] = (uint8_t)(rdata>>8);
	   usb_msg.read.databuf[0x03] = (uint8_t)(rdata>>0);
	   usb_msg.read.datalength    = 4;

	   return sCMDSuccess;
}
/*
//-----------------------------------------------------------------------------
// Func_CMD_SI544_Set
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     SI544 Set
//
//-----------------------------------------------------------------------------
uint8_t Func_CMD_SI544_Set( void )
{
		uint8_t i;
		uint8_t *Data =( uint8_t *)(&si544_freq);
		for( i = 0; i < 4; i++ ){
		   Data[i] = usb_msg.write.databuf[i];
		}
		SI544_Config(si544_freq);

		usb_msg.read.datalength = 0;
		return sCMDSuccess;
}
//-----------------------------------------------------------------------------

// Func_CMD_SI544_Read
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     SI544 Read
//
//-----------------------------------------------------------------------------
uint8_t Func_CMD_SI544_Read( void )
{
	   uint8_t *rdata =( uint8_t *)(&si544_freq);
	  // SI544_Read(rdata);
	   usb_msg.read.databuf[0x00] = rdata[0];
	   usb_msg.read.databuf[0x01] = rdata[1];
	   usb_msg.read.databuf[0x02] = rdata[2];
	   usb_msg.read.databuf[0x03] = rdata[3];
	   usb_msg.read.datalength    = 4;

	   return sCMDSuccess;
}
*/
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Func_CMD_Ctrl_GetPortMonitor
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     Get this value portMonitor
//
//-----------------------------------------------------------------------------
uint8_t  Func_CMD_Ctrl_GetPortMonitor (void)
{
	usb_msg.read.databuf[0x00] = (Port_Monitor&0x01);
	usb_msg.read.datalength    = 0x01;
	return sCMDSuccess;
}


//-----------------------------------------------------------------------------
// Func_CMD_Ctrl_SetPortMonitor
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     Set this value portMonitor
//
//-----------------------------------------------------------------------------
uint8_t  Func_CMD_Ctrl_SetPortMonitor (void)
{
	Port_Monitor = (usb_msg.write.databuf[0x00]&0x01);
	usb_msg.read.datalength = 0x01;
	return sCMDSuccess;
}
//-----------------------------------------------------------------------------
// Func_CMD_PAC1932_Read
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     PAC1932 Read
//
//-----------------------------------------------------------------------------
uint8_t Func_CMD_PAC1932_Read( void )
{
	int     i;
	float   value;
	uint16_t ADCValue;
	float    SamplingValue;
	uint8_t *pData = (uint8_t*)(&value);
	ADCValue = pac1932_read_vsense_1();
	SamplingValue = ADCValue;
	SamplingValue *= 100.;
	SamplingValue /= 0.3;
	SamplingValue /= 65536;
	SamplingValue *= 0.96;
    value = SamplingValue;
	for( i = 0; i < 4; i++ )
	{
		usb_msg.read.databuf[i] = pData[i];
	}
	usb_msg.read.datalength = 4;
	return sCMDSuccess;

}
//-----------------------------------------------------------------------------
// Func_CMD_PAC1932_Read BUS
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     PAC1932 Read BUS
//
//-----------------------------------------------------------------------------
uint8_t Func_CMD_PAC1932_Read_BUS( void )
{
	int     i;
	float   value;
	uint16_t ADCValue;
	float    SamplingValue;
	uint8_t *pData = (uint8_t*)(&value);
	ADCValue = pac1932_read_vbus_1();
	SamplingValue = ADCValue;
	SamplingValue *= 32.;
	SamplingValue /= 65536;
    value = SamplingValue;
	for( i = 0; i < 4; i++ )
	{
		usb_msg.read.databuf[i] = pData[i];
	}
	usb_msg.read.datalength = 4;
	return sCMDSuccess;

}
//-----------------------------------------------------------------------------
// Func_CMD_Get_AD7298_Coeff
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Get AD7298 Coeff
//
//-----------------------------------------------------------------------------
uint8_t Func_CMD_Get_AD7298_Coeff (void)
{
	int i;
	int lane;
	uint8_t *pData1;
	uint8_t *pData2;
	lane = usb_msg.write.databuf[0];
	pData1 = (uint8_t*)(&(MCUPer.Rssi_Meas[lane]));
	pData2 = (uint8_t*)(&(MCUPer.Rssi_Real[lane]));
	for( i = 0; i < 12; i++ )
	{
		usb_msg.read.databuf[0x00 + 4*i ] = pData1[0x03 + 4*i ];
		usb_msg.read.databuf[0x01 + 4*i ] = pData1[0x02 + 4*i ];
		usb_msg.read.databuf[0x02 + 4*i ] = pData1[0x01 + 4*i ];
		usb_msg.read.databuf[0x03 + 4*i ] = pData1[0x00 + 4*i ];


		usb_msg.read.databuf[0x30 + 4*i ] = pData2[0x03 + 4*i ];
		usb_msg.read.databuf[0x31 + 4*i ] = pData2[0x02 + 4*i ];
		usb_msg.read.databuf[0x32 + 4*i ] = pData2[0x01 + 4*i ];
		usb_msg.read.databuf[0x33 + 4*i ] = pData2[0x00 + 4*i ];
	}
	usb_msg.read.datalength = 0x20;
	return sCMDSuccess;
}


//-----------------------------------------------------------------------------
// Func_CMD_Set_AD7298_Coeff
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Set AD7298 Coeff
//
//-----------------------------------------------------------------------------
uint8_t Func_CMD_Set_AD7298_Coeff (void)
{
	int i;
	int lane;
	uint8_t *pData1;
	uint8_t *pData2;
	lane = usb_msg.write.databuf[0];
	pData1 = (uint8_t*)(&(MCUPer.Rssi_Meas[lane]));
	pData2 = (uint8_t*)(&(MCUPer.Rssi_Real[lane]));
	for( i = 0; i < 12; i++ )
	{
		pData1[0x00 + 4*i ] = usb_msg.write.databuf[0x01 + 4*i ];
		pData1[0x01 + 4*i ] = usb_msg.write.databuf[0x02 + 4*i ];
		pData1[0x02 + 4*i ] = usb_msg.write.databuf[0x03 + 4*i ];
		pData1[0x03 + 4*i ] = usb_msg.write.databuf[0x04 + 4*i ];


		pData2[0x00 + 4*i ] = usb_msg.write.databuf[0x31 + 4*i ];
		pData2[0x01 + 4*i ] = usb_msg.write.databuf[0x32 + 4*i ];
		pData2[0x02 + 4*i ] = usb_msg.write.databuf[0x33 + 4*i ];
		pData2[0x03 + 4*i ] = usb_msg.write.databuf[0x34 + 4*i ];
	}

	gFlagWriteFlash = 1;
	return sCMDSuccess;
}

//-----------------------------------------------------------------------------
// Func_CMD_Get_Power
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Get Power
//
//-----------------------------------------------------------------------------
uint8_t Func_CMD_Get_Power (void)
{
	int i;
	int lane;
	uint8_t *pData;
	lane = usb_msg.write.databuf[0];
	pData = (uint8_t*)(&(MCUPer.fVAPD_RL[lane]));
	for( i = 0; i < 0x04; i++ )
	{
		usb_msg.read.databuf[i] = pData[i];
	}
	usb_msg.read.datalength = 0x04;
	return sCMDSuccess;
}


//-----------------------------------------------------------------------------
// Func_CMD_Set_Power
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Set Power
//
//-----------------------------------------------------------------------------
uint8_t Func_CMD_Set_Power (void)
{
	int i;
	int lane;
	uint8_t *pData;
	lane = usb_msg.write.databuf[0];
	pData = (uint8_t*)(&(MCUPer.fVAPD_RL[lane]));
	for( i = 0; i < 4; i++ )
	{
		pData[i] = usb_msg.write.databuf[i + 1];
	}

	gFlagWriteFlash = 1;
	return sCMDSuccess;
}







