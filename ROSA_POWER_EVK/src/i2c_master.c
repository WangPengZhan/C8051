//-----------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//-----------------------------------------------------------------------------
//
// file name  :       function.c
//
// description:       I2C Master Driver
//
// Target     :       C8051F34x / C8051F38x
//
// version    :       V100.001
//					  2017/11/16 by roy zhou
//
//-----------------------------------------------------------------------------
#include "include.h"

//-----------------------------------------------------------------------------
// I2C_Master_start
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     Send I2C Start signal
//
//-----------------------------------------------------------------------------
uint8_t I2C_Master_start(void)
{
	// ����SCL SDA�Ĳ�ͬ��ʼ״̬����SCL SDA����������Ϊ1��׼���ã����������STOP��״̬
	if ( Get_SCL() == 1 )
	{
		if ( Get_SDA() == 0 )
		{
			SCL_L();
			delay_us_timer1(Rise_Time_Delay);
			SDA_HIZ();
			delay_us_timer1(Rise_Time_Delay);
			SCL_HIZ();
		}
	}
	else
	{
		if ( Get_SDA() == 1 ) // ʱ����Ϊ�ͣ�������Ϊ��
		{
			SCL_HIZ();
		}
		else // ʱ����Ϊ�ͣ�������Ϊ��
		{
			SDA_HIZ();
			delay_us_timer1(Rise_Time_Delay);
			SCL_HIZ();
		}
	}

	delay_us_timer1(Rise_Time_Delay);

	if (( Get_SCL() == 1 ) && ( Get_SDA() == 1 ))
	{
		delay_us_timer1(I2C_Master_HoldTime);
		SDA_L();
		delay_us_timer1(I2C_Master_HoldTime);
		SCL_L();
		delay_us_timer1(I2C_Master_Delay);  // Ϊ�˱���SCLΪ�͵�ƽ��ʱ��ԼΪ������

		return 0;
	}

	return 1;
}



//-----------------------------------------------------------------------------
// I2C_Master_stop
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     Send I2C Stop signal
//
//-----------------------------------------------------------------------------
uint8_t I2C_Master_stop(void)
{
	// ����SCL SDA�Ĳ�ͬ��ʼ״̬����SCL=1 SDA=0��ͬʱ�������STOP��״̬
	if ( Get_SCL() == 0 )
	{
		if ( Get_SDA() == 0 ) // SCL=0 SDA=0
		{
			SCL_HIZ();
		}
		else // SCL=0 SDA=1
		{
			SDA_L();
			delay_us_timer1(Rise_Time_Delay);
			SCL_HIZ();
		}
	}
	else
	{
		if ( Get_SDA() == 1 ) // SCL=1 SDA=1
		{
			SCL_L();
			delay_us_timer1(Rise_Time_Delay);
			SDA_L();
			delay_us_timer1(Rise_Time_Delay);
			SCL_HIZ();
		}
	}

	delay_us_timer1(Rise_Time_Delay); // �ȴ�SCL SDA�ȶ�

	if ( ( Get_SCL() == 1 ) && ( Get_SDA() == 0 ) )
	{
		delay_us_timer1(I2C_Master_HoldTime);
		SDA_HIZ();
		delay_us_timer1(I2C_Master_HoldTime);

		if (( Get_SCL() == 1 ) && ( Get_SDA() == 1 ))
	    {
	    	return 0; // SCL SDA��Ϊ�� ����
	    }
	    else
	    {
	       return 1; // SCL SDA�޷��ﵽ��ֹ״̬�������쳣
	    }
	}

	return 1; // SCL SDA�޷��趨Ϊ��ʼ״̬�������쳣
}


//-----------------------------------------------------------------------------
// I2C_Master_bit_out
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    send bit
//
// Configures     Send one bit to I2C slave
//
//-----------------------------------------------------------------------------
uint8_t I2C_Master_bit_out( uint8_t bit_out)
{
	uint8_t timercount;

	SDA_OUT(bit_out);                              // ���һ��bit���ݵ�SDA������

	delay_us_timer1(Rise_Time_Delay);              // Ҫ��ȴ�ʱ�����2us

	if ( Get_SDA() != bit_out )                    // ���SDA�Ƿ���Ŀ��ֵһ�£���һ���򱨴�
	{
		return 1;
	}

	SCL_HIZ();                                     // ����ʱ����

	timercount = SCL_Stretch_Timeout;              // ���ó�ʱ�ȴ�ʱ�䣬ʱ�����ڣ�8

	delay_us_timer1(Rise_Time_Delay);              // Ҫ��ȴ�ʱ�����2us

	while( !Get_SCL() )                            // ���SCL״̬�Ƿ�Ϊ�ߣ���Ϊ����ȴ�����ִ��while��ʱ�����ڣ�3
	{
		delay_us_timer1(I2C_Master_HaftCycle);

		if ( timercount-- == 0 )                    // ����8��I2C��������SCLû�лָ����򱨴�
		{
	         return 1;
		}
	}

	delay_us_timer1( I2C_Master_Delay );            // ��ʱ�����ƴ�������

	SCL_L();                                        // ����SCLʱ����

	delay_us_timer1( I2C_Master_Delay );            // ��ʱ�����ƴ�������

	return 0;                                       // ����ִ����
}


//-----------------------------------------------------------------------------
// I2C_Master_bit_in
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    receive bit
//
// Configures     Receive one bit from I2C slave
//
//-----------------------------------------------------------------------------
uint8_t I2C_Master_bit_in( uint8_t *bit_in)
{
	uint8_t timercount;

	SDA_HIZ();                      	// ��SDA�趨Ϊ����ģʽ

	delay_us_timer1(Rise_Time_Delay); 	// �ȴ�SDA��·�ȶ�

	SCL_HIZ();                      	// ����ʱ����

	timercount = SCL_Stretch_Timeout;   // ���ó�ʱ�ȴ�ʱ�䣬ʱ�����ڣ�8

	delay_us_timer1(Rise_Time_Delay);   // �ȴ�SCL��·�ȶ�

	while( !Get_SCL() )                 // ���SCL״̬�Ƿ�Ϊ�ߣ���Ϊ����ȴ�����ִ��while��ʱ�����ڣ�3
	{
		delay_us_timer1(I2C_Master_HaftCycle);

		if ( timercount-- == 0 )       // ����8��I2C��������SCLû�лָ����򱨴�
		{
			return 1;
		}
	}

	*bit_in = Get_SDA();

	delay_us_timer1( I2C_Master_Delay );

	SCL_L();

	delay_us_timer1( I2C_Master_Delay );

	return 0;
}

//-----------------------------------------------------------------------------
// I2C_Master_byte_out
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    send byte
//
// Configures     Send one byte to I2C slave
//
//-----------------------------------------------------------------------------
uint8_t I2C_Master_byte_out( uint8_t byte_out)
{
	uint8_t   bit_count = 8;
	uint8_t   errorcode;
	uint8_t   ack;

	while (bit_count)
	{
		if ( byte_out & 0x80 )                            // ����һ��bit����1
		{
			if ( I2C_Master_bit_out(1) )
			{
	            return 1;
			}
		}
		else                                              // ����һ��bit����0
		{
			if ( I2C_Master_bit_out(0) )
			{
	            return 1;
			}
		}

		byte_out <<= 1;
		bit_count--;
	}

	errorcode = I2C_Master_bit_in( &ack );
	if (( errorcode == 1 ) || ( ack == 1 ))
	{
		return 2;
	}

	return 0;
}


//-----------------------------------------------------------------------------
// I2C_Master_byte_in
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    receive byte
//
// Configures     Receive one byte from I2C slave
//
//-----------------------------------------------------------------------------
uint8_t I2C_Master_byte_in (uint8_t ack_out, uint8_t *byte_in)
{
	uint8_t bit_count = 8;
	uint8_t bit_in;

	*byte_in  = 0;

	while (bit_count)
	{
		*byte_in = (*byte_in) << 1;

		if ( I2C_Master_bit_in( &bit_in ) ) // ��ȡһ��bit������
		{
	         return 1;
		}

		*byte_in = (*byte_in) | bit_in;
		bit_count--;
	}

	if ( I2C_Master_bit_out(ack_out) )
	{
		return 1;
	}

	return 0;
}


//-----------------------------------------------------------------------------
// I2C_Master_Init
//-----------------------------------------------------------------------------
//
// Return Value:  None
// Parameters:    None
//
// Configures     Initialize I2C Master
//
//-----------------------------------------------------------------------------
uint8_t I2C_Master_Init(void)
{
	SCL_L();
	SDA_L();

	delay_us_timer1(Rise_Time_Delay);

	SDA_HIZ();
	SCL_HIZ();

	delay_us_timer1(Rise_Time_Delay);            // �ȴ�ʱ�����������

	if (( Get_SCL() == 1 ) && ( Get_SDA() == 1 ))
	{
		return 0;                                // ��ʼ���ɹ�
	}

	return 1;                                    // �ܽ�״̬���ԣ���ʼ���쳣
}


//-----------------------------------------------------------------------------
// I2C_Master_read_byte
//-----------------------------------------------------------------------------
//
// Return Value:  0 : Success / 1 : Error
// Parameters:    None
//
// Configures     send one byte registet adress and read one byte data
//
//-----------------------------------------------------------------------------
uint8_t I2C_Master_read_byte ( uint8_t device, uint8_t address, uint8_t *bufPtr )
{
	// ����START�ź�
	if ( I2C_Master_start() )
	{
		I2C_Master_stop();
		return 1;
	}

	// ���豸��ַ����SLA+WѰַ
	if ( I2C_Master_byte_out( (device & 0xFE) ) )
	{
		I2C_Master_stop();
		return 2;
	}

	// д������д����ӵ�ַ
	if ( I2C_Master_byte_out(address) )
	{
	   I2C_Master_stop();
	   return 3;
	}

	// ����RESTART�ź�
	if ( I2C_Master_start() )
	{
		I2C_Master_stop();
		return 4;
	}

	// ���豸��ַ����SLA+RѰַ
	if ( I2C_Master_byte_out( (device | 0x01) ) )
	{
		I2C_Master_stop();
		return 5;
	}

	// ��ȡһ���ֽڵ����ݣ�������NACK
	if ( I2C_Master_byte_in(1, bufPtr) )
	{
		I2C_Master_stop();
		return 6;
	}

	// ����STOP�ź�
	if ( I2C_Master_stop() )
	{
		return 7;
	}

	return 0;
}



//-----------------------------------------------------------------------------
// I2C_Master_write_byte
//-----------------------------------------------------------------------------
//
// Return Value:  0 : Success / 1 : Error
// Parameters:    None
//
// Configures     send one byte registet adress and write one byte data
//
//-----------------------------------------------------------------------------
uint8_t I2C_Master_write_byte ( uint8_t device, uint8_t address, uint8_t buf )
{
	// ����START�ź�
	if ( I2C_Master_start() )
	{
		I2C_Master_stop();
		return 1;
	}

	// ���豸��ַ����SLA+WѰַ
	if ( I2C_Master_byte_out( (device & 0xFE) ) )
	{
		I2C_Master_stop();
		return 2;
	}

	// д������д����ӵ�ַ
	if ( I2C_Master_byte_out(address) )
	{
		I2C_Master_stop();
		return 3;
	}

	// д������
	if ( I2C_Master_byte_out(buf) )
	{
		I2C_Master_stop();
		return 4;
	}

	// ����STOP�ź�
	if ( I2C_Master_stop() )
	{
		return 5;
	}

	return 0;
}



//-----------------------------------------------------------------------------
// I2C_Master_readBytes
//-----------------------------------------------------------------------------
//
// Return Value:  0 : Success / 1 : Error
// Parameters:    None
//
// Configures     send one byte registet adress and read (length) bytes data
//
//-----------------------------------------------------------------------------
uint8_t I2C_Master_readBytes( uint8_t device, uint8_t address, uint16_t length, uint8_t *bufPtr )
{
	uint16_t i;

   // ����START�ź�
   if ( I2C_Master_start() )
   {
      I2C_Master_stop();
      return 1;
   }

   // ���豸��ַ����SLA+WѰַ
   if ( I2C_Master_byte_out( (device & 0xFE) ) )
   {
      I2C_Master_stop();
      return 2;
   }

   // д������д����ӵ�ַ
   if ( I2C_Master_byte_out(address) )
   {
      I2C_Master_stop();
      return 3;
   }

   // ����RESTART�ź�
   if ( I2C_Master_start() )
   {
      I2C_Master_stop();
      return 4;
   }

   // ���豸��ַ����SLA+RѰַ
   if ( I2C_Master_byte_out( (device | 0x01) ) )
   {
      I2C_Master_stop();
      return 5;
   }


   for ( i = 0; i < length; i++ )
   {
      if ( I2C_Master_byte_in((i==(length-1))?1:0, &bufPtr[i]) )
      {
         I2C_Master_stop();
         return 6;
      }
   }

   // ����STOP�ź�
   if ( I2C_Master_stop() )
   {
      return 7;
   }

   return 0 ;
}


//-----------------------------------------------------------------------------
// I2C_Master_writeBytes
//-----------------------------------------------------------------------------
//
// Return Value:  0 : Success / 1 : Error
// Parameters:    None
//
// Configures     send one byte registet adress and write (length) bytes data
//
//-----------------------------------------------------------------------------
uint8_t I2C_Master_writeBytes( uint8_t device, uint8_t address, uint16_t length, uint8_t *bufPtr )
{
	uint16_t i;

   // ����START�ź�
   if ( I2C_Master_start() )
   {
      I2C_Master_stop();
      return 1;
   }

   // ���豸��ַ����SLA+WѰַ
   if ( I2C_Master_byte_out( (device & 0xFE) ) )
   {
      I2C_Master_stop();
      return 2;
   }

   // д������д����ӵ�ַ
   if ( I2C_Master_byte_out(address) )
   {
      I2C_Master_stop();
      return 3;
   }

   for ( i = 0; i < length; i++ )
   {
      if ( I2C_Master_byte_out(bufPtr[i]) )
      {
         I2C_Master_stop();
         return 4;
      }
   }

   // ����STOP�ź�
   if ( I2C_Master_stop() )
   {
       return 5;
   }

   return 0;
}


//-----------------------------------------------------------------------------
// I2C_Master_read_word
//-----------------------------------------------------------------------------
//
// Return Value:  0 : Success / 1 : Error
// Parameters:    None
//
// Configures     send one byte registet adress and read one word data
//
//-----------------------------------------------------------------------------
uint8_t I2C_Master_read_word( uint8_t device, uint8_t address,  uint16_t *bufPtr )
{
	uint8_t buf_h,buf_l;

	// ����START�ź�
	if ( I2C_Master_start() )
	{
		I2C_Master_stop();
		return 1;
	}

	// ���豸��ַ����SLA+WѰַ
	if ( I2C_Master_byte_out( (device & 0xFE) ) )
	{
		I2C_Master_stop();
		return 2;
	}

	// д������д����ӵ�ַ
	if ( I2C_Master_byte_out(address) )
	{
		I2C_Master_stop();
		return 3;
	}

	// ����RESTART�ź�
	if ( I2C_Master_start() )
	{
		I2C_Master_stop();
		return 4;
	}

	// ���豸��ַ����SLA+RѰַ
	if ( I2C_Master_byte_out( (device | 0x01) ) )
	{
		I2C_Master_stop();
		return 5;
	}

	// ��ȡһ���ֽڵ����ݣ�������ACK
	if ( I2C_Master_byte_in(1, &buf_h) )
	{
		I2C_Master_stop();
		return 6;
	}

	// ��ȡһ���ֽڵ����ݣ�������NACK
	if ( I2C_Master_byte_in(0, &buf_l) )
	{
		I2C_Master_stop();
		return 7;
	}

	// ����STOP�ź�
	if ( I2C_Master_stop() )
	{
		return 8;
	}

	*bufPtr = ((uint16_t)buf_h << 8) | buf_l;

	return 0;
}


//-----------------------------------------------------------------------------
// I2C_Master_write_word
//-----------------------------------------------------------------------------
//
// Return Value:  0 : Success / 1 : Error
// Parameters:    None
//
// Configures     send one byte registet adress and write one word data
//
//-----------------------------------------------------------------------------
uint8_t I2C_Master_write_word (uint8_t device, uint8_t address, uint16_t buf )
{
	// ����START�ź�
	if ( I2C_Master_start() )
	{
		I2C_Master_stop();
		return 1;
	}

	// ���豸��ַ����SLA+WѰַ
	if ( I2C_Master_byte_out( (device & 0xFE) ) )
	{
		I2C_Master_stop();
		return 2;
	}

	// д������д����ӵ�ַ
	if ( I2C_Master_byte_out(address) )
	{
		I2C_Master_stop();
		return 3;
	}

	// д������
	if ( I2C_Master_byte_out((uint8_t)(buf >> 8)) )
	{
		I2C_Master_stop();
		return 4;
	}

	// д������
	if ( I2C_Master_byte_out((uint8_t)(buf >> 0)) )
	{
		I2C_Master_stop();
		return 5;
	}

	// ����STOP�ź�
	if ( I2C_Master_stop() )
	{
		return 6;
	}

	return 0;
}

