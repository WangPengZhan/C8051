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
#ifndef I2C_MASTER_H
#define I2C_MASTER_H

#define   I2C_Master_Speed             40  //��λΪKHZ

/****************************************************************************
����SDA�趨�󣬾���һ�������أ������趨һ����������ʱ2.5΢��
������BIT�����У�SDA������ǰһ��Rise_Time_Delay׼����
Ϊ�˲��ζԳƣ�ǰ��һ��BIT������Ϻ���Ҫ����ʱ����һ��Rise_Time_Delay
SCL�ĸߵ�ƽ����ʱ����պ���Ҫʱһ��������
���ں����ĵ��û�����������ִ��Ҳ������һЩʱ�䣬����ʵ�ʵ�SCL�͵�ƽʱ�佫����
�ߵ�ƽʱ��һЩ������ʱ��Ƶ�ʻ���С���趨ʱ��Ŀ�����ʣ�
I2C_Master_HoldTime��ָSTART STOP״̬ʱ��SCL SDA�仯ǰ�ı���ʱ��
*****************************************************************************/
#define   Rise_Time_Delay              2.5
#define   I2C_Master_HoldTime          10
#define   I2C_Master_Delay             ((int)( 500 / I2C_Master_Speed - Rise_Time_Delay ))
#define   I2C_Master_HaftCycle         ((int)( 500 / I2C_Master_Speed ))

#define   SCL_Stretch_Timeout          8                      // SCL����ӳ�8�������ڣ���4������

#define   SCL_HIZ()                    Port_I2C_SCL = 1       // ����SCLΪ����̬
#define   SCL_L()                      Port_I2C_SCL = 0       // ����SCLΪ��
#define   Get_SCL()                    Port_I2C_SCL

#define   SDA_HIZ()                    Port_I2C_SDA = 1       // ����SDAΪ����̬
#define   SDA_L()                      Port_I2C_SDA = 0       // ����SDAΪ��
#define   SDA_OUT(b)                   if(b){SDA_HIZ();}else{SDA_L();}
#define   Get_SDA()                    Port_I2C_SDA

//------------------------- Internal Function ------------------------/
uint8_t I2C_Master_start           (void);
uint8_t I2C_Master_stop            (void);
uint8_t I2C_Master_bit_out         (uint8_t bit_out);       // ����һ��bit
uint8_t I2C_Master_bit_in          (uint8_t *bit_in);       // ����һ��bit
uint8_t I2C_Master_byte_out        (uint8_t byte_out);      // ����һ��Byte
uint8_t I2C_Master_byte_in         (uint8_t ack_out, uint8_t *byte_in); // ����һ��Byte���������Ƿ����ACK

//-------------- ���߳�ʼ�� �Լ� ����ַ���ֽڶ�д����  ----------------------/
extern   uint8_t   I2C_Master_Init         (void);
extern   uint8_t   I2C_Master_write_byte   (uint8_t device, uint8_t address, uint8_t buf);
extern   uint8_t   I2C_Master_read_byte    (uint8_t device, uint8_t address, uint8_t *buf);

extern   uint8_t   I2C_Master_writeBytes   (uint8_t device,
                                            uint8_t address,
                                            uint16_t length,
                                            uint8_t *bufPtr);

extern   uint8_t   I2C_Master_readBytes    (uint8_t device,
                                            uint8_t address,
                                            uint16_t length,
                                            uint8_t *bufPtr);

//----------------------------- ����ַ˫�ֽڶ�д���� ---------------------------------------/
extern   uint8_t   I2C_Master_write_word  (uint8_t device, uint8_t address, uint16_t  buf);
extern   uint8_t   I2C_Master_read_word   (uint8_t device, uint8_t address, uint16_t  *buf);

#endif
