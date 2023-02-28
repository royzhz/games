/*2050271 ��20 ���*/
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

     ���ļ����ܣ�
	1���ű� hanoi_main.cpp/hanoi_menu.cpp �еĸ��������õĲ˵������Ӧ��ִ�к���

     ���ļ�Ҫ��
	1�����������ⲿȫ�ֱ�����const��#define�������Ʒ�Χ�ڣ�
	2�������徲̬ȫ�ֱ�����������Ҫ��������Ҫ�����ĵ���ʾ��ȫ�ֱ�����ʹ��׼���ǣ����á����á��ܲ��þ������ã�
	3����̬�ֲ����������������ƣ���ʹ��׼��Ҳ�ǣ����á����á��ܲ��þ�������
	4���������ϵͳͷ�ļ����Զ���ͷ�ļ��������ռ��

   ----------------------------------------- */


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int a[10] = { 0 }, b[10] = { 0 }, c[10] = { 0 };
int at = 0, bt = 0, ct = 0;
int s = 1;
static int time1;



void chen(int* a, char* b, char* c, int mode)//������������
{

	if (mode == 0)
	{
		*a = input_normal(1, 10, "�����뺺ŵ���Ĳ���(1-10)��");
		while (1)
		{
			cout << "��������ʼ��(A-C)��" << endl;
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
			cout << "������Ŀ����(A-C)��" << endl;
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
				cout << "Ŀ����(A)��������ʼ��(A)��ͬ" << endl;
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
		*a = input_normal(0, 5, "�������ƶ��ٶ�(0-5: 0-���س�������ʾ 1-��ʱ� 5-��ʱ���)");
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

//��ͣ
void to_be_continued(int x )
{
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	cct_setcolor(); 
	for (int i = 0; i < x; i++)
		cout << endl;
	cout << "���س�������...";

	/* ���Գ��س�������������루ע�⣺_getch�Ļس���\r����getchar��\n��*/
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
//��Բ��
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
//������

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

//��ӡ��
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

//��ӡ��
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

//��ӡ����
void printlie1(int mode)
{
	if (mode == 9)
		mode--;
	printlie('A',mode);
	printlie('B',mode);
	printlie('C',mode);
	cct_gotoxy(0, 18);
}

//��ӡ����
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
	int zuobiao2 = g - (panchang - 1) / 2;//������


	if (mode >7)
	{
		cct_setcolor();
		move1(src, dst);
		cct_gotoxy(0, 33);
		cout << "��" << setw(4) << s << "��(" << n << "#: " << src << "-->" << dst << ") ";
		printl();
		printlie1(mode);
	}



	/* ��һ���ַ����µ����ƶ� */
	for (int y = chishi; y > 0; y--)
	{
		cct_showstr(zuobiao1, y, " ", color, color, panchang);
		if (mode != 9)
			Sleep((5 - time1) * 10);

		if (y > 1) {
			/* �����ʾ(���һ�α���)���������Ϊ��������ɫ+�ո��ػ�һ��ղŵ�λ�� */

			{
				cct_showch(zuobiao1, y, ' ', COLOR_BLACK, COLOR_WHITE, panchang);
				if (y > 2)
					cct_showch(zuobiao1 + panchang / 2, y, ' ', 14, 14, 1);
			}

		}
	}

	if (zuobiao1 < zuobiao2)
	{
		/* ��һ���ַ����������ƶ� */
		for (int x = zuobiao1; x < zuobiao2 + 1; x++) {
			/* ������(x,2)λ�ô�������ӡ10���ַ� */
			cct_showch(x, 1, ' ', color, color, panchang);

			/* ��ʱ0.1�� */

			if (mode != 9)
				Sleep((5 - time1) * 10);

			if (x < zuobiao2) {
				/* �����ʾ(���һ�α���)���������Ϊ��������ɫ+�ո��ػ�һ��ղŵ�λ�� */
				cct_showch(x, 1, ' ', COLOR_BLACK, COLOR_WHITE, panchang);
			}
		}
	}
	else
	{
		/* ��һ���ַ����������ƶ� */
		for (int x = zuobiao1; x > zuobiao2 + 1; x--) {
			/* ������(x,2)λ�ô�������ӡ10���ַ� */
			cct_showch(x, 1, ' ', color, color, panchang);

			/* ��ʱ0.1�� */
			if (mode != 9)
				Sleep((5 - time1) * 10);

			if (x < zuobiao1) {
				/* �����ʾ(���һ�α���)���������Ϊ��������ɫ+�ո��ػ�һ��ղŵ�λ�� */
				cct_showch(x, 1, ' ', COLOR_BLACK, COLOR_WHITE, panchang + 1);
			}
		}
	}

	/* ��һ���ַ����������ƶ� */
	for (int y = 1; y < mo + 1; y++) {
		/* ������(x,2)λ�ô�������ӡ10���ַ� */
		cct_showstr(zuobiao2, y, " ", color, color, panchang);

		/* ��ʱ0.3�� */
		if (mode != 9)
			Sleep((5 - time1) * 10);

		if (y < mo) {
			/* �����ʾ(���һ�α���)���������Ϊ��������ɫ+�ո��ػ�һ��ղŵ�λ�� */
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

		cout << "�� " << src << " �ƶ��� " << dst << "���� " << n << " ��";
		if (mode == 4 || mode == 8)
			cout << ",��ʱ����Ϊ" << time1;
	}

	//��������
	int p = n;
	if (src == 'A')
		at = p;
	if (src == 'B')
		bt = p;
	if (src == 'C')
		ct = p;
	//��ֵ
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
		cout << "��ʼ:" << setw(16);
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

//�ƶ�����


//��ӡ
void daying(int n, char src, char tmp, char dst, int mode)
{
	if (mode == 4 || mode == 8)
		controltime();


	if (mode >7)
	{
		movepan(n * 2 + 1, src, dst,mode,n);
		cct_setcolor();
	}
	//�ƶ�
	if(mode!=8&&mode!=9)
	move1(src, dst);


	if (mode == 1)
		cout << n << "# " << src << "---->" << dst << endl;
	if(mode==2)
		cout << "��"<<setw(4) << s << " ��(" << setw(2) << n << "#:" << src << "-->" << dst <<")"<< endl;
	if (mode == 3)
	{
		cout << "��" << setw(4) << s << " ��(" << setw(2) << n << "#:" << src << "-->" << dst << ")";
		printl();
	}

	if (mode == 4)
	{
		cct_gotoxy(0, 17+(mode-4)*4);
		cout << "��" << setw(4) << s << "��(" << n << "#: " << src << "-->" << dst << ") ";
		printl();
	    printlie1(mode);
	}

	s++;
}

int yidong(int censhu)
{
	cct_gotoxy(0, 34);
	cct_setcolor();
	cout << "�������ƶ�������(������ʽ��AC = A���˵������ƶ���C��Q = �˳�) ��";
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
				cout << "��Ϸ��ֹ������";
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
			cout << "����ѹС�̣��Ƿ��ƶ���" << endl;
			Sleep(1000);
			cct_gotoxy(0, 35);
			cout << "                                                                              ";
		}
		else if (chuzhi == 0)
		{
			cct_gotoxy(0, 35);
			cout << "Դ��Ϊ��" << endl;
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
			cout << "��Ϸ��ֹ������";
			return 0;
		}
		if (g1 == 'B' && bt == censhu)
		{
			cct_gotoxy(0, 35);
			cout << "��Ϸ��ֹ������";
			return 0;
		}
		if (g1 == 'C' && ct == censhu)
		{
			cct_gotoxy(0, 35);
			cout << "��Ϸ��ֹ������";
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