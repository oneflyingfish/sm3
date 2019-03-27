#pragma once
#include"miracl.h"
#include"mirdef.h"
#include<stdlib.h>
extern int Max;
//����һ���ṹ�壬��ʾһ��bit�ڵ�
typedef struct BitList
{
	short int value;
	struct BitList* nextNode;
}BitList;

//�²���һ���ڵ㲢��ʼ��
BitList* NewBitList(int initValue);
//��ȡ����β��
BitList *GetListEnd(BitList* headNode);
//ʮ�������ַ�ת����
int HexToInt(char ch);
//�ͷŶ�������
void FreeList(BitList* headNode);
//����һ��bit��������ʾ��ֵ
big BitListToBig(BitList* headNode, int startIndex, int length);

//����β����ӽڵ�
void AddNode(BitList* headNode, int value);
//������ĩβ���һ��ʮ�������ַ�,����ͷ��Ϊ���ýڵ�
void AddHexToNode(BitList* headNode, char ch);
//������ĩβ���ʮ����������,����ͷ��Ϊ���ýڵ�
void AddCharsToNode(BitList* headNode, char* array,int length);

