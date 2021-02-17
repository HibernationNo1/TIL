#include <iostream>

using namespace std;

int main(void)
{
	int num[24] = {};
	int a;
	cin >> a;
	for (int i = 1; i <= a; i++)
	{
		int x; 
		cin >> x;
		num[x] ++;
	}
	for (int i = 1; i < 24; i++)
	{
		cout << num[i] << " ";
	}

	return 0;
}