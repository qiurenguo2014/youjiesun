/*************************************************************************
#    FileName: bsp_key.c
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 
#  LastChange: 2014-05-07 16:32:58
*************************************************************************/
/* Includes ------------------------------------------------------------*/
#include "stm32f10x.h"
#include "bsp_key.h"
/* Types ---------------------------------------------------------------*/
/* Constants -----------------------------------------------------------*/
/* Define --------------------------------------------------------------*/
#define KEY_UP GPIOB
#define KEY_UP_Pin GPIO_Pin_4
#define KEY_PAIYOU GPIOE
#define KEY_PAIYOU_Pin GPIO_Pin_8
#define KEY_DOWN GPIOE
#define KEY_DOWN_Pin GPIO_Pin_5
#define KEY_ENTER GPIOB
#define KEY_ENTER_Pin GPIO_Pin_6
#define KEY_BACK GPIOB
#define KEY_BACK_Pin GPIO_Pin_7
/* Variables -----------------------------------------------------------*/
volatile uint8_t vk_msg;
/* Functions prototypes ------------------------------------------------*/
/* Functions -----------------------------------------------------------*/
uint16_t KEY_Listen_allkey (void)
{
	uint16_t data;
	data = GPIO_ReadInputData (GPIOB);
	return data;
}
/*
@brief  1 按下 0 没按.
@param  None.
@retval None.
*/
uint8_t KEY_Listen_DOWN (void)
{
	return GPIO_ReadInputDataBit (KEY_DOWN, KEY_DOWN_Pin);
}

/*
@brief  1 按下 0 没按.
@param  None.
@retval None.
*/
uint8_t KEY_Listen_UP (void)
{
	return GPIO_ReadInputDataBit (KEY_UP, KEY_UP_Pin);
}
/*
@brief  1 按下 0 没按.
@param  None.
@retval None.
*/
uint8_t KEY_Listen_PAIYOU (void)
{
	return GPIO_ReadInputDataBit (KEY_PAIYOU, KEY_PAIYOU_Pin);
}
/*
@brief  1 按下 0 没按.
@param  None.
@retval None.
*/
uint8_t KEY_Listen_ENTER (void)
{
	return GPIO_ReadInputDataBit (KEY_ENTER, KEY_ENTER_Pin);
}
/*
@brief  1 按下 0 没按.
@param  None.
@retval None.
*/
uint8_t KEY_Listen_BACK (void)
{
	return GPIO_ReadInputDataBit (KEY_BACK, KEY_BACK_Pin);
}
#include "gui.h"
void KEY_Send_Keymsg (uint8_t VK_MSG)
{	
	vk_msg = VK_MSG;	
}
uint8_t GUI_Get_Keymsg (void)
{
	uint8_t tmp;
	tmp = vk_msg;
	vk_msg = VK_NOKEY;
	return tmp;
}
uint8_t GUI_Get_Keymsg_a (void)
{
	return vk_msg;
}
/*
@brief  按键扫描 放在中断里最好 间隔10ms扫描一次.
@param  None.
@retval None.
*/
#define VK_DOWN_MASK (0X1<<5)
#define VK_UP_MASK (0X1<<4)
#define VK_PAIYOU_MASK (0X1<<4)
#define VK_ENTER_MASK (0X1<<6)
#define VK_BACK_MASK (0X1<<7)
void KEY_Listen_KEY (void)
{
	static uint16_t delay_limit_down = DELAY_VK1;
	static uint16_t delay_limit_back = DELAY_VK1;
	static uint16_t delay_limit_enter = DELAY_VK1;
	static uint16_t delay_limit_up = DELAY_VK1;
	static uint16_t delay_down = 0;
	static uint16_t delay_back = 0;
	static uint16_t delay_enter = 0;
	static uint16_t delay_up = 0;
	uint16_t keymsg;
	keymsg = KEY_Listen_allkey ();
	if (~keymsg&VK_DOWN_MASK){//(_GUI_Listen_Down ()){
		delay_down ++;
	}else{
		delay_down = 0;
		if (delay_limit_down > DELAY_VK1){				//ËÉ¿ªÅÐ¶Ï
//			if(delay_limit_down <= DELAY_VK1+DELAY_VK2){
				KEY_Send_Keymsg(VK_DOWN|VK_LOOSE);
//			}
		}
		delay_limit_down = DELAY_VK1;
	}
	/* ----------- */
	if (~keymsg&VK_BACK_MASK){//(_GUI_Listen_Back ()){
		delay_back ++;
	}else{
		delay_back = 0;
		if (delay_limit_back > DELAY_VK1){
//			if(delay_limit_back <= DELAY_VK1+DELAY_VK2){
				KEY_Send_Keymsg(VK_BACK|VK_LOOSE);		
//			}
		}
		delay_limit_back = DELAY_VK1;
	}
	/* ---------- */
	if (~keymsg&VK_ENTER_MASK){//(_GUI_Listen_Enter ()){
		delay_enter ++;
	}else{
		delay_enter = 0;
		if (delay_limit_enter > DELAY_VK1){
			//if(delay_limit_enter <= DELAY_VK1+DELAY_VK2){
				KEY_Send_Keymsg(VK_ENTER|VK_LOOSE);
			//}
		}
		delay_limit_enter = DELAY_VK1;
	}	
	if (~keymsg&VK_UP_MASK){
		delay_up ++;
	}else{
		delay_up = 0;
		if (delay_limit_up > DELAY_VK1){
			if(delay_limit_up <= DELAY_VK1+DELAY_VK2){
				KEY_Send_Keymsg(VK_UP|VK_LOOSE);
			}
		}
		delay_limit_up = DELAY_VK1;
	}
	
// 	if (~keymsg&VK_PAIYOU_MASK){
// 		delay_paiyou ++;
// 	}else{
// 		delay_paiyou = 0;
// 		if (delay_limit_paiyou > DELAY_VK1){
// 			if(delay_limit_paiyou <= DELAY_VK1+DELAY_VK2){
// 				KEY_Send_Keymsg(VK_PAIYOU|VK_LOOSE);
// 			}
// 		}
// 		delay_limit_paiyou = DELAY_VK1;
// 	}	
	/* ---------- */
	if (delay_down > delay_limit_down){
		if (delay_limit_down == DELAY_VK1){
			delay_limit_down += DELAY_VK2;
			KEY_Send_Keymsg(VK_DOWN);
		}else if (delay_limit_down >= DELAY_VK2+DELAY_VK1){
			delay_limit_down += DELAY_VK3;
			KEY_Send_Keymsg(VK_DOWN|VK_CONT);
		}
	}
	if (delay_enter > delay_limit_enter){
		if (delay_limit_enter == DELAY_VK1){
			delay_limit_enter += DELAY_VK2;
			KEY_Send_Keymsg(VK_ENTER);
		}else if (delay_limit_enter >= DELAY_VK2+DELAY_VK1){
			delay_limit_enter += DELAY_VK3;
			KEY_Send_Keymsg(VK_ENTER|VK_CONT);
		}
	}
	if (delay_back > delay_limit_back){
		if (delay_limit_back == DELAY_VK1){
			delay_limit_back += DELAY_VK2;
			KEY_Send_Keymsg(VK_BACK);
		}else if (delay_limit_back >= DELAY_VK2+DELAY_VK1){
			delay_limit_back += DELAY_VK3;
			KEY_Send_Keymsg(VK_BACK|VK_CONT);
		}
	}
	if (delay_up > delay_limit_up){
		if (delay_limit_up == DELAY_VK1){
			delay_limit_up += DELAY_VK2;
			KEY_Send_Keymsg(VK_UP);
		}else if (delay_limit_up >= DELAY_VK2+DELAY_VK1){
			delay_limit_up += DELAY_VK3;
			KEY_Send_Keymsg(VK_UP|VK_CONT);
		}
	}
// 	if (delay_paiyou > delay_limit_paiyou){
// 		if (delay_limit_paiyou == DELAY_VK1){
// 			delay_limit_paiyou += DELAY_VK2;
// 			KEY_Send_Keymsg(VK_PAIYOU);
// 		}else if (delay_limit_paiyou >= DELAY_VK2+DELAY_VK1){
// 			delay_limit_paiyou += DELAY_VK3;
// 			KEY_Send_Keymsg(VK_PAIYOU|VK_CONT);
// 		}
// 	}
	/* ------------------- */	
}
/*
@brief  .
@param  None.
@retval None.
*/
void KEY_Configuration (void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE, ENABLE);
	/* Configure IO connected to IIC*********************/
	GPIO_InitStructure.GPIO_Pin = KEY_PAIYOU_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(KEY_PAIYOU, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = KEY_UP_Pin;
	GPIO_Init(KEY_UP, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = KEY_DOWN_Pin;
	GPIO_Init(KEY_DOWN, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = KEY_ENTER_Pin;
	GPIO_Init(KEY_ENTER, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = KEY_BACK_Pin;
	GPIO_Init(KEY_BACK, &GPIO_InitStructure);	
}
/*********************************END OF FILE****************************/

