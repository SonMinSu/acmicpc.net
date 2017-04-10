#include <stdio.h>

#define DEBUG 0
#define INF 99999999

int n, min;
int dy[] = { -1,0,1,0 }, dx[] = { 0,1,0,-1 };
char arr[55][55];

void process(int y, int x, int dir, int count)
{
	if (count >= min)
		return;

	if (arr[y][x] == '#')
	{
		if (count < min)
			min = count;
		return;
	}
	else if (arr[y][x] == '*')
		return;

	if (arr[y][x] == '.' || arr[y][x] == '!')
		process(y + dy[dir], x + dx[dir], dir, count);

	if (arr[y][x] == '!')
	{
		arr[y][x] = '*';
		process(y + dy[(dir + 1) % 4], x + dx[(dir + 1) % 4], (dir + 1) % 4, count + 1);	// 오른쪽으로 방향 전환
		process(y + dy[(dir + 3) % 4], x + dx[(dir + 3) % 4], (dir + 3) % 4, count + 1);	// 왼쪽으로 방향 전환
		arr[y][x] = '!';
	}
}

int main()
{
	int i, j, y, x;

	scanf("%d", &n);

	for (i = 1; i <= n; i++)
	{
		scanf("%s", &arr[i][1]);
		arr[0][i] = '*';
		arr[n + 1][i] = '*';
		arr[i][0] = '*';
		arr[i][n + 1] = '*';
	}

	y = -1;
	for (i = 1; i <= n && y == -1; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if (arr[i][j] == '#')
			{
				y = i;
				x = j;
				break;
			}
		}
	}

	arr[y][x] = '.';
	min = INF;
	for (i = 0; i < 4; i++)
		process(y, x, i, 0);

	if (DEBUG)
	{
		for (i = 0; i <= n + 1; i++)
		{
			for (j = 0; j <= n + 1; j++)
			{
				printf("%c", arr[i][j]);
			}
			printf("\n");
		}
	}

	if (min == INF) min = 0;
	printf("%d\n", min);

	return 0;
}