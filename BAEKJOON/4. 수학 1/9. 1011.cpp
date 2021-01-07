#include <iostream>
using namespace std;


int main(void)
{
	int t;
	cin >> t;

	for (int i = 0; i < t; i++)
	{
		
		int x, y;        // y-1 까지 최대한
		cin >> x >> y;
		int tmp = y - x;

		int n = 1, k1 = 0, k2 = 1;   
		int m = 1;
		while (1)
		{

			if ((k1 < tmp) && (tmp <= k2))
			{
				cout << n << endl;
				break;
			}
			else
			{
				if (n % 2 == 0)
				{
					k1 = k2;
					k2 = k2 + m;
					n++;
				}
				else
				{
					k1 = k2;
					k2 = k2 + m;
					m++;
					n++;
				}
			}
		}

		
	}
	return 0;
}