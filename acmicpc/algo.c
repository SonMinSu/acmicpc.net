#include <stdio.h>

#define DEBUG 1
#define MAXNUMBER 10

int listSize;
int list[11];
int sum[11][11];
char checkList[11][11];

int validate(int index)
{
	int row;

	for (row = 1; row <= index; row++)
	{
		if (checkList[row][index] == '+' && sum[row][index] <= 0)
			return 0;
		else if (checkList[row][index] == '0' && sum[row][index] != 0)
			return 0;
		else if (checkList[row][index] == '-' && sum[row][index] >= 0)
			return 0;
	}

	return 1;
}

void makeSequence(int index)
{
	int i, row, sign;

	if (index > listSize)
	{
		for (i = 1; i <= listSize; i++)
			printf("%d ", list[i]);

		exit(0);
	}

	if (checkList[index][index] == '0')
	{
		list[index] = 0;

		makeSequence(index + 1);
	}
	else
	{
		sign = 1;
		if (checkList[index][index] == '-')
			sign = -1;

		for (i = 1; i <= MAXNUMBER; i++)
		{
			list[index] = i * sign;
			for (row = 1; row <= index; row++)
				sum[row][index] = sum[row][index - 1] + (i * sign);

			if (validate(index))
				makeSequence(index + 1);
		}
	}
}

int main()
{
	int row, col;

	scanf("%d", &listSize);

	for (row = 1; row <= listSize; row++)
	{
		for (col = row; col <= listSize; col++)
		{
			scanf(" %c", &checkList[row][col]);
		}
	}

	makeSequence(1);

	if (DEBUG)
	{
		for (row = 1; row <= listSize; row++)
		{
			for (col = 1; col <= listSize; col++)
			{
				printf("%3c", checkList[row][col]);
			}
			printf("\n");
		}
	}

	return 0;
}