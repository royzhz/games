/*2050271 –≈20 ’≈Ó£*/
#pragma once
#include <Windows.h>


void begin(int hard,int mode);
void shuruzuobiao(int& x, int& y,int hard,int mode);
void confirmsize(int& size_x, int& size_y, int& number, int hard);
void putlei(int map[18][32], int hard);
int win(int s, int hard,int mode=1);
void shuru4(int& x, int& y, int& z, int hard);
void gmap(int hard,int mode=6);
void gopen(int map[18][32],int hard);
void gopengezi(int map[18][32], int x, int y, int youjian = 0);
int shubiao(int hard, int& x, int& y ,int mode = 6);
void gotodiduan(int hard);
int shubiao2(int hard, int& x, int& y, int mode, int opennum[18][32], int map[18][32], int left, LARGE_INTEGER begin, LARGE_INTEGER tick);
void tishi(int mode, LARGE_INTEGER begin, LARGE_INTEGER tick, int z = 0, int left = 0);
void shijian(LARGE_INTEGER begin, LARGE_INTEGER tick);