/*2050271 信20 张睿*/
#include <iostream>
#include <conio.h>
#include <iomanip>
#include "../include/cmd_console_tools.h"
using namespace std;

struct cell
{
	int num = 0;
	int open = 2;
};

void cmd_print(int column, int line, const char linename[])
{
	cout << "  |";
	for (int i =0; i < column; i++)
	{
		cout << linename[i]<<" ";
	}
	cout << endl;
	cout << "--+";
	for (int i = 0; i < column * 2 + 1; i++)
		cout << "-";
	cout << endl;
}





void cmd_print(int line , int column,cell table[12][12], int mode,const char linename[],const char columnname[])//1输出num,0输出open,2输出彩色
{
	cmd_print(column, line,linename);
	for (int x = 1; x < line + 1; x++)
	{
		cout << columnname[x-1]<< " |";
		for (int y =1; y < column + 1; y++)
		{

			if (mode == 1)
				cout << table[x][y].num << ' ';
			if (mode == 0)
				cout << table[x][y].open << ' ';
			if (mode == 2)
			{
				if (table[x][y].open!=0)
				{
					cct_setcolor(3, 7);
					cout << table[x][y].num;
					cct_setcolor();
					cout << ' ';
				}
				else
					cout << table[x][y].num << ' ';
			}
		}
		cout << endl;
	}
	cout << endl << endl;
}


void gmap(int line, int column, int size_line, int size_column, int mode)//1为不画骨架，2为花骨架
{
	cct_setfontsize("新宋体", 14);

	if (mode == 2)
	{
		size_line++;
		size_column=size_column+2;
	}

	//cct_setconsoleborder(column * (size_column)+7, line * (size_line)+15);


	cct_gotoxy(0, 1);
	for (int i = 0; i < column; i++)
	{
		cout << setw(size_column) << i;
	}
	for (int i = 0; i < line; i++)
	{
		cct_gotoxy(0, i * size_line + 4);
		cout << char('A' + i);
	}

	cct_setcolor(15, 8);

	if (mode == 1)
	{
		cct_gotoxy(2, 2);
		cout << "╔";
		for (int i = 0; i < column * size_column / 2; i++)
			cout << "═";
		cout << "╗" << endl;
		for (int i = 0; i <= line* size_line; i++)
		{
			cct_gotoxy(2, i + 3);
			cout << "║" << endl;
			cct_gotoxy(column * size_column + 4, i + 3);
			cout << "║" << endl;
		}
		cct_gotoxy(2, line * size_line + 3);
		cout << "╚";
		for (int i = 0; i < column * size_column / 2; i++)
			cout << "═";
		cout << "╝" << endl;
	}

	if (mode == 2)
	{
		cct_gotoxy(2, 2);
		cout << "╔";
		for (int i = 0; i < column * size_column / 2 - 1; i++)
				cout << "═";
		cout << "╗" << endl;
		for (int i = 0; i <= line * size_line-1; i++)
		{
			cct_gotoxy(2, i + 3);
			cout << "║" << endl;
			cct_gotoxy(column * size_column + 2, i + 3);
			cout << "║" << endl;
		}
		cct_gotoxy(2, line * size_line + 2);
		cout << "╚";
		for (int i = 0; i < column * size_column / 2-1; i++)
			cout << "═";
		cout << "╝" << endl;

		for (int j = 2+size_column; j < column * (size_column); j = j + size_column)
		{
			cct_gotoxy(j,2);
			cout << "╦";
			for (int i = 0; i < line * size_line; i++)
			{
				cct_gotoxy(j, i + 3);
				cout << "║" << endl;
			}
			cct_gotoxy(j, line* size_line+2);
			cout << "╩";
		}


		for (int j = 2 + size_line; j < line * size_line + 2; j = j + size_line)
		{
			cct_gotoxy(2, j);
			cout << "╠";
			for (int i = 0; i < column * size_column / 2 - 1; i++)
				if (i % (size_column - 4) == 3)
					cout << "╬";
				else
					cout << "═";
			cout << "╣" << endl;

		}

		cct_setcolor();
	}
}