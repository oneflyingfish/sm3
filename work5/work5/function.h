#pragma once
#include"BitList.h"
#include"miracl.h"
#include"mirdef.h"
#include"InputInfo.h"
#include<stdio.h>

#define maxInputLength 2000
//外部导入输入文件路径
extern int Max;

//读取磁盘文件
InputInfo* ReadInputFile(char* filePath);
//填充消息
void FillInputInfo(InputInfo *inputInfo);
//对消息分组
GroupsInfo* DivideIntoGroups(InputInfo *inputInfo);
//读取数组中某部分表示的值
big ReadNumber(int *array,int startIndex,int length);
//读取数组中某部分表示的十六进制字符
char ReadHexChar(int *array, int startIndex);
//四字节大数转化为十六进制字符串
char* BigWordToHexString(big value);

//实现SM3内置函数，注：内部四字节big均以大端法存储（index=0对应最高位bit）

//四字节big转化为整形(<=32bit)
int BigWordToInt(big value);
//常量
big Tj(int j);
//布尔函数
big GGj(int j, big X, big Y, big Z);
big FFj(int j, big X, big Y, big Z);
//置换函数
big Px0(big value);
big Px1(big value);
//压缩函数
big* CF(big* Vi, GroupsInfo *groupInfo, int i);

//word基本运算
big And(big x, big y);
big Or(big x, big y);
big Not(big x);
big Xor(big x, big y);
big Add(big x, big y);
big Multiply(big x, big y);
big Divide(big x, big y);
big Mod(big x, big y);
big shiftLeft(big x, int length);

