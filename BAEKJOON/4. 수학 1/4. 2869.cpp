#include <iostream>

using namespace std;

int main(void)
{
	int A, B, V;
	cin >> A >> B >> V;
	int x = (V - A) / (A - B);
	if (A == V)
	{
		cout << 1 << endl;
	}
	else if (x == 0)
	{
		cout << 2 << endl;
	}
	else if ((V - A) % (A - B) != 0)
	{
		cout << x + 2 << endl;
	}
	else
		cout << x + 1 << endl;



	return 0;

}