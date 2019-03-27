#include"BitList.h"
#include"function.h"
#include"miracl.h"

//�²���һ���ڵ㲢��ʼ��
BitList* NewBitList(int initValue)
{
	//miracl *mip = mirsys(16, Max);
	BitList* bitList = (BitList*)malloc(sizeof(BitList));
	bitList->value = initValue;
	bitList->nextNode = NULL;
	return bitList;
}

//������ĩβ���һ��ʮ�������ַ�,����ͷ��Ϊ���ýڵ�
void AddHexToNode(BitList* headNode, char ch)
{
	//miracl *mip = mirsys(16, Max);
	//��ȡ���һ����Ч�ڵ�ָ��
	BitList *endNode = GetListEnd(headNode);

	int number = HexToInt(ch);
	short int bits[4];

	//��ȡbit��ʾ(��˷�)
	for (int i = 3; i >= 0; i--)
	{
		bits[i] = number % 2;
		number = number / 2;
	}

	//���뵽����β
	for (int i = 0; i < 4; i++)
	{
		endNode->nextNode = NewBitList(bits[i]);
		endNode = endNode->nextNode;
	}
}

//��ȡ����β��
BitList *GetListEnd(BitList* headNode)
{
	//miracl *mip = mirsys(16, Max);
	//��ȡ���һ����Ч�ڵ�ָ��
	BitList *endNode = headNode;
	while (endNode->nextNode != NULL)
	{
		endNode = endNode->nextNode;
	}
	return endNode;
}

//����β����ӽڵ�
void AddNode(BitList* headNode, int value)
{
	//miracl *mip = mirsys(16, Max);
	BitList *endNode = GetListEnd(headNode);
	endNode->nextNode = NewBitList(value);
}

//ʮ�������ַ�ת����
int HexToInt(char ch)
{
	//miracl *mip = mirsys(16, Max);
	int a = -1;
	switch (ch)
	{
	case '0': a = 0; break;
	case '1': a = 1; break;
	case '2': a = 2; break;
	case '3': a = 3; break;
	case '4': a = 4; break;
	case '5': a = 5; break;
	case '6': a = 6; break;
	case '7': a = 7; break;
	case '8': a = 8; break;
	case '9': a = 9; break;
	case 'a': a = 10; break;
	case 'b': a = 11; break;
	case 'c': a = 12; break;
	case 'd': a = 13; break;
	case 'e': a = 14; break;
	case 'f': a = 15; break;
	case 'A': a = 10; break;
	case 'B': a = 11; break;
	case 'C': a = 12; break;
	case 'D': a = 13; break;
	case 'E': a = 14; break;
	case 'F': a = 15; break;
	default:
		break;
	}
	return a;
}

//�ͷŶ�������
void FreeList(BitList* headNode)
{
	//miracl *mip = mirsys(16, Max);
	while (headNode != NULL)
	{
		BitList* node = headNode->nextNode;
		free(headNode);
		headNode = node;
	}
}

big BitListToBig(BitList* headNode, int startIndex, int length)
{
	//miracl *mip = mirsys(16, Max);
	big value = mirvar(0);
	BitList *node = headNode;

	//��ת����Ӧ������
	for (int i = 0; i < startIndex; i++)
	{
		node = node->nextNode;
	}

	//��ȡlength���ڵ�
	for (int i = 0; i < length; i++)
	{
		value=Multiply(value, mirvar(2));			//value*=2;
		value=Add(value, mirvar(node->value));		//value+=node->value;
		node = node->nextNode;
	}

	return value;
}

void AddCharsToNode(BitList* headNode, char* array, int length)
{
	//miracl *mip = mirsys(16, Max);
	for (int i = 0; i < length; i++)
	{
		AddHexToNode(headNode, array[i]);
	}
}