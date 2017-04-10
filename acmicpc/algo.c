#include <stdio.h>

int main()
{
	char list[111], translation[222];
	int i, listLen, translationLen, underbarCheck, upperCheck, gap = 'a' - 'A';

	scanf("%s", list);

	underbarCheck = 0;
	upperCheck = 0;
	for (listLen = 0; list[listLen] != '\0'; listLen++)
	{
		if (list[listLen] == '_')
			underbarCheck = 1;
		else if ('A' <= list[listLen] && list[listLen] <= 'Z')
			upperCheck = 1;
	}

	if ((underbarCheck && upperCheck) || ('A' <= list[0] && list[0] <= 'Z'))
		printf("Error!");
	else
	{
		translationLen = 0;
		for (i = 0; i < listLen; i++)
		{
			if (underbarCheck)
			{
				// Java로 인식 한 경우

			}
			else
			{
				// C++로 인식한 경우
			}
		}
	}

	return 0;
}