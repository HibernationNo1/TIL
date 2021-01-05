#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
	int a, b, c;
	cin >> a >> b >> c;
	int day = 1;
	while (1)
	{
		if ((day % a == 0) && (day % b == 0) && (day % c== 0))
		{
			cout << day << endl;
			break;
		}
		else
		{
			day++;
			continue;
		}
	}
	
	return 0;
}