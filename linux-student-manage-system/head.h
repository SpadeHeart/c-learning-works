

#ifndef __HEAD_H
#define __HEAD_H //基本头文件包含

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>
//#include <conio.h> //linux下没有这个库

#define TYPE_NUM 1  //数字输入 （允许输入 . ）
#define TYPE_ALPHA 2  //字母输入
#define TYPE_CHINESE 3 //汉字输入

// char * weekTransform[7] = {"周日","周一","周二","周三","周四","周五","周六"};

int InputX;
int InputY;

typedef struct Stu{
    char *id;
    char *name;
    char *age;
    char *grade;
    char *fee;
}Student;

#endif