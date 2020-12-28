#include <iostream>
#include <cstring>

using namespace std;

int main(void)
{
	int T;
	cin >> T;
	char test[21] = {};

	for (int i = 1; i <= T; i++)
	{
		int x;
		cin >> x >> test;

		for (int j = 0; j < strlen(test); j++)
		{
			for (int s = 1; s <= x; s++)
			{
				cout << test[j];
			}
		}
		cout << endl;

	}

	return 0;
}