/*************************************************************************
#    FileName: ad7367.h
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 
#  LastChange: 2014-05-05 17:14:05
*************************************************************************/
/* Define to prevent recursive inclusion -------------------------------*/
#ifndef __AD7367_H
#define __AD7367_H

/* Includes ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------*/
/* Exported constants --------------------------------------------------*/
/* Exported define -----------------------------------------------------*/
#define AD7367_BUSY GPIOB
#define AD7367_BUSY_Pin GPIO_Pin_11
#define AD7367_ADDR GPIOB
#define AD7367_ADDR_Pin GPIO_Pin_10
/* Exported variables --------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------*/
extern void AD7367_Init (void);
#endif 
/*********************************END OF FILE****************************/


