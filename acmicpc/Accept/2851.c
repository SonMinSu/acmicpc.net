#include <stdio.h>

// https://www.acmicpc.net/problem/2851 - ½´ÆÛ ¸¶¸®¿À

#define MAX 10

int abs(int a)
{
	return a > 0 ? a : a * -1;
}

int main()
{
	int i, sum, t;

	sum = 0;
	for (i = 0; i < MAX; i++)
	{
		scanf("%d", &t);
		if (sum + t <= 100)
			sum += t;
		else if (sum + t > 100)
		{
			if (abs(100 - sum) >= abs(100 - sum - t))
				sum = sum + t;
			break;
		}
		else
			break;
	}

	printf("%d", sum);

	return 0;
}