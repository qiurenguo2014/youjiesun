#ifndef MY_INITTASK_H
#define MY_INITTASK_H

#include "stm32f10x.h"
#include "bsp_usart.h"

void My_InitTask(void); 
   
void RCC_Configuration(void);
void NVIC_Configuration(void);
void SysTick_Configuration(void);
void BSP_BeepClose (void);
void BSP_BeepOpen (void);

#endif /* MY_INITTASK_H */
















