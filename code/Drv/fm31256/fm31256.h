/*************************************************************************
#    FileName: fm31256.h
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 
#  LastChange: 2014-05-06 14:52:12
*************************************************************************/
/* Define to prevent recursive inclusion -------------------------------*/
#ifndef __FM31256_H
#define __FM31256_H

/* Includes ------------------------------------------------------------*/
#include <stdint.h>
/* Exported types ------------------------------------------------------*/
/* Exported constants --------------------------------------------------*/
/* Exported define -----------------------------------------------------*/
#define IIC_READ 	0XA1     //flash
#define IIC_WRITE 	(0XA0)   //
#define REG_READ 	0XD1	//reg
#define REG_WRITE 	(0XD0)

#define MAX_FLASHSIZE 32 //kBYTE

#define IIC_uiLen   0x02
#define REG_uiLen   0x01

#define RUN 		1
#define STOP 		0
#define NOP 		_nop_()
//===============================
#define SERIALNUM 	0X11

#define COUNTER2M 	0X10
#define COUNTER2L 	0X0F
#define COUNTER1M 	0X0E
#define COUNTER1L 	0X0D
#define COUNTCON 	0X0C	//ALARM MINUTES

#define COMPANION 	0X0B	//ALARM SECONDS
#define WDCON 		0X0A
#define WDFLAG 		0X09	//WATCHDOG

#define YEAR 		0X08	//YEARS
#define MONTH 		0X07	//MONTH
#define DATE 		0X06	//DATE
#define DAY 		0X05	//DAY
#define HOURS 		0X04	//HOURS
#define MINUTES 	0X03	//MINUTES
#define SECONDS 	0X02	//SECONDS

#define CONTROL 	0x01	//USER-NV
#define FLAGS 		0x00	//FLAGS/CONTROL

#define BL_write    0x00
#define BL_read     0x01
//enum{EI2C_send,EI2C_Recv};
/* Exported variables --------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------*/
extern void FM31256_Init (void);
extern void FM31256_OSCEN (void);
extern void FM31256_OSCDIS (void);
extern void FM31256_GetTime (unsigned char *data);
extern void FM31256_SetTime (unsigned char *data);
extern void FM31256_ReadFlashDataS (uint16_t addr, uint8_t *data, 
									uint16_t no);
extern void FM31256_WriteFlashDataS (uint16_t addr, uint8_t *data, 
									uint16_t no);
extern void FM31256_WriteFlashDataSuint (uint16_t addr, uint32_t *data, 
									uint16_t no);
extern void FM31256_ReadFlashDataSuint (uint16_t addr, uint32_t *data, 
									uint16_t no);
#endif 
/*********************************END OF FILE****************************/


