#include <iostream>
using namespace std;

int main(void)
{
	int a;
	cin >> a;
	if (a < 0)
	{
		if (a % 2 == 0)
		{
			cout << "minus \neven" << endl;
		}
		else
		{
			cout << "minus \nodd" << endl;
		}
	}
	else
	{
		if (a % 2 == 0)
		{
			cout << "plus \neven" << endl;
		}
		else
		{
			cout << "plus \nodd" << endl;
		}
	}

	return 0;
}
