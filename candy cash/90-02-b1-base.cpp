/*2050271 ��-20 ���*/
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

//�ƶ��붯������
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


//��������



void clear(cell table[12][12], int line, int column)//ȷ�����
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





int inandprint(int hang, int lie, cell table[12][12],int &locationx,int &locationy)//����ͼ��������ȥ�����ٻ���,�������ȥ���ӵ�����
{ 
	cmd_print(hang, lie, table, 2,"123456789abcdefg","ABCDEFGHIJKLMN");

	char x, y;
	int s=0;
	while (1)
	{

		input_normal(x, y, "������ĸ+������ʽ[����c2]����������꣺", lie, hang);
		if (table[x - 'A' + 1][y - '0' + 1].open == 2)
		{
			cout <<" ��������Ѿ�������ģ�����������" << endl;
			continue;
		}

		open(table, x - 'A' + 1, y - '0' + 1,s);
		locationx = x - 'A' + 1;
		locationy = y - '0' + 1;

		if (!s)
		{
			table[x - 'A' + 1][y - '0' + 1].open = 0;
			cout << "����ľ�������λ�ô���������ֵͬ������������" << endl;
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

//ȡ��ѡ������
void beback(cell table[12][12])//ȡ��ѡ��
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

//����Ƿ��������
int checkaround(cell table[12][12],int line,int column)//1Ϊ������0Ϊ����,2Ϊ��ȫ����
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


//cmd��ȷ������
void cmd_eliminate(cell table[12][12], int score, int nowscore, int hang, int lie)
{
	clear(table, hang, lie);
	cout << "���ε÷֣�" << nowscore << " �ܵ÷֣�" << score << endl << endl;
	cmd_print(hang, lie, table, 2, "123456789abcdefg", "ABCDEFGHIJKLMN");
	to_be_continued("���س������������������...\n");
	move(table, hang, lie, 1);
	cmd_print(hang, lie, table, 2, "123456789abcdefg", "ABCDEFGHIJKLMN");
}


//����cell����
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

//������ģʽ
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
				cout << "��ȷ���Ƿ��" << char(x + 'A' - 1) << char(y + '0' - 1) << "����Χ����ֵͬ����(Y/N/Q)��";
				char choose = input_menu("YNQ", 3);
				if (choose == 'Y')
				{
					cmd_eliminate(table, score, nowscore, hang, lie);
					if (!checkaround(table, hang, lie))
					{
						to_be_continued("��Ϸ��������һ��");
						if (mode !=3)
							return 0;
						break;
					}
				}
				else if (choose == 'Q')
					return -1;
				else
					beback(table);//��ԭ����ǰ������
			}
			to_be_continued("�س�����");
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


//�������봦��
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







void mouseaction(int size_line, int size_column, int line, int column, cell table[12][12], int& returnline, int& returncolumn, int mode)//1Ϊ������2ΪE,��˼Ϊ��С�������������ص�����
{
	//����������׼������
	int X = 0, Y = 0;//x���У�y����
	int  maction;
	int keycode1, keycode2;
	int before[2] = { returnline,returncolumn };
	int cell_line = returnline, cell_column = returncolumn, showlocation = line * 3 + 4;
	cct_enable_mouse();
	cct_setcursor(CURSOR_INVISIBLE);
	cct_gotoxy(0, showlocation);
	cct_setcolor();


	//�����ⲿģʽ�����ڲ�ģʽ
	int fmode = 1;
	if (mode == 5)
		fmode = 2;
	if (mode == 2)
		showlocation = line * (size_line + 2) - 3;


	//����ѭ��
	while (1)
	{
		//��ȡ���,����״̬
		maction = -1;
		cct_setcolor();
		int ret;
		ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
		keyboard(keycode1, keycode2, cell_line, cell_column, line, column, table);
		//x = X, y = Y;
		int rx = (X + 2) / size_column, ry = (Y) / size_line;

		//����¼�����
		if (ret == CCT_MOUSE_EVENT)
		{
			if (mode == 1)
			{
				if (rx <= 0 || rx > column || ry <= 0 || ry > line || table[ry][rx].open == 2)
				{
					cct_gotoxy(0, showlocation);
					cout << "λ�ô���                                                              ";
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
					cout << "λ�ô���                                                           ";
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

		//��ʾ���꣬���û���
		cct_gotoxy(0, showlocation);
		cout << "[��ǰ���λ��] X:" << cell_column - 1 << " Y:" << char(cell_line + 'A' - 1) << "                                                      ";
		mouse_move(cell_line, cell_column, table, before, mode);
		before[0] = cell_line;
		before[1] = cell_column;

		//������س�����
		if (maction == MOUSE_LEFT_BUTTON_CLICK || keycode1 == 13)
		{
			cct_gotoxy(0, showlocation);
			cct_setcolor();
			cout << "ѡ����" << cell_column - 1 << char(cell_line + 'A' - 1) << "                                            ";
			returnline = cell_line, returncolumn = cell_column;
			break;
		}
	}
}

//��ʾ��������
void showscore(int hang,int s,int score)
{
	cct_gotoxy(0, hang * 3 + 6);
	cct_setcolor();

	cout << "���ε÷�:";
	if (s * s * 5 >= 100)
		cct_setcolor(0, 6);
	if (s * s * 5 >= 300)
		cct_setcolor(0, 13);
	cout << setw(6) << s * s * 5;
	cct_setcolor();
	cout << "      �ܵ÷�:";
	if (score >= 500)
		cct_setcolor(0, 6);
	if (score >= 1000)
		cct_setcolor(0, 13);
	cout << setw(6) << score;
}

//������Ϸ��ʾ����
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
	cout << endl << "����" << left << "����                                       " << endl;
	cct_setcolor();
	cout << "���� " << finscore - score << " ��                                " << endl;
	cout << "���յ÷�:";

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

		int X = 0, Y = 0;//x���У�y����
		int  maction = -1;
		int keycode1 = 0, keycode2 = 0;


		//��ȡ��ѡ����
		mouseaction(3, 6, hang, lie, table, returnline, returncolumn, fmode);

		//print ��ʾ
		if (mode < 6)
		{
			to_be_continued("�س�����");
			return 0;
		}
		else
		{
			cct_gotoxy(0, hang * 3 + 4);
			cout << "��ͷ/����ƶ�ȡ�����س�/��������ϳ�            ";
		}


	    //��
		int s=0;
		open(table, returnline, returncolumn,s);


		//��������
		if (s == 0)
		{
			table[returnline][returncolumn].open = 0;
			cct_gotoxy(0, hang * 3 + 4);
			cout << "������������                               ";
			continue;
		}
		else
		{
			setcellcolor(table, 7, hang, lie, 1);
		}

		while (1)
		{
			//���������״̬
			cct_setcolor();
			cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
			int rx = (X + 2) / 6, ry = (Y) / 3;

			//���������߻س�
			if (maction == MOUSE_LEFT_BUTTON_CLICK || keycode1 == 13|| maction == MOUSE_LEFT_BUTTON_DOUBLE_CLICK)
			{
				//�����ѡ����
				setcellcolor(table, 7, hang, lie, 2);
				clear(table, hang, lie);

				//�÷��ۼ�
				score = score + s * s * 5;

				//mode6�������ݣ��ɺ���
				while (mode == 6)
				{
					cct_gotoxy(0, hang * 3 + 4);
					cct_setcolor();
					cout << "�س��򵥻�����                                             ";
					cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
					if (maction == MOUSE_LEFT_BUTTON_CLICK || keycode1 == 13)
					{
						move(table, hang, lie, 2);
						cct_gotoxy(0, hang * 3 + 5);
						to_be_continued("�س�����");
						return 0;
					}
				}

				//�ƶ�����Ͷ���
				move(table, hang, lie, 2);

				//Ŀǰ���㷵�ص�һ��û����������
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

				//��ʾ����
				showscore(hang, s, score);

				//����Ƿ���ֹ״̬
				if (!checkaround(table, hang, lie))
				{
					int left = leftcell(table, hang, lie), finscore = score;
					end_game(score, left, hang);
					to_be_continued("��Ϸ��������һ��");
					return left;
				}
				break;
			}
			//�ƶ����������
			else if (keycode1 == 0xe0 || returncolumn != rx || returnline != ry)
			{
				//ȡ��ѡ��
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








