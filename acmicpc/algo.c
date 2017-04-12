#include <stdio.h>

#define MAXSIZE 22
#define MAXDEPTH 5
#define DEBUG 1

int size, maxValue;
int dyx[4][2] = { { 1, 0 },{ 0, -1 },{ -1, 0 },{ 0, 1 } };

void make2048(int count, int (*map)[MAXSIZE])
{
	int moveMap[MAXSIZE][MAXSIZE], check[MAXSIZE][MAXSIZE];
	int dir, i, j, k, row, col, pivotRow, pivotCol, tmp, moveCheck;

	/*
	for (row = 0; row < size; row++)
		for (col = 0; col < size; col++)
			moveMap[row][col] = map[row][col];
	*/
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
				else if (dir == 2) row = size - j - 1, col = i, pivotRow = size - 1, pivotCol = 0;
				else if (dir == 3) row = i, col = j, pivotRow = i, pivotCol = 0;

				if (map[row][col] != 0)
				{
					if (check[row][col] == 0 && k > 0 && moveMap[pivotRow + (k - 1) * dyx[dir][0]][pivotCol + (k - 1) * dyx[dir][1]] == map[row][col])
					{
						check[row][col] = 1;
						moveMap[pivotRow + (k - 1) * dyx[dir][0]][pivotCol + (k - 1) * dyx[dir][1]] += map[row][col];
						if (moveMap[pivotRow + (k - 1) * dyx[dir][0]][pivotCol + (k - 1) * dyx[dir][1]] > maxValue)
							maxValue = moveMap[pivotRow + (k - 1) * dyx[dir][0]][pivotCol + (k - 1) * dyx[dir][1]];
					}
					else if (check[row][col] == 0)
					{
						moveMap[pivotRow + k * dyx[dir][0]][pivotCol + k * dyx[dir][1]] = map[row][col];
						check[row][col] = 1;
						if (moveMap[pivotRow + k * dyx[dir][0]][pivotCol + k * dyx[dir][1]] > maxValue)
							maxValue = moveMap[pivotRow + k * dyx[dir][0]][pivotCol + k * dyx[dir][1]];
						k++;
						j--;
					}
				}

				if (map[row][col] != moveMap[row][col])
					moveCheck = 1;

/*
				for (k = 1; k <= size - j - 1; k++)
				{
					tmp = moveMap[row + k * dyx[dir][0]][col + k * dyx[dir][1]];
					if (tmp == 0)
						continue;
					else if (moveMap[row][col] != 0 && moveMap[row][col] != tmp)
						break;
					
					if (moveMap[row][col] == 0)
						moveMap[row][col] = tmp, j = j - 1;
					else if (moveMap[row][col] == tmp)
						moveMap[row][col] += tmp;
					moveMap[row + k * dyx[dir][0]][col + k * dyx[dir][1]] = 0;
					moveCheck = 1;
					break;
				}
				if (moveMap[row][col] > maxValue)
					maxValue = moveMap[row][col];
*/				
			}
		}

		if (DEBUG)
		{
			printf("\n----------------------------------------\nDEBUG\n\nCOUNT : %3d\nMAX : %5d, DIR : %3d, MOVE : %3d\n", count, maxValue, dir, moveCheck);
			for (row = 0; row < size; row++)
			{
				for (col = 0; col < size; col++)
					printf("%3d", moveMap[row][col]);
				printf("\n");
			}
		}

		if (moveCheck && count + 1 <= MAXDEPTH)
			make2048(count + 1, moveMap);

		/*
		for (row = 0; row < size; row++)
			for (col = 0; col < size; col++)
				moveMap[row][col] = map[row][col];
		*/
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