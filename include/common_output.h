/*2050271 ��20 ���*/
#pragma once

struct cell;
void cmd_print(int column, int line, const char linename[]);
void cmd_print(int line, int column, cell table[12][12], int mode, const char linename[], const char columnname[]);//1���num,0���open,2�����ɫ
void gmap(int line, int column, int size_line, int size_column, int mode);