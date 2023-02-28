/*2050271 信20 张睿*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <conio.h>
#include <Windows.h>
#include <cstring>
#include "../include/cmd_console_tools.h"
#include "../include/common_input.h"
#include "90-01-b1-hanoi.h"
using namespace std;

/* -----------------------------------------

     本文件功能：
	1、放被 hanoi_main.cpp/hanoi_menu.cpp 中的各函数调用的菜单各项对应的执行函数

     本文件要求：
	1、不允许定义外部全局变量（const及#define不在限制范围内）
	2、允许定义静态全局变量（具体需要的数量不要超过文档显示，全局变量的使用准则是：少用、慎用、能不用尽量不用）
	3、静态局部变量的数量不限制，但使用准则也是：少用、慎用、能不用尽量不用
	4、按需加入系统头文件、自定义头文件、命名空间等

   ----------------------------------------- */


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int a[10] = { 0 }, b[10] = { 0 }, c[10] = { 0 };
int at = 0, bt = 0, ct = 0;
int s = 1;
static int time1;



void chen(int* a, char* b, char* c, int mode)//输入所有数字
{

	if (mode == 0)
	{
		*a = input_normal(1, 10, "请输入汉诺塔的层数(1-10)：");
		while (1)
		{
			cout << "请输入起始柱(A-C)：" << endl;
			cin >> *b;
			cin.clear();
			cin.ignore(99999999, '\n');
			if ((*b > 64 && *b < 68) || (*b > 96 && *b < 100))
				break;
		}
		if (*b == 97)
			*b = 65;
		if (*b == 98)
			*b = 66;
		if (*b == 99)
			*b = 67;


		while (1)
		{
			cout << "请输入目标柱(A-C)：" << endl;
			cin >> *c;
			if (*c == 97)
				*c = 65;
			if (*c == 98)
				*c = 66;
			if (*c == 99)
				*c = 67;

			cin.clear();
			cin.ignore(99999999, '\n');
			if (((*c > 64 && *c < 68) || (*c > 96 && *c < 100)) && *c != *b)
				break;
			else if (*c == *b)
				cout << "目标柱(A)不能与起始柱(A)相同" << endl;
		}
	}
	if (mode == 1)
	{
		*a = 0;
		char h[20] = { 0 };
		while (1)
		{


			h[*a] = _getch();
			if (h[*a] == ' ')
				continue;
			if (h[*a] != '\b')
				cout << h[*a];
			if (h[*a] == 'a')
				h[*a] = 'A';
			if (h[*a] == 'b')
				h[*a] = 'B';
			if (h[*a] == 'c')
				h[*a] = 'C';
			if (h[*a] == '\r' || *a == 20)
			{
				*b = h[0];
				*c = h[1];
				break;
			}
			(*a)++;

		}

	}
	if (mode == 2)
		*a = input_normal(0, 5, "请输入移动速度(0-5: 0-按回车单步演示 1-延时最长 5-延时最短)");
}



char zhong(char b, char c)
{
	char d;
	if (c == 'A' || b == 'A')
	{
		if (b == 'B' || c == 'B')
			d = 'C';
		else
			d = 'B';
	}
	else
		d = 'A';
	return d;
}

//暂停
void to_be_continued(int x )
{
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	cct_setcolor(); 
	for (int i = 0; i < x; i++)
		cout << endl;
	cout << "按回车键继续...";

	/* 忽略除回车键外的所有输入（注意：_getch的回车是\r，而getchar是\n）*/
	while (_getch() != '\r')
		;

	cct_cls();

	return;
}

void yuanzhu()
{
	cct_setcursor(CURSOR_INVISIBLE);
	cct_showch(1, 15, ' ', 14, 7, 23);
	cct_showch(33, 15, ' ', 14, 7, 23);
	cct_showch(65, 15, ' ', 14, 7, 23);
	for (int i = 15; i > 2; i--)
	{
		Sleep(50);
		for (int a = 1 + 11; a < 68 + 10; a = a + 32)
			cct_showch(a, i, ' ', 14, 7, 1);
	}
}
//画圆盘
void yuanpan(char src,int n)
{
	int a = n;
	yuanzhu();
	int panchang = 3 + (n - 1) * 2;
	int g = 0;
	if (src == 'A')
		g = 12;
	else if (src == 'B')
		g = 12+ 32;
	else
		g = 12 + 32 * 2;
	for (int chen = 14; chen > 14 - n; chen--, panchang = panchang - 2,a--)
	{
		cct_showch(g - (panchang - 1) / 2, chen, ' ', a+3 , 7, panchang);
		Sleep(50);
	}
}
//画底盘

void controltime()
{
	int i = 0;
	if (time1 == 0)
	{
		while (1) {
			i = _getch();
			if (i == '\r')
				break;
		}
	}
	if (time1 != 0)
		Sleep((5 - time1) * 200);
}

//打印行
void printa(char src)
{
	cout << " " << src << ":";
	for (int i = 0; i < 10; i++)
	{
		if (src == 'A')
		{
			if (a[i] != 0)
				cout << setiosflags(ios::right) << setw(2) << a[i];
			else
				cout << "  ";
		}
		if (src == 'B')
		{
			if (b[i] != 0)
				cout << setiosflags(ios::right) << setw(2) << b[i];
			else
				cout << "  ";
		}
		if (src == 'C')
		{
			if (c[i] != 0)
				cout << setiosflags(ios::right) << setw(2) << c[i];
			else
				cout << "  ";
		}
	}
}

//打印列
void printlie(char src,int mode)
{
	if (mode == 9)
		mode = 8;
	int f = 11 + (mode - 4) * 4;
	for (int i = 0; i < 10; i++)
	{
		if (src == 'A')
		{
			cct_gotoxy(10, f);
			if (a[i] != 0)
			{
				if (a[i] != 10)
					cct_gotoxy(11, f);
				cout << a[i];
			}
			else
				cout << "   ";
		}
		if (src == 'B')
		{
			cct_gotoxy(20, f);
			if (b[i] != 0)
			{

				if (b[i] != 10)
					cct_gotoxy(21, f);
				cout << b[i];
			}
			else
				cout << "   ";
		}
		if (src == 'C')
		{
			cct_gotoxy(30, f);
			if (c[i] != 0)
			{
				if (c[i] != 10)
					cct_gotoxy(31, f);
				cout << c[i];
			}
			else
				cout << "   ";
		}
		f--;
	}
}

//打印整列
void printlie1(int mode)
{
	if (mode == 9)
		mode--;
	printlie('A',mode);
	printlie('B',mode);
	printlie('C',mode);
	cct_gotoxy(0, 18);
}

//打印整行
void printl()
{
	printa('A');
	printa('B');
	printa('C');
	cout << endl;
}

void chushihua()
{
	s = 1;
	int u = 0;
	while (1)
	{
		a[u] = 0;
		b[u] = 0;
		c[u] = 0;
		if (u == 9)
			break;
		u++;
	}
	at = 0;
	bt = 0;
	ct = 0;
	time1 = 2;
}

void move1(char src, char dst)
{
	if (src == 'A' && dst == 'B')
	{
		b[bt] = a[at - 1];
		a[at - 1] = 0;
		bt++;
		at--;
	}
	if (src == 'A' && dst == 'C')
	{
		c[ct] = a[at - 1];
		a[at - 1] = 0;
		ct++;
		at--;
	}
	if (src == 'B' && dst == 'C')
	{
		c[ct] = b[bt - 1];
		b[bt - 1] = 0;
		ct++;
		bt--;
	}
	if (src == 'B' && dst == 'A')
	{
		a[at] = b[bt - 1];
		b[bt - 1] = 0;
		at++;
		bt--;
	}
	if (src == 'C' && dst == 'A')
	{
		a[at] = c[ct - 1];
		c[ct - 1] = 0;
		at++;
		ct--;
	}
	if (src == 'C' && dst == 'B')
	{
		b[bt] = c[ct - 1];
		c[ct - 1] = 0;
		bt++;
		ct--;
	}
}

void shangyi(char src, char dst, int panchang, int zhizhen1, int zhizhen2, int color, int mode, int n)
{
	int chishi = 15 - zhizhen1, mo = 14 - zhizhen2;
	int g;
	if (src == 'A')
		g = 12;
	else if (src == 'B')
		g = 12 + 32;
	else
		g = 12 + 32 * 2;
	int zuobiao1 = g - (panchang - 1) / 2;
	if (dst == 'A')
		g = 12;
	else if (dst == 'B')
		g = 12 + 32;
	else
		g = 12 + 32 * 2;
	int zuobiao2 = g - (panchang - 1) / 2;//列坐标


	if (mode >7)
	{
		cct_setcolor();
		move1(src, dst);
		cct_gotoxy(0, 33);
		cout << "第" << setw(4) << s << "步(" << n << "#: " << src << "-->" << dst << ") ";
		printl();
		printlie1(mode);
	}



	/* 将一串字符从下到上移动 */
	for (int y = chishi; y > 0; y--)
	{
		cct_showstr(zuobiao1, y, " ", color, color, panchang);
		if (mode != 9)
			Sleep((5 - time1) * 10);

		if (y > 1) {
			/* 清除显示(最后一次保留)，清除方法为用正常颜色+空格重画一遍刚才的位置 */

			{
				cct_showch(zuobiao1, y, ' ', COLOR_BLACK, COLOR_WHITE, panchang);
				if (y > 2)
					cct_showch(zuobiao1 + panchang / 2, y, ' ', 14, 14, 1);
			}

		}
	}

	if (zuobiao1 < zuobiao2)
	{
		/* 将一串字符从左向右移动 */
		for (int x = zuobiao1; x < zuobiao2 + 1; x++) {
			/* 在坐标(x,2)位置处连续打印10个字符 */
			cct_showch(x, 1, ' ', color, color, panchang);

			/* 延时0.1秒 */

			if (mode != 9)
				Sleep((5 - time1) * 10);

			if (x < zuobiao2) {
				/* 清除显示(最后一次保留)，清除方法为用正常颜色+空格重画一遍刚才的位置 */
				cct_showch(x, 1, ' ', COLOR_BLACK, COLOR_WHITE, panchang);
			}
		}
	}
	else
	{
		/* 将一串字符从右向左移动 */
		for (int x = zuobiao1; x > zuobiao2 + 1; x--) {
			/* 在坐标(x,2)位置处连续打印10个字符 */
			cct_showch(x, 1, ' ', color, color, panchang);

			/* 延时0.1秒 */
			if (mode != 9)
				Sleep((5 - time1) * 10);

			if (x < zuobiao1) {
				/* 清除显示(最后一次保留)，清除方法为用正常颜色+空格重画一遍刚才的位置 */
				cct_showch(x, 1, ' ', COLOR_BLACK, COLOR_WHITE, panchang + 1);
			}
		}
	}

	/* 将一串字符从上向下移动 */
	for (int y = 1; y < mo + 1; y++) {
		/* 在坐标(x,2)位置处连续打印10个字符 */
		cct_showstr(zuobiao2, y, " ", color, color, panchang);

		/* 延时0.3秒 */
		if (mode != 9)
			Sleep((5 - time1) * 10);

		if (y < mo) {
			/* 清除显示(最后一次保留)，清除方法为用正常颜色+空格重画一遍刚才的位置 */
			cct_showch(zuobiao2, y, ' ', COLOR_BLACK, COLOR_WHITE, panchang);
			if (y > 2)
				cct_showch(zuobiao2 + panchang / 2, y, ' ', 14, 14, 1);
		}
	} //end of for


}

void movepan(int panchang, char src, char dst, int mode,int n)
{
	int color,  zhizhen1 = 0, zhizhen2 = 0;
	if (src == 'A')
		zhizhen1 = at;
	if (src == 'B')
		zhizhen1 = bt;
	if (src == 'C')
		zhizhen1 = ct;
	if (dst == 'A')
		zhizhen2 = at;
	if (dst == 'B')
		zhizhen2 = bt;
	if (dst == 'C')
		zhizhen2 = ct;

	color=n+3;
	shangyi(src, dst, panchang, zhizhen1, zhizhen2, color, mode,n);
}



void begin(int n, char src, char tmp, char dst, int mode)
{
	chushihua();

	if (mode == 4 || mode == 8)
	{
		chen(&time1, &src, &dst, 2);
	}	
	if (mode > 3)
			cct_cls();
	if (mode == 7 || mode == 9 || mode == 4 || mode == 8)
	{
		cct_gotoxy(0, 0);
		cct_setcolor();

		cout << "从 " << src << " 移动到 " << dst << "，共 " << n << " 层";
		if (mode == 4 || mode == 8)
			cout << ",延时设置为" << time1;
	}

	//建立数组
	int p = n;
	if (src == 'A')
		at = p;
	if (src == 'B')
		bt = p;
	if (src == 'C')
		ct = p;
	//赋值
	for (int i = 0; i < n; i++)
	{
		if (src == 'A')
			a[i] = p;
		if (src == 'B')
			b[i] = p;
		if (src == 'C')
			c[i] = p;
		p = p - 1;
	}
	if (mode == 4 || mode == 8||mode==9)
	{
		if (mode == 9)
			mode--;
		cct_gotoxy(0, 17 + (mode - 4) * 4);
		cout << "初始:" << setw(16);
		printl();

		for (int i = 9; i < 34; i++)
		{
			cct_gotoxy(i, 12 + (mode - 4) * 4);
			cout << "=";
		}
		cct_gotoxy(11, 13 + (mode - 4) * 4);
		cout << "A";
		cct_gotoxy(21, 13 + (mode - 4) * 4);
		cout << "B";
		cct_gotoxy(31, 13 + (mode - 4) * 4);
		cout << "C";
		printlie1(mode);
	}

	if (mode > 5)
		yuanpan(src, n);
	if (mode == 7)
	{

		if (n == 0)
			movepan(3, src, dst, 7, 1);
		else
			movepan(3, src, tmp, 7, 1);

	}
}

//移动数组


//打印
void daying(int n, char src, char tmp, char dst, int mode)
{
	if (mode == 4 || mode == 8)
		controltime();


	if (mode >7)
	{
		movepan(n * 2 + 1, src, dst,mode,n);
		cct_setcolor();
	}
	//移动
	if(mode!=8&&mode!=9)
	move1(src, dst);


	if (mode == 1)
		cout << n << "# " << src << "---->" << dst << endl;
	if(mode==2)
		cout << "第"<<setw(4) << s << " 步(" << setw(2) << n << "#:" << src << "-->" << dst <<")"<< endl;
	if (mode == 3)
	{
		cout << "第" << setw(4) << s << " 步(" << setw(2) << n << "#:" << src << "-->" << dst << ")";
		printl();
	}

	if (mode == 4)
	{
		cct_gotoxy(0, 17+(mode-4)*4);
		cout << "第" << setw(4) << s << "步(" << n << "#: " << src << "-->" << dst << ") ";
		printl();
	    printlie1(mode);
	}

	s++;
}

int yidong(int censhu)
{
	cct_gotoxy(0, 34);
	cct_setcolor();
	cout << "请输入移动的柱号(命令形式：AC = A顶端的盘子移动到C，Q = 退出) ：";
	char d = 0,g0,g1;
	while (1)
	{
		//char src, dst;
		cct_setcolor();
		int chuzhi = 0;
		int mowei = 0;
		cct_gotoxy(64, 34);
		int i = 0;
		while (1)
		{

			char h0, h1;
			chen(&i, &h0, &h1, 1);
			cct_gotoxy(64, 34);
			cout << "                     ";
			cct_gotoxy(64, 34);
			if (i == 2 && h0 > 64 && h0 < 68 && h1 > 64 && h1 < 68)
			{
				g0 = h0;
				g1 = h1;
				break;
			}

			if (i == 1 && (h0 == 'Q' || h0 == 'q'))
			{
				cout << "游戏终止！！！";
				return 0;
			}
		}
		cct_gotoxy(64, 34);
		cout << "                                                                              ";
		d = zhong(g0, g1);
		if (g0 == 'A')
		{
			if (at != 0)
				chuzhi = a[at - 1];
			else
				chuzhi = 0;
		}
		if (g0 == 'B')
		{
			if (bt != 0)
				chuzhi = b[bt - 1];
			else
				chuzhi = 0;
		}
		if (g0 == 'C')
		{
			if (ct != 0)
				chuzhi = c[ct - 1];
			else
				chuzhi = 0;
		}
		if (g1 == 'A')
		{
			if (at != 0)
				mowei = a[at - 1];
			else
				mowei = 0;
		}
		if (g1 == 'B')
		{
			if (bt != 0)
				mowei = b[bt - 1];
			else
				mowei = 0;
		}
		if (g1 == 'C')
		{
			if (ct != 0)
				mowei = c[ct - 1];
			else
				mowei = 0;
		}
		if (chuzhi > mowei && mowei != 0)
		{
			cct_gotoxy(0, 35);
			cout << "大盘压小盘，非法移动！" << endl;
			Sleep(1000);
			cct_gotoxy(0, 35);
			cout << "                                                                              ";
		}
		else if (chuzhi == 0)
		{
			cct_gotoxy(0, 35);
			cout << "源盘为空" << endl;
			Sleep(1000);
			cct_gotoxy(0, 35);
			cout << "                                                                              ";
		}
		else if (chuzhi == mowei)
			continue;
		else
			daying(chuzhi, g0, d, g1, 9);
		if (g1 == 'A' && at == censhu)
		{
			cct_gotoxy(0, 35);
			cout << "游戏终止！！！";
			return 0;
		}
		if (g1 == 'B' && bt == censhu)
		{
			cct_gotoxy(0, 35);
			cout << "游戏终止！！！";
			return 0;
		}
		if (g1 == 'C' && ct == censhu)
		{
			cct_gotoxy(0, 35);
			cout << "游戏终止！！！";
			return 0;
		}
	}
	return 0;

}

void hanoi(int n, char src, char tmp, char dst,int mode)
{
	if (n == 1)
	{
		daying(n, src, tmp, dst, mode);
	}
	else
	{
		hanoi(n - 1, src, dst, tmp, mode);
		daying(n, src, tmp, dst, mode);
		hanoi(n - 1, tmp, src, dst,mode);
	}
}