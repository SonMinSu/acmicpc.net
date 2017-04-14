#include <stdio.h>

#define INFMIN 999999999

struct snakeData
{
	int row;
	int col;
	int dir;
	long long int time;
};

struct data
{
	int minRow;
	int minCol;
	int maxRow;
	int maxCol;
};

int mapSize, cmdCount, colDataCount, rowDataCount;
int dyx[4][2] = { {0, 1}, {-1, 0}, {0, -1}, {1, 0} };
struct snakeData snake;
struct data colData[1111], rowData[1111];

int min(int a, int b)
{
	return a > b ? b : a;
}

int max(int a, int b)
{
	return a > b ? a : b;
}

int abs(int a)
{
	return a > 0 ? a : a * -1;
}

int moveSnake(int cmdTime, char cDir)
{
	int nextRow, nextCol, minRow, minCol, maxRow, maxCol, i, moveCheck, minDepth, tmpDepth, dir;

	dir = 1;
	if (cDir == 'L')
		dir = 3;

	nextRow = snake.row + dyx[snake.dir][0] * cmdTime;
	nextCol = snake.col + dyx[snake.dir][1] * cmdTime;

	moveCheck = 0;
	minDepth = INFMIN;
	minRow = min(snake.row, nextRow);
	minCol = min(snake.col, nextCol);
	maxRow = max(snake.row, nextRow);
	maxCol = max(snake.col, nextCol);

	if (nextRow < mapSize * -1 || nextRow > mapSize)
	{
		minDepth = mapSize - abs(snake.row) + 1;
		moveCheck = 1;
	}
	else if (nextCol < mapSize * -1 || nextCol > mapSize)
	{
		minDepth = mapSize - abs(snake.col) + 1;
		moveCheck = 1;
	}

	if (snake.dir == 0 || snake.dir == 2)
	{
		// 진행방향이 가로일 때
		for (i = 0; i < rowDataCount - 1; i++)
		{
			if (rowData[i].minRow <= minRow && minRow <= rowData[i].maxRow && minCol <= rowData[i].maxCol && rowData[i].maxCol <= maxCol)
			{
				tmpDepth = abs(rowData[i].maxCol - snake.col);
				if (tmpDepth < minDepth)
					minDepth = tmpDepth;
				moveCheck = 1;
			}
		}

		for (i = 0; i < colDataCount; i++)
		{
			if (snake.dir == 0 && minRow == colData[i].maxRow && minCol <= colData[i].minCol && colData[i].minCol <= maxCol)
			{
				tmpDepth = abs(colData[i].minCol - minCol);
				if (tmpDepth < minDepth)
					minDepth = tmpDepth;
				moveCheck = 1;
			}
			else if (snake.dir == 3 && minRow == colData[i].maxRow && minCol <= colData[i].maxCol && colData[i].maxCol <= maxCol)
			{
				tmpDepth = abs(colData[i].maxCol - maxCol);
				if (tmpDepth < minDepth)
					minDepth = tmpDepth;
				moveCheck = 1;
			}
		}
	}
	else
	{
		// 진행방향이 세로일 때
		for (i = 0; i < colDataCount - 1; i++)
		{
			if (colData[i].minCol <= minCol && minCol <= colData[i].maxCol && minRow <= colData[i].maxRow && colData[i].maxRow <= maxRow)
			{
				tmpDepth = abs(colData[i].maxRow - snake.row);
				if (tmpDepth < minDepth)
					minDepth = tmpDepth;
				moveCheck = 1;
			}
		}

		for (i = 0; i < rowDataCount; i++)
		{
			if (snake.dir == 1 && minCol == rowData[i].minCol && minRow <= rowData[i].maxRow && rowData[i].maxRow <= maxRow)
			{
				tmpDepth = abs(rowData[i].maxRow - maxRow);
				if (tmpDepth < minDepth)
					minDepth = tmpDepth;
				moveCheck = 1;
			}
			else if (snake.dir == 3 && minCol == rowData[i].maxCol && minRow <= rowData[i].minRow && rowData[i].minRow <= maxRow)
			{
				tmpDepth = abs(rowData[i].minRow - minRow);
				if (tmpDepth < minDepth)
					minDepth = minDepth;
				moveCheck = 1;
			}
		}
	}

	if (moveCheck == 0)
	{
		if (snake.dir == 0 || snake.dir == 2)
		{
			colData[colDataCount].minRow = minRow;
			colData[colDataCount].minCol = minCol;
			colData[colDataCount].maxRow = maxRow;
			colData[colDataCount].maxCol = maxCol;
			colDataCount++;
		}
		else
		{
			rowData[rowDataCount].minRow = minRow;
			rowData[rowDataCount].minCol = minCol;
			rowData[rowDataCount].maxRow = maxRow;
			rowData[rowDataCount].maxCol = maxCol;
			rowDataCount++;
		}
		snake.time += cmdTime;
		snake.row = nextRow;
		snake.col = nextCol;
	}
	else
		snake.time += minDepth;
	snake.dir = (snake.dir + dir) % 4;

	return moveCheck;
}

int main()
{
	int count, cmdTime;
	char dir;

	snake.dir = snake.row = snake.col = 0;
	scanf("%d %d", &mapSize, &cmdCount);

	for (count = 0; count < cmdCount; count++)
	{
		scanf("%d %c", &cmdTime, &dir);

		if (moveSnake(cmdTime, dir))
			break;
	}

	moveSnake(mapSize * 2, 0);
	printf("%lld", snake.time);

	return 0;
}