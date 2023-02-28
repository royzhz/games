/*2050271 信20 张睿*/
#pragma once

struct cell;
void cmd_print(int column, int line, const char linename[]);
void cmd_print(int line, int column, cell table[12][12], int mode, const char linename[], const char columnname[]);//1输出num,0输出open,2输出彩色
void gmap(int line, int column, int size_line, int size_column, int mode);