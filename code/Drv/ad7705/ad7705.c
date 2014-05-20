/*************************************************************************
#    FileName: ad7705.c
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 
#  LastChange: 2014-05-05 15:17:10
*************************************************************************/
/* Includes ------------------------------------------------------------*/
#include "stm32f10x.h"
#include "..\..\bsp\bsp_spi.h"
#include "ad7705.h"
/* Types ---------------------------------------------------------------*/
/* Constants -----------------------------------------------------------*/
/* Define --------------------------------------------------------------*/
/* Variables -----------------------------------------------------------*/
/* Functions prototypes ------------------------------------------------*/
/* Functions -----------------------------------------------------------*/
/**
  * @brief  .
  * @param  None
  * @retval None
  */
void AD7705_Init(void)
{
	/* drdy */
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = AD7705_DRDY_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init (AD7705_DRDY, &GPIO_InitStructure);
	/* rst */
	GPIO_InitStructure.GPIO_Pin = AD7705_RST_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init (AD7705_RST, &GPIO_InitStructure);
	GPIO_WriteBit (AD7705_RST,AD7705_RST_Pin,Bit_SET);
	
}
void _AD7705_Test (void)
{
	unsigned short reg_msg;
	AD7705_ReadWriteData ((0xff));
	AD7705_ReadWriteData ((0xff));
	AD7705_ReadWriteData ((0xff));
	AD7705_ReadWriteData ((0xff));
	AD7705_ReadWriteData ((0xff));
	AD7705_ReadWriteData ((0xff));
	AD7705_ReadWriteData ((0xff));
	AD7705_ReadWriteData ((0xff));
	
	AD7705_ReadWriteData ((0x78));
	reg_msg = AD7705_ReadWriteData (0xff);
	printf ("reg_msg0 is %x\r\n",reg_msg);
	
	reg_msg = AD7705_ReadWriteData (0xff);
	printf ("reg_msg0 is %x\r\n",reg_msg);
	
	reg_msg = AD7705_ReadWriteData (0xff);
	printf ("reg_msg0 is %x\r\n",reg_msg);
	
	reg_msg = AD7705_ReadWriteData (0xff);
	printf ("reg_msg0 is %x\r\n",reg_msg);
	/*
reg_msg0 is 57
reg_msg0 is 61
reg_msg0 is ab
reg_msg0 is ff
	*/
}
unsigned char AD7705_ReadWriteData (unsigned char data)
{
	unsigned char dat;
	while (SPI_I2S_GetFlagStatus (SPI_MASTER, SPI_I2S_FLAG_TXE) == RESET);
	SPI_I2S_SendData(SPI_MASTER,data);	
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
	dat = SPI_I2S_ReceiveData (SPI_MASTER);
	return dat;
}
/*
@brief  绛夊緟杞崲缁撴潫.
@param  None.
@retval None.
*/
void AD7705_waitDRDY (void)
{
	while((GPIO_ReadInputDataBit(AD7705_DRDY, AD7705_DRDY_Pin)));
}
/**
  * @brief  .
  * @param  None
  * @retval None
  */
unsigned int AD7705_readReg (const AD7705_REG reg)
{
/*	unsigned int reg_msg = 0;
	unsigned int reg_msg1 = 0;
	unsigned int reg_msg2 = 0;
	if (reg == COMMUN_REG){

	}else if (reg == SETUP_REG){

	}else if (reg == CLOCK_REG){

	}else if (reg == DATA_REG){
		AD7705_waitDRDY ();
		AD7705_writeDWordData (0x38);
		AD7705_writeDWordData (0xff);
		SPI_I2S_ReceiveData (SPI_MASTER);
		while (SPI_I2S_GetFlagStatus(SPI_MASTER, SPI_I2S_FLAG_RXNE) == RESET);
		reg_msg = (unsigned int)SPI_I2S_ReceiveData (SPI_MASTER);
		AD7705_writeDWordData (0xff);
		while (SPI_I2S_GetFlagStatus(SPI_MASTER, SPI_I2S_FLAG_RXNE) == RESET);
		reg_msg1 = (unsigned int)SPI_I2S_ReceiveData (SPI_MASTER);
		reg_msg <<= 8;
		reg_msg |= reg_msg1;
		if (reg_msg >= 0x8000){
			reg_msg -= 0x7ffful;
		}else{
			reg_msg = 0x8000ul-reg_msg;
		}
	}else if (reg == TEST_REG){

	}else if (reg == OFFSET_REG){
		AD7705_waitDRDY ();
		AD7705_writeDWordData (0x68);
		AD7705_writeDWordData (0xff);
		SPI_I2S_ReceiveData (SPI_MASTER);
		while (SPI_I2S_GetFlagStatus(SPI_MASTER, SPI_I2S_FLAG_RXNE) == RESET);
		reg_msg = (unsigned int)SPI_I2S_ReceiveData (SPI_MASTER);
		AD7705_writeDWordData (0xff);
		while (SPI_I2S_GetFlagStatus(SPI_MASTER, SPI_I2S_FLAG_RXNE) == RESET);
		reg_msg1 = (unsigned int)SPI_I2S_ReceiveData (SPI_MASTER);
		AD7705_writeDWordData (0xff);
		while (SPI_I2S_GetFlagStatus(SPI_MASTER, SPI_I2S_FLAG_RXNE) == RESET);
		reg_msg2 = (unsigned int)SPI_I2S_ReceiveData (SPI_MASTER);
		//printf ("%x,%x,%x\r\n",reg_msg,reg_msg1,reg_msg2);
	}else if (reg == GAIN_REG){

	}
	return reg_msg;*/
}
/*********************************END OF FILE****************************/


