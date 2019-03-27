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

		//��ȡ��������
		InputInfo *inputInfo = ReadInputFile(filePath);
		//���
		FillInputInfo(inputInfo);
		//����Bn��Wj
		GroupsInfo *groupInfo = DivideIntoGroups(inputInfo);
		//����n
		int n = groupInfo->count;

		big Vi[8];
		//����V0
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

		//����Vn
		big* V = Vi;
		for (int i = 0; i < n; i++)
		{
			V = CF(V, groupInfo, i);
		}

		//����Vn����Ӵ�ֵ
		printf("��%2d��SM3�Ӵ�ֵΪ: ",i);
		for (int i = 0; i < 8; i++)
		{
			char *resultString = BigWordToHexString(V[i]);
			printf("%s ", resultString);
			//�ͷ��ڴ�
			free(resultString);
		}
		printf("\n\n");

		FreeList(inputInfo->inputBitList);
		free(inputInfo);
		free(groupInfo);
	}

	printf("��ע��13-14��Ϊpdf�ϲ�������\n");
	system("pause");
	return 0;
}