#include <iostream>

using namespace std;

int main(void)
{
	int A, B, C;
	cin >> A >> B >> C;
	int num;

	if (C <= B)
	{
		cout << -1 << endl;
	}
	else
	{
		num = A / (C - B);
		cout << num + 1 << endl;
	}

	return 0;

}