
/*  -------------------------Includes-----------------------------------------*/
#include "My_InitTask.h" 
#include "..\drv\t6963\t6963.h"
#include "..\drv\fm31256\fm31256.h"
#include "..\drv\tda7396\tda7396.h"
#include "bsp_relay.h"
#include "bsp_i2c.h"
#include "bsp_systick.h"
#include "bsp_pwm.h"
#include "bsp_dac.h"
#include "..\app\flashdata.h"
void BSP_BeepConfiguration (void);
void BSP_GndaskConfiguration(void);
/*  -------------------------Functions-----------------------------------------*/

/**** stm32的初始化工作全部在这里完成  *****/
void My_InitTask(void)
{
   /* Configure the system clocks */ 
  	RCC_Configuration();
	NVIC_Configuration ();	
	/* PA09 PA10 UART1 */
	USART_Configuration ();
	/* PD8 9 采集板和显示板通信*/
	UCOM_Configuration ();
	SYSTICK_Configuration ();
	/* shell port*/
	SHL_Init ();
	/*AC DC输出  PA5(DA)  PB13(VLOSE_IO) PB12(HDCOUT) */
	DA_Configuration ();
	/* 温度采集初始化 PA7(FREQ TIM3CH2) */
	PWM_Configuration ();
	/* 温度升降指示灯 PB8.9(UP DOWN TEMP LED 关闭) PE9 pwm*/
	PWMT_Configuration ();
	/* 工频频率测量 PD12*/
	HN220V_Configuration ();
	/* PB14 PD14 过流 过温配置 开中断*/
	OVETI_Configuration ();
	/* t6963 */
	T6963_Configuration ();	
	/* beep */
	BSP_BeepConfiguration ();	
	/* fm31256 */
	I2C_Configuration ();
	FM31256_Init ();
	FD_Init ();
	/* relay */
	RL_Configuration();
	/* tda 7396 PE11 PD13 开PE11中断*/
	TDA7396_Init ();
	/*接地检测初始化*/
	BSP_GndaskConfiguration ();
}
/* 接地检测 高电平未接地 */
void BSP_GndaskConfiguration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_SetBits (GPIOD, GPIO_Pin_15);
}
/*
@brief  beep init.
@param  None.
@retval None.
*/
void BSP_BeepConfiguration (void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_ResetBits (GPIOB, GPIO_Pin_3);
}
/*
@brief  open beep.
@param  None.
@retval None.
*/
void BSP_BeepOpen (void)
{
	GPIO_SetBits (GPIOB,GPIO_Pin_3);
}
/*
@brief  close beep.
@param  None.
@retval None.
*/
void BSP_BeepClose (void)
{
	GPIO_ResetBits (GPIOB, GPIO_Pin_3);
}
void BSP_BeepKeyDelay(void)
{
	uint32_t i = 500000;
	BSP_BeepOpen ();
	while(i--);
	BSP_BeepClose ();
}
/*
@brief  system reset , (shell port).
@param  None.
@retval None.
*/
void Bsp_SystemReset (void)
{
	NVIC_SystemReset ();
}
void NVIC_Configuration(void)
{
	static NVIC_InitTypeDef NVIC_InitStructure;
	//NVIC_InitTypeDef NVIC_InitStructure;

#ifdef  VECT_TAB_RAM  
	/* Set the Vector Table base location at 0x20000000 */ 
	NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH  */
	/* Set the Vector Table base location at 0x08000000 */ 
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x2000);   
#endif
	NVIC_SetPriorityGrouping (5);//抢占式优先级(0~3),亚优先级(0~3)
	//NVIC_SetPriority(UART3_RX_TX_IRQn,NVIC_EncodePriority(5,1,2));
	NVIC_SetPriority(SysTick_IRQn,NVIC_EncodePriority(5,1,3));
	/* Configure one bit for preemption priority */
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0 ;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	/* Enable the EXTI15_10 Interrupt tda7396 wrong*/
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	/* 捕获 */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	

}
void RCC_Configuration(void)
{
  ErrorStatus HSEStartUpStatus;

  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)
  {
    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */ 
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
}




// #include "core_cm3.h"
// void SysTick_Configuration(void)
// {
//   /* Select AHB clock(HCLK) as SysTick clock source */
//   SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
// 	SysTick->LOAD  = 72000000/1000;//CLOCKS_PER_SEC - 1;       /* set reload register */1ms
// 	SysTick->VAL   = 0;                                          /* Load the SysTick Counter Value */
// 	SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
// 				SysTick_CTRL_TICKINT_Msk   |
// 				SysTick_CTRL_ENABLE_Msk;                    /* Enable SysTick IRQ and SysTick Timer */
// 	//SysTick_Config (1000);

// }
// static __INLINE uint32_t SysTick_Config(uint32_t ticks)
// { 
//   if (ticks > SysTick_LOAD_RELOAD_Msk)  return (1);            /* Reload value impossible */
//                                                                
//   SysTick->LOAD  = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;      /* set reload register */
//   NVIC_SetPriority (SysTick_IRQn, (1<<__NVIC_PRIO_BITS) - 1);  /* set Priority for Cortex-M0 System Interrupts */
//   SysTick->VAL   = 0;                                          /* Load the SysTick Counter Value */
//   SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | 
//                    SysTick_CTRL_TICKINT_Msk   | 
//                    SysTick_CTRL_ENABLE_Msk;                    /* Enable SysTick IRQ and SysTick Timer */
//   return (0);                                                  /* Function successful */
// }

















