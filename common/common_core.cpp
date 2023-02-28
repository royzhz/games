/*2050271 ĞÅ20 ÕÅî£*/
#include <iostream>
#include <conio.h>
#include <iomanip>
#include "../include/cmd_console_tools.h"
using namespace std;

struct cell
{
	int num = 0;
	int open = 2;
};

int open(cell table[12][12], int line, int column, int& sum)
{
	table[line][column].open = true;
	if (table[line + 1][column].open == false && table[line + 1][column].num == table[line][column].num)
	{
		sum++;
		open(table, line + 1, column, sum);
	}
	if (table[line - 1][column].open == false && table[line - 1][column].num == table[line][column].num)
	{
		sum++;
		open(table, line - 1, column, sum);
	}
	if (table[line][column - 1].open == false && table[line][column - 1].num == table[line][column].num)
	{
		sum++;
		open(table, line, column - 1, sum);
	}
	if (table[line][column + 1].open == false && table[line][column + 1].num == table[line][column].num)
	{
		sum++;
		open(table, line, column + 1, sum);
	}
	return sum;
}

