/*2050271 ��20 ���*/
#include <iostream>
#include "90-01-b2-mine_sweeper.h"
#include "../include/cmd_console_tools.h"
#include "../include/common_input.h"
using namespace std;

int main()
{
	while (1)
	{
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
		cct_setfontsize("������", 20);
		cct_setconsoleborder(80, 30,80,250);
		int mode, hard;

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

		mode=input_menu();
		if (mode == 0)
			break;

		cct_cls();
		cout << "��ѡ���Ѷȣ�" << endl;
		cout << "1.����(9 * 9 - 10����)" << endl;
		cout << "2.�м�(16 * 16 - 40����)" << endl;
		cout << "3.�߼�(16 * 30 - 99����)" << endl;
		cout << "������[1..3]��";
		hard = input_menu(1, 3);
		begin(hard, mode);
		to_be_continued("   ");
	}
	return 0;
}
