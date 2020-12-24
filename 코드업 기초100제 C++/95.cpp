#include <iostream>
using namespace std;
int num[10000] = {};
int main(void)
{
	int a,i;
	
	cin >> a;

	for (i = 1; i <= a; i++)
	{
		cin >> num[i];
	}
	
	for (i = a; i >= 1; i--)
	{
		if (i - 1 == 0)
		{
			cout << num[i] << endl;
			break;
		}
		else
		{
			if (num[i] < num[i - 1])
			{
				int x;
				x = num[i];
				num[i] = num[i - 1];
				num[i - 1] = x;
			}
		}
    }

	return 0;
}