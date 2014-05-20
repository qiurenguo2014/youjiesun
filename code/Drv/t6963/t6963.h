#ifndef __BSP_T6963_H__
#define __BSP_T6963_H__

#ifndef __BSP_T6963_C__
#define __BSP_T6963_C__	extern
#endif

#define T6963DEBUG 0

#define LCD_CURSOR              0x21
#define LCD_OFFSET              0x22
#define LCD_ADDRESS             0x24
#define LCD_TEXTHOME            0x40
#define LCD_TEXTAREA            0x41
#define LCD_GFXHOME             0x42
#define LCD_GFXAREA             0x43
#define LCD_ORMODE              0x80
#define LCD_XORMODE             0x81
#define LCD_ANDMODE             0x83
#define LCD_ATTRMODE            0x84
#define LCD_DISPLAY             0x90
#define LCD_CLINES              0xA0
#define LCD_AUTOWRITE           0xB0
#define LCD_AUTOREAD            0xB1
#define LCD_AUTORESET           0xB2
#define LCD_WRITEINC            0xC0
#define LCD_READINC             0xC1
#define LCD_WRITEDEC            0xC2
#define LCD_READDEC             0xC3
#define LCD_SCREENPEEK          0xE0
#define LCD_SCREENCOPY          0xE8
#define LCD_BITSET              0xF0
#define CTRL                    0x01
#define DATA                    0x00


#define LCD_ROW_BYTES			30			//lie
#define LCD_COLUMN_BYTES		128			//hang
#define LCD_ROW_DOT				LCD_ROW_BYTES*8
#define LCD_COLUMN_DOT			LCD_COLUMN_BYTES


#define LCD_BUS	 				GPIOD
#define LCD_BL					GPIOB
#define LCD_CD	 				GPIOC
#define LCD_CE					GPIOC
#define LCD_WR					GPIOA
#define LCD_RD					GPIOC

#define LCD_BUS_PIN  			0x00FF
#define LCD_BL_Pin				GPIO_Pin_3
#define LCD_CD_Pin	 			GPIO_Pin_12
#define LCD_CE_Pin	 			GPIO_Pin_11
#define LCD_WR_Pin	 			GPIO_Pin_15
#define LCD_RD_Pin	 			GPIO_Pin_10

#define LCD_BUS_RCC	 			RCC_APB2Periph_GPIOD
#define LCD_BL_RCC				RCC_APB2Periph_GPIOB
#define LCD_CD_RCC	 			RCC_APB2Periph_GPIOC
#define LCD_CE_RCC				RCC_APB2Periph_GPIOC
#define LCD_WR_RCC				RCC_APB2Periph_GPIOA
#define LCD_RD_RCC				RCC_APB2Periph_GPIOC


#define LCD_CE_SET   			GPIO_WriteBit(LCD_CE, LCD_CE_Pin, Bit_SET)
#define LCD_CE_CLR   			GPIO_WriteBit(LCD_CE, LCD_CE_Pin, Bit_RESET)
#define LCD_CD_SET   			GPIO_WriteBit(LCD_CD, LCD_CD_Pin, Bit_SET)
#define LCD_CD_CLR   			GPIO_WriteBit(LCD_CD, LCD_CD_Pin, Bit_RESET)
#define LCD_RD_SET   			GPIO_WriteBit(LCD_RD, LCD_RD_Pin, Bit_SET)
#define LCD_RD_CLR   			GPIO_WriteBit(LCD_RD, LCD_RD_Pin, Bit_RESET)
#define LCD_WR_SET   			GPIO_WriteBit(LCD_WR, LCD_WR_Pin, Bit_SET)
#define LCD_WR_CLR   			GPIO_WriteBit(LCD_WR, LCD_WR_Pin, Bit_RESET)
#define LCD_LED_ON				//GPIO_WriteBit(LCD_BL, LCD_BL_Pin, Bit_SET)
#define LCD_LED_OFF				//GPIO_WriteBit(LCD_BL, LCD_BL_Pin, Bit_RESET)

typedef struct{
    unsigned char lcdBuffer[LCD_COLUMN_BYTES*LCD_ROW_BYTES];
}LCD_StructType;

__BSP_T6963_C__ LCD_StructType lcd,*plcd;
__BSP_T6963_C__ void T6963_ScreenUpdate(LCD_StructType *p);
__BSP_T6963_C__ void T6963_ScreenUpdata (void);
__BSP_T6963_C__ void T6963_Configuration (void);


#endif

