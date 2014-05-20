/*************************************************************************
#    FileName: commu.c
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 
#  LastChange: 2014-05-17 16:56:19
*************************************************************************/
/* Includes ------------------------------------------------------------*/
#include "commu.h"
/* Types ---------------------------------------------------------------*/
/* Constants -----------------------------------------------------------*/
/* Define --------------------------------------------------------------*/
/* Variables -----------------------------------------------------------*/
DATA_StructType recdata;
DATA_StructType senddata;
/* Functions prototypes ------------------------------------------------*/
/* Functions -----------------------------------------------------------*/
/*
@brief  通信初始化.
@param  None.
@retval None.
*/
void CM_Init (void)
{

}
void CM_ClearCount (void)
{
	recdata.count = 0;
}
/* 解析报文 */
void CM_AnlyMsg (DATA_StructType *msg)
{

}
void CM_ProcessReceData (void)
{
	switch (recdata.count-1){
		case QIZHI1:
			if(recdata.byte[recdata.count-1] == COM_QIZHI1){
			}else{
					recdata.count = 0;
			}
			break;
		case QIZHI2:
			if(recdata.byte[recdata.count-1] == COM_QIZHI2){
			}else{
					recdata.count = 0;
			}
			break;
		case MAINPCB:
			if(recdata.byte[recdata.count-1] == COM_MAINPCB){
			}else{
					recdata.count = 0;
			}
			break;
		case SLPCB:
			if(recdata.byte[recdata.count-1] == COM_SLPCB){
			}else{
					recdata.count = 0;
			}
			break;
		case SIZE:
			
			break;
		case CMD:
			break;
		case DATAS:
			break;
		default:
			break;
	}
}
void CM_ReceiveData(uint8_t ch)
{
	recdata.byte[recdata.count] = ch;
	recdata.count += 1;
	CM_ProcessReceData ();
}
/*********************************END OF FILE****************************/


