#include <stdio.h>

// https://www.acmicpc.net/problem/1614 - 영식이의 손가락

int main()
{
	long long int n, k, maximum;

	scanf("%lld %lld", &n, &k);

	if (n == 1)
		maximum = 8 * k;
	else if (n == 2)
	{
		maximum = (k / 2) * 8 + 7;
		if (k % 2 == 0)
			maximum -= 6;
	}
	else if (n == 3)
		maximum = 2 + 4 * k;
	else if (n == 4)
	{
		maximum = (k / 2) * 8 + 5;
		if (k % 2 == 0)
			maximum -= 2;
	}
	else if (n == 5)
		maximum = 8 * k + 4;

	printf("%lld", maximum);

	return 0;
}