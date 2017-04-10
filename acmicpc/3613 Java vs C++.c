#include <stdio.h>

char list[111], translation[222];

int main()
{
	int index, len, underbarCheck, upperCheck, gap = 'a' - 'A';

	scanf("%s", list);

	underbarCheck = 0;
	upperCheck = 0;

	len = 0;
	for (index = 0; list[index] != '\0'; index++)
	{
		if ('A' <= list[index] && list[index] <= 'Z')
		{
			upperCheck = 1;
			if (underbarCheck == 1)
				break;

			translation[len] = '_';
			len++;
			translation[len] = list[index] + gap;
			len++;
		}
		else if (list[index] == '_')
		{
			underbarCheck = 1;
			if (upperCheck == 1)
				break;

			if (list[index + 1] == '\0' || list[index + 1] == '_')
			{
				underbarCheck = 1;
				upperCheck = 1;
				break;
			}
			else
			{
				if ('A' <= list[index + 1] && list[index + 1] <= 'Z')
				{
					upperCheck = 1;
					break;
				}
				index++;
				translation[len] = list[index] - gap;
				len++;
			}
		}
		else
		{
			translation[len] = list[index];
			len++;
		}
	}
	translation[len] = '\0';

	if (list[0] == '_' || (underbarCheck && upperCheck) || ('A' <= list[0] && list[0] <= 'Z'))
		printf("Error!\n");
	else
		printf("%s\n", translation);

	return 0;
}

/*
Input Test Case

abvd_a_b_C

acm_icpc_net
acmIcpcNet

long_and_mnemonic_identifier
longAndMnemonicIdentifier

java_identifier
javaIdentifier

a_b_c_d_e_f_g
aBCDEFG
*/