/*************************************************************************
#    FileName: commu.c
#      Author: Allen
#       Email: qiurenguo@gmail.com
#    HomePage: Allen
#       Brief: 
#  LastChange: 2014-05-17 16:56:19
*************************************************************************/
/* Includes ------------------------------------------------------------*/
#include "sigop.h"
#include "commu.h"
/* Types ---------------------------------------------------------------*/
/* Constants -----------------------------------------------------------*/
/* Define --------------------------------------------------------------*/
/* Variables -----------------------------------------------------------*/
DATA_StructType recdata;
DATA_StructType senddata;
/* Functions prototypes ------------------------------------------------*/
extern void USART3_SendData(uint8_t ch);
/* Functions -----------------------------------------------------------*/
/*
@brief  
@param  None.
@retval None.
*/
void CM_Init (void)
{

}
void CM_ClearSuccess (DATA_StructType *p)
{
	p->status &= ~COM_STTS_SUCCESS;
}
void CM_ClearCount (DATA_StructType *p)
{
	p->count = 0;
}
void CM_SetSuccess (DATA_StructType *p)
{
	p->status |= COM_STTS_SUCCESS;
}
void CM_SendData (void)
{
	uint16_t i,j;
	i = senddata.byte[SIZE]+5;
	for(j=0; j<i; j++){
		USART3_SendData (senddata.byte[j]);
		printf("%x",senddata.byte[j]);
	}
}
/* 发送测量交流电压信号 */
void CM_SendVread (void)
{
	uint8_t *data;
	uint8_t i=0;
	
	data = (uint8_t *)&sig.prefre;
	
	senddata.byte[QIZHI1] = COM_QIZHI1;
	senddata.byte[QIZHI2] = COM_QIZHI2;
	senddata.byte[MAINPCB] = COM_MAINPCB;
	senddata.byte[SLPCB] = COM_SLPCB;
	senddata.byte[SIZE] = 1+sizeof(sig.prefre);
	senddata.byte[SIZE+i] = EstartV_main;
	for(; i<senddata.byte[SIZE]; i++){
		senddata.byte[SIZE+i] = data[i];
	}
	CM_SendData ();
}
void CM_AnlyMsg (DATA_StructType *msg)
{

}
void CM_ProcessRecData (DATA_StructType *msg)
{
	static uint8_t size;
	switch (msg->count-1){
		case QIZHI1:
			if(msg->byte[QIZHI1] != COM_QIZHI1){
				CM_ClearCount (msg);
				DPrintf ("error1\r\n");
			}
			break;
		case QIZHI2:
			if(msg->byte[QIZHI2] != COM_QIZHI2){
				CM_ClearCount (msg);
				DPrintf ("error2\r\n");
			}
			break;
		case MAINPCB:
			if(msg->byte[MAINPCB] != COM_MAINPCB){
				CM_ClearCount (msg);
				DPrintf ("error3\r\n");
			}
			break;
		case SLPCB:
			if(msg->byte[SLPCB] != COM_SLPCB){
				CM_ClearCount (msg);
				DPrintf ("error4\r\n");
			}
			break;
		case SIZE:
			size = msg->byte[SIZE];
			break;
		case CMD:
			if(size != 0){
				size --;
			}
			break;
		default:
			if(size != 0){
				size --;
			}else{
				CM_SetSuccess(msg);
			}
			break;
	}
}
void CM_ReceiveData(uint8_t ch)
{
	recdata.byte[recdata.count] = ch;
	recdata.count += 1;
	CM_ProcessRecData (&recdata);
}
/*********************************END OF FILE****************************/


