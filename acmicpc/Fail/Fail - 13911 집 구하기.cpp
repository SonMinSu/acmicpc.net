#include <stdio.h>

#define DEBUG 0
#define MAXIMUM 2100000000

struct nodeData
{
	char storeCheck;		// 0=집, 1=맥도날드, 2=스타벅스, 3=맥도날드&스타벅스
	int minimumWeight[2];	// 0=맥도날드 최소거리, 1=스타벅스 최소거리
};

struct storeNodeData
{
	int node;
	char storeCheck;		// 1=맥도날드, 2=스타벅스, 3=맥도날드&스타벅스
};

int weightMap[10001][10001];
struct nodeData nodeInfo[10001];
struct storeNodeData storeNode[20001];
int nodeCount, edgeCount, macCount, starCount;
int minimumMacWeight, minimumStarWeight;
int minimumWeightHouseNode;

void minimumWeightFindStoreToHouse(int startNode, int totalWeight, char storeCheck)
{
	int i, nextTotalWeight;

	for (i = 1; i <= nodeCount; i++)
	{
		if (weightMap[startNode][i] > 0)	// 간선을 발견 했을 경우
		{
			nextTotalWeight = totalWeight + weightMap[startNode][i];
			if (nodeInfo[i].minimumWeight[storeCheck - 1] == 0)
			{
				nodeInfo[i].minimumWeight[storeCheck - 1] = nextTotalWeight;

				minimumWeightFindStoreToHouse(i, nextTotalWeight, storeCheck);
			}
			else if (nodeInfo[i].minimumWeight[storeCheck - 1] > nextTotalWeight)
			{
				nodeInfo[i].minimumWeight[storeCheck - 1] = nextTotalWeight;

				minimumWeightFindStoreToHouse(i, nextTotalWeight, storeCheck);
			}
		}
	}
}

int main()
{
	int i, u, v, j, w, minMacStarWeight;

	scanf("%d %d", &nodeCount, &edgeCount);

	for (i = 0; i < edgeCount; i++)
	{
		scanf("%d %d %d", &u, &v, &w);
		if (weightMap[u][v] == 0)
		{
			weightMap[u][v] = w;
			weightMap[v][u] = w;
		}
		else if (weightMap[u][v] > w)
		{
			weightMap[u][v] = w;
			weightMap[v][u] = w;
		}
	}

	scanf("%d %d", &macCount, &minimumMacWeight);
	for (i = 0; i < macCount; i++)
	{
		scanf("%d", &storeNode[i].node);
		storeNode[i].storeCheck = 1;

		nodeInfo[storeNode[i].node].storeCheck |= 1;		// 상점 노드로 지정
		nodeInfo[storeNode[i].node].minimumWeight[0] = -MAXIMUM;
	}

	scanf("%d %d", &starCount, &minimumStarWeight);
	for (i = 0; i < starCount; i++)
	{
		scanf("%d", &storeNode[macCount + i].node);
		storeNode[macCount + i].storeCheck = 2;

		nodeInfo[storeNode[macCount + i].node].storeCheck |= 2;		// 상점 노드로 지정
		nodeInfo[storeNode[macCount + i].node].minimumWeight[1] = -MAXIMUM;
	}

	for (i = 0; i < macCount + starCount; i++)
	{
		minimumWeightFindStoreToHouse(storeNode[i].node, 0, storeNode[i].storeCheck);

		if (DEBUG)
		{
			printf("\n\n------------------------------\n");
			printf("%d StoreNode Complte\n", storeNode[i].node);
			for (j = 1; j <= nodeCount; j++)
			{
				printf("node : %5d | nodeCheck : %2d | MacWeight : %13d | StarWeight : %13d\n", j, nodeInfo[j].storeCheck, nodeInfo[j].minimumWeight[0], nodeInfo[j].minimumWeight[1]);
			}
		}
	}

	minimumWeightHouseNode = -1;
	minMacStarWeight = MAXIMUM;
	for (i = 1; i <= nodeCount; i++)
	{
		if (nodeInfo[i].storeCheck == 0 &&
			0 < nodeInfo[i].minimumWeight[0] && nodeInfo[i].minimumWeight[0] <= minimumMacWeight &&
			0 < nodeInfo[i].minimumWeight[1] && nodeInfo[i].minimumWeight[1] <= minimumStarWeight &&
			nodeInfo[i].minimumWeight[0] + nodeInfo[i].minimumWeight[1] < minMacStarWeight)
		{
			minimumWeightHouseNode = i;
			minMacStarWeight = nodeInfo[i].minimumWeight[0] + nodeInfo[i].minimumWeight[1];
		}
	}

	printf("%d", minimumWeightHouseNode);

	if (DEBUG)
	{
		printf("\n\n---------- DEBUG ----------\n");
		printf("StoreNode Info\n");
		for (i = 0; i < macCount + starCount; i++)
			printf("StoreType : %3d | Node : %5d\n", storeNode[i].storeCheck, storeNode[i].node);
		printf("\nminMacStarWeight : %d\n", minMacStarWeight);
		for (i = 1; i <= nodeCount; i++)
		{
			printf("node : %5d | nodeCheck : %2d | MacWeight : %13d | StarWeight : %13d\n", i, nodeInfo[i].storeCheck, nodeInfo[i].minimumWeight[0], nodeInfo[i].minimumWeight[1]);
		}
	}

	return 0;
}