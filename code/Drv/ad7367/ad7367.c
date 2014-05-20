/*************************************************************************
#    FileName: ad7367.c
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 
#  LastChange: 2014-05-05 17:13:35
*************************************************************************/
/* Includes ------------------------------------------------------------*/
#include "stm32f10x.h"
#include "..\..\bsp\bsp_spi.h"
#include "..\..\bsp\bsp_pwm.h"
#include "ad7367.h"
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
unsigned short AD7367_ReadWriteData (unsigned short data)
{
	unsigned short dat;
	while (SPI_I2S_GetFlagStatus (SPI2_MASTER, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI2_MASTER,data);	
	while (SPI_I2S_GetFlagStatus(SPI2_MASTER, SPI_I2S_FLAG_RXNE) == RESET);
	dat = SPI_I2S_ReceiveData (SPI2_MASTER);
	return dat;
}
/*
@brief  cs enable.
@param  None.
@retval None.
*/
void AD7367_ENABLECS (void)
{
	GPIO_WriteBit (SPI2_MASTER_GPIO,SPI2_MASTER_PIN_NSS,Bit_RESET);
}
/*
@brief  cs disable.
@param  None.
@retval None.
*/
void AD7367_DISABLECS (void)
{
	GPIO_WriteBit (SPI2_MASTER_GPIO,SPI2_MASTER_PIN_NSS,Bit_SET);
}
/*
@brief  0:jx  1:jacn.
@param  None.
@retval None.
*/
void AD7367_GetValue (short *val)
{
	unsigned int valb;
	AD7367_ENABLECS ();
	val[0] = AD7367_ReadWriteData (0);
	val[0] = AD7367_ReadWriteData (0);
	valb = val[0];
	valb <<= 16;
	valb |= val[1];
	val[0] >>= 2;
	valb >>= 4;
	val[1] = valb;
	val[1] &= 0x3fff;
	if(val[0] >= 0x2000){
		val[0] += 0xc000;
	}
	if(val[1] >= 0x2000){
		val[1] += 0xc000;
	}
	AD7367_DISABLECS ();
}
/*
@brief  ad7367 init, busy, cnv, addr config.
@param  None.
@retval None.
*/
void AD7367_Init (void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	/* BUSY */
	GPIO_InitStructure.GPIO_Pin = AD7367_BUSY_Pin;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(AD7367_BUSY, &GPIO_InitStructure);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);
	// Configure EXTI Line11 to generate an interrupt on falling edge 
	EXTI_InitStructure.EXTI_Line = EXTI_Line11;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	

	/* ADDR */
	GPIO_InitStructure.GPIO_Pin = AD7367_ADDR_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init (AD7367_ADDR, &GPIO_InitStructure);
	GPIO_WriteBit (AD7367_ADDR,AD7367_ADDR_Pin,Bit_RESET);
}
/*********************************END OF FILE****************************/


