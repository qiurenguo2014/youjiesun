/*************************************************************************
#    FileName: bsp_systick.h
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 
#  LastChange: 2014-05-09 11:22:02
*************************************************************************/
/* Define to prevent recursive inclusion -------------------------------*/
#ifndef __BSP_SYSTICK_H
#define __BSP_SYSTICK_H

/* Includes ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------*/
/* Exported constants --------------------------------------------------*/
/* Exported define -----------------------------------------------------*/
/* Exported variables --------------------------------------------------*/
extern volatile long jiffies;
/* Exported functions prototypes ---------------------------------------*/
extern void SYSTICK_Configuration (void);
extern void SYSTICK_Delay10ms(long i);
#endif 
/*********************************END OF FILE****************************/


