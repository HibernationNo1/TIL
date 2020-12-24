#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
	long long int series;
	int a,r, n;
	cin >> a >> r >> n;
	if (n == 1)
	{
		series = a;
	}
	else
	{
		series = a * pow(r, n - 1);
	}
	cout << series << endl;

	return 0;
}