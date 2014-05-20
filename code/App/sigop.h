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
	double tgc;//����
	double Cx;//������
	double Uac;//������ѹ
	double Er;//���ʳ���
	double Udc;//ֱ����ѹ
	double Rp;//���������
	double T_oil;//����
}SIGOP_DataStructType;//�������ݽ��
typedef struct{
	SIGOP_DataStructType data;
	float prefre;//��ǰDA�����Ƶ��
	float preacvol;//��ǰDA����ķ�ֵ
}SIGOP_StructType;
extern SIGOP_StructType sig;
/* Exported constants --------------------------------------------------*/
/* Exported define -----------------------------------------------------*/
/* Exported variables --------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------*/
#endif 
/*********************************END OF FILE****************************/


