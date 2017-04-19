#include <stdio.h>

int n, arr[222];

void quicksort(int low, int high)
{
	int mid, left, right, t;

	if (low < high)
	{
		mid = arr[(low + high) / 2];
		left = low - 1;
		right = high + 1;
		while (1)
		{
			do { left++; } while (arr[left] < mid);
			do { right--; } while (arr[right] > mid);
			if (left >= right) break;
			t = arr[left];
			arr[left] = arr[right];
			arr[right] = t;
		}
		quicksort(low, left - 1);
		quicksort(right + 1, high);
	}
}

int main()
{
	int i;

	scanf("%d", &n);

	for (i = 0; i < n; i++)
		scanf("%d", &arr[i]);

	quicksort(0, n - 1);

	for (i = 0; i < n; i++)
		printf("%4d", arr[i]);

	return 0;
}