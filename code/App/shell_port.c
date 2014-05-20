/*************************************************************************
#    FileName: chshell_port.c
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 
#  LastChange: 2014-02-05 23:05:34
*************************************************************************/
/* Includes ------------------------------------------------------------*/
#include <stdio.h>
//这里包含你的串口驱动头文件
#include "E:\MyFunc\shell\shell.h"
/* Types ---------------------------------------------------------------*/
/* Constants -----------------------------------------------------------*/
/* Define --------------------------------------------------------------*/
/* Variables -----------------------------------------------------------*/
/* Functions prototypes ------------------------------------------------*/
/* Functions -----------------------------------------------------------*/
struct UARTSHELL_DEV SHL_Dev;
/**
  * @brief  .
  * @param  None.
  * @retval None.
  * @verify .
  */
u8 SHL_TestFun(u8 *str1, u8 num1, u8 *str2, u8 num2, u8 *str3)
{
	printf("进入TestFun函数\r\n");
	printf("参数1: %s\r\n",str1);
	printf("参数2: %d\r\n",num1);
	printf("参数3: %s\r\n",str2);
	printf("参数4: %d\r\n",num2);
	printf("参数5: %s\r\n",str3);
	return 100;
}
/**
  * @brief  函数管理窗口.
  * @param  None.
  * @retval None.
  * @verify .
  */
#include <stdint.h>
extern void FD_SetHistoryData (void);
extern void FD_GetHistoryData (void);
extern void FD_Inc_jiezhisunhao (void);
extern void _fd_printfhisdata(void);
extern void FM31256_WriteFlashData (uint16_t addr, uint8_t data);
extern uint8_t FM31256_ReadFlashData (uint16_t addr);
extern void DA_OpenDCMODEL (void);
extern void DA_CloseDCMODEL (void);
extern void DA_StopACoutput (void);
extern void DA_StartACoutput (void);
extern void DA_SetDCoutput (uint16_t da);
extern void RL_Active_JCIO (void);
extern void RL_nActive_JCIO (void);
extern void RL_nActive_HACRELAY (void);
extern void RL_Active_HACRELAY (void);
extern void TDA7396_Open (void);
extern void DA_SwitchAC (void);
extern void DA_StartACoutput (void);
extern void RL_Active_HACRELAY (void);
extern void RL_nActive_HACRELAY (void);
extern void RL_Active_HOTPOWER (void);
extern void RL_nActive_HOTPOWER (void);
extern void DA_SetAmp (float amp);
extern uint8_t SIGOP_EmptyExit (void);
void setamp(uint32_t amp)
{
	float a;
	a = amp/100.0;
	DA_SetAmp (a);
}
const struct UARTSHELL_FunTab SHL_FunTab[]=
{
	(u32*) SHL_TestFun,"u8 SHL_TestFun(u8* str1,u8 num1,u8* str2,u8 num2,u8* str3)",
	(void*) FD_SetHistoryData, "void fdsh(void) 保存历史测量参数",
	(void*) FD_GetHistoryData, "void fdgh(void)",
	(void*) FD_Inc_jiezhisunhao, "void fdinc(void)",
	(void*) _fd_printfhisdata, "void fdpr(void)",
	(void*) FM31256_WriteFlashData, "void fmwf(u16 addr,u8 data)",
	(uint8_t*) FM31256_ReadFlashData, "u8 fmrf(u16 addr)",
	(void*) DA_OpenDCMODEL, "void DA_OpenDCMODEL(void)",
	(void*) DA_CloseDCMODEL,"void DA_CloseDCMODEL(void)",
	(void*) DA_StopACoutput, "void DA_StopACoutput(void)",
	(void*) DA_StartACoutput, "void DA_StartACoutput(void)",
	(void*) DA_SetDCoutput, "void dasetda(u16 da)",
	(void*) RL_Active_JCIO,"void RL_Active_JCIO(void)",
	(void*) RL_nActive_JCIO,"void RL_nActive_JCIO(void)",
	(void*) RL_nActive_HACRELAY,"void RL_nActive_HACRELAY(void)",
	(void*) RL_Active_HACRELAY,"void RL_Active_HACRELAY(void)",
	(void*) TDA7396_Open,"void TDA7396_Open(void)",
	(void*) DA_SwitchAC,"void DA_SwitchAC(void)",
	(void*) DA_StartACoutput,"void DA_StartACoutput(void)",
	(void*) RL_Active_HACRELAY, "void RL_Active_HACRELAY(void)",
	(void*) RL_nActive_HACRELAY, "void RL_nActive_HACRELAY(void)",
	(void*) RL_Active_HOTPOWER, "void RL_Active_HOTPOWER(void)",
	(void*) setamp, "void setamp(u32 amp)",
	(uint8_t*) SIGOP_EmptyExit,"u8 emptyexit(void)",
};	
/**
  * @brief  SHELL组件初始化.
  * @param  None.
  * @retval None.
  * @verify .
  */
extern void Bsp_SystemReset (void);
void SHL_Init(void)
{
	//UART_Init(UART3,115200l); //初始化调试串口 //默认 UART3 115200 在UART.H中定义
	SHL_Dev.cnum = 0;
	SHL_Dev.funs = SHL_FunTab;
	SHL_Dev.USART_STAT = 0;
	SHL_Dev.fnum = sizeof(SHL_FunTab)/sizeof(struct UARTSHELL_FunTab);
	SHL_PowerDown = 0;
	SHL_BootLoad = &Bsp_SystemReset;//&NVIC_SystemReset;
}
/*********************************END OF FILE****************************/


