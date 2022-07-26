
#ifndef __TOOLS_H
#define __TOOLS_H //工具函数

#include "head.h"



char getch(); //获取一个键盘输入

void gotoxy(int x, int y); //移动光标到指定位置

void arr2pnt(char * des,char src[],int len); //数组转指针

void locRemoveR(char * way); //去除字符串结尾的换行符

char **split(const char *source, char flag); //分割字符串

void Input(char * res,int type); //输入函数

void delay();

void timeC(); //获取当前系统时间

void timeSimple(); //精确到天

void clearDown(); //清空界面下方的提示信息,避免不同输出互相叠加

#define MAXINPUT 20

#endif