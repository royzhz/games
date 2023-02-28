/*2050271 信-20 张睿*/
#include <iostream>
#include <ctime>
#include <iomanip>
#include "../include/cmd_console_tools.h"
#include"90-02-b1.h"
#include "../include/common_input.h"
#include "../include/common_output.h"
#include "../include/common_core.h"
using namespace std;



void cmd_changelocation(cell table[12][12], int unusedcellcolumn, int usedcellcolumn, int unusedcellline, int usedcellline, int mode = 1)
{

	if (mode == 2)
	{
		if (unusedcellcolumn == usedcellcolumn)
		{
			g_cell_move_line(unusedcellline, unusedcellcolumn, usedcellline, usedcellcolumn, table);
		}
		if (unusedcellline == usedcellline)
		{
			g_cell_move_column(unusedcellline, unusedcellcolumn, usedcellline, usedcellcolumn, table);
		}
	}

	cell middle;
	middle = table[unusedcellline][unusedcellcolumn];
	table[unusedcellline][unusedcellcolumn] = table[usedcellline][usedcellcolumn];
	table[usedcellline][usedcellcolumn] = middle;
}

void movecolumn(cell table[12][12], int line, int column, int s[12], int mode)
{

	for (int i = 1; i <= column; i++)
	{
		int dist = -1, start = -1;
		if (s[i] != line)
			continue;
		else
		{
			dist = i;
			while (1)
			{
				i++;
				if (i > 10)
					return;
				if (s[i] != line)
				{
					start = i;
					break;
				}
			}
			for (int j = 1; j <= line; j++)
			{
				if (table[j][start].num != 0)
					cmd_changelocation(table, start, dist, j, j, mode);
			}
			int middle = s[start];
			s[start] = s[dist];
			s[dist] = middle;
			i = 1;
			continue;

		}

	}
}


int leftcell(cell table[12][12], int line, int column)
{
	int su = 0;
	for (int i = 1; i <= line; i++)
	{
		for (int j = 1; j <= column; j++)
		{
			if (table[i][j].open == 0)
				su++;
		}
	}
	return su;
}

//移动与动画函数
void move(cell table[12][12], int line, int& column,int mode=1)
{
	int i = line, lowest, s[12] = { 0 };
	for (int j = 1; j <= column; j++)
	{
		i = line, lowest = 0;
		while (1)
		{
			if (table[i][j].num == 0)
				s[j]++;
			if (table[i][j].num == 0 && i >= lowest)
			{
				lowest = i;
				i--;
			}
			else if (table[i][j].num != 0 && lowest != 0)
			{
				cmd_changelocation(table, j, j, i, lowest,	mode);
				i = line, lowest = 0,s[j]=0;
				continue;
			}
			else
				i--;
			if (i ==0)
				break;
		}

	}
	movecolumn(table, line, column, s, mode);
}


//打开主函数



void clear(cell table[12][12], int line, int column)//确认清除
{
	for (int i = 1; i < line + 1; i++)
	{
		for (int j = 1; j < column + 1; j++)
		{
			if (table[i][j].open == 1)
			{
				table[i][j].open = 2;
				table[i][j].num = 0;
			}
		}
	}
}





int inandprint(int hang, int lie, cell table[12][12],int &locationx,int &locationy)//画出图，输入消去坐标再画出,并获得消去格子的坐标
{ 
	cmd_print(hang, lie, table, 2,"123456789abcdefg","ABCDEFGHIJKLMN");

	char x, y;
	int s=0;
	while (1)
	{

		input_normal(x, y, "请以字母+数字形式[例：c2]输入矩阵坐标：", lie, hang);
		if (table[x - 'A' + 1][y - '0' + 1].open == 2)
		{
			cout <<" 不能清除已经清除过的，请重新输入" << endl;
			continue;
		}

		open(table, x - 'A' + 1, y - '0' + 1,s);
		locationx = x - 'A' + 1;
		locationy = y - '0' + 1;

		if (!s)
		{
			table[x - 'A' + 1][y - '0' + 1].open = 0;
			cout << "输入的矩阵坐标位置处无连续相同值，请重新输入" << endl;
		}

		else
		{
			cmd_print(hang, lie, table, 0,"123456789abcdefg", "ABCDEFGHIJKLMN");
			cmd_print(hang, lie, table, 2, "123456789abcdefg", "ABCDEFGHIJKLMN");
			break;
		}
	}
	return s*s*5;
}

//取消选择处理函数
void beback(cell table[12][12])//取消选择
{
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (table[i][j].open == 1)
				table[i][j].open = 0;
		}
	}
}

//检查是否结束函数
int checkaround(cell table[12][12],int line,int column)//1为继续，0为结束,2为完全消除
{
	int s = 0;
	for (int i = 1; i <= line; i++)
	{
		for (int j = 1; j <= column; j++)
		{
			if (table[i][j].num==0)
			{
				s++;
				continue;
			}
			if (table[i + 1][j].num == table[i][j].num)
				return 1;
			if (table[i - 1][j].num == table[i][j].num)
				return 1;
			if (table[i][j - 1].num == table[i][j].num)
				return 1;
			if (table[i][j + 1].num == table[i][j].num)
				return 1;
		}
	}
	return 0;
}


//cmd下确认消除
void cmd_eliminate(cell table[12][12], int score, int nowscore, int hang, int lie)
{
	clear(table, hang, lie);
	cout << "本次得分：" << nowscore << " 总得分：" << score << endl << endl;
	cmd_print(hang, lie, table, 2, "123456789abcdefg", "ABCDEFGHIJKLMN");
	to_be_continued("按回车键进行数组下落操作...\n");
	move(table, hang, lie, 1);
	cmd_print(hang, lie, table, 2, "123456789abcdefg", "ABCDEFGHIJKLMN");
}


//设置cell数字
void setnumber(cell table[12][12],int hang,int lie)
{
	srand((unsigned int)(time(0)));

	for (int i = 1; i < hang + 1; i++)
	{
		for (int j = 1; j < lie + 1; j++)
		{
			table[i][j].open = false;
			table[i][j].num = rand() % 5 + 1;
		}
	}
}

//命令行模式
int cmd_begin(int mode, int hang, int lie)
{
	cell table[12][12];
	setnumber(table, hang, lie);

	while (1)
	{
		int x, y, nowscore, score = 0;

		while (1)
		{
			nowscore = inandprint(hang, lie, table, x, y);
			score = score + nowscore;
			if (mode != 1)
			{
				cout << "请确认是否把" << char(x + 'A' - 1) << char(y + '0' - 1) << "及周围的相同值消除(Y/N/Q)：";
				char choose = input_menu("YNQ", 3);
				if (choose == 'Y')
				{
					cmd_eliminate(table, score, nowscore, hang, lie);
					if (!checkaround(table, hang, lie))
					{
						to_be_continued("游戏结束，下一关");
						if (mode !=3)
							return 0;
						break;
					}
				}
				else if (choose == 'Q')
					return -1;
				else
					beback(table);//还原操作前的数组
			}
			to_be_continued("回车继续");
			if (mode != 3)
				return 0;
		}
	}
	return 0;

}


int mouse_move(int line, int column, cell table[12][12],int before[2],int mode)
{
	cct_setcolor(table[before[0]][before[1]].num + 1, 0);
	g_cell(before[0],before[1],mode);
	cct_setcolor(table[line][column].num + 1, 7);
	g_cell(line, column,mode);
	return 0;
}


//键盘输入处理
void keyboard(int keycode1, int keycode2, int& cell_line, int& cell_column, int line, int column, cell table[12][12])
{
	while (1)
	{
		if (keycode2 == KB_ARROW_UP && keycode1 == 0xe0)
		{
			cell_line--;
			if (cell_line < 1)
				cell_line = line;

		}
		else if (keycode2 == KB_ARROW_DOWN && keycode1 == 0xe0)
		{
			cell_line++;
			if (cell_line > line)
				cell_line = 1;
		}
		else if (keycode2 == KB_ARROW_LEFT && keycode1 == 0xe0)
		{
			cell_column--;
			if (cell_column < 1)
				cell_column = column;
		}
		else if (keycode2 == KB_ARROW_RIGHT && keycode1 == 0xe0)
		{
			cell_column++;
			if (cell_column > column)
				cell_column = 1;
		}
		if (table[cell_line][cell_column].open == 0)
		{
			break;
		}
	}
}







void mouseaction(int size_line, int size_column, int line, int column, cell table[12][12], int& returnline, int& returncolumn, int mode)//1为正常，2为E,意思为大小，行列数，返回的坐标
{
	//建立变量，准备工作
	int X = 0, Y = 0;//x是列，y是行
	int  maction;
	int keycode1, keycode2;
	int before[2] = { returnline,returncolumn };
	int cell_line = returnline, cell_column = returncolumn, showlocation = line * 3 + 4;
	cct_enable_mouse();
	cct_setcursor(CURSOR_INVISIBLE);
	cct_gotoxy(0, showlocation);
	cct_setcolor();


	//根据外部模式设立内部模式
	int fmode = 1;
	if (mode == 5)
		fmode = 2;
	if (mode == 2)
		showlocation = line * (size_line + 2) - 3;


	//进入循环
	while (1)
	{
		//获取鼠标,键盘状态
		maction = -1;
		cct_setcolor();
		int ret;
		ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
		keyboard(keycode1, keycode2, cell_line, cell_column, line, column, table);
		//x = X, y = Y;
		int rx = (X + 2) / size_column, ry = (Y) / size_line;

		//鼠标事件处理
		if (ret == CCT_MOUSE_EVENT)
		{
			if (mode == 1)
			{
				if (rx <= 0 || rx > column || ry <= 0 || ry > line || table[ry][rx].open == 2)
				{
					cct_gotoxy(0, showlocation);
					cout << "位置错误                                                              ";
					cct_setcolor(table[before[0]][before[1]].num + 1, 0);
					g_cell(before[0], before[1], 1);
					continue;

				}
				else
				{
					cell_column = rx;
					cell_line = ry;
				}
			}
			else if (mode == 2)
			{

				if(X<4|| X>column * (size_column + 2) + 1 || Y<3 || Y>line * (size_line + 1) + 1 || X % 8 == 2 || X % 8 == 3 || Y % 4 == 2)
				{
					cct_gotoxy(0, showlocation);
					cout << "位置错误                                                           ";
					cct_setcolor(table[before[0]][before[1]].num + 1, 0);
					g_cell(before[0], before[1], 2);
					continue;
				}
				else
				{
					cell_column = (X + 4) / 8, cell_line = (Y + 1) / 4;
				}

			}
		}

		//显示坐标，设置回显
		cct_gotoxy(0, showlocation);
		cout << "[当前鼠标位置] X:" << cell_column - 1 << " Y:" << char(cell_line + 'A' - 1) << "                                                      ";
		mouse_move(cell_line, cell_column, table, before, mode);
		before[0] = cell_line;
		before[1] = cell_column;

		//左键、回车处理
		if (maction == MOUSE_LEFT_BUTTON_CLICK || keycode1 == 13)
		{
			cct_gotoxy(0, showlocation);
			cct_setcolor();
			cout << "选中了" << cell_column - 1 << char(cell_line + 'A' - 1) << "                                            ";
			returnline = cell_line, returncolumn = cell_column;
			break;
		}
	}
}

//显示分数函数
void showscore(int hang,int s,int score)
{
	cct_gotoxy(0, hang * 3 + 6);
	cct_setcolor();

	cout << "本次得分:";
	if (s * s * 5 >= 100)
		cct_setcolor(0, 6);
	if (s * s * 5 >= 300)
		cct_setcolor(0, 13);
	cout << setw(6) << s * s * 5;
	cct_setcolor();
	cout << "      总得分:";
	if (score >= 500)
		cct_setcolor(0, 6);
	if (score >= 1000)
		cct_setcolor(0, 13);
	cout << setw(6) << score;
}

//结束游戏提示函数
void end_game(int score,int left,int hang)
{
	int finscore = score;
	if (left <= 10)
		finscore = finscore + 200;
	if (left <= 5)
		finscore = finscore + 200;
	if (left == 0)
		finscore = finscore + 500;

	cct_gotoxy(0, hang * 3 + 6);
	cct_setcolor();
	cct_setcolor(0, 6);
	cout << endl << "还有" << left << "颗星                                       " << endl;
	cct_setcolor();
	cout << "奖励 " << finscore - score << " 分                                " << endl;
	cout << "最终得分:";

	if (finscore >= 1500)
		cct_setcolor(0, 13);
	cout << setw(6) << finscore << "                               " << endl;
}


int g_begin(int mode, int hang, int lie)
{
	//build table
	cell table[12][12];
	setnumber(table, hang, lie);
	int fmode = 1;
	if (mode == 5)
		fmode = 2;

	//print map
	gmap(hang, lie, 3, 6, fmode);

	//print all cell
	for (int i = 1; i < hang + 1; i++)
	{
		for (int j = 1; j < lie + 1; j++)
		{
			cct_setcolor(table[i][j].num + 1, 0);
			g_cell(i, j, fmode);
		}
	}

	int returnline = 1, returncolumn = 1;
	int score = 0;

	while (1)
	{

		int X = 0, Y = 0;//x是列，y是行
		int  maction = -1;
		int keycode1 = 0, keycode2 = 0;


		//获取所选按键
		mouseaction(3, 6, hang, lie, table, returnline, returncolumn, fmode);

		//print 提示
		if (mode < 6)
		{
			to_be_continued("回车继续");
			return 0;
		}
		else
		{
			cct_gotoxy(0, hang * 3 + 4);
			cout << "箭头/鼠标移动取消，回车/单击左键合成            ";
		}


	    //打开
		int s=0;
		open(table, returnline, returncolumn,s);


		//初步处理
		if (s == 0)
		{
			table[returnline][returncolumn].open = 0;
			cct_gotoxy(0, hang * 3 + 4);
			cout << "单个不可消除                               ";
			continue;
		}
		else
		{
			setcellcolor(table, 7, hang, lie, 1);
		}

		while (1)
		{
			//获得鼠标键盘状态
			cct_setcolor();
			cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
			int rx = (X + 2) / 6, ry = (Y) / 3;

			//点击左键或者回车
			if (maction == MOUSE_LEFT_BUTTON_CLICK || keycode1 == 13|| maction == MOUSE_LEFT_BUTTON_DOUBLE_CLICK)
			{
				//清除被选内容
				setcellcolor(table, 7, hang, lie, 2);
				clear(table, hang, lie);

				//得分累加
				score = score + s * s * 5;

				//mode6特殊内容，可忽略
				while (mode == 6)
				{
					cct_gotoxy(0, hang * 3 + 4);
					cct_setcolor();
					cout << "回车或单击消除                                             ";
					cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
					if (maction == MOUSE_LEFT_BUTTON_CLICK || keycode1 == 13)
					{
						move(table, hang, lie, 2);
						cct_gotoxy(0, hang * 3 + 5);
						to_be_continued("回车继续");
						return 0;
					}
				}

				//移动数组和动画
				move(table, hang, lie, 2);

				//目前焦点返回第一个没开过的数组
				for (int i = 1, k = 1; i < hang + 1 && k == 1; i++)
				{
					for (int j = 1; j < lie + 1; j++)
					{
						if (table[i][j].open == 0)
						{
							returnline = i, returncolumn = j;
							k = 2;
							break;

						}
					}
				}


				//draw first cell
				cct_setcolor(table[returnline][returncolumn].num + 1, 7);
				g_cell(returnline, returncolumn, fmode);

				//显示分数
				showscore(hang, s, score);

				//检测是否终止状态
				if (!checkaround(table, hang, lie))
				{
					int left = leftcell(table, hang, lie), finscore = score;
					end_game(score, left, hang);
					to_be_continued("游戏结束，下一关");
					return left;
				}
				break;
			}
			//移动或点击方向键
			else if (keycode1 == 0xe0 || returncolumn != rx || returnline != ry)
			{
				//取消选中
				setcellcolor(table, 0, hang, lie, 1);
				beback(table);
				if (rx > 0 && rx <= lie && ry > 0 && ry <= hang && table[ry][rx].num != 0)
					returncolumn = rx, returnline = ry;
				break;
			}
		}
	}

	cout << endl << endl;

}








