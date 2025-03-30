#ifndef _CONTROL_H
#define _CONTROL_H
#include "mk60_sys.h"
#include "ov7725.h"
#include "oled.h"

extern u16 left[ROW],right[ROW],mid[ROW];
extern u16 correct_line;
extern u16 lose_left,lose_right;
extern u16 shizi_start;

extern int limit_row(int x);
void get_mid(void);
void shizi_handle(void);
 
#endif
