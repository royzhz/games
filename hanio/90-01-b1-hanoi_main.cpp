/*2050271 ��20 ���*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string.h>
#include <Windows.h>
#include "../include/cmd_console_tools.h"
#include "../include/common_input.h"
#include "90-01-b1-hanoi.h"
using namespace std;


int main()
{
	int  mode,censhu;
	char src,dst,tmp;

	cct_setconsoleborder(120, 40, 120, 9000);
    while (1)
	{
		cct_cls();
		cout << "---------------------------------" << endl;
		cout << "1.������" << endl;
		cout << "2.������(������¼)" << endl;
		cout << "3.�ڲ�������ʾ(����)" << endl;
		cout << "4.�ڲ�������ʾ(���� + ����)" << endl;
		cout << "5.ͼ�ν� - Ԥ�� - ������Բ��" << endl;
		cout << "6.ͼ�ν� - Ԥ�� - ����ʼ���ϻ�n������" << endl;
		cout << "7.ͼ�ν� - Ԥ�� - ��һ���ƶ�" << endl;
		cout << "8.ͼ�ν� - �Զ��ƶ��汾" << endl;
		cout << "9.ͼ�ν� - ��Ϸ��" << endl;
		cout << "0.�˳�" << endl;
		cout << "----------------------------------" << endl;
		cout << "[��ѡ��:] ";
		mode = input_menu();
		if (mode == 5)
		{
			cct_cls();
			yuanzhu();
		}
		else if (!mode)
			break;

		else
		{
			chen(&censhu,&src,&dst,0);
			tmp = zhong(src, dst);
			if (mode != 9)
			{

				begin(censhu, src, tmp, dst, mode);
				hanoi(censhu, src, tmp, dst, mode);
			}
			else
			{
				begin(censhu, src, tmp, dst, mode);
				yidong(censhu);
			}
		}




		if (mode < 5||mode==9)
			to_be_continued(1);
		else
			to_be_continued(25);
	}
	return 0;
}
