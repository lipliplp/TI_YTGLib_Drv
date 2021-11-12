#ifndef __OLED_H_
#define __OLED_H_

#include <msp430.h>

#define OLED_MODE 0
#define SIZE 8
#define XLevelL     0x00
#define XLevelH     0x10
#define Max_Column  128
#define Max_Row     64
#define Brightness  0xFF
#define X_WIDTH     128
#define Y_WIDTH     64

#define OLED_SCLK_Clr() P6OUT&=~BIT3  //CLK
#define OLED_SCLK_Set() P6OUT|=BIT3

#define OLED_SDIN_Clr() P6OUT&=~BIT4  //DIN
#define OLED_SDIN_Set() P6OUT|=BIT4

#define OLED_CMD  0
#define OLED_DATA 1


// Functions to control OLED are as follows
void OLED_WR_Byte(unsigned dat,unsigned cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(unsigned char x,unsigned char y,unsigned char t);
void OLED_Fill(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char dot);
void OLED_ShowChar(unsigned char x,unsigned char y,unsigned char chr,unsigned char Char_Size);
void OLED_ShowNum(unsigned char x,unsigned char y,unsigned int num,unsigned char len,unsigned char size);
void OLED_ShowVI(unsigned char x,unsigned char y,unsigned int num,unsigned char size);
void OLED_ShowString(unsigned char x,unsigned char y, unsigned char *p,unsigned char Char_Size);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void fill_picture(unsigned char fill_Data);
void Picture();
void IIC_Start();
void IIC_Stop();
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);
void IIC_Wait_Ack();

#endif /* _OLED_H_ */
