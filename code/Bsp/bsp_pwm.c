/*************************************************************************
#    FileName: bsp_pwm.c
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 
#  LastChange: 2014-05-06 09:45:19
*************************************************************************/
/* Includes ------------------------------------------------------------*/
#include "stm32f10x.h"
#include "bsp_pwm.h"
/* Types ---------------------------------------------------------------*/
/* Constants -----------------------------------------------------------*/
/* Define --------------------------------------------------------------*/
/* Variables -----------------------------------------------------------*/
/* Functions prototypes ------------------------------------------------*/
/* Functions -----------------------------------------------------------*/
/*
@brief  閲囬泦棰戠巼 娓╁害浣跨敤.
@param  None.
@retval None.
*/
void PWM_Configuration (void)
{
	TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM3,ENABLE);
	/*TIM1_CH3N*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING; 
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
 	TIM_TimeBaseStructure.TIM_Period = 0xffff;     //锻ㄦ湡0锝濬FFF
 	TIM_TimeBaseStructure.TIM_Prescaler = 499;       //镞堕挓鍒嗛 499+1
 	TIM_TimeBaseStructure.TIM_ClockDivision = 0;   //镞堕挓鍒嗗壊
 	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//妯″纺
 	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);//鍩烘湰鍒濆鍖?
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x0;
	TIM_PWMIConfig(TIM3, &TIM_ICInitStructure);
	/* Select the TIM3 Input Trigger: TI2FP2 */
	TIM_SelectInputTrigger(TIM3, TIM_TS_TI2FP2);
	/* Select the slave Mode: Reset Mode */
	TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Reset);
	/* Enable the Master/Slave Mode */
	TIM_SelectMasterSlaveMode(TIM3, TIM_MasterSlaveMode_Enable);
	//TIM_ITConfig(TIM3, TIM_IT_CC2, ENABLE);
	/* TIM enable counter */
	TIM_Cmd(TIM3, ENABLE);
}
/* 棰戠巼璁＄畻: 72000000.0/500(鍒嗛链?499+1)/value */
uint16_t PWM_GetInputValue (void)
{
	return TIM_GetCapture2 (TIM3);
}
/*
@brief  鎸囩ず鐏疨WM.
@param  None.
@retval None.
*/

void PWMT_OpenOutputs (void)
{
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}
void PWMT_CloseOutputs (void)
{
	TIM_CtrlPWMOutputs(TIM1, DISABLE);
}
void PWMT_OpenUptemp (void)
{
	GPIO_WriteBit(LED_TEMPUP, LED_TEMPUP_Pin, Bit_SET);
}
void PWMT_CloseUptemp (void)
{
	GPIO_WriteBit(LED_TEMPUP, LED_TEMPUP_Pin, Bit_RESET);
}
void PWMT_OpenDowntemp (void)
{
	GPIO_WriteBit(LED_TEMPDOWN, LED_TEMPDOWN_Pin, Bit_SET);
}
void PWMT_CloseDowntemp (void)
{
	GPIO_WriteBit(LED_TEMPDOWN, LED_TEMPDOWN_Pin, Bit_RESET);
}
void PWMT_Configuration (void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOB
				|RCC_APB2Periph_TIM1,ENABLE);
	/* Configure IO connected to IIC*********************/
	GPIO_InitStructure.GPIO_Pin = LED_TEMPUP_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(LED_TEMPUP, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = LED_TEMPDOWN_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(LED_TEMPDOWN, &GPIO_InitStructure);
	
	PWMT_CloseDowntemp ();
	PWMT_CloseUptemp ();
	
	/*TIM1_CH1*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP; 
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	TIM_BaseInitStructure.TIM_Period = 10000-1;
	TIM_BaseInitStructure.TIM_Prescaler = 0;//72M/Pre *per 
	TIM_BaseInitStructure.TIM_ClockDivision = 0;
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_BaseInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM1, &TIM_BaseInitStructure);
	//鍚敤ARR镄勫奖瀛愬瘎瀛桦櫒锛堢洿鍒颁骇鐢熸洿鏂颁簨浠舵墠镟存敼璁剧疆锛?
	TIM_ARRPreloadConfig(TIM1, ENABLE);	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    TIM_OCInitStructure.TIM_Pulse = 5000;
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);
    //鍚敤CCR1瀵勫瓨鍣ㄧ殑褰卞瓙瀵勫瓨鍣纸鐩村埌浜х敓镟存柊浜嬩欢镓嶆洿鏀硅缃级
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	//TIM1寮€鍚?
    TIM_Cmd(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}
/* 杩囨俯鍜岃绷娴佷缭鎶ゅ垵濮嫔寲 */
void OVETI_Configuration (void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;
	GPIO_InitStructure.GPIO_Pin =  OVERI_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(OVERI, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  OVERTEMP_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(OVERTEMP, &GPIO_InitStructure);
	// Configure EXTI Line14 to generate an interrupt on falling edge 
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	
}
/* 棰戠巼璁＄畻: 72000000.0/500(鍒嗛链?499+1)/value */
uint16_t HN220V_GetInputValue (void)
{
	return TIM_GetCapture1 (TIM4);
}
/* 宸ラ棰戠巼娴嬮噺 */
void HN220V_Configuration(void)
{
	TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOD| RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM4,ENABLE);
	/*TIM1_CH3N*/
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING; 
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_PinRemapConfig(GPIO_Remap_TIM4,ENABLE);
 	TIM_TimeBaseStructure.TIM_Period = 0xffff;		//锻ㄦ湡0锝濬FFF
 	TIM_TimeBaseStructure.TIM_Prescaler = 29;		//镞堕挓鍒嗛 29+1
 	TIM_TimeBaseStructure.TIM_ClockDivision = 0;	//镞堕挓鍒嗗壊
 	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//妯″纺
 	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);	//鍩烘湰鍒濆鍖?
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0x0;
	
	TIM_ICInit(TIM4, &TIM_ICInitStructure);
	/* Select the TIM4 Input Trigger: TI1FP1 */
	TIM_SelectInputTrigger(TIM4, TIM_TS_TI1FP1);
	/* Select the slave Mode: Reset Mode */
	TIM_SelectSlaveMode(TIM4, TIM_SlaveMode_Reset);
	/* Enable the Master/Slave Mode */
	TIM_SelectMasterSlaveMode(TIM4, TIM_MasterSlaveMode_Enable);
	/* TIM enable counter */
	TIM_Cmd(TIM4, ENABLE);
}
/*********************************END OF FILE****************************/


