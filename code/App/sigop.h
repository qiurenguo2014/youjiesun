/*************************************************************************
#    FileName: SIGOP.H
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 
#  LastChange: 2014-05-13 10:51:00
*************************************************************************/
/* Define to prevent recursive inclusion -------------------------------*/
#ifndef __SIGOP_H
#define __SIGOP_H

/* Includes ------------------------------------------------------------*/
#include <stdint.h>
/* Exported types ------------------------------------------------------*/
typedef struct{
	double tgc;//介损
	double Cx;//电容量
	double Uac;//交流电压
	double Er;//介质常数
	double Udc;//直流电压
	double Rp;//体积电阻率
	double T_oil;//油温
}SIGOP_DataStructType;//测量数据结果
typedef struct{
	SIGOP_DataStructType data;
	float prefre;//当前DA输出的频率
	float preacvol;//当前DA输出的幅值
}SIGOP_StructType;
extern SIGOP_StructType sig;
/* Exported constants --------------------------------------------------*/
/* Exported define -----------------------------------------------------*/
/* Exported variables --------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------*/
#endif 
/*********************************END OF FILE****************************/


