#include <iostream>
using namespace std;

int main(void)
{
	
	int a=1;

	while (a!=0)
	{
		cin >> a;
		if (a != 0)
		{
			cout << a << endl;
		}
		else if (a == 0)
			return 0;
	}

	return 0;
}