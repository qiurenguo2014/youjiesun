/*************************************************************************
#    FileName: flashdata.c
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 31K以上保存系统相关数据和初始化数据
				0~31K保存测试数据
#  LastChange: 2014-05-10 09:26:34
*************************************************************************/
/* Includes ------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "..\drv\fm31256\fm31256.h"
#include "flashdata.h"
/* Types ---------------------------------------------------------------*/
/* Constants -----------------------------------------------------------*/
/* Define --------------------------------------------------------------*/
/* Variables -----------------------------------------------------------*/
HISTORYTEST hisdata;
MODIFY_StructType modify;
/* Functions prototypes ------------------------------------------------*/
/* Functions -----------------------------------------------------------*/
void _fd_printfhisdata(void)
{
	printf("\r\n-------hisdata-------------");
	printf("\r\njiezhisunhao:%d",hisdata.jiezhisunhao);
	printf("\r\njiaoliupinlv:%d",hisdata.jiaoliupinlv);
	printf("\r\ntijidianzu:%d",hisdata.tijidianzu);
	printf("\r\njiareqidong:%d",hisdata.jiareqidong);
	printf("\r\nceshifangsi:%d",hisdata.ceshifangsi);
	printf("\r\nkongbeidianrong:%d",hisdata.kongbeidianrong);
	printf("\r\n--------------------");
}
/*
@brief  矫正历史测试数据.
@param  None.
@retval None.
*/
void FD_AdjustHistoryData (void)
{
	if(hisdata.jiezhisunhao >= AC_END){
		hisdata.jiezhisunhao = AC_0V;
	}
	if(hisdata.jiaoliupinlv >= FRE_END){
		hisdata.jiaoliupinlv = FRE_50HZ;
	}
	if(hisdata.tijidianzu >= DC_END){
		hisdata.tijidianzu = DC_OFF;
	}
	if(hisdata.jiareqidong >= TM_END){
		hisdata.jiareqidong = TM_OFF;
	}
	if(hisdata.ceshifangsi >= EEND_WORK){
		hisdata.ceshifangsi = EAUTO_WORK;
	}
	if(hisdata.kongbeidianrong == 0){
		hisdata.kongbeidianrong = 50*100;
	}
}
/*
@brief  保存历史测试数据参数.
@param  None.
@retval None.
*/
void FD_SetHistoryData (void)
{
	FM31256_WriteFlashDataSuint (FLASH_ADDR_SYSTEST, (uint32_t*)&hisdata.jiezhisunhao,sizeof(hisdata));
}
void FD_GetHistoryData (void)
{
	FM31256_ReadFlashDataSuint (FLASH_ADDR_SYSTEST, (uint32_t*)&hisdata.jiezhisunhao, sizeof(hisdata));
	FD_AdjustHistoryData ();
	FM31256_WriteFlashDataSuint (FLASH_ADDR_SYSTEST, (uint32_t*)&hisdata.jiezhisunhao,sizeof(hisdata));
}
/*
@brief  按键调用 按下后对应历史数据状态改变.
@param  None.
@retval None.
*/
void FD_Inc_jiezhisunhao (void)
{
	hisdata.jiezhisunhao += 1;
	FD_AdjustHistoryData ();
	FD_SetHistoryData ();
}
void FD_Inc_jiaoliupinlv (void)
{
	hisdata.jiaoliupinlv ++;
	FD_AdjustHistoryData ();
	FD_SetHistoryData ();
}
void FD_Inc_tijidianzu (void)
{
	hisdata.tijidianzu ++;
	FD_AdjustHistoryData ();
	FD_SetHistoryData ();
}
void FD_Inc_jiareqidong (void)
{
	hisdata.jiareqidong ++;
	FD_AdjustHistoryData ();
	FD_SetHistoryData ();
}
void FD_Inc_ceshifangsi (void)
{
	hisdata.ceshifangsi ++;
	FD_AdjustHistoryData ();
	FD_SetHistoryData ();
}
void FD_GetHisdataStr_jiezhisunhao (char *str)
{
	switch(hisdata.jiezhisunhao){
		case AC_0V:
			strcpy(str,"关");
			break;
		case AC_600V:
			strcpy(str,"600V");
			break;
		case AC_700V:
			strcpy(str,"700V");
			break;
		case AC_800V:
			strcpy(str,"800V");
			break;
		case AC_900V:
			strcpy(str,"900V");
			break;
		case AC_1000V:
			strcpy(str,"1000V");
			break;
		case AC_1100V:
			strcpy(str,"1100V");
			break;
		case AC_1200V:
			strcpy(str,"1200V");
			break;
		case AC_1300V:
			strcpy(str,"1300V");
			break;
		case AC_1400V:
			strcpy(str,"1400V");
			break;
		case AC_1500V:
			strcpy(str,"1500V");
			break;
		case AC_1600V:
			strcpy(str,"1600V");
			break;
		case AC_1700V:
			strcpy(str,"1700V");
			break;
		case AC_1800V:
			strcpy(str,"1800V");
			break;
		case AC_1900V:
			strcpy(str,"1900V");
			break;
		case AC_2000V:
			strcpy(str,"2000V");
			break;
		case AC_2100V:
			strcpy(str,"2100V");
			break;
		case AC_2200V:
			strcpy(str,"2200V");
			break;
		case AC_2300V:
			strcpy(str,"2300V");
			break;
		case AC_2400V:
			strcpy(str,"2400V");
			break;
		case AC_2500V:
			strcpy(str,"2500V");
			break;
		default:
			hisdata.jiezhisunhao = 0;
			strcpy(str,"关");
			break;
	}
}
void FD_GetHisdataStr_jiaoliupinlv (char *str)
{
	switch(hisdata.jiaoliupinlv){
		case FRE_50HZ:
			strcpy(str,"50Hz");
			break;
		case FRE_475_525HZ:
			strcpy(str,"47.5/52.5Hz");
			break;
		case FRE_45_55HZ:
			strcpy(str,"45/55Hz");
			break;
		case FRE_60HZ:
			strcpy(str,"60Hz");
			break;
		case FRE_575_625HZ:
			strcpy(str,"57.5/62.5Hz");
			break;
		case FRE_55_65HZ:
			strcpy(str,"55/65Hz");
			break;
		default:
			hisdata.jiaoliupinlv = 0;
			strcpy(str,"50Hz");
			break;
	}
}
void FD_GetHisdataStr_tijidianzu (char *str)
{
	switch(hisdata.tijidianzu){
		case DC_OFF:
			strcpy(str,"关");
			break;
		case DC_300V:
			strcpy(str,"300V");
			break;
		case DC_400V:
			strcpy(str,"400V");
			break;
		case DC_500V:
			strcpy(str,"500V");
			break;
		case DC_600V:
			strcpy(str,"600V");
			break;
		default:
			hisdata.tijidianzu = DC_OFF;
			strcpy(str,"关");
			break;
	}
}
void FD_GetHisdataStr_jiareqidong (char *str)
{
	switch(hisdata.jiareqidong){
		case TM_OFF:
			strcpy(str,"关");
			break;
		case TM_50C:
			strcpy(str,"50℃");
			break;
		case TM_55C:
			strcpy(str,"55℃");
			break;
		case TM_60C:
			strcpy(str,"60℃");
			break;
		case TM_65C:
			strcpy(str,"65℃");
			break;
		case TM_70C:
			strcpy(str,"70℃");
			break;
		case TM_75C:
			strcpy(str,"75℃");
			break;
		case TM_80C:
			strcpy(str,"80℃");
			break;
		case TM_85C:
			strcpy(str,"85℃");
			break;
		case TM_90C:
			strcpy(str,"90℃");
			break;
		case TM_95C:
			strcpy(str,"95℃");
			break;
		case TM_100C:
			strcpy(str,"100℃");
			break;
		case TM_105C:
			strcpy(str,"105℃");
			break;
		case TM_110C:
			strcpy(str,"110℃");
			break;
		case TM_115C:
			strcpy(str,"115℃");
			break;
		case TM_120C:
			strcpy(str,"120℃");
			break;
		case TM_125C:
			strcpy(str,"125℃");
			break;
		case TM_130C:
			strcpy(str,"130℃");
			break;
		default:
			hisdata.jiareqidong = TM_OFF;
			strcpy(str,"关");
			break;
	}
}
void FD_GetHisdataStr_ceshifangsi (char *str)
{
	switch(hisdata.ceshifangsi){
		case EAUTO_WORK:
			strcpy(str,"自动");
			break;
		case EHAND_WORK:
			strcpy(str,"手动");
			break;
		case ECOM_WORK:
			strcpy(str,"通信");
			break;
		case EEMPTY_WORK:
			strcpy(str,"空杯");
			break;
		case ERES_WORK:
			strcpy(str,"电阻");
			break;
		default:
			hisdata.ceshifangsi = EAUTO_WORK;
			strcpy(str,"自动");
			break;
	}
}
void FD_GetHisdataStr_kongbeidianrong (char *str)
{
	sprintf(str,"空杯电容 \n%5.2fpf",hisdata.kongbeidianrong/100.0);
	//strcpy(str,"空杯电容 \n%fpf",hisdata.kongbeidianrong);
// 	switch(hisdata.kongbeidianrong){
// 		case 0:
// 			strcpy(str,"空杯电容 \n120.85pf");
// 			break;
// 		default:
// 			hisdata.kongbeidianrong = 0;
// 			strcpy(str,"空杯电容 \n120.85pf"); 
// 			break;
// 	}
}
void FD_AdjustModifyData (void)
{
	if(modify.ac_k == 0){
		modify.ac_k = 1;
	}
}
/*获取修正系数数据*/
void FD_GetModifyData(void)
{
	uint16_t offset;//偏移量
	offset = sizeof(hisdata);
	FM31256_ReadFlashDataSuint (FLASH_ADDR_SYSTEST+offset, (uint32_t*)&modify.ac_k, sizeof(modify));
	FD_AdjustModifyData ();
	FD_SetModifyData ();
	
}
void FD_SetModifyData (void)
{
	uint16_t offset;//偏移量
	offset = sizeof(hisdata);
	FM31256_WriteFlashDataSuint (FLASH_ADDR_SYSTEST+offset, (uint32_t*)&modify.ac_k,sizeof(modify));
}
/*
@brief  内存初始化 检测是否第一次启动 获取油样测试出师值存入数组中.
@param  None.
@retval None.
*/
void FD_Init (void)
{
 	FD_GetHistoryData ();
	FD_GetModifyData ();
}
/*********************************END OF FILE****************************/


