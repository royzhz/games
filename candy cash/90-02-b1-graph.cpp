/*2050271 ��20 ���*/
#include <iostream>
#include <ctime>
#include<windows.h>
#include "../include/cmd_console_tools.h"
#include"90-02-b1.h"
#include "../include/common_input.h"
#include "../include/common_output.h"
using namespace std;


void setcellcolor(cell table[12][12], int color, int line, int column, int mode)//1Ϊѡ��2Ϊ���
{
	for (int i = 1; i < line + 1; i++)
	{
		for (int j = 1; j < column + 1; j++)
		{
			if (table[i][j].open == 1)
			{
				if (mode == 1)
				{
					cct_setcolor(table[i][j].num + 1, color);
					g_cell(i, j, 1);

				}
				if (mode == 2)
				{
					cct_setcolor(15, 0);
					g_cell(i, j, 3);
				}
			}
		}
	}
}

void g_cell(int line, int column, int mode)//1Ϊ������2ΪE,3Ϊ���
{
	if (mode == 1)
	{
		cct_gotoxy(column * 6 - 2, line * 3);
		cout << "�X�T�[";
		cct_gotoxy(column * 6 - 2, line * 3 + 1);
		cout << "�U��U";
		cct_gotoxy(column * 6 - 2, line * 3 + 2);
		cout << "�^�T�a";
	}
	else if (mode == 2)
	{
		cct_gotoxy(column * 8 - 4, line * 4 - 1);
		cout << "�X�T�[";
		cct_gotoxy(column * 8 - 4, line * 4 - 0);
		cout << "�U��U";
		cct_gotoxy(column * 8 - 4, line * 4 + 1);
		cout << "�^�T�a";
	}
	else if (mode == 3)
	{
		cct_gotoxy(column * 6 - 2, line * 3);
		cout << "      ";
		cct_gotoxy(column * 6 - 2, line * 3 + 1);
		cout << "      ";
		cct_gotoxy(column * 6 - 2, line * 3 + 2);
		cout << "      ";
	}
}

void g_cell_move_line(int line, int column, int d_line, int d_column, cell table[12][12])
{

	for (int i = line * 3; i < d_line * 3; i++)
	{
		Sleep(10);
		cct_gotoxy(column * 6 - 2, i);
		cct_setcolor(15, 15);
		cout << "      ";
		cct_setcolor(table[line][column].num + 1, 0);
		cct_gotoxy(column * 6 - 2, i + 1);
		cout << "�X�T�[";
		cct_gotoxy(column * 6 - 2, i + 2);
		cout << "�U��U";
		cct_gotoxy(column * 6 - 2, i + 3);
		cout << "�^�T�a";
	}
}

void g_cell_move_column(int line, int column, int d_line, int d_column, cell table[12][12])
{
	for (int i = column * 6 - 3; i > d_column * 6 - 3; i--)
	{
		Sleep(5);
		cct_setcolor(table[line][column].num + 1, 0);
		cct_gotoxy(i, line * 3);
		cout << "�X�T�[";
		cct_gotoxy(i, line * 3 + 1);
		cout << "�U��U";
		cct_gotoxy(i, line * 3 + 2);
		cout << "�^�T�a";
		cct_setcolor(15, 15);
		cct_gotoxy(i+6, line * 3);
		cout << " ";
		cct_gotoxy(i+6, line * 3 + 1);
		cout << " ";
		cct_gotoxy(i+6, line * 3 + 2);
		cout << " ";
	}
}
