
#ifndef __IO_H
#define __IO_H //文件读写模块

#include "head.h"

//char * allData[50]; //存储所有用户信息

void addOne(Student * stu);  //添加一个新的学生

int getAll(char * allData[]); //显示所有学生

void getAllShow(char * allData[],int curp,int total); //页面打印

void getOne(char * id); //根据学号显示一个学生

void delOne(char * id); //根据学号删除一个学生

void delAll(); //删除所有学生

int idCheck(char * num); //学号重复性校验

void updateOne(Student * stu); //修改一个学生信息

#endif