/*************************************************************************
#    FileName: bsp_pwm.h
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 
#  LastChange: 2014-05-06 09:45:27
*************************************************************************/
/* Define to prevent recursive inclusion -------------------------------*/
#ifndef __BSP_PWM_H
#define __BSP_PWM_H
/* Includes ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------*/
/* Exported constants --------------------------------------------------*/
/* Exported define -----------------------------------------------------*/
#define LED_TEMPUP GPIOB
#define LED_TEMPUP_Pin GPIO_Pin_9
#define LED_TEMPDOWN GPIOB
#define LED_TEMPDOWN_Pin GPIO_Pin_8
#define OVERTEMP GPIOD
#define OVERTEMP_Pin GPIO_Pin_14
#define OVERI GPIOB
#define OVERI_Pin GPIO_Pin_14
/* Exported variables --------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------*/
extern void PWM_Configuration (void);
extern void PWMT_Configuration (void);
extern void HN220V_Configuration(void);
extern void OVETI_Configuration (void);
#endif 
/*********************************END OF FILE****************************/


