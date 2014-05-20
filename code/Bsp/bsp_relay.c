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
#include "bsp_relay.h"
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
void RL_Configuration (void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RL_RCC, ENABLE);
	GPIO_InitStructure.GPIO_Pin =  RL_JC_IO_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(RL_JC_IO, &GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin =  RL_RELAY3_Pin;
	GPIO_Init(RL_RELAY3, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  RL_HOTRELAY1_Pin;
	GPIO_Init(RL_HOTRELAY1, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  RL_RELAY2_Pin;
	GPIO_Init(RL_RELAY2, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  RL_HACRELAY_Pin;
	GPIO_Init(RL_HACRELAY, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  RL_OILRELAY_Pin;
	GPIO_Init(RL_OILRELAY, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  RL_CHIRELAY_Pin;
	GPIO_Init(RL_CHIRELAY, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =  RL_HOTPOWER_Pin;
	GPIO_Init(RL_HOTPOWER, &GPIO_InitStructure);
}
void RL_Active_JCIO (void)
{
	GPIO_WriteBit (RL_JC_IO, RL_JC_IO_Pin, Bit_SET);
}
void RL_nActive_JCIO (void)
{
	GPIO_WriteBit (RL_JC_IO, RL_JC_IO_Pin, Bit_RESET);
}
void RL_Active_RELAY3 (void)
{
	GPIO_WriteBit (RL_RELAY3, RL_RELAY3_Pin, Bit_SET);
}
void RL_nActive_RELAY3 (void)
{
	GPIO_WriteBit (RL_RELAY3, RL_RELAY3_Pin, Bit_RESET);
}
/**/
void RL_Active_HOTRELAY1 (void)
{
	GPIO_WriteBit (RL_HOTRELAY1, RL_HOTRELAY1_Pin, Bit_SET);
}
void RL_nActive_HOTRELAY1 (void)
{
	GPIO_WriteBit (RL_HOTRELAY1, RL_HOTRELAY1_Pin, Bit_RESET);
}

void RL_Active_RELAY2 (void)
{
	GPIO_WriteBit (RL_RELAY2, RL_RELAY2_Pin, Bit_SET);
}
void RL_nActive_RELAY2 (void)
{
	GPIO_WriteBit (RL_RELAY2, RL_RELAY2_Pin, Bit_RESET);
}
/*TDA7396输出继电器 动作，与2000V变压器*/
void RL_Active_HACRELAY (void)
{
	GPIO_WriteBit (RL_HACRELAY, RL_HACRELAY_Pin, Bit_SET);
}
void RL_nActive_HACRELAY (void)
{
	GPIO_WriteBit (RL_HACRELAY, RL_HACRELAY_Pin, Bit_RESET);
}
/*油*/
void RL_Active_OILRELAY (void)
{
	GPIO_WriteBit (RL_OILRELAY, RL_OILRELAY_Pin, Bit_SET);
}
void RL_nActive_OILRELAY (void)
{
	GPIO_WriteBit (RL_OILRELAY, RL_OILRELAY_Pin, Bit_RESET);
}
/*磁*/
void RL_Active_CHIRELAY (void)
{
	GPIO_WriteBit (RL_CHIRELAY, RL_CHIRELAY_Pin, Bit_SET);
}
void RL_nActive_CHIRELAY (void)
{
	GPIO_WriteBit (RL_CHIRELAY, RL_CHIRELAY_Pin, Bit_RESET);
}
/* 加热 */
void RL_Active_HOTPOWER (void)
{
	GPIO_WriteBit (RL_HOTPOWER, RL_HOTPOWER_Pin, Bit_SET);
}
void RL_nActive_HOTPOWER (void)
{
	GPIO_WriteBit (RL_HOTPOWER, RL_HOTPOWER_Pin, Bit_RESET);
}
/*********************************END OF FILE****************************/


