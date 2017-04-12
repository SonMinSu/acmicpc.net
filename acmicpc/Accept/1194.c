#include <stdio.h>

// https://www.acmicpc.net/problem/1194 - 달이 차오른다, 가자

#define QUEUESIZE 100000
#define INFMIN 999999999

struct queData
{
	int row;
	int col;
	int count;
	int key;
	int before;
};

struct checkMap
{
	int count;
	int key;
};

int rowSize, colSize;
char map[52][52];
int direction[4][2] = { { -1, 0 },{ 0, 1 },{ 1, 0 },{ 0, -1 } };
int visit[64][52][52];
struct queData queue[QUEUESIZE];

int queuePush(int *tail, int row, int col, int count, int key, int before)
{
	queue[*tail].row = row;
	queue[*tail].col = col;
	queue[*tail].count = count;
	queue[*tail].key = key;
	queue[*tail].before = before;
	*tail += 1;

	visit[key][row][col] = count;
}

int searchMaze(int startRow, int startCol)
{
	int front, tail, dir, nextRow, nextCol, min;
	struct queData data;

	min = INFMIN;
	front = 0; tail = 0;
	queuePush(&tail, startRow, startCol, 0, 0, -1);
	//	queue[tail].row = startRow, queue[tail].col = startCol, queue[tail].count = 0, queue[tail].key = 0;
	//	tail++;

	while (front < tail)
	{
		for (dir = 0; dir < 4; dir++)
		{
			data = queue[front];
			nextRow = data.row + direction[dir][0];
			nextCol = data.col + direction[dir][1];
			if (map[nextRow][nextCol] == '.' &&
				(visit[data.key][nextRow][nextCol] > data.count + 1 ||		// 움직임 횟수가 더 작거나
					visit[data.key][nextRow][nextCol] == 0))				// 한 번도 방문 한 적이 없거나
			{
				queuePush(&tail, nextRow, nextCol, data.count + 1, data.key, front);
			}
			else if ('a' <= map[nextRow][nextCol] && map[nextRow][nextCol] <= 'f' &&
				(visit[data.key][nextRow][nextCol] == 0 ||
					visit[data.key][nextRow][nextCol] > data.count + 1))
			{
				queuePush(&tail, nextRow, nextCol, data.count + 1, data.key | (1 << (map[nextRow][nextCol] - 'a')), front);
			}
			else if ('A' <= map[nextRow][nextCol] && map[nextRow][nextCol] <= 'F' &&
				data.key & (1 << (map[nextRow][nextCol] - 'A')) &&
				(visit[data.key][nextRow][nextCol] > data.count + 1 || visit[data.key][nextRow][nextCol] == 0))
			{
				queuePush(&tail, nextRow, nextCol, data.count + 1, data.key, front);
			}
			else if (map[nextRow][nextCol] == '1')
			{
				if (min > data.count + 1)
					min = data.count + 1;
			}
		}

		front++;
	}

	if (min == INFMIN) min = -1;
	return min;
}

int main()
{
	int row, col, startRow, startCol;

	scanf("%d %d", &rowSize, &colSize);

	startRow = startCol = 0;
	for (row = 1; row <= rowSize; row++)
	{
		scanf("%s", &map[row][1]);
		map[row][0] = '#';
		map[row][colSize + 1] = '#';
		for (col = 1; col <= colSize && (startRow == 0 || row == 1); col++)
		{
			map[0][col] = '#';
			map[rowSize + 1][col] = '#';
			if (map[row][col] == '0')
			{
				startRow = row;
				startCol = col;
				map[row][col] = '.';
			}
		}
	}

	printf("%d", searchMaze(startRow, startCol));

	return 0;
}