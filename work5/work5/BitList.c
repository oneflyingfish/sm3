#include"BitList.h"
#include"function.h"
#include"miracl.h"

//新产生一个节点并初始化
BitList* NewBitList(int initValue)
{
	//miracl *mip = mirsys(16, Max);
	BitList* bitList = (BitList*)malloc(sizeof(BitList));
	bitList->value = initValue;
	bitList->nextNode = NULL;
	return bitList;
}

//向链表末尾添加一个十六进制字符,链表头部为无用节点
void AddHexToNode(BitList* headNode, char ch)
{
	//miracl *mip = mirsys(16, Max);
	//获取最后一个有效节点指针
	BitList *endNode = GetListEnd(headNode);

	int number = HexToInt(ch);
	short int bits[4];

	//求取bit表示(大端法)
	for (int i = 3; i >= 0; i--)
	{
		bits[i] = number % 2;
		number = number / 2;
	}

	//加入到链表尾
	for (int i = 0; i < 4; i++)
	{
		endNode->nextNode = NewBitList(bits[i]);
		endNode = endNode->nextNode;
	}
}

//获取链表尾部
BitList *GetListEnd(BitList* headNode)
{
	//miracl *mip = mirsys(16, Max);
	//获取最后一个有效节点指针
	BitList *endNode = headNode;
	while (endNode->nextNode != NULL)
	{
		endNode = endNode->nextNode;
	}
	return endNode;
}

//链表尾部添加节点
void AddNode(BitList* headNode, int value)
{
	//miracl *mip = mirsys(16, Max);
	BitList *endNode = GetListEnd(headNode);
	endNode->nextNode = NewBitList(value);
}

//十六进制字符转数字
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

//释放堆区链表
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

	//跳转到相应的索引
	for (int i = 0; i < startIndex; i++)
	{
		node = node->nextNode;
	}

	//读取length个节点
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