#include <stdio.h>

//https://www.acmicpc.net/problem/3108 - ·Î°í

struct square {
	int x1;
	int y1;
	int x2;
	int y2;
	char check;
};

int n, cnt;
struct square list[1001];

int min(int a, int b)
{
	return a > b ? b : a;
}

int max(int a, int b)
{
	return a > b ? a : b;
}

void process(int index)
{
	int i;

	list[index].check = 1;

	for (i = 0; i < n; i++)
	{
		if (list[i].check == 1)
			continue;

		if (list[index].x1 < list[i].x1 && list[i].x2 < list[index].x2 && list[index].y1 < list[i].y1 && list[i].y2 < list[index].y2)
			continue;
		if (list[i].x1 < list[index].x1 && list[index].x2 < list[i].x2 && list[i].y1 < list[index].y1 && list[index].y2 < list[i].y2)
			continue;
		if (list[i].y2 < list[index].y1 || list[index].x2 < list[i].x1 || list[index].y2 < list[i].y1 || list[i].x2 < list[index].x1)
			continue;

		process(i);
	}
}

int main()
{
	int i, x1, y1, x2, y2, start;

	cnt = 1;
	start = -999;

	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

		list[i].x1 = min(x1, x2);
		list[i].y1 = min(y1, y2);
		list[i].x2 = max(x1, x2);
		list[i].y2 = max(y1, y2);
		list[i].check = 0;

		if (((list[i].x1 == 0 || list[i].x2 == 0) && (list[i].y1 <= 0 && 0 <= list[i].y2)) ||
			((list[i].y1 == 0 || list[i].y2 == 0) && (list[i].x1 <= 0 && 0 <= list[i].x2)))
			start = i;
	}

	if (start >= 0)
		process(start);

	for (i = 0; i < n; i++)
	{
		if (list[i].check == 0)
		{
			process(i);
			cnt++;
		}
	}

	printf("%d\n", cnt - 1);

	return 0;
}