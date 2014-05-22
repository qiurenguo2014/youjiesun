/*
    FreeRTOS V7.0.0 - Copyright (C) 2011 Real Time Engineers Ltd.
	

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS tutorial books are available in pdf and paperback.        *
     *    Complete, revised, and edited pdf reference manuals are also       *
     *    available.                                                         *
     *                                                                       *
     *    Purchasing FreeRTOS documentation will not only help you, by       *
     *    ensuring you get running as quickly as possible and with an        *
     *    in-depth knowledge of how to use FreeRTOS, it will also help       *
     *    the FreeRTOS project to continue with its mission of providing     *
     *    professional grade, cross platform, de facto standard solutions    *
     *    for microcontrollers - completely free of charge!                  *
     *                                                                       *
     *    >>> See http://www.FreeRTOS.org/Documentation for details. <<<     *
     *                                                                       *
     *    Thank you for using FreeRTOS, and thank you for your support!      *
     *                                                                       *
    ***************************************************************************


    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation AND MODIFIED BY the FreeRTOS exception.
    >>>NOTE<<< The modification to the GPL is included to allow you to
    distribute a combined work that includes FreeRTOS without being obliged to
    provide the source code for proprietary components outside of the FreeRTOS
    kernel.  FreeRTOS is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
    more details. You should have received a copy of the GNU General Public
    License and the FreeRTOS license exception along with FreeRTOS; if not it
    can be viewed here: http://www.freertos.org/a00114.html and also obtained
    by writing to Richard Barry, contact details for whom are available on the
    FreeRTOS WEB site.

    1 tab == 4 spaces!

    http://www.FreeRTOS.org - Documentation, latest information, license and
    contact details.

    http://www.SafeRTOS.com - A version that is certified for use in safety
    critical systems.

    http://www.OpenRTOS.com - Commercial support, development, porting,
    licensing and training services.
*/
	

/* Standard includes. */
#include <stdio.h>


/* Library includes. */
#include "stm32f10x.h"
#include "stm32f10x_it.h"

/* user files  		*/
#include "gui.h"
#include "app\commun.h"
#include "bsp\My_InitTask.h"
#include "bsp\bsp_systick.h"
#include "bsp\bsp_dac.h"
#include "bsp\bsp_key.h"
#include "drv\t6963\t6963.h"
#include "drv\fm31256\fm31256.h"
void ProcessKeyMsg (void);
/*-----------------------------------------------------------*/
extern void MainTask (void);
extern void TimeUpdata (void);
/*-----------------------------------------------------------*/
void ProcessKeyMsg (void)
{
	uint8_t vk_msg;
	static uint8_t ent_cnt=0;
	vk_msg = GUI_Get_Keymsg();
		if(vk_msg == VK_ENTER){
		BSP_BeepKeyDelay ();
		GUI_SendKeyMsg(GUI_KEY_ENTER, 1);
		GUI_Exec1();
	}else if(vk_msg == VK_BACK){
		BSP_BeepKeyDelay ();
		GUI_SendKeyMsg(GUI_KEY_BACKSPACE, 1);
		GUI_Exec1();
	}else if(vk_msg == VK_DOWN){
		BSP_BeepKeyDelay ();
		GUI_SendKeyMsg(GUI_KEY_TAB, 1);
		GUI_Exec1();
	}else if(vk_msg == VK_UP){
		BSP_BeepKeyDelay ();
		GUI_SendKeyMsg(GUI_KEY_BACKTAB, 1);
		GUI_Exec1();
	}else if(vk_msg == (VK_ENTER|VK_LOOSE)){		
		ent_cnt=0;
		//GUI_SendKeyMsg(GUI_KEY_ENTER, 0);
	}else if(vk_msg == (VK_BACK|VK_LOOSE)){
		//GUI_SendKeyMsg(GUI_KEY_BACKSPACE, 0);	
	}else if(vk_msg == (VK_DOWN|VK_LOOSE)){
		//GUI_SendKeyMsg(GUI_KEY_TAB, 0);
	}else if(vk_msg == (VK_UP|VK_LOOSE)){
	}else if(vk_msg == (VK_PAIYOU|VK_LOOSE)){
	}else if(vk_msg == (VK_ENTER|VK_CONT)){		
		if(ent_cnt == 4){
			ent_cnt++;
			WM_NotifyParent(WM_GetFocussedWindow(), TestWin_GetTestNotifi());
		}else{
			ent_cnt++;
		}
		BSP_BeepKeyDelay ();
		GUI_SendKeyMsg(GUI_KEY_ENTER, 1);
		GUI_Exec1();
	}else if(vk_msg == (VK_BACK|VK_CONT)){
	}else if(vk_msg == (VK_DOWN|VK_CONT)){
		BSP_BeepKeyDelay ();
		GUI_SendKeyMsg(GUI_KEY_TAB, 1);
		GUI_Exec1();
	}else if(vk_msg == (VK_UP|VK_CONT)){
		BSP_BeepKeyDelay ();
		GUI_SendKeyMsg(GUI_KEY_BACKTAB, 1);
		GUI_Exec1();
	}
}
int main( void )				 
{
	uint8_t ch;
	static long jif_time=0;
	static long jif_exec;	
	My_InitTask();
	COM_Init ();
	MainTask ();
	while(1){
		if (GUI_Get_Keymsg_a()==VK_NOKEY){
		}else{
			ProcessKeyMsg ();
		}
		T6963_ScreenUpdata ();
		if(jif_time < jiffies){
			jif_time = jiffies + 1000;
			TimeUpdata ();
		}
		if(jif_exec < jiffies){
			jif_exec = jiffies + 1;
			GUI_Exec();
		}
	}
}
#define DPRINTF_EN 1
void DPrintf(const char *a,...)
{
#if DPRINTF_EN
	printf(a);
#endif
}

/*-----------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
/***********************  End of File ***************************************/
