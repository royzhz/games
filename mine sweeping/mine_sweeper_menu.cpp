/*2050271 ��20 ���*/
#include <iostream>
#include <conio.h>
#include "mine_sweeper.h"
#include "cmd_console_tools.h"
using namespace std;

void shuru(int& a,int mode)
{
	while (1)
	{
		a = _getch();
		if ((!mode && (a < 58 && a>47)) || (mode == 1 && (a < '4' && a>'0')))
		{
			a = a - 48;
			break;
		}
	}
}

void menu(int &a)
{
	cout << "------------------------------------------" << endl;
	cout << "1.ѡ���ѶȲ���ʾ�ڲ�����" << endl;
	cout << "2.�����ʼλ�ò���ʾ���򿪵ĳ�ʼ����" << endl;
	cout << "3.�ڲ����������" << endl;
	cout << "4.�ڲ����������棨��ǡ�����ʱ�䣩" << endl;
	cout << "5.����αͼ�λ���ܲ���ʾ�ڲ�����" << endl;
	cout << "6.������λ�úͺϷ��ԣ���������˳���" << endl;
	cout << "7.���ѡ���ʼλ�ò���ʾ���򿪵ĳ�ʼ����" << endl;
	cout << "8.αͼ�ν��������" << endl;
	cout << "9.αͼ�ν���������" << endl;
	cout << "0.�˳���Ϸ" << endl;
	cout << "------------------------------------------" << endl;
	cout << "[��ѡ��] :";
	shuru(a, 0);
}

void nandu(int& a)
{
	cout << "��ѡ���Ѷȣ�" << endl;
	cout << "1.����(9 * 9 - 10����)" << endl;
	cout << "2.�м�(16 * 16 - 40����)" << endl;
	cout << "3.�߼�(16 * 30 - 99����)" << endl;
	cout << "������[1..3]��";
	shuru(a, 1);
}



