/*************************************************************************
#    FileName: fm31256.c
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: fm31256 eeprom 256kbit 32K
#  LastChange: 2014-05-06 14:52:01
*************************************************************************/
/* Includes ------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include "..\..\bsp\bsp_i2c.h"
#include "fm31256.h"
/* Types ---------------------------------------------------------------*/
/* Constants -----------------------------------------------------------*/
/* Define --------------------------------------------------------------*/
/* Variables -----------------------------------------------------------*/
/* Functions prototypes ------------------------------------------------*/
/* Functions -----------------------------------------------------------*/
/*
@brief  启动振荡.
@param  None.
@retval None.
*/
void FM31256_OSCEN (void)
{
	I2C_WriteByte(REG_WRITE,CONTROL,0x0);
}
/*
@brief  停止振荡.
@param  None.
@retval None.
*/
void FM31256_OSCDIS (void)
{
	I2C_WriteByte(REG_WRITE,CONTROL,0x80);
}
/*
@brief  获取时间 BCD码.
@param  None.
@retval None.
*/
void FM31256_GetTime (unsigned char *data)
{
	/* 读时间 */
	I2C_WriteByte(REG_WRITE,FLAGS,1);
	I2C_ReadSByte (REG_READ, SECONDS, data, 7);
	/* 读完要恢复0 */
	I2C_WriteByte(REG_WRITE,FLAGS,0);
}
/*
@brief  设置时间.
@param  None.
@retval None.
*/
void FM31256_SetTime (unsigned char *data)
{
	/* 读时间 */
	I2C_WriteByte(REG_WRITE,FLAGS,0x2);
	I2C_WriteSByte (REG_WRITE, SECONDS, data, 7);
	/* 读完要恢复0 */
	I2C_WriteByte(REG_WRITE,FLAGS,0);
}
/*
@brief  关闭写保护.
@param  None.
@retval None.
*/
void FM31256_CloseWP (void)
{
	uint8_t db;
	db = I2C_ReadByte(REG_READ, COMPANION);
	I2C_WriteByte(REG_WRITE,COMPANION,db&0xe7);
}
/*
@brief  .
@param  None.
@retval None.
*/
uint8_t FM31256_ReadFlashData (uint16_t addr)
{
	uint8_t data;
	data = I2C_ReadByte1(IIC_READ, addr);
	return data;
}
/*
@brief  .
@param  None.
@retval None.
*/
void FM31256_WriteFlashData (uint16_t addr, uint8_t data)
{
	I2C_WriteByte1 (IIC_WRITE,addr,data);
}
/*
@brief  .
@param  None.
@retval None.
*/
void FM31256_ReadFlashDataS (uint16_t addr, uint8_t *data, uint16_t no)
{
	I2C_ReadSByte1(IIC_WRITE,addr,data,no);
}
/*
@brief  .
@param  None.
@retval None.
*/
void FM31256_WriteFlashDataS (uint16_t addr, uint8_t *data, uint16_t no)
{
	I2C_WriteSByte1(IIC_WRITE,addr,data,no);
}
/*
@brief  .
@param  None.
@retval None.
*/
void FM31256_ReadFlashDataSuint (uint16_t addr, uint32_t *data, uint16_t no)
{
	I2C_ReadSByte1(IIC_WRITE,addr,(uint8_t*)data,no);
}
/*
@brief  .
@param  None.
@retval None.
*/
void FM31256_WriteFlashDataSuint (uint16_t addr, uint32_t *data, uint16_t no)
{
	I2C_WriteSByte1(IIC_WRITE,addr,(uint8_t*)data,no);
}
/*
@brief  .
@param  None.
@retval None.
*/
void FM31256_Init (void)
{
	FM31256_CloseWP ();
}
void _fm31256_test(void)
{
	uint8_t databuf[100],i;
	FM31256_CloseWP ();
	FM31256_ReadFlashDataS (0, databuf, 100);
	for(i=0; i<100; i++){
		printf("\r\ndata:%u",databuf[i]);
	}
	for(i=0; i<100; i++){
		databuf[i] = i;
	}
	printf("\r\n--------------fenggexian-----------------");
	FM31256_WriteFlashDataS (0,databuf,100);
	FM31256_ReadFlashDataS (0, databuf, 100);
	for(i=0; i<100; i++){
		printf("\r\ndata:%u",databuf[i]);
	}
}
/*********************************END OF FILE****************************/


