#include <iostream>
using namespace std;


int main(void)
{
	int a, b, c;
	cin >> a >> b >> c;
	long long int d;
	double e;
	d = (long long)a + b + c;
	e = ((double)a + b + c) / 3;
	cout << d << endl;
	cout << fixed;
	cout.precision(1);
	cout << e << endl;
		return 0;
}