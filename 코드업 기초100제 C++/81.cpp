#include <iostream>

using namespace std;

int main(void)
{
	int a, b;
	cin >> a >> b;

	int c = 1;

	for (int i1 = 1; i1 <= a; i1++)
	{
		int d = 1;
		for (int i2 = 1; i2 <= b; i2++)
		{
			
			cout << c << " " << d << endl;
			d++;
		}
		c++;

	}

	return 0;
}