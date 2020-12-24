#include <iostream>
using namespace std;

int main(void)
{
	int a,i;
	int num[10000] = {};
	cin >> a;

	for (i = 1; i <= a; i++)
	{
		cin >> num[i];
	}
	
	for (i = a; i >= 1; i--)
	{
		
		cout << num[i] << " ";
	}

	return 0;
}