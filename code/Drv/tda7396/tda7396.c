/*************************************************************************
#    FileName: tda7396.c
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 
#  LastChange: 2014-05-07 08:42:23
*************************************************************************/
/* Includes ------------------------------------------------------------*/
#include "stm32f10x.h"
#include "tda7396.h"
/* Types ---------------------------------------------------------------*/
/* Constants -----------------------------------------------------------*/
/* Define --------------------------------------------------------------*/
#define TDA7396_STANDBY GPIOD
#define TDA7396_STANDBY_Pin GPIO_Pin_13
#define TDA7396_SINXWRONG GPIOE
#define TDA7396_SINXWRONG_Pin GPIO_Pin_11
/* Variables -----------------------------------------------------------*/
/* Functions prototypes ------------------------------------------------*/
/* Functions -----------------------------------------------------------*/

/*
@brief  shut down.
@param  None.
@retval None.
*/
void TDA7396_Close (void)
{
	GPIO_WriteBit (TDA7396_STANDBY, TDA7396_STANDBY_Pin, Bit_SET);
}
/*
@brief  open.
@param  None.
@retval None.
*/
void TDA7396_Open (void)
{
	GPIO_WriteBit (TDA7396_STANDBY, TDA7396_STANDBY_Pin, Bit_RESET);
}
/*
@brief  wrong test.
@param  None.
@retval None.
*/
unsigned char TDA7396_Wrongtest (void)
{
	return (GPIO_ReadInputDataBit (TDA7396_SINXWRONG, TDA7396_SINXWRONG_Pin));
}
/*
@brief  .
@param  None.
@retval None.
*/
void TDA7396_Init (void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOD| RCC_APB2Periph_GPIOE, ENABLE);
	/* SINXSTAND */
	GPIO_InitStructure.GPIO_Pin =  TDA7396_STANDBY_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(TDA7396_STANDBY, &GPIO_InitStructure);
	/* SINX_Wrong */
	GPIO_InitStructure.GPIO_Pin =  TDA7396_SINXWRONG_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(TDA7396_SINXWRONG, &GPIO_InitStructure);
	// Configure EXTI Line11 to generate an interrupt on falling edge 
	EXTI_InitStructure.EXTI_Line = EXTI_Line11;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);		
	TDA7396_Close ();
}
/*********************************END OF FILE****************************/


