/*2050271 ��20 ���*/
#pragma once

/* -----------------------------------------

     ���ļ����ܣ�
	1��Ϊ�˱�֤ hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp ���໥���ʺ����ĺ�������
	2��һ�����ϵ�cpp���õ��ĺ궨�壨#define����ȫ��ֻ����const����������������
	3�����Բο� cmd_console_tools.h ��д���������Ķ�����ᣩ
   ----------------------------------------- */

void chen(int *a, char *b, char *c,int mode);
char zhong(char b,char c);
void hanoi(int n, char src, char tmp, char dst,int mode);
void begin(int n, char src, char tmp, char dst,int mode);
void yuanzhu();
void to_be_continued(int x);
void yuanpan(char src, int n);
void movepan(int panchang, char src, char dst, int mode, int n);
int yidong(int censhu);