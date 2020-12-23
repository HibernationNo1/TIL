#include <iostream>

using namespace std;

int main(void)
{
	int a;
	cin >> hex >> a;
	for (int i = 1; i < 16; i++)
	{
		cout << hex <<uppercase<< a << "*" << i << "=" << a * i << endl;
	}

	return 0;
}