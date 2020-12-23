#include <iostream>

using namespace std;

int main(void)
{
	int x, y, z;
	int num = 0;
	cin >> x >> y >> z;

	for (int a = 0; a < x; a++)
	{
		for (int b = 0; b < y; b++)
		{
			for (int c = 0; c < z; c++)
			{
				cout << a << " " << b << " " << c << endl;
				num++;
			}
		}
	}
	cout << num << endl;

	return 0;
}