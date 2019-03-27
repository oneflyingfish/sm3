#pragma once
#include"BitList.h"
#include"miracl.h"
#include"mirdef.h"
#include"InputInfo.h"
#include<stdio.h>

#define maxInputLength 2000
//�ⲿ���������ļ�·��
extern int Max;

//��ȡ�����ļ�
InputInfo* ReadInputFile(char* filePath);
//�����Ϣ
void FillInputInfo(InputInfo *inputInfo);
//����Ϣ����
GroupsInfo* DivideIntoGroups(InputInfo *inputInfo);
//��ȡ������ĳ���ֱ�ʾ��ֵ
big ReadNumber(int *array,int startIndex,int length);
//��ȡ������ĳ���ֱ�ʾ��ʮ�������ַ�
char ReadHexChar(int *array, int startIndex);
//���ֽڴ���ת��Ϊʮ�������ַ���
char* BigWordToHexString(big value);

//ʵ��SM3���ú�����ע���ڲ����ֽ�big���Դ�˷��洢��index=0��Ӧ���λbit��

//���ֽ�bigת��Ϊ����(<=32bit)
int BigWordToInt(big value);
//����
big Tj(int j);
//��������
big GGj(int j, big X, big Y, big Z);
big FFj(int j, big X, big Y, big Z);
//�û�����
big Px0(big value);
big Px1(big value);
//ѹ������
big* CF(big* Vi, GroupsInfo *groupInfo, int i);

//word��������
big And(big x, big y);
big Or(big x, big y);
big Not(big x);
big Xor(big x, big y);
big Add(big x, big y);
big Multiply(big x, big y);
big Divide(big x, big y);
big Mod(big x, big y);
big shiftLeft(big x, int length);

