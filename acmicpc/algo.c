#include <stdio.h>

int size, map[22][22], maxValue;
int dyx[4][2] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

void make2048(int dir, int max)
{
	int i, row, col, saveMap[22][22];

	for (row = 0; row < size; row++)
		for (col = 0; col < size; col++)
			saveMap[row][col] = map[row][col];

	for (i = 0; i < 4; i++)
	{
		if (i == 0)
		{

		}
	}

	for (row = 0; row < size; row++)
		for (col = 0; col < size; col++)
			map[row][col] = saveMap[row][col];
}

int main()
{
	int row, col;

	scanf("%d", &size);
	for (row = 0; row < size; row++)
		for (col = 0; col < size; col++)
			scanf("%d", &map[row][col]);

	maxValue = 0;
	make2048(-1, 0);
	printf("%d", maxValue);

	return 0;
}