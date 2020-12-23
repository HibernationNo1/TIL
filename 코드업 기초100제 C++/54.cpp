#include <iostream>
using namespace std;

int main(void)
{
	bool a, b;
	cin >> a >> b;

	if (a && b)
	{
		cout << a << endl;
	}
	else
	{
		cout << (a && b) << endl;
	}

	return 0;
}