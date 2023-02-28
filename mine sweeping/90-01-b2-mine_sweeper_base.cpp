/*2050271 信20 张睿*/
#include <iostream>
#include <ctime>
#include <windows.h>
#include "90-01-b2-mine_sweeper.h"
#include "../include/common_input.h"
#include "../include/common_output.h"
#include "../include/cmd_console_tools.h"
#include "../include/common_core.h"
using namespace std;

void confirmsize(int& size_x, int& size_y, int& number, int hard)
{
	size_x = 9;
	size_y = 9;
	number = 10;
	if (hard == 2)
	{
		size_x = 16;
		size_y = 16;
		number = 40;
	}
	if (hard == 3)
	{
		size_x = 16;
		size_y = 30;
		number = 99;
	}
}

int check(int table[18][32], int a, int b)//列出数字
{
	int i = 0;
	if (table[a - 1][b - 1] == 9)
		i++;
	if (table[a - 1][b] == 9)
		i++;
	if (table[a - 1][b + 1] == 9)
		i++;
	if (table[a][b - 1] == 9)
		i++;
	if (table[a][b + 1] == 9)
		i++;
	if (table[a + 1][b - 1] == 9)
		i++;
	if (table[a + 1][b] == 9)
		i++;
	if (table[a + 1][b + 1] == 9)
		i++;
	return i;
}

void checknum(int map[18][32], int hard)//检查数组
{
	int size_x, size_y, number;
	confirmsize(size_x, size_y, number, hard);
	for (int x = 1; x < size_x + 1; x++)
	{
		for (int y = 1; y < size_y + 1; y++)
		{
			if (map[x][y] != 9)
				map[x][y] = check(map, x, y);
		}
	}
}

void printopen(int map[18][32], int hard, int mode, int opennum[18][32])//画出数组
{
	cout << "内部数组：" << endl;
	int column = 16;
	if (hard == 1)
		column = 9;
	if (hard == 3)
		column = 30;
	int size_x, size_y, number;
	confirmsize(size_x, size_y, number, hard);

	cmd_print(size_y, size_x,"0123456789abcdefghijklmnopqrst");

	char i = 'A';
	for (int x = 1; x < size_x + 1; x++, i++)
	{
		cout << i << " |";
		for (int y = 1; y < size_y + 1; y++)
		{
			if (opennum[x][y] || mode == 1)
			{
				if (opennum[x][y] == 2)
				{
					cct_setcolor(4);
					cout << "X";

					cct_setcolor();
					cout << " ";
				}
				else if (map[x][y] != 9)
				{
					if (mode != 1)
						cct_setcolor(14, map[x][y] + 3);
					cout << map[x][y];
					cct_setcolor();
					cout << " ";
				}
				else
					cout << "* ";
			}
			else
				cout << "X ";
		}
		cout << endl;
	}
}

void gotodiduan(int hard)
{
	int size_x, size_y, number;
	confirmsize(size_x, size_y, number, hard);
	cct_gotoxy(0, size_x * 3+ 3);
	cct_setcolor();
}


void shurumode4(int& x, int& y, int& z, int hard,int opennum[18][32],int map[18][32],int mode, LARGE_INTEGER begin, LARGE_INTEGER tick)
{
	while (1)
	{
		shuru4(x, y, z, hard);
		if (x == '&')
		{
			cout << endl;
			shijian(begin, tick);
		}
		if (z == '!' && opennum[x][y] != 1)
			opennum[x][y] = 2;
		if (z == '#' && opennum[x][y] == 2)
			opennum[x][y]=0;
		if (z != 0|| (z == 0 && opennum[x][y] == 2))
			printopen(map, hard, mode, opennum);
		if (z == 0&&x!='&')
			break;
	}
}

void setlei(int map[18][32], int x, int y)
{
	map[x-1][y+1] = 10;
	map[x-1][y] = 10;
	map[x-1][y-1] = 10;
	map[x][y+1] = 10;
	map[x][y] = 10;
	map[x][y-1] = 10;
	map[x+1][y + 1] = 10;
	map[x+1][y] = 10;
	map[x+1][y - 1] = 10;
}

void open(int map[18][32], int x, int y, int opennum[18][32], int hard, int& s, int mode = 1)//打开函数
{
	int size_x, size_y, number;
	confirmsize(size_x, size_y, number, hard);
	if (x > 0 && x < size_x + 1 && y>0 && y < size_y + 1 && opennum[x][y] == 0)
		s++;
	opennum[x][y] = 1;
	if (mode > 6 && x > 0 && x < size_x + 1 && y>0 && y < size_y + 1)
	{
		gopengezi(map, x, y);
	}


	if (x > 0 && x < size_x + 1 && y>0 && y < size_y + 1 && map[x][y] == 0)
	{
		if (!opennum[x - 1][y - 1])
			open(map, x - 1, y - 1, opennum, hard, s, mode);
		if (!opennum[x - 1][y])
			open(map, x - 1, y, opennum, hard, s, mode);
		if (!opennum[x - 1][y + 1])
			open(map, x - 1, y + 1, opennum, hard, s, mode);
		if (!opennum[x][y + 1])
			open(map, x, y + 1, opennum, hard, s, mode);
		if (!opennum[x][y - 1])
			open(map, x, y - 1, opennum, hard, s, mode);
		if (!opennum[x + 1][y + 1])
			open(map, x + 1, y + 1, opennum, hard, s, mode);
		if (!opennum[x + 1][y])
			open(map, x + 1, y, opennum, hard, s, mode);
		if (!opennum[x + 1][y - 1])
			open(map, x + 1, y - 1, opennum, hard, s, mode);
	}
}

void mode7(int hard, int map[18][32], int mode)
{
	int x, y, opennum[18][32] = { 0 };
	int s = 0,left=0;
	confirmsize(x, y,left, hard);
	gmap(hard,mode);

	LARGE_INTEGER tick, begin;
	QueryPerformanceFrequency(&tick);
	QueryPerformanceCounter(&begin);

	left = shubiao2(hard, x, y, mode, opennum, map,left,begin,tick);
	if (left == 200)
		return;

	setlei(map, x, y);
	putlei(map, hard);
	checknum(map, hard);

	open(map, x, y, opennum, hard, s,7);


	if (win(s, hard, mode))
	{
		if (mode == 9)
		{
			shijian(begin, tick);
			cout << "您获胜了";
		}
		return;
	}


	while (mode >= 8)
	{
		left = shubiao2(hard, x, y, mode, opennum, map,left,begin,tick);
		if (left == 200)
			return;
		open(map, x, y, opennum, hard, s, 7);

		if (map[x][y] == 9)
		{
			gotodiduan(hard);
			cout <<endl<< "扫到雷，结束游戏";
			return;
		}

		if (win(s, hard, mode))
		{
			if (mode == 9)
			{
				shijian(begin, tick);
				cout << "您获胜了";
			}
			return;
		}
	}
}


void zhixing(int mode, int hard, int map[18][32])//执行函数
{
	cct_cls();
	if (mode == 1)
	{
	    int opennum[18][32] = { 1 };
		putlei(map, hard);
		checknum(map, hard);
		printopen(map, hard, mode, opennum);
	} 
	if (mode == 2 || mode == 3||mode==4)
	{ 
		LARGE_INTEGER tick, begin;
		int opennum[18][32] = { 0 };
		int x, y,s=0,z=0;
		printopen(map, hard, mode, opennum);
		if(mode==3||mode==2)
		    shuruzuobiao(x, y, hard, mode);
		else
		{
			QueryPerformanceFrequency(&tick);
			QueryPerformanceCounter(&begin);
			shurumode4(x, y, z, hard, opennum, map, mode,begin,tick);
		}
		if (x == 'Q')
			return;
		setlei(map, x, y);
		putlei(map, hard);
		checknum(map, hard);
		open(map, x, y, opennum, hard,s);
		printopen(map, hard, mode, opennum);
		if (mode == 3||mode==4)
		{
			while (1)
			{
				if (mode == 3)
					shuruzuobiao(x, y, hard, mode);
				else
					shurumode4(x, y, z, hard, opennum, map, mode, begin, tick);
				if (x == 'Q')
					return;
				if (x == '&')
				{
					continue;
				}
				if (map[x][y] == 9)
				{
					open(map, x, y, opennum, hard, s);
					printopen(map, hard, mode, opennum);
					cout << endl << "扫到雷，游戏结束";
					return;
				}

				open(map, x, y, opennum, hard, s);
				printopen(map, hard, mode, opennum);
				if (win(s, hard))
					return;
			}
		}
	}
	if (mode == 5 || mode == 6 )
	{
		int x, y;
		putlei(map, hard);
		checknum(map, hard);
		gmap(hard);
		gopen(map, hard);
		if (mode != 5)
			shubiao(hard, x, y, mode);
		gotodiduan(hard);
		cout << endl << endl;
	}
	if (mode >6)
	{
		mode7(hard, map,mode);
		gotodiduan(hard);
		cout << endl << endl;
	}
}



void putlei(int map[18][32],int hard)//放雷
{
	int size_x, size_y, number;
	confirmsize(size_x, size_y, number, hard);
	int s = 0;
	while (1)
	{
		int b = rand() % size_x + 1;
		int c = rand() % size_y + 1;
		if (map[b][c] != 9&& map[b][c] != 10)//9为雷，10为第一个按的数
		{
			map[b][c] = 9;
			s++;
		}
		if (s == number)
			break;
	}
}

void begin(int hard,int mode)//建立数组
{
	int size_x, size_y, number;
	confirmsize(size_x,size_y, number, hard);
	int map[18][32] = { 0 };
	srand((unsigned int)(time(0)));
	zhixing(mode, hard,map);

}