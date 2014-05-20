#define __BSP_T6963_C__
#include "stm32f10x.h"
#include "t6963.h" 

unsigned char flag_updata=0;//0 不刷新 1刷新
static void RCC_Configuration(void) ;
static void GPIO_Configuration(void) ;
unsigned char T6963_ReadData (int ctrl);
static void T6963_WriteData (int ctrl, unsigned char val);
static void T6963_WriteCmd (unsigned char cmd);
static void T6963_WriteCmd (unsigned char cmd);
static void T6963_WriteByteCmd (unsigned char cmd, unsigned char data) ;
static void T6963_WriteWordCmd (unsigned char cmd, unsigned short arg);
static void LCDStructInit(LCD_StructType *p);

#if T6963DEBUG
static void delay_T6963 (void);
#endif
void T6963_SetDot (int X_coor, int Y_coor, int color)
{
	u32 divisor;
	u32 residue;
	u8 dot = 0x80;
	flag_updata = 1;
	/* X有30个字节 每个8 */
	divisor = X_coor/8;
	/* 移位 */
	residue = X_coor%8;
	dot >>= residue;
	/* 第几行+第几列 */
	if(color == 0){
		lcd.lcdBuffer[Y_coor*LCD_ROW_BYTES + divisor] |= dot;
	}else{
		lcd.lcdBuffer[Y_coor*LCD_ROW_BYTES + divisor] &= (~dot);
	}
	
}
unsigned char T6963_GetDot (int X_coor, int Y_coor)
{
	u32 divisor;
	u32 residue;
	u8 dot = 0x80;
	divisor = X_coor/8;
	residue = X_coor%8;
	dot >>= residue;
	if(lcd.lcdBuffer[Y_coor*LCD_ROW_BYTES + divisor] & dot){
		return 0;
	}
	return 1;
}
void T6963_ScreenUpdata (void)
{
	unsigned char col, row;
	if (flag_updata == 0){
	}else{
		flag_updata = 0;
	T6963_WriteWordCmd(LCD_ADDRESS, 0);
	T6963_WriteCmd(LCD_AUTOWRITE);
	for(col=0; col<LCD_COLUMN_BYTES; col++) {
		for(row=0; row<LCD_ROW_BYTES; row++) {
			
#if T6963DEBUG
	delay_T6963();
#else
	while ((T6963_ReadData(CTRL) & 0x08) == 0){};//BUSY
#endif
			
			LCD_BUS->BRR = LCD_BUS_PIN;
			LCD_BUS->BSRR = (u16)(lcd.lcdBuffer[col*LCD_ROW_BYTES+row]&0xff);
			LCD_CD_CLR;						//DATA
			LCD_CE_CLR;						//CE=0
			LCD_WR_CLR;
			LCD_WR_SET;
			LCD_CE_SET;						//CE=1
		}
	}
	T6963_WriteCmd(LCD_AUTORESET);
}
}
void T6963_ScreenUpdate(LCD_StructType *p) 
{
	unsigned char col, row;
	T6963_WriteWordCmd(LCD_ADDRESS, 0);
	T6963_WriteCmd(LCD_AUTOWRITE);
	for(col=0; col<LCD_COLUMN_BYTES; col++) {
		for(row=0; row<LCD_ROW_BYTES; row++) {
			
#if T6963DEBUG
	delay_T6963();
#else
	while ((T6963_ReadData(CTRL) & 0x08) == 0){};//BUSY
#endif
			
			LCD_BUS->BRR = LCD_BUS_PIN;
			LCD_BUS->BSRR = (u16)(p->lcdBuffer[col*LCD_ROW_BYTES+row]&0xff);
			LCD_CD_CLR;						//DATA
			LCD_CE_CLR;						//CE=0
			LCD_WR_CLR;
			LCD_WR_SET;
			LCD_CE_SET;						//CE=1
		}
	}
	T6963_WriteCmd(LCD_AUTORESET);
}

#if T6963DEBUG
static void delay_T6963 (void)
{
	unsigned int a = 15;
	while(a--);
}
#endif

unsigned char T6963_ReadData (int ctrl) {
	unsigned char result;
	LCD_BUS->BSRR = LCD_BUS_PIN;
	if (ctrl)
		LCD_CD_SET;		// CD
	else
		LCD_CD_CLR;
	LCD_CE_CLR;			// CE = 0
	LCD_RD_CLR;			// RD = 0
	result = GPIO_ReadInputData(LCD_BUS);
	LCD_RD_SET;			// RD = 1
	LCD_CE_SET;			// CE = 1
	return (result);
}

static void T6963_WriteData (int ctrl, unsigned char val) {
	LCD_BUS->BRR = LCD_BUS_PIN&(u16)(~val);
	if(ctrl)
		LCD_CD_SET;		//CD
	else
		LCD_CD_CLR;
	LCD_CE_CLR;			//CE=0
	LCD_WR_CLR;
	LCD_WR_SET;
	LCD_CE_SET;			//CE=1
	LCD_BUS->BSRR = LCD_BUS_PIN;
}

static void T6963_WriteCmd (unsigned char cmd) {
	//while ((T6963_ReadData(CTRL) & 0x01) == 0);
#if T6963DEBUG
	delay_T6963();
#else
	while ((T6963_ReadData(CTRL) & 0x01) == 0);
#endif
	T6963_WriteData(CTRL, cmd);
}

static void T6963_WriteByteCmd (unsigned char cmd, unsigned char data) {
	//while ((T6963_ReadData(CTRL) & 0x02) == 0);
#if T6963DEBUG
	delay_T6963();
#else
	while ((T6963_ReadData(CTRL) & 0x02) == 0);
#endif
	T6963_WriteData(DATA, data);
	//while ((T6963_ReadData(CTRL) & 0x01) == 0);
#if T6963DEBUG
	delay_T6963();
#else
	while ((T6963_ReadData(CTRL) & 0x01) == 0);
#endif
	T6963_WriteData(CTRL, cmd);
}

static void T6963_WriteWordCmd (unsigned char cmd, unsigned short arg) {
	//while ((T6963_ReadData(CTRL) & 0x02) == 0);
#if T6963DEBUG
	delay_T6963();
#else
	while ((T6963_ReadData(CTRL) & 0x02) == 0);
#endif
	T6963_WriteData(DATA, arg & 0xFF);
	//while ((T6963_ReadData(CTRL) & 0x02) == 0);
#if T6963DEBUG
	delay_T6963();
#else
	while ((T6963_ReadData(CTRL) & 0x02) == 0);
#endif
	T6963_WriteData(DATA, arg >> 8);
	//while ((T6963_ReadData(CTRL) & 0x01) == 0);
#if T6963DEBUG
	delay_T6963();
#else
	while ((T6963_ReadData(CTRL) & 0x01) == 0);
#endif
	T6963_WriteData(CTRL, cmd);
}
static void RCC_Configuration(void) 
{
	RCC_APB2PeriphClockCmd(LCD_BL_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(LCD_CD_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(LCD_CE_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(LCD_WR_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(LCD_RD_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(LCD_BUS_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
}

static void GPIO_Configuration(void) 
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
 	GPIO_InitStructure.GPIO_Pin = LCD_BL_Pin;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 	//GPIO_Init(LCD_BL, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LCD_CD_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(LCD_CD, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LCD_CE_Pin;
	GPIO_Init(LCD_CE, &GPIO_InitStructure);


	GPIO_InitStructure.GPIO_Pin = LCD_WR_Pin;
	GPIO_Init(LCD_WR, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = LCD_RD_Pin;
	GPIO_Init(LCD_RD, &GPIO_InitStructure);
	LCD_CE_SET;
	LCD_CD_SET;
	LCD_RD_SET;
	LCD_WR_SET;
	GPIO_InitStructure.GPIO_Pin = LCD_BUS_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_Init(LCD_BUS, &GPIO_InitStructure);
	GPIO_SetBits(LCD_BUS, LCD_BUS_PIN);
}

static void LCDStructInit(LCD_StructType *p)
{
	unsigned int col,row;		
	for(col=0; col < LCD_COLUMN_BYTES; col++) {
		for(row = 0; row < LCD_ROW_BYTES; row++) {
			p->lcdBuffer[col*LCD_ROW_BYTES+row] = 0x0;
		}
	}	
}

void T6963_Configuration(void) {
	RCC_Configuration ();
	GPIO_Configuration();
	T6963_WriteCmd(LCD_AUTORESET);
	// Graphics screen has 32 bytes per row, and resides at address 0
	T6963_WriteWordCmd(LCD_GFXHOME,  0x0000);
	T6963_WriteWordCmd(LCD_GFXAREA, 30);
	T6963_WriteWordCmd(LCD_TEXTHOME, 0x3840);
	T6963_WriteWordCmd(LCD_TEXTAREA, 16);
	T6963_WriteWordCmd(LCD_OFFSET,0x3000>>11);
	// Load custom graphic for a black square
	T6963_WriteWordCmd(LCD_ADDRESS,  0x3400);
	T6963_WriteByteCmd(LCD_WRITEINC, 0xFF);
	T6963_WriteByteCmd(LCD_WRITEINC, 0xFF);
	T6963_WriteByteCmd(LCD_WRITEINC, 0xFF);
	T6963_WriteByteCmd(LCD_WRITEINC, 0xFF);
	T6963_WriteByteCmd(LCD_WRITEINC, 0xFF);
	T6963_WriteByteCmd(LCD_WRITEINC, 0xFF);
	T6963_WriteByteCmd(LCD_WRITEINC, 0xFF);
	T6963_WriteByteCmd(LCD_WRITEINC, 0xFF);
	// Disable text and Enable graphics modes, with XOR mode
	T6963_WriteCmd(LCD_DISPLAY+0x08);
	T6963_WriteCmd(LCD_XORMODE);
	LCDStructInit(&lcd);
	T6963_ScreenUpdate(&lcd);
	LCD_LED_ON;
}


