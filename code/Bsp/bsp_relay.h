/*************************************************************************
#    FileName: bps_gpio.h
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 
#  LastChange: 2014-05-06 16:50:33
*************************************************************************/
/* Define to prevent recursive inclusion -------------------------------*/
#ifndef __BSP_GPIO_H
#define __BSP_GPIO_H

/* Includes ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------*/
/* Exported constants --------------------------------------------------*/
/* Exported define -----------------------------------------------------*/
#define RL_RCC (RCC_APB2Periph_GPIOC| RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE |RCC_APB2Periph_GPIOD)

#define RL_JC_IO GPIOC
#define RL_JC_IO_Pin GPIO_Pin_7

#define RL_RELAY3 GPIOB
#define RL_RELAY3_Pin GPIO_Pin_15

#define RL_HOTRELAY1 GPIOD
#define RL_HOTRELAY1_Pin GPIO_Pin_10

#define RL_RELAY2 GPIOE
#define RL_RELAY2_Pin GPIO_Pin_15

#define RL_HACRELAY GPIOE
#define RL_HACRELAY_Pin GPIO_Pin_14

#define RL_OILRELAY GPIOE
#define RL_OILRELAY_Pin GPIO_Pin_13

#define RL_CHIRELAY GPIOE
#define RL_CHIRELAY_Pin GPIO_Pin_12

#define RL_HOTPOWER GPIOD
#define RL_HOTPOWER_Pin GPIO_Pin_11

/* Exported variables --------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------*/
extern void RL_Configuration (void);
extern void RL_Active_JCIO (void);
extern void RL_nActive_JCIO (void);
extern void RL_Active_HOTRELAY1 (void);
extern void RL_nActive_HOTRELAY1 (void);
extern void RL_nActive_HACRELAY (void);
extern void RL_Active_HACRELAY (void);
extern void RL_Active_OILRELAY (void);
#endif 
/*********************************END OF FILE****************************/


