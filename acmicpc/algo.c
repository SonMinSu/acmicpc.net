#include <stdio.h>

#define MAXSIZE 22
#define MAXDEPTH 5

int size, maxValue;
int dyx[4][2] = { { 1, 0 },{ 0, -1 },{ -1, 0 },{ 0, 1 } };	// 새로 map을 만들 때 채워 갈 방향(움직임과 반대)
int moveMap[MAXSIZE][MAXSIZE], check[MAXSIZE][MAXSIZE];

void make2048(int count, int(*map)[MAXSIZE])
{
	int dir, i, j, k, row, col, pivotRow, pivotCol, tmp, moveCheck, tRow, tCol;
	int *data;

	for (dir = 0; dir < 4; dir++)
	{
		// 초기화
		for (row = 0; row < size; row++)
			for (col = 0; col < size; col++)
				moveMap[row][col] = 0, check[row][col] = 0;

		moveCheck = 0;	// 움직였을 때, moveMap과 map의 차이가 없으면 0, 차이가 있으면 1
		for (i = 0; i < size; i++)
		{
			k = 0;
			// dir에 따른 moveMap에서의 기준점
			if (dir == 0) pivotRow = 0, pivotCol = i;
			else if (dir == 1) pivotRow = i, pivotCol = size - 1;
			else if (dir == 2) pivotRow = size - 1, pivotCol = i;
			else pivotRow = i, pivotCol = 0;

			for (j = 0; j < size; j++)
			{
				// map에서 진행 방향
				if (dir == 0) row = j, col = i;
				else if (dir == 1) row = i, col = size - j - 1;
				else if (dir == 2) row = size - j - 1, col = i;
				else row = i, col = j;

				if (map[row][col] != 0 && check[row][col] == 0)	// map[row][col] 이 비어있지 않고, 사용 된 적이 없으면
				{
					tRow = pivotRow + (k - 1) * dyx[dir][0];
					tCol = pivotCol + (k - 1) * dyx[dir][1];
					if (k > 0 && check[tRow][tCol] != 2 && moveMap[tRow][tCol] == map[row][col])	// 직전에 추가한 숫자가 증가 하지 않고, map[row][col]과 같으면
					{
						data = &moveMap[tRow][tCol];
						check[tRow][tCol] = 2;
						check[row][col] = 1;
						*data += map[row][col];
						if (*data > maxValue)
							maxValue = *data;
					}
					else
					{
						// 빈 곳에 추가
						data = &moveMap[pivotRow + k * dyx[dir][0]][pivotCol + k * dyx[dir][1]];
						*data = map[row][col];
						check[row][col] = 1;
						if (*data > maxValue)
							maxValue = *data;
						k++;
						j--;
					}
				}

				// 변화가 있는지 체크
				if (map[row][col] != moveMap[row][col])
					moveCheck = 1;
			}
		}

		if (moveCheck && count + 1 <= MAXDEPTH)	// 변화가 있고, 최대 움직임이 아니라면 다시 호출
			make2048(count + 1, moveMap);
	}
}

int main()
{
	int row, col, map[MAXSIZE][MAXSIZE];

	scanf("%d", &size);
	for (row = 0; row < size; row++)
		for (col = 0; col < size; col++)
			scanf("%d", &map[row][col]);

	maxValue = 0;
	make2048(1, map);
	printf("%d", maxValue);

	return 0;
}