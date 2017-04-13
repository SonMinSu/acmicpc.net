#include <stdio.h>

// https://www.acmicpc.net/problem/3967 - 매직 스타

int sumMapping[6][4] = { { 0, 2, 5, 7 },{ 1, 2, 3, 4 },{ 0, 3, 6, 10 },{ 7, 8, 9, 10 },{ 1, 5, 8, 11 },{ 4, 6, 9, 11 } };
int useCheck[13], list[12];
char listToMap[12][2] = { { 0, 4 },{ 1, 1 },{ 1, 3 },{ 1, 5 },{ 1, 7 },{ 2, 2 },{ 2, 6 },{ 3, 1 },{ 3, 3 },{ 3, 5 },{ 3, 7 },{ 4, 4 } };
char mapToList[5][9] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0 },{ 0, 1, 0, 2, 0, 3, 0, 4, 0 },{ 0, 0, 5, 0, 0, 0, 6, 0, 0 },{ 0, 7, 0, 8, 0, 9, 0, 10, 0 },{ 0, 0, 0, 0, 11, 0, 0, 0, 0 } };
char map[5][10];

void makeHexagram(int index)
{
	int number, sum, row, col;

	if (index == 12)
	{
		for (row = 0; row < 6; row++)
		{
			sum = 0;
			for (col = 0; col < 4; col++)
			{
				sum += list[sumMapping[row][col]];
			}
			if (sum != 26) return;
		}

		for (number = 0; number < 12; number++)
			map[listToMap[number][0]][listToMap[number][1]] = list[number] + 'A' - 1;

		for (row = 0; row < 5; row++)
			printf("%s\n", map[row]);
		exit(0);
	}
	else if (list[index])
		makeHexagram(index + 1);
	else
	{
		for (number = 1; number <= 12; number++)
		{
			if (useCheck[number] == 0)
			{
				useCheck[number] = 1;
				list[index] = number;

				makeHexagram(index + 1);

				useCheck[number] = 0;
				list[index] = 0;
			}
		}
	}
}

int main()
{
	int row, col;

	for (row = 0; row < 5; row++)
	{
		scanf("%s", &map[row][0]);
		for (col = 0; col < 9; col++)
		{
			if ('A' <= map[row][col] && map[row][col] <= 'Z')
			{
				useCheck[map[row][col] - 'A' + 1] = 1;
				list[mapToList[row][col]] = map[row][col] - 'A' + 1;
			}
		}
	}

	makeHexagram(0);

	return 0;
}