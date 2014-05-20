/*************************************************************************
#    FileName: bsp_systick.c
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 
#  LastChange: 2014-05-09 11:21:53
*************************************************************************/
/* Includes ------------------------------------------------------------*/
#include <stdio.h>
#include "stm32f10x.h"
#include "bsp_systick.h"
/* Types ---------------------------------------------------------------*/
/* Constants -----------------------------------------------------------*/
/* Define --------------------------------------------------------------*/
/* Variables -----------------------------------------------------------*/
volatile long jiffies=0;
/* Functions prototypes ------------------------------------------------*/
/* Functions -----------------------------------------------------------*/
/*
@brief  systick.
@param  None.
@retval None.
*/
void SYSTICK_Configuration (void)
{
	jiffies = 0;
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	if(SysTick_Config(720000) == 1){//10ms
		printf("\r\nsystick fail");
		while(1);
	}	
}
void SYSTICK_Delay10ms(long i)
{
	long jif;
	jif = i+jiffies;
	while(jif>jiffies);
}
/*********************************END OF FILE****************************/


