/*************************************************************************
#    FileName: bps_gpio.c
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 
#  LastChange: 2014-05-06 16:50:26
*************************************************************************/
/* Includes ------------------------------------------------------------*/
#include "stm32f10x.h"
/* Types ---------------------------------------------------------------*/
/* Constants -----------------------------------------------------------*/
/* Define --------------------------------------------------------------*/
/* Variables -----------------------------------------------------------*/
/* Functions prototypes ------------------------------------------------*/
/* Functions -----------------------------------------------------------*/
/*
@brief  .
@param  None.
@retval None.
*/
void RELAY_Configuration (void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_WriteBit (GPIOC, GPIO_Pin_7, SET);
}
/*********************************END OF FILE****************************/


