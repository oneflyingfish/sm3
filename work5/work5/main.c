#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include"miracl.h"
#include"mirdef.h"
#include"InputInfo.h"
#include"function.h"
#include"BitList.h"

int Max =1200;

int main()
{
	miracl *mip = mirsys(160, Max);
	for (int i = 1; i <= 14; i++)
	{
		char filePath[100];
		sprintf(filePath, "%d.txt", i);

		//读取磁盘输入
		InputInfo *inputInfo = ReadInputFile(filePath);
		//填充
		FillInputInfo(inputInfo);
		//读物Bn和Wj
		GroupsInfo *groupInfo = DivideIntoGroups(inputInfo);
		//计算n
		int n = groupInfo->count;

		big Vi[8];
		//计算V0
		Vi[0] = mirvar(0);
		cinstr(Vi[0], "1937774191");
		Vi[1] = mirvar(0);
		cinstr(Vi[1], "1226093241");
		Vi[2] = mirvar(0);
		cinstr(Vi[2], "388252375");
		Vi[3] = mirvar(0);
		cinstr(Vi[3], "3666478592");
		Vi[4] = mirvar(0);
		cinstr(Vi[4], "2842636476");
		Vi[5] = mirvar(0);
		cinstr(Vi[5], "372324522");
		Vi[6] = mirvar(0);
		cinstr(Vi[6], "3817729613");
		Vi[7] = mirvar(0);
		cinstr(Vi[7], "2969243214");

		//计算Vn
		big* V = Vi;
		for (int i = 0; i < n; i++)
		{
			V = CF(V, groupInfo, i);
		}

		//根据Vn输出杂凑值
		printf("第%2d组SM3杂凑值为: ",i);
		for (int i = 0; i < 8; i++)
		{
			char *resultString = BigWordToHexString(V[i]);
			printf("%s ", resultString);
			//释放内存
			free(resultString);
		}
		printf("\n\n");

		FreeList(inputInfo->inputBitList);
		free(inputInfo);
		free(groupInfo);
	}

	printf("备注：13-14组为pdf上测试数据\n");
	system("pause");
	return 0;
}