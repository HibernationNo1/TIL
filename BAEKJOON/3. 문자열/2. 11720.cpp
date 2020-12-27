#include <iostream>
using namespace std;

int main(void)
{
	int n, sum = 0;
	
	cin >> n ;
	char* s = new char[n+1];

	for (int i = 1; i <= n; i++)
	{
		cin >> s[i];
		sum = sum + s[i] - 48;

	}
	cout << sum << endl;

	delete s;
	return 0;
}