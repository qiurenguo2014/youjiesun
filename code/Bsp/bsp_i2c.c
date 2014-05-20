/*************************************************************************
#    FileName: bsp_i2c.c
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 
#  LastChange: 2014-05-06 14:58:02
*************************************************************************/
/* Includes ------------------------------------------------------------*/
#include "stm32f10x.h"
#include "bsp_i2c.h"
/* Types ---------------------------------------------------------------*/
/* Constants -----------------------------------------------------------*/
/* Define --------------------------------------------------------------*/
/* Variables -----------------------------------------------------------*/
/* Functions prototypes ------------------------------------------------*/
/* Functions -----------------------------------------------------------*/
typedef enum{I2C_WRITE,I2C_READ}I2C_CTRL;
/*
@brief  .
@param  None.
@retval None.
*/
void I2C_WriteByte(unsigned char id,unsigned char write_address,unsigned char byte)
{
	I2C_GenerateSTART(I2C2,ENABLE);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2C2,id,I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	I2C_SendData(I2C2, write_address);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_SendData(I2C2, byte);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_GenerateSTOP(I2C2, ENABLE);
}
void I2C_WriteByte1(unsigned char id,unsigned short write_address,unsigned char byte)
{
	I2C_GenerateSTART(I2C2,ENABLE);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2C2,id,I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	I2C_SendData(I2C2, write_address>>8);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_SendData(I2C2, write_address);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	I2C_SendData(I2C2, byte);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_GenerateSTOP(I2C2, ENABLE);
}
void I2C_WriteSByte(u8 id,u8 addr,u8* pBuffer,  u16 no)
{
	if(no==0)
		return;	
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));
	/*起始位*/
	I2C_GenerateSTART(I2C2, ENABLE);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT)); 
	/*器件地址(写)*/
	I2C_Send7bitAddress(I2C2, id&0xfe, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));	
	/*写地址值*/
	I2C_SendData(I2C2, addr);
	while(! I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	while(no--)  
	{
	  I2C_SendData(I2C2, *pBuffer); 
	  pBuffer++; 
	  while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	}	
	/*停止位*/
	I2C_GenerateSTOP(I2C2, ENABLE);
}
void I2C_WriteSByte1(u8 id,u16 addr,const u8* pBuffer,  u16 no)
{
	if(no==0)
		return;	
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));
	/*起始位*/
	I2C_GenerateSTART(I2C2, ENABLE);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT)); 
	/*器件地址(写)*/
	I2C_Send7bitAddress(I2C2, id&0xfe, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));	
	/*写地址值*/
	I2C_SendData(I2C2, addr>>8);
	while(! I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_SendData(I2C2, addr);
	while(! I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
	while(no--)  
	{
	  I2C_SendData(I2C2, *pBuffer); 
	  pBuffer++; 
	  while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	}	
	/*停止位*/
	I2C_GenerateSTOP(I2C2, ENABLE);
}
/*
@brief  .
@param  None.
@retval None.
*/
unsigned char I2C_ReadByte(unsigned char id, unsigned char read_address)
{  
	unsigned char temp;
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));
  	I2C_GenerateSTART(I2C2, ENABLE);
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
  	I2C_Send7bitAddress(I2C2, id, I2C_Direction_Transmitter);
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  	I2C_Cmd(I2C2, ENABLE);
  	I2C_SendData(I2C2, read_address);  
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  	I2C_GenerateSTART(I2C2, ENABLE);
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
  	I2C_Send7bitAddress(I2C2, id, I2C_Direction_Receiver);
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    I2C_AcknowledgeConfig(I2C2, DISABLE);
    I2C_GenerateSTOP(I2C2, ENABLE);
    while(!(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED)));
	          temp = I2C_ReceiveData(I2C2);
  	I2C_AcknowledgeConfig(I2C2, ENABLE);
	return temp;
}
unsigned char I2C_ReadByte1(unsigned char id, unsigned short read_address)
{  
	unsigned char temp;
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));
  	I2C_GenerateSTART(I2C2, ENABLE);
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
  	I2C_Send7bitAddress(I2C2, id, I2C_Direction_Transmitter);
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  	I2C_Cmd(I2C2, ENABLE);
	
  	I2C_SendData(I2C2, read_address >> 8);
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	I2C_SendData(I2C2, read_address);
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	
  	I2C_GenerateSTART(I2C2, ENABLE);
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));
  	I2C_Send7bitAddress(I2C2, id, I2C_Direction_Receiver);
  	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    I2C_AcknowledgeConfig(I2C2, DISABLE);
    I2C_GenerateSTOP(I2C2, ENABLE);
    while(!(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED)));
	          temp = I2C_ReceiveData(I2C2);
  	I2C_AcknowledgeConfig(I2C2, ENABLE);
	return temp;
}
void I2C_ReadSByte(u8 id,u8 addr ,u8* pBuffer,u16 no)
{
    if(no==0)
		return;	
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));		
	/*允许1字节1应答模式*/
	I2C_AcknowledgeConfig(I2C2, ENABLE);
	/* 发送起始位 */
    I2C_GenerateSTART(I2C2, ENABLE);
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,主模式*/	
    /*发送器件地址(写)*/
    I2C_Send7bitAddress(I2C2,  id&0xfe, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	/*发送地址*/
	I2C_SendData(I2C2, addr);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));/*数据已发送*/		
	/*起始位*/
	I2C_GenerateSTART(I2C2, ENABLE);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));	
	/*器件读*/
	I2C_Send7bitAddress(I2C2, id|I2C_READ, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    while (no)
    {
		if(no==1)
		{
     		I2C_AcknowledgeConfig(I2C2, DISABLE);	//最后一位后要关闭应答的
    		I2C_GenerateSTOP(I2C2, ENABLE);			//发送停止位
		}	    
		while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */
	    *pBuffer = I2C_ReceiveData(I2C2);
	    pBuffer++;
	    /* Decrement the read bytes counter */
	    no--;
    }
	//再次允许应答模式
	I2C_AcknowledgeConfig(I2C2, ENABLE);
}
void I2C_ReadSByte1(u8 id,u16 addr ,u8* pBuffer,u16 no)
{
    if(no==0)
		return;	
	while(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));		
	/*允许1字节1应答模式*/
	I2C_AcknowledgeConfig(I2C2, ENABLE);
	/* 发送起始位 */
    I2C_GenerateSTART(I2C2, ENABLE);
    while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,主模式*/	
    /*发送器件地址(写)*/
    I2C_Send7bitAddress(I2C2,  id&0xfe, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	
	/*发送地址*/
	I2C_SendData(I2C2, addr>>8);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));/*数据已发送*/		
	I2C_SendData(I2C2, addr);
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));/*数据已发送*/		
	
	/*起始位*/
	I2C_GenerateSTART(I2C2, ENABLE);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT));	
	/*器件读*/
	I2C_Send7bitAddress(I2C2, id|I2C_READ, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
    while (no)
    {
		if(no==1)
		{
     		I2C_AcknowledgeConfig(I2C2, DISABLE);	//最后一位后要关闭应答的
    		I2C_GenerateSTOP(I2C2, ENABLE);			//发送停止位
		}	    
		while(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED)); /* EV7 */
	    *pBuffer = I2C_ReceiveData(I2C2);
	    pBuffer++;
	    /* Decrement the read bytes counter */
	    no--;
    }
	//再次允许应答模式
	I2C_AcknowledgeConfig(I2C2, ENABLE);
}
 
/*
@brief  .
@param  None.
@retval None.
*/
void I2C_Configuration (void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	I2C_InitTypeDef I2C_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);
	/* Configure IO connected to IIC*********************/
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 200000;

	I2C_Cmd(I2C2, ENABLE);
	I2C_Init(I2C2, &I2C_InitStructure);
}
/*********************************END OF FILE****************************/


