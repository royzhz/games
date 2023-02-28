/*2050271 ��20 ���*/
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





void cmd_print(int line , int column,cell table[12][12], int mode,const char linename[],const char columnname[])//1���num,0���open,2�����ɫ
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


void gmap(int line, int column, int size_line, int size_column, int mode)//1Ϊ�����Ǽܣ�2Ϊ���Ǽ�
{
	cct_setfontsize("������", 14);

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
		cout << "�X";
		for (int i = 0; i < column * size_column / 2; i++)
			cout << "�T";
		cout << "�[" << endl;
		for (int i = 0; i <= line* size_line; i++)
		{
			cct_gotoxy(2, i + 3);
			cout << "�U" << endl;
			cct_gotoxy(column * size_column + 4, i + 3);
			cout << "�U" << endl;
		}
		cct_gotoxy(2, line * size_line + 3);
		cout << "�^";
		for (int i = 0; i < column * size_column / 2; i++)
			cout << "�T";
		cout << "�a" << endl;
	}

	if (mode == 2)
	{
		cct_gotoxy(2, 2);
		cout << "�X";
		for (int i = 0; i < column * size_column / 2 - 1; i++)
				cout << "�T";
		cout << "�[" << endl;
		for (int i = 0; i <= line * size_line-1; i++)
		{
			cct_gotoxy(2, i + 3);
			cout << "�U" << endl;
			cct_gotoxy(column * size_column + 2, i + 3);
			cout << "�U" << endl;
		}
		cct_gotoxy(2, line * size_line + 2);
		cout << "�^";
		for (int i = 0; i < column * size_column / 2-1; i++)
			cout << "�T";
		cout << "�a" << endl;

		for (int j = 2+size_column; j < column * (size_column); j = j + size_column)
		{
			cct_gotoxy(j,2);
			cout << "�j";
			for (int i = 0; i < line * size_line; i++)
			{
				cct_gotoxy(j, i + 3);
				cout << "�U" << endl;
			}
			cct_gotoxy(j, line* size_line+2);
			cout << "�m";
		}


		for (int j = 2 + size_line; j < line * size_line + 2; j = j + size_line)
		{
			cct_gotoxy(2, j);
			cout << "�d";
			for (int i = 0; i < column * size_column / 2 - 1; i++)
				if (i % (size_column - 4) == 3)
					cout << "�p";
				else
					cout << "�T";
			cout << "�g" << endl;

		}

		cct_setcolor();
	}
}