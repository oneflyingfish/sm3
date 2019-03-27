#include"InputInfo.h"

GroupsInfo *NewGroupsInfo()
{
	//miracl *mip = mirsys(16, Max);
	GroupsInfo *groupsInfo = (GroupsInfo*)malloc(sizeof(GroupsInfo));
	for (int i = 0; i < 100; i++)
	{
		for (int j=0; j < 133; j++)
		{
			groupsInfo->bwn[i][j] = mirvar(0);
		}
	}
	return groupsInfo;
}