#pragma once
#include"miracl.h"
#include"mirdef.h"
#include<stdlib.h>
extern int Max;
//定义一个结构体，表示一个bit节点
typedef struct BitList
{
	short int value;
	struct BitList* nextNode;
}BitList;

//新产生一个节点并初始化
BitList* NewBitList(int initValue);
//获取链表尾部
BitList *GetListEnd(BitList* headNode);
//十六进制字符转数字
int HexToInt(char ch);
//释放堆区链表
void FreeList(BitList* headNode);
//计算一个bit链表所表示的值
big BitListToBig(BitList* headNode, int startIndex, int length);

//链表尾部添加节点
void AddNode(BitList* headNode, int value);
//向链表末尾添加一个十六进制字符,链表头部为无用节点
void AddHexToNode(BitList* headNode, char ch);
//向链表末尾添加十六进制数组,链表头部为无用节点
void AddCharsToNode(BitList* headNode, char* array,int length);

