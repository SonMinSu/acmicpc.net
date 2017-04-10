#include <stdio.h>

#define DEBUG 0

struct mapData
{
	int value;
	int dir;
};

struct cmdData
{
	int time;
	int dir;
};

int mapSize, appleCount, cmdCount;
struct mapData map[111][111];
struct cmdData cmd[111];

int main()
{
	int i, j;
	int tailY, tailX, frontY, frontX, y, x, ty, tx, time, cmdIndex;
	int dy[] = { -1, 0, 1, 0 }, dx[] = { 0, 1, 0, -1 };
	char t;

	scanf("%d", &mapSize);
	scanf("%d", &appleCount);

	frontY = frontX = tailY = tailX = 1;
	map[1][1].value = 1;
	map[1][1].dir = 1;
	for (i = 0; i < appleCount; i++)
	{
		scanf("%d %d", &y, &x);
		map[y][x].value = 2;
	}

	scanf("%d", &cmdCount);
	for (i = 0; i < cmdCount; i++)
	{
		scanf("%d %c", &cmd[i].time, &t);
		if (t == 'L')
			cmd[i].dir = 3;
		else
			cmd[i].dir = 1;
	}
	time = 0;
	cmdIndex = 0;
	while (1)
	{
		time++;
		y = frontY + dy[map[frontY][frontX].dir];
		x = frontX + dx[map[frontY][frontX].dir];

		if (y < 1 || y > mapSize || x < 1 || x > mapSize)	// º®¿¡ ´êÀ¸¸é
			break;
		if (map[y][x].value == 1)	// ÀÚ½ÅÀÇ ¸ö¿¡ ´êÀ¸¸é
			break;

		if (map[y][x].value != 2)
		{
			ty = tailY + dy[map[tailY][tailX].dir];
			tx = tailX + dx[map[tailY][tailX].dir];
			map[tailY][tailX].value = 0;
			tailY = ty;
			tailX = tx;
		}
		map[y][x].value = 1;
		map[y][x].dir = map[frontY][frontX].dir;
		frontY = y;
		frontX = x;

		if (cmdIndex < cmdCount && cmd[cmdIndex].time == time)
		{
			map[frontY][frontX].dir = (map[frontY][frontX].dir + cmd[cmdIndex].dir) % 4;
			cmdIndex++;
		}

		if (DEBUG)
		{
			printf("-----------------------\ntime : %d\n", time);
			for (i = 1; i <= mapSize; i++)
			{
				for (j = 1; j <= mapSize; j++)
				{
					printf("%3d", map[i][j].value);
				}
				printf("\n");
			}
		}
	}

	printf("%d\n", time);

	return 0;
}