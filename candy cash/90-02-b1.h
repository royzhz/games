/*2050271 –≈20 ’≈Ó£*/
#pragma once

struct cell
{
	int num = 0;
	int open = 2;
};

int cmd_begin(int mode, int hang, int lie);
int g_begin(int mode, int hang, int lie);
void g_cell(int line, int column,int mode);
void g_cell_move_line(int line, int column, int d_line, int d_column, cell table[12][12]);
void g_cell_move_column(int line, int column, int d_line, int d_column, cell table[12][12]);
void setcellcolor(cell table[12][12], int color, int line, int column, int mode);
