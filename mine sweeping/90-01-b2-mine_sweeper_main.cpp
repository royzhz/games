/*2050271 信20 张睿*/
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
		cct_setfontsize("新宋体", 20);
		cct_setconsoleborder(80, 30,80,250);
		int mode, hard;

		cout << "------------------------------------------" << endl;
		cout << "1.选择难度并显示内部数组" << endl;
		cout << "2.输入初始位置并显示被打开的初始区域" << endl;
		cout << "3.内部数组基础版" << endl;
		cout << "4.内部数组完整版（标记、运行时间）" << endl;
		cout << "5.画出伪图形化框架并显示内部数据" << endl;
		cout << "6.检测鼠标位置和合法性（左键单击退出）" << endl;
		cout << "7.鼠标选择初始位置并显示被打开的初始区域" << endl;
		cout << "8.伪图形界面基础版" << endl;
		cout << "9.伪图形界面完整版" << endl;
		cout << "0.退出游戏" << endl;
		cout << "------------------------------------------" << endl;
		cout << "[请选择] :";

		mode=input_menu();
		if (mode == 0)
			break;

		cct_cls();
		cout << "请选择难度：" << endl;
		cout << "1.初级(9 * 9 - 10颗雷)" << endl;
		cout << "2.中级(16 * 16 - 40颗雷)" << endl;
		cout << "3.高级(16 * 30 - 99颗雷)" << endl;
		cout << "请输入[1..3]：";
		hard = input_menu(1, 3);
		begin(hard, mode);
		to_be_continued("   ");
	}
	return 0;
}
