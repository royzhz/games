/*2050271 ��20 ���*/
#include <iostream>
#include "../include/cmd_console_tools.h"
#include"90-02-b1.h"
#include "../include/common_input.h"
using namespace std;

int main()
{
	cct_setconsoleborder(6* (9)+7,3 * (9)+15);
	int life = 100, guan = 1;;
	while (1)
	{
		cct_cls();
		cout << "����" << life << "����    ��" << guan << "��";
		life=life-g_begin(7, 9, 9);
		if (life <= 0)
			break;
		guan++;
	}
	cout << "��Ϸ������";
	system("pause");
	return 0;

}
