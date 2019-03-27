#define _CRT_SECURE_NO_WARNINGS
#include"function.h"
#include"BitList.h"
#include"miracl.h"
#include"mirdef.h"
#include<string.h>

InputInfo* ReadInputFile(char* filePath)
{
	//miracl *mip = mirsys(16, Max);
	FILE *fp = fopen(filePath, "r");
	char inputeString[maxInputLength];  //字符缓存
	//输入文件不存在
	if (fp == NULL)
	{
		printf("数据输入文件不存在\n");
		system("pause");
		exit(1);
	}

	BitList *headNode = NewBitList(2);
	fgets(inputeString, maxInputLength, fp);
	int charLength = strlen(inputeString);
	int size = 0;
	for(int i = 0; i < charLength; i++)
	{
		if (inputeString[i]=='\n')
		{
			continue;
		}
		AddHexToNode(headNode, inputeString[i]);
		size += 4;
	}

	InputInfo *inputInfo = (InputInfo*)malloc(sizeof(InputInfo));
	inputInfo->inputBitList = headNode;
	inputInfo->size = size;
	return inputInfo;
}


//64d20d27d0632957f8028c1e024f6b02edf23102a566c932ae8bd613a8e865fe58d225eca784ae300a81a2d48281a828e1cedf11c4219099840265375077bf7800000001
//64d20d27d0632957f8028c1e024f6b02edf23102a566c932ae8bd613a8e865fe58d225eca784ae300a81a2d48281a828e1cedf11c4219099840265375077bf7800000001

void FillInputInfo(InputInfo *inputInfo)
{
	//miracl *mip = mirsys(16, Max);
	//获取消息m的长度l
	int l = inputInfo->size;

	//添加"1"
	AddNode(inputInfo->inputBitList, 1);
	inputInfo->size++;

	//求解k
	int k = 0;
	while (!(((l+1+k)%512)==448))
	{
		k++;
	}
	
	//添加"0"
	for (int i = 0; i < k; i++)
	{
		AddNode(inputInfo->inputBitList, 0);
		inputInfo->size++;
	}

	//添加l的64位二进制
	int lBitList[64];
	for (int i = 63; i >= 0; i--)
	{
		lBitList[i] = l % 2;
		l = l / 2;
	}

	//添加到链表尾
	for (int i = 0; i < 64; i++)
	{
		AddNode(inputInfo->inputBitList, lBitList[i]);
	}

	inputInfo->size += 64;
	return;
}

GroupsInfo* DivideIntoGroups(InputInfo *inputInfo)
{
	//miracl *mip = mirsys(16, Max);
	//初始化groupInfo
	GroupsInfo *groupInfo = NewGroupsInfo();
	if (inputInfo->size % 512 != 0)
	{
		printf("size不为512倍数，计算错误\n");
		system("pause");
		exit(2);
	}

	//计算Bn的个数
	groupInfo->count = inputInfo->size / 512;
	
	//计算Bn
	for (int i = 0; i < groupInfo->count; i++)
	{
		int startIndex = 1 + 512 * i;
		//计算Bn
		//groupInfo->bwn[i][0] = BitListToBig(inputInfo->inputBitList,startIndex , 512);
		//计算wn
		for (int j = 0; j<=15; j++)
		{
			groupInfo->bwn[i][j+1]= BitListToBig(inputInfo->inputBitList,startIndex+j*32 ,32);
		}

		for (int j = 16; j <=67; j++)
		{
			groupInfo->bwn[i][j + 1] = Xor(Xor(Px1(Xor(Xor(groupInfo->bwn[i][j - 15], groupInfo->bwn[i][j - 8]), shiftLeft(groupInfo->bwn[i][j - 2], 15))), shiftLeft(groupInfo->bwn[i][j - 12], 7)), groupInfo->bwn[i][j - 5]);
		}

		for (int j = 68; j <=131; j++)
		{
			groupInfo->bwn[i][j + 1] = Xor(groupInfo->bwn[i][j-67], groupInfo->bwn[i][j-63]);
		}
	}

	return groupInfo;
}


big Tj(int j)
{
	//miracl *mip = mirsys(16, Max);
	if (j >= 0 && j <= 15)
	{
		return mirvar(2043430169);
	}
	else if (j >= 16 && j <= 63)
	{
		return mirvar(2055708042);
	}
	else
	{
		return mirvar(0);
	}
}

//X、Y、Z最大为一个字(32bit)
big FFj(int j, big X, big Y, big Z)
{
	//miracl *mip = mirsys(16, Max);
	int x = BigWordToInt(X);
	int y = BigWordToInt(Y);
	int z = BigWordToInt(Z);

	if (j >= 0 && j <= 15)
	{
		return Xor(Xor(X, Y), Z);
	}
	else if (j >= 16 && j <= 63)
	{

		return Or(Or(And(X, Y), And(X, Z)), And(Y, Z));
	}
	else
	{
		return mirvar(0);
	}
}

big GGj(int j, big X, big Y, big Z)
{
	//miracl *mip = mirsys(16, Max);

	if (j >= 0 && j <= 15)
	{
		return Xor(Xor(X, Y), Z);
	}
	else if (j >= 16 && j <= 63)
	{
		return Or(And(X, Y), And(Not(X),Z));
	}
	else
	{
		return mirvar(0);
	}
}

int BigWordToInt(big value)
{
	//miracl *mip = mirsys(16, Max);
	char ch[40];
	ch[32] = '\0';
	cotstr(value, ch);
	return atoi(ch);
}

big Px0(big X)
{
	//miracl *mip = mirsys(16, Max);
	int x = BigWordToInt(X);
	return Xor(Xor(X, shiftLeft(X, 9)), shiftLeft(X, 17));
}

big Px1(big X)
{
	//miracl *mip = mirsys(16, Max);
	return Xor(Xor(X,shiftLeft(X,15)),shiftLeft(X,23));
}

big And(big X, big Y)
{
	//miracl *mip = mirsys(16, Max);
	big x = mirvar(0);
	copy(X, x);
	big y = mirvar(0);
	copy(Y, y);

	//求解x二进制
	int a[32];
	for (int i = 31; i >= 0; i--)
	{
		a[i] = BigWordToInt(Mod(x, mirvar(2)));
		x = Divide(x, mirvar(2));
	}

	//求解y二进制
	int b[32];
	for (int i = 31; i >= 0; i--)
	{
		b[i] = BigWordToInt(Mod(y, mirvar(2)));
		y = Divide(y, mirvar(2));
	}

	//求解异或
	int z[32];
	for (int i = 31; i >= 0; i--)
	{
		z[i] = a[i] & b[i];
	}

	//转化为十进制
	big result = mirvar(0);
	for (int i = 0; i < 32; i++)
	{
		result = Multiply(result, mirvar(2));
		result = Add(result, mirvar(z[i]));
	}
	return result;
}

big Or(big X, big Y)
{
	//miracl *mip = mirsys(16, Max);
	big x = mirvar(0);
	copy(X, x);
	big y = mirvar(0);
	copy(Y, y);

	//求解x二进制
	int a[32];
	for (int i = 31; i >= 0; i--)
	{
		a[i] = BigWordToInt(Mod(x, mirvar(2)));
		x = Divide(x, mirvar(2));
	}

	//求解y二进制
	int b[32];
	for (int i = 31; i >= 0; i--)
	{
		b[i] = BigWordToInt(Mod(y, mirvar(2)));
		y = Divide(y, mirvar(2));
	}

	//求解异或
	int z[32];
	for (int i = 31; i >= 0; i--)
	{
		z[i] = a[i] | b[i];
	}

	//转化为十进制
	big result = mirvar(0);
	for (int i = 0; i < 32; i++)
	{
		result = Multiply(result, mirvar(2));
		result = Add(result, mirvar(z[i]));
	}
	return result;
}

big Not(big X)
{
	//miracl *mip = mirsys(16, Max);
	big x = mirvar(0);
	copy(X, x);

	//求解x二进制非运算结果
	int a[32];
	for (int i = 31; i >= 0; i--)
	{
		a[i] = BigWordToInt(Mod(x, mirvar(2)));
		x = Divide(x, mirvar(2));
		if (a[i] == 1)
		{
			a[i] = 0;
		}
		else
		{
			a[i] = 1;
		}
	}

	//转化为十进制
	big result = mirvar(0);
	for (int i = 0; i < 32; i++)
	{
		result = Multiply(result, mirvar(2));
		result = Add(result, mirvar(a[i]));
	}
	return result;
}

big Xor(big X, big Y)
{
	//miracl *mip = mirsys(16, Max);
	big x = mirvar(0);
	copy(X, x);
	big y = mirvar(0);
	copy(Y, y);

	//求解x二进制
	int a[32];
	for (int i = 31; i >= 0; i--)
	{
		a[i] = BigWordToInt(Mod(x, mirvar(2)));
		x = Divide(x, mirvar(2));
	}

	//求解y二进制
	int b[32];
	for (int i = 31; i >= 0; i--)
	{
		b[i] = BigWordToInt(Mod(y, mirvar(2)));
		y = Divide(y, mirvar(2));
	}

	//求解异或
	int z[32];
	for (int i = 31; i >= 0; i--)
	{
		z[i] = a[i] ^ b[i];
	}

	//转化为十进制
	big result = mirvar(0);
	for (int i = 0; i < 32; i++)
	{
		result = Multiply(result, mirvar(2));
		result = Add(result, mirvar(z[i]));
	}
	return result;
}

big shiftLeft(big X,int length)
{
	//miracl *mip = mirsys(16, Max);
	big x = mirvar(0);
	copy(X, x);

	//求解x二进制
	int a[32];
	for (int i = 31; i >= 0; i--)
	{
		a[i] = BigWordToInt(Mod(x, mirvar(2)));
		x = Divide(x, mirvar(2));
	}

	//求解循环右移二进制
	int b[32];
	for (int i = 0; i < 32; i++)
	{
		b[i] = a[(i + length) % 32];
	}

	//计算十进制
	big result = mirvar(0);
	for (int i = 0; i <32; i++)
	{
		result = Multiply(result, mirvar(2));
		result = Add(result, mirvar(b[i]));
	}

	return result;
}


big* CF(big* Vi, GroupsInfo *groupInfo, int i)
{
	big A = mirvar(0);
	big B = mirvar(0);
	big C = mirvar(0);
	big D = mirvar(0);
	big E = mirvar(0);
	big F = mirvar(0);
	big G = mirvar(0);
	big H = mirvar(0);

	copy(Vi[0], A);
	copy(Vi[1], B);
	copy(Vi[2], C);
	copy(Vi[3], D);
	copy(Vi[4], E);
	copy(Vi[5], F);
	copy(Vi[6], G);
	copy(Vi[7], H);

	big SS1 = mirvar(0);
	big SS2 = mirvar(0);
	big TT1 = mirvar(0);
	big TT2 = mirvar(0);

	for (int j = 0; j <= 63; j++)
	{
		SS1 = shiftLeft(Add(Add(shiftLeft(A, 12), E), shiftLeft(Tj(j), j)), 7);
		SS2 = Xor(SS1, shiftLeft(A, 12));
		TT1 = Add(Add(Add(FFj(j, A, B, C), D), SS2), groupInfo->bwn[i][69 + j]);
		TT2= Add(Add(Add(GGj(j, E, F, G), H), SS1), groupInfo->bwn[i][1 + j]);
		D = C;
		C = shiftLeft(B, 9);
		B = A;
		A = TT1;
		H = G;
		G= shiftLeft(F, 19);
		F = E;
		E = Px0(TT2);
	}

	big *V = (big*)malloc(sizeof(big)*8);

	V[0] = Xor (A, Vi[0]);
	V[1] = Xor (B, Vi[1]);
	V[2] = Xor (C, Vi[2]);
	V[3] = Xor (D, Vi[3]);
	V[4] = Xor (E, Vi[4]);
	V[5] = Xor (F, Vi[5]);
	V[6] = Xor (G, Vi[6]);
	V[7] = Xor (H, Vi[7]);

	//free(Vi);

	return V;
}

big ReadNumber(int *array,int startIndex, int length)
{
	//miracl *mip = mirsys(16, Max);
	big result = mirvar(0);
	for (int i = 0; i < length; i++)
	{
		multiply(result, mirvar(2), result);	//result *= 2;
		add(result, mirvar(array[startIndex + i]), result);
	}
	return result;
}

big Add(big x, big y)
{
	//miracl *mip = mirsys(16, Max);
	big result = mirvar(0);
	add(x, y, result);
	return result;
}

big Multiply(big x, big y)
{
	//miracl *mip = mirsys(16, Max);
	big result = mirvar(0);
	multiply(x, y, result);
	return result;
}

char* BigWordToHexString(big value)
{
	//miracl *mip = mirsys(16, Max);

	int v[32];
	//模拟value，大端法
	for (int j = 31; j >= 0; j--)
	{
		v[j] = BigWordToInt(Mod(value, mirvar(2)));				//v[j]= value %2
		value = Divide(value, mirvar(2));						//vi1 /= 2
	}

	char *hexString = (char*)malloc(9*sizeof(char));
	//计算存储为十六进制字符串
	for (int i = 0; i < 32; i += 4)
	{
		hexString[i/4] = ReadHexChar(v, i);
	}
	hexString[8] = '\0';
	return hexString;
}

char ReadHexChar(int *array, int startIndex)
{
	//miracl *mip = mirsys(16, Max);
	int charValue = array[startIndex] * 8 + array[startIndex + 1] * 4 + array[startIndex + 2] * 2 + array[startIndex + 3]*1;
	switch (charValue)
	{
	case 0:
		return '0';
	case 1:
		return '1';
	case 2:
		return '2';
	case 3:
		return '3';
	case 4:
		return '4';
	case 5:
		return '5';
	case 6:
		return '6';
	case 7:
		return '7';
	case 8:
		return '8';
	case 9:
		return '9';
	case 10:
		return 'a';
	case 11:
		return 'b';
	case 12:
		return 'c';
	case 13:
		return 'd';
	case 14:
		return 'e';
	case 15:
		return 'f';
	default:
		return '-';
	}
}

big Divide(big x, big y)
{
	//miracl *mip = mirsys(16, Max);
	big x1 = mirvar(0);
	big y1 = mirvar(0);
	big z1 = mirvar(0);
	copy(x, x1);
	copy(y, y1);
	divide(x1, y1, z1);
	return z1;
}

big Mod(big x, big y)
{
	//miracl *mip = mirsys(16, Max);
	big x1 = mirvar(0);
	big y1 = mirvar(0);
	big z1 = mirvar(0);
	copy(x, x1);
	copy(y, y1);
	powmod(x1, mirvar(1), y1, z1);
	return z1;
}
