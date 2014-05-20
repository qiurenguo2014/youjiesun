/*************************************************************************
#    FileName: SIGOP.C
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 信号输出控制 交流信号控制和直流信号控制
#  LastChange: 2014-05-13 10:50:52
*************************************************************************/
/* Includes ------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include "stm32f10x.h"
#include "flashdata.h"
#include "..\bsp\bsp_relay.h"
#include "..\bsp\bsp_dac.h"
#include "..\bsp\bsp_systick.h"
#include "..\drv\tda7396\tda7396.h"
#include "sigop.h"
/* Types ---------------------------------------------------------------*/
/* Constants -----------------------------------------------------------*/
/* Define --------------------------------------------------------------*/
/* Variables -----------------------------------------------------------*/
SIGOP_StructType sig;
/* Functions prototypes ------------------------------------------------*/
/* Functions -----------------------------------------------------------*/
/*
@brief  切换到AC模式 DC模块断电 切运放继电器 BU508导通 TDA工作 HAC继电器.
@param  None.
@retval None.
*/
void SIGOP_SwACmodel(void)
{
	DA_CloseDCMODEL ();
	RL_Active_JCIO ();
	DA_SwitchAC ();//bu508
	TDA7396_Open ();
	RL_Active_HACRELAY ();
}
void SIGOP_SwACmodelExit(void)
{
	DA_StopACoutput();
	RL_nActive_JCIO ();
	TDA7396_Close ();
	RL_nActive_HACRELAY ();	
}
/*
@brief  根据设置的参数设置频率 1
@param  None.
@retval None.
*/
void SIGOP_SetFre1(void)
{
	switch(hisdata.jiaoliupinlv){
		case FRE_50HZ:
			sig.prefre = 50;
			DA_SetFre(sig.prefre);
			break;
		case FRE_475_525HZ:
			sig.prefre = 47.5;
			DA_SetFre(sig.prefre);
			break;
		case FRE_45_55HZ:
			sig.prefre = 45;
			DA_SetFre(sig.prefre);
			break;
		case FRE_60HZ:
			sig.prefre = 60;
			DA_SetFre(sig.prefre);
			break;
		case FRE_575_625HZ:
			sig.prefre = 57.5;
			DA_SetFre(sig.prefre);
			break;
		case FRE_55_65HZ:
			sig.prefre = 55;
			DA_SetFre(sig.prefre);
			break;
		default:
			break;
	}
}
void SIGOP_SetFre2(void)
{
	switch(hisdata.jiaoliupinlv){
		case FRE_50HZ:
			sig.prefre = 50;
			DA_SetFre(sig.prefre);
			break;
		case FRE_475_525HZ:
			sig.prefre = 52.5;
			DA_SetFre(sig.prefre);
			break;
		case FRE_45_55HZ:
			sig.prefre = 55;
			DA_SetFre(sig.prefre);
			break;
		case FRE_60HZ:
			sig.prefre = 60;
			DA_SetFre(sig.prefre);
			break;
		case FRE_575_625HZ:
			sig.prefre = 62.5;
			DA_SetFre(sig.prefre);
			break;
		case FRE_55_65HZ:
			sig.prefre = 65;
			DA_SetFre(sig.prefre);
			break;
		default:
			break;
	}
}
/*
@brief  设置变压器输出级电压
		电压是缓慢上升到额定值
@param  None.
@retval None.
*/
void SIGOP_SetOutputVol (float vol)
{
	float a,bj,c;
	a = vol/2500.0;
	a *= modify.ac_k;
	DA_SetAmp (0);
	DA_StartACoutput ();
	for(bj=0; bj<1; bj+=0.1){
		c = a*bj;
		DA_SetAmp (c);
		SYSTICK_Delay10ms (20);
	}
	DA_SetAmp (a);
}

void SIGOP_SetAmp (void)
{
	switch(hisdata.jiezhisunhao){
	case AC_0V:
		sig.preacvol = 0;
		SIGOP_SetOutputVol (sig.preacvol);
		break;
	case AC_600V:
		sig.preacvol = 600;
		SIGOP_SetOutputVol (sig.preacvol);
		break;
	case AC_700V:
		sig.preacvol = 700;
		SIGOP_SetOutputVol (sig.preacvol);
		break;
	case AC_800V:
		sig.preacvol = 800;
		SIGOP_SetOutputVol (sig.preacvol);
		break;
	case AC_900V:
		sig.preacvol = 900;
		SIGOP_SetOutputVol (sig.preacvol);
		break;
	case AC_1000V:
		sig.preacvol = 1000;
		SIGOP_SetOutputVol (sig.preacvol);
		break;
	case AC_1100V:
		sig.preacvol = 1100;
		SIGOP_SetOutputVol (sig.preacvol);
		break;
	case AC_1200V:
		sig.preacvol = 1200;
		SIGOP_SetOutputVol (sig.preacvol);
		break;
	case AC_1300V:
		sig.preacvol = 1300;
		SIGOP_SetOutputVol (sig.preacvol);
		break;
	case AC_1400V:
		sig.preacvol = 1400;
		SIGOP_SetOutputVol (sig.preacvol);
		break;
	case AC_1500V:
		sig.preacvol = 1500;
		SIGOP_SetOutputVol (sig.preacvol);
		break;
	case AC_1600V:
		sig.preacvol = 1600;
		SIGOP_SetOutputVol (sig.preacvol);
		break;
	case AC_1700V:
		sig.preacvol = 1700;
		SIGOP_SetOutputVol (sig.preacvol);
		break;
	case AC_1800V:
		sig.preacvol = 1800;
		SIGOP_SetOutputVol (sig.preacvol);
		break;
	case AC_1900V:
		sig.preacvol = 1900;
		SIGOP_SetOutputVol (sig.preacvol);
		break;
	case AC_2000V:
		sig.preacvol = 2000;
		SIGOP_SetOutputVol (sig.preacvol);
		break;
	case AC_2100V:
		sig.preacvol = 2100;
		SIGOP_SetOutputVol (sig.preacvol);
		break;
	case AC_2200V:
		sig.preacvol = 2200;
		SIGOP_SetOutputVol (sig.preacvol);
		break;
	case AC_2300V:
		sig.preacvol = 2300;
		SIGOP_SetOutputVol (sig.preacvol);
		break;
	case AC_2400V:
		sig.preacvol = 2400;
		SIGOP_SetOutputVol (sig.preacvol);
		break;
	case AC_2500V:
		sig.preacvol = 2500;
		SIGOP_SetOutputVol (sig.preacvol);
		break;
	default:		
		break;
	}
}
/*
@brief  .
@param  None.
@retval None.
*/
uint8_t SIGOP_AutoTest(void)
{
	printf("\r\nzidongceliang");
	return 0;
}
/*
@brief  .
@param  None.
@retval None.
*/
uint8_t SIGOP_HandTest(void)
{
	printf("\r\nshoudongceliang");
	return 0;
}
/*
@brief  .
@param  None.
@retval None.
*/
uint8_t SIGOP_ComTest(void)
{
	printf("\r\ntongxinceliang");
	return 0;
}
/*
@brief  .
@param  None.
@retval None.
*/
uint8_t SIGOP_EmptyTest(void)
{
	printf("\r\nkongbeiceliang");	
	SIGOP_SwACmodel ();
	SIGOP_SetFre1 ();//第一次频率设定
	SIGOP_SetAmp ();//输出
	return 0;
}
/*退出空杯测量*/
uint8_t SIGOP_EmptyExit (void)
{
	SIGOP_SwACmodelExit ();
	return 0;
}
/*
@brief  .
@param  None.
@retval None.
*/
uint8_t SIGOP_ResTest(void)
{
	printf("\r\ndianzuceliang");
	return 0;
}
/*
@brief  .
@param  None.
@retval None.
*/
uint8_t SIGOP_StartTest (void)
{
	switch(hisdata.ceshifangsi){
		case EAUTO_WORK:
			SIGOP_AutoTest ();
			break;
		case EHAND_WORK:
			SIGOP_HandTest ();
			break;
		case ECOM_WORK:
			SIGOP_ComTest ();
			break;
		case EEMPTY_WORK:
			SIGOP_EmptyTest ();
			break;
		case ERES_WORK:
			SIGOP_ResTest ();
			break;
		default:
			break;
	}
	return 0;
}
/*
@brief  .
@param  None.
@retval None.
*/
void SIGOP_Init (void)
{
	
}
/*********************************END OF FILE****************************/


