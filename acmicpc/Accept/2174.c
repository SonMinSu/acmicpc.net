#include <stdio.h>

//https://www.acmicpc.net/problem/2174 - ·Îº¿ ½Ã¹Ä·¹ÀÌ¼Ç

struct robot
{
	int y;
	int x;
	int dir;
};

int maxY, maxX, robotCount, cmdCount;
int map[111][111];
int dy[] = { 1, 0, -1, 0 }, dx[] = { 0,1,0,-1 };
struct robot robotList[111];

int robotCheck(int robotIndex, int dir, int count)
{
	int i, ty, tx;

	for (i = 0; i < count; i++)
	{
		if (dir == 4)
		{
			map[robotList[robotIndex].y][robotList[robotIndex].x] = 0;

			ty = robotList[robotIndex].y + dy[robotList[robotIndex].dir];
			tx = robotList[robotIndex].x + dx[robotList[robotIndex].dir];

			if (ty < 1 || ty > maxY || tx < 1 || tx > maxX)
			{
				printf("Robot %d crashes into the wall\n", robotIndex);
				return 0;
			}
			else if (map[ty][tx] > 0)
			{
				printf("Robot %d crashes into robot %d\n", robotIndex, map[ty][tx]);
				return 0;
			}

			map[ty][tx] = robotIndex;
			robotList[robotIndex].y = ty;
			robotList[robotIndex].x = tx;
		}
		else
		{
			robotList[robotIndex].dir = (robotList[robotIndex].dir + dir) % 4;
		}
	}

	return 1;
}

int main()
{
	int i, checkResult, robotIndex, count;
	char cmd, textData[128];

	textData['N'] = 0;
	textData['E'] = 1;
	textData['S'] = 2;
	textData['W'] = 3;
	textData['L'] = 3;
	textData['R'] = 1;
	textData['F'] = 4;

	scanf("%d %d", &maxX, &maxY);
	scanf("%d %d", &robotCount, &cmdCount);

	for (i = 1; i <= robotCount; i++)
	{
		scanf("%d %d %c", &robotList[i].x, &robotList[i].y, &cmd);
		robotList[i].dir = (int)textData[cmd];
		map[robotList[i].y][robotList[i].x] = i;
	}

	for (i = 0; i < cmdCount; i++)
	{
		scanf("%d %c %d", &robotIndex, &cmd, &count);
		checkResult = robotCheck(robotIndex, (int)textData[cmd], count);

		if (checkResult == 0)
			return 0;
	}

	printf("OK\n");

	return 0;
}


/*
1 1
2 2
1 1 N
1 5 S
1 F 2
2 F 3


5 4
2 2
1 1 E
5 4 W
1 F 2
2 F 2
*/