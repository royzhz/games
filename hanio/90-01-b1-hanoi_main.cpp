/*2050271 信20 张睿*/
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
		cout << "1.基本解" << endl;
		cout << "2.基本解(步数记录)" << endl;
		cout << "3.内部数组显示(横向)" << endl;
		cout << "4.内部数组显示(纵向 + 横向)" << endl;
		cout << "5.图形解 - 预备 - 画三个圆柱" << endl;
		cout << "6.图形解 - 预备 - 在起始柱上画n个盘子" << endl;
		cout << "7.图形解 - 预备 - 第一次移动" << endl;
		cout << "8.图形解 - 自动移动版本" << endl;
		cout << "9.图形解 - 游戏版" << endl;
		cout << "0.退出" << endl;
		cout << "----------------------------------" << endl;
		cout << "[请选择:] ";
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
