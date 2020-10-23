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

#define   I2C_Master_Speed             40  //单位为KHZ

/****************************************************************************
由于SDA设定后，均有一个上升沿，所以设定一个上升沿延时2.5微秒
由于在BIT传送中，SDA都会提前一个Rise_Time_Delay准备；
为了波形对称，前面一个BIT传送完毕后，需要将延时减少一个Rise_Time_Delay
SCL的高电平保持时间则刚好需要时一个半周期
由于函数的调用或者其他代码执行也会消耗一些时间，所以实际的SCL低电平时间将长于
高电平时间一些，整体时钟频率会略小于设定时钟目标速率；
I2C_Master_HoldTime特指START STOP状态时候，SCL SDA变化前的保持时间
*****************************************************************************/
#define   Rise_Time_Delay              2.5
#define   I2C_Master_HoldTime          10
#define   I2C_Master_Delay             ((int)( 500 / I2C_Master_Speed - Rise_Time_Delay ))
#define   I2C_Master_HaftCycle         ((int)( 500 / I2C_Master_Speed ))

#define   SCL_Stretch_Timeout          8                      // SCL最多延迟8个半周期，即4个周期

#define   SCL_HIZ()                    Port_I2C_SCL = 1       // 设置SCL为高阻态
#define   SCL_L()                      Port_I2C_SCL = 0       // 设置SCL为低
#define   Get_SCL()                    Port_I2C_SCL

#define   SDA_HIZ()                    Port_I2C_SDA = 1       // 设置SDA为高阻态
#define   SDA_L()                      Port_I2C_SDA = 0       // 设置SDA为低
#define   SDA_OUT(b)                   if(b){SDA_HIZ();}else{SDA_L();}
#define   Get_SDA()                    Port_I2C_SDA

//------------------------- Internal Function ------------------------/
uint8_t I2C_Master_start           (void);
uint8_t I2C_Master_stop            (void);
uint8_t I2C_Master_bit_out         (uint8_t bit_out);       // 发送一个bit
uint8_t I2C_Master_bit_in          (uint8_t *bit_in);       // 接收一个bit
uint8_t I2C_Master_byte_out        (uint8_t byte_out);      // 发送一个Byte
uint8_t I2C_Master_byte_in         (uint8_t ack_out, uint8_t *byte_in); // 接收一个Byte，并决定是否给出ACK

//-------------- 总线初始化 以及 单地址单字节读写函数  ----------------------/
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

//----------------------------- 单地址双字节读写函数 ---------------------------------------/
extern   uint8_t   I2C_Master_write_word  (uint8_t device, uint8_t address, uint16_t  buf);
extern   uint8_t   I2C_Master_read_word   (uint8_t device, uint8_t address, uint16_t  *buf);

#endif
