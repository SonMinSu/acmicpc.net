#include <stdio.h>

// https://www.acmicpc.net/problem/14499 - 주사위 굴리기

#define DEBUG 0

int dice[7];
int rowSize, colSize, map[22][22];
int dyx[5][2] = { { 0, 0 },{ 0, 1 },{ 0, -1 },{ -1, 0 },{ 1, 0 } };
int diceRow, diceCol, cmdCount;

int main()
{
	int row, col, i, cmd, tRow, tCol, tmp;

	scanf("%d %d %d %d %d", &rowSize, &colSize, &diceRow, &diceCol, &cmdCount);

	for (row = 0; row < rowSize; row++)
	{
		for (col = 0; col < colSize; col++)
		{
			scanf("%d", &map[row][col]);
		}
	}

	for (i = 0; i < cmdCount; i++)
	{
		scanf("%d", &cmd);
		tRow = diceRow + dyx[cmd][0];
		tCol = diceCol + dyx[cmd][1];
		if (tRow < 0 || tRow >= rowSize || tCol < 0 || tCol >= colSize)
			continue;

		if (cmd == 1)
		{
			tmp = dice[3];
			dice[3] = dice[1];
			dice[1] = dice[4];
			dice[4] = dice[6];
			dice[6] = tmp;
		}
		else if (cmd == 2)
		{
			tmp = dice[4];
			dice[4] = dice[1];
			dice[1] = dice[3];
			dice[3] = dice[6];
			dice[6] = tmp;
		}
		else if (cmd == 3)
		{
			tmp = dice[2];
			dice[2] = dice[1];
			dice[1] = dice[5];
			dice[5] = dice[6];
			dice[6] = tmp;
		}
		else if (cmd == 4)
		{
			tmp = dice[5];
			dice[5] = dice[1];
			dice[1] = dice[2];
			dice[2] = dice[6];
			dice[6] = tmp;
		}

		if (map[tRow][tCol] == 0)
			map[tRow][tCol] = tmp;
		else
		{
			dice[6] = map[tRow][tCol];
			map[tRow][tCol] = 0;
		}

		diceRow = tRow;
		diceCol = tCol;
		printf("%d\n", dice[1]);

		if (DEBUG)
		{
			printf("\n--------------------\nDEBUG CMD : %d\n", i + 1);
			printf("diceRow : %3d, diceCol : %3d\n", diceRow, diceCol);
			printf("%6d\n", dice[2]);
			printf("%3d%3d%3d\n", dice[4], dice[1], dice[3]);
			printf("%6d\n", dice[5]);
			printf("%6d\n", dice[6]);
			printf("\n");
			for (row = 0; row < rowSize; row++)
			{
				for (col = 0; col < colSize; col++)
				{
					printf("%3d", map[row][col]);
				}
				printf("\n");
			}
			printf("\n--------------------\n\n");
		}
	}

	return 0;
}