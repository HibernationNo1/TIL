#include <iostream>
using namespace std;
int main(void)
{
	int n;
	cin >> n;
	
	int max, min, tmp;
	cin >> tmp;

	max = tmp;
	min = tmp;

	for (int i = 2; i <= n; i++)
	{
		cin >> tmp;

		if (tmp >= max)
		{
			max = tmp;
		}
		else if (tmp <= min)
		{
			min = tmp;
		}
		cout << min << " " << max << endl;

	}

	return 0;
}