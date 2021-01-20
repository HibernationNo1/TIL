#include <iostream>
using namespace std;

int main(void)
{
	int i, n;

	cin >> n;

	for (i = 1; i <=9 ; i++)
	{
		cout << n << " * " << i << " = " << i * n << '\n';
	}
	
	return 0;
}