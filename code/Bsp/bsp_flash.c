/*************************************************************************
#    FileName: bsp_flash.c
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 
#  LastChange: 2014-05-09 15:25:02
*************************************************************************/
/* Includes ------------------------------------------------------------*/
#include "stm32f10x.h"
#include "bsp_flash.h"
/* Types ---------------------------------------------------------------*/
/* Constants -----------------------------------------------------------*/
/* Define --------------------------------------------------------------*/
#define FLASH_PAGE_SIZE    ((uint16_t)0x800)//HD device size 
#define BANK1_WRITE_START_ADDR  ((uint32_t)0x08016000)//((uint32_t)0x08028000)
#define BANK1_WRITE_END_ADDR    ((uint32_t)0x08080000)
/* Variables -----------------------------------------------------------*/
/* Functions prototypes ------------------------------------------------*/
/* Functions -----------------------------------------------------------*/
/*
@brief  .
@param  None.
@retval None.
*/
void FL_Configuration (void)
{
	
}
// unsigned char FLASH_eraseAllFlashPages (void)
// {
// 	unsigned int NbrOfPage = 0x00;
// 	unsigned int EraseCounter = 0x00;
//     FLASH_Unlock();
// 	NbrOfPage = (BANK1_WRITE_END_ADDR - BANK1_WRITE_START_ADDR) / FLASH_PAGE_SIZE;
//     /* Unlock the Flash Bank1 Program Erase controller */
//     /* Clear All pending flags */
//     FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);

//     /* Erase the FLASH pages */
//     for(EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
//     {
//       FLASHStatus = FLASH_ErasePage(BANK1_WRITE_START_ADDR + (FLASH_PAGE_SIZE * EraseCounter));
//     }
//     FLASH_Lock();
//     if (FLASHStatus != FLASH_COMPLETE){
//         return FAILED;
//     }
//     return PASSED;
// }
/*
@brief  .
@param  None.
@retval None.
*/
unsigned char FL_programDatas (uint8_t *pData, uint32_t offset, uint32_t length)
{
    FLASH_Unlock();
    FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
    while (length--) {
        FLASH_ProgramOptionByteData(BANK1_WRITE_START_ADDR + offset, *pData);
        if (FLASH_GetStatus() != FLASH_COMPLETE) {
        	return 0;
        }
        else {
        	// 写入数据准确性校验
        	unsigned char checkNum;
        	checkNum = *(uint8_t*)(BANK1_WRITE_START_ADDR + offset);
        	if (*pData != checkNum) {
                FLASH_Lock();
        		return 0;		//数据出错
        	}
        	else {
        		offset ++;
        		pData ++;
        	}
        }
    }
    FLASH_Lock();
    return 1;
}
/*********************************END OF FILE****************************/


