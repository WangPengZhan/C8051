//-----------------------------------------------------------------------------
//      Copyright (c) 2017-2018, xy-technology International Co.,Ltd
//-----------------------------------------------------------------------------
//
// file name  :       pin.c
//
// description:       mcu pin define
//
// Target     :       C8051F34x / C8051F38x
//
// version    :       V100.001
//					  2017/11/16 by roy zhou
//
//-----------------------------------------------------------------------------
#ifndef PINS_DEFS_H
#define PINS_DEFS_H

#include <SI_C8051F340_Register_Enums.h>  // SFR declarations
//EN1V8 P0.1
SI_SBIT(Port_EN1V8,SFR_P0,1);

//EN5V P0.2
SI_SBIT(Port_EN5V,SFR_P0,2);

//EN-3V P0.3
SI_SBIT(Port_EN_N_3V,SFR_P0,3);

//EN_VCC3V3M_MON P0.4
SI_SBIT(Port_VCC3V3M_MON,SFR_P0,4);

//EN_3_3V P0.5
SI_SBIT(Port_EN_3_3V,SFR_P0,5);

//APD_ALARM0 P1.3
SI_SBIT(Port_APD_ALARM0,SFR_P1,3);

//APD_ALARM1 P1.4
SI_SBIT(Port_APD_ALARM1,SFR_P1,4);

//APD_ALARM2 P1.7
SI_SBIT(Port_APD_ALARM2,SFR_P1,7);

//APD_ALARM3 P1.6
SI_SBIT(Port_APD_ALARM3,SFR_P1,6);

//RX_LOS P2.0
SI_SBIT(Port_RX_LOS,SFR_P2,0);

//RX_DIS P2.1
SI_SBIT(Port_RX_DIS,SFR_P2,1);

//PWRDN P2.2
SI_SBIT(Port_PWRDN,SFR_P2,2);

//SLOW P2.3
SI_SBIT(Port_SLOW,SFR_P2,3);

//SPI_SCK P2.4
SI_SBIT(Port_SPI_SCK,SFR_P2,4);

//SPI_MISO P2.5
SI_SBIT(Port_SPI_MISO,SFR_P2,5);

//SPI_CS0 P2.6
SI_SBIT(Port_SPI_CS0,SFR_P2,6);

//SPI_MOSI P2.7
SI_SBIT(Port_SPI_MOSI,SFR_P2,7);



//OE P3.0
SI_SBIT(Port_OE,SFR_P3,0);

//I2C_SDA P3.2
SI_SBIT(Port_I2C_SDA,SFR_P3,2);

//I2C_SCL P3.3
SI_SBIT(Port_I2C_SCL,SFR_P3,3);


//HV_EN P3.4
SI_SBIT(Port_HV_EN,SFR_P3,4);

//BWC P3.7
SI_SBIT(Port_BWC,SFR_P3,7);

//Vdiver P4.0
#define	Port_Vdiver		    P4
#define MDIN_Vdiver		    P4MDIN
#define MDOUT_Vdiver	    P4MDOUT
#define Bit_Vdiver		    0

//Tsense_BUSY P4.1
#define	Port_Tsense_BUSY	P4
#define MDIN_Tsense_BUSY	P4MDIN
#define MDOUT_Tsense_BUSY	P4MDOUT
#define Bit_Tsense_BUSY		1

//PD/EST P4.2
#define	Port_PD_EST			P4
#define MDIN_PD_EST			P4MDIN
#define MDOUT_PD_EST		P4MDOUT
#define Bit_PD_EST			2



#endif
