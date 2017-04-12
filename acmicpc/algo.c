#include <stdio.h>

// https://www.acmicpc.net/problem/1194 - 달이 차오른다, 가자

#define QUEUESIZE 100000

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
struct checkMap visit[52][52];
struct queData queue[QUEUESIZE];

int queuePush(int *tail, int row, int col, int count, int key, int before)
{
	queue[*tail].row = row;
	queue[*tail].col = col;
	queue[*tail].count = count;
	queue[*tail].key = key;
	queue[*tail].before = before;
	*tail += 1;

	visit[row][col].count = count;
	visit[row][col].key = key;
}

int searchMaze(int startRow, int startCol)
{
	int front, tail, dir, nextRow, nextCol;
	int i, j;

	front = 0; tail = 0;
	queue[tail].row = startRow, queue[tail].col = startCol, queue[tail].count = 0, queue[tail].key = 0;
	tail++;

	while (front < tail)
	{
		for (dir = 0; dir < 4; dir++)
		{
			nextRow = queue[front].row + direction[dir][0];
			nextCol = queue[front].col + direction[dir][1];
			if (map[nextRow][nextCol] == '.' &&
				(visit[nextRow][nextCol].count > queue[front].count + 1 ||		// 움직임 횟수가 더 작거나
					visit[nextRow][nextCol].count == 0 ||						// 한 번도 방문 한 적이 없거나
					visit[nextRow][nextCol].key < queue[front].key))				// 열쇠를 더 많이 가지고있다면
			{
				queuePush(&tail, nextRow, nextCol, queue[front].count + 1, queue[front].key, front);
			}
			else if ('a' <= map[nextRow][nextCol] && map[nextRow][nextCol] <= 'f' &&
				(visit[nextRow][nextCol].count == 0 ||
					visit[nextRow][nextCol].count > queue[front].count + 1 ||
					visit[nextRow][nextCol].key < queue[front].key))
			{
				queuePush(&tail, nextRow, nextCol, queue[front].count + 1, queue[front].key | (1 << (map[nextRow][nextCol] - 'a')), front);
			}
			else if ('A' <= map[nextRow][nextCol] && map[nextRow][nextCol] <= 'F' &&
				queue[front].key & (1 << (map[nextRow][nextCol] - 'A')) &&
				visit[nextRow][nextCol].key < queue[front].key)
			{
				queuePush(&tail, nextRow, nextCol, queue[front].count + 1, queue[front].key, front);
			}
			else if (map[nextRow][nextCol] == '1')
			{
				for (i = 0; i <= front; i++)
				{
					printf("index : %3d, row : %3d, col : %3d, count : %3d, key : %3d, before : %3d\n", i, queue[i].row, queue[i].col, queue[i].count, queue[i].key, queue[i].before);
				}
				return queue[front].count + 1;
			}
		}

		front++;
	}

	return -1;
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