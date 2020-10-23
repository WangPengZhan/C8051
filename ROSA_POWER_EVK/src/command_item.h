//-----------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//-----------------------------------------------------------------------------
//
// file name  :       command_item.h
//
// description:       USB command process
//
// Target     :       C8051F34x / C8051F38x
//
// version    :       V100.001
//					  2017/11/16 by roy zhou
//
//-----------------------------------------------------------------------------
#ifndef _COMMAND_ITEM_H_H
#define _COMMAND_ITEM_H_H

#define COMMAND_BUFFER_SIZE       1024

#define COMMANDTYPE_COUNT_MAX     10
#define COMMANDSUB_COUNT_MAX      10

#define NUM_FW_VERSION            4
#define EP_CONTROL_LENGTH         64

#define sCMDSuccess        		  0x00
#define sCMDFailed         		  0x01
#define sCMDDoing                 0x80
#define sCMDUnknownType           0xFF
#define sCMDUnknownId             0xFE

#define NUM_FW_VERSION            4
#define NUM_PIN_STATUS            1
#define NUM_FLOAT_LENGTH          4
#define NUM_C2_DEVICEID           1
#define NUM_C2_REGDATA            1
#define NUM_REG_READ              3
#define NUM_REG_WRITE             4
#define NUM_RETURN_BACK_STATUS    6

// ������ṹ��
typedef struct
{
	// ��ȡ���������ִ������ܺ���
	uint8_t (*pfun)(void);

}CommandItemSub_s;


// ��������ṹ��
typedef struct
{
    // �����¼�����
    uint8_t count;

    // �����¸�������
    CommandItemSub_s item[COMMANDSUB_COUNT_MAX];

}CommandItem_s;


typedef struct {

    uint8_t  cmd_type;
	uint8_t  cmd_id;
	uint16_t cmd_status;
	uint16_t datalength;
	uint8_t  databuf[COMMAND_BUFFER_SIZE];

} command_execmsg_ctrl_t;


// ����������
typedef union udi_command_msg_union{

	command_execmsg_ctrl_t    write;
	command_execmsg_ctrl_t    read;

}udi_command_msg_s;


extern void   USB_Command_Init     (void);
extern bool   USB_Command_Decode   (void);

// ͨ������
extern uint8_t Func_CMD_General_QueryVersion (void);
extern uint8_t Func_CMD_General_GetEVK_ID    (void);
extern uint8_t Func_CMD_General_SetEVK_ID    (void);
extern uint8_t Func_CMD_General_Reboot       (void);

// MCU �Ĵ�������
extern uint8_t Func_CMD_MCU_ReadRegister   (void);
extern uint8_t Func_CMD_MCU_WriteRegister  (void);
extern uint8_t Func_CMD_MCU_SetRegister    (void);
extern uint8_t Func_CMD_MCU_ClearRegister  (void);

// I2C ͨ������
extern uint8_t Func_CMD_I2C_ReadArray      (void);
extern uint8_t Func_CMD_I2C_WriteArray     (void);

// ADC ����
extern uint8_t  Func_CMD_ADC_GetFeature	      (void);
extern uint8_t  Func_CMD_ADC_SetFeature	      (void);
extern uint8_t  Func_CMD_ADC_Read		   	  (void);
extern uint8_t  Func_CMD_ADC_GetSamplingValue (void);

//AD7298 ������
extern uint8_t Func_CMD_AD7298_Read (void);

//SI544 ����
extern uint8_t Func_CMD_SI544_Set(void);
extern uint8_t Func_CMD_SI544_Read(void);

// �ڲ����ƹ���
extern uint8_t  Func_CMD_Ctrl_GetPortMonitor (void);
extern uint8_t  Func_CMD_Ctrl_SetPortMonitor (void);

//PAC1932 ��ȡ
extern uint8_t  Func_CMD_PAC1932_Read(void);
extern uint8_t  Func_CMD_PAC1932_Read_BUS(void);

//AD7298У׼ϵ��
extern uint8_t Func_CMD_Get_AD7298_Coeff(void);
extern uint8_t Func_CMD_Set_AD7298_Coeff(void);

//�⹦�ʶ�д����
extern uint8_t Func_CMD_Get_Power(void);
extern uint8_t Func_CMD_Set_Power(void);


#endif


