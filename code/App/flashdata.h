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
#define FLASH_ADDREND 32*1024 //链€鍚庝竴涓湴鍧€ 涓嶈兘绛変簬瀹?
#define FLASH_SIZE 32*1024
/* 淇鏁版嵁瀛桦湪鍙傛暟璁剧疆鏁版嵁鍚庨溃 */
#define FLASH_ADDR_SYSTEST 31*1024 //绯荤粺鏁版嵁璧峰
									//0 浠嬭川鎹熻€?
									//1 浜ゆ祦棰戠巼
									//2 浣撶Н鐢甸樆
									//3 锷犵儹鍚姩
									//4 娴嬭瘯鏂瑰纺
									//5 绌烘澂鐢靛
/* Exported variables --------------------------------------------------*/
typedef enum{
	EAUTO_WORK,//镊姩
	EHAND_WORK,//镓嫔姩
	ECOM_WORK,//阃氢俊
	EEMPTY_WORK,//绌烘澂
	ERES_WORK,//鐢甸樆
	EEND_WORK,
}CESHIFANGSI_ENUM;//娴嬭瘯鏂瑰纺
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
/* */
typedef struct{
	volatile int32_t jiezhisunhao;//鍏?600-2000V
	volatile int32_t jiaoliupinlv;//50hz 47.5/52.5hz 45/55 60 57.5/62.5 55/65
	volatile int32_t tijidianzu;//鍏?300V 400 500 600
	volatile int32_t jiareqidong;//鍏?50-130 锛?搴︾殑锷狅级
	volatile int32_t ceshifangsi;//镊姩 镓嫔姩 阃氢俊 绌烘澂 鐢甸樆
	volatile int32_t kongbeidianrong;//绌烘澂鐢靛 //*100
}HISTORYTEST;
extern HISTORYTEST hisdata;
typedef struct{
	volatile float ac_k;//产生的交流修正系数 1000V = setamp(1000/2500*ac_k);
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


