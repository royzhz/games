/*2050271 信20 张睿*/
#pragma once

int input_menu(int start=0, int end=10);
char input_menu(const char choice[], const int no);
char menu(const char name[][100], const char choice[], const int no);
int input_normal(int start, int end, const char name[], bool feedback = 0, int x = -1, int y = -1, bool enter = 1);
void to_be_continued(const char name[] = "按回车键继续...");
void input_normal(char& xline, char& ycolumn, const char name[], int column, int line);