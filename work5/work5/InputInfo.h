#pragma once
#include"BitList.h"
extern int Max;

//定义原始二进制链表
typedef struct InputInfo
{
	BitList *inputBitList;	//消息的二进制链表形式
	int size;				//链表有效节点的个数（不包含头部节点）
}InputInfo;

//存储计算Bn、Wn，因为miracl限制，Bn设计但未计算
typedef struct GroupsInfo
{
	big bwn[100][133];			//最大支持100个B，即512*100bit bwn[n][0]表示Bn，  bwn[n][i]表示Wi-1, i>0
	int count;					//行个数
}GroupsInfo;

//产生并初始化GroupsInfo
GroupsInfo *NewGroupsInfo();