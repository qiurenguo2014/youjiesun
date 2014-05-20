/*************************************************************************
#    FileName: bsp_spi.h
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 
#  LastChange: 2014-05-05 14:56:20
*************************************************************************/
/* Define to prevent recursive inclusion -------------------------------*/
#ifndef __BSP_SPI_H
#define __BSP_SPI_H

/* Includes ------------------------------------------------------------*/
/* Exported types ------------------------------------------------------*/
/* Exported constants --------------------------------------------------*/
/* Exported define -----------------------------------------------------*/
#define SPI_MASTER                  SPI1
#define SPI_MASTER_CLK              RCC_APB2Periph_SPI1
#define SPI_MASTER_GPIO             GPIOA
#define SPI_MASTER_GPIO_CLK         RCC_APB2Periph_GPIOA  
#define SPI_MASTER_PIN_NSS          GPIO_Pin_4
#define SPI_MASTER_PIN_SCK          GPIO_Pin_5
#define SPI_MASTER_PIN_MISO			GPIO_Pin_6
#define SPI_MASTER_PIN_MOSI			GPIO_Pin_7
#define SPI_MASTER_Rx_DMA_Channel	DMA1_Channel2
#define SPI_MASTER_Rx_DMA_FLAG		DMA1_FLAG_TC2
#define SPI_MASTER_DR_Base			0X4001300C

#define SPI2_MASTER                  SPI2
#define SPI2_MASTER_CLK              RCC_APB1Periph_SPI2
#define SPI2_MASTER_GPIO             GPIOB
#define SPI2_MASTER_GPIO_CLK         RCC_APB2Periph_GPIOB
#define SPI2_MASTER_PIN_NSS          GPIO_Pin_12
#define SPI2_MASTER_PIN_SCK          GPIO_Pin_13
#define SPI2_MASTER_PIN_MISO		GPIO_Pin_14
#define SPI2_MASTER_PIN_MOSI		GPIO_Pin_15
/* Exported variables --------------------------------------------------*/
/* Exported functions prototypes ---------------------------------------*/
extern void SPI1_Configuration (void);
extern void SPI2_Configuration (void);
#endif 
/*********************************END OF FILE****************************/


