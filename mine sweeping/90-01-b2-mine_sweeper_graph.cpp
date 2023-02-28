/*2050271 信20 张睿*/
#include <iostream>
#include <iomanip>
#include <windows.h> 
#include "90-01-b2-mine_sweeper.h"
#include "../include/cmd_console_tools.h"
#include "../include/common_input.h"
using namespace std;

void gopen(int map[18][32],int hard)
{
	int xmax, ymax, num;
	confirmsize(xmax, ymax, num, hard);
	for (int x = 1; x < xmax+1; x++)
	{
		for (int y = 1; y < ymax+1; y++)
		{
			gopengezi(map, x, y);
		}
	}
}

void gopengezi(int map[18][32],int x,int y,int youjian)
{
	cct_setcolor(7, 0);
	cct_gotoxy(y * 6 - 2, x * 3);
	cout << "    ";
	cct_gotoxy(y * 6 -2, x * 3+1);
	if (youjian == 0)
	{
		if (map[x][y] != 9 && map[x][y] != 0)
		{
			cct_setcolor(7, map[x][y] + 7);//
			cout << " " << map[x][y] << "  ";
			cct_setcolor(7);
		}
		else if (map[x][y] == 0)
			cout << "    ";
		else
			cout << " *  ";
	}
	else if (youjian)
	{
		if(youjian==1)
		    cct_setcolor(5, 15);
		else
			cct_setcolor(6);
		cct_gotoxy(y * 6 - 2, x * 3);
		cout << "    ";
		cct_gotoxy(y * 6 - 2, x * 3 + 1);
		if (youjian == 1)
			cout << " #  ";
		else
			cout << "    ";
	}
}



void gmap(int hard,int mode)
{
	cct_setfontsize("新宋体", 14);	
	int xmax, ymax, num;
	confirmsize(xmax, ymax, num, hard);
	cct_setconsoleborder(ymax*6+5, xmax*3+12);

	if (mode > 7)
		cout << "按ESC退出";
	if (mode == 9)
		cout << "       按空格显示时间";

	cout << endl;

	for (int i = 0; i < ymax; i++)
		cout << setw(6) << i;
	cout<<endl;
	for (int x = 0; x < xmax*3+1; x++)
	{
		for (int y = 0; y < ymax * 3 + 2; y++)
		{
			cct_setcolor(15,8);
			if (x == 0 && y == 2)
				cout << "╔";
			else if (x == xmax * 3 && y == 2)
				cout << "╚";
			else if (x % 3 == 0 && y == 2)
				cout << "╠";
			else if ((y - 2) % 3 == 0 && x == xmax * 3)
				cout << "╩" ;
			else if ((y - 2) % 3 == 0 && x== 0)
				cout << "╦";
			else if ((y - 2) % 3 == 0 && x % 3 == 0)
				cout << "╬";
			else if (y == 2 || (y - 2) % 3 == 0)
				cout << "║";
			else if (y > 1 && x % 3 == 0)
				cout << "═";
			else if (y ==0&&x%3==2)
			{
				cct_setcolor();
				cout << char('A'+x/3);
			}
			else if (y <= 1)
			{
				cct_setcolor();
				cout << " ";
			}
			else
			{
				cct_setcolor(6);
				cout << "  ";
			}
		}
		cct_setcolor(15, 8);
		if (x == 0)
			cout << "╗" << endl;
		else if (x == xmax * 3)
			cout << "╝" << endl;
		else if (x % 3 == 0)
			cout << "╣" << endl;
		else
			cout << "║"<<endl;
		cct_setcolor();
	}
}


int shubiao(int hard, int& x, int& y, int mode)
{
	int X = 0, Y = 0;
	int ret, maction;
	int keycode1, keycode2;
	int loop = 1;
	cct_setcolor();
	cct_enable_mouse();
	int xmax, ymax, num;
	confirmsize(xmax, ymax, num, hard);

	cct_setcursor(CURSOR_INVISIBLE);
	while (loop) {
		ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
		if (ret == CCT_MOUSE_EVENT)
		{
			cct_gotoxy(0, xmax * 3 + 3);
			if ((X - 4) >= 0 && (X - 4) % 6 <= 3 && Y - 3 >= 0 && (Y - 3) % 3 < 2 && X < ymax * 6 + 4 && Y < xmax * 3 + 3)
			{
				cout << "[当前光标]：" << char((Y - 3) / 3 + 'A') << "行" << (X - 4) / 6 << "列";
				x = (Y - 3) / 3;
				y = (X - 4) / 6;
			}
			else
				cout << "[当前光标]:位置非法        ";

			switch (maction)
			{
			case MOUSE_LEFT_BUTTON_CLICK:			//按下左键
				if (mode == 6)
					return 0;
				if ((mode >6) && (X - 4) >= 0 && (X - 4) % 6 <= 3 && Y - 3 >= 0 && (Y - 3) % 3 < 2 && X < ymax * 6 + 4 && Y < xmax * 3 + 3)
				{
					x = (Y - 3) / 3 + 1;
					y = (X - 4) / 6 + 1;
					return 0;
				}
				break;
			case MOUSE_RIGHT_BUTTON_CLICK:
				if (mode >7 && (X - 4) >= 0 && (X - 4) % 6 <= 3 && Y - 3 >= 0 && (Y - 3) % 3 < 2 && X < ymax * 6 + 4 && Y < xmax * 3 + 3)
				{
					x = (Y - 3) / 3 + 1;
					y = (X - 4) / 6 + 1;
					return 1;
				}
				break;
			}

		}
		else if (ret == CCT_KEYBOARD_EVENT)
		{
			switch (keycode1)
			{
			case 27:	//ESC键
				if (mode != 6)
					return 200;//屏蔽mode6
				break;
			case 32:	//SPACE键
				return 300;
				break;
			}
		}

	}
	return 0;
}


int shubiao2(int hard, int& x, int& y, int mode, int opennum[18][32], int map[18][32], int left, LARGE_INTEGER begin, LARGE_INTEGER tick)
{
	while (1)
	{
		int z = shubiao(hard, x, y, mode);
		if (z == 0 && opennum[x][y] != 2)
			break;
		else if (z == 0 && opennum[x][y] == 2)
			continue;
		else if (z == 200)
			return 200;
		else if (opennum[x][y] == 2&&z!=300)
		{
			left++;
			opennum[x][y] = 0;
			gopengezi(map, x, y, 2);
		}
		else if (opennum[x][y] == 0 && z != 300)
		{
			left--;
			opennum[x][y] = 2;
			gopengezi(map, x, y, 1);
		}

		if (z == 300)
			tishi(mode, begin, tick, 2, left);
		else
			tishi(mode, begin, tick, 0, left);
	}
	tishi(mode, begin, tick, 0, left);
	return left;
}