/*************************************************************************
#    FileName: commu.h
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 
#  LastChange: 2014-05-17 16:56:26
*************************************************************************/
/* Define to prevent recursive inclusion -------------------------------*/
#ifndef __COMMU_H
#define __COMMU_H

/* Includes ------------------------------------------------------------*/
#include <stdint.h>
/* Exported types ------------------------------------------------------*/
#define COM_QIZHI1 0XAA
#define COM_QIZHI2 0X55
#define COM_MAINPCB 0X00
#define COM_SLPCB 0X01
typedef enum{
EstartTg_main,
EstartR_main,
EstartV_main,
EstartX_main,
Estop_main,
Emodifyin_main,
Emodifyout_main,
ECAL_main,
ERelay_main,
}COM_CMD_TYPE;
typedef enum{
	QIZHI1,//
	QIZHI2,
	MAINPCB,//
	SLPCB,//
	SIZE,//
	CMD,//
	DATAS,//
}COM_TYPE;//
typedef struct{
	uint32_t status;//
	uint8_t count;//
	uint8_t byte[0xff];
}DATA_StructType;
extern DATA_StructType recdata;
extern DATA_StructType senddata;
/* Exported constants --------------------------------------------------*/
/* Exported define -----------------------------------------------------*/
#define COM_STTS_SUCCESS (0X1<<0)
/* Exported variables --------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------*/
extern void CM_Init (void);
extern void CM_ReceiveData(uint8_t ch);
#endif 
/*********************************END OF FILE****************************/


