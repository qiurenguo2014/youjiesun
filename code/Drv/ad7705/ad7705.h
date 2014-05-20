/*************************************************************************
#    FileName: ad7705.h
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 
#  LastChange: 2014-05-05 15:17:29
*************************************************************************/
/* Define to prevent recursive inclusion -------------------------------*/
#ifndef __AD7705_H
#define __AD7705_H

/* Includes ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------*/
/* Exported constants --------------------------------------------------*/
/* Exported define -----------------------------------------------------*/
typedef enum{
	COMMUN_REG = 0,
	SETUP_REG,
	CLOCK_REG,
	DATA_REG,
	TEST_REG,
	NO_OP_REG,
	OFFSET_REG,
	GAIN_REG,
}AD7705_REG;
#define AD7705_DRDY GPIOC
#define AD7705_DRDY_Pin GPIO_Pin_5
#define AD7705_RST GPIOC
#define AD7705_RST_Pin GPIO_Pin_4
/* Exported variables --------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------*/
extern void AD7705_Init(void);
extern unsigned char AD7705_ReadWriteData (unsigned char data);
extern void AD7705_waitDRDY (void);
extern unsigned int AD7705_readReg (const AD7705_REG reg);
#endif 
/*********************************END OF FILE****************************/


