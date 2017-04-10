#include <stdio.h>

//https://www.acmicpc.net/problem/4574 - 스도미노쿠

#define DEBUG 0
#define MAX 9

int exitSudoku, sudokuBlankCount;
int sudoku[11][11];
char check[7][10][10];

void init()
{
	int row, col;

	exitSudoku = 0;
	for (row = 1; row <= MAX; row++)
	{
		for (col = 1; col <= MAX; col++)
		{
			sudoku[row][col] = 0;
			check[0][row][col] = 0;
			check[1][row][col] = 0;
			check[2][row][col] = 0;
			check[3][row][col] = 0;
			check[4][row][col] = 0;
		}
	}
}

void checkIn02(int row, int col, int value, int data)
{
	int y, x, index;

	sudoku[row][col] = value;
	if (data == 0)
		sudoku[row][col] = data;

	check[0][row][value] = data;
	check[1][value][col] = data;

	y = row / 3;
	if (row % 3 != 0)
		y++;
	x = col / 3;
	if (col % 3 != 0)
		x++;
	index = (y - 1) * 3 + x;
	check[2][index][value] = data;
}

int inputCheck(int row, int col, int value)
{
	int y, x, index;

	if (check[0][row][value] == 1)
		return 0;

	if (check[1][value][col] == 1)
		return 0;

	y = row / 3;
	if (row % 3 != 0)
		y++;
	x = col / 3;
	if (col % 3 != 0)
		x++;
	index = (y - 1) * 3 + x;

	if (check[2][index][value] == 1)
		return 0;

	return 1;
}

void sudominokuCheck(int count)
{
	int row, col, value1, value2;

	if (count == 0)
		exitSudoku = 1;

	if (exitSudoku == 1)
		return;

	for (row = 1; row <= MAX; row++)
	{
		for (col = 1; col <= MAX; col++)
		{
			if (check[5][row][col] == 0)
			{
				value1 = sudoku[row][col];
				if (col < MAX && check[5][row][col + 1] == 0)
				{
					value2 = sudoku[row][col + 1];

					if (value1 != value2 && check[6][value1][value2] == 0)
					{
						check[6][value1][value2] = check[6][value2][value1] = 1;
						check[5][row][col] = check[5][row][col + 1] = 1;

						sudominokuCheck(count - 2);

						check[6][value1][value2] = check[6][value2][value1] = 0;
						check[5][row][col] = check[5][row][col + 1] = 0;
					}
				}
				if (row < MAX && check[5][row + 1][col] == 0)
				{
					value2 = sudoku[row + 1][col];

					if (value1 != value2 && check[6][value1][value2] == 0)
					{
						check[6][value1][value2] = check[6][value2][value1] = 1;
						check[5][row][col] = check[5][row + 1][col] = 1;

						sudominokuCheck(count - 2);

						check[6][value1][value2] = check[6][value2][value1] = 0;
						check[5][row][col] = check[5][row + 1][col] = 0;
					}
				}
				return;
			}
		}
	}
}

void sudokuStart(int count)
{
	int row, col, number, flag;

	if (count == 0)
	{
		if (DEBUG)
		{
			printf("\n\nAnswer\n");
			printf("-----------------------------------\n");
			for (row = 1; row <= MAX; row++)
			{
				for (col = 1; col <= MAX; col++)
				{
					printf("%3d", sudoku[row][col]);
					if (col % 3 == 0)
						printf(" | ");
				}
				printf("\n");
				if (row % 3 == 0)
					printf("-----------------------------------\n");
			}
		}


		for (row = 1; row <= MAX; row++)
		{
			for (col = 1; col <= MAX; col++)
			{
				check[5][row][col] = check[4][row][col];
				check[6][row][col] = check[3][row][col];
			}
		}

		sudominokuCheck(sudokuBlankCount);
		if (exitSudoku == 1)
		{
			for (row = 1; row <= MAX; row++)
			{
				for (col = 1; col <= MAX; col++)
				{
					printf("%d", sudoku[row][col]);
				}
				printf("\n");
			}
			return;
		}
	}
	else
	{
		if (exitSudoku == 1)
			return;

		for (row = 1; row <= MAX; row++)
		{
			for (col = 1; col <= MAX; col++)
			{
				if (sudoku[row][col] == 0)
				{
					for (number = 1; number <= MAX; number++)
					{
						if (inputCheck(row, col, number))
						{
							flag = 0;
							checkIn02(row, col, number, 1);

							sudokuStart(count - 1);

							checkIn02(row, col, number, 0);
						}
					}
					return;
				}
			}
		}
	}
}

int main()
{
	int i, j, n, value1, value2, row, col, y, x, index, puzzleCount;
	char str1[5], str2[5];

	puzzleCount = 0;
	while (1)
	{
		scanf("%d", &n);
		if (n == 0)
			break;

		init();
		puzzleCount++;
		printf("Puzzle %d\n", puzzleCount);
		for (i = 0; i < n; i++)
		{
			scanf("%d %s %d %s", &value1, &str1, &value2, &str2);

			checkIn02(str1[0] - 'A' + 1, str1[1] - '0', value1, 1);
			checkIn02(str2[0] - 'A' + 1, str2[1] - '0', value2, 1);

			check[3][value1][value2] = 1;
			check[3][value2][value1] = 1;

			check[4][str1[0] - 'A' + 1][str1[1] - '0'] = 1;
			check[4][str2[0] - 'A' + 1][str2[1] - '0'] = 1;
		}

		for (i = 1; i <= MAX; i++)
		{
			scanf("%s", &str1);
			checkIn02(str1[0] - 'A' + 1, str1[1] - '0', i, 1);
			check[4][str1[0] - 'A' + 1][str1[1] - '0'] = 1;
		}

		if (DEBUG)
		{
			printf("\nSTART\n");
			printf("-----------------------------------\n");
			for (i = 1; i <= MAX; i++) {
				for (j = 1; j <= MAX; j++)
				{
					printf("%3d", sudoku[i][j]);
					if (j % 3 == 0)
						printf(" | ");
				}
				printf("\n");
				if (i % 3 == 0)
					printf("-----------------------------------\n");
			}
			for (i = 0; i < 5; i++)
			{
				printf("\n\nCase %d\n", i);
				printf("-----------------------------------\n");
				for (row = 1; row <= MAX; row++)
				{
					for (col = 1; col <= MAX; col++)
					{
						printf("%3d", check[i][row][col]);
						if (col % 3 == 0)
							printf(" | ");
					}
					printf("\n");
					if (row % 3 == 0)
						printf("-----------------------------------\n");
				}
			}
			printf("\n\n");
		}

		sudokuBlankCount = 81 - n * 2 - 9;
		sudokuStart(sudokuBlankCount);
	}

	return 0;
}