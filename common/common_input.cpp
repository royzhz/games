/*2050271 信20 张睿*/
#include <iostream>
#include <conio.h>
#include "../include/cmd_console_tools.h"
using namespace std;



int input_menu(int start, int end)
{
	char a = 0;
	while (1)
	{
		a = _getch();
		if (int(a) <= end + '0' && int(a) >= start + '0')
		{
			cout << a;
			cout << endl << endl << endl;
			return a - '0';
		}
	}
}

char input_menu(const char choice[], const int no)
{
	char a = 0;
	while (1)
	{
		a = _getch();
		for (int i = 0; i < no; i++)
		{
			if (a <= 'z' && a >= 'a')
				a = a + 'A' - 'a';
			if (a == choice[i])
			{
				cout << a;
				cout << endl << endl << endl;
				return a;
			}
		}
	}
}




char menu(const char name[][100],const char choice[], const int no)
{
	cout << "------------------------------------------" << endl;
	for (int i=0;i<no; i++)
	{
		for (int k=0; name[i][k] != '\n'; k++)
		{
			cout << name[i][k];
		}
		cout<<endl;
	}
	cout << "------------------------------------------" << endl;
	cout << "[请选择] :";
	return input_menu(choice, no);
}



int input_normal(int start, int end, const char name[],bool feedback,int x,int y,bool enter)
{
	int a;
	while (1)
	{
		if (enter == 1)
		{
			if (x != -1)
				cct_gotoxy(x, y);
			cout << name << endl;
		}
		else
		{
			if (x != -1)
			{
				cct_gotoxy(x, y);
				cout << "                                              ";
				cct_gotoxy(x, y);
			}
			cout << name;
		}
		if (!(cin >> a))
		{
			cin.clear();
			cin.ignore(99999999, '\n');
			if (feedback == 1)
				cout << "输入错误，请重新输入" << endl;
			continue;
		}
		else
		{
			cin.clear();
			cin.ignore(99999999, '\n');
			if (a > start - 1 && a < end + 1)
				break;
			else if (feedback == 1)
				cout  << "输入错误，请重新输入" << endl;
		}
	}
	return a;
}

void input_normal(char& xline, char& ycolumn, const char name[],int column,int line)
{
	char in[100];
	while (1)
	{
		cout << name;
		int cx, cy;
		cct_getxy(cx, cy);
		cout << "                                 ";
		cct_gotoxy(cx,cy);
		cin >> in;
		if (in[0] >= 'a' && in[0] <= 'z')
			in[0] = in[0] - 'a' + 'A';
		if (in[1] >= '0' && in[1] < '0'+column && in[0] >= 'A' && in[0] <= 'A' + line - 1)
		{
			xline = in[0];
			ycolumn = in[1];
			return;
		}
		else
		{
			cout << "输入错误，请重新输入" << endl;
			cct_getxy(cx, cy);
			cct_gotoxy(0, cy - 2);
		}
	}
}






void to_be_continued(const char name[]="按回车键继续...")
{
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	cct_setcolor();
		cout << name<< endl;


	while (_getch() != '\r')
		;
	//cct_cls();
	return;
}






