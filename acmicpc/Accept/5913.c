#include <stdio.h>

// https://www.acmicpc.net/problem/5913 - 준규와 사과

#define MAXSIZE 5

int map[5][5];
int dyx[4][2] = { { -1, 0 },{ 0, 1 },{ 1, 0 },{ 0, -1 } };
int wayCount;

void searchMap(int y, int x, int appleCount)
{
	int i, ty, tx;

	if (y == MAXSIZE - 1 && x == MAXSIZE - 1)
	{
		if (appleCount == 0)
			wayCount++;
		return;
	}

	map[y][x] = 1;

	for (i = 0; i < 4; i++)
	{
		ty = y + dyx[i][0];
		tx = x + dyx[i][1];
		if (ty < 0 || ty >= MAXSIZE || tx < 0 || tx >= MAXSIZE || map[ty][tx])
			continue;
		searchMap(ty, tx, appleCount - 1);
	}

	map[y][x] = 0;
}

int main()
{
	int i, y, x, k;

	scanf("%d", &k);
	for (i = 0; i < k; i++)
	{
		scanf("%d %d", &y, &x);
		map[y - 1][x - 1] = 1;
	}

	searchMap(0, 0, MAXSIZE*MAXSIZE - k - 1);

	printf("%d", wayCount);

	return 0;
}