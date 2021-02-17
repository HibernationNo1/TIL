#include <iostream>
using namespace std;

int main(void)
{
	
	int a, n;
	cin >> n;

here:
		cin >> a;
		cout << a << endl;
		if (n-- != 1)
		{
			goto here;
		}

	return 0;
}