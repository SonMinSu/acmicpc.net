#include <stdio.h>

int dice[7];
int rowSize, colSize, map[22][22];
int dyx[5][2] = { { 0, 0 },{ 0, 1 },{ 0, -1 },{ -1, 0 },{ 1, 0 } };
int diceRow, diceCol, cmdCount;
int moveMap[4][4] = { { 3, 1, 4, 6 },{ 4, 1, 3, 6 },{ 2, 1, 5, 6 },{ 5, 1, 2, 6 } };

int diceMove(int n)
{
	int tmp, i;

	tmp = dice[moveMap[n][0]];
	for (i = 0; i < 3; i++)
		dice[moveMap[n][i]] = dice[moveMap[n][i + 1]];
	dice[moveMap[n][i]] = tmp;

	return tmp;
}

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

		tmp = diceMove(cmd - 1);

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
	}

	return 0;
}