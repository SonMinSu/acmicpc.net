#include <stdio.h>

//https://www.acmicpc.net/problem/13460 - 째로탈출2

#define INF 999999999
#define MAXCOUNT 10

int rowSize, colSize, minCount;
char map[11][11];
int dYX[4][2] = { { -1, 0 },{ 0, 1 },{ 1, 0 },{ 0, -1 } };

int max(int a, int b)
{
	return a > b ? a : b;
}

void mapSearch(int dir, int redRow, int redCol, int blueRow, int blueCol, int count)
{
	int i, j, ballCheck;
	int nowRedRow, nowRedCol, nowBlueRow, nowBlueCol, nextRedRow, nextRedCol, nextBlueRow, nextBlueCol;

	if (count >= MAXCOUNT)
		return;

	for (i = 0; i < 4; i++)
	{
		if (dir != -1 && (i == dir || i == (dir + 2) % 4))
			continue;

		ballCheck = 0;
		nowRedRow = redRow;
		nowRedCol = redCol;
		nowBlueRow = blueRow;
		nowBlueCol = blueCol;
		for (j = 0; j < max(rowSize, colSize); j++)
		{
			if (!ballCheck & 1 << 0)
			{
				nextRedRow = nowRedRow + dYX[i][0];
				nextRedCol = nowRedCol + dYX[i][1];
				if (map[nextRedRow][nextRedCol] == '#')
				{
					nextRedRow = nowRedRow;
					nextRedCol = nowRedCol;
				}
				else if (nextRedRow == nowBlueRow && nextRedCol == nowBlueCol && map[nowBlueRow + dYX[i][0]][nowBlueCol + dYX[i][1]] == '#')
				{
					nextRedRow = nowRedRow;
					nextRedCol = nowRedCol;
				}
				else if (map[nextRedRow][nextRedCol] == 'O')
				{
					ballCheck |= 1 << 0;
				}
			}

			nextBlueRow = nowBlueRow + dYX[i][0];
			nextBlueCol = nowBlueCol + dYX[i][1];
			if (map[nextBlueRow][nextBlueCol] == '#')
			{
				nextBlueRow = nowBlueRow;
				nextBlueCol = nowBlueCol;
			}
			else if (map[nextBlueRow][nextBlueCol] == 'O')
			{
				ballCheck |= 1 << 1;
				break;
			}
			else if (nextBlueRow == nextRedRow && nextBlueCol == nextRedCol)
			{
				nextBlueRow = nowBlueRow;
				nextBlueCol = nowBlueCol;
			}

			nowRedRow = nextRedRow;
			nowRedCol = nextRedCol;
			nowBlueRow = nextBlueRow;
			nowBlueCol = nextBlueCol;
		}

		if (ballCheck & 1 << 1)
			continue;
		else if (ballCheck & 1 << 0)
		{
			if (minCount > count + 1)
				minCount = count + 1;
			return;
		}

		if (redRow == nextRedRow && redCol == nextRedCol && blueRow == nextBlueRow && blueCol == nextBlueCol)
			continue;

		if (dir == i)
			mapSearch(i, nextRedRow, nextRedCol, nextBlueRow, nextBlueCol, count);
		else
			mapSearch(i, nextRedRow, nextRedCol, nextBlueRow, nextBlueCol, count + 1);
	}
}

int main()
{
	int row, col, dir, redRow, redCol, blueRow, blueCol;

	scanf("%d %d", &rowSize, &colSize);

	for (row = 0; row < rowSize; row++)
	{
		scanf("%s", &map[row][0]);
		for (col = 0; col < colSize; col++)
		{
			if (map[row][col] == 'R')
			{
				redRow = row;
				redCol = col;
				map[row][col] = '.';
			}
			else if (map[row][col] == 'B')
			{
				blueRow = row;
				blueCol = col;
				map[row][col] = '.';
			}
		}
	}

	minCount = INF;
	mapSearch(-1, redRow, redCol, blueRow, blueCol, 0);

	if (minCount == INF)
		printf("-1");
	else
		printf("%d", minCount);

	return 0;
}