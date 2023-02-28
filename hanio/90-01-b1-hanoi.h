/*2050271 信20 张睿*/
#pragma once

/* -----------------------------------------

     本文件功能：
	1、为了保证 hanoi_main.cpp/hanoi_menu.cpp/hanoi_multiple_solutions.cpp 能相互访问函数的函数声明
	2、一个以上的cpp中用到的宏定义（#define）或全局只读（const）变量，个数不限
	3、可以参考 cmd_console_tools.h 的写法（认真阅读并体会）
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