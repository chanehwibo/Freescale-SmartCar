#ifndef _OLED_H
#define _OLED_H
#include "mk60_sys.h"

#define OLED_Width  128
#define OLED_Height 64


#define OLED_SCL  PCout(16)  
#define OLED_SDA  PCout(17)  
#define OLED_RST  PCout(18)  
#define OLED_DC   PCout(19) 

void OLED_RefreshGRAM(void);
void OLED_WR_CMD(u8 cmd);
void OLED_WR_DATA(u8 data);
void OLED_SetPos(u8 x,u8 y);
void OLED_DrawPoint(u8 x,u8 y,u8 mode);
u8 OLED_ReadPoint(u8 x,u8 y);
void OLED_Clear(u8 clear);
void OLED_Init(void);

void OLED_ShowChar(u8 x,u8 y,u8 num,u8 size);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowxNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowFont(u8 x,u8 y,u8 *fontL,u8 *fontH,u8 size);
void OLED_ShowStr(u8 x,u8 y,u8 width,u8 height,u8*str,u8 size);
void OLED_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u8 mode);
void OLED_DrawRectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 mode);
void OLED_Fill(u8 x,u8 y,u8 width,u8 height,u8 mode);
void OLED_DrawCircle(int x0,int y0,int r,int type,u8 mode);
void ShowClass(u8 x,u8 y,u8 width,u8 height,u8 press);
void DrawBitMap(u8 *pbuf,u8 *title);
#endif
