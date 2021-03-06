#include <stdio.h>

#define MAXSIZE 22
#define MAXDEPTH 5
#define DEBUG 0

int size, maxValue;
int dyx[4][2] = { { 1, 0 },{ 0, -1 },{ -1, 0 },{ 0, 1 } };
int history[MAXDEPTH];

void make2048(int count, int(*map)[MAXSIZE])
{
	int moveMap[MAXSIZE][MAXSIZE], check[MAXSIZE][MAXSIZE];
	int dir, i, j, k, row, col, pivotRow, pivotCol, tmp, moveCheck;
	int *data;

	for (dir = 0; dir < 4; dir++)
	{
		for (row = 0; row < size; row++)
			for (col = 0; col < size; col++)
				moveMap[row][col] = 0, check[row][col] = 0;

		moveCheck = 0;
		for (i = 0; i < size; i++)
		{
			k = 0;
			for (j = 0; j < size; j++)
			{
				if (dir == 0) row = j, col = i, pivotRow = 0, pivotCol = i;
				else if (dir == 1) row = i, col = size - j - 1, pivotRow = i, pivotCol = size - 1;
				else if (dir == 2) row = size - j - 1, col = i, pivotRow = size - 1, pivotCol = i;
				else if (dir == 3) row = i, col = j, pivotRow = i, pivotCol = 0;

				if (map[row][col] != 0 && check[row][col] == 0)
				{
					if (k > 0 && check[pivotRow + (k - 1) * dyx[dir][0]][pivotCol + (k - 1) * dyx[dir][1]] != 2 && moveMap[pivotRow + (k - 1) * dyx[dir][0]][pivotCol + (k - 1) * dyx[dir][1]] == map[row][col])
					{
						data = &moveMap[pivotRow + (k - 1) * dyx[dir][0]][pivotCol + (k - 1) * dyx[dir][1]];
						check[pivotRow + (k - 1) * dyx[dir][0]][pivotCol + (k - 1) * dyx[dir][1]] = 2;
						check[row][col] = 1;
						*data += map[row][col];
						if (*data > maxValue)
							maxValue = *data;
					}
					else
					{
						data = &moveMap[pivotRow + k * dyx[dir][0]][pivotCol + k * dyx[dir][1]];
						*data = map[row][col];
						check[row][col] = 1;
						if (*data > maxValue)
							maxValue = *data;
						k++;
						j--;
					}
				}
			}
		}

		for (row = 0; row < size && moveCheck == 0; row++)
		{
			for (col = 0; col < size; col++)
			{
				if (map[row][col] != moveMap[row][col])
				{
					moveCheck = 1;
					break;
				}
			}
		}

		if (DEBUG)
		{
			history[count - 1] = dir;
			printf("\n----------------------------------------\nDEBUG\n\nCOUNT : %3d\nMAX : %5d, DIR : %3d, MOVE : %3d\n", count, maxValue, dir, moveCheck);
			printf("History : %3d", history[0]);
			for (i = 1; i < count; i++)
				printf(" --> %3d", history[i]);
			printf("\n");
			for (row = 0; row < size; row++)
			{
				for (col = 0; col < size; col++)
					printf("%3d", moveMap[row][col]);
				printf("\n");
			}
		}

		if (moveCheck && count + 1 <= MAXDEPTH)
			make2048(count + 1, moveMap);
	}
}

int main()
{
	int row, col, map[MAXSIZE][MAXSIZE];

	scanf("%d", &size);
	for (row = 0; row < size; row++)
		for (col = 0; col < size; col++)
			scanf("%d", &map[row][col]);

	maxValue = 0;
	make2048(1, map);
	printf("%d", maxValue);

	return 0;
}