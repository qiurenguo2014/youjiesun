/*************************************************************************
#    FileName: bsp_i2c.h
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 
#  LastChange: 2014-05-06 14:58:13
*************************************************************************/
/* Define to prevent recursive inclusion -------------------------------*/
#ifndef __BSP_I2C_H
#define __BSP_I2C_H

/* Includes ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------*/
/* Exported constants --------------------------------------------------*/
/* Exported define -----------------------------------------------------*/
/* Exported variables --------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------*/
extern void I2C_Configuration (void);
extern void I2C_WriteByte(unsigned char id,unsigned char write_address,
					unsigned char byte);
extern void I2C_WriteByte1(unsigned char id,unsigned short write_address,
					unsigned char byte);
extern void I2C_WriteSByte(unsigned char id,unsigned char addr,
					unsigned char* pBuffer,  unsigned short no);
extern void I2C_WriteSByte1(unsigned char id,unsigned short addr,
					const unsigned char *pBuffer,  unsigned short no);
extern unsigned char I2C_ReadByte(unsigned char id, 
					unsigned char read_address);
extern unsigned char I2C_ReadByte1(unsigned char id, 
					unsigned short read_address);
extern void I2C_ReadSByte(unsigned char id,unsigned char addr ,
					unsigned char* pBuffer,unsigned short no);
extern void I2C_ReadSByte1(unsigned char id,unsigned short addr ,
					unsigned char* pBuffer,unsigned short no);
#endif 
/*********************************END OF FILE****************************/


