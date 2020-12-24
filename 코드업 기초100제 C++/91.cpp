#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
	long long int series;
	int a, m, d, n;
	cin >> a >> m >> d >> n;

	
	for (int i = 1; i <= n; i++)
	{
		if (i == 1)
		{
			series = (long long)a;
		}
		else
		{
			series = series * m + d;
		}
	}
	cout << series << endl;
	
	return 0;
}