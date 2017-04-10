#include <iostream>
#include <string>
using namespace std;

//https://www.acmicpc.net/problem/1251 - 단어 나누기

void change(string &tmpString, int left, int right)
{
	int i, j = 0;
	char t;

	for (i = left; i <= (int)(left + right) / 2; i++)
	{
		t = tmpString[i];
		tmpString[i] = tmpString[right - j];
		tmpString[right - j] = t;
		j++;
	}
}

int main()
{
	string solution, inString, tmpString;
	int i, j;

	cin >> inString;
	solution = inString;

	for (i = 1; i < inString.length() - 1; i++)
	{
		for (j = i + 1; j < inString.length(); j++)
		{
			tmpString = inString;
			change(tmpString, 0, i - 1);
			change(tmpString, i, j - 1);
			change(tmpString, j, inString.length() - 1);

			if (solution > tmpString)
				solution = tmpString;
		}
	}

	cout << solution << endl;

	return 0;
}