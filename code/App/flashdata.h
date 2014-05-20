/*************************************************************************
#    FileName: flashdata.h
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 
#  LastChange: 2014-05-10 09:26:43
*************************************************************************/
/* Define to prevent recursive inclusion -------------------------------*/
#ifndef __FLASHDATA_H
#define __FLASHDATA_H

/* Includes ------------------------------------------------------------*/
#include "stdint.h"
/* Exported types ------------------------------------------------------*/
/* Exported constants --------------------------------------------------*/
/* Exported define -----------------------------------------------------*/
#define FLASH_ADDREND 32*1024 //最后一个地址 不能等于它
#define FLASH_SIZE 32*1024
/* 修正数据存在参数设置数据后面 */
#define FLASH_ADDR_SYSTEST 31*1024 //系统数据起始
									//0 介质损耗
									//1 交流频率
									//2 体积电阻
									//3 加热启动
									//4 测试方式
									//5 空杯电容
/* Exported variables --------------------------------------------------*/
typedef enum{
	EAUTO_WORK,//自动
	EHAND_WORK,//手动
	ECOM_WORK,//通信
	EEMPTY_WORK,//空杯
	ERES_WORK,//电阻
	EEND_WORK,
}CESHIFANGSI_ENUM;//测试方式
typedef enum{
	FRE_50HZ,
	FRE_475_525HZ,
	FRE_45_55HZ,
	FRE_60HZ,
	FRE_575_625HZ,
	FRE_55_65HZ,
	FRE_END,
}JIAOLIUPINLV_ENUM;
typedef enum{
	AC_0V,
	AC_600V,
	AC_700V,
	AC_800V,
	AC_900V,
	AC_1000V,
	AC_1100V,
	AC_1200V,
	AC_1300V,
	AC_1400V,
	AC_1500V,
	AC_1600V,
	AC_1700V,
	AC_1800V,
	AC_1900V,
	AC_2000V,
	AC_2100V,
	AC_2200V,
	AC_2300V,
	AC_2400V,
	AC_2500V,
	AC_END,
}JIEZHISUNHAO_ENUM;
typedef enum{
	TM_OFF,
	TM_50C,
	TM_55C,
	TM_60C,
	TM_65C,
	TM_70C,
	TM_75C,
	TM_80C,
	TM_85C,
	TM_90C,
	TM_95C,
	TM_100C,
	TM_105C,
	TM_110C,
	TM_115C,
	TM_120C,
	TM_125C,
	TM_130C,
	TM_END,
}JIAREQIDONG_ENUM;
typedef enum{
	DC_OFF,
	DC_300V,
	DC_400V,
	DC_500V,
	DC_600V,
	DC_END,
}TIJIDIANZU_ENUM;
/*历史参数设置参数*/
typedef struct{
	volatile int32_t jiezhisunhao;//关 600-2000V
	volatile int32_t jiaoliupinlv;//50hz 47.5/52.5hz 45/55 60 57.5/62.5 55/65
	volatile int32_t tijidianzu;//关 300V 400 500 600
	volatile int32_t jiareqidong;//关 50-130 （5度的加）
	volatile int32_t ceshifangsi;//自动 手动 通信 空杯 电阻
	volatile int32_t kongbeidianrong;//空杯电容 //*100
}HISTORYTEST;
extern HISTORYTEST hisdata;
typedef struct{
	volatile float ac_k;//交流输出系数 变压器输出电压 1000V = setamp(1000/2500*ac_k);
}MODIFY_StructType;
extern MODIFY_StructType modify;
/* Exported functions prototypes ---------------------------------------*/
extern void FD_Init (void);
extern void FD_SetHistoryData (void);
extern void FD_GetHistoryData (void);
extern void FD_Inc_jiezhisunhao (void);
extern void FD_Inc_jiaoliupinlv (void);
extern void FD_Inc_tijidianzu (void);
extern void FD_Inc_jiareqidong (void);
extern void FD_Inc_ceshifangsi (void);
extern void FD_GetHisdataStr_jiezhisunhao (char *str);
extern void FD_GetHisdataStr_jiaoliupinlv (char *str);
extern void FD_GetHisdataStr_tijidianzu (char *str);
extern void FD_GetHisdataStr_jiareqidong (char *str);
extern void FD_GetHisdataStr_ceshifangsi (char *str);
extern void FD_GetHisdataStr_kongbeidianrong (char *str);
extern void FD_GetModifyData(void);
extern void FD_SetModifyData (void);
#endif 
/*********************************END OF FILE****************************/


