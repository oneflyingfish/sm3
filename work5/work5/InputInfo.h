#pragma once
#include"BitList.h"
extern int Max;

//����ԭʼ����������
typedef struct InputInfo
{
	BitList *inputBitList;	//��Ϣ�Ķ�����������ʽ
	int size;				//������Ч�ڵ�ĸ�����������ͷ���ڵ㣩
}InputInfo;

//�洢����Bn��Wn����Ϊmiracl���ƣ�Bn��Ƶ�δ����
typedef struct GroupsInfo
{
	big bwn[100][133];			//���֧��100��B����512*100bit bwn[n][0]��ʾBn��  bwn[n][i]��ʾWi-1, i>0
	int count;					//�и���
}GroupsInfo;

//��������ʼ��GroupsInfo
GroupsInfo *NewGroupsInfo();