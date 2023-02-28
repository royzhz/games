/*2050271 信20 张睿*/
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "90-01-b2-mine_sweeper.h"
#include "../include/cmd_console_tools.h"
#include "../include/common_input.h"
using namespace std;




void shijian(LARGE_INTEGER begin, LARGE_INTEGER tick)
{
	LARGE_INTEGER end;
	QueryPerformanceCounter(&end);
	cct_setcolor(0, 14);
	cout << "耗时" << double(end.QuadPart - begin.QuadPart) / tick.QuadPart << "秒   ";
	cct_setcolor();
}

void tishi(int mode, LARGE_INTEGER begin, LARGE_INTEGER tick, int z, int left)
{
	cct_gotoxy(0, 0);
	cct_setcolor();
	cct_setcolor(0, 14);
	if (mode == 9 && z == 0)
	{
		if (left >= 0)
			cout << "还有" << left << "个雷     ";
		else
			cout << "还有0个雷,";
	}
	if (mode == 9 && z == 2)
		shijian(begin, tick);
	cct_setcolor();
	if (mode > 7)
		cout << "按ESC退出";
	if (mode == 9)
		cout << "       按空格显示时间";
}

void shuruzuobiao(int& x, int& y,int hard,int mode)
{
	int xmax, ymax, num;
	confirmsize(xmax, ymax, num, hard);	
	cout << endl << endl;
    cout<< "输入非雷位置的行列坐标（先行后列，严格区分大小写，例：G1/Af，按Q/q退出）：";
	while (1)
	{
		x = _getch();
		if (x == 'Q' || x == 'q')
		{
			x = 'Q';
			return;
		}
		if (x >= 'A' && x < 'A' + xmax)
		{
			cout << char(x);
			x = x - 'A' + 1;
			break;
		}
	}
	while (1)
	{
		y = _getch();
		if (y > '0' && y <='9')
		{
			cout << char(y);
			y = y - '0';
			break;
		}
		else if(y>='a'&&y<'a'+ymax-9)
		{
			cout << char(y);
			y = y - 'a' + 10;
			break;
		}
	}
	cout << endl;
}

void shuru4(int& x, int& y, int& z, int hard)
{
	z = 0;
	int xmax, ymax, num;
	confirmsize(xmax, ymax, num, hard);
	cout << endl << endl;
	cout << "特殊输入说明： & -游戏已运行时间(单字符即可，不需要加坐标)" << endl;
	cout << "!- 标记该坐标为雷(例：!E3)" << endl;
	cout << "# - 取消标记      (例：#E3)" << endl;
	cout << "输入非雷位置的行列坐标（先行后列，严格区分大小写，例：G1/Af，按Q/q退出）：" ;
	while (1)
	{
		x = _getch();
		if (x == 'Q' || x == 'q')
		{
			x = 'Q';
			return;
		}
		if (x >= 'A' && x < 'A' + xmax)
		{
			cout << char(x);
			x = x - 'A' + 1;
			break;
		}
		if (x == '&')
		{
			cout << char(x);
			return;
		}
		if (x == '!' && !z || x == '#' && !z)
		{
			z = x;
			cout << char(z);
		}
	}
	while (1)
	{
		y = _getch();
		if (y > '0' && y <= '9')
		{
			cout << char(y);
			y = y - '0';
			break;
		}
		else if (y >= 'a' && y < 'a' + ymax - 9)
		{
			cout << char(y);
			y = y - 'a' + 10;
			break;
		}
	}
	cout << endl;
}

int win(int s, int hard,int mode)
{
	int size_x, size_y, number;
	confirmsize(size_x, size_y, number, hard);
	if (s == size_x * size_y - number)
	{
		gotodiduan(hard);
		cout << endl;
		if (mode != 9)
			cout << "您获胜了";
		return 1;
	}
	else 
		return 0;
}

