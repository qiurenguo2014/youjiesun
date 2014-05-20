/*************************************************************************
#    FileName: bsp_dac.h
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 
#  LastChange: 2014-05-12 16:06:35
*************************************************************************/
/* Define to prevent recursive inclusion -------------------------------*/
#ifndef __BSP_DAC_H
#define __BSP_DAC_H
/* Includes ------------------------------------------------------------*/
#include <stdint.h>
/* Exported types ------------------------------------------------------*/
/* Exported constants --------------------------------------------------*/
/* Exported define -----------------------------------------------------*/
#define VCLOSE_IO GPIOB
#define VCLOSE_IO_Pin GPIO_Pin_13
#define HDC_12VOUT GPIOB
#define HDC_12VOUT_Pin GPIO_Pin_12
/* Exported variables --------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------*/
extern void DA_Configuration (void);
extern void DA_SwitchAC (void);
extern void DA_SwitchDC (void);
extern void DA_CloseDCMODEL (void);
extern void DA_OpenDCMODEL (void);
extern void DA_StartACoutput (void);
extern void DA_StopACoutput (void);
extern void DA_SetFre (float hz);
extern void DA_SetAmp (float amp);
#endif 
/*********************************END OF FILE****************************/


