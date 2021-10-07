#include <iostream>
using namespace std;

int main(void)
{
	int a;
	cin >> a;
	if ((a <= 100) && (90 <= a))
	{
		cout << "A" << endl;
	}
	else if ((a <= 89) && (70 <= a))
	{
		cout << "B" << endl;
	}
	else if ((a <= 69) && (40 <= a))
	{
		cout << "C" << endl;
	}
	else if ((a <= 39) && (0 <= a))
	{
		cout << "D" << endl;
	}

	return 0;
}
